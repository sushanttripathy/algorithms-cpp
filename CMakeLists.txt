cmake_minimum_required(VERSION 3.6)
project(algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp queue.h circular_queue.h stack.h heap.h priority_queue.h steins_gcd.h steins_gcd.cpp heapsort.h quicksort.h segment_tree.h binary_search_tree.h red_black_bst.h interval_tree.h doubly_linked_list.h double_ended_queue.h binary_indexed_tree.h k_th_element.h triplets.h array_actors.h dynamic_heap.h auto_suggest.h)
add_executable(algorithms ${SOURCE_FILES})