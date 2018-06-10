//
// Created by sushant on 5/28/18.
//

#ifndef ALGORITHMS_LINKED_LIST_H
#define ALGORITHMS_LINKED_LIST_H
#include <stdlib.h>
#include <exception>
#include <iostream>

namespace KAGU {
    template<typename X>
    struct doubly_linked_list_node {
        X val;
        doubly_linked_list_node<X> *prev;
        doubly_linked_list_node<X> *next;
    };

    template<typename X>
    class doubly_linked_list {
    public:
        doubly_linked_list();

        doubly_linked_list(X* arr, size_t size);

        ~doubly_linked_list();

        virtual doubly_linked_list_node<X> *get_head();

        virtual doubly_linked_list_node<X> *get_tail();

        virtual void set_head(doubly_linked_list_node<X> *node);

        virtual void set_tail(doubly_linked_list_node<X> *node);

        virtual doubly_linked_list_node<X> *insert(const X &val);

        virtual doubly_linked_list_node<X> *insert_front(const X &val);

        virtual bool remove(const X &val);

        virtual bool remove_node(doubly_linked_list_node<X> *node);

        virtual size_t get_num_nodes();

    protected:
        size_t num_nodes;
        doubly_linked_list_node<X> *head;
        doubly_linked_list_node<X> *tail;

        virtual doubly_linked_list_node<X> *create_node(const X &val, doubly_linked_list_node<X> *parent = nullptr);

        virtual void free_list(doubly_linked_list_node<X> *node);
        virtual void delete_node(doubly_linked_list_node<X> *node);
    };

    template<typename X>
    doubly_linked_list<X>::doubly_linked_list() {
        this->num_nodes = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    template<typename X>
    doubly_linked_list<X>::doubly_linked_list(X *arr, size_t size) {
        this->num_nodes = 0;
        this->head = nullptr;
        this->tail = nullptr;

        for(size_t i = 0; i < size; ++i){
            this->insert(arr[i]);
        }
    }

    template<typename X>
    doubly_linked_list<X>::~doubly_linked_list() {
        if(this->get_head() != nullptr){
            this->free_list(this->get_head());
            this->head = nullptr;
            this->tail = nullptr;
        }
    }

    template<typename X>
    doubly_linked_list_node<X> *doubly_linked_list<X>::get_head() {
        return this->head;
    }

    template<typename X>
    doubly_linked_list_node<X> *doubly_linked_list<X>::get_tail() {
        return this->tail;
    }

    template<typename X>
    doubly_linked_list_node<X> *doubly_linked_list<X>::insert(const X &val) {
        doubly_linked_list_node<X> *parent = this->get_tail(), *output = nullptr;
        output = this->create_node(val, parent);
        if(output){
            if(this->get_head() == nullptr){
                this->set_head(output);
            }
            this->set_tail(output);
            ++this->num_nodes;
        }

        return output;
    }

    template<typename X>
    bool doubly_linked_list<X>::remove(const X &val) {
        doubly_linked_list_node<X> *cur =  this->get_head();
        while(cur != nullptr && cur->val != val){
            cur = cur->next;
        }
        if(cur){
            this->remove_node(cur);
            return true;
        }
        return false;
    }

    template<typename X>
    bool doubly_linked_list<X>::remove_node(doubly_linked_list_node<X> *node) {
        if(node){
            if(node->prev && node->next){
                node->prev->next = node->next;
                node->next->prev = node->prev;

                node->prev = nullptr;
                node->next = nullptr;
            }
            else if(node->prev){
                //Tail node
                node->prev->next = nullptr;
                this->set_tail(node->prev);

                node->prev = nullptr;
            }
            else{
                //Head node
                if(node->next)
                {
                    node->next->prev = nullptr;
                    this->set_head(node->next);
                    node->next = nullptr;
                }
                else{
                    this->set_head(nullptr);
                }

            }
            --this->num_nodes;
            this->delete_node(node);
            return true;
        }
        return false;
    }

    template<typename X>
    doubly_linked_list_node<X> *doubly_linked_list<X>::create_node(const X &val, doubly_linked_list_node<X> *parent) {
        try {
            doubly_linked_list_node<X> *output = (doubly_linked_list_node<X> *)calloc(sizeof(doubly_linked_list_node<X>), 1);
            output->val = val;
            if(parent != nullptr){
                parent->next = output;
                output->prev = parent;
            }
            return output;
        }
        catch (const std::exception &e ){
            std::cerr << e.what() << std::endl;
        }
        return nullptr;
    }

    template<typename X>
    void doubly_linked_list<X>::delete_node(doubly_linked_list_node<X> *node) {
        free(node);
    }

    template<typename X>
    void doubly_linked_list<X>::free_list(doubly_linked_list_node<X> *node) {
        doubly_linked_list_node<X> *cur = node, *next;
        while(cur != nullptr){
            next = cur->next;
            this->delete_node(cur);
            cur = next;
        }
    }

    template<typename X>
    void doubly_linked_list<X>::set_head(doubly_linked_list_node<X> *node) {
        this->head = node;
    }

    template<typename X>
    void doubly_linked_list<X>::set_tail(doubly_linked_list_node<X> *node) {
        this->tail = node;
    }

    template<typename X>
    size_t doubly_linked_list<X>::get_num_nodes() {
        return this->num_nodes;
    }

    template<typename X>
    doubly_linked_list_node<X> *doubly_linked_list<X>::insert_front(const X &val) {

        doubly_linked_list_node<X> *parent = nullptr, *output = nullptr, *head = nullptr;
        output = this->create_node(val, parent);
        if(output){
            head = this->get_head();
            if(head ){
                head->prev = output;
                output->next = head;
            }
            this->set_head(output);

            if(this->get_tail() == nullptr){
                this->set_tail(output);
            }
            ++this->num_nodes;
        }

        return output;
    }
}


#endif //ALGORITHMS_LINKED_LIST_H
