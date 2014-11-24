// Frogger.cpp : Defines the entry point for the console application.
//Group: 53

/*---------INCLUDES WINDOWS------------*/
//#include "stdafx.h"
//#include <stdlib.h>
//#include "glut.h"
//#include "math.h"
//#include <array>
//#include <random>
//#include <iostream>
//#include <conio.h>
//#include <Windows.h>
/*-------------------------------------*/


/*---------INCLUDES MAC----------------*/
#include <GLUT/glut.h>
#include <array>
#include <random>
#include <iostream>
#include <stdlib.h>
#include "river64.h"
#include "river2.h"

#include "Rectangle.h"
#include "SceneObject.h"
#include "Frog.h"
#include "Car.h"
#include "Trunk.h"

/*-------------------------------------*/

#define FROG_VELOCITY 0.0005f;

#ifndef USE_GLES
void glPrintString(void *font, const char *str)
{
int i,l = (int)strlen(str);

for(i=0; i<l; i++)
{
glutBitmapCharacter(font,*str++);
}
}
#endif

// Print an integer to the top left corner of the canvas
void DrawInt(int param)
{
glDisable(GL_TEXTURE_2D);
char buffer[80] = "";
sprintf(buffer, "%d", param);
glColor3f(1.0f, 0.0f, 0.0f);
glRasterPos2f(-0.68, 0.9);
glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
glEnable(GL_TEXTURE_2D);
}



float frogDirection = 0.0;



Frog frog(Vector(0,-0.9,0), Vector(0,0,0));

//------ARRAY MODELLING-------
//float velocityArray[10] = {0.0006, 0.00065, 0.0007, 0.00075, 0.0008, 0.00085, 0.0009, 0.00095, 0.0010, 0.00105};
float velocityArray[10] = {0.00015, 0.0002, 0.00025, 0.0003, 0.00035, 0.0004, 0.00045, 0.0005, 0.00055, 0.0006};

Rectangle bottomSidewalk = Rectangle(2,0.2,Color(0.839,0,0));
Rectangle street = Rectangle(2,0.6,Color(0,0,0));
Rectangle topSidewalk = Rectangle(2,0.25,Color(0.839,0,0));
Rectangle river = Rectangle(2,0.5, Color(0.035, 0.435, 0.89));
Rectangle leaves = Rectangle(2,0.15,Color(0.216, 0.678, 0.047));
Rectangle score = Rectangle(2,0.3,Color(0.035, 0.36, 0.024));

//Frogs for lives
Frog frogLive1(Vector(0.5, 0.92, 0), Vector(0,0,0));
Frog frogLive2(Vector(0.6, 0.92, 0), Vector(0,0,0));
Frog frogLive3(Vector(0.7, 0.92, 0), Vector(0,0,0));
Frog frogLive4(Vector(0.8, 0.92, 0), Vector(0,0,0));
Frog frogLive5(Vector(0.9, 0.92, 0), Vector(0,0,0));
Frog frogLiveArray[5] = { frogLive5, frogLive4, frogLive3, frogLive2, frogLive1 };

//message cube
Cube box = Cube(Vector(0,0,0), 1.8, 0.8, 0.0);

