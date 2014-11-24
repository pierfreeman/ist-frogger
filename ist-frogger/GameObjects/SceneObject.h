//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __SceneObject_H_
#define __SceneObject_H_

#include "Vector.h"

class SceneObject
{
public:
    Vector pos;
    Vector velocity;

    SceneObject();
    SceneObject(Vector p, Vector v);

public:
    void Animate(long dt);

    virtual void Draw();
};

#endif //__SceneObject_H_