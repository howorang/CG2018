#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include<stdlib.h>	//exit(0)
#include<math.h>
#include "Camera.h"
#include <SOIL.h>
#include <GL/glext.h>

typedef struct PlanetConf {
    GLuint texture;
    GLfloat size;
    GLfloat semiMajorAxis;
    GLfloat eccentricity;
    GLfloat orbitalPeriod;
    GLfloat dayLength;
    void (*drawFunc)(GLuint, GLfloat) = NULL;
} PlanetConf;

static const int TIME_FACTOR = 500;
static const int SCALE_FACTOR = 250;
Camera *camera = nullptr;

GLuint sunTexture;
GLuint saturnRingTexture;
PlanetConf planetConfs[8];

double time = 0;
void timer(int);

void drawSun();

void drawPlanet(PlanetConf* planetConf);

void drawPlanetSimple(GLuint texture, GLfloat size);

void drawSaturn(GLuint texture, GLfloat size);

GLuint loadTexture(const char *texturePath);

void init (void) {
    sunTexture = loadTexture("assets/sun.jpg");

    PlanetConf mercuryConf = {.texture = loadTexture("assets/mercury.jpg"), .size = 2439,
                              .semiMajorAxis = 0.3870, .eccentricity = 0.2056, .orbitalPeriod = 0.2408, .dayLength = 1.408};

    PlanetConf venusConf = {.texture = loadTexture("assets/venus.jpg"), .size = 6051,
            .semiMajorAxis = 0.7233, .eccentricity = 0.0067, .orbitalPeriod = 0.6151, .dayLength = 5.832};

    PlanetConf earthConf = {.texture = loadTexture("assets/earth.jpg"), .size = 6378,
            .semiMajorAxis = 1, .eccentricity = 0.01671, .orbitalPeriod = 1, .dayLength = 24};

    PlanetConf marsConf = {.texture = loadTexture("assets/mars.jpg"), .size = 3396,
            .semiMajorAxis = 1.5237, .eccentricity = 0.09339, .orbitalPeriod = 1.8808, .dayLength = 25};

    PlanetConf jupiterConf = {.texture = loadTexture("assets/jupiter.jpg"), .size = 71492,
            .semiMajorAxis = 2.2029, .eccentricity = 0.0484, .orbitalPeriod = 11.8626, .dayLength = 10};

    PlanetConf saturnConf = {.texture = loadTexture("assets/saturn.jpg"), .size = 60268,
            .semiMajorAxis = 3.537, .eccentricity = 0.0539, .orbitalPeriod = 29.4474, .dayLength = 11,
            .drawFunc = drawSaturn};

    PlanetConf uranusConf = {.texture = loadTexture("assets/uranus.jpg"), .size = 25559,
            .semiMajorAxis = 4.189, .eccentricity = 0.04726, .orbitalPeriod = 84.0168, .dayLength = 17};

    PlanetConf neptuneConf = {.texture = loadTexture("assets/neptune.jpg"), .size = 24764,
            .semiMajorAxis = 5.0699, .eccentricity = 0.00859, .orbitalPeriod = 164.7913, .dayLength = 16};

    planetConfs[0] = mercuryConf;
    planetConfs[1] = venusConf;
    planetConfs[2] = earthConf;
    planetConfs[3] = marsConf;
    planetConfs[4] = jupiterConf;
    planetConfs[5] = saturnConf;
    planetConfs[6] = uranusConf;
    planetConfs[7] = neptuneConf;

    saturnRingTexture = loadTexture("assets/saturn_ring_alpha.png");
}

GLuint loadTexture(const char *texturepath) {
    return SOIL_load_OGL_texture
            (
                    texturepath,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void drawPlanet(PlanetConf* planetConf) {
    GLfloat a = planetConf -> semiMajorAxis;
    GLfloat c = a * planetConf -> eccentricity;
    GLfloat b  = (GLfloat)(sqrt(pow(a,2) - pow(c,2)));
    GLfloat posx = (GLfloat)(a * cos(time/ TIME_FACTOR /planetConf -> orbitalPeriod));
    GLfloat posy = (GLfloat)(b * sin(time / TIME_FACTOR / planetConf -> orbitalPeriod));
    glPushMatrix();
    glRotatef(time /TIME_FACTOR/ planetConf -> dayLength, 0, 1, 0);
    glTranslatef(posx * SCALE_FACTOR, 0, posy * SCALE_FACTOR);
    glTranslatef(0, 0, planetConf -> eccentricity * SCALE_FACTOR);
    if (planetConf -> drawFunc != NULL) {
        planetConf->drawFunc(planetConf->texture, planetConf->size);
    } else {
        drawPlanetSimple(planetConf->texture, planetConf->size);
    }
    glPopMatrix();
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();
    camera->camera();
    enable();
    drawSun();
    for (int i = 0; i < 8; ++i) {
        drawPlanet(&planetConfs[i]);
    }
    glutTimerFunc(5, timer, 0);
    glFlush();
    glutSwapBuffers(); //swap the buffers
}

void drawPlanetSimple(GLuint texture, GLfloat size) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLUquadricObj *sphereQuadratic = gluNewQuadric();
    gluQuadricDrawStyle(sphereQuadratic, GLU_FILL);
    gluQuadricTexture(sphereQuadratic, TRUE);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    gluSphere(sphereQuadratic, size/1000, 50, 50);
    glPopMatrix();
    gluDeleteQuadric(sphereQuadratic);
}

void drawSaturn(GLuint texture, GLfloat size) {
    drawPlanetSimple(texture, size);
    GLUquadricObj *discQuadratic = gluNewQuadric();
    glPushMatrix();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, saturnRingTexture);
    gluQuadricDrawStyle(discQuadratic, GLU_FILL);
    gluQuadricTexture(discQuadratic, TRUE);
    glRotatef(90, 1, 0, 0);
    glScaled(1, 1, 0.01);
    gluSphere(discQuadratic, size/1000 + 70, 50, 50);
    glPopMatrix();
    gluDeleteQuadric(discQuadratic);
}

void drawSun() {
    GLfloat emissionParams[] = { 1, 0.5, 0.5, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionParams);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, sunTexture);
    GLUquadricObj* sunQuadratic = gluNewQuadric();
    glRotatef(time /TIME_FACTOR , 0, 1, 0);
    gluQuadricDrawStyle(sunQuadratic, GLU_FILL);
    gluQuadricTexture(sunQuadratic, TRUE);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    gluSphere(sunQuadratic, 695700/20000, 50, 50);
    glPopMatrix();
    gluDeleteQuadric(sunQuadratic);
    emissionParams[0] = 0.0;
    emissionParams[1] = 0.0;
    emissionParams[2] = 0.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionParams);
}




void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 5000.0); //set the perspective (angle of sight, width, height, depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

void timer(int par) {
    time += 1;
    glutPostRedisplay();
}


int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic FPS OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    camera = new Camera();
    glutMainLoop ();
    return 0;
}