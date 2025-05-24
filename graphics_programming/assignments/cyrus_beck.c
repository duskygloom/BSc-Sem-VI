#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define WIDTH 600
#define HEIGHT 400

int PRINT = 1;

vector_t P1, P2;

int polygonSize;
vector_t *vertices;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

void drawClippingWindow() {
    /* draw clipping window */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.25, 0.25, 0.25);
    glColor3f(0.9, 0.2, 0.9);
    glBegin(GL_POLYGON);
    for (int i = 0; i < polygonSize; ++i)
        glVertex2f(vertices[i].x, vertices[i].y);
    glVertex2f(vertices[0].x, vertices[0].y); // back to first point
    glEnd();
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
 * @note
 * Parameter is the value of t in a parametric
 * equation. This struct stores the float value
 * of t and isLower a boolean value storing if
 * the t belongs to t_L or not.
 */
typedef struct Parameter {
    float value;
    int isLower;
} parameter_t;

/**
 * @brief
 * Finds the intersection at edge ab.
 * start and end are the start and end points of the
 * line to be clipped respectively.
 * 
 * @note
 * If there is no intersection point, then parameter
 * .isLower is -1.
 * 
 * @returns
 * Parametric point where the line intersects the edge.
 */
parameter_t getParameter(vector_t a, vector_t b, vector_t start, vector_t end) {
    vector_t f = a;
    vector_t w = vectorDiff(start, f);
    vector_t D = vectorDiff(end, start);
    vector_t edge = vectorDiff(b, a);
    vector_t n = normalVector(edge);
    float numerator = -vectorDot(w, n);
    float denominator = vectorDot(D, n);
    if (denominator == 0) return (parameter_t){0, -1};
    return (parameter_t){numerator/denominator, denominator < 0};
}

/**
 * @note
 * Calculates Tvalues where the line intersects each edge
 * and stores it in Tvalues array. So make sure Tvalues
 * can store polygonSize float values.
 */
void cyrusBeck(vector_t start, vector_t end, parameter_t *Tvalues) {
    for (int i = 0; i < polygonSize; ++i) {
        parameter_t t = getParameter(vertices[i], 
            vertices[(i+1) % polygonSize],  start, end);
        Tvalues[i] = t;
    }
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawClippingWindow();
    drawLine();

    parameter_t *Tvalues = calloc(polygonSize, sizeof(parameter_t));
    cyrusBeck(P1, P2, Tvalues);

    /* find greatest lower bound and least upper bound */
    float start = -1.0, end = 1.0;

    /* display clipped line */
    for (int i = 0; i < polygonSize; ++i) {
        /* find start and end point */
        if (Tvalues[i].isLower == 1 && Tvalues[i].value > start)
            start = Tvalues[i].value;
        if (Tvalues[i].isLower == 0 && Tvalues[i].value < end)
            end = Tvalues[i].value; 
        
        glPointSize(4);
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        vector_t intersection = vectorSum(P1, vectorScale(vectorDiff(P2, P1), Tvalues[i].value));
        glVertex2f(intersection.x, intersection.y);
        glEnd();
    }

    /* draw clipped line */
    if (start <= end) {
        if (start < 0) start = 0;
        if (end > 1) end = 1;
        glColor3f(0.9, 0.9, 0.2);
        glBegin(GL_LINES);
        vector_t startPoint = vectorSum(P1, vectorScale(vectorDiff(P2, P1), start));
        glVertex2f(startPoint.x, startPoint.y);
        vector_t endPoint = vectorSum(P1, vectorScale(vectorDiff(P2, P1), end));
        glVertex2f(endPoint.x, endPoint.y);
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
     * This code illustrates Cyrus-Beck line clipping
     * algorithm for irregular convex windows.
     * The user can also move the starting point using
     * A,W,S,D and the end point using arrow keys.
     */
    printf("Number of vertices in the clipping window: ");
    scanf("%d", &polygonSize);
    vertices = calloc(polygonSize, sizeof(vector_t));
    printf("Enter vertices in clockwise order (very important!)\n");
    for (int i = 0; i < polygonSize; ++i) {
        printf("Vertex %d (x, y): ", i+1);
        scanf("%f %f", &(vertices[i].x), &(vertices[i].y));
    }

    printf("Point 1 (x, y): ");
    scanf("%f %f", &(P1.x), &(P1.y));
    printf("Point 2 (x, y): ");
    scanf("%f %f", &(P2.x), &(P2.y));

    printf("Use arrow keys to move point 1 and A,W,S,D keys to move point 2.\n");

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutCreateWindow("Cyrus-Beck");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);

    glutMainLoop(); // loop
}
