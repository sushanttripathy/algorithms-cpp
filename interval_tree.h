//
// Created by sushant on 5/20/18.
//

#ifndef ALGORITHMS_INTERVAL_TREE_H
#define ALGORITHMS_INTERVAL_TREE_H

#include "circular_queue.h"
#include "red_black_bst.h"
#include "doubly_linked_list.h"

//TODO: Implement a IntervalNodesCursor class which auto allocates and deallocates memory (it should extend a LinkedList Class)
//TODO: Implement a remove function
//TODO: Add a destroy_node function to binary search tree (replace the free function)

namespace KAGU {

#define DEFAULT_INTERVALS_POINTERS_SIZE 20000

    template<typename X>
    struct interval {
    public:
        X begin;
        X end;

        interval() {
        }

        interval(X a, X b) {
            if(a < b){
                this->begin = a;
                this->end = b;
            }else{
                this->begin = b;
                this->end = a;
            }
        }

        bool operator==(const interval<X> &in) {
            return this->begin == in.begin;
        }

        bool operator<(const interval<X> &in) {
            return this->begin < in.begin;
        }

        bool operator>(const interval<X> &in) {
            return this->begin > in.begin;
        }

        bool operator<=(const interval<X> &in) {
            return this->begin <= in.begin;
        }

        bool operator>=(const interval<X> &in) {
            return this->begin >= in.begin;
        }

        bool operator!=(const interval<X> &in) {
            return this->begin != in.begin;
        }


        bool is_overlapping(const interval<X> &in) const {
            if (this->begin <= in.begin && this->end >= in.begin) {
                return true;
            } else if (this->begin >= in.begin && this->begin <= in.end) {
                return true;
            }
            return false;
        }

        void merge(const interval<X> &in) {
            if (this->begin > in.begin) {
                this->begin = in.begin;
            }
            if (this->end < in.end) {
                this->end = in.end;
            }
        }

    };

    template<typename X>
    struct interval_tree_node : public rb_bst_node<interval<X>> {
        X max_end;
    };

    template <typename X>
    class interval_tree_results:public doubly_linked_list<interval<X>>{
    public:

        ~interval_tree_results() {

        }


        interval_tree_results() {

        }
    };




    template<typename X>
    class interval_tree : public red_black_binary_search_tree<interval<X>> {
    public:
        interval_tree(bool merge_overlapping_intervals = false);

        interval_tree(interval<X> *arr, size_t size, bool merge_overlapping_intervals = false);

        ~interval_tree();

        virtual bst_node <interval<X>> *insert_interval(X begin, X end);

        bst_node <interval<X>> *insert(const interval<X> &c);

//
        virtual size_t find_overlapping_intervals(X begin, X end, interval<X> *arr, size_t arr_size);

        virtual size_t find_overlapping_intervals(const interval<X> &intval, interval<X> *arr, size_t arr_size);

        virtual interval_tree_results<X> *find_overlapping_intervals(X begin, X end);

        virtual interval_tree_results<X> *find_overlapping_intervals(const interval<X> &intval);

        virtual void clear_results(interval_tree_results<X> *input);

        virtual void update_max_end(interval_tree_node<X> *node);

        void print_traversal_results(int traversal_type = binary_search_tree<interval<X>>::INORDER, bst_node<interval<X>> *node = NULL);
//
//        bool find_exact_interval(X begin, X end);
//
//        interval<X> *find_exact_interval(interval<X> intval);
//
//
//        bool remove_overlapping_intervals(interval<X> intval);
//
//        bool remove_exact_intervals(interval<X> intval);

    protected:
        bool merge_overlapping_intervals;

        size_t merge_intervals_helper(interval<X> *arr, size_t size);

        int num_intervals;

        bst_node <interval<X>> *create_node(const interval<X> &val, bst_node <interval<X>> *parent = NULL);

        interval_tree_node<X> **find_all_overlapping_intervals(const interval<X> &intval, size_t &size);

        static void get_all_overlaps(const interval<X> &intval, interval_tree_node<X> *node,
                              interval_tree_node<X> **arr, size_t &writepos);
        static void get_all_overlaps(const interval<X> &intval, interval_tree_node<X> *node,
                                      interval_tree_results<X> *linked_list);

        virtual bool rotate_left(rb_bst_node <interval<X>> *node);

