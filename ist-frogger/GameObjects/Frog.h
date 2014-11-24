//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Frog_H_
#define __Frog_H_

#include "SceneObject.h"
#include "Cube.h"
#include "Sphere.h"

class Frog : public SceneObject
{
    float size;

public:
    float frogDirection;
    bool previous_isItOnATrunk;
    bool isItOnATrunk;
    Vector previous_pos;
    Cube body;
    Cube leg1;
    Cube leg2;
    Cube leg3;
    Cube leg4;
    Sphere head;

    Frog(Vector a, Vector b);

    virtual void Draw();

};

#endif //__Frog_H_