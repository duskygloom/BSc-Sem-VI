#include "vector.h"

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

int PRINT = 1;

const vector_t camera = {300, 500, 800};
const vector_t boxColour = {0.8, 0.4, 0.2};

/* Lights */

typedef struct Light {
    vector_t position;
    float brightness;
} light_t;

const light_t lights[] = {
    {{-80,    300,    300},        1.0},
    {{-500,   -400,   -300},       0.4},
    {{600,    600,    600},        0.8},
    {{100,    100,   -100},        0.6},
};

/* Vertices */
const vector_t VA = {0, 0, 0};
const vector_t VB = {0, 200, 0};
const vector_t VC = {200, 200, 0};
const vector_t VD = {200, 0, 0};
const vector_t VE = {200, 0, 200};
const vector_t VF = {0, 0, 200};
const vector_t VG = {0, 200, 200};
const vector_t VH = {200, 200, 200};

/* Face normals 
   Could be calculated using cross product,
   but hardcoding for simplicity. */
const vector_t N1 = {0, 0, -1};
const vector_t N2 = {-1, 0, 0};
const vector_t N3 = {0, 0, 1};
const vector_t N4 = {1, 0, 0};
const vector_t N5 = {0, 1, 0};
const vector_t N6 = {0, -1, 0};

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

void drawLights(void) {
    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 1; i < sizeof(lights) / sizeof(light_t); ++i)
        glVertex3i(lights[i].position.x, lights[i].position.y, lights[i].position.z);
    glEnd();
}

float clamp(float f) {
    return f > 1.0 ? 1.0 : (f < 0.0 ? 0.0 : f);
}

void changeColorAndIntensity(vector_t color, float specularI, float nonSpecularI) {
    vector_t finalColor = vectorSum(vectorScale(color, nonSpecularI),
                                    vectorScale((vector_t){1.0, 1.0, 1.0}, specularI));
    glColor3f(clamp(finalColor.x),
              clamp(finalColor.y),
              clamp(finalColor.z));
}

vector_t getQuadCenter(vector_t A, vector_t B, vector_t C, vector_t D) {
    vector_t total = vectorSum(A, vectorSum(B, vectorSum(C, D)));
    return vectorScale(total, 0.25);
}

/* Intensity calculation functions */

float getAmbientI() {
    const float ia = 0.5;
    const float ka = 0.4;
    return ia * ka;
}

/**
 * @param light
 * Light position.
 * @param point
 * The point to be illuminated.
 * @param normal
 * Normal vector at the point P.
 */
float getDiffusedI(vector_t light, float brightness, vector_t point, vector_t normal) {
    const float il = 1.0;
    float kd = brightness;
    vector_t lightVector = vectorSum(light, vectorScale(point, -1));
    float dotProduct = vectorDot(lightVector, normal);
    if (dotProduct <= 0) return 0;
    float magnitude = vectorMagnitude(lightVector) * vectorMagnitude(normal);
    return il * kd * (dotProduct / magnitude);
}

float getSpecularI(vector_t light, vector_t point, vector_t normal) {
    const float il = 0.6;
    const float ks = 0.4;
    const float n = 8.0;
    vector_t lightVector = vectorSum(light, vectorScale(point, -1));
    vector_t cameraVector = vectorSum(camera, vectorScale(point, -1));

    vector_t halfwayVector = vectorSum(lightVector, cameraVector);
    float dotProduct = vectorDot(normal, halfwayVector);
    if (dotProduct <= 0) return 0;
    float magnitude = vectorMagnitude(normal) * vectorMagnitude(halfwayVector);
    return il * ks * powf(dotProduct / magnitude, n);
}

float getTotalSpecularI(vector_t point, vector_t normal) {
    float specular = 0;
    for (int i = 0; i < sizeof(lights) / sizeof(light_t); ++i) {
        specular += getSpecularI(lights[i].position, point, normal);
    }
    if (PRINT) printf("Specular: %.4f\n", specular);
    return clamp(specular);
}

