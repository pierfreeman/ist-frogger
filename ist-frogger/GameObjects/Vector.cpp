//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Vector.h"
#include <cmath>


Vector::Vector(float xx, float yy, float zz){
    x = xx; y = yy; z = zz;
}

void Vector::Set(float xx, float yy, float zz) {
    x = xx; y = yy; z = zz;
}

// binary operators
Vector Vector::operator+(const Vector& c) const {
    return Vector(x + c.x, y + c.y, z + c.z);
}

Vector Vector::operator-(const Vector& c) const {
    return Vector(x - c.x, y - c.y, z - c.z);
}

Vector Vector::operator*(float f) const {
    return Vector(x * f, y * f, z * f);
}

Vector Vector::operator/(float f) const {
    return Vector(x / f, y / f, z / f);
}

// unary operators
void Vector::operator+=(float f) {
    x += f; y += f; z += f;
}

void Vector::operator+=(const Vector& c) {
    x += c.x; y += c.y; z += c.z;
}

void Vector::operator*=(float f) {
    x *= f; y *= f; z *= f;
}

Vector Vector::operator-(void) const {
    return Vector(-x, -y, -z);
}

// other methods
float Vector::operator*(const Vector& v) const {                // DotProduct
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator%(const Vector& v) const {               // CrossProduct
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

void Vector::operator<=(const Vector& smallVec) {
    if (x > smallVec.x) x = smallVec.x;
    if (y > smallVec.y) y = smallVec.y;
    if (z > smallVec.z) z = smallVec.z;
}

void Vector::operator>=(const Vector& largeVec) {
    if (x < largeVec.x) x = largeVec.x;
    if (y < largeVec.y) y = largeVec.y;
    if (z < largeVec.z) z = largeVec.z;
}
//length
float Vector::Norm(void) const {
    return sqrt(x*x + y*y + z*z);
}
//normal
void Vector::Normalize() {
    float norm = Norm();
    x /= norm;
    y /= norm;
    z /= norm;
}

inline Vector operator*(float f, const Vector& v) {
    return Vector(f * v.x, f * v.y, f * v.z);
}

