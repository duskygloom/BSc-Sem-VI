#include <stdio.h>
#include <GL/glut.h>

#define BIG_CIRCLE
#define PRINT_TABLE

void drawCircle(int r, int cx, int cy) {
    #ifndef BIG_CIRCLE
    r *= 10;
    cx *= 10;
    cy *= 10;
    #endif

    int x = 0, y = r;

    int p = 1 - r;

    int k = 0;

    while (x <= y) {
        glBegin(GL_POINTS);
        glVertex2d(cx + x, cy + y);
        glVertex2d(cx + y, cy + x);
        glVertex2d(cx - x, cy + y);
        glVertex2d(cx - y, cy + x);
        glVertex2d(cx + x, cy - y);
        glVertex2d(cx + y, cy - x);
        glVertex2d(cx - x, cy - y);
        glVertex2d(cx - y, cy - x);
        glEnd();
        
        #ifdef PRINT_TABLE
        printf("%d\t", k++);
        printf("%d\t", p);
        #endif
        x += 1;
        if (p >= 0) {
            y -= 1;
            p -= 2*y;
        }
        p += 2*x + 1;
        #ifdef PRINT_TABLE
        printf("(%d\t%d)\n", x, y);
        #endif
    }
}

void displayFunc(void) {
    glClearColor(1, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    #ifdef BIG_CIRCLE
    glVertex2d(0, -30);
    glVertex2d(0, 30);
    #else
    glVertex2d(0, -300);
    glVertex2d(0, 300);
    #endif
    glEnd();

    glBegin(GL_LINES);
    #ifdef BIG_CIRCLE
    glVertex2d(-40, 0);
    glVertex2d(40, 0);
    #else
    glVertex2d(-400, 0);
    glVertex2d(400, 0);
    #endif
    glEnd();

    #ifdef PRINT_TABLE
    printf("Begins:\n");
    #endif
    glColor3f(0, 0, 0);
    drawCircle(16, 3, 4);

    glColor3f(0, 0, 1);
    drawCircle(8, 7, 7);

    glColor3f(0, 1, 0);
    drawCircle(10, 10, 12);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("Midpoint circle");

    glMatrixMode(GL_PROJECTION);
    #ifdef BIG_CIRCLE
    gluOrtho2D(-40, 40, -30, 30);
    glPointSize(10);
    #else
    gluOrtho2D(-400, 400, -300, 300);
    glPointSize(1);
    #endif

    glutDisplayFunc(displayFunc);

    glutMainLoop();
}
