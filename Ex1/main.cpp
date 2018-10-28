//#include “stdafx.h”
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "custom_types.h"
#include <stdlib.h>

static const double DRIFT_AWAY_SPEED = 0.0833333;

static const double TIME_FACTOR = 0.25;

void triangle(GLfloat red, GLfloat green, GLfloat blue);

void timer(int);

void rotateByCenterOfMass(GLfloat ax,  GLfloat ay,
                          GLfloat bx, GLfloat by,
                          GLfloat cx, GLfloat cy, int isReverse);

void drawTriangle(GLfloat x, GLfloat y,
                  GLfloat red, GLfloat green, GLfloat blue, int isReverse);

void drawQuarter();

float degreee = 0;
float driftAway = 0;
int away = true;

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//=1
    // The new scene
    glRotated(degreee, 0, 0, 1);
    drawQuarter();

    glRotated(90, 0, 0, 1);
    drawQuarter();

    glRotated(90, 0, 0, 1);
    drawQuarter();

    glRotated(90, 0, 0, 1);
    drawQuarter();
    // The end of scene
    glFlush();//start processing buffered OpenGL
    glutTimerFunc(5, timer, 0);
    glutSwapBuffers();
}

void drawQuarter() {
    drawTriangle(0, 0,
                 0, 0, 255, false);
    drawTriangle(0,100,
                 0,255,0, true);
    drawTriangle(100,100,
                 255,255,0, false);
    drawTriangle(0,200,
                 255,0,0, false);


    drawTriangle(100,0,
                 207,47, 47, true);
    drawTriangle(200,0,
                 255,0,144, false);
}

void drawTriangle(GLfloat x, GLfloat y,
                  GLfloat red, GLfloat green, GLfloat blue, int isReverse) {
    glPushMatrix();
    glTranslated(x, y, 0);
    glTranslated(driftAway, driftAway, 0);
    rotateByCenterOfMass(100, 0,
                         0, 100,
                         0, 0, isReverse);
    triangle(red, green, blue);
    glPopMatrix();
}

void rotateByCenterOfMass(GLfloat ax,  GLfloat ay,
        GLfloat bx, GLfloat by,
        GLfloat cx, GLfloat cy, int isReverse) {
    GLfloat xc = (ax + bx + cx) / 3;
    GLfloat yc = (ay + by + cy) / 3;
    glTranslated(xc, yc, 0);
    glRotated(isReverse ? (degreee * 3) :  -(degreee * 3), 0, 0, 1);
    glTranslated(-xc, -yc, 0);
}

void timer(int par) {
    if (driftAway > 100) {
        away = false;
    }
    if (driftAway < 0) {
        away = true;
    }
    degreee += 1 * TIME_FACTOR;
    if (away) {
        driftAway += DRIFT_AWAY_SPEED * TIME_FACTOR;
    } else {
        driftAway -= DRIFT_AWAY_SPEED * TIME_FACTOR;
    }
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