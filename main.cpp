#include <iostream>
#include "circular_queue.h"
#include "queue.h"
#include "stack.h"
#include "heap.h"
#include "priority_queue.h"
#include "steins_gcd.h"
#include "heapsort.h"
#include "quicksort.h"
#include "binary_search_tree.h"
#include "red_black_bst.h"
#include "interval_tree.h"
#include "segment_tree.h"
#include "double_ended_queue.h"
#include "binary_indexed_tree.h"
#include "dynamic_heap.h"

#include <ctime>
#include <random>
#include <queue>
#include <stack>
#include <cassert>
#include "trie.h"




using namespace KAGU;

template <typename X>
class segment_sum_tree:public segment_tree <X>{
public:
    segment_sum_tree(size_t size):segment_tree<X>(size) {

    }

    ~segment_sum_tree() {

    }

protected:
    X merge_func(const X &a, const X &b) {
        return a + b;
    }

    inline X not_found_value(){
        return (X) 0;
    };

    inline X null_value(){
        return (X) 0;
    };
};


template <typename X>
class binary_indexed_sum_tree:public binary_indexed_tree<X>{
public:
    binary_indexed_sum_tree(size_t size):binary_indexed_tree<X>(size){

    }

    ~binary_indexed_sum_tree(){

    }

protected:
    inline X merge_func(const X& a, const X& b){
        return a+b;
    }

    inline X initial_value(){
        return (X)0;
    }

    inline X null_value(){
        return (X)0;
    }
};

