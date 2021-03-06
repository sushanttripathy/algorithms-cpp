//
// Created by sushant on 7/20/18.
//

#ifndef ALGORITHMS_UNIT_TEST_H
#define ALGORITHMS_UNIT_TEST_H

//TODO: Smooth the data-size vs. run-time data points?
// Might help with the random noise in the BST O estimations

#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <string>
#include <exception>
#include "algorithms/basic_statistics.h"

namespace KAGU {
#ifndef EMPTY_STRING
#define EMPTY_STRING
    const std::string empty = std::string();
#endif
    enum RUN_TIME_COMPLEXITY {
        LOG_N, N, N_LOG_N, N2, N3
    };

#ifndef UNIT_TEST_DATA_NOT_FOUND
#define UNIT_TEST_DATA_NOT_FOUND

    struct unit_test_data_not_found : public std::exception {
        const char *what() const throw() {
            return "Unable to find a suitable data-set.";
        }
    };

#endif

    class method_test_base {
    public:
        method_test_base() {

        }

        virtual ~method_test_base() {

        }

        virtual bool run() = 0;
    };

#define MAX_UNIT_TEST_RUNS_TO_SHOW 5

#define DEBUG_CALCULATIONS false
#define USE_RSS false

    template<typename X>
    class method_test_with_complexity_analysis : public method_test_base {
    public:
        method_test_with_complexity_analysis(int n_start = 1000, int n_end = 100000, int n_step = 2000, int reruns = 3);

        virtual ~method_test_with_complexity_analysis();

        virtual void initialize() = 0;

        virtual void cleanup();

        virtual bool run_one_test(int data_size, int run_num, int &precision_time) = 0;

        virtual bool run_tests(int n_start = 1000, int n_end = 10000, int n_step = 1000, int individual_set_reruns = 1,
                               int show_every_n_runs = 5,
                               const std::string &init_message = empty, const std::string &end_message = empty);

        virtual bool run();

        virtual void add_descriptive_strings(std::string init_message, std::string end_message);

    protected:
        int n_start, n_end, n_step, reruns;

        virtual void store(int n_size, int run_num, std::vector<X> &in);

        virtual std::vector<X> *get_stored_inputs(int n_size, int run_num);

        std::map<int, std::map<int, std::vector<X>>> *data;

        std::string init_message, end_message;

    };

    template<typename X>
    method_test_with_complexity_analysis<X>::method_test_with_complexity_analysis(int n_start, int n_end, int n_step,
                                                                                  int reruns) {
        this->n_start = n_start;
        this->n_end = n_end;
        this->n_step = n_step;
        this->reruns = reruns;
        this->data = nullptr;
    }

    template<typename X>
    method_test_with_complexity_analysis<X>::~method_test_with_complexity_analysis() {
        if (this->data) {
            delete this->data;
            this->data = nullptr;
        }
    }

    template<typename X>
    bool method_test_with_complexity_analysis<X>::run() {
        this->initialize();
        if (!this->init_message.length() && !this->end_message.length()) {
            this->run_tests(this->n_start, this->n_end, this->n_step, this->reruns);
        } else {
            this->run_tests(this->n_start, this->n_end, this->n_step, this->reruns, 5, this->init_message,
                            this->end_message);
        }

        this->cleanup();
    }

