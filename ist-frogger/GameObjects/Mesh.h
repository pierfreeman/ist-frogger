//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Mesh_H_
#define __Mesh_H_

#include "Triangle.h"


class Mesh
{
public:
    Triangle * halo;
    int numtri;

public:

    //Constructor
    Mesh();

    void AddTriangle(Triangle t);
};


#endif //__Mesh_H_
