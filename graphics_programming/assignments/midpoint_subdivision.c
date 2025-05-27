#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 400

#define MINIMUM_DIFFERENCE 1

/**
 * @brief
 * Stores coordinates of a point in a 2D
 * cartesian plane.
 */
typedef struct {
    float x, y;
} Point;

/**
 * @brief
 * Stores boundaries of a rectangular
 * window.
 */
typedef struct {
    float left, right, bottom, top;
} Rect;

Point P1, P2;
Rect clip;

void display(void);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);

void main(int argc, char **argv) {
    printf("Clipping window (LRBT): ");
    scanf("%f %f %f %f", &(clip.left), &(clip.right),
                         &(clip.bottom), &(clip.top));
    printf("Point 1 (x, y): ");
    scanf("%f %f", &(P1.x), &(P1.y));
    printf("Point 2 (x, y): ");
    scanf("%f %f", &(P2.x), &(P2.y));
    printf("Press A,W,S,D to move the first point ");
    printf("and arrow keys to move the second point.\n");

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Midpoint subdivision");

    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    P1 = (Point){-200, -50};
    P2 = (Point){50, -150};
    clip = (Rect){-150, 200, -100, 100};

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
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
    glVertex2f(P1.x, P1.y);
    glVertex2f(P2.x, P2.y);
    glEnd();
}

void drawWindow(void) {
    glLineWidth(1);
    glColor3f(0.75, 0.75, 0.25);
    glBegin(GL_LINES);
    glVertex2f(clip.left, clip.bottom);
    glVertex2f(clip.left, clip.top);
    glVertex2f(clip.left, clip.top);
    glVertex2f(clip.right, clip.top);
    glVertex2f(clip.right, clip.top);
    glVertex2f(clip.right, clip.bottom);
    glVertex2f(clip.right, clip.bottom);
    glVertex2f(clip.left, clip.bottom);
    glEnd();
}

int pointCode(Point p, Rect window) {
    int code = 0;
    code = 2*code + (p.y > window.top);
    code = 2*code + (p.y < window.bottom);
    code = 2*code + (p.x > window.right);
    code = 2*code + (p.x < window.left);
    return code;
}

float distanceBetween(Point a, Point b) {
    float dx = (a.x - b.x) * (a.x - b.x);
    float dy = (a.y - b.y) * (a.y - b.y);
    return sqrtf(dx + dy);
}

void midpointClipping(Point start, Point end, Rect window) {
    if (distanceBetween(start, end) < 1) {
        // limit reached
        return;
    }

    int startCode = pointCode(start, window);
    int endCode = pointCode(end, window);

    if (startCode == 0 && endCode == 0) {
        // trivially visible
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor3f(0.4, 0.2, 0.75);
        glVertex2f(start.x, start.y); glVertex2f(end.x, end.y);
        glEnd();
    } else if ((startCode & endCode) != 0) {
        // trivially invisible
        return;
    } else {
        float midx = (start.x + end.x) / 2;
        float midy = (start.y + end.y) / 2;
        Point midpoint = (Point){midx, midy};
        midpointClipping(start, midpoint, window);
        midpointClipping(midpoint, end, window);
    }
}

void display(void) {
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPoints();
    drawWindow();

    midpointClipping(P1, P2, clip);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        P1.x -= 5; break;
        case 'd':
        P1.x += 5; break;
        case 's':
        P1.y -= 5; break;
        case 'w':
        P1.y += 5; break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
        P2.x -= 5; break;
        case GLUT_KEY_RIGHT:
        P2.x += 5; break;
        case GLUT_KEY_DOWN:
        P2.y -= 5; break;
        case GLUT_KEY_UP:
        P2.y += 5; break;
    }
    glutPostRedisplay();
}
