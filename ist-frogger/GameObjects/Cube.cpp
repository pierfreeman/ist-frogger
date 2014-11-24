//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Cube.h"
#include <GLUT/glut.h>

Cube::Cube( Vector kp, float A, float B, float C)
{
    middlepoint = kp;
    csucsok = new Vector[8]; // cs�csok t�mmbje ( fenti lapon majd lentin )
    a=A/2; b=B/2; c=C/2;

    csucsok[0]= Vector(kp.x + a, kp.y - b, kp.z - c);
    csucsok[1]= Vector(kp.x + a, kp.y - b, kp.z + c);
    csucsok[2]= Vector(kp.x + a, kp.y + b, kp.z + c);
    csucsok[3]= Vector(kp.x + a, kp.y + b, kp.z - c);
    csucsok[4]= Vector(kp.x - a, kp.y - b, kp.z - c);
    csucsok[5]= Vector(kp.x - a, kp.y - b, kp.z + c);
    csucsok[6]= Vector(kp.x - a, kp.y + b, kp.z + c);
    csucsok[7]= Vector(kp.x - a, kp.y + b, kp.z - c);

    // 3sz�gek (laponk�nt 2 )
    AddTriangle( Triangle(csucsok[0], csucsok[1], csucsok[2], Vector(1,0,0), Vector(1,0,0), Vector(1,0,0)));
    AddTriangle( Triangle(csucsok[0], csucsok[2], csucsok[3], Vector(1,0,0), Vector(1,0,0), Vector(1,0,0)));
    AddTriangle( Triangle(csucsok[0], csucsok[1], csucsok[4], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
    AddTriangle( Triangle(csucsok[1], csucsok[4], csucsok[5], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
    AddTriangle( Triangle(csucsok[1], csucsok[2], csucsok[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
    AddTriangle( Triangle(csucsok[2], csucsok[6], csucsok[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
    AddTriangle( Triangle(csucsok[4], csucsok[5], csucsok[7], Vector(-1,0,0), Vector(-1,0,0), Vector(-1,0,0)));
    AddTriangle( Triangle(csucsok[5], csucsok[6], csucsok[7], Vector(-1,0,0), Vector(-1,0,0), Vector(-1,0,0)));
    AddTriangle( Triangle(csucsok[0], csucsok[4], csucsok[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
    AddTriangle( Triangle(csucsok[0], csucsok[3], csucsok[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
    AddTriangle( Triangle(csucsok[2], csucsok[6], csucsok[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));
    AddTriangle( Triangle(csucsok[2], csucsok[3], csucsok[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));

    a=A; b=B; c=C;

}

Cube::Cube(){}

// kirajzol� fv
void Cube::Draw()
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
