//
// Created by sushant on 4/15/18.
//

#ifndef ALGORITHMS_SEGMENT_TREE_H
#define ALGORITHMS_SEGMENT_TREE_H

#define DEFAULT_SEGMENT_TREE_SIZE 1024
namespace KAGU{

    template <typename X>
    struct segment_tree_node{
        int left;
        int right;
        X value;
    };

    template <typename X>
    class segment_tree{
    public:
        segment_tree(int size = DEFAULT_SEGMENT_TREE_SIZE);
        segment_tree(X* arr);
        ~segment_tree();

        virtual X merge_func(X a, X b) = 0;
    private:
        int capacity;
        int contents;

    };
}

#endif //ALGORITHMS_SEGMENT_TREE_H
