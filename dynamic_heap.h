//
// Created by sushant on 6/13/18.
//

#ifndef ALGORITHMS_DYNAMIC_HEAP_H
#define ALGORITHMS_DYNAMIC_HEAP_H

#include <stdlib.h>
#include <vector>
#include "circular_queue.h"

//TODO: Make the circular queue size bounds tighter

namespace KAGU {
    template<typename X>
    struct dynamic_heap_node {
    public:
        X key;
        dynamic_heap_node<X> *left, *right, *parent;
    };

    template<typename X>
    class dynamic_heap {
    public:
        dynamic_heap(bool is_max_heap = true);

        dynamic_heap(X *arr, size_t size, bool is_max_heap = true);

        dynamic_heap(std::vector<X> *arr, bool is_max_heap = true);

        ~dynamic_heap();

        virtual void heappush(const X &x);

        virtual X heappop();

        virtual bool empty();

        virtual bool full();

        virtual size_t size();

        virtual int get_level(int sindex);

    private:
        virtual void heapify(X *arr, size_t size);

        virtual void percolate_up(dynamic_heap_node<X> *i);

        virtual void percolate_down(dynamic_heap_node<X> *i);

        virtual dynamic_heap_node<X> *create_node(const X &val, dynamic_heap_node<X> *parent = nullptr);

        virtual void swap_keys(dynamic_heap_node<X> *a, dynamic_heap_node<X> *b);

        virtual void free_heap(dynamic_heap_node<X> *node);

        virtual void delete_node(dynamic_heap_node<X> *node);

        virtual dynamic_heap_node<X> *get_node_with_index(int index);

        virtual dynamic_heap_node<X> *make_heap(X *arr, size_t size);

        bool is_max_heap;
        int contents;
        dynamic_heap_node<X> *root;
    };

    template<typename X>
    dynamic_heap<X>::dynamic_heap(bool is_max_heap) {
        this->contents = 0;
        this->is_max_heap = is_max_heap;
        this->root = nullptr;


    }

    template<typename X>
    dynamic_heap<X>::dynamic_heap(X *arr, size_t size, bool is_max_heap) {
        this->contents = 0;
        this->is_max_heap = is_max_heap;
        this->root = nullptr;

        this->heapify(arr, size);
    }

    template<typename X>
    dynamic_heap<X>::dynamic_heap(std::vector<X> *arr, bool is_max_heap) {
        this->contents = 0;
        this->is_max_heap = is_max_heap;
        this->root = nullptr;

    }

    template<typename X>
    dynamic_heap<X>::~dynamic_heap() {
        if (this->root) {
            this->free_heap(this->root);
            this->root = nullptr;
        }

    }

    template<typename X>
    void dynamic_heap<X>::heappush(const X &x) {
        if (this->contents) {
            //No need to push in to root
            int parent_index = (this->contents - 1) >> 1;
            dynamic_heap_node<X> *parent = this->get_node_with_index(parent_index);
            dynamic_heap_node<X> *child = this->create_node(x, parent);
            if ((this->contents - 1) % 2) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            this->percolate_up(child);
        } else {
            this->root = this->create_node(x, nullptr);
        }
    }

#ifndef POPPING_EMPTY_DYNAMIC_HEAP
#define POPPING_EMPTY_DYNAMIC_HEAP

    struct popping_empty_dynamic_heap : public std::exception {
        const char *what() const throw() {
            return "Unable to pop a key from an empty (dynamic) heap.";
        }
    };

#endif

    template<typename X>
    X dynamic_heap<X>::heappop() {

        if (this->contents > 1) {
            X temp = this->root->key;

            int parent_index = (this->contents - 2) >> 1;
            dynamic_heap_node<X> *parent = this->get_node_with_index(parent_index);

            if (parent->right) {
                this->swap_keys(parent->right, this->root);
                this->delete_node(parent->right);
                parent->right = nullptr;
            } else {
                this->swap_keys(parent->left, this->root);
                this->delete_node(parent->left);
                parent->left = nullptr;
            }
            this->percolate_down(this->root);
            return temp;
        } else if (this->contents == 1) {
            X temp = this->root->key;
            this->delete_node(this->root);
            this->root = nullptr;
            return temp;
        } else {
            throw popping_empty_dynamic_heap();
        }
    }

    template<typename X>
    bool dynamic_heap<X>::empty() {
        if (this->contents)
            return false;
        else
            return true;
    }

    template<typename X>
    bool dynamic_heap<X>::full() {
        return false;
    }

    template<typename X>
    void dynamic_heap<X>::heapify(X *arr, size_t size) {
        this->root = this->make_heap(arr, size);
        if (this->contents) {
            for (int i = this->contents / 2 - 1; i >= 0; --i) {
                this->percolate_down(this->get_node_with_index(i));
            }
        }
    }

    template<typename X>
    size_t dynamic_heap<X>::size() {
        return this->contents;
    }

