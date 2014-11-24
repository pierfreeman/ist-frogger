//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Car_H_
#define __Car_H_

#include "SceneObject.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Trapeze.h"


class Car : public SceneObject
{
public:
    Cylinder wheel1;
    Cylinder wheel2;
    Cylinder wheel3;
    Cylinder wheel4;

    Cube body;
    Trapeze top;

    Car(Vector a, Vector b);

    void Animate(long dt);

    virtual void Draw();
};


#endif //__Car_H_
