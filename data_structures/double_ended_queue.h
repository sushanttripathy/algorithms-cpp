//
// Created by sushant on 6/9/18.
//

#ifndef ALGORITHMS_DOUBLE_ENDED_QUEUE_H
#define ALGORITHMS_DOUBLE_ENDED_QUEUE_H

#include "doubly_linked_list.h"
namespace KAGU{
    template <typename X>
    class double_ended_queue: protected doubly_linked_list <X>{
    public:
        double_ended_queue();
        ~double_ended_queue();

        void put(const X &val);
        void put_left(const X &val);
        X get();
        X get_left();
        X &operator [](int ind);
        bool empty();

    protected:


    };

    template<typename X>
    KAGU::double_ended_queue<X>::double_ended_queue() {

    }

    template<typename X>
    KAGU::double_ended_queue<X>::~double_ended_queue() {

    }

    template<typename X>
    void KAGU::double_ended_queue<X>::put(const X &val) {
        this->insert(val);
    }

    template<typename X>
    void KAGU::double_ended_queue<X>::put_left(const X &val) {
        this->insert_front(val);
    }

    template<typename X>
    X KAGU::double_ended_queue<X>::get() {
        doubly_linked_list_node<X> *tail = this->get_tail();
        if(tail){
            X temp = tail->val;
            this->remove_node(tail);
            return temp;
        }
        return (X) 0;
    }

    template<typename X>
    X KAGU::double_ended_queue<X>::get_left() {
        doubly_linked_list_node<X> *head = this->get_head();
        if(head){
            X temp = head->val;
            this->remove_node(head);
            return temp;
        }
        return (X) 0;
    }

#ifndef ACCESSING_OUT_OF_BOUNDS_QUEUE_INDEX_DQ
#define ACCESSING_OUT_OF_BOUNDS_QUEUE_INDEX_DQ

    struct accessing_out_of_bounds_queue_index_dq : public std::exception {
        const char *what() const throw() {
            return "Error trying to access out of bounds queue index for a dynamic queue.";
        }
    };

#endif

    template<typename X>
    X &KAGU::double_ended_queue<X>::operator[](int ind) {
        if(ind >= 0 && ind < this->num_nodes){
            doubly_linked_list_node<X> *cur = this->get_head();
            while(cur && ind){
                cur = cur->next;
                --ind;
            }

            return cur->val;
        }
        else if(ind < 0 && ind*(-1) <= this->num_nodes){
            doubly_linked_list_node<X> *cur = this->get_tail();
            ++ind;
            while(cur && ind){
                cur = cur->prev;
                ++ind;
            }
            return cur->val;
        }
        else{
            //throw not available exception here
            throw accessing_out_of_bounds_queue_index_dq();
        }

    }

    template<typename X>
    bool KAGU::double_ended_queue<X>::empty() {
        if(this->num_nodes == 0){
            return true;
        }
        return false;
    }
}

#endif //ALGORITHMS_DOUBLE_ENDED_QUEUE_H