    template<typename X>
    void dynamic_heap<X>::percolate_up(dynamic_heap_node<X> *i) {
        if (this->is_max_heap) {
            //Max heap
            if (i->parent) {
                if (i->key > i->parent->key) {
                    this->swap_keys(i, i->parent);
                    this->percolate_up(i->parent);
                }
            }
        } else {
            //Min heap
            if (i->parent) {
                if (i->key < i->parent->key) {
                    this->swap_keys(i, i->parent);
                    this->percolate_up(i->parent);
                }
            }

        }
    }

    template<typename X>
    void dynamic_heap<X>::percolate_down(dynamic_heap_node<X> *i) {
        if (this->is_max_heap) {
            //Max heap
            if (i->left && i->right) {
                if (i->key < i->right->key || i->key < i->left->key) {
                    if (i->left->key > i->right->key) {
                        this->swap_keys(i, i->left);
                        this->percolate_down(i->left);
                    } else {
                        this->swap_keys(i, i->right);
                        this->percolate_down(i->right);
                    }
                }
            } else if (i->left) {
                if (i->key < i->left->key) {
                    this->swap_keys(i, i->left);
                    this->percolate_down(i->left);
                }
            } else if (i->right) {
                if (i->key < i->right->key) {
                    this->swap_keys(i, i->right);
                    this->percolate_down(i->right);
                }
            }
        } else {
            //Min heap
            if (i->left && i->right) {
                if (i->key > i->right->key || i->key > i->left->key) {
                    if (i->left->key < i->right->key) {
                        this->swap_keys(i, i->left);
                        this->percolate_down(i->left);
                    } else {
                        this->swap_keys(i, i->right);
                        this->percolate_down(i->right);
                    }
                }
            } else if (i->left) {
                if (i->key > i->left->key) {
                    this->swap_keys(i, i->left);
                    this->percolate_down(i->left);
                }
            } else if (i->right) {
                if (i->key > i->right->key) {
                    this->swap_keys(i, i->right);
                    this->percolate_down(i->right);
                }
            }

        }

    }

    template<typename X>
    dynamic_heap_node<X> *dynamic_heap<X>::create_node(const X &val, dynamic_heap_node<X> *parent) {
        dynamic_heap_node<X> *output = nullptr;
        try {
            output = (dynamic_heap_node<X> *) calloc(1, sizeof(dynamic_heap_node<X>));
            output->key = val;
            output->parent = parent;
            ++this->contents;
        }
        catch (std::exception &e) {

        }
        return output;
    }

    template<typename X>
    void dynamic_heap<X>::free_heap(dynamic_heap_node<X> *node) {
        if (node) {
            if (node->left) {
                this->free_heap(node->left);
            }
            if (node->right) {
                this->free_heap(node->right);
            }
            this->delete_node(node);
        }
    }

    template<typename X>
    void dynamic_heap<X>::delete_node(dynamic_heap_node<X> *node) {
        if (node) {
            free(node);
            --this->contents;
        }
    }

    template<typename X>
    void dynamic_heap<X>::swap_keys(dynamic_heap_node<X> *a, dynamic_heap_node<X> *b) {
        X temp = a->key;
        a->key = b->key;
        b->key = temp;
    }

    template<typename X>
    int dynamic_heap<X>::get_level(int index) {
        int level = 0;
        int temp = index + 1;
        while (temp > 1) {
            ++level;
            temp = temp >> 1;
        }
        return level;
    }


    template<typename X>
    dynamic_heap_node<X> *dynamic_heap<X>::get_node_with_index(int index) {
        dynamic_heap_node<X> *current = this->root;
        int node_level_from_current = this->get_level(index);

        int current_index = 0;
        int dummy_index = index + 1;

        int temp;

        while (current_index != index and current_index < this->contents) {
            temp = (dummy_index >> (node_level_from_current - 1)) - 1;
            if (temp % 2) {
                current = current->left;
                current_index = (current_index << 1) + 1;
            } else {
                current = current->right;
                current_index = (current_index << 1) + 2;
            }
            --node_level_from_current;
        }
        return current;
    }

    template<typename X>
    dynamic_heap_node<X> *dynamic_heap<X>::make_heap(X *arr, size_t size) {
        if (size) {
            KAGU::circular_queue<dynamic_heap_node<X> *> bfs(size);
            dynamic_heap_node<X> *output = this->create_node(arr[0], nullptr);

            bfs.put(output);
            size_t cur_index = 1;
            while (cur_index < size) {
                dynamic_heap_node<X> *parent = bfs.get();
                dynamic_heap_node<X> *child_left = this->create_node(arr[cur_index], parent);
                parent->left = child_left;
                bfs.put(child_left);
                ++cur_index;

                if (cur_index < size) {
                    dynamic_heap_node<X> *child_right = this->create_node(arr[cur_index], parent);
                    parent->right = child_right;
                    bfs.put(child_right);
                    ++cur_index;
                }
            }
            return output;
        }

        return nullptr;
    }
}

#endif //ALGORITHMS_DYNAMIC_HEAP_H