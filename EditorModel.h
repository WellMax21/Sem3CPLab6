#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "IDocumentStorage.h"
#include "IPrimitiveFactory.h"
#include "IView.h"

class EditorModel {
public:
    EditorModel(std::shared_ptr<IPrimitiveFactory> factory,
                std::shared_ptr<IDocumentStorage> storage)
        : factory_(std::move(factory)), storage_(std::move(storage)) {}

    void subscribe(const std::shared_ptr<IView>& view) { views_.push_back(view); }

    void createDocument() {
        document_ = std::make_shared<Document>(++lastDocumentId_);
        notify([this](IView& v) { v.onDocumentCreated(*document_); });
    }

    void importDocument(const std::string& path) {
        document_ = storage_->importFrom(path, ++lastDocumentId_);
        notify([this, &path](IView& v) { v.onDocumentImported(*document_, path); });
    }

    void exportDocument(const std::string& path) {
        Document& document = current();
        storage_->exportTo(document, path);
        notify([&document, &path](IView& v) { v.onDocumentExported(document, path); });
    }

    void createPrimitive(PrimitiveType type) {
        Document& document = current();
        std::shared_ptr<Primitive> primitive = factory_->create(type, document.nextPrimitiveId());
        document.add(primitive);
        notify([&document, &primitive](IView& v) { v.onPrimitiveAdded(document, *primitive); });
    }

    void removePrimitive(int primitiveId) {
        Document& document = current();
        std::shared_ptr<Primitive> removed = document.remove(primitiveId);
        if (!removed) {
            throw std::runtime_error("примитив №" + std::to_string(primitiveId) +
                                     " не найден в документе №" + std::to_string(document.id()));
        }
        notify([&document, &removed](IView& v) { v.onPrimitiveRemoved(document, *removed); });
    }

    void requestRender() {
        Document& document = current();
        notify([&document](IView& v) { v.render(document); });
    }

private:
    Document& current() {
        if (!document_) throw std::runtime_error("нет открытого документа");
        return *document_;
    }

    template <typename F>
    void notify(F action) {
        for (const auto& weak : views_) {
            if (auto view = weak.lock()) action(*view);
        }
    }

    std::shared_ptr<IPrimitiveFactory> factory_;
    std::shared_ptr<IDocumentStorage> storage_;
    std::shared_ptr<Document> document_;
    std::vector<std::weak_ptr<IView>> views_;
    int lastDocumentId_ = 0;
};
