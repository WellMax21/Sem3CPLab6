#pragma once

#include "Primitive.h"

class Circle : public Primitive {
public:
    Circle(int id, const Point& center, double radius)
        : Primitive(id), center_(center), radius_(radius) {}

    PrimitiveType type() const override { return PrimitiveType::Circle; }
    void draw(IRenderer& renderer) const override { renderer.drawCircle(center_, radius_); }

private:
    Point center_;
    double radius_;
};
