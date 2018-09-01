//
// Created by sushant on 7/21/18.
//

#ifndef ALGORITHMS_BASIC_STATISTICS_H
#define ALGORITHMS_BASIC_STATISTICS_H

#include <complex>

namespace KAGU {
    template<typename X>
    X get_standard_deviation_and_mean(X *array, int array_size, X &mean) {
        X sum_ = 0;
        for (int i = 0; i < array_size; ++i) {
            sum_ += array[i];
        }
        X mean_ = sum_ / (X) array_size;

        X var = 0;
        for (int i = 0; i < array_size; ++i) {
            var += (array[i] - mean_) * (array[i] - mean_);
        }
        var /= (X) (array_size - 1);
        mean = mean_;

        return std::sqrt(var);
    }

    template<typename X>
    X get_scaled_standard_deviation_and_mean(X *array, int array_size, X &mean) {
        X min_ = array[0];
        X max_ = array[0];

        for (int i = 1; i < array_size; ++i) {
            if (array[i] > max_) {
                max_ = array[i];
            }
            if (array[i] < min_) {
                min_ = array[i];
            }
        }

        X range_ = max_ - min_;

        X sum_ = 0;
        for (int i = 0; i < array_size; ++i) {
            sum_ += array[i];
        }
        X mean_ = sum_ / (X) array_size;

        X var = 0;
        for (int i = 0; i < array_size; ++i) {
            var += ((array[i] - mean_)/range_) * ((array[i] - mean_)/range_);
        }
        var /= (X) (array_size - 1);
        mean = (mean_-min_)/range_;

        return std::sqrt(var);
    }


    template <typename X>
    X get_residual_sum_of_squares(X *array1, X *array2, int array_size){
        X rss = 0;
        for (int i =0; i < array_size; ++i){
            rss += (array1[i] - array2[i])*(array1[i] - array2[i]);
        }
        return rss;
    }

    template <typename X>
    X get_absolute_residual_sum(X *array1, X *array2, int array_size){
        X rss = 0;
        for (int i =0; i < array_size; ++i){
            rss += std::abs(array1[i] - array2[i]);
        }
        return rss;
    }
}

#endif //ALGORITHMS_BASIC_STATISTICS_H
