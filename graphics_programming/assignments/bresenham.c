#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

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

void drawPoint(int x, int y) {
    glVertex2i(x, y);
    if (PRINT) printf("(%d, %d)\n", x, y);
}

void drawLine(int x1, int y1, int x2, int y2) {
    /* dx and dy are absolute values. 
       Their signs are stored in xincr and yincr resp. */
    int dx = abs(x2 - x1), dy = abs(y2 - y1);

    int xincr = (x2 > x1) * 2 - 1;
    int yincr = (y2 > y1) * 2 - 1;

    glBegin(GL_POINTS);

    drawPoint(x1, y1);
    if (PRINT) printf("(%d, %d)\n", x1, y1);

    if (dx == 0) {
        /* vertical line with infinite slope */
        do {
            y1 += yincr;
            drawPoint(x1, y1);
        } while (y1 != y2);
    } else if (dy == 0) {
        /* horizontal line with zero slope */
        do {
            x1 += xincr;
            drawPoint(x1, y1);
        } while (x1 != x2);
    } else if (dx > dy) {
        /* x increases rapidly */
        int p = 2*dy - dx;
        do {
            x1 += xincr;
            y1 += (p >= 0) * yincr;
            drawPoint(x1, y1);
            p += 2*dy - (p >= 0) * 2*dx;
        } while (x1 != x2);
    } else {
        /* y increases rapidly or equally */
        int p = 2*dx - dy;
        do {
            x1 += (p >= 0) * xincr;
            y1 += yincr;
            drawPoint(x1, y1);
            p += 2*dx - (p >= 0) * 2*dy;
        } while (y1 != y2);
    }

    glEnd();
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
     * using Bresenham algorithm.
     */
    printf("Point 1: ");
    scanf("%d %d", &X1, &Y1);
    printf("Point 2: ");
    scanf("%d %d", &X2, &Y2);

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutCreateWindow("Bresenham");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);

    glutMainLoop(); // loop
}
