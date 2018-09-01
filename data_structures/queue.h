//
// Created by Tripathy, Sushant on 3/26/18.
//

#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include <stdlib.h>
#include <exception>
#include "circular_queue.h"

namespace KAGU {

#define DEFAULT_Q_SIZE 1000
#define IGNORE_ENQUEUE_FULL_QUEUE false

    template<typename X>
    class queue {
    public:
        queue(int size = DEFAULT_Q_SIZE);

        ~queue();

        void put(const X &x);

        X get();

        X peek();

        bool empty();

        bool full();

        X operator[](int index);

    private:
        X *arr;
        int capacity;
        int contents;
    };


    template<typename X>
    queue<X>::queue(int nsize) {
        this->capacity = nsize;
        this->contents = 0;
        this->arr = (X *) calloc(this->capacity, sizeof(X)); //Put a try catch here
    }

    template<typename X>
    queue<X>::~queue() {
        if (this->arr != NULL) {
            free(this->arr);
            this->arr = NULL;
        }
        this->capacity = 0;
        this->contents = 0;
    }

#ifndef ENQUEUEING_FULL_QUEUE
#define ENQUEUEING_FULL_QUEUE
    struct enqueueing_full_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to enqueue a value into a full queue.";
        }
    };
#endif

    template<typename X>
    void queue<X>::put(const X &x) {
        if (this->contents < this->capacity) {
            this->arr[this->contents] = x;
            ++this->contents;
        } else if (!IGNORE_ENQUEUE_FULL_QUEUE) {
            throw enqueueing_full_queue();
        }
    }

#ifndef DEQUEUEING_EMPTY_QUEUE
#define DEQUEUEING_EMPTY_QUEUE
    struct dequeueing_empty_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to dequeue a value from an empty queue.";
        }
    };
#endif

    template<typename X>
    X queue<X>::get() {
        if (this->contents > 0) {
            X temp = this->arr[0];
            int i = 1;
            while (i < this->contents) {
                this->arr[i - 1] = this->arr[i];
                ++i;
            }
            --this->contents;
            return temp;
        } else {
            throw dequeueing_empty_queue();
//            return this->arr[0];
        }
    }


    template<typename X>
    bool queue<X>::empty() {
        if (this->contents <= 0) {
            return true;
        } else {
            return false;
        }
    }

    template<typename X>
    bool queue<X>::full() {
        if (this->contents < this->capacity) {
            return false;
        } else {
            return true;
        }
    }

#ifndef PEEKING_EMPTY_QUEUE
#define PEEKING_EMPTY_QUEUE

    struct peeking_empty_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to peek into an empty queue.";
        }
    };

#endif

    template<typename X>
    X queue<X>::peek() {
        if (this->contents > 0) {
            return this->arr[0];
        } else {
            throw peeking_empty_queue();
        }
    }

#ifndef ACCESSING_OUT_OF_BOUNDS_QUEUE_INDEX
#define ACCESSING_OUT_OF_BOUNDS_QUEUE_INDEX

    struct accessing_out_of_bounds_queue_index : public std::exception {
        const char *what() const throw() {
            return "Error trying to access out of bounds queue index.";
        }
    };

#endif

    template<typename X>
    X queue<X>::operator[](int index) {

        if (this->contents) {
            if (index >= 0 && index < this->contents) {
                return this->arr[index];
            } else if (index < 0 && this->contents + index >= 0) {
                return this->arr[this->contents + index];
            } else {
                throw accessing_out_of_bounds_queue_index();
            }
        } else {
            throw peeking_empty_queue();
        }
    }

}
#endif //ALGORITHMS_QUEUE_H
