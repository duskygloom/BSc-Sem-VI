#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

int PRINT = 0;

int RX, RY, CX, CY;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

void drawEllipse(int rx, int ry, int cx, int cy) {
    const int RX_SQUARED = rx * rx;
    const int RY_SQUARED = ry * ry;
    
    int x = 0, y = ry;
    int p = RY_SQUARED - RX_SQUARED*ry + RX_SQUARED/4;

    glBegin(GL_POINTS);

    while (RY_SQUARED * x <= RX_SQUARED * y) {
        glVertex2d(cx + x, cy + y);
        glVertex2d(cx - x, cy + y);
        glVertex2d(cx + x, cy - y);
        glVertex2d(cx - x, cy - y);

        x += 1;
        if (p >= 0) {
            y -= 1;
            p -= 2 * RX_SQUARED * y;
        }
        p += RY_SQUARED * (1 + 2*x);
    }
    
    x = rx, y = 0;
    p = RX_SQUARED - rx * RY_SQUARED + RY_SQUARED / 4;
    
    while (RY_SQUARED * x > RX_SQUARED * y) {
        glBegin(GL_POINTS);
        glVertex2d(cx + x, cy + y);
        glVertex2d(cx - x, cy + y);
        glVertex2d(cx + x, cy - y);
        glVertex2d(cx - x, cy - y);
        glEnd();
        
        y += 1;
        if (p >= 0) {
            x -= 1;
            p -= 2 * RY_SQUARED * x;
        }
        p += RX_SQUARED * (1 + 2*y);
    }

    glEnd();
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glColor3f(1, 1, 1);
    drawEllipse(RX, RY, CX, CY);
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will draw a circle with horizontal radius RX,
     * vertical radius RY and center (CX, CY) using midpoint
     * circle algorithm.
     */
    printf("Radii (horizontal, vertical): ");
    scanf("%d %d", &RX, &RY);
    printf("Center: ");
    scanf("%d %d", &CX, &CY);

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Midpoint ellipse");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);

    glutMainLoop(); // loop
}
