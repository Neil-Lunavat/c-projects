#ifndef UTILS_H_MAKEITUNIQUE
#define UTILS_H_MAKEITUNIQUE

#include <stdio.h>

char checkForIntersect(int x1, int w1, int x2, int w2) {
    return (x2 < x1 + w1 && x1 < x2 + w2) ? 1 : 0;
}

#endif  // UTILS_H_MAKEITUNIQUE