std::array<Car, 14> carArray = {
    *new Car(Vector(-1.1, -0.3, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-1.5, -0.3, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-2.0, -0.3, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-2.4, -0.3, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(1.1, -0.4, 0.03), Vector(-velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(1.6, -0.4, 0.03), Vector(-velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(2.1, -0.4, 0.03), Vector(-velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-1.1, -0.5, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-1.7, -0.5, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(1.1, -0.6, 0.03), Vector(-velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(1.6, -0.6, 0.03), Vector(-velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(1.9, -0.6, 0.03), Vector(-velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-1.1, -0.7, 0.03), Vector(velocityArray[0], 0.0, 0.0)),
    *new Car(Vector(-1.6, -0.7, 0.03), Vector(velocityArray[0], 0.0, 0.0))
};

std::array<Trunk, 11> trunkArray = {
    *new Trunk(Vector(-1.1, 0.5, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 2.0),
    *new Trunk(Vector(-1.7, 0.5, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 2.0),
    *new Trunk(Vector(-2.5, 0.5, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 3.0),
    *new Trunk(Vector(-2.3, 0.4, -0.04), Vector(-velocityArray[0], 0.0, 0.0), 0.1, 2.0),
    *new Trunk(Vector(-2.9, 0.4, -0.04), Vector(-velocityArray[0], 0.0, 0.0), 0.1, 3.0),
    *new Trunk(Vector(-0.5, 0.3, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 3.0),
    *new Trunk(Vector(1.5, 0.3, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 2.0),
    *new Trunk(Vector(2.1, 0.2, -0.04), Vector(-velocityArray[0], 0.0, 0.0), 0.1, 3.0),
    *new Trunk(Vector(2.9, 0.2, -0.04), Vector(-velocityArray[0], 0.0, 0.0), 0.1, 2.0),
    *new Trunk(Vector(-1.2, 0.1, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 3.0),
    *new Trunk(Vector(-1.7, 0.1, -0.04), Vector(velocityArray[0], 0.0, 0.0), 0.1, 2.0)
};

int velocityIndex = 0;
long gameTime = 0;
long actual_time = 0;
long elapsed_time = 0;
int cameramode = 1;
int lives = 5;
bool paused = false;
long timeAtReset = 0;
bool lockPaused = false;

//variables for checking if a key is being pressed or not
bool p_pressed = false;
bool a_pressed = false;
bool o_pressed = false;
bool q_pressed = false;
bool c_pressed = false;
bool l_pressed = false;
bool n_pressed = false;
bool h_pressed = false;
bool h_save = false;

//Definition of the six lightpoints positions
GLfloat light_pos0[] = {-0.7, -0.9, 1, 1.00};
GLfloat light_pos1[] = {0.7, -0.9, 1, 1, 1.00};
GLfloat light_pos2[] = {-0.7, -0.075, 1, 1.00};
GLfloat light_pos3[] = {0.7, -0.075, 1, 1.00};
GLfloat light_pos4[] = {-0.7, 0.7, 1, 1.00};
GLfloat light_pos5[] = {0.7, 0.7, 1, 1.00};
GLfloat *light_posFrog;
GLfloat *frog_spotlightDir;
GLfloat lmKa[] = {0.1, 0.1, 0.1, 1.0};

//Definition of the lightpoints parameters
GLfloat light_Ka[] = {0.0, 0.0, 0.0, 1.00}; //ambient
GLfloat light_Kd[] = {1.0, 1.0, 1.0, 1.00}; //diffusion
GLfloat light_Ks[] = {0.5, 0.5, 0.5, 1.00}; //specular
GLfloat attenuation = 2;

char gamemessage[80] = "Points:";

void reshape( int w, int h) {
	float xmin = -1., xmax = 1., ymin = -1., ymax = 1.;
	float ratio = (xmax - xmin) / (ymax - ymin);
	float aspect = (float) w / h; 
	if ( aspect > ratio )
	glViewport( (w-h*ratio)/2, 0, h*ratio, h);
	else
	glViewport( 0, (h-w/ratio)/2, w, w/ratio);
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D( xmin, xmax, ymin, ymax);
}

void DrawRoad() {

    GLfloat material_Ka[] = {0.2, 0.2, 0.2, 1.00}; //ambient
    GLfloat material_Kd[] = {0.4, 0.4, 0.4, 1.00}; //diffusion
    GLfloat material_Ks[] = {0.6, 0.6, 0.6, 1.00}; //specular
    GLfloat material_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material_Se[] = {20}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_Se);

	float countI = 0.0;
	float countJ = 0.0;
	for(int j=0; j<4; j++) {		//for each sections os the road 

		for(int i = 0; i<12; i++) {	//for multiple lines in the same row
	
			glColor3f(1.0f, 1.0f, 1.0f);
			glPushMatrix();		
				glTranslatef(-0.85+countI, -0.35+countJ, 0.0);
				glScalef(25, 1.0f, 1.0f);
				glutSolidCube(0.004);
			glPopMatrix();
			
			countI += 0.25f;
		}
		countJ-=0.1f;
		countI = 0.0f;
	}

	float aux = 0.0;
	for(int l=0; l<2; l++) {
		
		glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
			glTranslatef(0.0, -0.251-aux, 0.0);
			glScalef(200, 1.0f, 1.0f);
			glutSolidCube(0.01);
        glPopMatrix();
		aux = 0.5f;
	}
}

void DrawBackGround()
{

    //TODO: normal?

	glPushMatrix();
        GLfloat material0[] = {0.00, 0.00, 0.00, 1.00}; //ambient
        GLfloat material0_Se[] = {128}; //shineness
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material0);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material0);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material0);
        glMaterialfv(GL_FRONT, GL_EMISSION, material0);
        glMaterialfv(GL_FRONT, GL_SHININESS, material0_Se);
        glColor3f(0,0,0);
        glTranslatef(1.5,0,0);
        glScalef(1,3,3);
        glutSolidCube(1);
        glTranslatef(-3,0,0);
        glutSolidCube(1);
	glPopMatrix();
    
	//bottom sidewalk
    GLfloat material1_Ka[] = {0.05, 0.05, 0.05, 1.00}; //ambient
    GLfloat material1_Kd[] = {0.05, 0.05, 0.05, 1.00}; //diffusion
    GLfloat material1_Ks[] = {0.5, 0.5, 0.5, 1.00}; //specular
    GLfloat material1_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material1_Se[] = {10}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material1_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material1_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material1_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material1_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material1_Se);
    
    glPushMatrix();
    glTranslatef(0, -0.9, 0);
    bottomSidewalk.Draw();
    glPopMatrix();

    
    //Road
    GLfloat material2_Ka[] = {0.01, 0.01, 0.01, 1.00}; //ambient
    GLfloat material2_Kd[] = {0.005, 0.005, 0.005, 1.00}; //diffusion
    GLfloat material2_Ks[] = {0.5, 0.5, 0.5, 1.00}; //specular
    GLfloat material2_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material2_Se[] = {20}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material2_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material2_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material2_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material2_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material2_Se);

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    street.Draw();
    glPopMatrix();
 
    
	//top sidewalk

    GLfloat material3_Ka[] = {0.05, 0.05, 0.05, 1.00}; //ambient
    GLfloat material3_Kd[] = {0.05, 0.05, 0.05, 1.00}; //diffusion
    GLfloat material3_Ks[] = {0.5, 0.5, 0.5, 1.00}; //specular
    GLfloat material3_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material3_Se[] = {10}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material3_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material3_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material3_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material3_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material3_Se);

    glPushMatrix();
    glTranslatef(0, -0.075, 0);
    topSidewalk.Draw();
    glPopMatrix();

    
	//River
    GLfloat material4_Ka[] = {0.00, 0.00, 0.2, 1.00}; //ambient
    GLfloat material4_Kd[] = {0.3, 0.3, 0.7, 1.00}; //diffusion
    GLfloat material4_Ks[] = {0.4, 0.4, 1.0, 1.00}; //specular
    GLfloat material4_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material4_Se[] = {128}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material4_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material4_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material4_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material4_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material4_Se);

	glEnable(GL_TEXTURE_2D);

	GLuint texids;
	glGenTextures(1,&texids);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texids);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,64,32,0,GL_RGB,GL_UNSIGNED_BYTE, header_data);

    glPushMatrix();
    glTranslatef(0, 0.3, 0);
    river.Draw();
    glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//leafs?
    GLfloat material5_Ka[] = {0.00, 0.1, 0.00, 1.00}; //ambient
    GLfloat material5_Kd[] = {0.0, 0.2, 0.0, 1.00}; //diffusion
    GLfloat material5_Ks[] = {0.0, 0.7, 0.0, 1.00}; //specular
    GLfloat material5_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material5_Se[] = {70}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material5_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material5_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material5_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material5_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material5_Se);

    glPushMatrix();
    glTranslatef(0, 0.625, 0);
    leaves.Draw();
    glPopMatrix();

	//game points
    GLfloat material6_Ka[] = {0.00, 0.01, 0.00, 1.00}; //ambient
    GLfloat material6_Kd[] = {0.00, 0.1, 0.00, 1.00}; //diffusion
    GLfloat material6_Ks[] = {0.00, 0.6, 0.00, 1.00}; //specular
    GLfloat material6_Ke[] = {0.0, 0.0, 0.0, 0.00}; //emission
    GLfloat material6_Se[] = {128}; //shineness
    glMaterialfv(GL_FRONT, GL_AMBIENT, material6_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material6_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material6_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material6_Ke);
    glMaterialfv(GL_FRONT, GL_SHININESS, material6_Se);

    glPushMatrix();
    glTranslatef(0, 0.85, 0);
    score.Draw();
    glPopMatrix();

	DrawRoad();

}

int points = 0;
bool cross_cars = false;
bool cross_trunks = false;
void Points() {

	if(lives == 0) {
		cross_cars = false;
		cross_trunks = false;
	}
	if(frog.pos.y > -0.2 && !cross_cars) {
		points+=1;
		cross_cars = true;
	}
	else if((frog.pos.y > 0.6) && !cross_trunks) {
		points+=3;
		cross_trunks = true;
	}
}

Vector eyepos= Vector(0,-2,1);
Vector eyelookat= Vector(0,0,0);

//TODO: why in orthogonal view object no color
//TODO: why perspective view lights on background not well visible
//TODO: frog must turn with the keys

void onDisplay(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    //glEnable(GL_COLOR_MATERIAL);

   // light_posFrog = (GLfloat [4]) {
   //         frog.pos.x, frog.pos.y, frog.pos.z + 0.25f, 1.00
   // };


	light_posFrog = (GLfloat*) malloc(sizeof(GLfloat)*4);
	*light_posFrog = frog.pos.x;
	*(light_posFrog+1) = frog.pos.y;
	*(light_posFrog+2) = frog.pos.z + 0.25f;
	*(light_posFrog+3) = 1.00;


    GLfloat xDir = (GLfloat) (-0.2 * sin(frog.frogDirection / 180 * M_PI));
    GLfloat yDir = (GLfloat) (0.2 * cos(frog.frogDirection / 180 * M_PI));
   // frog_spotlightDir = (GLfloat [3]) {xDir, yDir, -0.05};


	frog_spotlightDir = (GLfloat*) malloc(sizeof(GLfloat)*3);
	*frog_spotlightDir = xDir;
	*(frog_spotlightDir+1) = yDir;
	*(frog_spotlightDir+2) = -0.05;

    //Ambient lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);


    //Light 1
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuation);

    //Light 2
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, attenuation);

    //Light 3
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, attenuation);

    //Light 4
    glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, attenuation);

    //Light 5
    glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);
    glLightfv(GL_LIGHT4, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT4, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, attenuation);

    //Light 6
    glLightfv(GL_LIGHT5, GL_POSITION, light_pos5);
    glLightfv(GL_LIGHT5, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT5, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, attenuation);

    //Frog Light
    glLightfv(GL_LIGHT7, GL_POSITION, light_posFrog);
    glLightfv(GL_LIGHT7, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT7, GL_SPECULAR, light_Ks);
    glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, attenuation);
    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 55.0);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, frog_spotlightDir);

    //Definition of the DIRECTIONAL AMBIENT LIGHTING - Day/Night
    GLfloat lightDir[] = {0.5, 0.5, 0.5, 0.0}; //last parameter: 0 (directional) or 1 (positional)
    GLfloat lightDir_Ka[] = {0.05, 0.05, 0.05, 1.0}; //brighter color than the pointlights
    GLfloat lightDir_Kd[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat lightDir_Ks[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT6, GL_POSITION, lightDir);
    glLightfv(GL_LIGHT6, GL_AMBIENT, lightDir_Ka);
    glLightfv(GL_LIGHT6, GL_DIFFUSE, lightDir_Kd);
    glLightfv(GL_LIGHT6, GL_SPECULAR, lightDir_Ks);
    glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, attenuation);



    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    //glEnable(GL_CULL_FACE);
    
    //ENABLE LIGHTING
    if (l_pressed) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }
    //ENABLE LIGHTING POINTS
    if (c_pressed) {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
        glEnable(GL_LIGHT5);
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
    }
