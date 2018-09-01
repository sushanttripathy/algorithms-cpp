//
// Created by sushant on 6/10/18.
//

#ifndef ALGORITHMS_BINARY_INDEXED_TREE_H
#define ALGORITHMS_BINARY_INDEXED_TREE_H

#include <stdlib.h>

namespace KAGU {
#define DEFAULT_BINARY_INDEXED_TREE_SIZE 1024

    template<typename X>
    class binary_indexed_tree {
    public:
        binary_indexed_tree(size_t size = DEFAULT_BINARY_INDEXED_TREE_SIZE);

        binary_indexed_tree(X *arr, size_t size);

        ~binary_indexed_tree();

        virtual X merge_func(const X &a, const X &b) = 0;

        virtual X initial_value() = 0;

        virtual X null_value() = 0;

        virtual void update(size_t leaf_index, const X &update_val);

        virtual X get_merge_func_until(size_t index);

    protected:
        X *arr;
        int capacity;


    };

    template<typename X>
    binary_indexed_tree<X>::binary_indexed_tree(size_t size) {
        if (size) {
            this->arr = (X *) calloc(size + 1, sizeof(X));
            this->capacity = size + 1;
        } else {
            this->arr = nullptr;
        }
    }

    template<typename X>
    binary_indexed_tree<X>::binary_indexed_tree(X *arr, size_t size) {
        if (size) {
            this->arr = (X *) calloc(size + 1, sizeof(X));
            this->capacity = size + 1;
            for (size_t i = 0; i < size; ++i) {
                this->update(i, arr[i]);
            }
        } else {
            this->arr = nullptr;
        }
    }

    template<typename X>
    binary_indexed_tree<X>::~binary_indexed_tree() {
        if (this->arr) {
            free(this->arr);
            this->arr = nullptr;
            this->capacity = 0;
        }
    }

    template<typename X>
    void binary_indexed_tree<X>::update(size_t leaf_index, const X &update_val) {
        if (this->arr && leaf_index + 1 < this->capacity) {
            int index = (int) leaf_index + 1;
            while (index < this->capacity) {
                this->arr[index] += update_val;
                index += index & (-index);
            }
        }
    }

    template<typename X>
    X binary_indexed_tree<X>::get_merge_func_until(size_t leaf_index) {
        if (leaf_index + 1 < this->capacity) {
            X output = this->initial_value();
            int index = (int) leaf_index + 1;
            while (index) {
                output = this->merge_func(output, this->arr[index]);
                index -= index & (-index);
            }
            return output;
        } else {
            return this->null_value();
        }
    }
}

#endif //ALGORITHMS_BINARY_INDEXED_TREE_H
