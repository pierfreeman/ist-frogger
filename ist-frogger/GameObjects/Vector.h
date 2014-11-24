//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Vector_H_
#define __Vector_H_


class Vector {
public:
    float x, y, z;

    //Constructor
        Vector(float xx=0, float yy=0, float zz=0);

        void Set(float xx, float yy, float zz);

        // binary operators
        Vector operator+(const Vector& c) const;

        Vector operator-(const Vector& c) const;

        Vector operator*(float f) const;

        Vector operator/(float f) const;

        // unary operators
        void operator+=(float f);

        void operator+=(const Vector& c);

        void operator*=(float f);

        Vector operator-(void) const;

        // other methods
        float operator*(const Vector& v) const;               // DotProduct

        Vector operator%(const Vector& v) const;              // CrossProduct

        void operator<=(const Vector& smallVec);

        void operator>=(const Vector& largeVec);

        //length
        float Norm(void) const;

        //normals
        void Normalize();

    // other methods
    friend Vector operator*(float f, const Vector& v);
};

inline Vector operator*(float f, const Vector& v);

#endif //__Vector_H_
