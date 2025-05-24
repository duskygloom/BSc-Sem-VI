#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

int PRINT = 1;

int L, R, B, T;

typedef struct Vector {
    float x, y;
} vector_t;

vector_t P1, P2;

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
int getCode(vector_t p) {
    int code = 0;
    code = 2 * code + (p.y > T);
    code = 2 * code + (p.y < B);
    code = 2 * code + (p.x > R);
    code = 2 * code + (p.x < L);
    return code;
}

void drawClippingWindow() {
    /* draw line divisions */
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glColor3f(0.25, 0.25, 0.25);
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

void drawLine() {
    // glEnable(GL_LINE_STIPPLE);
    // glLineStipple(1, 0x00FF);
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_LINES);
    glVertex2i(P1.x, P1.y); glVertex2i(P2.x, P2.y);
    glEnd();
    // glDisable(GL_LINE_STIPPLE);
}

/**
 * @warning
 * If the code of p is 0, then it returns (0, 0). So, make
 * sure that p is not already inside clipping window.
 */
vector_t getIntersection(vector_t p) {
    int code = getCode(p);
    float slope = (P2.y - P1.y) / (P2.x - P1.x);
    if (code & 0b1000) { // top
        int x = (T - P1.y) / slope + P1.x;
        return (vector_t){x, T};
    } else if (code & 0b0100) { // bottom
        int x = (B - P1.y) / slope + P1.x;
        return (vector_t){x, B};
    } else if (code & 0b0010) { // right
        int y = slope * (R - P1.x) + P1.y;
        return (vector_t){R, y};
    } else if (code & 0b0001) { // left
        int y = slope * (L - P1.x) + P1.y;
        return (vector_t){L, y};
    }
    return (vector_t){0, 0};
}

typedef struct Line {
    vector_t start, end;
} line_t;

/**
 * @note
 * Returns the clipped line. If there is no clipped line,
 * returns (0, 0). Sets found = 1 if line is clipped else
 * sets found = 0.
 */
line_t cyrusBeck(vector_t start, vector_t end, int *found) {
    int startCode = getCode(start);
    int endCode = getCode(end);

    if (startCode == 0 && endCode == 0) {
        *found = 1;
        return (line_t){start, end};
    } else if ((startCode & endCode) != 0) {
        *found = 0;
        return (line_t){{0, 0}, {0, 0}};
    } else if (startCode == 0) {
        return cyrusBeck(start, getIntersection(end), found);
    } else {
        return cyrusBeck(getIntersection(start), end, found);
    }
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawClippingWindow();
    drawLine();

    int found = 0;
    line_t clippedLine = cyrusBeck(P1, P2, &found);

    /* display clipped line */
    if (found) {
        glColor3f(0.9, 0.2, 0.9);
        glBegin(GL_LINES);
        glVertex2f(clippedLine.start.x, clippedLine.start.y);
        glVertex2f(clippedLine.end.x, clippedLine.end.y);
        glEnd();
        glPointSize(4);
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        glVertex2f(clippedLine.start.x, clippedLine.start.y);
        glVertex2f(clippedLine.end.x, clippedLine.end.y);
        glEnd();
    }
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

void specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
        P1.y += 10; break;
        case GLUT_KEY_DOWN:
        P1.y -= 10; break;
        case GLUT_KEY_LEFT:
        P1.x -= 10; break;
        case GLUT_KEY_RIGHT:
        P1.x += 10; break;
    }
    glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        P2.y += 10; break;
        case 's':
        P2.y -= 10; break;
        case 'a':
        P2.x -= 10; break;
        case 'd':
        P2.x += 10; break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    /**
     * @note
     * This code illustrates Cohen-Sutherland line
     * clipping algorithm. It takes clipping window
     * and line end points from the user.
     * The user can also move the starting point using
     * A,W,S,D and the end point using arrow keys.
     */
    printf("Clipping window (LRBT): ");
    scanf("%d %d %d %d", &L, &R, &B, &T);

    printf("Point 1: ");
    scanf("%f %f", &P1.x, &P1.y);
    printf("Point 2: ");
    scanf("%f %f", &P2.x, &P2.y);

    printf("Use arrow keys to move point 1 and A,W,S,D keys to move point 2.\n");

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutCreateWindow("Cohen-Sutherland");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);

    glutMainLoop(); // loop
}
