#include <stdio.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 400

typedef struct {
    float x, y;
} Point;

Point P1, P2;

void display(void);

void main(int argc, char **argv) {
    printf("Point 1 (x, y): ");
    scanf("%f %f", &(P1.x), &(P1.y));
    printf("Point 2 (x, y): ");
    scanf("%f %f", &(P2.x), &(P2.y));

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Line Drawing - DDA");

    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

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
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    float xincr = b.x > a.x ? 1 : -1;
    float yincr = b.y > a.y ? 1 : -1;

    float slope = (b.y - a.y) / (b.x - a.x);

    glPointSize(1);
    glBegin(GL_POINTS);
    if (a.x == b.x) {
        int steps = dy;
        for (int i = 0; i <= steps; ++i) {
            glVertex2i(a.x, a.y);
            a.y += yincr;
        }
    } else if (dx > dy) {
        int steps = dx;
        for (int i = 0; i <= steps; ++i) {
            glVertex2i(a.x, a.y);
            a.x += xincr;
            a.y += xincr * slope;
        }
    } else {
        int steps = dy;
        for (int i = 0; i <= steps; ++i) {
            glVertex2i(a.x, a.y);
            a.x += yincr / slope;
            a.y += yincr;
        }
    }
    glEnd();
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
