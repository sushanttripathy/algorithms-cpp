//
// Created by sushant on 5/19/18.
//

#ifndef ALGORITHMS_RED_BLACK_BST_H
#define ALGORITHMS_RED_BLACK_BST_H

#include <stdlib.h>
#include "binary_search_tree.h"
//#include "quicksort.h"
#include "../algorithms/heapsort.h"


namespace KAGU {
    template<typename X>
    struct rb_bst_node : public bst_node<X> {
    public:
        bool is_black;
    };

    template<typename X>
    class red_black_binary_search_tree : public binary_search_tree<X> {
    public:
        red_black_binary_search_tree(X *arr, size_t size);

        red_black_binary_search_tree();

        ~red_black_binary_search_tree();

        bst_node <X> *insert(const X &a);

    protected:


        rb_bst_node<X> *get_parent(rb_bst_node<X> *node);

        rb_bst_node<X> *get_sibling(rb_bst_node<X> *node);

        rb_bst_node<X> *get_uncle(rb_bst_node<X> *node);

        rb_bst_node<X> *get_grand_parent(rb_bst_node<X> *node);

        virtual bool rotate_left(rb_bst_node<X> *node);

        virtual bool rotate_right(rb_bst_node<X> *node);


        bst_node <X> *create_node(const X &val, bst_node <X> *parent = NULL);

        //virtual void destroy_node_and_rooted_tree(bst_node <X> *node);

        virtual void destroy_node(bst_node <X> *node);


        bst_node<X> * make_balanced_tree(X *sorted_arr, size_t size);

        virtual void insert_repair(rb_bst_node<X> *node);

        void remove_node(bst_node <X> *node);


        void delete_repair(rb_bst_node<X> *node, rb_bst_node<X> *replacing_child);

        void delete_repair_helper1(rb_bst_node<X> *node);

        void delete_repair_helper2(rb_bst_node<X> *node);

        void delete_repair_helper3(rb_bst_node<X> *node);

        void delete_repair_helper4(rb_bst_node<X> *node);

        void delete_repair_helper5(rb_bst_node<X> *node);

        void delete_repair_helper6(rb_bst_node<X> *node);
    };


    template<typename X>
    red_black_binary_search_tree<X>::red_black_binary_search_tree():binary_search_tree<X>() {
        this->root = NULL;
    };

    template<typename X>
    red_black_binary_search_tree<X>::red_black_binary_search_tree(X *arr, size_t size):binary_search_tree<X>() {
//        for (size_t i = 0; i < size; ++i) {
//            this->insert(arr[i]);
//        }

//        quicksort(arr, size, true, false);
        heapsort(arr, size);
        this->make_balanced_tree(arr, size);
    };

    template<typename X>
    red_black_binary_search_tree<X>::~red_black_binary_search_tree() {
        if (this->get_root() != NULL) {
            this->destroy_node_and_rooted_tree(this->get_root());
            this->set_root(NULL);
        }
    }

    template<typename X>
    bst_node<X> *red_black_binary_search_tree<X>::make_balanced_tree(X *sorted_arr, size_t size) {
        if (size > 2) {
            size_t middle = size / 2 + 1;
            bst_node<X> *output = this->insert(sorted_arr[middle]);

            this->make_balanced_tree(sorted_arr, middle);


            this->make_balanced_tree(sorted_arr + middle + 1, size - (middle + 1));

            return output;
        } else if (size > 0) {
            bst_node<X> *output = this->insert(sorted_arr[0]);
            if (size > 1) {
                this->insert(sorted_arr[1]);
            }
            return output;
        }
        return NULL;
    }


