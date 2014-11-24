//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Trapezio_H_
#define __Trapezio_H_

#include "Mesh.h"

class Trapeze : public Mesh
{
public:
    Vector middlepoint;
    float h, bw, sw, d;	//height(z), bigger width(x), smaller width(x) and depth(y)
    Vector * vertexcoord;

    // USE THIS CONSTRUCTOR YOU NEED TO PASS THE MIDDLE POINT AND THE 3 SIDE LENGTH
    Trapeze( Vector kp, float H, float BW, float SW, float D);

    Trapeze();

    // kirajzol� fv
    void Draw();

};

#endif //__Trapezio_H_
