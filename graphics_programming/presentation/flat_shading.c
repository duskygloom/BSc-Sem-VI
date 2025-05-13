#include "vector.h"

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

/* Subtle tweaks. */
int PRINT = 1;
int USE_DISTANCE = 1;
int DRAW_LIGHT_AXES = 0;
int DRAW_WORLD_AXES = 1;

/* About light sources. */
vector_t lights[] = {
    /* Position                 Color                   Brightness (only .x is used)*/
    //    {-500, 400, -300},       {0xff, 0xe9, 0x48},     {0.4, 0, 0},
       {600, 600, 600},         {0xff, 0xff, 0xff},     {0.2, 0, 0},
};

const int nLights = sizeof(lights) / sizeof(vector_t) / 3;

/* Value of p and k used in the algorithm. */
int pValue = 1;
float kValue = 0.0001f;

/* Global angle value to rotate the scene. */
float angle = 0;


/* Utility functions to make life easier. */

vector_t getLightPos(int i) {
    if (i < 0 || i >= nLights) { // return zero vector if out of bounds
        vector_t nullVector = {0, 0, 0};
        return nullVector;
    }
    return lights[3*i];
}

vector_t getLightColor(int i) {
    if (i < 0 || i >= nLights) {
        vector_t nullVector = {0, 0, 0};
        return nullVector;
    }
    return lights[3*i+1];
}

float getLightBrightness(int i) {
    if (i < 0 || i >= nLights) return 0.0;
    return lights[3*i+2].x;
}

void drawVertex(vector_t point) {
    glVertex3d(point.x, point.y, point.z);
}

/** if (PRINT) printf("I3: %.4f\n", I3);
        color3 = vectorSum(color3, getColorWithIntensity(getLightColor(i), I3));
    }
    changeColor3f(color3);
    drawVertex(A3);
    drawVertex(B3);
    drawVertex(C3);
    drawVertex(D3);
 * @brief
 * Clamps a float value between 0 and 1.
 */
float clamp(float f) {
    return f > 1.0 ? 1.0 : (f < 0.0 ? 0.0 : f);
}

void changeColor3f(vector_t color) {
    glColor3f(clamp(color.x),
              clamp(color.y),
              clamp(color.z));
}

void changeColor3i(vector_t color) {
    glColor3f(clamp(color.x/255.0),
              clamp(color.y/255.0),
              clamp(color.z/255.0));
}

vector_t getColorWithIntensity(vector_t color, float intensity) {
    vector_t newColor = {(color.x/255.0) * intensity,
                         (color.y/255.0) * intensity,
                         (color.z/255.0) * intensity};
    return newColor;
}

/**
 * @brief
 * Calculates the intensity of the reflected light using
 * the faceCenter and outerNormal. 
 */
float getIntensity(vector_t lightPos, float brightness, vector_t faceCenter, vector_t outerNormal) {
    const float iAlpha = 0.4;
    const float kAlpha = 0.4;

    float ambient = kAlpha * iAlpha;

    float iLight = 1.0;

    if (USE_DISTANCE) {
        /* Camera is at (600, 600, 600), so the diagonal
        distance from origin to camera is used as the
        maximum distance. */
        float maxDistance = 600.0 * sqrtf(3);
        float distance = clamp(vectorDistance(faceCenter, lightPos)
                               / maxDistance); // relative
        iLight /= (kValue + pow(distance, pValue));
    }

    float theta;
    vector_t lightVector = vectorSum(lightPos, vectorScale(faceCenter, -1));
    float magnitudes = vectorMagnitude(lightVector) * vectorMagnitude(outerNormal);
    if (magnitudes == 0) theta = 0.0;
    else theta = clamp(vectorDot(outerNormal, lightVector) / magnitudes);

    float diffused = brightness * iLight * theta;

    return ambient + diffused;
}

