#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector3d {
    float x, y, z;
} vector_t;

vector_t vectorSum(vector_t a, vector_t b);
vector_t vectorScale(vector_t v, float scalar);

float vectorDot(vector_t a, vector_t b);
vector_t vectorCross(vector_t a, vector_t b);

float vectorMagnitude(vector_t v);
float vectorDistance(vector_t a, vector_t b);
vector_t unitVector(vector_t v);

void printVector(const vector_t v);

#endif // VECTOR_H