//    //ENABLE DAY/NIGHT LIGHTS
//    if (n_pressed) {
//        glEnable(GL_LIGHT6);
//    } else {
//        glDisable(GL_LIGHT6);
//    }
//
//    //ENABLE frog headlight
//    if (h_pressed) {
//        glEnable(GL_LIGHT7);
//    } else {
//        glDisable(GL_LIGHT7);
//    }

	if (cameramode == 1)
	{
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
	if (cameramode == 2)
	{
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);	
		glLoadIdentity(); 
		gluPerspective(54, (float)600/(float)600, 0.1, 100);
    
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		gluLookAt(eyepos.x,eyepos.y,eyepos.z,eyelookat.x,eyelookat.y,eyelookat.z,0,1,0);
	}

	if (cameramode == 3)
	{
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);	
		glLoadIdentity(); 
		gluPerspective(54, (float)600/(float)600, 0.1, 100);
    
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		gluLookAt(frog.pos.x,frog.pos.y-1,frog.pos.z+1,frog.pos.x,frog.pos.y+0.5,frog.pos.z,0,1,0);
	}

    if (cameramode == 4)
    {
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(54, (float)600/(float)600, 0.1, 100);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(frog.pos.x,frog.pos.y+0.02,frog.pos.z+0.05,frog.pos.x,frog.pos.y+0.5,frog.pos.z,0,1,0);
    }

	//Debug: see the frog head in the trunks
	if (cameramode == 8)
	{
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);	
		glLoadIdentity(); 
		gluPerspective(50, (float)600/(float)600, 0.1, 100);
    
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		gluLookAt(frog.pos.x,frog.pos.y+2,frog.pos.z+1,frog.pos.x,frog.pos.y+0.5,frog.pos.z,0,-1,0);
	}

