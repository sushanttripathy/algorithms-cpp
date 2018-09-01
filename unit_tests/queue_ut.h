//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_QUEUE_UT_H
#define ALGORITHMS_QUEUE_UT_H

#include <map>
#include <random>
#include <cassert>
#include "../data_structures/queue.h"
#include "../unit_test_framework.h"

namespace KAGU {
    template<typename X>
    class queue_push_pop_test : public method_test_with_complexity_analysis<X> {
    public:
        queue_push_pop_test();

        ~queue_push_pop_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int run_num, int &prec);

    };

    template<typename X>
    queue_push_pop_test<X>::queue_push_pop_test():method_test_with_complexity_analysis<X>(1000, 10000, 250, 3) {
    }

    template<typename X>
    queue_push_pop_test<X>::~queue_push_pop_test() {

    }

    template<typename X>
    void queue_push_pop_test<X>::initialize() {


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
    void queue_push_pop_test<X>::cleanup() {

    }

    template<typename X>
    bool queue_push_pop_test<X>::run_one_test(int data_size, int run_num, int &prec) {
        typename std::vector<X>::iterator it;
        std::vector<X> *p = this->get_stored_inputs(data_size, run_num);

        KAGU::queue<X> queue1(data_size), queue2(data_size);
        assert(queue1.empty());

        for (it = p->begin(); it != p->end(); ++it) {
            queue1.put(*it);
        }


        assert(!queue1.empty());
        assert(queue1.full());

        int dequeue_index = 0;

        while (!queue1.empty()) {
            assert(queue1.get() == (*p)[dequeue_index++]);
        }
        assert(queue1.empty());
        assert(!queue1.full());

        int start = clock();
        for (int i = 0; i < data_size; ++i) {
            queue2.put((X) i);
        }

        while (!queue2.empty()) {
            queue2.get();
        }
        int stop = clock();
        prec = (stop - start);

        return true;
    }


}

#endif //ALGORITHMS_QUEUE_UT_H
