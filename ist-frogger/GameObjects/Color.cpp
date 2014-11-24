//
// Created by Piercarlo Serena on 24/11/14.
//

#include "Color.h"


//Constructors and operators remapping
Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(float rr, float gg, float bb) {
    r = rr; g = gg; b = bb;
}

// binary operators
Color Color::operator+(const Color& c) const {
    return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator*(float f) const {
    return Color(r * f, g * f, b * f);
}

Color Color::operator*(const Color& c) const {
    return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator/(float f) const {
    return Color(r / f, g / f, b / f);
}

// unary operators
void Color::operator+=(const Color& c) {
    r += c.r; g += c.g; b += c.b;
}

inline Color operator*(float f, const Color& c) {
    return Color(f * c.r, f * c.g, f * c.b);
};