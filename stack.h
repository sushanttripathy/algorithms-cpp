//
// Created by Tripathy, Sushant on 3/26/18.
//

#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <stdlib.h>
#include <exception>

namespace KAGU {
#define DEFAULT_STACK_SIZE 1000
#define IGNORE_PUSH_INTO_FULL_STACK false

    template<typename X>
    class stack {
    public:
        stack(int nsize = DEFAULT_STACK_SIZE);

        ~stack();

        void push(X x);

        X pop();

        bool empty();

        bool full();

    private:
        X *arr;
        int capacity;
        int contents;
    };

    template<typename X>
    stack<X>::stack(int nsize) {
        this->capacity = nsize;
        this->contents = 0;
        this->arr = (X *) calloc(nsize, sizeof(X));
    }

    template<typename X>
    stack<X>::~stack() {
        if (this->arr != NULL) {
            free(this->arr);
            this->arr = NULL;
        }
        this->capacity = 0;
        this->contents = 0;
    }

#ifndef PUSHING_FULL_STACK
#define PUSHING_FULL_STACK

    struct pushing_full_stack : public std::exception {
        const char *what() const throw() {
            return "Unable to push a key into a full stack.";
        }
    };

#endif

    template<typename X>
    void stack<X>::push(X x) {
        if (this->contents < this->capacity) {
            this->arr[this->contents] = x;
            ++this->contents;
        }
        else if(IGNORE_PUSH_INTO_FULL_STACK){
            throw pushing_full_stack();
        }
    }

#ifndef POPPING_EMPTY_STACK
#define POPPING_EMPTY_STACK

    struct popping_empty_stack : public std::exception {
        const char *what() const throw() {
            return "Unable to pop a key from an empty stack.";
        }
    };

#endif

    template<typename X>
    X stack<X>::pop() {
        if (this->contents > 0) {
            X temp = this->arr[this->contents-1];
            --this->contents;
            return temp;
        } else {
            throw popping_empty_stack();
        }
    }

    template<typename X>
    bool stack<X>::empty() {
        if (this->contents <= 0) {
            return true;
        } else {
            return false;
        }
    }

    template<typename X>
    bool stack<X>::full() {
        if (this->contents < this->capacity) {
            return false;
        } else {
            return true;
        }
    }
}
#endif //ALGORITHMS_STACK_H
