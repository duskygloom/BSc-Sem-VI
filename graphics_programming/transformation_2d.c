#define __USE_MISC // to include math.h constants

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

typedef float Matrix3x3[3][3];

#define DEG_TO_RAD(x) (x * M_PI / 180.0)

#define BIG_POINTS

int PRINT_TEXT = 1;

/**
 * @brief
 * Sets all elements of m to 0.0
 */
void zeroMatrix(Matrix3x3 m) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j] = 0.0;
}

void unitMatrix(Matrix3x3 m) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++i)
            m[i][j] = (i == j);
}

void copyMatrix(const Matrix3x3 src, Matrix3x3 dest) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            dest[i][j] = src[i][j];
}

void printMatrix(const Matrix3x3 m) {
    if (!PRINT_TEXT) return;
    printf("[\n");
    printf("  [%6.2f %6.2f %6.2f]\n", m[0][0], m[0][1], m[0][2]);
    printf("  [%6.2f %6.2f %6.2f]\n", m[1][0], m[1][1], m[1][2]);
    printf("  [%6.2f %6.2f %6.2f]\n", m[2][0], m[2][1], m[2][2]);
    printf("]\n");
}

/**
 * @brief
 * Multiplies a with b and stores the result in a.
 */
void multiplication(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 product;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            product[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
    copyMatrix(product, a);
}

void translateMatrix(Matrix3x3 matrix, float tx, float ty) {
    Matrix3x3 tm = { // translation matrix
        {1.0, 0.0, tx},
        {0.0, 1.0, ty},
        {0.0, 0.0, 1.0}
    };
    multiplication(matrix, tm);
}

void rotateMatrix(Matrix3x3 matrix, float degrees) {
    Matrix3x3 rm = { // rotation matrix
        {cosf(DEG_TO_RAD(degrees)), -sinf(DEG_TO_RAD(degrees)), 0.0},
        {sinf(DEG_TO_RAD(degrees)), cosf(DEG_TO_RAD(degrees)), 0.0},
        {0.0, 0.0, 1.0}
    };
    multiplication(matrix, rm);
}

void scaleMatrix(Matrix3x3 matrix, float sx, float sy) {
    Matrix3x3 sm = { // scaling matrix
        {sx, 0.0, 0.0},
        {0.0, sy, 0.0},
        {0.0, 0.0, 1.0}
    };
    multiplication(matrix, sm);
}

typedef enum {
    ALONG_X_AXIS,
    ALONG_Y_AXIS,
    ALONG_ORIGIN
} reflection_t;

void reflectMatrix(Matrix3x3 matrix, reflection_t type) {
    Matrix3x3 rm = { // reflection matrix
        {(type == ALONG_X_AXIS ? 1.0 : -1.0), 0.0, 0.0},
        {0.0, (type == ALONG_Y_AXIS ? 1.0 : -1.0), 0.0},
        {0.0, 0.0, 1.0}
    };
    multiplication(matrix, rm);
}

typedef struct {
    float x, y;
} Point;

Point newPoint(float x, float y) {
    Point p = {x, y};
    return p;
}

void printPoint(const Point p) {
    if (!PRINT_TEXT) return;
    printf("(%6.2f, %6.2f)\n", p.x, p.y);
}

static inline void plotPoint(Point p) {
    glVertex2d(p.x, p.y);
}

Point transformPoint(Point p, Matrix3x3 m) {
    float nx = p.x * m[0][0] + p.y * m[0][1] + m[0][2];
    float ny = p.x * m[1][0] + p.y * m[1][1] + m[1][2];
    Point np = {nx, ny};
    return np;
}

void drawStuff(void) {
    Matrix3x3 transformation = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    Point a = newPoint(4, 2);
    Point b = newPoint(4, 6);
    Point c = newPoint(8, 6);
    Point d = newPoint(8, 2);

    glClearColor(1, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);                       // yellow background

    /* X and Y axis */
    glColor3f(0, 1, 0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2d(300, 0);
    glVertex2d(-300, 0);
    glVertex2d(0, 400);
    glVertex2d(0, -400);
    glEnd();

    glColor3f(0, 0, 1);                                 // blue pen color
    #ifdef BIG_POINTS
    glPointSize(10);
    #else
    glPointSize(1);
    #endif

    glBegin(GL_LINES);
    plotPoint(a);
    plotPoint(b);
    plotPoint(b);
    plotPoint(c);
    plotPoint(c);
    plotPoint(d);
    plotPoint(d);
    plotPoint(a);
    glEnd();

    /* transform unit matrix */
    
    translateMatrix(transformation, 6, 4);
    
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_LINES);
    plotPoint(transformPoint(a, transformation));
    plotPoint(transformPoint(b, transformation));
    plotPoint(transformPoint(b, transformation));
    plotPoint(transformPoint(c, transformation));
    plotPoint(transformPoint(c, transformation));
    plotPoint(transformPoint(d, transformation));
    plotPoint(transformPoint(d, transformation));
    plotPoint(transformPoint(a, transformation));
    glEnd();
    
    rotateMatrix(transformation, 45);

    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_LINES);
    plotPoint(transformPoint(a, transformation));
    plotPoint(transformPoint(b, transformation));
    plotPoint(transformPoint(b, transformation));
    plotPoint(transformPoint(c, transformation));
    plotPoint(transformPoint(c, transformation));
    plotPoint(transformPoint(d, transformation));
    plotPoint(transformPoint(d, transformation));
    plotPoint(transformPoint(a, transformation));
    glEnd();
    
    translateMatrix(transformation, -6, -4);
    
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_LINES);
    plotPoint(transformPoint(a, transformation));
    plotPoint(transformPoint(b, transformation));
    plotPoint(transformPoint(b, transformation));
    plotPoint(transformPoint(c, transformation));
    plotPoint(transformPoint(c, transformation));
    plotPoint(transformPoint(d, transformation));
    plotPoint(transformPoint(d, transformation));
    plotPoint(transformPoint(a, transformation));
    glEnd();

    glFlush();

    PRINT_TEXT = 0;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Transformations");
    #ifdef BIG_POINTS
    gluOrtho2D(-40, 40, -30, 30);
    #else
    gluOrtho2D(-400, 400, -300, 300);
    #endif
    glutDisplayFunc(drawStuff);
    glutMainLoop();
    return 0;
}
