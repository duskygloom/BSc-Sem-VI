#include "vector.h"

#include <math.h>
#include <stdio.h>

vector_t vectorSum(vector_t a, vector_t b) {
    vector_t result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

vector_t vectorDiff(vector_t a, vector_t b) {
    vector_t result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

vector_t vectorScale(vector_t v, float scalar) {
    vector_t result;
    result.x = scalar * v.x;
    result.y = scalar * v.y;
    return result;
}

float vectorDot(vector_t a, vector_t b) {
    return a.x * b.x + a.y * b.y;
}

vector_t normalVector(vector_t a) {
    return (vector_t){-a.y, a.x};
}

float vectorMagnitude(vector_t v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

float vectorDistance(vector_t a, vector_t b) {
    return sqrtf((b.x - a.x) * (b.x - a.x) +
                 (b.y - a.y) * (b.y - a.y));
}

vector_t unitVector(vector_t v) {
    float mag = vectorMagnitude(v);
    vector_t result;
    if (mag > 0) {
        result.x = v.x / mag;
        result.y = v.y / mag;
    } else {
        result.x = 0;
        result.y = 0;
    }
    return result;
}

void printVector(const vector_t v) {
    printf("(%.4f, %.4f)\n", v.x, v.y);
}