/**
 * @brief
 * Draw guidelines to make the drawing more obvious
 * because it's 3D and I can't really understand it
 * without the coordinate axes.
 */
void drawAxes(void) {
    glBegin(GL_LINES);

    if (DRAW_LIGHT_AXES) {
        glColor3f(0.4, 0.4, 0.4);
        for (int i = 0; i < nLights; ++i) {
            glVertex3d(getLightPos(i).x, 0, 0); drawVertex(getLightPos(i));
            glVertex3d(0, getLightPos(i).y, 0); drawVertex(getLightPos(i));
            glVertex3d(0, 0, getLightPos(i).z); drawVertex(getLightPos(i));
        }
    }

    if (DRAW_WORLD_AXES) {
        glColor3f(1, 0, 0);
        glVertex3d(0, 0, 0); glVertex3d(1000, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3d(0, 0, 0); glVertex3d(0, 1000, 0);
        glColor3f(0, 0, 1);
        glVertex3d(0, 0, 0); glVertex3d(0, 0, 1000);
    }

    glEnd();
}

/**
 * @brief
 * Draw the light source as a thick dot.
 */
void drawLight(void) {
    glPointSize(8);
    glBegin(GL_POINTS);
    for (int i = 0; i < nLights; ++i) {
        changeColor3i(getLightColor(i));
        drawVertex(getLightPos(i));
    }
    glEnd();
}

/**
 * @brief
 * Returns the center of a 3D triangular face.
 */
vector_t getTriCenter(vector_t A, vector_t B, vector_t C) {
    vector_t AB = vectorSum(A, B);
    vector_t ABC = vectorSum(AB, C);
    vector_t faceCenter = vectorScale(ABC, 1.0/3);
    return faceCenter;
}

/**
 * @brief
 * Returns the center of a 3D quadrilateral face.
 */
vector_t getQuadCenter(vector_t A, vector_t B, vector_t C, vector_t D) {
    vector_t AB = vectorSum(A, B);
    vector_t CD = vectorSum(C, D);
    vector_t ABCD = vectorSum(AB, CD);
    vector_t faceCenter = vectorScale(ABCD, 0.25);
    return faceCenter;
}

void display(void) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    drawLight();

    glBegin(GL_QUADS); // 3 quadrilaterals

    /* FACE 1 */
    vector_t A1 = {0, 0, 0};
    vector_t B1 = {0, 200, 0};
    vector_t C1 = {200, 200, 0};
    vector_t D1 = {200, 0, 0}; // vertices
    vector_t N1 = {0, 0, -1}; // outward normal
    vector_t faceCenter1 = getQuadCenter(A1, B1, C1, D1);
    vector_t color1 = {0, 0, 0};
    for (int i = 0; i < nLights; ++i) {
        float I1 = getIntensity(getLightPos(i), getLightBrightness(i), faceCenter1, N1);
        if (PRINT) printf("I1: %.4f\n", I1);
        color1 = vectorSum(color1, getColorWithIntensity(getLightColor(i), I1));
    }
    changeColor3f(color1);
    drawVertex(A1);
    drawVertex(B1);
    drawVertex(C1);
    drawVertex(D1);

    /* FACE 2 */
    vector_t A2 = {0, 0, 0};
    vector_t B2 = {0, 200, 0};
    vector_t C2 = {0, 200, 200};
    vector_t D2 = {0, 0, 200};
    vector_t N2 = {-1, 0, 0};
    vector_t faceCenter2 = getQuadCenter(A2, B2, C2, D2);
    vector_t color2 = {0, 0, 0};
    for (int i = 0; i < nLights; ++i) {
        float I2 = getIntensity(getLightPos(i), getLightBrightness(i), faceCenter2, N2);
        if (PRINT) printf("I1: %.4f\n", I2);
        color2 = vectorSum(color2, getColorWithIntensity(getLightColor(i), I2));
    }
    changeColor3f(color2);
    drawVertex(A2);
    drawVertex(B2);
    drawVertex(C2);
    drawVertex(D2);

    /* FACE 3 */
    vector_t A3 = {0, 200, 200};
    vector_t B3 = {0, 0, 200};
    vector_t C3 = {200, 0, 0};
    vector_t D3 = {200, 200, 0};
    vector_t N3 = {1, 0, 1};
    vector_t faceCenter3 = getQuadCenter(A3, B3, C3, D3);
    vector_t color3 = {0, 0, 0};
    for (int i = 0; i < nLights; ++i) {
        float I3 = getIntensity(getLightPos(i), getLightBrightness(i), faceCenter3, N3);
        if (PRINT) printf("I3: %.4f\n", I3);
        color3 = vectorSum(color3, getColorWithIntensity(getLightColor(i), I3));
    }
    changeColor3f(color3);
    drawVertex(A3);
    drawVertex(B3);
    drawVertex(C3);
    drawVertex(D3);

    glEnd();

    glBegin(GL_TRIANGLES); // 2 triangles

    /* FACE 4 */
    vector_t A4 = {0, 200, 0};
    vector_t B4 = {0, 200, 200};
    vector_t C4 = {200, 200, 0};
    vector_t N4 = {0, 1, 0};
    vector_t faceCenter4 = getTriCenter(A4, B4, C4);
    vector_t color4 = {0, 0, 0};
    for (int i = 0; i < nLights; ++i) {
        float I4 = getIntensity(getLightPos(i), getLightBrightness(i), faceCenter4, N4);
        if (PRINT) printf("I4: %.4f\n", I4);
        color4 = vectorSum(color4, getColorWithIntensity(getLightColor(i), I4));
    }
    changeColor3f(color4);
    drawVertex(A4);
    drawVertex(B4);
    drawVertex(C4);
    
    /* FACE 5 */
    vector_t A5 = {0, 0, 0};
    vector_t B5 = {0, 0, 200};
    vector_t C5 = {200, 0, 0};
    vector_t N5 = {0, -1, 0};
    vector_t faceCenter5 = getTriCenter(A5, B5, C5);
    vector_t color5 = {0, 0, 0};
    for (int i = 0; i < nLights; ++i) {
        float I5 = getIntensity(getLightPos(i), getLightBrightness(i), faceCenter5, N5);
        if (PRINT) printf("I5: %.4f\n", I5);
        color5 = vectorSum(color5, getColorWithIntensity(getLightColor(i), I5));
    }
    changeColor3f(color5);
    drawVertex(A5);
    drawVertex(B5);
    drawVertex(C5);

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
        case '1':
        angle += 0.1;
        glRotatef(angle, 1, 0, 0);
        break;
        case '2':
        angle += 0.1;
        glRotatef(angle, 0, 1, 0);
        break;
        case '3':
        angle += 0.1;
        glRotatef(angle, 0, 0, 1);
        break;
        case '4':
        angle += 0.1;
        glRotatef(angle, 1, 1, 0);
        break;
        case '5':
        angle += 0.1;
        glRotatef(angle, 0, 1, 1);
        break;
        case '6':
        angle += 0.1;
        glRotatef(angle, 1, 0, 1);
        break;
        case 'a':
        glTranslatef(-10, 0, 0);
        break;
        case 'd':
        glTranslatef(10, 0, 0);
        break;
        case 'w':
        glTranslatef(0, 10, 0);
        break;
        case 's':
        glTranslatef(0, -10, 0);
        break;
        case 'q':
        glTranslatef(0, 0, 10);
        break;
        case 'e':
        glTranslatef(0, 0, -10);
        break;
        case '=':
        glScalef(1.2, 1.2, 1.2);
        break;
        case '-':
        glScalef(0.8, 0.8, 0.8);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Flat shading");

    /* Set 3D viewing attributes. */
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 4.0/3, 1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(600, 600, 600, 0, 0, 0, 0, 1, 0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