    template<typename X>
    bst_node <X> *red_black_binary_search_tree<X>::create_node(const X &val, bst_node <X> *parent) {
        try {
            rb_bst_node<X> *node = (rb_bst_node<X> *) calloc(sizeof(rb_bst_node<X>), 1);
            node->key = val;
            node->parent = parent;
            return node;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    template<typename X>
    rb_bst_node<X> *red_black_binary_search_tree<X>::get_parent(rb_bst_node<X> *node) {
        if (node != NULL) {
            return (rb_bst_node<X> *) node->parent;
        }
        return NULL;
    }

    template<typename X>
    rb_bst_node<X> *red_black_binary_search_tree<X>::get_sibling(rb_bst_node<X> *node) {
        if (node != NULL) {
            if (node->parent != NULL) {
                if (node->parent->left == node)
                    return (rb_bst_node<X> *) node->parent->right;
                else
                    return (rb_bst_node<X> *) node->parent->left;
            }
        }
        return NULL;
    }

    template<typename X>
    rb_bst_node<X> *red_black_binary_search_tree<X>::get_uncle(rb_bst_node<X> *node) {
        if (node != NULL) {
            if (node->parent != NULL) {
                if (node->parent->parent != NULL) {
                    if (node->parent->parent->left == node->parent)
                        return (rb_bst_node<X> *) node->parent->parent->right;
                    else
                        return (rb_bst_node<X> *) node->parent->parent->left;
                }
            }
        }
        return NULL;
    }

    template<typename X>
    rb_bst_node<X> *red_black_binary_search_tree<X>::get_grand_parent(rb_bst_node<X> *node) {
        if (node != NULL) {
            if (node->parent != NULL) {
                if (node->parent->parent != NULL) {
                    return (rb_bst_node<X> *) node->parent->parent;
                }
            }
        }
        return NULL;
    }

    template<typename X>
    bool red_black_binary_search_tree<X>::rotate_left(rb_bst_node<X> *node) {
        if (node != NULL) {
            rb_bst_node<X> *new_node = (rb_bst_node<X> *) node->right;
            if (new_node != NULL) {
                node->right = new_node->left;
                if (new_node->left) {
                    new_node->left->parent = node;
                }
                new_node->left = node;
                new_node->parent = node->parent;

                if (!node->parent) {
                    this->set_root(new_node);
                } else if (node->parent->right == node) {
                    node->parent->right = new_node;
                } else {
                    node->parent->left = new_node;
                }

                node->parent = new_node;
                return true;
            }
        }
        return false;
    }

    template<typename X>
    bool red_black_binary_search_tree<X>::rotate_right(rb_bst_node<X> *node) {
        if (node != NULL) {
            rb_bst_node<X> *new_node = (rb_bst_node<X> *) node->left;
            if (new_node != NULL) {
                node->left = new_node->right;
                if (new_node->right) {
                    new_node->right->parent = node;
                }
                new_node->right = node;
                new_node->parent = node->parent;

                if (!node->parent) {
                    this->set_root(new_node);
                } else if (node->parent->right == node) {
                    node->parent->right = new_node;
                } else {
                    node->parent->left = new_node;
                }

                node->parent = new_node;
                return true;
            }
        }
        return false;
    }

    template<typename X>
    void red_black_binary_search_tree<X>::insert_repair(rb_bst_node<X> *node) {

        rb_bst_node<X> *uncle = this->get_uncle(node);
        if (node->parent == NULL) {
            node->is_black = true;
        } else if (this->get_parent(node)->is_black) {
            // do nothing
            return;
        } else if (uncle != NULL && !uncle->is_black) {
            this->get_parent(node)->is_black = true;
            uncle->is_black = true;
            rb_bst_node<X> *gp = this->get_grand_parent(node);
            gp->is_black = false;
            this->insert_repair(gp);
        } else {
            rb_bst_node<X> *gp = this->get_grand_parent(node);
            rb_bst_node<X> *p = this->get_parent(node);

            if (gp != NULL) {
                if (gp->left != NULL && node == gp->left->right) {
                    this->rotate_left(p);
                    node = (rb_bst_node<X> *) node->left;
                } else if (gp->right != NULL && node == gp->right->left) {
                    this->rotate_right(p);
                    node = (rb_bst_node<X> *) node->right;
                }
            }

            p = this->get_parent(node);
            gp = this->get_grand_parent(node);
            if (gp != NULL) {
                if (p != NULL && node == p->left) {
                    this->rotate_right(gp);
                } else {
                    this->rotate_left(gp);
                }
                p->is_black = true;
                gp->is_black = false;
            }
        }
        return;
    }

    template<typename X>
    bst_node <X> *red_black_binary_search_tree<X>::insert(const X &a) {
        rb_bst_node<X> *assigned;
        assigned = (rb_bst_node<X> *)binary_search_tree<X>::insert(a);
        //Now to fix colors
        this->insert_repair(assigned);
        return assigned;
    }

//    template<typename X>
//    void red_black_binary_search_tree<X>::destroy_node_and_rooted_tree(bst_node <X> *node) {
//        if (node->left != NULL) {
//            destroy_node_and_rooted_tree(node->left);
//        }
//        if (node->right != NULL) {
//            destroy_node_and_rooted_tree(node->right);
//        }
//
//    }


    template<typename X>
    void red_black_binary_search_tree<X>::remove_node(bst_node <X> *node) {
        rb_bst_node<X> *replacement_node = NULL;

        if (node->left && node->right) {

            bst_node<X> *inorder_successor = this->find_inorder_successor(node);

            //node->key = inorder_successor->key;
            this->copy_node_attributes(inorder_successor, node);
            this->remove_node(inorder_successor);
        } else if (node->left) {
            replacement_node = (rb_bst_node<X> *) node->left;

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

            this->delete_repair((rb_bst_node<X> *) node, replacement_node);

            this->destroy_node_and_rooted_tree(node);


        } else if (node->right) {
            replacement_node = (rb_bst_node<X> *) node->right;

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

            this->delete_repair((rb_bst_node<X> *) node, replacement_node);

            this->destroy_node_and_rooted_tree(node);

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

            this->delete_repair((rb_bst_node<X> *) node, replacement_node);

            this->destroy_node_and_rooted_tree(node);

        }
    }


    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair(rb_bst_node<X> *node, rb_bst_node<X> *replacing_child) {
        bool is_node_black = (node != NULL) ? node->is_black : true;
        bool is_replacement_black = (replacing_child != NULL) ? replacing_child->is_black : true;

        if (is_node_black) {
            if (!is_replacement_black && replacing_child) {
                replacing_child->is_black = true;
            } else {
                this->delete_repair_helper1(replacing_child);
            }
        }
    }

    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair_helper1(rb_bst_node<X> *node) {
        if (node != NULL && node->parent != NULL) {
            this->delete_repair_helper2(node);
        }
    }

    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair_helper2(rb_bst_node<X> *node) {
        rb_bst_node<X> *sibling = this->get_sibling(node);
        if (sibling != NULL && !sibling->is_black) {
            ((rb_bst_node<X> *) node->parent)->is_black = false;
            sibling->is_black = true;
            if (node == node->parent->left) {
                this->rotate_left(((rb_bst_node<X> *) node->parent));
            } else {
                this->rotate_right(((rb_bst_node<X> *) node->parent));
            }
        }
        this->delete_repair_helper3(node);
    }

    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair_helper3(rb_bst_node<X> *node) {
        rb_bst_node<X> *sibling = this->get_sibling(node);
        bool is_sibling_black = (sibling != NULL) ? sibling->is_black : true;
        if (sibling != NULL) {
            bool is_sibling_left_child_black = sibling->left ? ((rb_bst_node<X> *) sibling->left)->is_black : true;
            bool is_sibling_right_child_black = sibling->right ? ((rb_bst_node<X> *) sibling->right)->is_black : true;

            if (((rb_bst_node<X> *) node->parent)->is_black && is_sibling_black && is_sibling_left_child_black &&
                is_sibling_right_child_black) {
                sibling->is_black = false;
                this->delete_repair_helper1((rb_bst_node<X> *) node->parent);
            } else {
                this->delete_repair_helper4(node);
            }
        }

    }

    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair_helper4(rb_bst_node<X> *node) {
        rb_bst_node<X> *sibling = this->get_sibling(node);
        bool is_sibling_black = (sibling != NULL) ? sibling->is_black : true;
        if (sibling != NULL) {
            bool is_sibling_left_child_black = sibling->left ? ((rb_bst_node<X> *) sibling->left)->is_black : true;
            bool is_sibling_right_child_black = sibling->right ? ((rb_bst_node<X> *) sibling->right)->is_black : true;
            if (!((rb_bst_node<X> *) node->parent)->is_black && is_sibling_black && is_sibling_left_child_black &&
                is_sibling_right_child_black) {
                sibling->is_black = false;
                ((rb_bst_node<X> *) node->parent)->is_black = true;
            } else {
                this->delete_repair_helper5(node);
            }
        }
    }

    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair_helper5(rb_bst_node<X> *node) {
        rb_bst_node<X> *sibling = this->get_sibling(node);
        bool is_sibling_black = (sibling != NULL) ? sibling->is_black : true;
        if (sibling != NULL && is_sibling_black) {
            bool is_sibling_left_child_black = sibling->left ? ((rb_bst_node<X> *) sibling->left)->is_black : true;
            bool is_sibling_right_child_black = sibling->right ? ((rb_bst_node<X> *) sibling->right)->is_black : true;
            if (node == node->parent->left && is_sibling_right_child_black && !is_sibling_left_child_black) {
                sibling->is_black = false;
                ((rb_bst_node<X> *) sibling->left)->is_black = true;
                this->rotate_right(sibling);
            } else if (node == node->parent->right && is_sibling_left_child_black && !is_sibling_right_child_black) {
                sibling->is_black = false;
                ((rb_bst_node<X> *) sibling->right)->is_black = true;
                this->rotate_left(sibling);
            }
        }
        this->delete_repair_helper6(node);
    }

    template<typename X>
    void red_black_binary_search_tree<X>::delete_repair_helper6(rb_bst_node<X> *node) {
        rb_bst_node<X> *sibling = this->get_sibling(node);
        if (sibling != NULL) {
            sibling->is_black = ((rb_bst_node<X> *) node->parent)->is_black;
            ((rb_bst_node<X> *) node->parent)->is_black = true;

            if (node == node->parent->left) {
                if (sibling->right) {
                    ((rb_bst_node<X> *) sibling->right)->is_black = true;
                }
                this->rotate_left((rb_bst_node<X> *) node->parent);
            } else {
                if (sibling->left) {
                    ((rb_bst_node<X> *) sibling->left)->is_black = true;
                    this->rotate_right((rb_bst_node<X> *) node->parent);
                }
            }
        }
    }

    template<typename X>
    void red_black_binary_search_tree<X>::destroy_node(bst_node <X> *node) {
        if(node){
            free((rb_bst_node<X> *) node);
        }
    }
}

#endif //ALGORITHMS_RED_BLACK_BST_H
