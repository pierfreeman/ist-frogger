//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Cylinder.h"
#include <GLUT/glut.h>

Cylinder::Cylinder(){}

Cylinder::Cylinder(Vector midPoint, float sug, float side)
{
    float alfa = (3.14*3.6)/180; // 100 3sz�gre bontva az alapk�rt egy szelet k�z�pponti sz�ge (folyamatosan n�)
    float aktz= midPoint.z + sug; // alap�llapot x =side fele minuszban, y = 0, z=1(sug�r)  eltolva a k�z�pponttal
    float aktx= midPoint.x - (side /2);
    float akty = midPoint.y;
    float x,y,z;

    r = sug;
    length = side /2;

    // h�romsz�gh�l� sz�m�t�sa
    for( int i =0; i< 102; i++)
    {
        z = midPoint.z-r* cos(alfa);
        y = midPoint.y-r* sin(alfa);
        x= midPoint.x - length;

        // fed�lapokon a h�romsz�gszeletek (lenti majd fenti)
        AddTriangle( Triangle(Vector(x, midPoint.y, midPoint.z), Vector(x,y,z), Vector(aktx,akty,aktz),Vector(-1,0,0), Vector(-1,0,0), Vector(-1,0,0)));
        AddTriangle( Triangle(Vector(x+ side, midPoint.y, midPoint.z), Vector(x+ side,y,z), Vector(aktx+ side,akty,aktz) , Vector(1,0,0), Vector(1,0,0), Vector(1,0,0)));
        // oldallapi t�glalap 2 h�romsz�gre bontva
        AddTriangle( Triangle(Vector(x,y,z), Vector(aktx,akty,aktz), Vector(x+ side,y,z),Vector(0,y,z), Vector(0,akty,aktz), Vector(0,y,z)));
        AddTriangle( Triangle(Vector(aktx,akty,aktz), Vector(x+ side,y,z), Vector(aktx+ side,akty,aktz), Vector(0,akty,aktz), Vector(0,y,z), Vector(0,akty,aktz)));

        aktz=z; // eddigi �llapot ment�se
        akty=y;


        alfa = alfa + (3.14*3.6)/180; // sz�g n�vel�se
    }
}

// kirajzol� f�ggv�ny
void Cylinder::Draw()
{
    glEnable(GL_NORMALIZE);
    glBegin(GL_TRIANGLES);

    // v�gigmegy a 3sz�gh�l�n �s kirajzolja 3sz�genk�nt
    for(int i = 0; i<numtri; i++)
    {
        glNormal3f(halo[i].n1.x, halo[i].n1.y, halo[i].n1.z);
        glVertex3f(halo[i].p1.x, halo[i].p1.y, halo[i].p1.z);
        glNormal3f(halo[i].n2.x, halo[i].n2.y, halo[i].n2.z);
        glVertex3f(halo[i].p2.x, halo[i].p2.y, halo[i].p2.z);
        glNormal3f(halo[i].n3.x, halo[i].n3.y, halo[i].n3.z);
        glVertex3f(halo[i].p3.x, halo[i].p3.y, halo[i].p3.z);
    }
    glEnd();
}
