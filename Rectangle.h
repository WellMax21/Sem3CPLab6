#pragma once

#include "Primitive.h"

class Rectangle : public Primitive {
public:
    Rectangle(int id, const Point& topLeft, double width, double height)
        : Primitive(id), topLeft_(topLeft), width_(width), height_(height) {}

    PrimitiveType type() const override { return PrimitiveType::Rectangle; }
    void draw(IRenderer& renderer) const override {
        renderer.drawRectangle(topLeft_, width_, height_);
    }

private:
    Point topLeft_;
    double width_;
    double height_;
};
