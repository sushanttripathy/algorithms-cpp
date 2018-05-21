//
// Created by sushant on 5/19/18.
//

#ifndef ALGORITHMS_BINARY_SEARCH_TREE_H
#define ALGORITHMS_BINARY_SEARCH_TREE_H


#include <stdlib.h>
#include <exception>
#include <iostream>
#include "quicksort.h"
#include "binary_search_tree_old.h"

namespace KAGU {


    template<typename X>
    struct bst_node {
    public:
        X key;
        bst_node<X> *left, *right, *parent;
    };

    template<typename X>
    class binary_search_tree {
    public:
        static const int INORDER = 0;
        static const int PREORDER = 1;
        static const int POSTORDER = 2;

        binary_search_tree(X *arr, size_t size);

        binary_search_tree();

        ~binary_search_tree();

        virtual bst_node<X> *insert(X a);

        virtual bst_node<X> *find(X a);

        virtual bool remove(X a);

        void print_traversal_results(int traversal_type = binary_search_tree<X>::INORDER, bst_node<X> *node = NULL);

    protected:

        bst_node<X> *root;

        virtual bst_node<X> *make_node(X val, bst_node<X> *parent = NULL);

        virtual void free_nodes(bst_node<X> *node);

        virtual bst_node<X> *get_root();

        virtual void set_root(bst_node<X> *node);


        bst_node<X> *find_inorder_successor(bst_node<X> *node);

        bst_node<X> *find_subtree_min(bst_node<X> *node);

        bst_node<X> *make_balanced_tree(X *sorted_arr, size_t size);

        virtual void remove_node(bst_node<X> *node);

    };

    template<typename X>
    bst_node<X> *binary_search_tree<X>::make_balanced_tree(X *sorted_arr, size_t size) {
        if (size > 2) {
            size_t middle = size / 2 + 1;
            bst_node<X> *output = this->make_node(sorted_arr[middle]);

            output->left = this->make_balanced_tree(sorted_arr, middle);
            if (output->left)
                output->left->parent = output;

            output->right = this->make_balanced_tree(sorted_arr + middle + 1, size - (middle + 1));
            if (output->right)
                output->right->parent = output;
            return output;
        } else if (size > 0) {
            bst_node<X> *output = this->make_node(sorted_arr[0]);
            if (size > 1) {
                output->right = this->make_node(sorted_arr[1], output);
            }

            return output;
        }
        return NULL;
    }

    template<typename X>
    binary_search_tree<X>::binary_search_tree(X *arr, size_t size) {
        this->set_root(NULL);

        quicksort(arr, size);

        this->set_root(this->make_balanced_tree(arr, size));
    }

    template<typename X>
    binary_search_tree<X>::binary_search_tree() {
        this->set_root(NULL);
    }

    template<typename X>
    bst_node<X> *binary_search_tree<X>::get_root() {
        return this->root;
    }

    template<typename X>
    void binary_search_tree<X>::set_root(bst_node<X> *node) {
        this->root = node;
    }


    template<typename X>
    bst_node<X> *binary_search_tree<X>::insert(X a) {
        bst_node<X> *cur = this->get_root(), *assigned = NULL;
        if (cur == NULL) {
            this->set_root(this->make_node(a));
            assigned = this->get_root();
        } else {

            while (true) {
                if (cur->key > a) {
                    if (cur->left == NULL) {
                        cur->left = this->make_node(a, cur);
                        assigned = cur->left;
                        break;
                    } else {
                        cur = cur->left;
                    }
                } else {
                    if (cur->right == NULL) {
                        cur->right = this->make_node(a, cur);
                        assigned = cur->right;
                        break;
                    } else {
                        cur = cur->right;
                    }
                }
            }
        }

        return assigned;
    }


