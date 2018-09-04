cmake_minimum_required(VERSION 3.6)
project(algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp data_structures/queue.h data_structures/circular_queue.h data_structures/stack.h data_structures/heap.h data_structures/priority_queue.h algorithms/steins_gcd.h algorithms/steins_gcd.cpp algorithms/heapsort.h algorithms/quicksort.h data_structures/segment_tree.h data_structures/binary_search_tree.h data_structures/red_black_bst.h data_structures/interval_tree.h data_structures/doubly_linked_list.h data_structures/double_ended_queue.h data_structures/binary_indexed_tree.h algorithms/k_th_element.h data_structures/triplets.h data_structures/array_actors.h data_structures/dynamic_heap.h data_structures/trie.h unit_test_framework.h unit_tests/stack_ut.h algorithms/basic_statistics.h unit_tests/queue_ut.h unit_tests/circular_queue_ut.h unit_tests/heapsort_ut.h unit_tests/quicksort_ut.h unit_tests/k_th_element_ut.h unit_tests/binary_search_tree_ut.h data_structures/duplet.h unit_tests/red_black_bst_ut.h unit_tests/k_th_element_mom_ut.h data_structures/hash_map.h)
add_executable(algorithms ${SOURCE_FILES})