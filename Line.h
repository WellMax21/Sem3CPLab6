#pragma once

#include "Primitive.h"

class Line : public Primitive {
public:
    Line(int id, const Point& from, const Point& to) : Primitive(id), from_(from), to_(to) {}

    PrimitiveType type() const override { return PrimitiveType::Line; }
    void draw(IRenderer& renderer) const override { renderer.drawLine(from_, to_); }

private:
    Point from_;
    Point to_;
};
