/**
 * @todo
 * Add multiple light source support.
 */

#include "matrix.h"
#include "vector.h"

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Subtle tweaks. */
int PRINT = 1;
int USE_DISTANCE = 1;
int DRAW_LIGHT_AXES = 0;
int DRAW_WORLD_AXES = 1;

/* Camera. */
vector_t camera = {600, 600, 600};

/* About light sources. */
vector_t lights[] = {
    /* Position                 Color                   Brightness (only .x is used) */
       {300, 500, 300},         {0xff, 0xe9, 0x48},     {0.4, 0, 0},
       {-500, 500, -300},       {0xff, 0xe9, 0x48},     {0.4, 0, 0},
};

const int nLights = sizeof(lights) / sizeof(vector_t) / 3;

/* Value of p and k used in the algorithm. */
int pValue = 1;
float kValue = 0.0001f;


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

/**
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
        glVertex3d(-1000, 0, 0); glVertex3d(1000, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3d(0, -1000, 0); glVertex3d(0, 1000, 0);
        glColor3f(0, 0, 1);
        glVertex3d(0, 0, -1000); glVertex3d(0, 0, 1000);
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

void drawFace1() {
    vector_t A = {0, 0, 0};
    vector_t B = {0, 200, 0};
    vector_t C = {200, 200, 0};
    vector_t D = {200, 0, 0}; // vertices
    vector_t normal = {0, 0, -1}; // outward normal

    // calculate intensity at each vertex
    float IA = getIntensity(getLightPos(0), getLightBrightness(0), A, normal);
    float IB = getIntensity(getLightPos(0), getLightBrightness(0), B, normal);
    float IC = getIntensity(getLightPos(0), getLightBrightness(0), C, normal);
    float ID = getIntensity(getLightPos(0), getLightBrightness(0), D, normal);

    // first interpolate all points along AB
    float IABarray[201];
    for (int i = 0; i <= 200; ++i) {
        IABarray[i] = IA + (IB - IA) * (i / 200.0);
    }
    // then interpolate all points along DC
    float IDCarray[201];
    for (int i = 0; i <= 200; ++i) {
        IDCarray[i] = ID + (IC - ID) * (i / 200.0);
    }
    // finally interpolate all points from AB to DC
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i <= 200; ++i) {
        for (int j = 0; j <= 200; ++j) {
            float I = IABarray[j] + (IDCarray[j] - IABarray[j]) * (i / 200.0);
            vector_t point = {i, j, 0};
            changeColor3f(getColorWithIntensity(getLightColor(0), I));
            drawVertex(point);
        }
    }
    glEnd();
}

void drawFace2() {
    vector_t A = {0, 0, 0};
    vector_t B = {0, 200, 0};
    vector_t C = {0, 200, 200};
    vector_t D = {0, 0, 200};
    vector_t normal = {-1, 0, 0};

    // calculate intensity at each vertex
    float IA = getIntensity(getLightPos(0), getLightBrightness(0), A, normal);
    float IB = getIntensity(getLightPos(0), getLightBrightness(0), B, normal);
    float IC = getIntensity(getLightPos(0), getLightBrightness(0), C, normal);
    float ID = getIntensity(getLightPos(0), getLightBrightness(0), D, normal);

    // first interpolate all points along AB
    float IABarray[201];
    for (int i = 0; i <= 200; ++i) {
        IABarray[i] = IA + (IB - IA) * (i / 200.0);
    }

    // then interpolate all points along DC
    float IDCarray[201];
    for (int i = 0; i <= 200; ++i) {
        IDCarray[i] = ID + (IC - ID) * (i / 200.0);
    }

    // finally interpolate all points from AB to DC
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i <= 200; ++i) {
        for (int j = 0; j <= 200; ++j) {
            float I = IABarray[j] + (IDCarray[j] - IABarray[j]) * (i / 200.0);
            vector_t point = {0, i, j};
            changeColor3f(getColorWithIntensity(getLightColor(0), I));
            drawVertex(point);
        }
    }
    glEnd();
}

Matrix4x4 face3Transformation;

/**
 * @note
 * To make life easier, the third face will be drawn in the YX
 * plane. Then it can be transfomed to its actual position.
 * This function sets the transformation matrix which can then be
 * used to transform other points.
 */
void setFace3Transformation() {
    unitMatrix(face3Transformation);
    // translate 200 units along Z-axis
    multiplyMatrix(face3Transformation, (Matrix4x4){{1, 0, 0, 0},
                                               {0, 1, 0, 0},
                                               {0, 0, 1, 200},
                                               {0, 0, 0, 1}});
    // rotate 45 degrees around Y-axis
    const float root2Inverse = 1.0 / sqrtf(2);
    multiplyMatrix(face3Transformation, (Matrix4x4){{root2Inverse, 0, root2Inverse, 0},
                                               {0, 1, 0, 0},
                                               {-root2Inverse, 0, root2Inverse, 0},
                                               {0, 0, 0, 1}});
}

/**
 * @warning
 * Use this function before shading or the distance will
 * be incorrect. Use the normal of the original polygon
 * and not the simplified one in YX plane duh.
 */
