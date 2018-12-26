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

static const float T_STEP = 0.1;
static const float U_STEP = 0.1;

float lastx, lasty;

//positions of the cubes
float positionz[10];
float positionx[10];
Camera *camera = nullptr;

void cubepositions (void) { //set the positions of the cubes

    for (int i=0;i<10;i++)
    {
        positionz[i] = rand()%5 + 5;
        positionx[i] = rand()%5 + 5;
    }
}

//draw the cube
void cube (void) {
    for (int i=0;i<10;i++)
    {
        glPushMatrix();
        glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] * 10); //translate the cube
        glutSolidCube(2); //draw the cube
        glPopMatrix();
    }
}

void init (void) {
    cubepositions();
}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glEnable (GL_LIGHTING); //enable the lighting
    glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

}



void display (void) {
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();
    camera->camera();
    enable();
    cube();
    GLfloat x;
    GLfloat y;
    GLfloat z;
    int k;
    glColor3f (1.0, 1.0, 1.0);
    float t = 8 * M_PI;
    float u = 2 * M_PI;
    for (  float t = 8 * M_PI; t >= 0; t -= T_STEP) {
        glBegin(GL_QUAD_STRIP);
        for (float u = 2 * M_PI; u >= 0; u -= U_STEP) {
            for (k = 1; k >= 0; k--) {
                float ring_var = U_STEP * k;
                x = cos(t + ring_var) * (3.0 + cos(u));
                y = sin(t + ring_var) * (3.0 + cos(u));
                z = 0.6 * (t + ring_var) + sin(u);
                glVertex3d(x, y, z);
            }
        }
        glEnd();
    }
    glutSwapBuffers(); //swap the buffers
//    angle++; //increase the angle
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}



int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic FPS OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    camera = new Camera();
    glutMainLoop ();
    return 0;
}