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
 
 
 
 
 // EXAMPLE OF USAGE
 class car{
	Cube mainbody;
	Cube wheel1
	...
	
	// constructor
	Car(middlepoint of the car ) 
	{
		mainbody = Cube( Vector(0,0,0), 0.5,0.7,1); // -> here you give the sizes of the elements (but you will put them in the right position only in the Draw method!)
		...
	}
	
	Draw()
	{
		glPushMatrix();
        glRotatef(90,0,0,1);    
        glTranslatef(0,0,0.5);
        mainbody.Draw();
        glPopMatrix();
	}
	
 };