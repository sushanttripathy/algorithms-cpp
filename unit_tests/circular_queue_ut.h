//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_CIRCULAR_QUEUE_UT_H
#define ALGORITHMS_CIRCULAR_QUEUE_UT_H

#include <map>
#include <random>
#include <assert.h>
#include "../circular_queue.h"
#include "../unit_test_framework.h"

namespace KAGU {
    template<typename X>
    class circular_queue_push_pop_test : public method_test_with_complexity_analysis<X> {
    public:
        circular_queue_push_pop_test();

        ~circular_queue_push_pop_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);

    };

    template<typename X>
    circular_queue_push_pop_test<X>::circular_queue_push_pop_test():method_test_with_complexity_analysis<X>(1000, 50000,
                                                                                                            1000, 3) {
    }

    template<typename X>
    circular_queue_push_pop_test<X>::~circular_queue_push_pop_test() {

    }

    template<typename X>
    void circular_queue_push_pop_test<X>::initialize() {

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for (int size = this->n_start; size <= this->n_end; size += this->n_step) {

            for (int r = 0; r < this->reruns; ++r) {
                std::vector<X> l0;
                for (int i = 0; i < size; ++i) {
                    l0.push_back((X) dr(gen));
                }

                this->store(size, r, l0);
            }

        }
    }

    template<typename X>
    void circular_queue_push_pop_test<X>::cleanup() {
        if (this->data) {
            delete this->data;
            this->data = nullptr;
        }
    }

    template<typename X>
    bool circular_queue_push_pop_test<X>::run_one_test(int data_size, int run_num, int &prec) {
        typename std::vector<X>::iterator it;
        std::vector<X> *p = this->get_stored_inputs(data_size, run_num);

        KAGU::circular_queue<X> circular_queue1(data_size), circular_queue2(data_size);
        assert(circular_queue1.empty());

        for (it = p->begin(); it != p->end(); ++it) {
            circular_queue1.put(*it);
        }


        assert(!circular_queue1.empty());
        assert(circular_queue1.full());

        int circular_queue_dq_index = 0;

        while (!circular_queue1.empty()) {
            assert(circular_queue1.get() == (*p)[circular_queue_dq_index++]);
        }
        assert(circular_queue1.empty());
        assert(!circular_queue1.full());

        int start = clock();
        for (int i = 0; i < data_size; ++i) {
            circular_queue2.put((X) i);
        }

        while (!circular_queue2.empty()) {
            circular_queue2.get();
        }
        int stop = clock();
        prec = (stop - start);

        return true;
    }


}

#endif //ALGORITHMS_CIRCULAR_QUEUE_UT_H
