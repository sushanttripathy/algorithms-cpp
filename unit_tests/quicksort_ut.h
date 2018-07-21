//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_QUICKSORT_UT_H
#define ALGORITHMS_QUICKSORT_UT_H

#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include "../unit_test_framework.h"
#include "../quicksort.h"

namespace KAGU {
    template<typename X>
    class quicksort_test : public method_test_with_complexity_analysis {
    public:
        quicksort_test();

        ~quicksort_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int &prec);

    protected:
        std::map<int, std::vector<std::vector<X>>> *unsorted;
        std::map<int, std::vector<std::vector<X>>> *sorted;
        int internal_index;
    };

    template<typename X>
    quicksort_test<X>::quicksort_test() {
        this->internal_index = 0;
    }

    template<typename X>
    quicksort_test<X>::~quicksort_test() {

    }

    template<typename X>
    void quicksort_test<X>::initialize() {
        this->sorted = new std::map<int , std::vector<std::vector<X>>>();
        this->unsorted = new std::map<int , std::vector<std::vector<X>>>();

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for(int size = this->n_start; size <= this->n_end; size += this->n_step ){
            std::vector<std::vector<X>> m0;
            std::vector<std::vector<X>> m1;
            for(int r = 0; r < this->reruns; ++r){
                std::vector <X> l0;
                std::vector <X> l1;
                for(int i = 0; i < size; ++i){

                    X num = (X)dr(gen);
                    l0.push_back(num);
                    l1.push_back(num);
                }
                m0.push_back(l0);
                std::sort(l1.begin(), l1.end());
                m1.push_back(l1);
            }
            this->unsorted->insert(std::pair<int, std::vector<std::vector<X>>>(size, m0));
            this->sorted->insert(std::pair<int, std::vector<std::vector<X>>>(size, m1));
        }
    }

    template<typename X>
    void quicksort_test<X>::cleanup() {
        if(this->sorted){
            delete this->sorted;
            delete this->unsorted;

            this->sorted = nullptr;
            this->unsorted = nullptr;
        }

    }

    template<typename X>
    bool quicksort_test<X>::run_one_test(int data_size, int &prec) {
        typename std::vector <X>::iterator it;
        typename std::map<int, std::vector<std::vector<X>>>::iterator it0;
        typename std::map<int, std::vector<std::vector<X>>>::iterator it1;

        it0 = this->unsorted->find(data_size);
        it1 = this->sorted->find(data_size);

        if(it0 != this->unsorted->end() && it1 != this->sorted->end()){

            std::vector<std::vector <X>> *p0 = &(it0->second);
            std::vector<std::vector <X>> *p1 = &(it1->second);

            std::vector<X>*q0 = &((*p0)[this->internal_index%this->reruns]);
            std::vector<X>*q1 = &((*p1)[this->internal_index%this->reruns]);

            ++this->internal_index;

            X *temp_arr = (X*)calloc(data_size, sizeof(X));
            for(int i = 0; i < data_size; ++i){
                temp_arr[i] = (*q0)[i];
            }
            int start = clock();
            quicksort(temp_arr, data_size);
            int stop = clock();

            prec = stop - start;

            for(int i = 0; i < data_size; ++i){
                assert(temp_arr[i] == (*q1)[i]);
            }

        }else{
            throw unit_test_data_not_found();
        }

        return true;
    }
}

#endif //ALGORITHMS_QUICKSORT_UT_H
