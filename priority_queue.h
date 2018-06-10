//
// Created by Tripathy, Sushant on 3/27/18.
//

#ifndef ALGORITHMS_PRIORITY_QUEUE_H
#define ALGORITHMS_PRIORITY_QUEUE_H

#include <stdlib.h>
#include <exception>


namespace KAGU {
#define DEFAULT_PRIORITY_QUEUE_SIZE 1000
#define IGNORE_ENQUEUEING_INTO_FULL_PRIORITY_QUEUE false

    template<typename X, typename Y>
    class priority_queue {
    public:
        priority_queue(int nsize = DEFAULT_PRIORITY_QUEUE_SIZE, bool is_max_priority_queue = false);

        ~priority_queue();

        void put(const X &x, const Y &priority);

        X get(Y &priority);

        X get();

        bool empty();

        bool full();

    private:
        X *arr;
        Y *arr2;

        void percolate_down(int i);

        void percolate_up(int i);

        bool is_max_priority_queue;
        int capacity;
        int contents;
    };

    template<typename X, typename Y>
    priority_queue<X, Y>::priority_queue(int nsize, bool is_max_priority_queue) {
        this->capacity = nsize;
        this->contents = 0;
        this->arr = (X *) calloc(nsize, sizeof(X));
        this->arr2 = (Y *) calloc(nsize, sizeof(Y));
        this->is_max_priority_queue = is_max_priority_queue;
    }

    template<typename X, typename Y>
    priority_queue<X, Y>::~priority_queue() {
        if (this->arr != NULL) {
            free(this->arr);
            this->arr = NULL;
        }
        if (this->arr2 != NULL) {
            free(this->arr2);
            this->arr2 = NULL;
        }
        this->capacity = 0;
        this->contents = 0;
    }

#ifndef ENQUEUEING_FULL_PRIORITY_QUEUE
#define ENQUEUEING_FULL_PRIORITY_QUEUE

    struct enqueueing_full_priority_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to put a key into a full priority queue.";
        }
    };

#endif

    template<typename X, typename Y>
    void priority_queue<X, Y>::put(const X &x, const Y &priority) {
        if (this->contents < this->capacity) {
            this->arr[this->contents] = x;
            this->arr2[this->contents] = priority;
            this->contents++;
            this->percolate_up(this->contents - 1);
        }
        else if(!IGNORE_ENQUEUEING_INTO_FULL_PRIORITY_QUEUE){
            throw enqueueing_full_priority_queue();
        }
    }

#ifndef DEQUEUEING_EMPTY_PRIORITY_QUEUE
#define DEQUEUEING_EMPTY_PRIORITY_QUEUE

    struct dequeueing_empty_priority_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to get a key from an empty priority queue.";
        }
    };

#endif

    template<typename X, typename Y>
    X priority_queue<X, Y>::get() {
        if (this->contents > 0) {
            X temp = this->arr[0];
            Y temp2 = this->arr2[0];

            this->arr[0] = this->arr[this->contents -1];
            this->arr2[0] = this->arr2[this->contents -1];

            this->contents--;
            this->percolate_down(0);
            return temp;
        } else {
            throw dequeueing_empty_priority_queue();
        }
    }

    template<typename X, typename Y>
    X priority_queue<X, Y>::get(Y &priority) {
        if (this->contents > 0) {
            X temp = this->arr[0];
            Y temp2 = this->arr2[0];

            this->arr[0] = this->arr[this->contents];
            this->arr2[0] = this->arr2[this->contents];

            this->contents--;
            this->percolate_down(0);

            priority = temp2;
            return temp;
        } else {
            throw dequeueing_empty_priority_queue();
        }
    }

    template<typename X, typename Y>
    void priority_queue<X, Y>::percolate_up(int i) {
        if (i == 0) {
            return;
        }
        bool done = false;
        int cur = i;
        int parent;

        while (!done) {
            parent = cur / 2;
            if (cur % 2 == 0 && parent > 0) {
                parent--;
            }

            if (this->is_max_priority_queue) {
                if (cur == parent) {
                    done = true;
                    break;
                }
                if (this->arr2[cur] <= this->arr2[parent]) {
                    done = true;
                } else {
                    X temp = this->arr[cur];
                    Y temp2 = this->arr2[cur];

                    this->arr[cur] = this->arr[parent];
                    this->arr2[cur] = this->arr2[parent];

                    this->arr[parent] = temp;
                    this->arr2[parent] = temp2;

                    cur = parent;
                }
            } else {
                if (cur == parent) {
                    done = true;
                    break;
                }
                if (this->arr2[cur] >= this->arr2[parent]) {
                    done = true;
                } else {
                    X temp = this->arr[cur];
                    Y temp2 = this->arr2[cur];

                    this->arr[cur] = this->arr[parent];
                    this->arr2[cur] = this->arr2[parent];

                    this->arr[parent] = temp;
                    this->arr2[parent] = temp2;

                    cur = parent;
                }

            }
        }
    }

    template<typename X, typename Y>
    void priority_queue<X, Y>::percolate_down(int i){
        if (i == this->contents - 1) {
            return;
        }
        int left;
        int right;
        bool done;

        if(this->is_max_priority_queue){
            int largest = i;
            done = false;
            while (!done) {
                left = 2 * i + 1;
                right = 2 * i + 2;
                if (left < this->contents && (this->arr2[left] > this->arr2[largest])) {
                    largest = left;
                }

                if (right < this->contents && (this->arr2[right] > this->arr2[largest])) {
                    largest = right;
                }

                if (largest != i) {
                    X temp = this->arr[i];
                    Y temp2 = this->arr2[i];

                    this->arr[i] = this->arr[largest];
                    this->arr2[i] = this->arr2[largest];

                    this->arr[largest] = temp;
                    this->arr2[largest] = temp2;
                } else {
                    done = true;
                }
                i = largest;
            }
        }
        else{
            int smallest = i;
            done = false;
            while (!done) {
                left = 2 * i + 1;
                right = 2 * i + 2;
                if (left < this->contents && (this->arr2[left] < this->arr2[smallest])) {
                    smallest = left;
                }

                if (right < this->contents && (this->arr2[right] < this->arr2[smallest])) {
                    smallest = right;
                }

                if (smallest != i) {
                    X temp = this->arr[i];
                    Y temp2 = this->arr2[i];

                    this->arr[i] = this->arr[smallest];
                    this->arr2[i] = this->arr2[smallest];

                    this->arr[smallest] = temp;
                    this->arr2[smallest] = temp2;
                } else {
                    done = true;
                }
                i = smallest;
            }
        }
    }

    template<typename X, typename Y>
    bool priority_queue<X, Y>::empty() {
        if (this->contents <= 0) {
            return true;
        } else {
            return false;
        }
    }

    template<typename X, typename Y>
    bool priority_queue<X, Y>::full(){
        if (this->contents < this->capacity) {
            return false;
        } else {
            return true;
        }
    }
}

#endif //ALGORITHMS_PRIORITY_QUEUE_H
