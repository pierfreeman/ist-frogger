//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Trapeze.h"
#include <GLUT/glut.h>

Trapeze::Trapeze( Vector kp, float H, float BW, float SW, float D)
{
    middlepoint = kp;
    vertexcoord = new Vector[8]; // vector with all vertex positions
    h=H/2;
    bw=BW/2;
    sw=SW/2;
    d=D/2;

    vertexcoord[0]= Vector(kp.x + bw, kp.y - d, kp.z - h);
    vertexcoord[1]= Vector(kp.x + sw, kp.y - d, kp.z + h);
    vertexcoord[2]= Vector(kp.x + sw, kp.y + d, kp.z + h);
    vertexcoord[3]= Vector(kp.x + bw, kp.y + d, kp.z - h);
    vertexcoord[4]= Vector(kp.x - bw, kp.y - d, kp.z - h);
    vertexcoord[5]= Vector(kp.x - sw, kp.y - d, kp.z + h);
    vertexcoord[6]= Vector(kp.x - sw, kp.y + d, kp.z + h);
    vertexcoord[7]= Vector(kp.x - bw, kp.y + d, kp.z - h);

    // 3sz�gek (laponk�nt 2 )
    AddTriangle( Triangle(vertexcoord[0], vertexcoord[1], vertexcoord[2], Vector(1,0,1), Vector(1,0,1), Vector(1,0,1)));//Obliquo
    AddTriangle( Triangle(vertexcoord[0], vertexcoord[2], vertexcoord[3], Vector(1,0,1), Vector(1,0,1), Vector(1,0,1)));//Obliquo
    AddTriangle( Triangle(vertexcoord[0], vertexcoord[1], vertexcoord[4], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
    AddTriangle( Triangle(vertexcoord[1], vertexcoord[4], vertexcoord[5], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
    AddTriangle( Triangle(vertexcoord[1], vertexcoord[2], vertexcoord[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
    AddTriangle( Triangle(vertexcoord[2], vertexcoord[6], vertexcoord[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
    AddTriangle( Triangle(vertexcoord[4], vertexcoord[5], vertexcoord[7], Vector(-1,0,1), Vector(-1,0,1), Vector(-1,0,1)));//Obliquo
    AddTriangle( Triangle(vertexcoord[5], vertexcoord[6], vertexcoord[7], Vector(-1,0,1), Vector(-1,0,1), Vector(-1,0,1)));//Obliquo
    AddTriangle( Triangle(vertexcoord[0], vertexcoord[4], vertexcoord[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
    AddTriangle( Triangle(vertexcoord[0], vertexcoord[3], vertexcoord[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
    AddTriangle( Triangle(vertexcoord[2], vertexcoord[6], vertexcoord[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));
    AddTriangle( Triangle(vertexcoord[2], vertexcoord[3], vertexcoord[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));

    //a=A; b=B; c=C;

}

Trapeze::Trapeze(){}

// kirajzol� fv
void Trapeze::Draw()
{

    //glDisable(GL_TEXTURE_2D); glEnable(GL_NORMALIZE);
    glEnable(GL_NORMALIZE);
    glBegin(GL_TRIANGLES);

    // 3sz�genk�nt rajzol
    for(int i = 0; i<numtri; i++)
    {
        glNormal3f(halo[i].n1.x, halo[i].n1.y, halo[i].n1.z);
        glVertex3f(halo[i].p1.x, halo[i].p1.y, halo[i].p1.z);
        glVertex3f(halo[i].p2.x, halo[i].p2.y, halo[i].p2.z);
        glVertex3f(halo[i].p3.x, halo[i].p3.y, halo[i].p3.z);
    }
    glEnd();
}
