//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Rectangle.h"
#include <GLUT/glut.h>

Rectangle::Rectangle(){ width = 0; height = 0;}

Rectangle::Rectangle( float width_, float height_, Color color)
{
    width = width_;
    height = height_;
    szin = color;

}

void Rectangle::Draw()
{
    glBegin(GL_QUADS);
    glColor3f(szin.r, szin.g, szin.b);
    for(float u=0; u<1;u+=1.0/N)
        for( float v = 0; v<1; v+= 1.0/M)
        {
            float uc = u, vc = v;
            glTexCoord2f(uc,vc);
            glNormal3f(0, 0, 1);
            glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
            uc = u+1.0/N;
            glTexCoord2f(uc,vc);
            glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
            vc = v+1.0/M;
            glTexCoord2f(uc,vc);
            glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
            uc=u;
            glTexCoord2f(uc,vc);
            glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
        }

    glEnd();
}