    template<typename X>
    bst_node<X> *binary_search_tree<X>::make_node(X val, bst_node<X> *parent) {
        try {
            bst_node<X> *node = (bst_node<X> *) calloc(sizeof(bst_node<X>), 1);
            node->key = val;
            node->parent = parent;
            return node;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

    }

    template<typename X>
    bst_node<X> * binary_search_tree<X>::find(X a) {

        bst_node<X> *cur_node = this->get_root();
        while (cur_node != NULL) {
            if (cur_node->key == a) {
                return cur_node;
            } else if (cur_node->key > a) {
                cur_node = cur_node->left;
            } else {
                cur_node = cur_node->right;
            }
        }
        return NULL;
    }


    template<typename X>
    bst_node<X> *
    binary_search_tree<X>::find_subtree_min(bst_node<X> *node) {
        if (node != NULL) {
            bst_node<X> *min_node = node;


            if (node->right != NULL) {
                bst_node<X> *right_min = this->find_subtree_min(node->right);
                if (right_min->key < min_node->key) {
                    min_node = right_min;
                }
            }

            if (node->left != NULL) {
                bst_node<X> *left_min = this->find_subtree_min(node->left);
                if (left_min->key < min_node->key) {
                    min_node = left_min;
                }
            }
            return min_node;
        }
        return NULL;
    }

    template<typename X>
    bst_node<X> *
    binary_search_tree<X>::find_inorder_successor(bst_node<X> *node) {

        if (node->right != NULL) {
            bst_node<X> *successor = this->find_subtree_min(node->right);
            return successor;
        }
        return NULL;
    }


    template<typename X>
    void binary_search_tree<X>::remove_node(bst_node<X> *node) {
        if (node->left && node->right) {

            bst_node<X> *inorder_successor = this->find_inorder_successor(node);

            node->key = inorder_successor->key;
            this->remove_node(inorder_successor);
        } else if (node->left) {
            if (node->parent != NULL) {
                if (node->parent->right == node) {
                    node->parent->right = node->left;
                } else {
                    node->parent->left = node->left;
                }
            } else {
                this->set_root(node->left);
            }

            node->left->parent = node->parent;
            node->left = NULL;
            this->free_nodes(node);
        } else if (node->right) {
            if (node->parent != NULL) {
                if (node->parent->right == node) {
                    node->parent->right = node->right;
                } else {
                    node->parent->left = node->right;
                }
            } else {
                this->set_root(node->right);
            }

            node->right->parent = node->parent;
            node->right = NULL;
            this->free_nodes(node);
        } else {
            if (node->parent != NULL) {
                if (node->parent->right == node) {
                    node->parent->right = NULL;
                } else {
                    node->parent->left = NULL;
                }
            } else {
                this->set_root(NULL);
            }

            this->free_nodes(node);
        }
    }

    template<typename X>
    bool binary_search_tree<X>::remove(X a) {

        bst_node<X> *cur_node = this->get_root();

        while (cur_node != NULL) {
            if (cur_node->key == a) {
                this->remove_node(cur_node);
                return true;
            } else if (cur_node->key > a) {
                cur_node = cur_node->left;
            } else {
                cur_node = cur_node->right;
            }
        }

        return false;
    }

    template<typename X>
    void binary_search_tree<X>::free_nodes(bst_node<X> *node) {
        if (node->left != NULL) {
            free_nodes(node->left);
        }
        if (node->right != NULL) {
            free_nodes(node->right);
        }
        free(node);
    }


    template<typename X>
    void binary_search_tree<X>::print_traversal_results(int traversal_type, bst_node<X> *node) {
        if (node == NULL) {
            node = this->get_root();
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
                    std::cout << node->key;
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
                    std::cout << node->key;
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

                    std::cout << node->key;

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
    binary_search_tree<X>::~binary_search_tree() {

        if (this->get_root() != NULL) {
            this->free_nodes(this->get_root());
            this->set_root(NULL);
        }

    }
}

#endif //ALGORITHMS_BINARY_SEARCH_TREE_H
