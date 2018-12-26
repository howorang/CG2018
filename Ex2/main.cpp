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

static const float T_STEPS = 200;
static const float U_STEPS = 50;
Camera *camera = nullptr;

double time = 0;

void drawSpring();
void timer(int);
void init (void) {

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
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    drawSpring();
    glPopMatrix();
    glutTimerFunc(5, timer, 0);
    glutSwapBuffers(); //swap the buffers
//    angle++; //increase the angle
}

void drawSpring() {
    GLdouble x;
    GLdouble y;
    GLdouble z;
    int k;
    glColor3f (1.0, 1.0, 1.0);

    double change = 1 + sin(time/200) * 0.30;
    GLdouble t_max = 8 * M_PI;
    double_t u_max = 2 * M_PI;
    for (int i = 0; i <= T_STEPS; i++) {
        glBegin(GL_QUAD_STRIP);
        GLdouble t = t_max - (i * (t_max/ T_STEPS));
        for (int j = 0; j <= U_STEPS; j++) {
            GLdouble u = u_max - (j * (t_max/ T_STEPS));
            for (k = 1; k >= 0; k--) {
                GLdouble ring_var = (u_max/ U_STEPS) * k;
                x = cos(t + ring_var) * (3.0 + cos(u));
                y = sin(t + ring_var) * (3.0 + cos(u));
                z = 0.6 * ((t + ring_var) * change) + sin(u);
                glVertex3d(x, y, z);
            }
        }
        glEnd();
    }
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
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
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    camera = new Camera();
    glutMainLoop ();
    return 0;
}