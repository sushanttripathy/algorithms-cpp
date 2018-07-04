//
// Created by sushant on 6/24/18.
//

#ifndef ALGORITHMS_AUTO_SUGGEST_H
#define ALGORITHMS_AUTO_SUGGEST_H

#include <map>
#include <stdlib.h>
#include "priority_queue.h"
#include <array>

namespace KAGU {

#define NUM_RETURNED_MATCHES 10

    template<typename X, typename Y>
    struct auto_suggest_node {
    public:
        std::map<X, auto_suggest_node<X, Y> *> *children;
        std::map<X, Y> *end_weights;
        KAGU::priority_queue<long long, Y> *top_matches_ids;
        std::map<X, long long> *end_ids;
        auto_suggest_node<X, Y> *parent;

        auto_suggest_node() {
            this->children = new std::map<X, auto_suggest_node<X, Y> *>();
            this->end_weights = new std::map<X, Y>();
            this->top_matches_ids = new KAGU::priority_queue<long long, Y>(NUM_RETURNED_MATCHES);
            this->end_ids = new std::map<X, long long>();
            this->parent = nullptr;
        }

        ~auto_suggest_node() {
            delete this->children;
            delete this->end_weights;
            delete this->top_matches_ids;
            delete this->end_ids;
        }
    };

    template<typename X>
    struct entry_info {
    public:
        X *arr;
        size_t size;
    };


    template<typename X, typename Y>
    class auto_suggest {
    public:
        auto_suggest();

        ~auto_suggest();

        virtual void update_weight(X *arr, size_t arr_size, Y update);

        virtual void increment_weight(X *arr, size_t arr_size, Y increment);

        virtual void decrement_weight(X *arr, size_t arr_size, Y decrement);

        virtual std::array<X, NUM_RETURNED_MATCHES> get_best_matches(X *arr, size_t size);

    protected:
        std::map<long double, entry_info<X> *> *id_to_entry;
        long long increment_id;
        auto_suggest_node<X, Y> *root;

        virtual void deallocate_memory();

        virtual Y insert(X *arr, size_t arr_size, Y update);

        virtual Y upsert(X *arr, size_t arr_size, Y update);

        virtual Y update(X *arr, size_t arr_size, Y update);

        virtual bool get(X *arr, size_t arr_size, Y &val);

        virtual bool set(X *arr, size_t arr_size, Y update);

        virtual bool remove(X *arr, size_t arr_size, Y update);

        auto_suggest_node<X, Y> *make_chain(X *arr, size_t arr_size, Y weight, long long id, auto_suggest_node<X, Y> *parent);
    };

    template<typename X, typename Y>
    auto_suggest<X, Y>::auto_suggest() {
        this->increment_id = 0;
        this->id_to_entry = new std::map<long double, entry_info < X> * > ();
        this->root = new auto_suggest_node<X, Y>;
        this->root->parent = nullptr;

    }

    template<typename X, typename Y>
    auto_suggest<X, Y>::~auto_suggest() {
        this->deallocate_memory();

    }

    template<typename X, typename Y>
    void auto_suggest<X, Y>::update_weight(X *arr, size_t arr_size, Y update) {

    }

    template<typename X, typename Y>
    void auto_suggest<X, Y>::increment_weight(X *arr, size_t arr_size, Y increment) {

    }

    template<typename X, typename Y>
    void auto_suggest<X, Y>::decrement_weight(X *arr, size_t arr_size, Y decrement) {

    }

    template<typename X, typename Y>
    std::array<X, 10> auto_suggest<X, Y>::get_best_matches(X *arr, size_t size) {
        return std::array<X, 10>();
    }

    template<typename X, typename Y>
    void auto_suggest<X, Y>::deallocate_memory() {

    }

    template<typename X, typename Y>
    Y auto_suggest<X, Y>::insert(X *arr, size_t arr_size, Y update) {
        auto_suggest_node<X, Y> *cur = this->root;
        size_t i = 0;
        while (cur != nullptr && i < arr_size) {
            if (cur->children) {
                std::map<X, auto_suggest_node<X, Y> *>::iterator f = cur->children->find(arr[i]);
                if (f != cur->children->end()) {
                    cur = f->second;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        long long found_id = -1;

        if (i < arr_size) {
            found_id = this->increment_id++;

            cur->children->insert(std::pair<X, auto_suggest_node<X, Y> *>(arr[i],
                                                                      this->make_chain(arr + i + 1, arr_size - i - 1,
                                                                                       update, found_id, cur)));
        } else{
            std::map<X, long double> ::iterator f = cur->end_ids->find(arr[i-1]);
            if(f != cur->end_ids->end()){
                found_id = f->second;
            }
        }

        Y priority;
        do{
            cur->top_matches_ids->peek(priority);
            if(priority < update){
                cur->top_matches_ids->get();
                cur->top_matches_ids->put(found_id, update);
                cur = cur->parent;
            }
            else{
                break;
            }
        }while(cur->parent != nullptr);


        return update;
    }

    template<typename X, typename Y>
    Y auto_suggest<X, Y>::upsert(X *arr, size_t arr_size, Y update) {
        return nullptr;
    }

    template<typename X, typename Y>
    Y auto_suggest<X, Y>::update(X *arr, size_t arr_size, Y update) {
        return nullptr;
    }

    template<typename X, typename Y>
    bool auto_suggest<X, Y>::get(X *arr, size_t arr_size, Y &val) {
        return false;
    }

    template<typename X, typename Y>
    bool auto_suggest<X, Y>::set(X *arr, size_t arr_size, Y update) {
        return false;
    }

    template<typename X, typename Y>
    bool auto_suggest<X, Y>::remove(X *arr, size_t arr_size, Y update) {
        return false;
    }

    template<typename X, typename Y>
    auto_suggest_node<X, Y> *auto_suggest<X, Y>::make_chain(X *arr, size_t arr_size, Y weight, long long id, auto_suggest_node<X, Y> *parent) {
        if(arr_size == 1){
            auto_suggest_node<X, Y> *output = new auto_suggest_node<X, Y>;
            output->parent = parent;
            output->end_ids->insert(std::pair<X, long long >(arr[0], id));
            output->end_weights->insert(std::pair<X, Y>(arr[0], weight));
            output->top_matches_ids->put(id, weight);
            return output;
        }
        else if(arr_size > 1){
            auto_suggest_node<X, Y> *output = new auto_suggest_node<X, Y>;
            output->parent = parent;
            auto_suggest_node<X, Y> *child = this->make_chain(arr + 1, arr_size - 1, weight, id, output);
            output->children->insert(std::pair<X, auto_suggest_node<X, Y> *>(arr[0], child));
        }
        return nullptr;
    }

}


#endif //ALGORITHMS_AUTO_SUGGEST_H
