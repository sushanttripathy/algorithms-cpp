//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_STACK_UT_H
#define ALGORITHMS_STACK_UT_H

#include <map>
#include <random>
#include <cassert>
#include "../stack.h"
#include "../unit_test_framework.h"
namespace KAGU{
    template <typename X>
    class stack_push_pop_test:public method_test_with_complexity_analysis{
    public:
        stack_push_pop_test();
        ~stack_push_pop_test();

        void initialize();

        void cleanup();

        bool run_one_test(int data_size, int &prec);

    protected:
        std::map<int , std::vector<std::vector<X>>> *data;
        int internal_index;
    };

    template<typename X>
    stack_push_pop_test<X>::stack_push_pop_test():method_test_with_complexity_analysis(1000, 100000, 1000, 3) {
        this->internal_index = 0;

    }

    template<typename X>
    stack_push_pop_test<X>::~stack_push_pop_test() {

    }

    template<typename X>
    void stack_push_pop_test<X>::initialize() {
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
    void stack_push_pop_test<X>::cleanup() {
        if (this->data){
            delete this->data;
            this->data = nullptr;
        }
    }



    template<typename X>
    bool stack_push_pop_test<X>::run_one_test(int data_size, int &prec) {
        typename std::vector <X>::iterator it;
        typename std::map<int, std::vector<std::vector<X>>>::iterator it1;
        it1 = this->data->find(data_size);
        std::vector<std::vector <X>> *p0 = &(it1->second);
        std::vector<X>*p = &((*p0)[this->internal_index%this->reruns]);
        ++this->internal_index;

        KAGU::stack<X> stack1(data_size), stack2(data_size);
        assert(stack1.empty());

        for(it = p->begin(); it != p->end(); ++it){
            stack1.push(*it);
        }


        assert(!stack1.empty());
        assert(stack1.full());

        int pop_index = data_size - 1;

        while(!stack1.empty()){
            assert(stack1.pop() == (*p)[pop_index--]);
        }
        assert(stack1.empty());
        assert(!stack1.full());

        int start = clock();
        for(int i = 0; i < data_size; ++i){
            stack2.push((X)i);
        }

        while(!stack2.empty()){
            stack2.pop();
        }
        int stop = clock();
        prec = (stop - start);

        return true;
    }

}

#endif //ALGORITHMS_STACK_UT_H
