#include "matrix.h"

void unitMatrix(Matrix4x4 matrix) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void multiplyMatrix(Matrix4x4 a, const Matrix4x4 b) {
    Matrix4x4 result;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0.0f;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    // copy result into a
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            a[i][j] = result[i][j];
        }
    }
}
