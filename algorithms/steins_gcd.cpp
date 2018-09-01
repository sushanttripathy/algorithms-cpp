//
// Created by sushant on 4/3/18.
//
#include "steins_gcd.h"


int KAGU::steins_gcd(int a, int b) {
    int gcd = 1;
    int x, y;

    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    } else if (a == b) {
        return a;
    } else {
        x = a;
        y = b;
        if (x < 0) {
            x *= -1;
        }
        if (y < 0) {
            y *= -1;
        }
        while (true) {
            if (x == 0 || y == 0 || x == y) {
                if (x == y) {
                    gcd *= x;
                }
                return gcd;
            }

            if (~x & 1) {
                // x is even
                if (~y & 1) {
                    // y is even
                    gcd *= 2;
                    x = x >> 1;
                    y = y >> 1;
                } else {
                    x = x >> 1;
                }
            } else if (~y & 1) {
                //y is even x is not
                y = y >> 1;
            } else {
                // both odd
                if (y > x) {
                    y = (y - x) >> 1;
                } else if (x > y) {
                    x = (x - y) >> 1;
                }
            }
        }

    }
}


long KAGU::steins_gcd(long a, long b) {
    long gcd = 1;
    long x, y;

    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    } else if (a == b) {
        return a;
    } else {
        x = a;
        y = b;
        if (x < 0) {
            x *= -1;
        }
        if (y < 0) {
            y *= -1;
        }
        while (true) {
            if (x == 0 || y == 0 || x == y) {
                if (x == y) {
                    gcd *= x;
                }
                return gcd;
            }

            if (~x & 1) {
                // x is even
                if (~y & 1) {
                    // y is even
                    gcd *= 2;
                    x = x >> 1;
                    y = y >> 1;
                } else {
                    x = x >> 1;
                }
            } else if (~y & 1) {
                //y is even x is not
                y = y >> 1;
            } else {
                // both odd
                if (y > x) {
                    y = (y - x) >> 1;
                } else if (x > y) {
                    x = (x - y) >> 1;
                }
            }
        }

    }
}

long long KAGU::steins_gcd(long long a, long long b) {
    long long gcd = 1;
    long long x, y;

    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    } else if (a == b) {
        return a;
    } else {
        x = a;
        y = b;
        if (x < 0) {
            x *= -1;
        }
        if (y < 0) {
            y *= -1;
        }
        while (true) {
            if (x == 0 || y == 0 || x == y) {
                if (x == y) {
                    gcd *= x;
                }
                return gcd;
            }

            if (~x & 1) {
                // x is even
                if (~y & 1) {
                    // y is even
                    gcd *= 2;
                    x = x >> 1;
                    y = y >> 1;
                } else {
                    x = x >> 1;
                }
            } else if (~y & 1) {
                //y is even x is not
                y = y >> 1;
            } else {
                // both odd
                if (y > x) {
                    y = (y - x) >> 1;
                } else if (x > y) {
                    x = (x - y) >> 1;
                }
            }
        }

    }
}

#ifdef GCD_STEINS

int KAGU::gcd(int a, int b) {
    return steins_gcd(a, b);
}

long KAGU::gcd(long a, long b) {
    return steins_gcd(a, b);
}

long long KAGU::gcd(long long a, long long b) {
    return steins_gcd(a, b);
}

#endif