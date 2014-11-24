//
// Created by Piercarlo Serena on 24/11/14.
//

#include "SceneObject.h"

SceneObject::SceneObject(){}
SceneObject::SceneObject(Vector p, Vector v)
{
    pos = Vector(p.x,p.y,p.z);
    velocity = Vector(v.x,v.y,v.z);
}

void SceneObject::Animate(long dt)
{
    pos+= velocity*dt;
}

void SceneObject::Draw(){}
