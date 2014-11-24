//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Trunk.h"
#include <GLUT/glut.h>
#include <random>

Trunk::Trunk(Vector a, Vector b, float s, float l) {
    pos = a;
    velocity= b;
    size = s;
    length = l;
    trunk = Cube(Vector(0,0,0), size, size, size);
}

void Trunk::Animate(long dt) {
    //Moving from left to right
    if(velocity.x > 0) {
        //reaches the right window limit
        if(pos.x >1.3) {
            pos.x = ((float(rand()) / float(RAND_MAX)) * 4) - 5;
            length = (float(rand()) / float(RAND_MAX) * 2) + 2;
            //velocity = random;
        }
    }
        //Moving from right to left
    else if (velocity.x < 0) {
        //reaches the left window limit
        if(pos.x < -1.3) {
            pos.x = (float(rand()) / float(RAND_MAX)) + 1;
            length = (float(rand()) / float(RAND_MAX) * 2) + 2;
            //velocity = random;
        }
    }
    pos += velocity*dt;
}

void Trunk::Draw()
{
    glColor3f(0.5f, 0.35f, 0.05f);

    //Definition of the material parameters
    GLfloat material_Ka[] = {0.03, 0.01, 0.01, 1.00}; //ambient
    GLfloat material_Kd[] = {0.12, 0.07, 0.06, 1.00}; //diffusion
    GLfloat material_Ks[] = {0.45, 0.4, 0.29, 1.00}; //specular
    GLfloat material_Ke[] = {0.00, 0.00, 0.00, 0.00}; //emission
    GLfloat material_Se[] = {100}; //shineness

    //Setting the materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_Se);


    glColor3f(0.5f, 0.35f, 0.05f);
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glScalef(length, 1.0f, 1.0f);
    trunk.Draw();
    glPopMatrix();
}
