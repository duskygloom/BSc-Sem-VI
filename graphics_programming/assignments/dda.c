#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

/**
 * @note
 * For future self:
 * In book and other sources, ROUND(x) is defined as
 * (int)(x + 0.5) But this doesn't work for negative
 * numbers. To make it work for negative numbers, we
 * need to subtract 0.5 from x.
 */
#define ROUND(x) ((int)(x + 0.5 * (x < 0 ? -1 : 1)))

int PRINT = 0;

int X1, Y1, X2, Y2;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    double dx, dy;
    int steps;

    double slope = (double)(y2 - y1) / (x2 - x1);

    if (slope <= 1 && slope >= -1) { // x increases faster than or equal to y
        dx = x2 > x1 ? 1 : -1;
        dy = dx * slope;
        steps = dx * (x2 - x1);
    } else { // y increases faster than x
        dy = y2 > y1 ? 1 : -1;
        dx = dy / slope;
        steps = dy * (y2 - y1);
    }

    double x = x1, y = y1;

    for (int i = 0; i <= steps; ++i) {
        glBegin(GL_POINTS);
        if (PRINT) printf("(%d, %d)\n", ROUND(x), ROUND(y));
        glVertex2i(ROUND(x), ROUND(y));
        glEnd();
        x += dx;
        y += dy;
    }
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glColor3f(1, 1, 1);
    drawLine(X1, Y1, X2, Y2);
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will draw a line from (X1, Y1) to (X2, Y2)
     * using DDA algorithm.
     */
    printf("Point 1: ");
    scanf("%d %d", &X1, &Y1);
    printf("Point 2: ");
    scanf("%d %d", &X2, &Y2);

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutCreateWindow("DDA");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);

    glutMainLoop(); // loop
}
