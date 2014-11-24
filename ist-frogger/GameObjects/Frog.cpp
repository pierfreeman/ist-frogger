//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Frog.h"
#include <GLUT/glut.h>

Frog::Frog(Vector a, Vector b){
    pos = a; velocity= b;
    size = 0.05;
    previous_pos = Vector(0,0,0);
    leg1 = Cube(Vector(0,0,0), 0.7, 0.2, 0.2);
    leg2 = Cube(Vector(0,0,0), 0.7, 0.2, 0.2);
    leg3 = Cube(Vector(0,0,0), 0.7, 0.2, 0.2);
    leg4 = Cube(Vector(0,0,0), 0.7, 0.2, 0.2);
    body = Cube(Vector(0,0,0), 1, 1, 1);
    head=Sphere(Vector(0,0,0));
    frogDirection = 0;
}


void Frog::Draw()
{
    glColor3f(0.0f, 0.5f, 0.0f);

    //Definition of the material parameters
    GLfloat material_Ka[] = {0.00, 0.1, 0.00, 1.00}; //ambient
    GLfloat material_Kd[] = {0.1, 0.3, 0.1, 1.00}; //diffusion
    GLfloat material_Ks[] = {0.4, 1.00, 0.4, 1.00}; //specular
    GLfloat material_Ke[] = {0.00, 0.00, 0.00, 0.00}; //emission
    GLfloat material_Se[] = {128}; //shineness

    //Setting the materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_Se);

    glPushMatrix();

    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(frogDirection, 0, 0, 1);
    glScalef(size,size,size);
    //glutSolidCube(1);
    body.Draw();


    glPushMatrix();
    glTranslatef(0,0.7,0);
    //glutSolidSphere(0.3,10,10);
    head.Draw();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,0.45,0);
    glRotatef(-45,0,0,1);
    //glScalef(0.7,0.2,0.2);
    //glutSolidCube(1);
    leg1.Draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-0.45,0);
    glRotatef(45,0,0,1);
    // glScalef(0.7,0.2,0.2);
    // glutSolidCube(1);
    leg2.Draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,-0.45,0);
    glRotatef(-45,0,0,1);
    //glScalef(0.7,0.2,0.2);
    //glutSolidCube(1);
    leg3.Draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,0.45,0);
    glRotatef(45,0,0,1);
    // glScalef(0.7,0.2,0.2);
    // glutSolidCube(1);
    leg4.Draw();
    glPopMatrix();

    glPopMatrix();
}
