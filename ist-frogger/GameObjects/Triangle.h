//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Triangle_H_
#define __Triangle_H_

#include "Vector.h"


class Triangle
{
public:
    Vector p1; //vertex
    Vector p2;
    Vector p3;
    Vector n1; //vertex's normals
    Vector n2;
    Vector n3;

public: Triangle(){}
    // Constructor with normal vectors calculated
    Triangle(Vector a, Vector b, Vector c);

    // Constructor with normal vectors passed as input
    Triangle(Vector a, Vector b, Vector c, Vector d, Vector e, Vector f);
};


#endif //__Triangle_H_
