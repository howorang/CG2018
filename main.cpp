//#include “stdafx.h”
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "custom_types.h"
#include <stdlib.h>
void triangle(GLfloat red, GLfloat green, GLfloat blue);

void timer(int);

void rotateByCenterOfMass(GLfloat ax,  GLfloat ay,
                          GLfloat bx, GLfloat by,
                          GLfloat cx, GLfloat cy);

void drawTriangle(GLfloat x, GLfloat y,
                  GLfloat red, GLfloat green, GLfloat blue);

void drawQuarter();

float degreee = 0;

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//=1
    // The new scene
    glRotated(degreee, 0, 0, 1);
    drawQuarter();

    glTranslated(-(100/3)*2,0,0);
    glRotated(90, 0, 0, 1);
    drawQuarter();

    glTranslated(-(100/3)*2,0,0);
    glRotated(90, 0, 0, 1);
    drawQuarter();

    glTranslated(-(100/3)*2,0,0);
    glRotated(90, 0, 0, 1);
    drawQuarter();
    // The end of scene
    glFlush();//start processing buffered OpenGL
    glutTimerFunc(5, timer, 0);
    glutSwapBuffers();
}

void drawQuarter() {
    drawTriangle(0, 0,
                 0, 0, 255);
    drawTriangle(0,100,
                 0,255,0);
    drawTriangle(100,100,
                 255,255,0);
    drawTriangle(0,200,
                 255,0,0);


    drawTriangle(100,0,
                 207,47, 47);
    drawTriangle(200,0,
                 255,0,144);
}

void drawTriangle(GLfloat x, GLfloat y,
                  GLfloat red, GLfloat green, GLfloat blue) {
    glPushMatrix();
    glTranslated(x, y, 0);
    rotateByCenterOfMass(100, 0,
                         0, 100,
                         0, 0);
    triangle(red, green, blue);
    glPopMatrix();
}

void rotateByCenterOfMass(GLfloat ax,  GLfloat ay,
        GLfloat bx, GLfloat by,
        GLfloat cx, GLfloat cy) {
    GLfloat xc = (ax + bx + cx) / 3;
    GLfloat yc = (ay + by + cy) / 3;
    glRotated(-(degreee * 3), 0, 0, 1);
    glTranslated(-xc, -yc, 0);
}

void timer(int par) {
  // degreee += 0.25;
    if (degreee == 360) {
        degreee = 0;
    }
    glutPostRedisplay();
}

void triangle(GLfloat red, GLfloat green, GLfloat blue) {
    glBegin(GL_POLYGON);
    glColor4f(red, green, blue, 1.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();
}
void MyInit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
    /* initialize viewing values */
    glViewport(0, 0, 300, 300);//window origin and size
    glMatrixMode(GL_PROJECTION);//
    gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//=1
}

int main(int argc, char** argv) { //<- for normal API
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//single buffer and RGBA
    glutInitWindowSize(600, 600);//initial window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My window");//create widnow, hello title bar
    MyInit();
    glutDisplayFunc(MyDisplay);//
    glutMainLoop();//enter main loop and process events
    return 0;
}