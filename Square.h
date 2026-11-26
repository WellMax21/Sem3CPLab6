#pragma once

#include "Primitive.h"

class Square : public Primitive {
public:
    Square(int id, const Point& topLeft, double side)
        : Primitive(id), topLeft_(topLeft), side_(side) {}

    PrimitiveType type() const override { return PrimitiveType::Square; }
    void draw(IRenderer& renderer) const override {
        renderer.drawRectangle(topLeft_, side_, side_);
    }

private:
    Point topLeft_;
    double side_;
};
