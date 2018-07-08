//
// Created by sushant on 6/12/18.
//

#ifndef ALGORITHMS_K_TH_SMALLEST_NUMBER_H
#define ALGORITHMS_K_TH_SMALLEST_NUMBER_H

#include "triplets.h"
#include "dynamic_heap.h"
#include "array_actors.h"

namespace KAGU {
    template<typename X>
    X get_kth_element(array_actor_2d<X> *input, int k, bool(*is_valid)(triplet_type1<X, int, int> &, array_actor_2d<X> *) = nullptr,
                      bool order_ascending = true) {
        X ret;
        if (input) {

            dynamic_heap<triplet_type1<X, int, int>> *h;
            int counts = 0;
            if (order_ascending) {
                //k-th smallest element
                //let's make a min heap
                h = new dynamic_heap<triplet_type1<X, int, int>>(false);
            } else {
                h = new dynamic_heap<triplet_type1<X, int, int>>(true);
            }
            if (input->rows() < input->columns()) {
                for (size_t i = 0; i < input->rows(); ++i) {
                    h->heappush(triplet_type1<X, int, int>((*input)[i][0], i, 0));
                }


                while (counts < k && !h->empty()) {
                    triplet_type1<X, int, int> p = h->heappop();

                    if (is_valid) {
                        if ((*is_valid)(p, input)) {
                            ++counts;
                            if (p.z < input->columns() - 1) {
                                h->heappush(triplet_type1<X, int, int>((*input)[p.y][p.z + 1], p.y, p.z + 1));
                            }
                            if (counts == k) {
                                ret = p.x;
                            }
                        } else {
                            if (p.z < input->columns() - 1) {
                                h->heappush(triplet_type1<X, int, int>((*input)[p.y][p.z + 1], p.y, p.z + 1));
                            }
                        }
                    } else {
                        ++counts;
                        if (p.z < input->columns() - 1) {
                            h->heappush(triplet_type1<X, int, int>((*input)[p.y][p.z + 1], p.y, p.z + 1));
                        }
                        if (counts == k) {
                            ret = p.x;
                        }
                    }

                }

            } else {
                for (size_t i = 0; i < input->columns(); ++i) {
                    h->heappush(triplet_type1<X, int, int>((*input)[0][i], 0, i));
                }

                while (counts < k && !h->empty()) {
                    triplet_type1<X, int, int> p = h->heappop();



                    if (is_valid) {
                        if ((*is_valid)(p, input)) {

                            ++counts;
                            if (p.y < input->rows() - 1) {
                                h->heappush(triplet_type1<X, int, int>((*input)[p.y+1][p.z], p.y + 1, p.z ));
                            }
                            if (counts == k) {
                                ret = p.x;
                            }
                        } else {
                            if (p.y < input->rows() - 1) {
                                h->heappush(triplet_type1<X, int, int>((*input)[p.y+1][p.z], p.y + 1, p.z ));
                            }
                        }
                    } else {
                        ++counts;
                        if (p.y < input->rows() - 1) {
                            h->heappush(triplet_type1<X, int, int>((*input)[p.y+1][p.z], p.y + 1, p.z ));
                        }
                        if (counts == k) {
                            ret = p.x;
                        }
                    }
                }
            }

            if (h) {
                delete h;
            }

        }
        return ret;
    }
}


#endif //ALGORITHMS_K_TH_SMALLEST_NUMBER_H