float getTotalDiffusedI(vector_t point, vector_t normal) {
    float diffused = 0;
    for (int i = 0; i < sizeof(lights) / sizeof(light_t); ++i) {
        diffused += getDiffusedI(lights[i].position,
                                         lights[i].brightness, point, normal);
    }
    if (PRINT) printf("Diffused: %.4f\n", diffused);
    return clamp(diffused);
}

void display(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    drawLights();

    glBegin(GL_QUADS);

    /* FACE 1 */
    vector_t faceCenter1 = getQuadCenter(VA, VB, VC, VD);
    float specularI1 = getTotalSpecularI(faceCenter1, N1);
    float nonSpecularI1 = getAmbientI() + getTotalDiffusedI(faceCenter1, N1);
    changeColorAndIntensity(boxColour, specularI1, nonSpecularI1);
    glVertex3i(VA.x, VA.y, VA.z);
    glVertex3i(VB.x, VB.y, VB.z);
    glVertex3i(VC.x, VC.y, VC.z);
    glVertex3i(VD.x, VD.y, VD.z);

    /* FACE 2 */
    vector_t faceCenter2 = getQuadCenter(VB, VA, VF, VG);
    float specularI2 = getTotalSpecularI(faceCenter2, N2);
    float nonSpecularI2 = getAmbientI() + getTotalDiffusedI(faceCenter2, N2);
    changeColorAndIntensity(boxColour, specularI2, nonSpecularI2);
    glVertex3i(VB.x, VB.y, VB.z);
    glVertex3i(VA.x, VA.y, VA.z);
    glVertex3i(VF.x, VF.y, VF.z);
    glVertex3i(VG.x, VG.y, VG.z);

    /* FACE 3 */
    vector_t faceCenter3 = getQuadCenter(VF, VE, VH, VG);
    float specularI3 = getTotalSpecularI(faceCenter3, N3);
    float nonSpecularI3 = getAmbientI() + getTotalDiffusedI(faceCenter3, N3);
    changeColorAndIntensity(boxColour, specularI3, nonSpecularI3);
    glVertex3i(VF.x, VF.y, VF.z);
    glVertex3i(VE.x, VE.y, VE.z);
    glVertex3i(VH.x, VH.y, VH.z);
    glVertex3i(VG.x, VG.y, VG.z);

    /* FACE 4 */
    vector_t faceCenter4 = getQuadCenter(VE, VD, VC, VH);
    float specularI4 = getTotalSpecularI(faceCenter4, N4);
    float nonSpecularI4 = getAmbientI() + getTotalDiffusedI(faceCenter4, N4);
    changeColorAndIntensity(boxColour, specularI4, nonSpecularI4);
    glVertex3i(VE.x, VE.y, VE.z);
    glVertex3i(VD.x, VD.y, VD.z);
    glVertex3i(VC.x, VC.y, VC.z);
    glVertex3i(VH.x, VH.y, VH.z);

    /* FACE 5 */
    vector_t faceCenter5 = getQuadCenter(VB, VG, VH, VC);
    float specularI5 = getTotalSpecularI(faceCenter5, N5);
    float nonSpecularI5 = getAmbientI() + getTotalDiffusedI(faceCenter5, N5);
    changeColorAndIntensity(boxColour, specularI5, nonSpecularI5);
    glVertex3i(VB.x, VB.y, VB.z);
    glVertex3i(VG.x, VG.y, VG.z);
    glVertex3i(VH.x, VH.y, VH.z);
    glVertex3i(VC.x, VC.y, VC.z);

    /* FACE 6 */
    vector_t faceCenter6 = getQuadCenter(VA, VD, VE, VF);
    float specularI6 = getTotalSpecularI(faceCenter6, N6);
    float nonSpecularI6 = getAmbientI() + getTotalDiffusedI(faceCenter6, N6);
    changeColorAndIntensity(boxColour, specularI6, nonSpecularI6);
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
    glutCreateWindow("With flat shading");

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
