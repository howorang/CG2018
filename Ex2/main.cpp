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

static const int T_STEPS = 200;
static const int U_STEPS = 50;
Camera *camera = nullptr;

double time = 0;
GLuint metalTexture;
GLuint woodTexture;

void drawSpring();
void timer(int);

void drawSphere();

void drawCylinder(GLdouble base, GLdouble top,
        GLdouble height, GLint slices, GLint stacks);

void init (void) {
    metalTexture = SOIL_load_OGL_texture
            (
                    "metal.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    woodTexture = SOIL_load_OGL_texture
            (
                    "wood.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
   // glEnable (GL_LIGHTING); //enable the lighting
    //glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader
    glEnable(GL_TEXTURE_2D);

}



void display (void) {
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();
    camera->camera();
    enable();
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glPushMatrix();
    glTranslated(2,0,-2);
    drawCylinder(2, 2, 3, 30, 5);
    glPopMatrix();
    drawSpring();
    glPopMatrix();
    glutTimerFunc(5, timer, 0);
    glFlush();
    glutSwapBuffers(); //swap the buffers
}

void drawCylinder(GLdouble base, GLdouble top,
        GLdouble height, GLint slices, GLint stacks){
    GLUquadricObj* discQuadratic = gluNewQuadric();
    gluQuadricTexture(discQuadratic, TRUE);
    gluDisk(discQuadratic, 0, base, slices, stacks);
    gluDeleteQuadric(discQuadratic);
    GLUquadricObj* cylinderQuadratic = gluNewQuadric();
    gluQuadricDrawStyle(cylinderQuadratic, GLU_FILL);
    gluQuadricTexture(cylinderQuadratic, TRUE);
    gluCylinder(cylinderQuadratic,
             base, top, height, slices, stacks);
    glPushMatrix();
    glTranslated(0, 0, height);
    gluDisk(discQuadratic, 0, base, slices, stacks);
    glPopMatrix();
    gluDeleteQuadric(cylinderQuadratic);
}

void drawSpring() {
    GLdouble x;
    GLdouble y;
    GLdouble z;
    double change = 1 + sin(time/200) * 0.30;
    GLdouble t_max = 8 * M_PI;
    double_t u_max = 2 * M_PI;

    glBindTexture(GL_TEXTURE_2D, metalTexture);

    GLdouble polygonData[T_STEPS + 1][U_STEPS + 1][3];

    for (int i = 0; i <= T_STEPS; i++) {
        GLdouble t = t_max - (i * (t_max/ T_STEPS));
        for (int j = 0; j <= U_STEPS; j++) {
            GLdouble u = u_max - (j * (u_max/ U_STEPS));
                x = cos(t) * (3.0 + cos(u));
                y = sin(t) * (3.0 + cos(u));
                z = 0.6 * ((t) * change) + sin(u);
                polygonData[i][j][0] = x;
                polygonData[i][j][1] = y;
                polygonData[i][j][2] = z;
        }
    }

    for (int i = 0; i < T_STEPS; i++) {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= U_STEPS; j++) {
            GLdouble u = u_max - (j * (u_max/ U_STEPS));
            for (int k = 1; k >= 0; k--) {
                glTexCoord2d(k, u/u_max);
                glVertex3d(polygonData[i + k][j][0] , polygonData[i + k][j][1], polygonData[i + k][j][2]);
            }
        }
        glEnd();
    }

    glPushMatrix();
    x = cos(t_max) * (3.0 + cos(u_max));
    y = sin(t_max) * (3.0 + cos(u_max));
    z = 0.6 * ((t_max) * change) + sin(u_max);
    glTranslated(x,y,z);
    drawCylinder(2, 2, 3, 30, 5);
    glPushMatrix();
    glTranslated(0,0,6);
    drawSphere();
    glPopMatrix();
    glPopMatrix();
}

void drawSphere() {
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    GLUquadricObj* sphereQuadratic = gluNewQuadric();
    gluQuadricDrawStyle(sphereQuadratic, GLU_FILL);
    gluQuadricTexture(sphereQuadratic, TRUE);
    gluSphere(sphereQuadratic, 5, 30, 30);
    gluDeleteQuadric(sphereQuadratic);
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
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