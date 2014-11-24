//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Triangle.h"

// Constructor with normal vectors calculated
Triangle::Triangle(Vector a, Vector b, Vector c)
{
    p1=a;
    p2=b;
    p3=c;
    n1=Vector(0,0,0);
    n2=Vector(0,0,0);
    n3=Vector(0,0,0);
}

//Constructor with normal vectors passed as input
Triangle::Triangle(Vector a, Vector b, Vector c, Vector d, Vector e, Vector f)
{
    p1=a;
    p2=b;
    p3=c;
    n1=d;
    n2=e;
    n3=f;
}