        virtual bool rotate_right(rb_bst_node <interval<X>> *node);

    private:

//        bst_node<interval<X>> *find(const interval<X> & a);
//
//        bool remove(const interval<X>  &a);

    };

    template<typename X>
    interval_tree<X>::interval_tree(bool merge_overlapping_intervals_):red_black_binary_search_tree<interval<X>>() {
        this->merge_overlapping_intervals = merge_overlapping_intervals_;
        this->num_intervals = 0;
    };

    template<typename X>
    size_t interval_tree<X>::merge_intervals_helper(interval<X> *arr, size_t size) {
        if (size == 0 || size == 1)
            return size;

        size_t write_loc = 0;
        size_t read_loc = 0;

        while (read_loc < size - 1) {

            interval<X> current = arr[read_loc];
            bool done = false;
            while (!done) {
                if (read_loc + 1 < size && current.is_overlapping(arr[read_loc + 1])) {
                    current.merge(arr[read_loc + 1]);
                    ++read_loc;
                } else {

                    arr[write_loc] = current;
                    ++read_loc;
                    ++write_loc;
                    done = true;
                }
            }
        }
        return write_loc;
    }


    template<typename X>
    interval_tree<X>::interval_tree(interval<X> *arr, size_t size,
                                    bool merge_overlapping_intervals_):red_black_binary_search_tree<interval<X>>() {
        this->merge_overlapping_intervals = merge_overlapping_intervals_;
        heapsort(arr, size);

        if (this->merge_overlapping_intervals) {
            size = this->merge_intervals_helper(arr, size);
        }

        this->make_balanced_tree(arr, size);

    };

