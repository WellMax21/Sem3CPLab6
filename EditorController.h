#pragma once

#include <exception>
#include <memory>
#include <string>

#include "EditorModel.h"
#include "IView.h"

class EditorController {
public:
    EditorController(std::shared_ptr<EditorModel> model, std::shared_ptr<IView> view)
        : model_(std::move(model)), view_(std::move(view)) {
        model_->subscribe(view_);
    }

    void onNewDocument() {
        handle([this] { model_->createDocument(); });
    }
    void onImportDocument(const std::string& path) {
        handle([this, &path] { model_->importDocument(path); });
    }
    void onExportDocument(const std::string& path) {
        handle([this, &path] { model_->exportDocument(path); });
    }
    void onCreatePrimitive(PrimitiveType type) {
        handle([this, type] { model_->createPrimitive(type); });
    }
    void onRemovePrimitive(int primitiveId) {
        handle([this, primitiveId] { model_->removePrimitive(primitiveId); });
    }
    void onShowDocument() {
        handle([this] { model_->requestRender(); });
    }

private:
    template <typename F>
    void handle(F action) {
        try {
            action();
        } catch (const std::exception& e) {
            view_->showError(e.what());
        }
    }

    std::shared_ptr<EditorModel> model_;
    std::shared_ptr<IView> view_;
};