//	//Debug
//	if (cameramode == 9)
//	{
//		DrawDebugZone();
//
//		glEnable(GL_DEPTH_TEST);
//		glMatrixMode(GL_PROJECTION);	
//		glLoadIdentity(); 
//		gluPerspective(54, (float)600/(float)600, 0.1, 100);
//    
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//	
//		gluLookAt(x_rotate, y_rotate, 1, 5, 0, 0.25, 0, 0, 1);
//	}
    
	DrawBackGround();
	
	for (int i=0; i<14; i++){
        carArray[i].Draw();
    }
    
    for (int i=0; i<11; i++){
        trunkArray[i].Draw();
    }

	frog.Draw();



	glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix() ; // save
    glLoadIdentity();// and clear
    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;
    glDisable( GL_DEPTH_TEST ) ;


	//glDisable(GL_TEXTURE_2D);

	/*--------TRY  INSTANCIATE FROGS FOR LIVES---------------*/

	for(int aux = 0; aux < lives; aux++) {
		frogLiveArray[aux].Draw();
	}

	/*--------------------------------------------------------*/
    glColor3f(1.0f, 1.0f, 1.0f);
	DrawInt(points);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9, 0.9);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPrintString(GLUT_BITMAP_HELVETICA_18, gamemessage);
    //glEnable(GL_TEXTURE_2D);


	//Pause message
	if(paused && lives != 0 ) {
		box.Draw();
		glColor3f(0.0f, 0.0f, 0.0f);
        GLfloat material5_Ka[] = {0.00, 0.1, 0.00, 1.00}; //ambient
        GLfloat material5_Kd[] = {0.0, 0.2, 0.0, 1.00}; //diffusion
        GLfloat material5_Ks[] = {0.0, 0.7, 0.0, 1.00}; //specular
        GLfloat material5_Ke[] = {1.0, 1.0, 1.0, 0.00}; //emission
        GLfloat material5_Se[] = {70}; //shineness
        glMaterialfv(GL_FRONT, GL_AMBIENT, material5_Ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material5_Kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material5_Ks);
        glMaterialfv(GL_FRONT, GL_EMISSION, material5_Ke);
        glMaterialfv(GL_FRONT, GL_SHININESS, material5_Se);
        glRasterPos2f(-0.6, -0.05);
        char * temp_s = "GAME PAUSED! PRESS 'S' TO CONTINUE";
        glPrintString(GLUT_BITMAP_HELVETICA_18, temp_s);
	}

    if(lives == 0)
    {
		box.Draw();
        glColor3f(0.0f, 0.0f, 0.0f);
        GLfloat material5_Ka[] = {0.00, 0.1, 0.00, 1.00}; //ambient
        GLfloat material5_Kd[] = {0.0, 0.2, 0.0, 1.00}; //diffusion
        GLfloat material5_Ks[] = {0.0, 0.7, 0.0, 1.00}; //specular
        GLfloat material5_Ke[] = {1.0, 1.0, 1.0, 0.00}; //emission
        GLfloat material5_Se[] = {70}; //shineness
        glMaterialfv(GL_FRONT, GL_AMBIENT, material5_Ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material5_Kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material5_Ks);
        glMaterialfv(GL_FRONT, GL_EMISSION, material5_Ke);
        glMaterialfv(GL_FRONT, GL_SHININESS, material5_Se);
        glRasterPos2f(-0.8, 0.0);
        char * temp = "GAME OVER !!! DO YOU WANT TO RESTART ?";
        char * temp2 = "(PRESS R)";
        glPrintString(GLUT_BITMAP_HELVETICA_18, temp);
        glRasterPos2f(-0.2, -0.2);
        glPrintString(GLUT_BITMAP_HELVETICA_18, temp2);
    }


    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on
    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix() ; // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix() ;

	glDisable(GL_TEXTURE_2D);


	glFlush();

}

