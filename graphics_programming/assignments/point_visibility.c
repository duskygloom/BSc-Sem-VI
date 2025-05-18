#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 400

int PRINT = 1;

int X, Y;

void drawAxes() {
    glBegin(GL_LINES);
    glColor3ub(255, 100, 100);
    glVertex2i(-WIDTH/2, 0); glVertex2i(WIDTH/2, 0);
    glColor3ub(100, 255, 100);
    glVertex2i(0, -HEIGHT/2); glVertex2i(0, HEIGHT/2);
    glEnd();
}

int isVisible(int x, int y) {
    return x <= WIDTH/2 && x >= -WIDTH/2 && y <= HEIGHT/2 && y >= -HEIGHT/2;
}

void displayFunc(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glColor3f(1, 1, 1);
    if (isVisible(X, Y)) {
        if (PRINT) printf("Point is visible.\n");
        glBegin(GL_POINTS);
        glVertex2i(X, Y);
        glEnd();
    } else {
        if (PRINT) printf("Point is not visible.\n");
    }
    
    glutSwapBuffers(); // somehow works like flush
    PRINT = 0; // print only once
}

int main(int argc, char **argv) {
    /**
     * @note
     * Code will take a point as input from the user
     * and check if it is visible or not.
     */
    printf("Point: ");
    scanf("%d %d", &X, &Y);

    glutInit(&argc, argv);

    glutInitWindowSize(WIDTH, HEIGHT);
    // RGB and double buffer (whatever that means)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutCreateWindow("Point visibility");

    glMatrixMode(GL_PROJECTION);
    // window coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    glutDisplayFunc(displayFunc);

    glutMainLoop(); // loop
}
