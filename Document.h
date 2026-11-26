#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "IRenderer.h"
#include "Primitive.h"

class Document {
public:
    explicit Document(int id) : id_(id) {}

    int id() const { return id_; }

    int nextPrimitiveId() { return ++lastPrimitiveId_; }

    void add(std::shared_ptr<Primitive> primitive) {
        primitives_.push_back(std::move(primitive));
    }

   std::shared_ptr<Primitive> remove(int primitiveId) {
        auto it = std::find_if(primitives_.begin(), primitives_.end(),
                               [primitiveId](const std::shared_ptr<Primitive>& p) {
                                   return p->id() == primitiveId;
                               });
        if (it == primitives_.end()) return nullptr;
        std::shared_ptr<Primitive> removed = *it;
        primitives_.erase(it);
        return removed;
    }

    std::size_t size() const { return primitives_.size(); }

    void draw(IRenderer& renderer) const {
        for (const auto& primitive : primitives_) primitive->draw(renderer);
    }

    const std::vector<std::shared_ptr<Primitive>>& primitives() const { return primitives_; }

private:
    int id_;
    int lastPrimitiveId_ = 0;
    std::vector<std::shared_ptr<Primitive>> primitives_;
};