void increaseObjectsVelocity(int value) {
  
	if(!paused) {
		if( velocityIndex < 10 ) {
			for (int j=0; j<14; j++) {
				//If car have positive velocity, change it from array
				if(carArray[j].velocity.x > 0) {
					carArray[j].velocity.x = velocityArray[velocityIndex];
				}
				//If car have negative velocity, change it from array and put it negative again
				else if(carArray[j].velocity.x < 0) {
					carArray[j].velocity.x = -velocityArray[velocityIndex];
				}	
			}
			//loop for each trunk
			for (int j=0; j<11; j++) {
				//If car have positive velocity, change it from array
				if(trunkArray[j].velocity.x > 0) {
					trunkArray[j].velocity.x = velocityArray[velocityIndex];
				}
				//If car have negative velocity, change it from array and put it negative again
				else if(trunkArray[j].velocity.x < 0) {
					trunkArray[j].velocity.x = -velocityArray[velocityIndex];
				}
			}
		velocityIndex += 1;
		glutTimerFunc(10000, increaseObjectsVelocity, 10);
		}
	}
}

void betterFrogBorders() {





}

float FrogTrunkFlowMov(bool o, bool p) {

	float O, P;

	if(o) { O = -FROG_VELOCITY; }
	else if(!o) { O = 0.0; }
	if(p) { P = FROG_VELOCITY; }
	else if(!p) { P = 0.0; }

	return (O + P);
}

