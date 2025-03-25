#include <stdio.h>

#include <GL/glut.h>

#define APP_WIDTH 600
#define APP_HEIGHT 400

void drawFinland(void) {
    glClearColor(1, 1, 1, 1);                                           // background color
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.01, 0.01, 0.95);                                        // line color
    glLineWidth(60);                                                    // line width

    glBegin(GL_LINES);                                                  // vertical line
    glVertex2i(APP_WIDTH / 3, 0);
    glVertex2i(APP_WIDTH / 3, APP_HEIGHT);
    glEnd();

    glBegin(GL_LINES);                                                  // horizontal line
    glVertex2i(0, APP_HEIGHT / 2);
    glVertex2i(APP_WIDTH, APP_HEIGHT / 2);
    glEnd();

    glFlush();                                                          // finalize
}

void drawSweden(void) {
    glClearColor(0.4, 0.2, 0.8, 1);                                     // background colour
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.8, 0.9, 0);                                             // line colour
    glLineWidth(60);                                                    // line width

    glBegin(GL_LINES);                                                  // vertical line
    glVertex2i(APP_WIDTH / 3, 0);
    glVertex2i(APP_WIDTH / 3, APP_HEIGHT);
    glEnd();

    glBegin(GL_LINES);                                                  // horizontal line
    glVertex2i(0, APP_HEIGHT / 2);
    glVertex2i(APP_WIDTH, APP_HEIGHT / 2);
    glEnd();

    glFlush();                                                          // finalize
}

void createWindow(const char *title) {
    glutInitWindowSize(APP_WIDTH, APP_HEIGHT);                          // window size
    glutCreateWindow(title);                                            // create window with title
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 400);                                         // reference frame
}

int main(int argc, char **argv) {
    int option;
    printf("0. Quit.\n\n");
    printf("1. Finland\n");
    printf("2. Sweden\n");
    printf("Select country: ");
    scanf("%d", &option);
    switch (option) {
    case 0:
        break;
    case 1:
        glutInit(&argc, argv);
        createWindow("Finland");
        glutDisplayFunc(drawFinland);
        break;
    case 2:
        glutInit(&argc, argv);
        createWindow("Sweden");
        glutDisplayFunc(drawSweden);
        break;
    default:
        printf("Invalid option: %d\n", option);
        break;
    }
    glutMainLoop();
}