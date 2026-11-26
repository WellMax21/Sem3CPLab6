#pragma once

#include <string>

#include "Document.h"
#include "Primitive.h"

class IView {
public:
    virtual ~IView() = default;

    virtual void onDocumentCreated(const Document& document) = 0;
    virtual void onDocumentImported(const Document& document, const std::string& path) = 0;
    virtual void onDocumentExported(const Document& document, const std::string& path) = 0;
    virtual void onPrimitiveAdded(const Document& document, const Primitive& primitive) = 0;
    virtual void onPrimitiveRemoved(const Document& document, const Primitive& primitive) = 0;
    virtual void render(const Document& document) = 0;
    virtual void showError(const std::string& message) = 0;
};
