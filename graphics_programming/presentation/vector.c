#include "vector.h"

#include <math.h>
#include <stdio.h>

typedef struct Vector3d {
    float x, y, z;
} vector_t;

vector_t vectorSum(vector_t a, vector_t b) {
    vector_t result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

vector_t vectorScale(vector_t v, float scalar) {
    vector_t result;
    result.x = scalar * v.x;
    result.y = scalar * v.y;
    result.z = scalar * v.z;
    return result;
}

float vectorDot(vector_t a, vector_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vector_t vectorCross(vector_t a, vector_t b) {
    vector_t result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

float vectorMagnitude(vector_t v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vectorDistance(vector_t a, vector_t b) {
    return sqrtf((b.x - a.x) * (b.x - a.x) +
                 (b.y - a.y) * (b.y - a.y) +
                 (b.z - a.z) * (b.z - a.z));
}

vector_t unitVector(vector_t v) {
    float mag = vectorMagnitude(v);
    vector_t result;
    if (mag > 0) {
        result.x = v.x / mag;
        result.y = v.y / mag;
        result.z = v.z / mag;
    } else {
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }
    return result;
}

void printVector(const vector_t v) {
    printf("(%.4f, %.4f, %.4f)\n", v.x, v.y, v.z);
}
