#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

int PRINT = 0;

int R, CX, CY;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

void drawCircle(int r, int cx, int cy) {
    int x = 0, y = r;
    int p = 1 - r;

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
        
        x += 1;
        if (p >= 0) {
            y -= 1;
            p -= 2*y;
        }
        p += 2*x + 1;
    }
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glColor3f(1, 1, 1);
    drawCircle(R, CX, CY);
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will draw a circle of radius R and center (CX, CY)
     * using midpoint circle algorithm.
     */
    printf("Radius: ");
    scanf("%d", &R);
    printf("Center: ");
    scanf("%d %d", &CX, &CY);

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Midpoint circle");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);

    glutMainLoop(); // loop
}
