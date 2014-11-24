//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Car.h"
#include <GLUT/glut.h>
#include <random>

Car::Car(Vector a, Vector b)
{
    pos = a; velocity= b;
    wheel1 =Cylinder((0, 0, 0), 0.01f, 0.004f);
    wheel2 =Cylinder((0, 0, 0), 0.01f, 0.004f);
    wheel3 =Cylinder((0, 0, 0), 0.01f, 0.004f);
    wheel4 =Cylinder((0, 0, 0), 0.01f, 0.004f);

    body = Cube(Vector(0,0,0), 0.11, 0.06, 0.02);
    top = Trapeze(Vector(0,0,0), 0.02, 0.07, 0.03, 0.06);
}

void Car::Animate(long dt) {
    //double random = rand()*0.1;

    //std::cout << random << + "\n  ";

    //Moving from left to right
    if(velocity.x > 0) {
        //reaches the right window limit
        if(pos.x >1.1)
            pos.x = ((float(rand()) / float(RAND_MAX)) * 4) - 5;
        //velocity = random;
    }
        //Moving from right to left
    else if (velocity.x < 0) {
        //reaches the left window limit
        if(pos.x < -1.1)
            pos.x = (float(rand()) / float(RAND_MAX)) + 1;
        //velocity = random;
    }
    pos += velocity*dt;
    //acceleration = velocity/(10000*dt);
    //velocity += acceleration;
}

void Car::Draw()
{

    glColor3f(1.0f, 1.0f, 1.0f);

    //Body
    glPushMatrix();

    glTranslatef(pos.x,pos.y,pos.z);
    //glRotatef(-90,0,0,1);

    //Definition of the material parameters
    GLfloat material_Ka[] = {0.01, 0.01, 0.01, 1.00}; //ambient
    GLfloat material_Kd[] = {0.2, 0.2, 0.2, 1.00}; //diffusion
    GLfloat material_Ks[] = {0.4, 0.4, 0.4, 1.00}; //specular
    GLfloat material_Ke[] = {0.00, 0.00, 0.00, 0.00}; //emission
    GLfloat material_Se[] = {128}; //shineness

    //Setting the materials
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_Se);

    if (velocity.x > 0)
        glRotatef(180.0f, 0.0, 0.0, 1.0);
    //Wheel1
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(90,0,0,1);
    glTranslatef(-0.03,-0.03,-0.01);
    wheel1.Draw();
    glPopMatrix();

    //Wheel2
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(90,0,0,1);
    glTranslatef(0.03,-0.03,-0.01);
    wheel2.Draw();
    glPopMatrix();

    //Wheel3
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(90,0,0,1);
    glTranslatef(0.03,0.03,-0.01);
    wheel3.Draw();
    glPopMatrix();

    //Wheel4
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(90,0,0,1);
    glTranslatef(-0.03,0.03,-0.01);
    wheel4.Draw();
    glPopMatrix();

    //Body Car
    glColor3f(0.0664f, 0.539f, 0.129f);
    //Definition of the material parameters
    GLfloat materialBody_Ka[] = {0.05, 0.01, 0.01, 1.00}; //ambient
    GLfloat materialBody_Kd[] = {0.3, 0.1, 0.1, 1.00}; //diffusion
    GLfloat materialBody_Ks[] = {1.0, 0.3, 0.3, 1.00}; //specular
    GLfloat materialBody_Ke[] = {0.00, 0.00, 0.00, 0.00}; //emission
    GLfloat materialBody_Se[] = {128}; //shineness

    //Setting the materials
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialBody_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialBody_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialBody_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialBody_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialBody_Se);
    body.Draw();

    //top of the car
    glPushMatrix();
    glColor3f(0.0429f, 0.6875f, 0.129f);
    //Definition of the material parameters
    GLfloat materialTop_Ka[] = {0.05, 0.01, 0.01, 1.00}; //ambient
    GLfloat materialTop_Kd[] = {0.2, 0.05, 0.05, 1.00}; //diffusion
    GLfloat materialTop_Ks[] = {0.8, 0.4, 0.4, 1.00}; //specular
    GLfloat materialTop_Ke[] = {0.00, 0.00, 0.00, 0.00}; //emission
    GLfloat materialTop_Se[] = {128}; //shineness

    //Setting the materials
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialTop_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialTop_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialTop_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialTop_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialTop_Se);
    glTranslatef(0.01,0.0,0.02);
    top.Draw();
    glPopMatrix();

    glPopMatrix();

}
