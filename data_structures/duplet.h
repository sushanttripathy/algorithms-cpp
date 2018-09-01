//
// Created by sushant on 8/23/18.
//

#ifndef ALGORITHMS_TUPLE_H
#define ALGORITHMS_TUPLE_H

template <typename X, typename Y>
struct duplet_type1{
public:

    duplet_type1(){

    }

    duplet_type1(X x, Y y){
        this->x = x;
        this->y = y;

    }

    bool operator == (const duplet_type1<X,Y> &input){
        return this->x == input.x;
    }

    bool operator != (const duplet_type1<X,Y> &input){
        return this->x != input.x;
    }

    bool operator > (const duplet_type1<X,Y> &input){
        return this->x > input.x;
    }

    bool operator >= (const duplet_type1<X,Y> &input){
        return this->x >= input.x;
    }

    bool operator < (const duplet_type1<X,Y> &input){
        return this->x < input.x;
    }

    bool operator <= (const duplet_type1<X,Y> &input){
        return this->x <= input.x;
    }

    X x;
    Y y;
};

#endif //ALGORITHMS_TUPLE_H
