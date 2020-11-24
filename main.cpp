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
    float color[3] = {1,1,1};
    int n=1;
};

struct Proton {

    float x = 0;
    float y = 0;
    float r=5;
    float vx;
    float vy;
    float m=2000;
    float color[3] = {1,1,0};
};

// The mass and size ratios are with respect to the original ratio of electron to the nucleus.


void init() ;
int min(int,int) ;
void timer(int = 0);
void display();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);
bool inside(int x, int y, int x1, int y1, int x2, int y2);
void color_equals(float[], float[]) ;

float theta = 0;
int Mouse_x, Mouse_y, WIN;

// Used for mouse callbacks
bool PRESSED_LEFT = false, PRESSED_RIGHT = false, PRESSED_MIDDLE = false;

// Atomic Number
int z = 1 ;

float absorbed[] = {1.0,1.0,1.0};
float emmited[] = {1.0,1.0,1.0};

//Color Codings
float ultra_violet[] = {0.0,0.0,0.0};
float infra_red[] = {0.5,0.0,0.0} ;
float violet[] = {1.0,0.0,0.5};
float indigo[] = {0.25,0.0,1.0};
float blue[] = {0.0,0.0,1.0};
float green[] = {0.0,1.0,0.0};
float yellow[] = {1.0,1.0,0.0};
float orange[] = {1.0,0.5,0.0};
float red[] = {1.0,0.0,0.0};
float white[] = {1.0,1.0,1.0};
float energy = 0;

// Nucleus and electron
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

void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0) ;
}

void timer(int) {

    display();

    // Position and velocity update
    e.x = p.x + 25*(e.n*e.n)*cos(theta)/(z);
    e.vx = 25*(e.n*e.n)*cos(theta)/(z);
    e.y = p.y + 25*(e.n*e.n)*sin(theta)/(z);
    e.vy = 25*(e.n*e.n)*cos(theta)/(z);

    // Adjust the theta value manually to change the speed if you want, higher theta means more speed
    theta += 0.1*(z)/e.n ;
    if(theta>=2*M_PI) theta = 0.1*(z)/e.n ;

    // Radiation Emitted
    if(energy<0) {

        color_equals(absorbed,white) ;
        float lambda = 12400.0/(abs(energy));

        if(lambda<=3600) {
            color_equals(emmited,ultra_violet);
        }

        else if(lambda<=4000) {
            color_equals(emmited,violet);
        }

        else if(lambda<=4600) {
            color_equals(emmited,indigo);
        }

        else if(lambda<=5000) {
            color_equals(emmited,blue);
        }

        else if(lambda<=5500) {
            color_equals(emmited,green);
        }

        else if(lambda<=6200) {
            color_equals(emmited,yellow);
        }

        else if(lambda<=6800) {
            color_equals(emmited,orange);
        }

        else if(lambda<=7600) {
            color_equals(emmited,red);
        }

        else {
            color_equals(emmited,infra_red);
        }
    }

    // Radiation Absorbed
    else if(energy>0) {

        color_equals(emmited,white) ;
        float lambda = 12400/abs(energy);

        if(lambda<=3600) {
            color_equals(absorbed,ultra_violet);
        }

        else if(lambda<=4000) {
            color_equals(absorbed,violet);
        }

        else if(lambda<=4600) {
            color_equals(absorbed,indigo);
        }

        else if(lambda<=5000) {
            color_equals(absorbed,blue);
        }

        else if(lambda<=5500) {
            color_equals(absorbed,green);
        }

        else if(lambda<=6200) {
            color_equals(absorbed,yellow);
        }

        else if(lambda<=6800) {
            color_equals(absorbed,orange);
        }

        else if(lambda<=7600) {
            color_equals(absorbed,red);
        }

        else {
            color_equals(absorbed,infra_red);
        }
    }

    // reset
    energy = 0;

    glutTimerFunc(5, timer, 0);
}

bool inside(int x, int y, int x1, int x2, int y1, int y2) {

    if(x>=x1 and x<=x2) {
        if(y>=y1 and y<=y2)
            return true;
    }

    return false ;

}

void color_equals(float col_1[], float col_2[]) {

    col_1[0] = col_2[0] ;
    col_1[1] = col_2[1] ;
    col_1[2] = col_2[2] ;
}

int min(int a, int b) {

    if(a<b) return a;
    else return b ;
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5) ;
    glBegin(GL_POINT) ;

    glColor3f(1,1,0) ;
    glVertex2f(-50,-50);
    glVertex2f(50,50);
    glEnd() ;

    glBegin(GL_POLYGON);
    glColor3f(p.color[0], p.color[1], p.color[2]);

    for(float a = 0; a < 2*M_PI; a+=0.2)
        glVertex2f(p.r*cos(a) + p.x, p.r*sin(a) + p.y);

    glEnd();

    // particle drawing
    glBegin(GL_POLYGON);
    glColor3f(e.color[0], e.color[1], e.color[2]);

    for(float a = 0; a < 2*M_PI; a+=0.2)
        glVertex2f(e.r*cos(a) + e.x, e.r*sin(a) + e.y);

    glEnd();

    // pointers drawing
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,1);
    glVertex2f(-230,30);
    glVertex2f(-220,5);
    glVertex2f(-240,5);

    glVertex2f(-240,-5);
    glVertex2f(-220,-5);
    glVertex2f(-230,-30);

    glEnd();

    // Emitted box drawing
    glBegin(GL_POLYGON);

    glColor3f(absorbed[0],absorbed[1],absorbed[2]);
    glVertex2f(220,50);
    glVertex2f(240,50);
    glVertex2f(240,20);
    glVertex2f(220,20);

    glEnd() ;

    // Absorbed box drawing
    glBegin(GL_POLYGON) ;

    glColor3f(emmited[0],emmited[1],emmited[2]);
    glVertex2f(220,-20);
    glVertex2f(240,-20);
    glVertex2f(240,-50);
    glVertex2f(220,-50);

    glEnd();

    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

    Mouse_x = x - 250;
    Mouse_y = y - 250;

    if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and inside(Mouse_x,Mouse_y,-240,-220,-30,-5)) {
        z = (z==4?4:++z);
    }

    else if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and inside(Mouse_x,Mouse_y,-240,-220,5,30)) {
        z = (z>1?--z:1);
    }

    // Click middle mouse button to reset to Hydrogen Atom
    else if(button == GLUT_MIDDLE_BUTTON and state == GLUT_DOWN) {

        e.n = 1;
        z=1;
        color_equals(emmited,white);
        color_equals(absorbed,white);
    }
}

void keyboard(unsigned char key, int x, int y) {

    // change orbit number using keys
    int initial = e.n ;

    if(key>'0' and key<='9') {

        // To avoid program failure
        switch(z) {

            case 1 : e.n = min(3,e.n = key-'0') ;
                     break ;

            case 2 : e.n = min(5,e.n = key-'0') ;
                     break ;

            case 3 : e.n = min(6,e.n = key-'0') ;
                     break ;

            case 4 : e.n = min(8,e.n = key-'0') ;
                     break ;
        }
    }

    else if(key==27){

        glutDestroyWindow(WIN);
        exit(0);
    }
    energy = 13.6*(1.0/float(((initial)*(initial))) - 1.0/float((e.n*e.n)))*z*z ;
}
