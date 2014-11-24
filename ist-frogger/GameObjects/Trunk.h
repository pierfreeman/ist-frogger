//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Trunk_H_
#define __Trunk_H_

#include "SceneObject.h"
#include "Cube.h"

class Trunk : public SceneObject
{

public:
    float size;
    float length;

    Cube trunk;

    Trunk(Vector a, Vector b, float s, float l);

    void Animate(long dt);

    void Draw();
};


#endif //__Trunk_H_