vector_t getFace3TransformedPoint(vector_t point) {
    float x = face3Transformation[0][0] * point.x +
              face3Transformation[0][1] * point.y +
              face3Transformation[0][2] * point.z +
              face3Transformation[0][3];
    float y = face3Transformation[1][0] * point.x +
              face3Transformation[1][1] * point.y +
              face3Transformation[1][2] * point.z +
              face3Transformation[1][3];
    float z = face3Transformation[2][0] * point.x +
              face3Transformation[2][1] * point.y +
              face3Transformation[2][2] * point.z +
              face3Transformation[2][3];
    return (vector_t){x, y, z};
}

/**
 * @note
 * This face is a bit special. Refer to the note of
 * setFace3Transformation().
 */
void drawFace3() {
    vector_t A = {0, 0, 0};
    vector_t B = {0, 200, 0};
    vector_t C = {282, 200, 0};
    vector_t D = {282, 0, 0}; // vertices
    vector_t normal = {1, 0, 1}; // outward normal

    // calculate intensity at each vertex
    float IA = getIntensity(getLightPos(0), getLightBrightness(0), A, normal);
    float IB = getIntensity(getLightPos(0), getLightBrightness(0), B, normal);
    float IC = getIntensity(getLightPos(0), getLightBrightness(0), C, normal);
    float ID = getIntensity(getLightPos(0), getLightBrightness(0), D, normal);

    // first interpolate all points along AB
    float IABarray[201];
    for (int i = 0; i <= 200; ++i) {
        IABarray[i] = IA + (IB - IA) * (i / 200.0);
    }

    // then interpolate all points along DC
    float IDCarray[201];
    for (int i = 0; i <= 200; ++i) {
        IDCarray[i] = ID + (IC - ID) * (i / 200.0);
    }

    // finally interpolate all points from AB to DC
    glPointSize(2);
    glBegin(GL_POINTS);
    setFace3Transformation(); // calculate the transformation matrix
    for (int i = 0; i <= 282; ++i) {
        for (int j = 0; j <= 200; ++j) {
            float I = IABarray[j] + (IDCarray[j] - IABarray[j]) * (i / 282.0);
            // transform the point to its actual position
            vector_t point = getFace3TransformedPoint((vector_t){i, j, 0});
            changeColor3f(getColorWithIntensity(getLightColor(0), I));
            drawVertex(point);
        }
    }
    glEnd();
}

void drawFace4() {
    vector_t A = {0, 200, 0};
    vector_t B = {0, 200, 200};
    vector_t C = {200, 200, 0};
    vector_t normal = {0, 1, 0}; // outward normal

    // calculate intensity at each vertex
    float IA = getIntensity(getLightPos(0), getLightBrightness(0), A, normal);
    float IB = getIntensity(getLightPos(0), getLightBrightness(0), B, normal);
    float IC = getIntensity(getLightPos(0), getLightBrightness(0), C, normal);

    // first interpolate all points along AB
    float IABarray[201];
    for (int i = 0; i <= 200; ++i) {
        IABarray[i] = IA + (IB - IA) * (i / 200.0);
    }

    // then interpolate all points along AC
    float IACarray[201];
    for (int i = 0; i <= 200; ++i) {
        IACarray[i] = IA + (IC - IA) * (i / 200.0);
    }

    // finally interpolate all points from AB to AC
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i <= 200; ++i) {
        if (i == 0) continue; // to avoid division by zero
        for (int j = 0; j <= i; ++j) {
            float I = IABarray[i] + (IACarray[i] - IABarray[i]) * (j / i);
            vector_t point = {200-i, 200, j};
            changeColor3f(getColorWithIntensity(getLightColor(0), I));
            drawVertex(point);
        }
    }
    glEnd();
}

void drawFace5() {
    vector_t A = {0, 0, 0};
    vector_t B = {0, 0, 200};
    vector_t C = {200, 0, 0};
    vector_t normal = {0, -1, 0}; // outward normal

    // calculate intensity at each vertex
    float IA = getIntensity(getLightPos(0), getLightBrightness(0), A, normal);
    float IB = getIntensity(getLightPos(0), getLightBrightness(0), B, normal);
    float IC = getIntensity(getLightPos(0), getLightBrightness(0), C, normal);

    // first interpolate all points along AB
    float IABarray[201];
    for (int i = 0; i <= 200; ++i) {
        IABarray[i] = IA + (IB - IA) * (i / 200.0);
    }

    // then interpolate all points along AC
    float IACarray[201];
    for (int i = 0; i <= 200; ++i) {
        IACarray[i] = IA + (IC - IA) * (i / 200.0);
    }

    // finally interpolate all points from AB to AC
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i <= 200; ++i) {
        if (i == 0) continue; // to avoid division by zero error
        for (int j = 0; j <= i; ++j) {
            float I = IABarray[i] + (IACarray[i] - IABarray[i]) * (j / i);
            vector_t point = {200-i, 0, j};
            changeColor3f(getColorWithIntensity(getLightColor(0), I));
            drawVertex(point);
        }
    }
    glEnd();
}

void display(void) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    drawLight();

    drawFace1();
    drawFace2();
    drawFace3();
    drawFace4();
    drawFace5();

    glutSwapBuffers();
    PRINT = 0; // to avoid printing the second time display 
               // function is called
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
    glutCreateWindow("Gouroud shading");

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