    template<typename X>
    bool
    method_test_with_complexity_analysis<X>::run_tests(int n_start, int n_end, int n_step, int individual_set_reruns,
                                                       int show_every_n_runs,
                                                       const std::string &init_message,
                                                       const std::string &end_message) {
        int size = int(float(n_end - n_start) / float(n_step) + 1);

        if (size < 1) {
            size = 1;
            n_start = 1000;
            n_end = 1000;
            n_step = 1;
        }

        double *run_times = (double *) calloc(size, sizeof(double));
        double *sizes = (double *) calloc(size, sizeof(double));
        int ind = 0;

        if (individual_set_reruns < 1) {
            individual_set_reruns = 1;
        }

        if (init_message == empty) {
            std::cout << std::endl << "Beginning unit test runs with time complexity analyses " << std::endl;
        } else {
            std::cout << std::endl << init_message << std::endl;
        }


        float total_runs = (float) size * (float) reruns;
        float completed_runs = 0.0;
        float progress = 0.0;
        int bar_width = 70;
        double total_time = 0;

        for (int n = n_start; n <= n_end; n += n_step) {
            double cur_timing = 0;
            int cur_run_count = 0;
            int clock_start;
            int clock_stop;
            int precision_time = -1;
            while (cur_run_count < individual_set_reruns) {

                clock_start = clock();
                this->run_one_test(n, cur_run_count, precision_time);
                clock_stop = clock();

                if (precision_time == -1)
                    cur_timing += double(clock_stop - clock_start) / double(CLOCKS_PER_SEC) * 1000;
                else
                    cur_timing += double(precision_time) / double(CLOCKS_PER_SEC) * 1000;
                ++cur_run_count;

                ++completed_runs;
                progress = completed_runs / total_runs;
                std::cout << "[";
                int pos = bar_width * progress;
                for (int g = 0; g < bar_width; ++g) {
                    if (g < pos) std::cout << "=";
                    else if (g == pos) std::cout << ">";
                    else std::cout << " ";
                }
                std::cout << "] " << int(progress * 100.0) << " %\r";
                std::cout.flush();

            }
            run_times[ind] = cur_timing / (double) individual_set_reruns;
            total_time += cur_timing;
            sizes[ind++] = (double) n;
        }
        std::cout << std::endl;

        if (show_every_n_runs > 0) {
            std::cout << "Input lengths (arbitrary units) and run times (ms) : " << std::endl << std::endl;
            int show_count = 0;

            for (ind = 0; ind < size; ++ind) {
                if (ind % show_every_n_runs == 0) {
                    std::cout << sizes[ind] << ", " << run_times[ind] << std::endl;
                    ++show_count;
                    if (show_count >= MAX_UNIT_TEST_RUNS_TO_SHOW)
                        break;
                }

            }
        }


        if (end_message == empty) {
            std::cout << std::endl << "Finished unit test runs, all tests passed in " << total_time << " ms"
                      << std::endl;
        } else {
            std::cout << std::endl << end_message << std::endl;
        }

        long double *x = (long double *) calloc(size - 1, sizeof(long double));
        long double *y = (long double *) calloc(size - 1, sizeof(long double));

        long double *diff_log_n = (long double *) calloc(size - 1, sizeof(long double));
        long double *diff_n = (long double *) calloc(size - 1, sizeof(long double));
        long double *diff_n_log_n = (long double *) calloc(size - 1, sizeof(long double));
        long double *diff_n2 = (long double *) calloc(size - 1, sizeof(long double));
        long double *diff_n3 = (long double *) calloc(size - 1, sizeof(long double));

        long double log_n_coeff = 0;
        long double n_coeff = 0;
        long double n_log_n_coeff = 0;
        long double n2_coeff = 0;
        long double n3_coeff = 0;

        for (ind = 1; ind < size; ++ind) {
            x[ind - 1] = (sizes[ind - 1] + sizes[ind]) / 2.0;
            y[ind - 1] = (run_times[ind] - run_times[ind - 1]) / (sizes[ind] - sizes[ind - 1]);

            if (DEBUG_CALCULATIONS)
                std::cout << x[ind - 1] << " , " << y[ind - 1] << std::endl;

            diff_log_n[ind - 1] = 1.0 / (x[ind - 1]);
            diff_n[ind - 1] = 1.0;
            diff_n_log_n[ind - 1] = (1.0 + std::log(x[ind - 1]));
            diff_n2[ind - 1] = 2 * x[ind - 1];
            diff_n3[ind - 1] = 3 * x[ind - 1] * x[ind - 1];

            log_n_coeff += y[ind - 1] * (x[ind - 1]);
            n_coeff += y[ind - 1];
            n_log_n_coeff += y[ind - 1] / diff_n_log_n[ind - 1];
            n2_coeff += y[ind - 1] / diff_n2[ind - 1];
            n3_coeff += y[ind - 1] / diff_n3[ind - 1];

        }

        log_n_coeff /= size;
        n_coeff /= size;
        n_log_n_coeff /= size;
        n2_coeff /= size;
        n3_coeff /= size;

        if(DEBUG_CALCULATIONS){
            std::cout << "Coefficients: " << std::endl;
            std::cout << log_n_coeff << std::endl;
            std::cout << n_coeff << std::endl;
            std::cout << n_log_n_coeff << std::endl;
            std::cout << n2_coeff << std::endl;
            std::cout << n3_coeff << std::endl;
            std::cout << std::endl;

        }


        for (ind = 0; ind < size - 1; ++ind) {
            diff_log_n[ind] *= log_n_coeff;
            diff_n[ind] *= n_coeff;
            diff_n_log_n[ind] *= n_log_n_coeff;
            diff_n2[ind] *= n2_coeff;
            diff_n3[ind] *= n3_coeff;
        }


        long double rss_log_n;
        long double rss_n;
        long double rss_n_log_n;
        long double rss_n2;
        long double rss_n3;

        if(USE_RSS){
            rss_log_n = get_residual_sum_of_squares<long double>(diff_log_n, y, size - 1);
            rss_n = get_residual_sum_of_squares<long double>(diff_n, y, size - 1);
            rss_n_log_n = get_residual_sum_of_squares<long double>(diff_n_log_n, y, size - 1);
            rss_n2 = get_residual_sum_of_squares<long double>(diff_n2, y, size - 1);
            rss_n3 = get_residual_sum_of_squares<long double>(diff_n3, y, size - 1);
        }
        else{
            rss_log_n = get_absolute_residual_sum<long double>(diff_log_n, y, size - 1);
            rss_n = get_absolute_residual_sum<long double>(diff_n, y, size - 1);
            rss_n_log_n = get_absolute_residual_sum<long double>(diff_n_log_n, y, size - 1);
            rss_n2 = get_absolute_residual_sum<long double>(diff_n2, y, size - 1);
            rss_n3 = get_absolute_residual_sum<long double>(diff_n3, y, size - 1);
        }



        if(DEBUG_CALCULATIONS){
            std::cout << rss_log_n << std::endl;
            std::cout << rss_n << std::endl;
            std::cout << rss_n_log_n << std::endl;
            std::cout << rss_n2 << std::endl;
            std::cout << rss_n3 << std::endl;
        }



        RUN_TIME_COMPLEXITY most_likely_runtime = LOG_N;
        long double min_rss = rss_log_n;

        if (rss_n < min_rss) {
            most_likely_runtime = N;
            min_rss = rss_n;
        }

        if (rss_n_log_n < min_rss) {
            most_likely_runtime = N_LOG_N;
            min_rss = rss_n_log_n;
        }

        if (rss_n2 < min_rss) {
            most_likely_runtime = N2;
            min_rss = rss_n2;
        }

        if (rss_n3 < min_rss) {
            most_likely_runtime = N3;
            min_rss = rss_n3;
        }

        std::cout << "Estimated time complexity is ";
        switch (most_likely_runtime) {
            case LOG_N:
                std::cout << "O(log(N))" << std::endl << std::endl;
                break;

            case N:
                std::cout << "O(N)" << std::endl << std::endl;
                break;

            case N_LOG_N:
                std::cout << "O(N*log(N))" << std::endl << std::endl;
                break;

            case N2:
                std::cout << "O(N^2)" << std::endl << std::endl;
                break;

            case N3:
                std::cout << "O(N^3)" << std::endl << std::endl;
                break;

        }

        free(run_times);
        free(sizes);
        free(x);
        free(y);
        free(diff_log_n);
        free(diff_n);
        free(diff_n_log_n);
        free(diff_n2);
        free(diff_n3);
        return true;
    }

