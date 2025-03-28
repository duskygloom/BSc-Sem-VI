#include <GL/glut.h>

#include <stdio.h>

#define APP_WIDTH 600
#define APP_HEIGHT 400

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    /* dx and dy are absolute values. 
       Their signs are stored in xincr and yincr resp. */
    int dx = abs(x2 - x1), dy = abs(y2 - y1);

    int xincr = (x2 > x1) * 2 - 1;
    int yincr = (y2 > y1) * 2 - 1;

    drawPoint(x1, y1);

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
}

void testFunc(void) {
    glClearColor(0, 0.8, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    for (int i = 0; i <= 400; i += 50) {
        drawLine(0, i, 300, 200);
    }

    glColor3f(0, 0, 1);
    for (int i = 0; i <= 600; i += 50) {
        drawLine(i, 0, 300, 200);
    }

    glColor3f(1, 1, 1);
    for (int i = 0; i <= 400; i += 50) {
        drawLine(600, i, 300, 200);
    }

    glColor3f(0, 0, 0);
    for (int i = 0; i <= 600; i += 50) {
        drawLine(i, 400, 300, 200);
    }
    
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(APP_WIDTH, APP_HEIGHT);
    glutCreateWindow("Bresenham");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 400);

    glutDisplayFunc(testFunc);

    glutMainLoop();
}
