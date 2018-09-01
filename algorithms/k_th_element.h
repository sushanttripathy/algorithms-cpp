//
// Created by sushant on 6/12/18.
//

#ifndef ALGORITHMS_K_TH_SMALLEST_NUMBER_H
#define ALGORITHMS_K_TH_SMALLEST_NUMBER_H

#include "../data_structures/triplets.h"
#include "../data_structures/dynamic_heap.h"
#include "../data_structures/array_actors.h"
#include "quicksort.h"
#include "../data_structures/duplet.h"

namespace KAGU {
    template<typename X>
    X get_kth_element_2d(array_actor_2d<X> *input, int k,
                         bool(*is_valid)(triplet_type1<X, int, int> &, array_actor_2d<X> *) = nullptr,
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
                                h->heappush(triplet_type1<X, int, int>((*input)[p.y + 1][p.z], p.y + 1, p.z));
                            }
                            if (counts == k) {
                                ret = p.x;
                            }
                        } else {
                            if (p.y < input->rows() - 1) {
                                h->heappush(triplet_type1<X, int, int>((*input)[p.y + 1][p.z], p.y + 1, p.z));
                            }
                        }
                    } else {
                        ++counts;
                        if (p.y < input->rows() - 1) {
                            h->heappush(triplet_type1<X, int, int>((*input)[p.y + 1][p.z], p.y + 1, p.z));
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


    //Median of Medians Algorithm
#define MEDIAN_OF_MEDIANS_SUBLIST_SIZE 5

    template<typename X>
    X median_of_medians(X *input, size_t size, int k, bool make_copy = true) {
        if (input && size) {

//            std::cout << "Input : [";
//            for (int i = 0; i < size; ++i)
//                std::cout << input[i] << ",";
//            std::cout << "] , " << k << std::endl;

            X output;
            X *input_copy;
            if (make_copy) {
                input_copy = (X *) calloc(sizeof(X), size);


                for (int i = 0; i < size; ++i) {
                    //Consider memcpy?
                    input_copy[i] = input[i];
                }
            } else {
                input_copy = input;
            }


            if (size <= MEDIAN_OF_MEDIANS_SUBLIST_SIZE) {
                quicksort(input_copy, size);
                output = input_copy[k - 1];

                if (make_copy)
                    free(input_copy);
                return output;
            }

            size_t median_array_size =
                    size / MEDIAN_OF_MEDIANS_SUBLIST_SIZE + ((size % MEDIAN_OF_MEDIANS_SUBLIST_SIZE) ? 1 : 0);
            X *medians = (X *) calloc(sizeof(X), median_array_size);

            int start = 0;
            int finish = 0;
            int count = 0;


            while (start < size) {
                finish = start + MEDIAN_OF_MEDIANS_SUBLIST_SIZE - 1;
                finish = (finish < size - 1) ? finish : (size - 1);
                quicksort<X>(input_copy + start, (finish - start + 1));

                int index = (start + finish) / 2;
                medians[count] = input_copy[index];

                start += MEDIAN_OF_MEDIANS_SUBLIST_SIZE;
                ++count;
            }

            X pivot;

            if (median_array_size <= MEDIAN_OF_MEDIANS_SUBLIST_SIZE) {
                quicksort<X>(medians, median_array_size);
                pivot = medians[median_array_size / 2];
            } else {
                pivot = median_of_medians < X > (medians, median_array_size, median_array_size / 2, false);
            }

//            std::cout << "pivot : " << pivot << std::endl;
            int piv_index = 0;
            while (input_copy[piv_index] != pivot && piv_index < size)
                ++piv_index;

            swap<X>(*(input_copy + piv_index), *(input_copy + size - 1));
            int i, j;

            partition<X>(input_copy, 0, size - 1, i, j);

//            std::cout << "Partitioned : [";
//            for (int l = 0; l < size; ++l)
//                std::cout << input_copy[l] << ",";
//            std::cout << "] , " << k << std::endl;

            if (i > j) {
                swap<int>(i, j);
            }

            if (i + 1 <= k && k <= j) {
                output = pivot;
            } else if (k < i + 1) {
                output = median_of_medians < X > (input_copy, i + 1, k, false);
            } else if (k > j) {
                output = median_of_medians < X > (input_copy + j, size - j, k - j, false);
            }

            free(medians);
            if (make_copy)
                free(input_copy);
            return output;
        }

    }

    template<typename X>
    X get_kth_element_1d(X *input, size_t size, int k) {
        X ret;
        if (k <= size) {

            return median_of_medians<X>(input, size, k);
        }
        return ret;
    }
}


#endif //ALGORITHMS_K_TH_SMALLEST_NUMBER_H
