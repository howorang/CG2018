#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>

class Camera {
private:
    static double xpos, ypos, zpos, xrot, yrot;
public:

    void static keyboard(unsigned char key, int x, int y) {
        if (key == 'w') {
            double xrotrad, yrotrad;
            yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);
            xpos += sin(yrotrad);
            zpos -= cos(yrotrad);
            ypos -= sin(xrotrad);
        }

        if (key == 's') {
            double xrotrad, yrotrad;
            yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);
            xpos -= sin(yrotrad);
            zpos += cos(yrotrad);
            ypos += sin(xrotrad);
        }

        if (key == 'd') {
            double yrotrad;
            yrotrad = (yrot / 180 * 3.141592654f);
            xpos += cos(yrotrad) * 0.2;
            zpos += sin(yrotrad) * 0.2;
        }

        if (key == 'a') {
            double yrotrad;
            yrotrad = (yrot / 180 * 3.141592654f);
            xpos -= cos(yrotrad) * 0.2;
            zpos -= sin(yrotrad) * 0.2;
        }

        if (key == 'p') {
            ypos += 1;
        }

        if (key == 'o') {
            ypos -= 1;
        }
    }

    void static SpecialInput(int key, int x, int y) {
        switch (key) {
            case GLUT_KEY_UP:
                xrot -= 1;
                break;
            case GLUT_KEY_DOWN:
                xrot += 1;
                break;
            case GLUT_KEY_LEFT:
                yrot -= 1;
                break;
            case GLUT_KEY_RIGHT:
                yrot += 1;
                break;
        }
    }

    void camera(void) {
        glRotated(xrot, 1.0, 0.0, 0.0);
        glRotated(yrot, 0.0, 1.0, 0.0);
        glTranslated(-xpos, -ypos, -zpos);
    }

    Camera() {
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(SpecialInput);
    }
};

double Camera::xpos = 0, Camera::ypos = 0, Camera::zpos = 0, Camera::xrot = 0, Camera::yrot = 0;

#endif
