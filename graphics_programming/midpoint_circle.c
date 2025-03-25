#include <stdio.h>
#include <GL/glut.h>

void drawCircle(int r, int cx, int cy) {
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

    glColor3f(0, 0, 0);
    glPointSize(2);
    drawCircle(200, 400, 300);

    glFlush();

    return;

    glBegin(GL_LINES);
    glVertex2d(0, -30);
    glVertex2d(0, 30);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-40, 0);
    glVertex2d(40, 0);
    glEnd();

    glPointSize(10);

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
    // gluOrtho2D(-40, 40, -30, 30);
    gluOrtho2D(0, 800, 0, 600);

    glutDisplayFunc(displayFunc);

    glutMainLoop();
}
