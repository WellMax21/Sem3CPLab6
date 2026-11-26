#pragma once

#include <memory>
#include <string>

#include "Document.h"

class IDocumentStorage {
public:
    virtual ~IDocumentStorage() = default;

    virtual std::shared_ptr<Document> importFrom(const std::string& path, int documentId) = 0;
    virtual void exportTo(const Document& document, const std::string& path) = 0;
};
