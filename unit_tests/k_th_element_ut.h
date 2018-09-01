//
// Created by sushant on 7/23/18.
//

#ifndef ALGORITHMS_K_TH_ELEMENT_UT_H
#define ALGORITHMS_K_TH_ELEMENT_UT_H

#include <map>
#include <random>
#include <cassert>
#include "../algorithms/k_th_element.h"
#include "../unit_test_framework.h"
#include <algorithm>

namespace KAGU {
    template<typename X>
    class k_th_element_test : public method_test_with_complexity_analysis<X> {
    public:
        k_th_element_test();

        ~k_th_element_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);

    };

    template<typename X>
    k_th_element_test<X>::k_th_element_test() {

    }

    template<typename X>
    k_th_element_test<X>::~k_th_element_test() {

    }

    template<typename X>
    void k_th_element_test<X>::initialize() {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for(int size = this->n_start; size <= this->n_end; size += this->n_step ){

            for(int r = 0; r < this->reruns; ++r){
                std::vector <X> l0;
                std::vector <X> l1;
                for(int i = 0; i < size; ++i){
                    X temp = (X)dr(gen);
                    l0.push_back(temp);
                    l1.push_back(temp);
                }
                std::sort(l1.begin(), l1.end());

                this->store(size, 2*r, l0);
                this->store(size, 2*r+1, l1);
            }

        }
    }

    template<typename X>
    void k_th_element_test<X>::cleanup() {

    }

    template<typename X>
    bool k_th_element_test<X>::run_one_test(int data_size, int run_num, int &prec) {
        typename std::vector<X>::iterator it;

        std::vector<X> *unsorted = this->get_stored_inputs(data_size, run_num * 2), *sorted = this->get_stored_inputs(
                data_size, run_num * 2 + 1);

        if (sorted && unsorted) {

            X *temp_arr = (X *) calloc(data_size, sizeof(X));
            for (int i = 0; i < data_size; ++i) {
                temp_arr[i] = (*unsorted)[i];
            }
            int start = clock();

            int stop = clock();

            prec = stop - start;

            for (int i = 0; i < data_size; ++i) {
                assert(temp_arr[i] == (*sorted)[i]);
            }

        } else {
            throw unit_test_data_not_found();
        }

        return false;
    }
}

#endif //ALGORITHMS_K_TH_ELEMENT_UT_H
