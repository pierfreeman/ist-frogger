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
#include <cmath>
#include <array>
#include <random>
#include <iostream>
#include <stdlib.h>
#include "river64.h"
#include "river2.h"
#include "lodepng.h"
/*-------------------------------------*/

#define FROG_VELOCITY 0.0005f;

class Color {
public:
       float r, g, b;          // color coefficients on the representative wavelengths
 
//konstruktorok es operator atdefinialasok
       Color() {
               r = 0;
               g = 0;
               b = 0;
       }
 
       Color(float rr, float gg, float bb) {
               r = rr; g = gg; b = bb;
       }
 
       void Set(float rr, float gg, float bb) {
               r = rr; g = gg; b = bb;
       }
 
       // binary operators
       Color operator+(const Color& c) const {
               return Color(r + c.r, g + c.g, b + c.b);
       }
 
       Color operator*(float f) const {
               return Color(r * f, g * f, b * f);
       }
 
       Color operator*(const Color& c) const {
               return Color(r * c.r, g * c.g, b * c.b);
       }
 
       Color operator/(float f) const {
               return Color(r / f, g / f, b / f);
       }
 
       // unary operators
       void operator+=(const Color& c) {
               r += c.r; g += c.g; b += c.b;
       }
 
       //luminancia
       float Lum() const {
               return (r + g + b) / 3.0;
       }
       friend Color operator*(float f, const Color& c);
};
 
inline Color operator*(float f, const Color& c) {
       return Color(f * c.r, f * c.g, f * c.b);
}
 
const Color     gColorBlack(0, 0, 0); //fekete arnyalat
const Color     gColorWhite(1, 1, 1); //feh�r arnyalat
const Color     gColorAmbient(1.5, 1.5, 1.5);   // global ambient


//VEKTOR OSZT�LY �s m�veletei




class Vector {
public:
       float x, y, z;
 
//konstruktorok, operator feluldefinialasok
       Vector(float xx=0, float yy=0, float zz=0) {
               x = xx; y = yy; z = zz;
       }
 
       void Set(float xx, float yy, float zz) {
               x = xx; y = yy; z = zz;
       }
 
       // binary operators
       Vector operator+(const Vector& c) const {
               return Vector(x + c.x, y + c.y, z + c.z);
       }
 
       Vector operator-(const Vector& c) const {
               return Vector(x - c.x, y - c.y, z - c.z);
       }
 
       Vector operator*(float f) const {
               return Vector(x * f, y * f, z * f);
       }
 
       Vector operator/(float f) const {
               return Vector(x / f, y / f, z / f);
       }
 
       // unary operators
       void operator+=(float f) {
               x += f; y += f; z += f;
       }
 
       void operator+=(const Vector& c) {
               x += c.x; y += c.y; z += c.z;
       }
 
       void operator*=(float f) {
               x *= f; y *= f; z *= f;
       }
 
       Vector operator-(void) const {
               return Vector(-x, -y, -z);
       }
 
       // other methods
       float operator*(const Vector& v) const {                // DotProduct
               return x * v.x + y * v.y + z * v.z;
       }
 
       Vector operator%(const Vector& v) const {               // CrossProduct
               return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
       }
 
       void operator<=(const Vector& smallVec) {
               if (x > smallVec.x) x = smallVec.x;
               if (y > smallVec.y) y = smallVec.y;
               if (z > smallVec.z) z = smallVec.z;
       }
 
       void operator>=(const Vector& largeVec) {
               if (x < largeVec.x) x = largeVec.x;
               if (y < largeVec.y) y = largeVec.y;
               if (z < largeVec.z) z = largeVec.z;
       }
//length
       float Norm(void) const {
               return sqrt(x*x + y*y + z*z);
       }
//normalas
       void Normalize() {
               float norm = Norm();
               x /= norm;
               y /= norm;
               z /= norm;
       }
 
 
// other methods
       friend Vector operator*(float f, const Vector& v);
};
 
inline Vector operator*(float f, const Vector& v) {
       return Vector(f * v.x, f * v.y, f * v.z);
}

void normal (Vector v[3], Vector& normal)
{
   Vector a(0,0,0);
      Vector b(0,0,0);
 
   a.x = v[0].x - v[1].x;
   a.y = v[0].y - v[1].y;
   a.z = v[0].z - v[1].z;
 
   b.x = v[1].x - v[2].x;
   b.y = v[1].y - v[2].y;
   b.z = v[1].z - v[2].z;
 
   normal.x = (a.y * b.z) - (a.z * b.y);
   normal.y = (a.z * b.x) - (a.x * b.z);
   normal.z = (a.x * b.y) - (a.y * b.x);
 
       normal.Normalize();
}

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

