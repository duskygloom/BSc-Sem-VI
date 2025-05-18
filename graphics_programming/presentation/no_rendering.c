#include "vector.h"

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

int PRINT = 1;

vector_t camera = {300, 500, 800};

/* Vertices */
const vector_t VA = {0, 0, 0};
const vector_t VB = {200, 0, 0};
const vector_t VC = {200, 0, 200};
const vector_t VD = {0, 0, 200};
const vector_t VE = {0, 200, 200};
const vector_t VF = {0, 200, 0};
const vector_t VG = {200, 200, 0};
const vector_t VH = {200, 200, 200};

void drawAxes(void) {
    glBegin(GL_LINES);

    glColor3f(1.0, 0.4, 0.4);
    glVertex3d(-1000, 0, 0); glVertex3d(1000, 0, 0);
    glColor3f(0.4, 1.0, 0.4);
    glVertex3d(0, -1000, 0); glVertex3d(0, 1000, 0);
    glColor3f(0.4, 0.2, 1.4);
    glVertex3d(0, 0, -1000); glVertex3d(0, 0, 1000);

    glEnd();
}

void display(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();

    glBegin(GL_QUADS); // 3 quadrilaterals

    glColor3f(0.8, 0.4, 0.2);

    /* FACE 1 */
    glVertex3i(VA.x, VA.y, VA.z);
    glVertex3i(VB.x, VB.y, VB.z);
    glVertex3i(VC.x, VC.y, VC.z);
    glVertex3i(VD.x, VD.y, VD.z);

    /* FACE 2 */
    glVertex3i(VB.x, VB.y, VB.z);
    glVertex3i(VA.x, VA.y, VA.z);
    glVertex3i(VF.x, VF.y, VF.z);
    glVertex3i(VG.x, VG.y, VG.z);

    /* FACE 3 */
    glVertex3i(VF.x, VF.y, VF.z);
    glVertex3i(VE.x, VE.y, VE.z);
    glVertex3i(VH.x, VH.y, VH.z);
    glVertex3i(VG.x, VG.y, VG.z);

    /* FACE 4 */
    glVertex3i(VE.x, VE.y, VE.z);
    glVertex3i(VD.x, VD.y, VD.z);
    glVertex3i(VC.x, VC.y, VC.z);
    glVertex3i(VH.x, VH.y, VH.z);

    /* FACE 5 */
    glVertex3i(VB.x, VB.y, VB.z);
    glVertex3i(VG.x, VG.y, VG.z);
    glVertex3i(VH.x, VH.y, VH.z);
    glVertex3i(VC.x, VC.y, VC.z);

    /* FACE 6 */
    glVertex3i(VA.x, VA.y, VA.z);
    glVertex3i(VD.x, VD.y, VD.z);
    glVertex3i(VE.x, VE.y, VE.z);
    glVertex3i(VF.x, VF.y, VF.z);
    
    glEnd();

    glutSwapBuffers();

    PRINT = 0;
}

/**
 * @brief
 * Keyboard controls for controlling world rotation.
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        /* rotation */
        case '1':
        glRotatef(10, 1, 0, 0); break;
        case '2':
        glRotatef(10, 0, 1, 0); break;
        case '3':
        glRotatef(10, 0, 0, 1); break;
        case '4':
        glRotatef(10, 1, 1, 0); break;
        case '5':
        glRotatef(10, 0, 1, 1); break;
        case '6':
        glRotatef(10, 1, 0, 1); break;
        /* translation */
        case 'a':
        glTranslatef(-10, 0, 0); break;
        case 'd':
        glTranslatef(10, 0, 0); break;
        case 'w':
        glTranslatef(0, 10, 0); break;
        case 's':
        glTranslatef(0, -10, 0); break;
        case 'q':
        glTranslatef(0, 0, 10); break;
        case 'e':
        glTranslatef(0, 0, -10); break;
        /* scaling */
        case '=':
        glScalef(1.2, 1.2, 1.2); break;
        case '-':
        glScalef(0.8, 0.8, 0.8); break;
    }
    glutPostRedisplay();
}

/**
 * @brief
 * What to do if window size changes?
 */
void reshape(int width, int height) {
    int newHeight, newWidth, top, left;
    /* force 4:3 aspect ratio */
    const float aspectRatio = 4.0 / 3;
    if (width >= height*aspectRatio) {
        // decrease width and center horizontally
        newHeight = height;
        newWidth = height*aspectRatio;
        top = 0;
        left = (width - newWidth) / 2;
    } else {
        // decrease height and center vertically
        newWidth = width;
        newHeight = width/aspectRatio;
        left = 0;
        top = (height - newHeight) / 2;
    }
    glViewport(left, top, newWidth, newHeight);
    /* preserve projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, aspectRatio, 1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.x, camera.y, camera.z,
              0, 0, 0,
              0, 1, 0);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Without rendering");

    /* Set 3D viewing attributes. */
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 4.0/3, 1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.x, camera.y, camera.z,
              0, 0, 0,
              0, 1, 0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
