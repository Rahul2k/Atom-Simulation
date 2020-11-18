#include <iostream>
#include <algorithm>
#include <GL/glut.h>
#include <vector>
#include <cmath>

struct Electron {

    float x = 25;
    float y = 0;
    float r=2;
    float vx;
    float vy;
    float m=1;
    float color[3] = {0,0,1.0};
    int n=1;
};

struct Proton {

    float x = 0;
    float y = 0;
    float r=5;
    float vx;
    float vy;
    float m=2000;
    float color[3] = {1.0,1.0,0};
};


void timer(int = 0);
void display();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);
bool inside(int x, int y, int x1, int y1, int x2, int y2);

float theta = 0;
int Mx, My, WIN;
bool PRESSED_LEFT = false, PRESSED_RIGHT = false, PRESSED_MIDDLE = false, SPEED_PARTICLES = false;
int z = 1 ;

Proton p ;
Electron e ;

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    WIN = glutCreateWindow("Neils Bohr Atomic Model");

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250.0, 250.0, -250.0, 250.0, 0, 1);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    timer();

    glutMainLoop();
    return 0;
}

void timer(int) {

    display();

    e.x = p.x + 25*(e.n*e.n)*cos(theta)/(z);
    e.y = p.y + 25*(e.n*e.n)*sin(theta)/(z);

    theta += 0.1*(z)/e.n ;
    if(theta>=2*M_PI) theta = 0.1*(z)/e.n ;

    glutTimerFunc(5, timer, 0);

}

bool inside(int x, int y, int x1, int x2, int y1, int y2) {

    if(x>=x1 and x<=x2) {
        if(y>=y1 and y<=y2)
            return true;
    }

    return false ;

}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5) ;
    glBegin(GL_POINT) ;

    glColor3f(1,1,1) ;
    for(float a = 0; a < 2*M_PI; a+=1)
        glVertex2f(20*cos(a), 20*sin(a));

    glEnd() ;

    glBegin(GL_POLYGON);
    glColor3f(p.color[0], p.color[1], p.color[2]);

    for(float a = 0; a < 2*M_PI; a+=0.2)
        glVertex2f(p.r*cos(a) + p.x, p.r*sin(a) + p.y);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(e.color[0], e.color[1], e.color[2]);

    for(float a = 0; a < 2*M_PI; a+=0.2)
        glVertex2f(e.r*cos(a) + e.x, e.r*sin(a) + e.y);

    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(1,1,1);
    glVertex2f(-230,30);
    glVertex2f(-220,5);
    glVertex2f(-240,5);

    glVertex2f(-240,-5);
    glVertex2f(-220,-5);
    glVertex2f(-230,-30);

    glEnd();


    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

    Mx = x - 250;
    My = y - 250;

    if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and inside(Mx,My,-240,-220,-30,-5)) {
        z = (z==4?4:++z);
    }

    else if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and inside(Mx,My,-240,-220,5,30)) {
        z = (z>1?--z:1);
    }

    else if(button == GLUT_MIDDLE_BUTTON and state == GLUT_DOWN) {
        e.n = 1;
        z=1;
    }
}

void keyboard(unsigned char key, int x, int y) {

    if(key>'0' and key<='9') {
        e.n = key-'0' ;
    }

    else if(key==27){
        glutDestroyWindow(WIN);
        exit(0);
    }
}