// h�romsz�g oszt�ly
class Triangle 
{
public:
    Vector p1; // pont
    Vector p2;
    Vector p3;
    Vector n1; // ponthoz a norm�lvektorok
    Vector n2;
    Vector n3;
 
public: Triangle(){}
    Triangle(Vector a, Vector b, Vector c) // konstruktor norm�lvektorok n�lk�l
    {
        p1=a;
        p2=b;
        p3=c;
        n1=Vector(0,0,0);
        n2=Vector(0,0,0);
        n3=Vector(0,0,0);
    }
 
    // konstruktor 3 ponttal �s a pontokhoz tartoz� norm�lvektorokkal
    Triangle(Vector a, Vector b, Vector c, Vector d, Vector e, Vector f)
    {
        p1=a;
        p2=b;
        p3=c;
        n1=d;
        n2=e;
        n3=f;
    }
};
 
// H�ROMSZ�GH�L�
class Mesh
{
public:
    Triangle * halo; // 3sz�g t�mb
    int numtri; // 3sz�gek sz�ma
 
public:
 
    Mesh() // konstr
    {
        halo = new Triangle[1000];
        numtri =0;
    }
 
    // 3sz�g hozz�ad� fv.
    void AddTriangle(Triangle t) 
    {
        halo[numtri]= t;
        numtri++;
    }
};
 
// Cylinder
class Cylinder :Mesh
{
public:
    Vector middlepoint; // middlepointpont
    float r, length; // sug�r, length
 
    Cylinder ( ){}
 
	// USE THIS CONSTRUCTOR YOU NEED TO PASS THE MIDDLE POINT THE RADIUS AND THE LENGTH OF THE CYLINDER
    Cylinder(Vector kp, float sug, float oldal)
    {
        float alfa = (3.14*3.6)/180; // 100 3sz�gre bontva az alapk�rt egy szelet k�z�pponti sz�ge (folyamatosan n�)
        float aktz=kp.z+sug; // alap�llapot x =oldal fele minuszban, y = 0, z=1(sug�r)  eltolva a k�z�pponttal
        float aktx=kp.x - (oldal/2);
        float akty =kp.y;
        float x,y,z;   
 
        r=sug; 
        middlepoint = kp;
        length = oldal/2;
        
        // h�romsz�gh�l� sz�m�t�sa
        for( int i =0; i< 102; i++)
        {
            z = kp.z-r* cos(alfa);
            y = kp.y-r* sin(alfa);
            x= kp.x - length;
 
            // fed�lapokon a h�romsz�gszeletek (lenti majd fenti)
            AddTriangle( Triangle(Vector(x,kp.y,kp.z), Vector(x,y,z), Vector(aktx,akty,aktz),Vector(-1,0,0), Vector(-1,0,0), Vector(-1,0,0)));
            AddTriangle( Triangle(Vector(x+oldal,kp.y,kp.z), Vector(x+oldal,y,z), Vector(aktx+oldal,akty,aktz) , Vector(1,0,0), Vector(1,0,0), Vector(1,0,0)));
            // oldallapi t�glalap 2 h�romsz�gre bontva
            AddTriangle( Triangle(Vector(x,y,z), Vector(aktx,akty,aktz), Vector(x+oldal,y,z), 
                        Vector(0,y,z), Vector(0,akty,aktz), Vector(0,y,z)));
            AddTriangle( Triangle(Vector(aktx,akty,aktz), Vector(x+oldal,y,z), Vector(aktx+oldal,akty,aktz) , 
                        Vector(0,akty,aktz), Vector(0,y,z), Vector(0,akty,aktz)));
 
            aktz=z; // eddigi �llapot ment�se
            akty=y;
 
 
            alfa = alfa + (3.14*3.6)/180; // sz�g n�vel�se
        }
    }
 
    // kirajzol� f�ggv�ny
    void Draw()
    {
        glEnable(GL_NORMALIZE);
        glBegin(GL_TRIANGLES);
        
        // v�gigmegy a 3sz�gh�l�n �s kirajzolja 3sz�genk�nt
            for(int i = 0; i<numtri; i++)
            {
                glNormal3f(halo[i].n1.x, halo[i].n1.y, halo[i].n1.z);  
                glVertex3f(halo[i].p1.x, halo[i].p1.y, halo[i].p1.z);
                glNormal3f(halo[i].n2.x, halo[i].n2.y, halo[i].n2.z);
                glVertex3f(halo[i].p2.x, halo[i].p2.y, halo[i].p2.z);
                glNormal3f(halo[i].n3.x, halo[i].n3.y, halo[i].n3.z);
                glVertex3f(halo[i].p3.x, halo[i].p3.y, halo[i].p3.z);
            }
        glEnd();
    }
 
};


