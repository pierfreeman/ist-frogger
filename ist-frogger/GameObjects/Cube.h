//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Cube_H_
#define __Cube_H_

#include "Mesh.h"


class Cube : public Mesh
{
public:
    Vector middlepoint;
    float a,b,c; // oldallengthak
    Vector * csucsok;

    // USE THIS CONSTRUCTOR YOU NEED TO PASS THE MIDDLE POINT AND THE 3 SIDE LENGTH
    Cube( Vector kp, float A, float B, float C);

    Cube();

    // kirajzol� fv
    void Draw();

};


#endif //__Cube_H_
