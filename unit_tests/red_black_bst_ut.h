//
// Created by sushant on 8/31/18.
//

#ifndef ALGORITHMS_RED_BLACK_BST_UT_H
#define ALGORITHMS_RED_BLACK_BST_UT_H

//
// Created by sushant on 7/23/18.
//


#include <map>
#include <random>
#include <cassert>
#include "../data_structures/red_black_bst.h"
#include "../unit_test_framework.h"
#include <algorithm>

namespace KAGU {

#define RB_BST_UNIT_TEST_SAMPLE_SIZE 10
    template<typename X>
    class red_black_bst_ut_insert : public method_test_with_complexity_analysis<X> {

    public:
        red_black_bst_ut_insert(int n_start, int n_end, int n_step);

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);
    };

    template<typename X>
    void red_black_bst_ut_insert<X>::initialize() {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for (int size = this->n_start; size <= this->n_end; size += this->n_step) {

            for (int r = 0; r < this->reruns; ++r) {
                std::vector<X> l0;
                for (int i = 0; i < size; ++i) {

                    X num = (X) dr(gen);
                    l0.push_back(num);
                }

                this->store(size, r, l0);
            }
        }
    }

    template<typename X>
    void red_black_bst_ut_insert<X>::cleanup() {
        method_test_with_complexity_analysis<X>::cleanup();
    }

    template<typename X>
    bool red_black_bst_ut_insert<X>::run_one_test(int data_size, int run_num, int &prec) {

        typename std::vector<X>::iterator it;
        std::vector<X> *p = this->get_stored_inputs(data_size, run_num);

        KAGU::red_black_binary_search_tree<X> red_black_binary_search_tree1;

        X *random_sample = (X*)calloc(sizeof(X), RB_BST_UNIT_TEST_SAMPLE_SIZE);
        int cnt = 0,ind = 0;
        int step = p->size()/RB_BST_UNIT_TEST_SAMPLE_SIZE;

        for (it = p->begin(); it != p->end(); ++it) {
            red_black_binary_search_tree1.insert(*it);
            if(cnt % step == 0 && ind < RB_BST_UNIT_TEST_SAMPLE_SIZE){
                random_sample[ind++] = *it;
            }
            ++cnt;
        }


        int start = clock();
        for (int i  = 0; i < ind; ++i )
            red_black_binary_search_tree1.insert(random_sample[i]);
        int stop = clock();
        prec = (stop - start);
        free(random_sample);
        return true;
    }

    template<typename X>
    red_black_bst_ut_insert<X>::red_black_bst_ut_insert(int n_start, int n_end, int n_step)
            :method_test_with_complexity_analysis<X>(n_start, n_end, n_step,6) {

    }


    template<typename X>
    class red_black_bst_ut_remove : public method_test_with_complexity_analysis<X> {

    public:
        red_black_bst_ut_remove(int n_start, int n_end, int n_step);

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);
    };

    template<typename X>
    void red_black_bst_ut_remove<X>::initialize() {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for (int size = this->n_start; size <= this->n_end; size += this->n_step) {

            for (int r = 0; r < this->reruns; ++r) {
                std::vector<X> l0;
                for (int i = 0; i < size; ++i) {

                    X num = (X) dr(gen);
                    l0.push_back(num);
                }

                this->store(size, r, l0);
            }
        }
    }

    template<typename X>
    void red_black_bst_ut_remove<X>::cleanup() {
        method_test_with_complexity_analysis<X>::cleanup();
    }

    template<typename X>
    bool red_black_bst_ut_remove<X>::run_one_test(int data_size, int run_num, int &prec) {
        typename std::vector<X>::iterator it;
        std::vector<X> *p = this->get_stored_inputs(data_size, run_num);

        KAGU::red_black_binary_search_tree<X> red_black_binary_search_tree1;

        X *random_sample = (X*)calloc(sizeof(X), RB_BST_UNIT_TEST_SAMPLE_SIZE);
        int cnt = 0,ind = 0;
        int step = p->size()/RB_BST_UNIT_TEST_SAMPLE_SIZE;

        for (it = p->begin(); it != p->end(); ++it) {
            red_black_binary_search_tree1.insert(*it);
            if(cnt % step == 0 && ind < RB_BST_UNIT_TEST_SAMPLE_SIZE){
                random_sample[ind++] = *it;
            }
            ++cnt;
        }



        int start = clock();
        for (int i  = 0; i < ind; ++i)
            red_black_binary_search_tree1.remove(random_sample[i]);
        int stop = clock();

        prec = (stop - start);
        free(random_sample);
        return true;
    }

    template<typename X>
    red_black_bst_ut_remove<X>::red_black_bst_ut_remove(int n_start, int n_end, int n_step)
            :method_test_with_complexity_analysis<X>(n_start, n_end, n_step, 6) {

    }


    template<typename X>
    class red_black_bst_ut_find : public method_test_with_complexity_analysis<X> {
    public:
        red_black_bst_ut_find(int n_start, int n_end, int n_step);

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);
    };

    template<typename X>
    void red_black_bst_ut_find<X>::initialize() {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for (int size = this->n_start; size <= this->n_end; size += this->n_step) {

            for (int r = 0; r < this->reruns; ++r) {
                std::vector<X> l0;
                for (int i = 0; i < size; ++i) {

                    X num = (X) dr(gen);
                    l0.push_back(num);
                }

                this->store(size, r, l0);
            }
        }

    }

    template<typename X>
    void red_black_bst_ut_find<X>::cleanup() {

        method_test_with_complexity_analysis<X>::cleanup();
    }

    template<typename X>
    bool red_black_bst_ut_find<X>::run_one_test(int data_size, int run_num, int &prec) {
        typename std::vector<X>::iterator it, it2;
        std::vector<X> *p = this->get_stored_inputs(data_size, run_num);

        KAGU::red_black_binary_search_tree<X> red_black_binary_search_tree1;

        X *random_sample = (X*)calloc(sizeof(X), RB_BST_UNIT_TEST_SAMPLE_SIZE);
        int cnt = 0,ind = 0;
        int step = p->size()/RB_BST_UNIT_TEST_SAMPLE_SIZE;

        for (it = p->begin(); it != p->end(); ++it) {
            red_black_binary_search_tree1.insert(*it);
            if(cnt % step == 0 && ind < RB_BST_UNIT_TEST_SAMPLE_SIZE){
                random_sample[ind++] = *it;
            }
            ++cnt;
        }

        bst_node<X> *res = nullptr;

        int start = clock();

        for (int i = 0; i < ind; ++i)
            res =red_black_binary_search_tree1.find(random_sample[i]);
        int stop = clock();
        prec = (stop - start);

        free(random_sample);

        assert(res!= nullptr);


        return true;
    }

    template<typename X>
    red_black_bst_ut_find<X>::red_black_bst_ut_find(int n_start, int n_end, int n_step)
            :method_test_with_complexity_analysis<X>(n_start, n_end, n_step, 6) {

    }


    template<typename X>
    class red_black_bst_ut : public class_test {
        void initialize() {

            red_black_bst_ut_insert<X> *method_test1 = new red_black_bst_ut_insert<X>(50000, 100000, 1000);
            red_black_bst_ut_remove<X> *method_test2 = new red_black_bst_ut_remove<X>(50000, 100000, 1000);
            red_black_bst_ut_find<X> *method_test3 = new red_black_bst_ut_find<X>(50000, 100000, 1000);

            method_test1->add_descriptive_strings("Running Red-Black BST insertion tests with complexity analyses", empty);
            method_test2->add_descriptive_strings("Running Red-Black BST removal tests with complexity analyses", empty);
            method_test3->add_descriptive_strings("Running Red-Black BST search tests with complexity analyses", empty);


            this->add_method_test(method_test1);
            this->add_method_test(method_test2);
            this->add_method_test(method_test3);
        };

        void cleanup() {
            if (this->data) {
                typename std::vector<method_test_base *>::iterator it0;
                for (it0 = this->data->begin(); it0 != this->data->end(); ++it0) {
                    delete (*it0);
                }
            }
        }
    };
};


#endif //ALGORITHMS_RED_BLACK_BST_UT_H
