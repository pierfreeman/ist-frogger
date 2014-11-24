//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Mesh.h"

Mesh::Mesh()
{
    halo = new Triangle[1000];
    numtri =0;
}

void Mesh::AddTriangle(Triangle t)
{
    halo[numtri]= t;
    numtri++;
}