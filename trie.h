//
// Created by sushant on 7/10/18.
//

#ifndef ALGORITHMS_RADIX_TREE_H
#define ALGORITHMS_RADIX_TREE_H

#include <stdlib.h>
#include <set>
#include <map>

namespace KAGU {
    template<typename X, typename Y>
    struct trie_node {
    public:
        Y *value;
        std::map<X, trie_node<X, Y> *> *children;
        trie_node<X, Y> *parent;
    };


    template<typename X, typename Y>
    class trie {
    public:
        trie();

        trie(X *(*tokenizer)(X *in, size_t in_size, size_t &out_elements));

        ~trie();

        virtual void insert_sequence(X *seq, size_t size, Y &val);

        virtual void update_sequence(X *seq, size_t size, Y &val);

        virtual void upsert_sequence(X *seq, size_t size, Y &val);

        virtual void increment_sequence_val(X *seq, size_t size, Y &diff, bool insert_if_sequence_not_found = true);

        virtual void delete_sequence(X *seq, size_t size, bool silent_delete = false);

        virtual bool find_sequence(X *seq, size_t size, Y &val);

    protected:
        X *(*tokenizer)(X *in, size_t in_size, size_t &out_elements);

        trie_node<X, Y> *root;

        //TODO: Consider removing this property to facilitate atomicity?
        size_t contents;

        virtual void destroy_all_nodes();

        virtual trie_node<X, Y> *create_node(trie_node<X, Y> *parent = nullptr);

        virtual void destroy_node(trie_node<X, Y> *node);

    };

    template<typename X, typename Y>
    void trie<X, Y>::destroy_all_nodes() {
        if (this->root) {
            this->destroy_node(this->root);
            this->root = nullptr;
        }
    }

    template<typename X, typename Y>
    trie_node<X, Y> *trie<X, Y>::create_node(trie_node<X, Y> *parent) {
//        trie_node<X, Y> *new_node = (trie_node<X, Y> *) calloc(1, sizeof(trie_node<X, Y>));
        trie_node<X, Y> *new_node =  new trie_node<X, Y>();
        new_node->children = new std::map<X, trie_node<X, Y> *>();
        new_node->parent = parent;
        return new_node;
        //TODO : strucutre dexception handling for memory allocation
    }

    template<typename X, typename Y>
    void trie<X, Y>::destroy_node(trie_node<X, Y> *node) {
        if (node) {
            for (typename std::map<X, trie_node<X, Y> *>::iterator f = node->children->begin(); f != node->children->end(); ++f) {
                this->destroy_node(f->second);
            }
            if (node->value != nullptr) {
                free(node->value);
                node->value = nullptr;
            }
            delete node->children;
            delete node;
        }
    }

    template<typename X, typename Y>
    trie<X, Y>::trie() {
        this->root = this->create_node();
        this->contents = 0;
        this->tokenizer = nullptr;
    }

    template<typename X, typename Y>
    trie<X, Y>::trie(X *(*tokenizer)(X *, size_t, size_t &)) {
        this->root = this->create_node();
        this->contents = 0;
        this->tokenizer = tokenizer;
    }

    template<typename X, typename Y>
    trie<X, Y>::~trie() {
        if (this->root) {
            this->destroy_all_nodes();
        }
    }

#ifndef SEQUENCE_ALREADY_IN_TRIE_INSERT_FAILURE
#define SEQUENCE_ALREADY_IN_TRIE_INSERT_FAILURE

    struct sequence_already_in_trie_insert_failure : public std::exception {
        const char *what() const throw() {
            return "Error trying to insert sequence into trie, as sequence already exists in trie.";
        }
    };

#endif


    template<typename X, typename Y>
    void trie<X, Y>::insert_sequence(X *seq, size_t size, Y &val) {
        if (seq == nullptr || size == 0) {
            return;
        }

        trie_node<X, Y> *cur = this->root;
        size_t insert_start = 0;
        while (cur != nullptr && insert_start < size) {
            typename std::map<X, trie_node<X, Y> *>::iterator f = cur->children->find(seq[insert_start]);
            if (f == cur->children->end()) {
                break;
            } else {
                cur = f->second;
                ++insert_start;
            }
        }

        if (insert_start < size) {
            for (; insert_start < size; ++insert_start) {
                trie_node<X, Y> *new_node = this->create_node(cur);
//                cur->children[seq[insert_start]] = new_node;
                cur->children->insert(std::pair<X, trie_node<X, Y> *>(seq[insert_start], new_node));
                cur = new_node;
            }
        }

        if (cur->value != nullptr) {
            throw sequence_already_in_trie_insert_failure();
        } else {
            cur->value = (Y *) calloc(1, sizeof(Y));
            *(cur->value) = val;
            ++this->contents;
        }
    }

#ifndef SEQUENCE_NOT_FOUND_UPDATE_FAILURE
#define SEQUENCE_NOT_FOUND_UPDATE_FAILURE

    struct sequence_not_found_update_failure : public std::exception {
        const char *what() const throw() {
            return "Error trying to update associated sequence value in trie, as sequence does not exist in trie.";
        }
    };

#endif