void FrogCollisionsTrunks() {

	// Collosion detection
	float fx= frog.pos.x;
	float fy = frog.pos.y;
	float fz = frog.pos.z;

	for (int i=0; i<11; i++){
		if(trunkArray[i].pos.x + (trunkArray[i].length*0.1)/2.0 >= fx && trunkArray[i].pos.x - (trunkArray[i].length*0.1)/2.0 <= fx) {
			if(trunkArray[i].pos.y + trunkArray[i].size/2.0 >= fy && trunkArray[i].pos.y - trunkArray[i].size/2.0 <= fy) {
				frog.isItOnATrunk = true;
				frog.velocity.x = trunkArray[i].velocity.x  + FrogTrunkFlowMov(o_pressed, p_pressed);
				break;
			}
			frog.isItOnATrunk = false;
		}
		frog.isItOnATrunk = false;
	}
}

void RestartGame() {

	velocityIndex = 0;
	gameTime = 0;
	actual_time = 0;
	elapsed_time = 0;
	lives = 5;
	timeAtReset = glutGet(GLUT_ELAPSED_TIME);
	points = 0;

    carArray[0].pos = Vector(-1.1, -0.3, 0.03);
	carArray[1].pos = Vector(-1.5, -0.3, 0.03);
	carArray[2].pos = Vector(-2.0, -0.3, 0.03);
	carArray[3].pos = Vector(-2.4, -0.3, 0.03);
	carArray[4].pos = Vector(1.1, -0.4, 0.03);
	carArray[5].pos = Vector(1.6, -0.4, 0.03);
	carArray[6].pos = Vector(2.1, -0.4, 0.03);
	carArray[7].pos = Vector(-1.1, -0.5, 0.03);
	carArray[8].pos = Vector(-1.7, -0.5, 0.03);
	carArray[9].pos = Vector(1.1, -0.6, 0.03);
	carArray[10].pos = Vector(1.6, -0.6, 0.03);
	carArray[11].pos = Vector(1.9, -0.6, 0.03);
	carArray[12].pos = Vector(-1.1, -0.7, 0.03);
	carArray[13].pos = Vector(-1.6, -0.7, 0.03);
	
	trunkArray[0].pos = Vector(-1.1, 0.5, -0.04);
	trunkArray[1].pos = Vector(-1.7, 0.5, -0.04);
	trunkArray[2].pos = Vector(-2.5, 0.5, -0.04);
	trunkArray[3].pos = Vector(-2.3, 0.4, -0.04);
	trunkArray[4].pos = Vector(-2.9, 0.4, -0.04);
	trunkArray[5].pos = Vector(-0.5, 0.3, -0.04);
	trunkArray[6].pos = Vector(1.5, 0.3, -0.04);
	trunkArray[7].pos = Vector(2.1, 0.2, -0.04);
	trunkArray[8].pos = Vector(2.9, 0.2, -0.04);
	trunkArray[9].pos = Vector(-1.2, 0.1, -0.04);
	trunkArray[10].pos = Vector(-1.7, 0.1, -0.04);

	//puts the game running again and unlocks the Pause botton
	paused = false;
	lockPaused = false;
}

void PauseMenu() {
	if(paused) {
		system("clear");
		std::cout << "The game is PAUSED\nPress 'S' to continue\n";
		onDisplay();

	}
}

void RestartMenu() {
	system("clear");
	std::cout << "You lost the game, do you want to restart? (Press 'R')\n"; 
	//Block the Pause botton
	lockPaused = true;
	paused = true;
}


