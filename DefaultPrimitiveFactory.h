#pragma once

#include <stdexcept>

#include "Circle.h"
#include "IPrimitiveFactory.h"
#include "Line.h"
#include "Rectangle.h"
#include "Square.h"

class DefaultPrimitiveFactory : public IPrimitiveFactory {
public:
    std::unique_ptr<Primitive> create(PrimitiveType type, int id) const override {
        switch (type) {
            case PrimitiveType::Line:
                return std::make_unique<Line>(id, Point{0, 0}, Point{10, 10});
            case PrimitiveType::Rectangle:
                return std::make_unique<Rectangle>(id, Point{0, 0}, 20, 10);
            case PrimitiveType::Circle:
                return std::make_unique<Circle>(id, Point{5, 5}, 5);
            case PrimitiveType::Square:
                return std::make_unique<Square>(id, Point{0, 0}, 10);
        }
        throw std::invalid_argument("неизвестный тип примитива");
    }
};
