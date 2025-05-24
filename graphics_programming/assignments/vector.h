#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector2d {
    float x, y;
} vector_t;

vector_t vectorSum(vector_t a, vector_t b);
vector_t vectorDiff(vector_t a, vector_t b);
vector_t vectorScale(vector_t v, float scalar);

float vectorDot(vector_t a, vector_t b);

/**
 * @brief
 * Returns the anti-clockwise perpendicular vector to a.
 */
vector_t normalVector(vector_t a);

float vectorMagnitude(vector_t v);
float vectorDistance(vector_t a, vector_t b);
vector_t unitVector(vector_t v);

void printVector(const vector_t v);

#endif // VECTOR_H
