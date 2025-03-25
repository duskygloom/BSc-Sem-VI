#include <GL/glut.h>

#include <stdio.h>

#define APP_WIDTH 600
#define APP_HEIGHT 400

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;

    if (dx == 0) {
        if (y1 > y2) {
            int temp = y1; y1 = y2; y2 = temp;
            temp = x1; x1 = x2; x2 = temp;
            dx = -dx; dy = -dy;
        }
        while (y1 <= y2) {
            glBegin(GL_POINTS);
            glVertex2d(x1, y1);
            glEnd();
            y1 += 1;
        }
        return;
    }

    int slope = dy / dx;

    if (slope > 1 || slope < -1) { // y changes faster
        // swap coordinates in increasing order of y
        if (y2 < y1) {
            int temp = y1; y1 = y2; y2 = temp;
            temp = x1; x1 = x2; x2 = temp;
            dx = -dx; dy = -dy;
        }
        // initial parameter
        int p = 2*dx - dy;
        int xincr = dx < 0 ? -1 : 1;
        // other points
        while (y1 <= y2) {
            glBegin(GL_POINTS);
            glVertex2d(x1, y1);
            glEnd();

            y1 += 1;
            if (p >= 0) {
                x1 += xincr;
                p -= 2*dy;
            }
            p += 2*dx;
        }
    } else { // x changes faster or equally
        // swap coordinates in increasing order of x
        if (x2 < x1) {
            int temp = y1; y1 = y2; y2 = temp;
            temp = x1; x1 = x2; x2 = temp;
            dx = -dx; dy = -dy;
        }
        // initial parameter
        int p = 2*dy - dx;
        int yincr = dy < 0 ? -1 : 1;
        // other points
        while (x1 <= x2) {
            p += 2*dy;
            glBegin(GL_POINTS);
            glVertex2d(x1, y1);
            glEnd();

            x1 += 1;
            if (p >= 0) {
                y1 += yincr;
                p -= 2*dx;
            }
        }
    }
}

void displayFunc(void) {
    glClearColor(0, 0.8, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // glColor3f(1, 0, 0);
    // for (int i = 50; i < APP_HEIGHT; i += 50) {
    //     drawLine(10, i, 300, 200);
    // }

    // glColor3f(0, 0, 1);
    // for (int i = 50; i < APP_WIDTH; i += 50) {
    //     drawLine(i, 10, 300, 200);
    // }

    // glColor3f(1, 1, 1);
    // for (int i = 50; i < APP_HEIGHT; i += 50) {
    //     drawLine(590, i, 300, 200);
    // }

    // glColor3f(0, 0, 0);
    // for (int i = 50; i < APP_WIDTH; i += 50) {
    //     drawLine(i, 390, 300, 200);
    // }

    glPointSize(10);

    glColor3f(1, 1, 1);
    drawLine(5, 5, 10, 15);

    glColor3f(0, 0, 0);
    drawLine(15, 10, 5, 5);

    glColor3f(0, 0, 1);
    drawLine(15, 5, 5, 10);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(APP_WIDTH, APP_HEIGHT);
    glutCreateWindow("Bresenham");

    glMatrixMode(GL_PROJECTION);
    // gluOrtho2D(0, 600, 0, 400);
    gluOrtho2D(0, 60, 0, 40);

    glutDisplayFunc(displayFunc);

    glutMainLoop();
}
