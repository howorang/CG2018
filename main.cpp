//#include “stdafx.h”
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
void MyDisplay(void) {
    // Wyswietlana scena - poczatek
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    //zmiana stanu OpenGL’a
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    //Red;
    glVertex2f(100.0f, 50.0f);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    //Green
    glVertex2f(450.0f, 400.0f);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    //Blue
    glVertex2f(450.0f, 50.0f);
    glEnd();
    // Wyswietlana scena - koniec
    glFlush();
    //start processing buffered OpenGL routines
}
void MyInit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //select clearing (background) color
    /* initialize viewing values */
    glViewport(0, 0, 300, 300);
    //pocz•tek u.ws. lewy górny róg
    glMatrixMode(GL_PROJECTION
    );//Nast•pne 2 wiersze b•d• modyfikowały m. PROJECTION
    glLoadIdentity();
    //inicjalizacja
    gluOrtho2D(0.0, 500.0*1.2, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    //Nast•pny wiersz b•dzie modyfikował m. MODELVIEW
    glLoadIdentity();
}
/*int APIENTRY WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR     lpCmdLine,
int       nCmdShow){
glutInit(&__argc, __argv);             */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //single buffer and RGBA
    glutInitWindowSize(250, 250);
    //initial window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My window");
    //create widnow, hello title bar
    MyInit();
    glutDisplayFunc(MyDisplay);
    //register display function (call-back)
    /*     glutSetMenu(menu);
    glutReshapeFunc(NULL);
    glutReshapeFunc(NULL);
    glutKeyboardFunc(NULL);
    glutKeyboardFunc(NULL);
    glutMouseFunc(NULL);
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutMotionFunc(NULL);
    glutVisibilityFunc(NULL);
    glutVisibilityFunc(NULL);
    glutMenuStateFunc(NULL);
    glutMenuStateFunc(NULL);
    glutMenuStatusFunc(NULL);
    glutMenuStatusFunc(NULL);
    glutSpecialFunc(NULL);
    glutSpecialFunc(NULL);
    glutSpaceballMotionFunc(NULL);
    glutSpaceballMotionFunc(NULL);
    glutSpaceballRotateFunc(NULL);
    glutSpaceballRotateFunc(NULL);
    glutSpaceballButtonFunc(NULL);
    glutSpaceballButtonFunc(NULL);
    glutButtonBoxFunc(NULL);
    glutButtonBoxFunc(NULL);
    glutDialsFunc(NULL);
    glutDialsFunc(NULL);
    glutTabletMotionFunc(NULL);
    glutTabletMotionFunc(NULL);
    glutTabletButtonFunc(NULL);
    glutTabletButtonFunc(NULL);
    glutTimerFunc(100, NULL, 1); ... */
    glutMainLoop();
    //enter main loop and process events
    return 0;
}