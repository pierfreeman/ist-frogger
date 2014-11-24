//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Sphere.h"
#include <GLUT/glut.h>
#include <cmath>

Sphere::Sphere(){}

Sphere::Sphere(Vector kozep)
{
    r=0.3;
    kp=kozep;
}

void Sphere::Draw()
{
    glPushMatrix();
    //glDisable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHTING);
    //glColor3f(1,0,0);
    for(int i=0; i<100; i++)
    {
        glTranslatef(kp.x, kp.y, kp.z);
        glRotatef(1.8*i,1,0,0 );
        glTranslatef(-kp.x,-kp.y, - kp.z);
        belsoDraw();

    }
    glPopMatrix();
    //glEnable(GL_LIGHTING);
    //glEnable(GL_TEXTURE_2D);
}

void Sphere::belsoDraw()
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(kp.x, kp.y, kp.z);
    for(int j=0; j<92; j++)
        glVertex3f(kp.x+ r*sin(4*j*3.14/180),kp.y, kp.z+ r*cos(4*j*3.14/180));
    glEnd();
}
