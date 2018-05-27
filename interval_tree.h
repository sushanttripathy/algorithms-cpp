//
// Created by sushant on 5/20/18.
//

#ifndef ALGORITHMS_INTERVAL_TREE_H
#define ALGORITHMS_INTERVAL_TREE_H

#include "circular_queue.h"
#include "red_black_bst.h"

namespace KAGU {

#define DEFAULT_INTERVALS_POINTERS_SIZE 20000

    template <typename X>
    struct interval{
        X begin;
        X stop;
    };

    template<typename X>
    struct interval_tree_node : public rb_bst_node {
    public:
        X end;
        X get_begin(){
            return this->key;
        }
        X get_end(){
            return this->end;
        }

        X get_interval_width(){
            return (this->get_end() - this->get_begin());
        }
    };


    template <typename X>
    class interval_tree:public red_black_binary_search_tree <X>{
    public:
        interval_tree(bool merge_overlapping_intervals = false);
        interval_tree(interval<X> *arr, size_t size, bool merge_overlapping_intervals = false);

        ~interval_tree();

        bst_node<X>* insert(X begin, X end);
        bst_node<X>* insert(interval<X> intval);
        interval<X>*find_overlapping_intervals(X begin, X end);
        interval<X>*find_overlapping_intervals(interval <X> intval);

        interval <X>*find_exact_interval(X begin, X end);
        interval <X>*find_exact_interval(interval <X> intval);


        bool remove_overlapping_intervals(interval <X>intval);
        bool remove_exact_intervals(interval <X>intval);

    protected:
        bool merge_intervals;

        circular_queue <interval<X>**> *interval_pointer;


    private:
        bst_node <X>*insert(X val);
        bst_node<X> *find(X a);
        bool remove(X a);

    };
}

#endif //ALGORITHMS_INTERVAL_TREE_H
