//
// Created by Tripathy, Sushant on 3/27/18.
//

#ifndef ALGORITHMS_HEAP_H
#define ALGORITHMS_HEAP_H

#include <stdlib.h>
#include <exception>

namespace KAGU {
#define DEFAULT_HEAP_SIZE 1000
#define IGNORE_PUSHING_INTO_FULL_HEAP false


    template<typename X>
    class heap {
    public:
        heap(int nsize = DEFAULT_HEAP_SIZE, bool is_max_heap = true);

        heap(X *arr, int arr_size, bool is_max_heap = true);

        ~heap();

        void heappush(X x);

        X heappop();

        bool empty();

        bool full();

    private:
        void heapify();

        void percolate_up(int i);

        void percolate_down(int i);

        bool is_max_heap;
        int capacity;
        int contents;
        X *arr;
    };

    template<typename X>
    heap<X>::heap(int nsize, bool is_max_heap) {
        this->capacity = nsize;
        this->contents = 0;
        this->arr = (X *) calloc(nsize, sizeof(X));
        this->is_max_heap = is_max_heap;
    }

    template<typename X>
    heap<X>::heap(X *arr, int arr_size, bool is_max_heap) {
        this->capacity = arr_size;
        this->contents = arr_size;
        this->arr = (X *) calloc(arr_size, sizeof(X));
        for (int i = 0; i < this->contents; ++i) {
            this->arr[i] = arr[i];
        }
        this->is_max_heap = is_max_heap;
        this->heapify();
    }

    template<typename X>
    heap<X>::~heap() {
        if (this->arr != NULL) {
            free(this->arr);
            this->arr = NULL;
        }
        this->capacity = 0;
        this->contents = 0;
    }

    template<typename X>
    void heap<X>::heapify() {
        if (this->capacity && this->contents) {
            for (int i = this->contents / 2 - 1; i >= 0; --i) {
                this->percolate_down(i);
            }
        }
    }

#ifndef PUSHING_FULL_HEAP
#define PUSHING_FULL_HEAP

    struct pushing_full_heap : public std::exception {
        const char *what() const throw() {
            return "Unable to push a key into a full heap.";
        }
    };

#endif

    template<typename X>
    void heap<X>::heappush(X x) {
        if (this->contents < this->capacity) {
            this->arr[this->contents] = x;
            ++this->contents;
            this->percolate_up(this->contents - 1);
        } else if(!IGNORE_PUSHING_INTO_FULL_HEAP){
            throw pushing_full_heap();
        }
    }


#ifndef POPPING_EMPTY_HEAP
#define POPPING_EMPTY_HEAP

    struct popping_empty_heap : public std::exception {
        const char *what() const throw() {
            return "Unable to pop a key from an empty heap.";
        }
    };

#endif

    template<typename X>
    X heap<X>::heappop() {
        if (this->contents > 0) {
            X temp = this->arr[0];
            this->arr[0] = this->arr[this->contents - 1];
            --this->contents;
            this->percolate_down(0);
            return temp;
        } else {
            throw popping_empty_heap();
        }


    }

    template<typename X>
    void heap<X>::percolate_up(int i) {
        if (i == 0) {
            return;
        }
        bool done = false;
        int cur = i;
        int parent;

        while (!done) {
            parent = cur / 2;
            if (cur % 2 == 0 && parent > 0) {
                --parent;
            }
            if (this->is_max_heap) {

                if (cur == parent) {
                    done = true;
                    break;
                }
                if (this->arr[cur] <= this->arr[parent]) {
                    done = true;
                } else {
                    X temp = this->arr[cur];
                    this->arr[cur] = this->arr[parent];
                    this->arr[parent] = temp;
                    cur = parent;
                }
            } else {
                if (cur == parent) {
                    done = true;
                    break;
                }
                if (this->arr[cur] >= this->arr[parent]) {
                    done = true;
                } else {
                    X temp = this->arr[cur];
                    this->arr[cur] = this->arr[parent];
                    this->arr[parent] = temp;
                    cur = parent;
                }
            }
        }
    }

    template<typename X>
    void heap<X>::percolate_down(int i) {
        if (i == this->contents - 1) {
            return;
        }
        int left;
        int right;
        bool done;


        if (this->is_max_heap) {
            int largest = i;
            done = false;
            while (!done) {
                left = 2 * i + 1;
                right = 2 * i + 2;
                if (left < this->contents && (this->arr[left] > this->arr[largest])) {
                    largest = left;
                }

                if (right < this->contents && (this->arr[right] > this->arr[largest])) {
                    largest = right;
                }

                if (largest != i) {
                    X temp = this->arr[i];
                    this->arr[i] = this->arr[largest];
                    this->arr[largest] = temp;
                } else {
                    done = true;
                }
                i = largest;
            }
        } else {
            int smallest = i;
            done = false;
            while (!done) {
                left = 2 * i + 1;
                right = 2 * i + 2;
                if (left < this->contents && (this->arr[left] < this->arr[smallest])) {
                    smallest = left;
                }

                if (right < this->contents && (this->arr[right] < this->arr[smallest])) {
                    smallest = right;
                }

                if (smallest != i) {
                    X temp = this->arr[i];
                    this->arr[i] = this->arr[smallest];
                    this->arr[smallest] = temp;
                } else {
                    done = true;
                }
                i = smallest;
            }
        }
    }

    template<typename X>
    bool heap<X>::empty() {
        if (this->contents <= 0) {
            return true;
        } else {
            return false;
        }
    }

    template<typename X>
    bool heap<X>::full() {
        if (this->contents < this->capacity) {
            return false;
        } else {
            return true;
        }
    }
}
#endif //ALGORITHMS_HEAP_H
