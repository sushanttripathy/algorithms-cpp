//
// Created by sushant on 6/13/18.
//

#ifndef ALGORITHMS_TRIPLET_H
#define ALGORITHMS_TRIPLET_H

template <typename X, typename Y, typename Z>
struct triplet_type1{
public:
    triplet_type1(X x, Y y, Z z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator == (const triplet_type1<X,Y,Z> &input){
        return this->x == input.x;
    }

    bool operator != (const triplet_type1<X,Y,Z> &input){
        return this->x != input.x;
    }

    bool operator > (const triplet_type1<X,Y,Z> &input){
        return this->x > input.x;
    }

    bool operator >= (const triplet_type1<X,Y,Z> &input){
        return this->x >= input.x;
    }

    bool operator < (const triplet_type1<X,Y,Z> &input){
        return this->x < input.x;
    }

    bool operator <= (const triplet_type1<X,Y,Z> &input){
        return this->x <= input.x;
    }

    X x;
    Y y;
    Z z;
};

#endif //ALGORITHMS_TRIPLET_H
