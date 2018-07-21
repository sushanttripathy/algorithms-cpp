//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_QUEUE_UT_H
#define ALGORITHMS_QUEUE_UT_H

#include <map>
#include <random>
#include <cassert>
#include "../queue.h"
#include "../unit_test_framework.h"

namespace KAGU {
    template<typename X>
    class queue_push_pop_test : public method_test_with_complexity_analysis {
    public:
        queue_push_pop_test();

        ~queue_push_pop_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int &prec);

    protected:
        std::map<int, std::vector<std::vector < X>>> *data;
        int internal_index;
    };

    template<typename X>
    queue_push_pop_test<X>::queue_push_pop_test():method_test_with_complexity_analysis(1000, 10000, 250, 3) {
        this->internal_index = 0;
    }

    template<typename X>
    queue_push_pop_test<X>::~queue_push_pop_test() {

    }

    template<typename X>
    void queue_push_pop_test<X>::initialize() {
        this->data = new std::map<int , std::vector<std::vector<X>>>();

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dr(-50000.0, 50000.0);

        for(int size = this->n_start; size <= this->n_end; size += this->n_step ){
            std::vector<std::vector<X>> l;
            for(int r = 0; r < this->reruns; ++r){
                std::vector <X> l0;
                for(int i = 0; i < size; ++i){
                    l0.push_back((X)dr(gen));
                }
                l.push_back(l0);
            }
            this->data->insert(std::pair<int, std::vector<std::vector<X>>>(size, l));
        }
    }

    template<typename X>
    void queue_push_pop_test<X>::cleanup() {
        if (this->data){
            delete this->data;
            this->data = nullptr;
        }
    }

    template<typename X>
    bool queue_push_pop_test<X>::run_one_test(int data_size, int &prec) {
        typename std::vector <X>::iterator it;
        typename std::map<int, std::vector<std::vector<X>>>::iterator it1;
        it1 = this->data->find(data_size);
        std::vector<std::vector <X>> *p0 = &(it1->second);
        std::vector<X>*p = &((*p0)[this->internal_index%this->reruns]);
        ++this->internal_index;

        KAGU::queue<X> queue1(data_size), queue2(data_size);
        assert(queue1.empty());

        for(it = p->begin(); it != p->end(); ++it){
            queue1.put(*it);
        }


        assert(!queue1.empty());
        assert(queue1.full());

        int dequeue_index = 0;

        while(!queue1.empty()){
            assert(queue1.get() == (*p)[dequeue_index++]);
        }
        assert(queue1.empty());
        assert(!queue1.full());

        int start = clock();
        for(int i = 0; i < data_size; ++i){
            queue2.put((X)i);
        }

        while(!queue2.empty()){
            queue2.get();
        }
        int stop = clock();
        prec = (stop - start);

        return true;
    }


}

#endif //ALGORITHMS_QUEUE_UT_H
