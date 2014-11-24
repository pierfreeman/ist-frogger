//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Cylinder_H_
#define __Cylinder_H_

#include "Mesh.h"
#include <cmath>

class Cylinder : public Mesh
{
public:
    float r, length; // radius, length

    Cylinder();

    // USE THIS CONSTRUCTOR YOU NEED TO PASS THE MIDDLE POINT, THE RADIUS AND THE LENGTH OF THE CYLINDER
    Cylinder(Vector midPoint, float sug, float side);

    // drawing function
    void Draw();

};

#endif //__Cylinder_H_