    template<typename X>
    void method_test_with_complexity_analysis<X>::store(int n_size, int run_num, std::vector<X> &in) {
        if (!this->data) {
            this->data = new std::map<int, std::map<int, std::vector<X>>>();
        }

        typename std::map<int, std::map<int, std::vector<X>>>::iterator it0;
        typename std::map<int, std::vector<X>>::iterator it1;

        it0 = this->data->find(n_size);
        if (it0 == this->data->end()) {
            //insert everything
            std::map<int, std::vector<X>> ins;
            ins.insert(std::pair<int, std::vector<X>>(run_num, in));

            this->data->insert(std::pair<int, std::map<int, std::vector<X>>>(n_size, ins));
        } else {
            //n_size entry exists
            it1 = it0->second.find(run_num);
            if (it1 == it0->second.end()) {
                //insert run_num, vector pair
                it0->second.insert(std::pair<int, std::vector<X>>(run_num, in));
            } else {
                //replace the previous entry
                it1->second = in;
            }
        }
    }

    template<typename X>
    std::vector<X> *method_test_with_complexity_analysis<X>::get_stored_inputs(int n_size, int run_num) {
        if (!this->data)
            return nullptr;
        typename std::map<int, std::map<int, std::vector<X>>>::iterator it0;
        typename std::map<int, std::vector<X>>::iterator it1;

        it0 = this->data->find(n_size);
        if (it0 != this->data->end()) {
            it1 = it0->second.find(run_num);
            if (it1 != it0->second.end()) {
                return &(it1->second);
            }
        }
        return nullptr;
    }

    template<typename X>
    void method_test_with_complexity_analysis<X>::cleanup() {

    }

    template<typename X>
    void method_test_with_complexity_analysis<X>::add_descriptive_strings(std::string init_message,
                                                                          std::string end_message) {
        this->init_message = init_message;
        this->end_message = end_message;
    }


    template<typename X>
    class method_test : public method_test_base {
    public:
        method_test();

        virtual ~method_test();

        virtual void initialize() = 0;

        virtual void cleanup();

