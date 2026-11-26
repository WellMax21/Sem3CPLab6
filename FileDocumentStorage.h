#pragma once

#include "IDocumentStorage.h"

class FileDocumentStorage : public IDocumentStorage {
public:
    std::shared_ptr<Document> importFrom(const std::string&, int documentId) override {
        return std::make_shared<Document>(documentId);
    }

    void exportTo(const Document&, const std::string&) override {}
};
