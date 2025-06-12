#include <stdio.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 400

typedef struct {
    int x, y;
} Point;

Point P1, P2;

void display(void);

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Line Drawing - Bresenham");

    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    P2 = (Point){50, 50};
    P1 = (Point){150, 100};
    glutDisplayFunc(display);
    glutMainLoop();
}

void drawAxes(void) {
    glBegin(GL_LINES);
    glColor3f(0.9, 0.2, 0.4);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3f(0.2, 0.9, 0.4);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

void drawPoints(void) {
    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(P1.x, P1.y);
    glVertex2i(P2.x, P2.y);
    glEnd();
}

void drawLine(Point a, Point b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    int xincr = b.x > a.x ? 1 : -1;
    int yincr = b.y > a.y ? 1 : -1;

    if (abs(dx) > abs(dy)) {
        int p = dx*yincr - 2*dy*xincr;
        int steps = abs(dx);
        glPointSize(1);
        glBegin(GL_POINTS);
        for (int i = 0; i <= steps; ++i) {
            glVertex2i(a.x, a.y);
            p -= 2*dy*xincr;
            a.x += xincr;
            if (p <= 0)  {
                p += 2*dx*yincr;
                a.y += yincr;
            }
        }
        glEnd();
    } else {
        int p = dy*xincr - 2*dx*yincr;
        int steps = abs(dy);
        glPointSize(1);
        glBegin(GL_POINTS);
        for (int i = 0; i <= steps; ++i) {
            glVertex2i(a.x, a.y);
            p -= 2*dx*yincr;
            a.y += yincr;
            if (p <= 0) {
                p += 2*dy*xincr;
                a.x += xincr;
            }
        }
        glEnd();
    }
}

void display(void) {
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPoints();

    glColor3f(0.25, 0.75, 0.75);
    drawLine(P1, P2);

    glFlush();
}
