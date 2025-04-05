#include <stdio.h>
#include <GL/glut.h>

#define BIG_PIXELS
#define PRINT_TABLE

void drawEllipse(int rx, int ry, int cx, int cy) {
    #ifndef BIG_PIXELS
    rx *= 10;
    ry *= 10;
    cx *= 10;
    cy *= 10;
    #endif

    const int RX_SQUARED = rx * rx;
    const int RY_SQUARED = ry * ry;
    
    int x = 0, y = ry;
    int p = RY_SQUARED - RX_SQUARED*ry + RX_SQUARED/4;

    #ifdef PRINT_TABLE
    printf("First half\n");
    int k = 0;
    #endif

    while (RY_SQUARED * x <= RX_SQUARED * y) {
        glBegin(GL_POINTS);
        glVertex2d(cx + x, cy + y);
        glVertex2d(cx - x, cy + y);
        glVertex2d(cx + x, cy - y);
        glVertex2d(cx - x, cy - y);
        glEnd();
        
        #ifdef PRINT_TABLE
        printf("%d\t", k++);
        printf("%d\t", p);
        #endif

        x += 1;
        if (p >= 0) {
            y -= 1;
            p -= 2 * RX_SQUARED * y;
        }
        p += RY_SQUARED * (1 + 2*x);
        
        #ifdef PRINT_TABLE
        printf("(%d\t%d)\n", x, y);
        #endif
    }
    
    x = rx, y = 0;
    p = RX_SQUARED - rx * RY_SQUARED + RY_SQUARED / 4;
    
    #ifdef PRINT_TABLE
    printf("Second half\n");
    k = 0;
    #endif

    while (RY_SQUARED * x > RX_SQUARED * y) {
        glBegin(GL_POINTS);
        glVertex2d(cx + x, cy + y);
        glVertex2d(cx - x, cy + y);
        glVertex2d(cx + x, cy - y);
        glVertex2d(cx - x, cy - y);
        glEnd();
        
        #ifdef PRINT_TABLE
        printf("%d\t", k++);
        printf("%d\t", p);
        #endif

        y += 1;
        if (p >= 0) {
            x -= 1;
            p -= 2 * RY_SQUARED * x;
        }
        p += RX_SQUARED * (1 + 2*y);
        
        #ifdef PRINT_TABLE
        printf("(%d\t%d)\n", x, y);
        #endif
    }
}

void displayFunc(void) {
    glClearColor(1, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    #ifdef BIG_PIXELS
    glVertex2d(0, -30);
    glVertex2d(0, 30);
    #else
    glVertex2d(0, -300);
    glVertex2d(0, 300);
    #endif
    glEnd();

    glBegin(GL_LINES);
    #ifdef BIG_PIXELS
    glVertex2d(-40, 0);
    glVertex2d(40, 0);
    #else
    glVertex2d(-400, 0);
    glVertex2d(400, 0);
    #endif
    glEnd();

    glColor3f(0, 0, 0);
    drawEllipse(8, 6, 3, 4);

    glColor3f(0, 0, 1);
    drawEllipse(8, 10, 7, 7);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("Midpoint ellipse");

    glMatrixMode(GL_PROJECTION);
    #ifdef BIG_PIXELS
    gluOrtho2D(-40, 40, -30, 30);
    glPointSize(10);
    #else
    gluOrtho2D(-400, 400, -300, 300);
    glPointSize(1);
    #endif

    glutDisplayFunc(displayFunc);

    glutMainLoop();
}
