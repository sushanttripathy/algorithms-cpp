//
// Created by Tripathy, Sushant on 3/26/18.
//

#ifndef ALGORITHMS_CIRCULAR_QUEUE_H
#define ALGORITHMS_CIRCULAR_QUEUE_H

#include <stdlib.h>
#include <exception>

namespace KAGU {
#define DEFAULT_CQ_SIZE 1000
#define IGNORE_ENQUEUE_FULL_CIRCULAR_QUEUE false


    template<typename X>
    class circular_queue {
    public:
        circular_queue(int size = DEFAULT_CQ_SIZE);

        ~circular_queue();

        void put(const X &x);

        X get();

        X peek();

        bool empty();

        bool full();

        X& operator[](int index);

    private:
        X *arr;
        int capacity;
        int contents;
        int start;
        int end;
    };


    template<typename X>
    circular_queue<X>::circular_queue(int nsize) {
        this->capacity = nsize;
        this->contents = 0;
        this->start = 0;
        this->end = 0;
        this->arr = (X *) calloc(this->capacity, sizeof(X)); //Put a try catch here
    }

    template<typename X>
    circular_queue<X>::~circular_queue() {
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
            return "Trying to put a key into a full queue.";
        }
    };

#endif

    template<typename X>
    void circular_queue<X>::put(const X &x) {
        if (this->contents < this->capacity) {
            this->arr[this->end] = x;
            this->end = (this->end + 1) % this->capacity;
            ++this->contents;
        } else if (!IGNORE_ENQUEUE_FULL_CIRCULAR_QUEUE) {
            throw enqueueing_full_queue();
        }
    }

#ifndef DEQUEUEING_EMPTY_QUEUE
#define DEQUEUEING_EMPTY_QUEUE

    struct dequeueing_empty_queue : public std::exception {
        const char *what() const throw() {
            return "Trying to get a key from an empty queue.";
        }
    };

#endif

    template<typename X>
    X circular_queue<X>::get() {
        if (this->contents > 0) {
            X temp = this->arr[this->start];
            this->start = (this->start + 1) % this->capacity;
            --this->contents;
            return temp;
        } else {
            throw dequeueing_empty_queue();
        }
    }


    template<typename X>
    bool circular_queue<X>::empty() {
        if (this->contents <= 0) {
            return true;
        } else {
            return false;
        }
    }

    template<typename X>
    bool circular_queue<X>::full() {
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
    X circular_queue<X>::peek() {
        if (this->contents > 0) {
            return this->arr[this->start];
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
    X& circular_queue<X>::operator[](int index) {
        if (this->contents > 0) {
            if (index >= 0 && index < this->contents) {
                return this->arr[(this->start + index)%this->capacity];
            } else if (index < 0 && this->contents + index >= 0) {
                return this->arr[(this->start + this->contents + index)%this->capacity];
            } else {
                throw accessing_out_of_bounds_queue_index();
            }
        } else {
            throw peeking_empty_queue();
        }
    }
}

#endif //ALGORITHMS_CIRCULAR_QUEUE_H
