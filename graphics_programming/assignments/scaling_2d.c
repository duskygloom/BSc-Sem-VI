#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int PRINT = 0;
int transformPolygon = 1;

int PX, PY;
float SX, SY;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

int X1 = -20, Y1 = -60;
int X2 = -20, Y2 = 100;
int X3 = 80, Y3 = 20;

/* Matrix stuff. */

typedef float Matrix3x3[3][3];

void unitMatrix(Matrix3x3 m) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j] = (i == j) ? 1 : 0;
}

/**
 * @brief
 * Multiplies a and b and stores the result in a.
 */
void matrixMultiply(Matrix3x3 a, Matrix3x3 b) {
    // store result in c
    Matrix3x3 c;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < 3; ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
    // copy c to a
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            a[i][j] = c[i][j];
}

/* Matrix stuff ends. */

// global variable to store transformation matrix
Matrix3x3 transformation;

void translate(int tx, int ty) {
    // create translation matrix
    Matrix3x3 translation = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };
    // multiply with global transformation matrix
    matrixMultiply(transformation, translation);
}

void scale(float sx, float sy) {
    // create translation matrix
    Matrix3x3 scaling = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };
    // multiply with global transformation matrix
    matrixMultiply(transformation, scaling);
}

float getTransformedX(int x, int y) {
    // multiplication of first row and first column
    return transformation[0][0] * x
           + transformation[0][1] * y
           + transformation[0][2];
}

float getTransformedY(int x, int y) {
    // multiplication of second row and first column
    return transformation[1][0] * x 
           + transformation[1][1] * y
           + transformation[1][2];
}

void retransform() {
    // begin transformation!
    unitMatrix(transformation);
    translate(PX, PY);
    scale(SX, SY);
    translate(-PX, -PY);
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawAxes();

    glColor3f(1, 1, 0); // yellow
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2i(PX, PY); // pivot point
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // draw a faint polygon to show the original position
    glColor4f(1, 1, 1, 0.25);
    glBegin(GL_TRIANGLES);
    glVertex2i(X1, Y1);
    glVertex2i(X2, Y2);
    glVertex2i(X3, Y3);
    glEnd();

    if (transformPolygon) {
        // a solid polygon to show the translated position
        glColor4f(1, 1, 1, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex2i(getTransformedX(X1, Y1), getTransformedY(X1, Y1));
        glVertex2i(getTransformedX(X2, Y2), getTransformedY(X2, Y2));
        glVertex2i(getTransformedX(X3, Y3), getTransformedY(X3, Y3));
        glEnd();
    }
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            SX -= 0.1; break;
        case 'd':
            SX += 0.1; break;
        case 'w':
            SY += 0.1; break;
        case 's':
            SY -= 0.1; break;
    }
    retransform();
    transformPolygon = 1; // show polygon transformation
    glutPostRedisplay();
}

void specialKeyFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            PX -= 10; break;
        case GLUT_KEY_RIGHT:
            PX += 10; break;
        case GLUT_KEY_UP:
            PY += 10; break;
        case GLUT_KEY_DOWN:
            PY -= 10; break;
    }
    transformPolygon = 0; // dont show polygon transformation
                          // when moving pivot
    SX = SY = 1; // reset scaling factors
    glutPostRedisplay(); // redraw window
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will draw a polygon and then scale it
     * along a pivot point.
     */
    printf("Pivot(x, y): ");
    scanf("%d %d", &PX, &PY);
    printf("Scaling factor (x, y): ");
    scanf("%f %f", &SX, &SY);

    retransform(); // initial transformation

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA);
    glutCreateWindow("2D scaling");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);
    glutSpecialFunc(specialKeyFunc);
    glutKeyboardFunc(keyboardFunc);

    printf("Use arrow keys to move the pivot and A,W,S,D keys to control scaling.\n");

    glutMainLoop(); // loop
}
