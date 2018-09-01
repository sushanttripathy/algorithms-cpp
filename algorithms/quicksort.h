//
// Created by sushant on 4/3/18.
//

#ifndef ALGORITHMS_QUICKSORT_H
#define ALGORITHMS_QUICKSORT_H

#include <stdlib.h>
#include "../data_structures/stack.h"
namespace KAGU{


    template <typename X> void swap( X &a, X &b){
        X temp = a;
        a = b;
        b = temp;
    }

    template <typename X> void partition(X* arr,  int l, int r, int &i, int &j, bool sort_ascending = true){
        i = l-1, j = r;
        int p = l-1, q = r;
        X pivot = arr[r];
        while(true)
        {


            if (sort_ascending) {
                while (arr[++i] < pivot);

                while (arr[--j] > pivot)
                    if (j == l)
                        break;
            }
            else{
                while (arr[++i] > pivot);

                while (arr[--j] < pivot)
                    if (j == l)
                        break;
            }

            if(i >= j)
                break;

            swap(arr[i], arr[j]);

            if (arr[i] == pivot)
            {
                ++p;
                swap(arr[p], arr[i]);
            }

            if (arr[j] == pivot)
            {
                --q;
                swap(arr[j], arr[q]);
            }

        }
        swap(arr[i], arr[r]);
        j = i-1;
        for (int k = l; k < p; k++, j--)
            swap(arr[k], arr[j]);

        i = i+1;
        for (int k = r-1; k > q; k--, i++)
            swap(arr[i], arr[k]);
    }



    template <typename X> void quicksort_recursive(X *arr, int l, int r, bool sort_ascending = true){
        if (r <= l) return;

        int i, j;

        partition(arr, l, r, i, j, sort_ascending);

        quicksort_recursive(arr, l, j, sort_ascending);
        quicksort_recursive(arr, i, r, sort_ascending);
    }

    template <typename X> void quicksort_iterative(X *arr, int l, int r, bool sort_ascending = true){
        if (r <= l) return;

        stack <int> s(r - l + 1);
        s.push(r);
        s.push(l);

        int i, j;

        while(!s.empty()){
            l = s.pop();
            r = s.pop();
            partition(arr, l, r, i , j , sort_ascending);

            if(j > l){
                s.push(j);
                s.push(l);
            }

            if(r > i){
                s.push(r);
                s.push(i);
            }
        }
    }

    template <typename X> void quicksort(X *arr, size_t arr_size, bool sort_ascending = true, bool use_recursive = true){
        if(use_recursive)
            quicksort_recursive(arr, 0, arr_size - 1, sort_ascending);
        else
            quicksort_iterative(arr, 0, arr_size - 1, sort_ascending);
    }
}

#endif //ALGORITHMS_QUICKSORT_H