    template<typename X>
    bst_node <interval<X>> *interval_tree<X>::create_node(const interval<X> &val, bst_node <interval<X>> *parent) {
        try {
            interval_tree_node <X> *node = (interval_tree_node <X> *) calloc(sizeof(interval_tree_node < X > ),
                                                                             1), *cur;
            node->key = val;
            node->parent = parent;
            node->max_end = val.end;

            if (parent) {
                cur = (interval_tree_node <X> *) parent;
                while (cur) {
                    if (cur->max_end >= val.end) {
                        break;
                    } else {
                        cur->max_end = val.end;
                        cur = (interval_tree_node <X> *) cur->parent;
                    }
                }
            }

            return node;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }


    template<typename X>
    bst_node <interval<X>> *interval_tree<X>::insert_interval(X begin, X end) {
        interval<X> C(begin, end);
        return this->insert(C);
    }

    template<typename X>
    bst_node <interval<X>> *interval_tree<X>::insert(const interval<X> &c) {

        if (this->merge_overlapping_intervals) {
            size_t found = 0;
            interval_tree_node <X> **all_overlapping_nodes = this->find_all_overlapping_intervals(c, found);
            if (all_overlapping_nodes != NULL) {
                interval<X> d = c;
                for (size_t i = 0; i < found; ++i) {
                    d.merge(all_overlapping_nodes[i]->key);
                    red_black_binary_search_tree<interval<X>>::remove_node(all_overlapping_nodes[i]);
                }
                free(all_overlapping_nodes);
                red_black_binary_search_tree<interval<X>>::insert(d);
                this->num_intervals = this->num_intervals - found + 1;
            } else {
                red_black_binary_search_tree<interval<X>>::insert(c);
                ++this->num_intervals;
            }

        } else {
            red_black_binary_search_tree<interval<X>>::insert(c);
            ++this->num_intervals;
        }

    }

    template<typename X>
    interval_tree_node<X> **
    interval_tree<X>::find_all_overlapping_intervals(const interval<X> &intval, size_t &size) {
        interval_tree_node <X> *root = (interval_tree_node < X > *)
        this->get_root();
        if (this->root) {
            try {
                interval_tree_node <X> **output = (interval_tree_node <X> **) calloc(
                        sizeof(interval_tree_node < X > *), this->num_intervals);
                this->get_all_overlaps(intval, root, output, size);
                return output;
            }
            catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }


        return NULL;
    }

    template<typename X>
    interval_tree<X>::~interval_tree() {

    }

    template<typename X>
    void interval_tree<X>::get_all_overlaps(const interval<X> &intval, interval_tree_node<X> *node,
                                            interval_tree_node<X> **arr, size_t &writepos) {
        if(node){
            if (intval.is_overlapping(node->key)) {
                arr[writepos] = node;
                ++writepos;

                if (node->left && ((interval_tree_node<X> *) node->left)->max_end >= intval.begin){
                    interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->left, arr, writepos);
                }

                if(node->right  ){//&& ((interval_tree_node<X> *) node->right)->key.begin <= intval.end
                    interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->right, arr, writepos);
                }
            }
            else{
                if (node->left && ((interval_tree_node<X> *) node->left)->max_end >= intval.begin) {
                    if (((interval_tree_node<X> *) node->left)->key < node->key)
                        interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->left, arr, writepos);
                    else {
                        interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->left, arr, writepos);
                        if (node->right) {
                            interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->right, arr, writepos);
                        }
                    }
                } else if (node->right) {
                    interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->right, arr, writepos);

                }

            }
        }
    }

    template<typename X>
    bool interval_tree<X>::rotate_left(rb_bst_node <interval<X>> *node) {
        interval_tree_node <X> *right_child = (interval_tree_node <X> *) node->right, *np = (interval_tree_node <X> *) node;
        bool retval = red_black_binary_search_tree<interval<X>>::rotate_left(node);

        //Fix node first
        np->max_end = np->key.end;
        if (np->left && ((interval_tree_node <X> *) np->left)->max_end > np->max_end)
            np->max_end = ((interval_tree_node <X> *) np->left)->max_end;
        if (np->right && ((interval_tree_node <X> *) np->right)->max_end > np->max_end)
            np->max_end = ((interval_tree_node <X> *) np->right)->max_end;

        //Fixing the right child
        if (right_child && np->max_end > right_child->max_end)
            right_child->max_end = np->max_end;

        return retval;

    }

    template<typename X>
    bool interval_tree<X>::rotate_right(rb_bst_node <interval<X>> *node) {
        interval_tree_node < X > *parent = (interval_tree_node < X > *)
        this->get_parent(node);
        bool retval = red_black_binary_search_tree<interval<X>>::rotate_right(node);

        //Fix erstwhile parent's max_end
        if (parent) {
            parent->max_end = parent->key.end;
            if (parent->left && parent->left->key.end > parent->max_end)
                parent->max_end = parent->left->key.end;
            if (parent->right && parent->right->key.end > parent->max_end)
                parent->max_end = parent->right->key.end;

            //Fix node's max_end
            if (parent->max_end > ((interval_tree_node <X> *) node)->max_end) {
                ((interval_tree_node <X> *) node)->max_end = parent->max_end;
            }
        }


        return retval;
    }

    template<typename X>
    size_t interval_tree<X>::find_overlapping_intervals(X begin, X end, interval<X> *arr, size_t arr_size) {
        interval<X> C(begin, end);

        return this->find_overlapping_intervals(C, arr, arr_size);
    }

    template<typename X>
    size_t interval_tree<X>::find_overlapping_intervals(const interval<X> &intval, interval<X> *arr, size_t arr_size) {
        size_t found_num = 0;
        interval_tree_node <X> **found_nodes = this->find_all_overlapping_intervals(intval, found_num);

        if (!found_nodes) {
            return 0;
        } else {
            size_t i;
            for (i = 0; i < found_num && i < arr_size; ++i) {
                arr[i] = found_nodes[i]->key;
            }
            free(found_nodes);
            return i;
        }
    }




    template<typename X>
    std::ostream &operator<<(std::ostream &os, const KAGU::interval<X> &intval) {
        os << "(" << intval.begin << ',' << intval.end << ")";
        return os;
    }


    template<typename X>
    void interval_tree<X>::print_traversal_results(int traversal_type, bst_node<interval<X>> *n) {
        interval_tree_node <X> *node = (interval_tree_node <X> *)n;
        if (node == NULL) {
            node = (interval_tree_node <X> *)(this->get_root());
        }

        if (node != NULL) {

            bool rc_set = node->right != NULL;
            bool lc_set = node->left != NULL;

            switch (traversal_type) {
                case binary_search_tree<X>::INORDER:


                    if (lc_set || rc_set) {
                        std::cout << '[';
                    }
                    if (lc_set) {
                        this->print_traversal_results(traversal_type, node->left);
                        std::cout << ' ';
                    } else if (rc_set) {
                        std::cout << "* ";
                    }
                    std::cout << node->key << "|" << node->max_end;
                    if (rc_set) {
                        std::cout << ' ';
                        this->print_traversal_results(traversal_type, node->right);
                    } else if (lc_set) {
                        std::cout << " *";
                    }

                    if (lc_set || rc_set) {
                        std::cout << ']';
                    }
                    if (node == this->get_root()) {
                        std::cout << std::endl;
                    }
                    break;

                case binary_search_tree<X>::PREORDER:

                    if (lc_set || rc_set) {
                        std::cout << '[';
                    }
                    std::cout << node->key << "|" << node->max_end;
                    if (lc_set) {
                        std::cout << ' ';
                        this->print_traversal_results(traversal_type, node->left);
                    } else if (rc_set) {
                        std::cout << " *";
                    }

                    if (rc_set) {
                        std::cout << ' ';
                        this->print_traversal_results(traversal_type, node->right);
                    } else if (lc_set) {
                        std::cout << " *";
                    }

                    if (lc_set || rc_set) {
                        std::cout << ']';
                    }
                    if (node == this->get_root()) {
                        std::cout << std::endl;
                    }
                    break;

                case binary_search_tree<X>::POSTORDER:

                    if (lc_set || rc_set) {
                        std::cout << '[';
                    }

                    if (lc_set) {

                        this->print_traversal_results(traversal_type, node->left);
                        std::cout << ' ';
                    } else if (rc_set) {
                        std::cout << "* ";
                    }

                    if (rc_set) {
                        this->print_traversal_results(traversal_type, node->right);
                        std::cout << ' ';
                    } else if (lc_set) {
                        std::cout << "* ";
                    }

                    std::cout << node->key << "|" << node->max_end;

                    if (lc_set || rc_set) {
                        std::cout << ']';
                    }
                    if (node == this->get_root()) {
                        std::cout << std::endl;
                    }
                    break;
            }
        }
    }

    template<typename X>
    void interval_tree<X>::update_max_end(interval_tree_node<X> *node) {
                                                                                                                                                                                                                                                                                                                                      
    }

    template<typename X>
    interval_tree_results<X> *interval_tree<X>::find_overlapping_intervals(X begin, X end) {
        interval<X> C(begin, end);
        return this->find_overlapping_intervals(C);
    }

    template<typename X>
    interval_tree_results<X> *interval_tree<X>::find_overlapping_intervals(const interval<X> &intval) {
        interval_tree_results<X>* output = NULL;
        interval_tree_node <X> *root = (interval_tree_node < X > *)
                this->get_root();
        if (this->root) {
            try {
                output = (interval_tree_results<X>*) calloc(
                        sizeof(interval_tree_results<X>), 1);
                new(output) interval_tree_results<X>();
                this->get_all_overlaps(intval, root, output);
                return output;
            }
            catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        return NULL;
    }

    template<typename X>
    void interval_tree<X>::get_all_overlaps(const interval<X> &intval, interval_tree_node<X> *node,
                                            interval_tree_results<X> *linked_list) {
        if(node){
            if (intval.is_overlapping(node->key)) {
                linked_list->insert(node->key);


                if (node->left && ((interval_tree_node<X> *) node->left)->max_end >= intval.begin){
                    interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->left, linked_list);
                }

                if(node->right  ){//&& ((interval_tree_node<X> *) node->right)->key.begin <= intval.end
                    interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->right, linked_list);
                }
            }
            else{
                if (node->left && ((interval_tree_node<X> *) node->left)->max_end >= intval.begin) {
                    if (((interval_tree_node<X> *) node->left)->key < node->key)
                        interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->left, linked_list);
                    else {
                        interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->left, linked_list);
                        if (node->right) {
                            interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->right, linked_list);
                        }
                    }
                } else if (node->right) {
                    interval_tree<X>::get_all_overlaps(intval, (interval_tree_node <X> *) node->right, linked_list);

                }

            }
        }
    }

    template<typename X>
    void interval_tree<X>::clear_results(interval_tree_results<X> *input) {
        if(input){
            input->~interval_tree_results<X>();
            free(input);
        }
    }


}

#endif //ALGORITHMS_INTERVAL_TREE_H