    template<typename X, typename Y>
    void trie<X, Y>::update_sequence(X *seq, size_t size, Y &val) {
        if (seq == nullptr || size == 0) {
            return;
        }

        trie_node<X, Y> *cur = this->root;
        size_t insert_start = 0;
        while (cur != nullptr && insert_start < size) {
            typename std::map<X, trie_node<X, Y> *>::iterator f = cur->children->find(seq[insert_start]);
            if (f == cur->children->end()) {
                break;
            } else {
                cur = f->second;
                ++insert_start;
            }
        }

        if (insert_start < size) {
            throw sequence_not_found_update_failure();
        }

        if (cur->value == nullptr) {
            throw sequence_not_found_update_failure();
        } else {
            *(cur->value) = val;
        }
    }

    template<typename X, typename Y>
    void trie<X, Y>::upsert_sequence(X *seq, size_t size, Y &val) {
        if (seq == nullptr || size == 0) {
            return;
        }

        trie_node<X, Y> *cur = this->root;
        size_t insert_start = 0;
        while (cur != nullptr && insert_start < size) {
            typename std::map<X, trie_node<X, Y> *>::iterator f = cur->children->find(seq[insert_start]);
            if (f == cur->children->end()) {
                break;
            } else {
                cur = f->second;
                ++insert_start;
            }
        }

        if (insert_start < size) {
            for (; insert_start < size; ++insert_start) {
                trie_node<X, Y> *new_node = this->create_node(cur);
                cur->children->insert(std::pair<X, trie_node<X, Y> *>(seq[insert_start], new_node));
                cur = new_node;
            }
        }

        if (cur->value != nullptr) {
            *(cur->value) = val;
        } else {
            cur->value = (Y *) calloc(1, sizeof(Y));
            *(cur->value) = val;
            ++this->contents;
        }
    }

    template<typename X, typename Y>
    void trie<X, Y>::increment_sequence_val(X *seq, size_t size, Y &diff, bool insert_if_sequence_not_found) {
        if (seq == nullptr || size == 0) {
            return;
        }

        trie_node<X, Y> *cur = this->root;
        size_t insert_start = 0;
        while (cur != nullptr && insert_start < size) {
            typename std::map<X, trie_node<X, Y> *>::iterator f = cur->children->find(seq[insert_start]);
            if (f == cur->children->end()) {
                break;
            } else {
                cur = f->second;
                ++insert_start;
            }
        }

        if (insert_start < size) {
            for (; insert_start < size; ++insert_start) {
                trie_node<X, Y> *new_node = this->create_node(cur);
                cur->children->insert(std::pair<X, trie_node<X, Y> *>(seq[insert_start], new_node));
                cur = new_node;
            }
        }

        if (cur->value != nullptr) {
            *(cur->value) += diff;

        } else {
            if (insert_if_sequence_not_found) {
                cur->value = (Y *) calloc(1, sizeof(Y));
                *(cur->value) = diff;
            } else {
                throw sequence_not_found_update_failure();
            }
        }

    }

#ifndef SEQUENCE_NOT_FOUND_DELETE_FAILURE
#define SEQUENCE_NOT_FOUND_DELETE_FAILURE

    struct sequence_not_found_delete_failure : public std::exception {
        const char *what() const throw() {
            return "Error trying to delete sequence from trie, as sequence does not exist in trie.";
        }
    };

#endif

    template<typename X, typename Y>
    void trie<X, Y>::delete_sequence(X *seq, size_t size, bool silent_delete) {
        if (seq == nullptr || size == 0) {
            return;
        }

        trie_node<X, Y> *cur = this->root;
        size_t seq_match = 0;
        while (cur != nullptr && seq_match < size) {
            typename std::map<X, trie_node<X, Y> *>::iterator f = cur->children->find(seq[seq_match]);
            if (f == cur->children->end()) {
                break;
            } else {
                cur = f->second;
                ++seq_match;
            }
        }
        if (seq_match == size ) {
            //Sequence found, proceed to deletion
            if (cur->value != nullptr) {
                free(cur->value);
                cur->value = nullptr;

                while (cur  && cur->children->size() == 0 && cur->value == nullptr) {
                    trie_node<X, Y> *parent = cur->parent;
                    if(!parent){
                        // this is the root node
                        // we're not going to delete this
                        break;
                    }
                    this->destroy_node(cur);
                    if (parent) {
                        parent->children->erase(seq[--seq_match]);
                    }
                    cur = parent;
                }

            } else if (!silent_delete) {
                throw sequence_not_found_delete_failure();
            }
        } else if (!silent_delete) {
            throw sequence_not_found_delete_failure();
        }
    }

    template<typename X, typename Y>
    bool trie<X, Y>::find_sequence(X *seq, size_t size, Y &val) {
        if (seq == nullptr || size == 0) {
            return false;
        }

        trie_node<X, Y> *cur = this->root;
        size_t seq_match = 0;
        while (cur != nullptr && seq_match < size) {
            typename std::map<X, trie_node<X, Y> *>::iterator f = cur->children->find(seq[seq_match]);
            if (f == cur->children->end()) {
                break;
            } else {
                cur = f->second;
                ++seq_match;
            }
        }

        if (seq_match == size) {
            //Sequence found
            if (cur->value) {
                val = *(cur->value);
                return true;
            }
        }
        return false;
    }
}

#endif //ALGORITHMS_RADIX_TREE_H
