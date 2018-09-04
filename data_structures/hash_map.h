//
// Created by sushant on 9/2/18.
//

#ifndef ALGORITHMS_HASH_MAP_H
#define ALGORITHMS_HASH_MAP_H

#include "doubly_linked_list.h"

namespace KAGU{
    template <typename X, typename Y>
    class hash_map{
    public:
        hash_map(int n_buckets = 10000);
        ~hash_map();
        virtual int hash_code(X key);

        virtual bool has_key(X key);
        virtual Y operator [] (const X& key);

    protected:

    };
}


#endif //ALGORITHMS_HASH_MAP_H
