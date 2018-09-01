//
// Created by sushant on 4/3/18.
//

#ifndef ALGORITHMS_STEINS_GCD_H
#define ALGORITHMS_STEINS_GCD_H
namespace KAGU {
    int steins_gcd(int a, int b);
    long steins_gcd(long a, long b);
    long long steins_gcd(long long a, long long b);

#ifndef GCD_DEF
#define GCD_DEF
#define GCD_STEINS
    int gcd(int a, int b);

    long gcd(long a, long b);

    long long gcd(long long a, long long b);
#endif
}




#endif //ALGORITHMS_STEINS_GCD_H
