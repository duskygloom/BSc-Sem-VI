#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

int PRINT = 0;

int TX, TY;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

const int X1 = -20, Y1 = -60;
const int X2 = -20, Y2 = 100;
const int X3 = 80, Y3 = 20;

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
Matrix3x3 transfomation;

void translate(int tx, int ty) {
    // create translation matrix
    Matrix3x3 translation = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };
    // multiply with global transformation matrix
    matrixMultiply(transfomation, translation);
}

float getTransformedX(int x, int y) {
    // multiplication of first row and first column
    return transfomation[0][0] * x
           + transfomation[0][1] * y
           + transfomation[0][2];
}

float getTransformedY(int x, int y) {
    // multiplication of second row and first column
    return transfomation[1][0] * x 
           + transfomation[1][1] * y
           + transfomation[1][2];
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawAxes();

    // a faint polygon to show the original position
    glColor4f(1, 1, 1, 0.25);
    // only draw the outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    glVertex2i(X1, Y1);
    glVertex2i(X2, Y2);
    glVertex2i(X3, Y3);
    glEnd();

    // begin transformation!
    unitMatrix(transfomation);
    translate(TX, TY);
    if (PRINT) printf("%d %d\n", TX, TY);

    // a solid polygon to show the translated position
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(getTransformedX(X1, Y1), getTransformedY(X1, Y1));
    glVertex2i(getTransformedX(X2, Y2), getTransformedY(X2, Y2));
    glVertex2i(getTransformedX(X3, Y3), getTransformedY(X3, Y3));
    glEnd();
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

void specialKeyFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            TX -= 10; break;
        case GLUT_KEY_RIGHT:
            TX += 10; break;
        case GLUT_KEY_UP:
            TY += 10; break;
        case GLUT_KEY_DOWN:
            TY -= 10; break;
    }
    glutPostRedisplay(); // redraw window
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will draw a polygon and then translate it
     * according to tx and ty specified by the user.
     * Additionally, the user can also use direction
     * keys to translate the polygon.
     */
    printf("Tx, Ty: ");
    scanf("%d %d", &TX, &TY);

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
    glutCreateWindow("2D translation");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);
    glutSpecialFunc(specialKeyFunc);

    printf("Use arrow keys to translate the polygon.\n");

    glutMainLoop(); // loop
}