void UpdateLives() {
	lives -= 1;
	if(lives > 0){
		system("clear");
		std::cout << "You died! You only have " << lives << " lives left...\n";

		//gamemessage[80] = "Lives: 5";
	}
	if(lives == 0) {
		RestartMenu();
	}
}

void FrogDirection() {

	if(o_pressed && q_pressed) { frog.frogDirection = 45; }

	else if(o_pressed && a_pressed) { frog.frogDirection = 135; }

	else if(p_pressed && q_pressed) { frog.frogDirection = -45; }

	else if(p_pressed && a_pressed) { frog.frogDirection = -135; }

	else if(q_pressed) { frog.frogDirection = 0; }

	else if(a_pressed) { frog.frogDirection = 180; }

	else if(o_pressed) { frog.frogDirection = 90; }

	else if(p_pressed) { frog.frogDirection = -90; }

}

void animateWorld(long dt)
{
	//condition stop animate when game paused
	if(!paused) {
		frog.Animate(dt);

		for (int i=0; i<14; i++){
			carArray[i].Animate(dt);
		}
    
		for (int i=0; i<11; i++){
			trunkArray[i].Animate(dt);
		}

		//update points
		Points();

		//change directions of the frog
		FrogDirection();

		// Collosion detection
		float fx= frog.pos.x;
		float fy = frog.pos.y;
		float fz = frog.pos.z;

		// for each element of cararray car[i].pos    
		for (int i=0; i<14; i++){
			if(carArray[i].pos.x + 0.06 >= fx-0.035 && carArray[i].pos.x - 0.06 <= fx+0.035) {
				if(carArray[i].pos.y + 0.04 >= fy-0.035 && carArray[i].pos.y - 0.04 <= fy + 0.035)
				{
					frog.pos.x = 0;
					frog.pos.y = -0.9;
					frog.pos.z = 0;
					UpdateLives();
					cross_cars = false;
					cross_trunks = false;
				}
			}
		}


			//Checks frog's collisions with trunks
			FrogCollisionsTrunks();

		/*------------- New code for half of frog----------------*/
			for (int i=0; i<11; i++){
				if(trunkArray[i].pos.x + (trunkArray[i].length*0.1)/2.0 >= fx - 0.035 && trunkArray[i].pos.x - (trunkArray[i].length*0.1)/2.0 <= fx+0.035) {
					if(trunkArray[i].pos.y + trunkArray[i].size/2.0 >= fy - 0.035 && trunkArray[i].pos.y - trunkArray[i].size/2.0 <= fy+0.035)
					{
						frog.isItOnATrunk = true;
						frog.velocity.x = trunkArray[i].velocity.x  + FrogTrunkFlowMov(o_pressed, p_pressed);
						break;
					}
					frog.isItOnATrunk = false;
				}
				frog.isItOnATrunk = false;
			}
		/*-------------------------------------------------------*/


			/*
			for (int i=0; i<11; i++){
				if(trunkArray[i].pos.x + (trunkArray[i].length*0.1)/2.0 >= fx - 0.035 && trunkArray[i].pos.x - (trunkArray[i].length*0.1)/2.0 <= fx+0.035) {
					if(trunkArray[i].pos.y + trunkArray[i].size/2.0 >= fy - 0.035 && trunkArray[i].pos.y - trunkArray[i].size/2.0 <= fy+0.035)
					{
						frog.isItOnATrunk = true;
						frog.velocity.x = trunkArray[i].velocity.x  + FrogTrunkFlowMov(o_pressed, p_pressed);
						break;
					}
					frog.isItOnATrunk = false;
				}
				frog.isItOnATrunk = false;
			}
			*/

			//CHECKS IF THE FROG IS IN THE WATER  ||  checks if frog reach the left and right bounderies while still on a trunk
			if( (!frog.isItOnATrunk && fy >= 0.05 && fy <= 0.55) || (frog.isItOnATrunk && (fx+ 0.035>= 1.0 || fx- 0.035 <= -1.0) ) )
			{
				frog.pos.x = 0;
				frog.pos.y = -0.9;
				frog.pos.z = 0;

				frog.velocity.x = 0;
				UpdateLives();
				cross_cars = false;
				cross_trunks = false;
			}

			// boundaries
			if(!frog.isItOnATrunk && (fy - 0.035 <= -1.0 || fx + 0.035 >= 1.0 || fx - 0.035 <= -1.0)) {
			
				frog.pos = frog.previous_pos;
		

			//reach the top
			}
			if(fy+ 0.035 >= 0.7) {
				frog.pos.x = 0;
				frog.pos.y = -0.9;
				frog.pos.z = 0;

				frog.velocity.x = 0;
				cross_cars = false;
				cross_trunks = false;
			}
			//Tests if the frog just left the trunk and if so, but is velocity.x to 0
			if(frog.previous_isItOnATrunk == true && frog.isItOnATrunk == false) {
				frog.velocity.x = 0.0;
			}
			frog.previous_pos = frog.pos;
			frog.previous_isItOnATrunk = frog.isItOnATrunk;

		glutPostRedisplay();
	}
}

