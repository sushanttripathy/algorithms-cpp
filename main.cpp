//
// Created by sushant on 7/21/18.
//

#include <iostream>
#include "data_structures/circular_queue.h"
#include "data_structures/queue.h"
#include "data_structures/stack.h"
#include "data_structures/heap.h"
#include "data_structures/priority_queue.h"
#include "algorithms/steins_gcd.h"
#include "algorithms/heapsort.h"
#include "algorithms/quicksort.h"
#include "data_structures/binary_search_tree.h"
#include "data_structures/red_black_bst.h"
#include "data_structures/interval_tree.h"
#include "data_structures/segment_tree.h"
#include "data_structures/double_ended_queue.h"
#include "data_structures/binary_indexed_tree.h"
#include "data_structures/dynamic_heap.h"

#include <ctime>
#include <random>
#include <queue>
#include <stack>
#include <cassert>
#include "data_structures/trie.h"

#include "unit_tests/stack_ut.h"
#include "unit_tests/queue_ut.h"
#include "unit_tests/circular_queue_ut.h"
#include "unit_tests/heapsort_ut.h"
#include "unit_tests/quicksort_ut.h"
#include "unit_tests/binary_search_tree_ut.h"
#include "unit_tests/red_black_bst_ut.h"
#include "unit_tests/k_th_element_mom_ut.h"

#include "algorithms/k_th_element.h"

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


    std::cout << "Testing binary_search_tree<int>" << std::endl;
    binary_search_tree_ut<int> bst_test1;
    bst_test1.run();

    std::cout << "Testing red-black binary_search_tree<int>" << std::endl;
    red_black_bst_ut<int> rb_bst_ut1;
    rb_bst_ut1.run();

    std::cout << "Testing get_kth_element_1d<int>" << std::endl;
    k_th_element_mom_ut<int> k_th_element_mom_ut1;
    k_th_element_mom_ut1.run();

}