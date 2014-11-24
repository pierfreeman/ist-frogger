//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Rectangle_H_
#define __Rectangle_H_

#include "Color.h"


class Rectangle
{
public:
    float M = 20;
    float N = 20;
    float width;
    float height;
    Color szin;

    Rectangle();

    Rectangle( float width_, float height_, Color color);

    void Draw();
};


#endif //__Rectangle_H_
