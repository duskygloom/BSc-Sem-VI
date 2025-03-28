#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define APP_WIDTH 600
#define APP_HEIGHT 400

#define ROUND(x) ((int)(x + 0.5))

void drawLine(int x1, int y1, int x2, int y2) {
    double dx, dy;
    int steps;

    double slope = (double)(y2 - y1) / (x2 - x1);
    printf("Slope: %.4lf\n", slope);

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
        glVertex2d(ROUND(x), ROUND(y));
        glEnd();
        x += dx;
        y += dy;
    }
}

void displayFunc(void) {
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
    glutInit(&argc, argv); // init glut

    glutInitWindowSize(APP_WIDTH, APP_HEIGHT);
    glutCreateWindow("DDA"); // create window

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, APP_WIDTH, 0, APP_HEIGHT); // reference frame

    glutDisplayFunc(displayFunc); // display function

    glutMainLoop(); // loop
}