int main() {
    try{
        trie<char,int>t;
        int d0 = 2;
        t.insert_sequence((char*)"hello", 5, d0);
        int d;
        std::cout << d  << " " << t.find_sequence((char*)"hello", 5 , d) << std::endl;
        t.delete_sequence((char*)"hello", 5);
        d0 = 3;
        t.insert_sequence((char*)"hello", 5, d0);
        t.insert_sequence((char*)"hello world", sizeof("hello world"), d0);
        d = 0;
        std::cout << d  << " " << t.find_sequence((char*)"hello", 5 , d) << std::endl;
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
        exit(-1);
    }


    circular_queue<int> Q(10000);
    queue<long> Q2(10000);
    stack<long> stack1(10000);
    heap<long> heap1(10000, false);
    priority_queue<float, long> pq(10000);

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(-5000, 5000);


    for (int i = 0; i < 10000; ++i) {
        Q.put(i);
        Q2.put(i);
        stack1.push(i);
        heap1.heappush(5);
        pq.put(float(i) / 10.0, i);
    }

    std::cout << "Running time complexity tests on STL Queue " << std::endl;
    for (int i = 1; i < 11; ++i) {
        std::queue<int> temp_q;
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.push(j);
        }
        while (!temp_q.empty()) {
            temp_q.pop();
        }
        int stop_s = clock();
        std::cout << " Q Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Circular Queue " << std::endl << std::endl;

    std::cout << "Running time complexity tests on Circular Queue " << std::endl;
    for (int i = 1; i < 11; ++i) {
        circular_queue<int> temp_q(i * 1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.put(j);
        }
        while (!temp_q.empty()) {
            temp_q.get();
        }
        int stop_s = clock();
        std::cout << " CQ Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Circular Queue " << std::endl << std::endl;


    std::cout << "Running time complexity tests on Queue " << std::endl;
    for (int i = 1; i < 11; ++i) {
        queue<int> temp_q(i * 1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.put(j);
        }
        while (!temp_q.empty()) {
            temp_q.get();
        }
        int stop_s = clock();
        std::cout << " Q Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Queue " << std::endl << std::endl;

    std::cout << "Running time complexity tests on Double Ended Queue " << std::endl;
    for (int i = 1; i < 11; ++i) {
        double_ended_queue<int> temp_q;
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.put(j);
        }
        while (!temp_q.empty()) {
            temp_q.get();
        }
        int stop_s = clock();
        std::cout << " DEQ Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
    }

    std::cout << "Running time complexity tests on Double Ended Queue (put left, get left) " << std::endl;
    for (int i = 1; i < 11; ++i) {
        double_ended_queue<int> temp_q;
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.put_left(j);
        }
        while (!temp_q.empty()) {
            temp_q.get_left();
        }
        int stop_s = clock();
        std::cout << " DEQ Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
    }

    std::cout << "Finished running time complexity tests on Double Ended Queue " << std::endl << std::endl;


    std::cout << "Running time complexity tests on STL Priority Queue " << std::endl;
    for (int i = 1; i < 11; ++i) {
        std::priority_queue<std::pair<float, int>> temp_q;
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.push(std::pair<float, int>((float) j, j));
        }
        while (!temp_q.empty()) {
            temp_q.pop();
        }
        int stop_s = clock();
        std::cout << " PQ Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Priority Queue " << std::endl << std::endl;

    std::cout << "Running time complexity tests on Priority Queue " << std::endl;
    for (int i = 1; i < 11; ++i) {
        priority_queue<float, int> temp_q(i * 1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.put((float) j, j);
        }
        while (!temp_q.empty()) {
            temp_q.get();
        }
        int stop_s = clock();
        std::cout << " PQ Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Priority Queue " << std::endl << std::endl;

    std::cout << "Running time complexity tests on Heap " << std::endl;
    for (int i = 1; i < 11; ++i) {
        heap<int> temp_q(i * 1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.heappush(j);
        }
        while (!temp_q.empty()) {
            temp_q.heappop();
        }
        int stop_s = clock();
        std::cout << "HP Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Heap " << std::endl << std::endl;


    std::cout << "Running time complexity tests on Dynamic Heap " << std::endl;
    for (int i = 1; i < 11; ++i) {
        dynamic_heap<int> temp_q;
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.heappush(j);
        }
        while (!temp_q.empty()) {
            temp_q.heappop();
        }
        int stop_s = clock();
        std::cout << "DHP Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Dynamic Heap " << std::endl << std::endl;


    std::cout << "Running time complexity tests on STL Stack " << std::endl;
    for (int i = 1; i < 11; ++i) {
        std::stack<int> temp_q;
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.push(j);
        }
        while (!temp_q.empty()) {
            temp_q.pop();
        }
        int stop_s = clock();
        std::cout << "ST Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on STL Stack " << std::endl << std::endl;

    std::cout << "Running time complexity tests on Stack " << std::endl;
    for (int i = 1; i < 11; ++i) {
        stack<int> temp_q(i * 1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            temp_q.push(j);
        }
        while (!temp_q.empty()) {
            temp_q.pop();
        }
        int stop_s = clock();
        std::cout << "ST Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Stack " << std::endl << std::endl;



//    int a [] = {2,15,31,2,3,9,6,5,1,9,10,11,43,57};
    int a[20];
    int n = sizeof(a) / sizeof(int);
    for (int k = 0; k < n; k++) {
        a[k] = dis(gen);
    }
    heapsort(a, n, false);

    std::cout << " Heapsort results: " << std::endl;
    for (int i = 0; i < n; i++) {

        std::cout << a[i] << std::endl;
    }
    std::cout << std::endl;


    int b1[20];
    int b_n = sizeof(b1) / sizeof(int);
    for (int k = 0; k < b_n; ++k) {
        b1[k] = dis(gen);
    }
    dynamic_heap <int> dh_i(b1, b_n);

    std::cout << " Heapsort results using dynamic heap: " << std::endl;
    for (int i = 0; i < b_n; ++i) {

        std::cout << dh_i.heappop() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Running time complexity tests on Heapsort " << std::endl;
    for (int i = 1; i < 11; ++i) {
        int *arr = (int *) calloc(i * 1000, sizeof(int));
        for (int j = 0; j < i * 1000; ++j) {
            arr[j] = dis(gen);
        }

        int start_s = clock();

        heapsort(arr, i * 1000, false);
        int stop_s = clock();
        std::cout << "Arr Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
                  << " ms"
                  << std::endl;
        free(arr);
    }
    std::cout << "Finished running time complexity tests on Heapsort " << std::endl << std::endl;




//    int start_s=clock();
//    std::cout << std::endl << gcd(35492l,18324l) << std::endl;
//    int stop_s=clock();
//    std::cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;


    float b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 9.0, 1.0, 2.0, 3.0, 1.0, 11.0, 9.0};
    n = sizeof(b) / sizeof(float);

    quicksort(b, n, false);

    std::cout << " Quicksort results: " << std::endl;
    for (int j = 0; j < n; j++) {
        std::cout << b[j] << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Running time complexity tests on Quicksort " << std::endl;
    for (int i = 1; i < 11; ++i) {
        int *arr = (int *) calloc(i * 1000, sizeof(int));
        int *arr2 = (int *) calloc(i * 1000, sizeof(int));

        for (int j = 0; j < i * 1000; ++j) {
            arr[j] = dis(gen);
            arr2[j] = arr[j];
        }

        int start_s = clock();

        quicksort(arr, i * 1000, false, false);
        int stop_s = clock();

        double t1 = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

        start_s = clock();

        quicksort(arr2, i * 1000, false, true);
        stop_s = clock();

        double t2 = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

        std::cout << "Arr Size: " << i * 1000 << " time (iter) : " << t1 << " ms" << " time (recu) : " << t2 << " ms"
                  << std::endl;
        free(arr);
        free(arr2);
    }
    std::cout << "Finished running time complexity tests on Quicksort " << std::endl << std::endl;

    std::cout << "Comparing time complexity of Heapsort and Quicksort " << std::endl;
    for (int i = 1; i < 11; ++i) {
        int *arr = (int *) calloc(i * 1000, sizeof(int));
        int *arr2 = (int *) calloc(i * 1000, sizeof(int));

        for (int j = 0; j < i * 1000; ++j) {
            arr[j] = dis(gen);
            arr2[j] = arr[j];
        }

        int start_s = clock();

        quicksort(arr, i * 1000, false, false);
        int stop_s = clock();

        double t1 = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

        start_s = clock();

        heapsort(arr2, i * 1000, false);
        stop_s = clock();

        double t2 = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

        std::cout << "Arr Size: " << i * 1000 << " time (qs iter) : " << t1 << " ms" << " time (hs) : " << t2 << " ms"
                  << std::endl;
        free(arr);
        free(arr2);
    }
    std::cout << "Finished running time complexity comparisons of Quicksort and Heapsort " << std::endl << std::endl;


    std::cout << "Comparing worst case time complexity of Heapsort and Quicksort " << std::endl;
    for (int i = 1; i < 11; ++i) {
        int *arr = (int *) calloc(i * 1000, sizeof(int));
        int *arr2 = (int *) calloc(i * 1000, sizeof(int));

        for (int j = 0; j < i * 1000; ++j) {
            arr[j] = dis(gen);
//            arr2[j] = arr[j];
        }

        quicksort(arr,i * 1000, false, false);
        for (int j = 0; j < i * 1000; ++j) {
            arr2[j] = arr[j];
        }

        int start_s = clock();

        quicksort(arr, i * 1000, false, false);
        int stop_s = clock();

        double t1 = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

        start_s = clock();

        heapsort(arr2, i * 1000, false);
        stop_s = clock();

        double t2 = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

        std::cout << "Arr Size: " << i * 1000 << " time (qs iter) : " << t1 << " ms" << " time (hs) : " << t2 << " ms"
                  << std::endl;
        free(arr);
        free(arr2);
    }
    std::cout << "Finished running time complexity comparisons of Quicksort and Heapsort " << std::endl << std::endl;

    std::cout << sizeof(char) << std::endl;

    const int gen_size = 1000000;
    int arr[gen_size];
    for (int i = 0; i < gen_size; i++) {
        arr[i] = dis(gen);
    }

    std::cout << " Example of working of Red Black Binary Search Tree " << std::endl;
    int arr1[] = {99, 3, 9, 3, 7, 1, 8, 9, 11, 21, 33, 59, 219, 7, 11};

    red_black_binary_search_tree<int> *bst = new red_black_binary_search_tree<int>(arr1, sizeof(arr1) / sizeof(int));
    //arr1,

//    for (int i = 0; i <  sizeof(arr1) / sizeof(int); i++ ){
//        bst->insert(arr1[i]);
//    }

    std::cout << " In-order tree traversal : " << std::endl;
    bst->print_traversal_results();//binary_search_tree<int>::PREORDER);

    std::cout << " Removing 9" << std::endl;
    bst->remove(9);

    bst->print_traversal_results();

    std::cout << " Removing 3" << std::endl;
    bst->remove(3);

    bst->print_traversal_results();

    std::cout << " Removing 3" << std::endl;
    bst->remove(3);

    bst->print_traversal_results();

    std::cout << " Searching for 11 " << std::endl;

    std::cout << (bst->find(11) != NULL) << std::endl;

    std::cout << " Searching for 12 " << std::endl;

    std::cout << (bst->find(12) != NULL) << std::endl;

    std::cout << "Done with Red Black BST demo." << std::endl << std::endl;

    std::cout << "Running tests on normal Binary Search Tree intialized using an array of " << gen_size << " integers."
              << std::endl;
    int start_s = clock();
    binary_search_tree<int> *binary_search_tree1 = new binary_search_tree<int>(arr, gen_size);

    int stop_s = clock();
    std::cout << "Insert time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;


    start_s = clock();
    for (int i = 0; i < gen_size; i++) {
        if (binary_search_tree1->find(arr[i]) == NULL)
            std::cerr << "Error with find" << std::endl;
    }

    binary_search_tree1->find(arr[10]);
    stop_s = clock();
    std::cout << "Find time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;

    start_s = clock();
    for (int i = 0; i < gen_size; i++) {
        binary_search_tree1->remove(arr[i]);
    }
    stop_s = clock();

    std::cout << "Remove time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;

    std::cout << std::endl;
    std::cout << "Running tests on Red Black Binary Search Tree intialized using the same array of " << gen_size
              << " integers." << std::endl;

    start_s = clock();


    red_black_binary_search_tree<int> *binary_search_tree2 = new red_black_binary_search_tree<int>(arr, gen_size);
    stop_s = clock();
    std::cout << "Insert time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;


    start_s = clock();
    for (int i = 0; i < gen_size; i++) {
        if (binary_search_tree2->find(arr[i]) == NULL)
            std::cerr << "Error with find" << std::endl;
    }


    stop_s = clock();
    std::cout << "Find time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;

    start_s = clock();
    for (int i = 0; i < gen_size; i++) {
        binary_search_tree2->remove(arr[i]);
    }
    stop_s = clock();
    std::cout << "Remove time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;

    std::cout << std::endl;

    interval<int>B[10];
    interval_tree <int> *A = new interval_tree<int>();
    A->insert_interval(0,1);
    A->insert_interval(0,1);
    A->insert_interval(1,2);
    A->insert_interval(2,3);
    A->insert_interval(1,2);
    A->insert_interval(1,3);
    A->insert_interval(2,3);
    A->insert_interval(3,4);
    A->insert_interval(0,1);
    size_t found  = A->find_overlapping_intervals(2, 3, B, 10);
    std::cout << " Found " << found << " intervals : " << std::endl;
    for(size_t i = 0; i < found; ++i){
        std::cout << B[i] << std::endl;
    }

    interval_tree_results <int> *cursor = A->find_overlapping_intervals(2, 3);
    std::cout << " Found : " << cursor->get_num_nodes() << " results" << std::endl;
    doubly_linked_list_node <interval<int>> *current = cursor->get_head();
    while (current != NULL){
        std::cout << current->val << std::endl;
        current = current->next;
    }
    A->clear_results(cursor);

    A->print_traversal_results(interval_tree<int>::PREORDER);



    std::cout << "Running time complexity tests on Segment Tree " << std::endl;
    for (int i = 1; i < 11; ++i) {
        segment_sum_tree<int> *S = new segment_sum_tree<int>(i*1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            S->update(j, j+1);
        }

        for (int j = 0; j < i * 1000; ++j) {
            for(int k = j+1; k < i*1000;++k){
                S->get_range_func(j, j+1);
            }
        }

        int stop_s = clock();
        std::cout << "SegT Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Segment Tree " << std::endl << std::endl;

    std::cout << "Running time complexity tests on Binary Indexed (Fenwick) Tree " << std::endl;
    for (int i = 1; i < 11; ++i) {
        binary_indexed_sum_tree<int> *S = new binary_indexed_sum_tree<int>(i*1000);
        int start_s = clock();

        for (int j = 0; j < i * 1000; ++j) {
            S->update(j, j+1);
        }

        for (int j = 0; j < i * 1000; ++j) {
            for(int k = j+1; k < i*1000;++k){
                S->get_merge_func_until(k) - S->get_merge_func_until(j);
            }
        }

        int stop_s = clock();
        std::cout << "BiT Size: " << i * 1000 << " time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << " ms"
                  << std::endl;
    }
    std::cout << "Finished running time complexity tests on Binary Indexed Tree " << std::endl << std::endl;


    binary_indexed_sum_tree<int> *S = new binary_indexed_sum_tree<int>(1000);
    for(size_t i = 0; i < 1000; ++i){
        S->update(i, i+1);
    }

    std::cout << S->get_merge_func_until(499) << std::endl;

    std::cout << " Checking Segment Tree and Binary Indexed Tree coherence." << std::endl;

    binary_indexed_sum_tree<int> *S1 = new binary_indexed_sum_tree<int>(1000);
    segment_sum_tree<int> *S2 = new segment_sum_tree<int>(1000);
    for (size_t i = 0; i < 1000; ++i){
        S1->update(i, i+1);
        S2->update(i, i+1);
    }

    for (size_t i = 0; i < 1000; ++i){
        for (size_t j = i+1; j < 1000; ++j){
            assert((S1->get_merge_func_until(j) - S1->get_merge_func_until(i-1)) == S2->get_range_func(i, j));
        }
    }

    std::cout << " All checks passed" << std::endl;





    return 0;
}


