//
// Created by sushant on 7/21/18.
//

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

#include "unit_tests/stack_ut.h"
#include "unit_tests/queue_ut.h"
#include "unit_tests/circular_queue_ut.h"
#include "unit_tests/heapsort_ut.h"
#include "unit_tests/quicksort_ut.h"

using namespace KAGU;
int main() {
    std::cout << "Testing stack<int>" << std::endl;
    stack_push_pop_test<int> stack_test1;
    stack_test1.run();

    std::cout << "Testing queue<int>" << std::endl;
    queue_push_pop_test<int> queue_test1;
    queue_test1.run();

    std::cout << "Testing circular_queue<int>" << std::endl;
    circular_queue_push_pop_test<int>circular_queue_test1;
    circular_queue_test1.run();

    std::cout << "Testing heapsort<int>" << std::endl;
    heapsort_test<int> heapsort_test1;
    heapsort_test1.run();

    std::cout << "Testing quicksort<int>" << std::endl;
    quicksort_test<int> quicksort_test1;
    quicksort_test1.run();
}