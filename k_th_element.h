//
// Created by sushant on 6/12/18.
//

#ifndef ALGORITHMS_K_TH_SMALLEST_NUMBER_H
#define ALGORITHMS_K_TH_SMALLEST_NUMBER_H

#include "triplets.h"
#include "heap.h"
#include "array_actors.h"

namespace KAGU{
    template <typename X>
    X get_kth_element(array_actor_2d<X> *input, bool order_ascending = true){
        if(input){
            heap <triplet_type1<X, int, int>> *h;
            if(order_ascending){
                //k-th smallest element
                //let's make a min heap
                h = input->size();
            }
        }
    }
}


#endif //ALGORITHMS_K_TH_SMALLEST_NUMBER_H
