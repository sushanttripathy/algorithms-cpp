//
// Created by sushant on 4/15/18.
//

#ifndef ALGORITHMS_SEGMENT_TREE_H
#define ALGORITHMS_SEGMENT_TREE_H

#include <stdlib.h>
#include <cstring>
#include <exception>

namespace KAGU {
#define DEFAULT_SEGMENT_TREE_SIZE 1024
    template<typename X>
    struct segment_tree_node {
        segment_tree_node<X> *left, *right, *parent;
        X value;
        size_t lo, hi;
    };

    template<typename X>
    class segment_tree {
    public:
        segment_tree(size_t size = DEFAULT_SEGMENT_TREE_SIZE);

        segment_tree(X *arr, size_t size);

        ~segment_tree();

        virtual X merge_func(const X &a, const X &b) = 0;

        virtual X not_found_value() = 0;

        virtual X null_value() = 0;

        virtual void update(size_t leaf_index, const X &update_val);

        virtual X get_range_func(size_t lo, size_t hi);

    private:
        int capacity;


        segment_tree_node<X> *root;
        segment_tree_node<X> **leaf_nodes;

        virtual segment_tree_node<X> *make_tree(X *arr, size_t lo, size_t hi, segment_tree_node<X> *parent = nullptr);

        virtual void free_nodes(segment_tree_node<X> *node);

        virtual X get_range_func_helper(size_t lo, size_t hi, segment_tree_node<X> *node);
    };

    template<typename X>
    segment_tree<X>::segment_tree(size_t size) {
        if (size) {
            this->leaf_nodes = (segment_tree_node<X> **) calloc(size, sizeof(segment_tree_node<X> *));
            this->capacity = size;
            X *temp = (X *) calloc(size, sizeof(X));
            this->root = this->make_tree(temp, 0, size - 1, nullptr);
        } else {
            this->leaf_nodes = nullptr;
            this->capacity = 0;
            this->root = nullptr;
        }
    }

    template<typename X>
    segment_tree<X>::segment_tree(X *arr, size_t size) {
        if (size) {
            this->leaf_nodes = (segment_tree_node<X> **) calloc(size, sizeof(segment_tree_node<X> *));
            this->capacity = size;
            this->root = this->make_tree(arr, 0, size - 1, nullptr);
        } else {
            this->leaf_nodes = nullptr;
            this->capacity = 0;
            this->root = nullptr;
        }
    }

    template<typename X>
    void segment_tree<X>::free_nodes(KAGU::segment_tree_node<X> *node) {
        if (node) {
            if (node->left) {
                this->free_nodes(node->left);
            }
            if (node->right) {
                this->free_nodes(node->right);
            }
            free(node);
        }
    }

    template<typename X>
    segment_tree<X>::~segment_tree() {
        if (this->root) {
            this->free_nodes(this->root);
            this->root = nullptr;
        }
        if (this->leaf_nodes) {
            free(this->leaf_nodes);
            this->leaf_nodes = nullptr;
            this->capacity = 0;
        }
    }

    template<typename X>
    void segment_tree<X>::update(size_t leaf_index, const X &update_val) {
        if (leaf_index < this->capacity) {
            segment_tree_node<X> *current = this->leaf_nodes[leaf_index];
            while (current) {
                current->value += update_val;
                current = current->parent;
            }
        }
    }

    template<typename X>
    X segment_tree<X>::get_range_func(size_t lo, size_t hi) {
        if (lo > hi) {
            size_t x = lo;
            hi = lo;
            lo = x;
        }
        if (this->capacity && this->root) {
            return this->get_range_func_helper(lo, hi, this->root);
        } else {
            return this->null_value();
        }
    }

    template<typename X>
    segment_tree_node<X> *segment_tree<X>::make_tree(X *arr, size_t lo, size_t hi, segment_tree_node<X> *parent) {
        try {
            segment_tree_node<X> *node = (segment_tree_node<X> *) calloc(1, sizeof(segment_tree_node<X>));
            node->lo = lo;
            node->hi = hi;
            node->parent = parent;
            if (lo == hi) {
                node->value = arr[lo];
                this->leaf_nodes[lo] = node;
            } else {
                size_t mid = (lo + hi) / 2;
                node->left = this->make_tree(arr, lo, mid, node);
                node->right = this->make_tree(arr, mid + 1, hi, node);
            }
            return node;
        } catch (std::exception &e) {
            //throw alloc error here
        }

        return nullptr;
    }

    template<typename X>
    X segment_tree<X>::get_range_func_helper(size_t lo, size_t hi, segment_tree_node<X> *node) {
        if (lo <= node->lo && hi >= node->hi) {
            return node->value;
        } else if (lo > node->hi || hi < node->lo) {
            return this->not_found_value();
        } else {
            return this->merge_func(this->get_range_func_helper(lo, hi, node->left),
                                    this->get_range_func_helper(lo, hi, node->right));
        }
    }
}

#endif //ALGORITHMS_SEGMENT_TREE_H
