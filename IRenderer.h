#pragma once

#include "Geometry.h"

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void drawLine(const Point& from, const Point& to) = 0;
    virtual void drawRectangle(const Point& topLeft, double width, double height) = 0;
    virtual void drawCircle(const Point& center, double radius) = 0;
};
