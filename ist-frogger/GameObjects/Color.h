//
// Created by Piercarlo Serena on 24/11/14.
//


#ifndef __Color_H_
#define __Color_H_


class Color {
public:
    float r, g, b;          // color coefficients on the representative wavelengths

//Constructors and operators remapping
    Color();

    Color(float rr, float gg, float bb);

    // binary operators
    Color operator+(const Color& c) const;

    Color operator*(float f) const;

    Color operator*(const Color& c) const;

    Color operator/(float f) const;

    // unary operators
    void operator+=(const Color& c);

    friend Color operator*(float f, const Color& c);
};

inline Color operator*(float f, const Color& c);

#endif //__Color_H_
