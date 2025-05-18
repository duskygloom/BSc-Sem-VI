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
    for (int i = 0; i < sizeof(lights) / sizeof(light_t); ++i)
        glVertex3i(lights[i].position.x, lights[i].position.y, lights[i].position.z);
    glEnd();
}

float clamp(float f) {
    return f > 1.0 ? 1.0 : (f < 0.0 ? 0.0 : f);
}

void changeColorAndIntensity(vector_t color, float specularI,
                             float nonSpecularI) {
    vector_t finalColor = vectorSum(vectorScale(color, nonSpecularI),
                               vectorScale((vector_t){1.0, 1.0, 1.0}, specularI));
    glColor3f(clamp(finalColor.x),
              clamp(finalColor.y),
              clamp(finalColor.z));
}

/* Intensity calculation */

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
    const float ks = 0.6;
    const float n = 10.0;
    vector_t lightVector = vectorSum(light, vectorScale(point, -1));
    vector_t cameraVector = vectorSum(camera, vectorScale(point, -1));

    vector_t halfwayVector = vectorSum(lightVector, cameraVector);
    float dotProduct = vectorDot(normal, halfwayVector);
    if (dotProduct <= 0) return 0;
    float magnitude = vectorMagnitude(normal) * vectorMagnitude(halfwayVector);
    return il * ks * powf(dotProduct / magnitude, n);
}

/**
 * @brief
 * Calculates the total specular reflection intensity at a point
 * from all light sources.
 */
float getTotalSpecularI(vector_t point, vector_t normal) {
    float specular = 0;
    for (int i = 0; i < sizeof(lights) / sizeof(light_t); ++i) {
        specular += getSpecularI(lights[i].position, point, normal);
    }
    if (PRINT) printf("Specular: %.4f\n", specular);
    return clamp(specular);
}

/**
 * @brief
 * Calculates the total diffused reflection intensity at a point
 * from all light sources.
 */
float getTotalDiffusedI(vector_t point, vector_t normal) {
    float diffused = 0;
    for (int i = 0; i < sizeof(lights) / sizeof(light_t); ++i) {
        diffused += getDiffusedI(lights[i].position,
                                         lights[i].brightness, point, normal);
    }
    if (PRINT) printf("Diffused: %.4f\n", diffused);
    return clamp(diffused);
}

/* Interpolation calculation */

/**
 * @param x, y
 * Coordinates of the point to be calculated.
 * @param IA, IB, IC, ID
 * Intensities at the corners of the rectangle.
 * @param XL, XR
 * X-coordinates of the left and right edges of the rectangle.
 * @param YB, YT
 * Y-coordinates of the bottom and top edges of the rectangle.
 */
float getIntensityAt(int x, int y, float IA, float IB, float IC, float ID,
                     int XL, int XR, int YB, int YT) {
    float IP = IA * (y - YB)/(YT - YB) + ID * (YT - y)/(YT - YB);
    float IQ = IB * (y - YB)/(YT - YB) + IC * (YT - y)/(YT - YB);
    float I = IP * (XR - x)/(XR - XL) + IQ * (x - XL)/(XR - XL);
    return I;
}

