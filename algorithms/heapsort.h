//
// Created by sushant on 4/3/18.
//

#ifndef ALGORITHMS_HEAPSORT_H
#define ALGORITHMS_HEAPSORT_H

#include "../data_structures/heap.h"

namespace KAGU {
    template <typename X> void heapsort(X *arr, size_t arr_size, bool sort_ascending = true){
        heap <X> heap1(arr, arr_size, !sort_ascending);
        for(size_t i = 0; i < arr_size; ++i){
            arr[i] = heap1.heappop();
        }
    }
}

#endif //ALGORITHMS_HEAPSORT_H