class Cube : public Mesh
{
public:
    Vector middlepoint;
    float a,b,c; // oldallengthak
    Vector * csucsok;
 
	// USE THIS CONSTRUCTOR YOU NEED TO PASS THE MIDDLE POINT AND THE 3 SIDE LENGTH
    Cube( Vector kp, float A, float B, float C)
    {
        middlepoint = kp;
        csucsok = new Vector[8]; // cs�csok t�mmbje ( fenti lapon majd lentin )
        a=A/2; b=B/2; c=C/2;
 
        csucsok[0]= Vector(kp.x + a, kp.y - b, kp.z - c);
        csucsok[1]= Vector(kp.x + a, kp.y - b, kp.z + c);
        csucsok[2]= Vector(kp.x + a, kp.y + b, kp.z + c);
        csucsok[3]= Vector(kp.x + a, kp.y + b, kp.z - c);
        csucsok[4]= Vector(kp.x - a, kp.y - b, kp.z - c);
        csucsok[5]= Vector(kp.x - a, kp.y - b, kp.z + c);
        csucsok[6]= Vector(kp.x - a, kp.y + b, kp.z + c);
        csucsok[7]= Vector(kp.x - a, kp.y + b, kp.z - c);
 
        // 3sz�gek (laponk�nt 2 )
        AddTriangle( Triangle(csucsok[0], csucsok[1], csucsok[2], Vector(1,0,0), Vector(1,0,0), Vector(1,0,0)));
        AddTriangle( Triangle(csucsok[0], csucsok[2], csucsok[3], Vector(1,0,0), Vector(1,0,0), Vector(1,0,0)));
        AddTriangle( Triangle(csucsok[0], csucsok[1], csucsok[4], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
        AddTriangle( Triangle(csucsok[1], csucsok[4], csucsok[5], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
        AddTriangle( Triangle(csucsok[1], csucsok[2], csucsok[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
        AddTriangle( Triangle(csucsok[2], csucsok[6], csucsok[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
        AddTriangle( Triangle(csucsok[4], csucsok[5], csucsok[7], Vector(-1,0,0), Vector(-1,0,0), Vector(-1,0,0)));
        AddTriangle( Triangle(csucsok[5], csucsok[6], csucsok[7], Vector(-1,0,0), Vector(-1,0,0), Vector(-1,0,0)));
        AddTriangle( Triangle(csucsok[0], csucsok[4], csucsok[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
        AddTriangle( Triangle(csucsok[0], csucsok[3], csucsok[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
        AddTriangle( Triangle(csucsok[2], csucsok[6], csucsok[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));
        AddTriangle( Triangle(csucsok[2], csucsok[3], csucsok[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));
 
        a=A; b=B; c=C;
 
    }
 
    Cube(){}
 
    // kirajzol� fv
    void Draw()
    {
        
        //glDisable(GL_TEXTURE_2D); glEnable(GL_NORMALIZE);
        glEnable(GL_NORMALIZE);
        glBegin(GL_TRIANGLES);
        
            // 3sz�genk�nt rajzol
            for(int i = 0; i<numtri; i++)
            {
                glNormal3f(halo[i].n1.x, halo[i].n1.y, halo[i].n1.z);
                glVertex3f(halo[i].p1.x, halo[i].p1.y, halo[i].p1.z);
                glVertex3f(halo[i].p2.x, halo[i].p2.y, halo[i].p2.z);
                glVertex3f(halo[i].p3.x, halo[i].p3.y, halo[i].p3.z);
            }
        glEnd();
    }
 
};

class Trapezio : public Mesh
{
public:
    Vector middlepoint;
    float h, bw, sw, d;	//height(z), bigger width(x), smaller width(x) and depth(y) 
    Vector * vertexcoord;
 
	// USE THIS CONSTRUCTOR YOU NEED TO PASS THE MIDDLE POINT AND THE 3 SIDE LENGTH
    Trapezio( Vector kp, float H, float BW, float SW, float D)
    {
        middlepoint = kp;
        vertexcoord = new Vector[8]; // vector with all vertex positions
        h=H/2;
		bw=BW/2;
		sw=SW/2;
		d=D/2;
 
        vertexcoord[0]= Vector(kp.x + bw, kp.y - d, kp.z - h);
        vertexcoord[1]= Vector(kp.x + sw, kp.y - d, kp.z + h);
        vertexcoord[2]= Vector(kp.x + sw, kp.y + d, kp.z + h);
		vertexcoord[3]= Vector(kp.x + bw, kp.y + d, kp.z - h);
	    vertexcoord[4]= Vector(kp.x - bw, kp.y - d, kp.z - h);
        vertexcoord[5]= Vector(kp.x - sw, kp.y - d, kp.z + h);
        vertexcoord[6]= Vector(kp.x - sw, kp.y + d, kp.z + h);
        vertexcoord[7]= Vector(kp.x - bw, kp.y + d, kp.z - h);
 
        // 3sz�gek (laponk�nt 2 )
        AddTriangle( Triangle(vertexcoord[0], vertexcoord[1], vertexcoord[2], Vector(1,0,1), Vector(1,0,1), Vector(1,0,1)));//Obliquo
        AddTriangle( Triangle(vertexcoord[0], vertexcoord[2], vertexcoord[3], Vector(1,0,1), Vector(1,0,1), Vector(1,0,1)));//Obliquo
        AddTriangle( Triangle(vertexcoord[0], vertexcoord[1], vertexcoord[4], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
        AddTriangle( Triangle(vertexcoord[1], vertexcoord[4], vertexcoord[5], Vector(0,-1,0), Vector(0,-1,0), Vector(0,-1,0)));
        AddTriangle( Triangle(vertexcoord[1], vertexcoord[2], vertexcoord[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
        AddTriangle( Triangle(vertexcoord[2], vertexcoord[6], vertexcoord[5], Vector(0,0,1), Vector(0,0,1), Vector(0,0,1)));
        AddTriangle( Triangle(vertexcoord[4], vertexcoord[5], vertexcoord[7], Vector(-1,0,1), Vector(-1,0,1), Vector(-1,0,1)));//Obliquo
        AddTriangle( Triangle(vertexcoord[5], vertexcoord[6], vertexcoord[7], Vector(-1,0,1), Vector(-1,0,1), Vector(-1,0,1)));//Obliquo
        AddTriangle( Triangle(vertexcoord[0], vertexcoord[4], vertexcoord[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
        AddTriangle( Triangle(vertexcoord[0], vertexcoord[3], vertexcoord[7], Vector(0,0,-1), Vector(0,0,-1), Vector(0,0,-1)));
        AddTriangle( Triangle(vertexcoord[2], vertexcoord[6], vertexcoord[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));
        AddTriangle( Triangle(vertexcoord[2], vertexcoord[3], vertexcoord[7], Vector(0,1,0), Vector(0,1,0), Vector(0,1,0)));
 
        //a=A; b=B; c=C;
 
    }
 
    Trapezio(){}
 
    // kirajzol� fv
    void Draw()
    {
        
        //glDisable(GL_TEXTURE_2D); glEnable(GL_NORMALIZE);
        glEnable(GL_NORMALIZE);
        glBegin(GL_TRIANGLES);
        
            // 3sz�genk�nt rajzol
            for(int i = 0; i<numtri; i++)
            {
                glNormal3f(halo[i].n1.x, halo[i].n1.y, halo[i].n1.z);
                glVertex3f(halo[i].p1.x, halo[i].p1.y, halo[i].p1.z);
                glVertex3f(halo[i].p2.x, halo[i].p2.y, halo[i].p2.z);
                glVertex3f(halo[i].p3.x, halo[i].p3.y, halo[i].p3.z);
            }
        glEnd();
    }
 
};


class Sphere
{
public:
    Vector kp;
    float r;
    
    Sphere(){}
    
    Sphere(Vector kozep)
    {
        r=0.3;
        kp=kozep;
    }
    
    void Draw()
    {
        glPushMatrix();
        //glDisable(GL_TEXTURE_2D);
        //glDisable(GL_LIGHTING);
        //glColor3f(1,0,0);
        for(int i=0; i<100; i++)
        {
            glTranslatef(kp.x, kp.y, kp.z);
            glRotatef(1.8*i,1,0,0 );
            glTranslatef(-kp.x,-kp.y, - kp.z);
            belsoDraw();
            
        }
        glPopMatrix();
        //glEnable(GL_LIGHTING);
        //glEnable(GL_TEXTURE_2D);
    }
    
    void belsoDraw()
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(kp.x, kp.y, kp.z);
        for(int j=0; j<92; j++)
            glVertex3f(kp.x+ r*sin(4*j*3.14/180),kp.y, kp.z+ r*cos(4*j*3.14/180));
        glEnd();
    }
    
};

float M = 20;
float N = 20;

class Teglalap
{
public:
    
    float width;
    float height;
    Color szin;
    
    Teglalap( float width_, float height_, Color color)
    {
        width = width_;
        height = height_;
        szin = color;
        
    }
    
    void Draw()
    {
        glBegin(GL_QUADS);
        glColor3f(szin.r, szin.g, szin.b);
        for(float u=0; u<1;u+=1.0/N)
            for( float v = 0; v<1; v+= 1.0/M)
            {
                float uc = u, vc = v;
                glTexCoord2f(uc,vc);
                glNormal3f(0, 0, 1);
                glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
                uc = u+1.0/N;
                glTexCoord2f(uc,vc);
                glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
                vc = v+1.0/M;
                glTexCoord2f(uc,vc);
                glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
                uc=u;
                glTexCoord2f(uc,vc);
                glVertex3f( uc*width - width/2.0,  vc*height - height/2.0, 0.0);
            }
        
        glEnd();
    }
    Teglalap(){ width = 0; height = 0;}
};


class SceneObject
{
public:
	Vector pos;
	Vector velocity;
	//Vector acceleration;
	SceneObject(){}
	SceneObject(Vector p, Vector v)
	{
		pos = Vector(p.x,p.y,p.z);
		velocity = Vector(v.x,v.y,v.z);
		//acceleration = Vector(0,0,0);
	}
	
public:
	void Animate(long dt)
	{
		pos+= velocity*dt;
	}
	
	virtual void Draw(){}
};

float frogDirection = 0.0;
class Frog : public SceneObject
{ 
float size;

public:
	float frogDirection;
	bool previous_isItOnATrunk;
	bool isItOnATrunk;
	Vector previous_pos;
    Cube body;
    Cube leg1;
    Cube leg2;
    Cube leg3;
    Cube leg4;
    Sphere head;
    
    Frog(Vector a, Vector b){
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


	virtual void Draw()
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

};

class Car : public SceneObject
{
public:
	Cylinder wheel1;
	Cylinder wheel2;
	Cylinder wheel3;
	Cylinder wheel4;

	Cube body;
	Trapezio top;

	Car(Vector a, Vector b)
	{
		pos = a; velocity= b; 
		wheel1 =Cylinder((0, 0, 0), 0.01f, 0.004f); 
		wheel2 =Cylinder((0, 0, 0), 0.01f, 0.004f); 
		wheel3 =Cylinder((0, 0, 0), 0.01f, 0.004f); 
		wheel4 =Cylinder((0, 0, 0), 0.01f, 0.004f); 

		body = Cube(Vector(0,0,0), 0.11, 0.06, 0.02);
		top = Trapezio(Vector(0,0,0), 0.02, 0.07, 0.03, 0.06);
	}

	void Animate(long dt) {
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

	virtual void Draw() 
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
};

class Trunk : public SceneObject
{
	
public:
	float size;
	float length;

	Cube trunk;

	Trunk(Vector a, Vector b, float s, float l) {
		pos = a; 
		velocity= b; 
		size = s; 
		length = l; 
		trunk = Cube(Vector(0,0,0), size, size, size);
	}

	void Animate(long dt) {
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
    
    void Draw()
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
};

Frog frog(Vector(0,-0.9,0), Vector(0,0,0));

//------ARRAY MODELLING-------
//float velocityArray[10] = {0.0006, 0.00065, 0.0007, 0.00075, 0.0008, 0.00085, 0.0009, 0.00095, 0.0010, 0.00105};
float velocityArray[10] = {0.00015, 0.0002, 0.00025, 0.0003, 0.00035, 0.0004, 0.00045, 0.0005, 0.00055, 0.0006};

Teglalap bottomSidewalk = Teglalap(2,0.2,Color(0.839,0,0));
Teglalap street = Teglalap(2,0.6,Color(0,0,0));
Teglalap topSidewalk = Teglalap(2,0.25,Color(0.839,0,0));
Teglalap river = Teglalap(2,0.5, Color(0.035, 0.435, 0.89));
Teglalap leaves = Teglalap(2,0.15,Color(0.216, 0.678, 0.047));
Teglalap score = Teglalap(2,0.3,Color(0.035, 0.36, 0.024));

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

GLuint loadBMP_custom(const char * imagepath){
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
// Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(imagepath,"rb");
    if (!file)                              {printf("Image could not be opened\n"); return 0;}

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }

    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

//Everything is in memory now, the file can be closed
    fclose(file);
};

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
    GLuint image = loadBMP_custom("texRiver.bmp");
    //lodepng_load_file(&image, imageSize,  "texRiver.png");

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

}