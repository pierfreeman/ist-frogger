//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Sphere_H_
#define __Sphere_H_

#include "Vector.h"

class Sphere
{
public:
    Vector kp;
    float r;

    Sphere();

    Sphere(Vector kozep);

    void Draw();

    void belsoDraw();

};


#endif //__Sphere_H_