void onIdle()
{
	actual_time = glutGet(GLUT_ELAPSED_TIME) - timeAtReset;
	elapsed_time = actual_time- gameTime;

	animateWorld(elapsed_time);

	//gameTime += elapsed_time;
	gameTime = actual_time;
}

void onKeyboardDown(unsigned char key, int x, int y)
{
	if((key == 's' || key == 'S') && lockPaused == false)
	{
		paused = (paused) ? false:true;
		PauseMenu();
	}

	if((key == 'r' || key == 'R') && lives <= 0) {
		RestartGame();
	}

	if(!paused){
		//Right
		if(key=='p' || key=='P')
		{
			frog.velocity.x = FROG_VELOCITY;
			p_pressed = true;
			//eyepos.x+=0.1;
		}
		//Down
		if(key=='a' || key=='A')
		{
			frog.velocity.y = -FROG_VELOCITY;
			a_pressed = true;
			//eyepos.x-=0.1;
		}
		//Left
		if(key=='o' || key=='O')
		{
			frog.velocity.x = -FROG_VELOCITY;
			o_pressed = true;
			//eyepos.y+=0.1;
		}
		//Up
		if(key=='q' || key=='Q')
		{
			frog.velocity.y = FROG_VELOCITY;
			q_pressed = true;
			//eyepos.y-=0.1;
		}
    
		if(key=='c' || key=='C')
		{
			c_pressed = !c_pressed;
		}
    
		if(key=='l' || key=='L')
		{
			l_pressed = !l_pressed;
		}
		//ENABLE DAY/NIGHT LIGHTS
		if(key=='n' || key=='N')
		{
			n_pressed = !n_pressed;
			if(n_pressed) {
				h_save = h_pressed;
				h_pressed = false;
				glEnable(GL_LIGHT6);

			}
			else if(!n_pressed) {
				h_pressed = h_save;
				glDisable(GL_LIGHT6);
			}
		}
		//ENABLE frog headlight
		if(key=='h' || key=='H')
		{
			h_pressed = !h_pressed;
			if(!n_pressed) {
				glEnable(GL_LIGHT7);
			}
			else if(n_pressed) {
				glDisable(GL_LIGHT7);
			}
		}

		if(key=='1')
		{
			cameramode = 1;
		}

		if(key=='2')
		{
			cameramode = 2;
		}

		if(key=='3')
		{
			cameramode = 3;
		}

        if(key=='4')
        {
            cameramode = 4;
        }
		//Debug: see the frog head in the trunks
		if(key == '8') {
			cameramode = 8;
		}
	}	
}

void onKeyboardUp(unsigned char key, int x, int y)
{
	//Right
	if(key=='p' || key=='P')
	{
		p_pressed = false;
		if(o_pressed) { frog.velocity.x = -FROG_VELOCITY; }
		else if(!o_pressed) { frog.velocity.x = 0.0; }
		
		//eyepos.x+=0.1;
	}
	//Down
	if(key=='a' || key=='A')
	{
		a_pressed = false;
		if(q_pressed) { frog.velocity.y = FROG_VELOCITY; }
		else if(!q_pressed) { frog.velocity.y = 0.0; }
		
		//eyepos.x-=0.1;
	}
	//Left
	if(key=='o' || key=='O')
	{
		o_pressed = false;
		if(p_pressed) { frog.velocity.x = FROG_VELOCITY; }
		else if(!p_pressed) { frog.velocity.x = 0.0; }
		
		//eyepos.y+=0.1;
	}
	//Up
	if(key=='q' || key=='Q')
	{
		q_pressed = false;
		if(a_pressed) { frog.velocity.y = -FROG_VELOCITY; }
		else if(!a_pressed) { frog.velocity.y = 0.0; }
		
		//eyepos.y-=0.1;
	}

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (500, 50);

	
	glutCreateWindow("Frogger");

	glutDisplayFunc(onDisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboardDown);
	glutKeyboardUpFunc(onKeyboardUp);
	glutTimerFunc(10000, increaseObjectsVelocity, 10);


	glutMainLoop();

    return 0;
}