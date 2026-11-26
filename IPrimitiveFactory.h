#pragma once

#include <memory>

#include "Primitive.h"

class IPrimitiveFactory {
public:
    virtual ~IPrimitiveFactory() = default;

    virtual std::unique_ptr<Primitive> create(PrimitiveType type, int id) const = 0;
};
