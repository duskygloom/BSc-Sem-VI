#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

int PRINT = 1;

int X, Y, L, R, B, T;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

/**
 * @brief
 * Returns the code of point (x, y) with respect to the 
 * clipping window LRBT.
 */
int getCode(int x, int y) {
    int code = 0;
    code = 2 * code + (y > T);
    code = 2 * code + (y < B);
    code = 2 * code + (x > R);
    code = 2 * code + (x < L);
    return code;
}

void drawClippingWindow() {
    /* draw line divisions */
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_LINES);
    glVertex2i(L, -200); glVertex2i(L, 200);
    glVertex2i(R, -200); glVertex2i(R, 200);
    glVertex2i(-300, B); glVertex2i(300, B);
    glVertex2i(-300, T); glVertex2i(300, T);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    /* draw clipping window */
    // glColor3f(0.9, 0.2, 0.9);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glBegin(GL_QUADS);
    // glVertex2i(L, T); // left top
    // glVertex2i(R, T); // right top
    // glVertex2i(R, B); // right bottom
    // glVertex2i(L, B); // left bottom
    // glEnd();
}

void drawPoint() {
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2i(X, Y);
    glEnd();
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawClippingWindow();
    drawPoint();
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

void specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
        Y += 10; break;
        case GLUT_KEY_DOWN:
        Y -= 10; break;
        case GLUT_KEY_LEFT:
        X -= 10; break;
        case GLUT_KEY_RIGHT:
        X += 10; break;
    }
    glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case '\r':
        printf("Code: %04b\n", getCode(X, Y));
        break;
    }
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will take a point as input and then find
     * the code of the point with respect to a user
     * specified clipping window.
     * It also allows user to move the point using
     * arrow keys and print code using Enter key.
     */
    printf("Clipping window (LRBT): ");
    scanf("%d %d %d %d", &L, &R, &B, &T);

    printf("Point: ");
    scanf("%d %d", &X, &Y);

    printf("Code: %04b\n", getCode(X, Y));
    printf("Move the cursor point using arrow keys and print code by pressing Enter.\n");

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutCreateWindow("Code generation");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);

    glutMainLoop(); // loop
}
