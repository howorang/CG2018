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

Camera *camera = nullptr;

double time = 0;
void timer(int);

void init (void) {

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
    //
    glutTimerFunc(5, timer, 0);
    glFlush();
    glutSwapBuffers(); //swap the buffers
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