        virtual bool run_one_test(int run_num, int &precision_time) = 0;

        virtual bool run_tests(const std::string &init_message = empty, const std::string &end_message = empty);

        virtual bool run();

        virtual void add_descriptive_strings(std::string init_message, std::string end_message);

    protected:
        int n_runs;

        virtual void store(int index, std::vector<X> &in);

        virtual std::vector<X> *get_stored_inputs(int index);

        std::map<int, std::vector<X>> *data;

        std::string init_message, end_message;

    };

    template<typename X>
    method_test<X>::method_test() {

        this->n_runs = 0;
        this->data = nullptr;
    }

    template<typename X>
    method_test<X>::~method_test() {
        if (this->data) {
            delete this->data;
            this->data = nullptr;
        }
    }

    template<typename X>
    void method_test<X>::cleanup() {

    }

    template<typename X>
    bool
    method_test<X>::run_tests(const std::string &init_message, const std::string &end_message) {

        int size = this->n_runs;

        double total_run_time = 0;
        int ind = 0;

        if (init_message == empty) {
            std::cout << std::endl << "Beginning unit test runs " << std::endl;
        } else {
            std::cout << std::endl << init_message << std::endl;
        }


        float total_runs = (float) size;
        float completed_runs = 0.0;
        float progress = 0.0;
        int bar_width = 70;

        for (int n = 0; n <= this->n_runs; ++n) {
            double cur_timing = 0;

            int clock_start;
            int clock_stop;
            int precision_time = -1;


            clock_start = clock();
            this->run_one_test(n, precision_time);
            clock_stop = clock();

            if (precision_time == -1)
                cur_timing += (clock_stop - clock_start) / double(CLOCKS_PER_SEC) * 1000;
            else
                cur_timing += precision_time / double(CLOCKS_PER_SEC) * 1000;


            ++completed_runs;
            progress = completed_runs / total_runs;
            std::cout << "[";
            int pos = bar_width * progress;
            for (int g = 0; g < bar_width; ++g) {
                if (g < pos) std::cout << "=";
                else if (g == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << " %\r";
            std::cout.flush();


            total_run_time += cur_timing;
        }
        std::cout << std::endl;
        if (end_message == empty) {
            std::cout << std::endl << "Finished unit test runs, all tests passed in " << total_run_time << " ms"
                      << std::endl;
        } else {
            std::cout << std::endl << end_message << std::endl;
        }


        return true;
    }

    template<typename X>
    bool method_test<X>::run() {
        this->initialize();
        if (!this->init_message.length() && !this->end_message.length()) {
            this->run_tests();
        } else {
            this->run_tests(this->init_message,
                            this->end_message);
        }
        this->cleanup();
        return true;
    }

    template<typename X>
    void method_test<X>::store(int index, std::vector<X> &in) {
        if (!this->data) {
            this->data = new std::map<int, std::vector<X>>();
        }

        typename std::map<int, std::vector<X>>::iterator it1;

        it1 = this->data->find(index);
        if (it1 == this->data->end()) {
            //insert the vector
            this->data->insert(std::pair<int, std::vector<X>>(index, in));

        } else {
            //index entry exists
            it1->second = in;
        }

    }

    template<typename X>
    std::vector<X> *method_test<X>::get_stored_inputs(int index) {
        if (!this->data)
            return nullptr;

        typename std::map<int, std::vector<X>>::iterator it1;

        it1 = this->data->find(index);
        if (it1 != this->data->end()) {
            return &(it1->second);
        }

        return nullptr;
    }

    template<typename X>
    void method_test<X>::add_descriptive_strings(std::string init_message, std::string end_message) {
        this->init_message = init_message;
        this->end_message = end_message;
    }


    class class_test {
    public:
        class_test();

        ~class_test();

        virtual void initialize() = 0;

        virtual void cleanup();

        virtual void add_method_test(method_test_base *in);

        virtual bool run();

    protected:
        std::vector<method_test_base *> *data;
    };

    class_test::class_test() {
        this->data = new std::vector<method_test_base *>;
    }

    class_test::~class_test() {
        if (this->data) {
            delete this->data;
            this->data = nullptr;
        }
    }

    void class_test::add_method_test(method_test_base *in) {
        if (this->data) {
            this->data->push_back(in);
        }
    }

    bool class_test::run() {
        this->initialize();
        if (this->data) {
            typename std::vector<method_test_base *>::iterator it0;
            for (it0 = this->data->begin(); it0 != this->data->end(); ++it0) {
                (*it0)->run();
            }
        }
        this->cleanup();
        return true;
    }

    void class_test::cleanup() {

    }
};

#endif //ALGORITHMS_UNIT_TEST_H
