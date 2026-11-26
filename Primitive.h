#pragma once

#include <string>

#include "IRenderer.h"

enum class PrimitiveType { Line, Rectangle, Circle, Square };

inline std::string toString(PrimitiveType type) {
    switch (type) {
        case PrimitiveType::Line: return "линия";
        case PrimitiveType::Rectangle: return "прямоугольник";
        case PrimitiveType::Circle: return "окружность";
        case PrimitiveType::Square: return "квадрат";
    }
    return "неизвестный примитив";
}

class Primitive {
public:
    explicit Primitive(int id) : id_(id) {}
    virtual ~Primitive() = default;

    int id() const { return id_; }
    virtual PrimitiveType type() const = 0;
    virtual void draw(IRenderer& renderer) const = 0;

    std::string title() const { return toString(type()) + " №" + std::to_string(id_); }

private:
    int id_;
};