void display(void) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    drawLights();

    glPointSize(2);
    glBegin(GL_POINTS);

    /* Normals at each vertex */
    vector_t NA = vectorSum(N1, vectorSum(N2, N6));
    vector_t NB = vectorSum(N1, vectorSum(N2, N5));
    vector_t NC = vectorSum(N1, vectorSum(N4, N5));
    vector_t ND = vectorSum(N1, vectorSum(N4, N6));
    vector_t NE = vectorSum(N3, vectorSum(N4, N6));
    vector_t NF = vectorSum(N2, vectorSum(N3, N6));
    vector_t NG = vectorSum(N2, vectorSum(N3, N5));
    vector_t NH = vectorSum(N3, vectorSum(N4, N5));

    /* Total specular intensity at each vertex */
    float specularA = getTotalSpecularI(VA, NA);
    float specularB = getTotalSpecularI(VB, NB);
    float specularC = getTotalSpecularI(VC, NC);
    float specularD = getTotalSpecularI(VD, ND);
    float specularE = getTotalSpecularI(VE, NE);
    float specularF = getTotalSpecularI(VF, NF);
    float specularG = getTotalSpecularI(VG, NG);
    float specularH = getTotalSpecularI(VH, NH);

    /* Total ambient and diffused intensity at each vertex */
    float nonSpecularA = getTotalDiffusedI(VA, NA) + getAmbientI();
    float nonSpecularB = getTotalDiffusedI(VB, NB) + getAmbientI();
    float nonSpecularC = getTotalDiffusedI(VC, NC) + getAmbientI();
    float nonSpecularD = getTotalDiffusedI(VD, ND) + getAmbientI();
    float nonSpecularE = getTotalDiffusedI(VE, NE) + getAmbientI();
    float nonSpecularF = getTotalDiffusedI(VF, NF) + getAmbientI();
    float nonSpecularG = getTotalDiffusedI(VG, NG) + getAmbientI();
    float nonSpecularH = getTotalDiffusedI(VH, NH) + getAmbientI();

    /* FACE 1 */
    for (int x = 0; x <= 200; ++x) {
        for (int y = 0; y <= 200; ++y) {
            float specular = getIntensityAt(x, y, 
                specularB, specularC, specularD, specularA,
                0, 200, 0, 200);
            float nonSpecular = getIntensityAt(x, y,
                nonSpecularB, nonSpecularC, nonSpecularD, nonSpecularA,
                0, 200, 0, 200);
            changeColorAndIntensity(boxColour, specular, nonSpecular);
            glVertex3i(x, y, 0);
        }
    }

    /* FACE 2 */
    for (int x = 0; x <= 200; ++x) {
        for (int y = 0; y <= 200; ++y) {
            float specular = getIntensityAt(x, y,
                specularB, specularG, specularF, specularA,
                0, 200, 0, 200);
            float nonSpecular = getIntensityAt(x, y,
                nonSpecularB, nonSpecularG, nonSpecularF, nonSpecularA,
                0, 200, 0, 200);
            changeColorAndIntensity(boxColour, specular, nonSpecular);
            glVertex3i(0, y, x);
        }
    }

    /* FACE 3 */
    for (int x = 0; x <= 200; ++x) {
        for (int y = 0; y <= 200; ++y) {
            float specular = getIntensityAt(x, y,
                specularG, specularH, specularE, specularF,
                0, 200, 0, 200);
            float nonSpecular = getIntensityAt(x, y,
                nonSpecularG, nonSpecularH, specularE, nonSpecularF,
                0, 200, 0, 200);
            changeColorAndIntensity(boxColour, specular, nonSpecular);
            glVertex3i(x, y, 200);
        }
    }

    /* FACE 4 */
    for (int x = 0; x <= 200; ++x) {
        for (int y = 0; y <= 200; ++y) {
            float specular = getIntensityAt(x, y,
                specularC, specularH, specularE, specularD,
                0, 200, 0, 200);
            float nonSpecular = getIntensityAt(x, y,
                nonSpecularC, nonSpecularH, nonSpecularE, nonSpecularD,
                0, 200, 0, 200);
            changeColorAndIntensity(boxColour, specular, nonSpecular);
            glVertex3i(200, y, x);
        }
    }

    /* FACE 5 */
    for (int x = 0; x <= 200; ++x) {
        for (int y = 0; y <= 200; ++y) {
            float specular = getIntensityAt(x, y,
                specularG, specularH, specularC, specularB,
                0, 200, 0, 200);
            float nonSpecular = getIntensityAt(x, y,
                nonSpecularG, nonSpecularH, nonSpecularC, nonSpecularB,
                0, 200, 0, 200);
            changeColorAndIntensity(boxColour, specular, nonSpecular);
            glVertex3i(x, 200, y);
        }
    }

    /* FACE 6 */
    for (int x = 0; x <= 200; ++x) {
        for (int y = 0; y <= 200; ++y) {
            float specular = getIntensityAt(x, y,
                specularF, specularE, specularD, specularA,
                0, 200, 0, 200);
            float nonSpecular = getIntensityAt(x, y,
                nonSpecularF, nonSpecularE, nonSpecularD, nonSpecularA,
                0, 200, 0, 200);
            changeColorAndIntensity(boxColour, specular, nonSpecular);
            glVertex3i(x, 0, y);
        }
    }
    
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
    glutCreateWindow("With gouroud shading");

    /* Set 3D viewing attributes. */
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 4.0/3, 1, 2000);
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
