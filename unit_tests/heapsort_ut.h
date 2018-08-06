//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_HEAPSORT_UT_H
#define ALGORITHMS_HEAPSORT_UT_H

#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include "../unit_test_framework.h"
#include "../heapsort.h"

namespace KAGU {
    template<typename X>
    class heapsort_test : public method_test_with_complexity_analysis<X> {
    public:
        heapsort_test();

        ~heapsort_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);

    };

    template<typename X>
    heapsort_test<X>::heapsort_test() {
    }

    template<typename X>
    heapsort_test<X>::~heapsort_test() {

    }

    template<typename X>
    void heapsort_test<X>::initialize() {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for (int size = this->n_start; size <= this->n_end; size += this->n_step) {

            for (int r = 0; r < this->reruns; ++r) {
                std::vector<X> l0;
                std::vector<X> l1;
                for (int i = 0; i < size; ++i) {

                    X num = (X) dr(gen);
                    l0.push_back(num);
                    l1.push_back(num);
                }
                std::sort(l1.begin(), l1.end());

                this->store(size, r * 2, l0);
                this->store(size, r * 2 + 1, l1);
            }

        }
    }

    template<typename X>
    void heapsort_test<X>::cleanup() {

    }

    template<typename X>
    bool heapsort_test<X>::run_one_test(int data_size, int run_num, int &prec) {
        typename std::vector<X>::iterator it;

        std::vector<X> *unsorted = this->get_stored_inputs(data_size, run_num * 2), *sorted = this->get_stored_inputs(
                data_size, run_num * 2 + 1);

        if (sorted && unsorted) {

            X *temp_arr = (X *) calloc(data_size, sizeof(X));
            for (int i = 0; i < data_size; ++i) {
                temp_arr[i] = (*unsorted)[i];
            }
            int start = clock();
            heapsort(temp_arr, data_size);
            int stop = clock();

            prec = (stop - start);

            for (int i = 0; i < data_size; ++i) {
                assert(temp_arr[i] == (*sorted)[i]);
            }

        } else {
            throw unit_test_data_not_found();
        }

        return true;
    }
}


#endif //ALGORITHMS_HEAPSORT_UT_H
