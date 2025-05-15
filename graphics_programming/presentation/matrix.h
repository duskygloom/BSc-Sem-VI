#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_SIZE 4

typedef float Matrix4x4[MATRIX_SIZE][MATRIX_SIZE];

void unitMatrix(Matrix4x4 matrix);

/**
 * @brief
 * Multiplies two 4x4 matrices and stores the result in a.
 */
void multiplyMatrix(Matrix4x4 a, const Matrix4x4 b);

#endif // MATRIX_H
