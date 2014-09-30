// Frogger.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

class Car
{
    float velocity;
    float posx;
    float posy;
    float size;
    //	REctangle wheel1;
    
    
public:
    Car()
    {
        velocity = 0.1;
        posx = -1.1;
        posy = -0.5;
        size = 0.1;
    }
    void Animate(long dt)
    {
        if(posx >=1.1)
            posx = -1.1;
        else
            posx += velocity*dt/100.0;
    }
    
    void Draw()
    {
        /*		glPushMatrix();
         body.draw
         
         push
         translate
         wheel1.draw
         pop
         
         push
         translate
         wheel2.draw
         pop
         
         pop
         */
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex3f (posx-size, posy-size, 0.0f);
        glVertex3f (posx+size, posy-size, 0.0f);
        glVertex3f (posx+size, posy+size, 0.0f);
        glVertex3f (posx-size, posy+size, 0.0f);
        glEnd();
    }
    
};


Car car;

long time = 0;

void reshape( int w, int h) {
    float xmin = -1., xmax = 1., ymin = -1., ymax = 1.;
    float ratio = (xmax - xmin) / (ymax - ymin);
    float aspect = (float) w / h;
    if ( aspect > ratio )
        glViewport( (w-h*ratio)/2, 0, h*ratio, h);
    else
        glViewport( 0, (h-w/ratio)/2, w, w/ratio);
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D( xmin, xmax, ymin, ymax);
}

void DrawBackGround()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f (-1.0f, -1.0f, 0.0f);
    glVertex3f (1.0f, -1.0f, 0.0f);
    glVertex3f (1.0f, -0.8f, 0.0f);
    glVertex3f (-1.0f, -0.8f, 0.0f);
    glEnd();
    
    glColor3f(0.8f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f (-1.0f, -0.8f, 0.0f);
    glVertex3f (1.0f, -0.8f, 0.0f);
    glVertex3f (1.0f, -0.2f, 0.0f);
    glVertex3f (-1.0f, -0.2f, 0.0f);
    glEnd();
    
    glColor3f(0.6f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f (-1.0f, -0.2f, 0.0f);
    glVertex3f (1.0f, -0.2f, 0.0f);
    glVertex3f (1.0f, -0.0f, 0.0f);
    glVertex3f (-1.0f, -0.0f, 0.0f);
    glEnd();
    
    
    glColor3f(0.4f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f (-1.0f, 0.0f, 0.0f);
    glVertex3f (1.0f, 0.0f, 0.0f);
    glVertex3f (1.0f, 0.6f, 0.0f);
    glVertex3f (-1.0f, 0.6f, 0.0f);
    glEnd();
    
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f (-1.0f, 0.6f, 0.0f);
    glVertex3f (1.0f, 0.6f, 0.0f);
    glVertex3f (1.0f, 0.8f, 0.0f);
    glVertex3f (-1.0f, 0.8f, 0.0f);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f (-1.0f, 0.8f, 0.0f);
    glVertex3f (1.0f, 0.8f, 0.0f);
    glVertex3f (1.0f, 1.0f, 0.0f);
    glVertex3f (-1.0f, 1.0f, 0.0f);
    glEnd();
    
}

void onDisplay(void) {
    
    DrawBackGround();
    car.Draw();
    
    glFlush();
    
}

void animateWorld(long dt)
{
    car.Animate(dt);
    
    // Collosion detection
    glutPostRedisplay();
}

void onIdle()
{
    long actual_time = glutGet(GLUT_ELAPSED_TIME);
    long elapsed_time = actual_time- time;
    
    animateWorld(elapsed_time);
    
    time= actual_time;
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (50, 50);
    
    glutCreateWindow("Teste");
    
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(reshape);
    glutIdleFunc(onIdle);
    
    
    glutMainLoop();
    
}
