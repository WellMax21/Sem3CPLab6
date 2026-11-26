#include <memory>

#include "ConsoleView.h"
#include "DefaultPrimitiveFactory.h"
#include "EditorController.h"
#include "EditorModel.h"
#include "FileDocumentStorage.h"

void onNewDocumentClicked(EditorController& controller) {
    controller.onNewDocument();
}

void onImportClicked(EditorController& controller, const std::string& path) {
    controller.onImportDocument(path);
}

void onExportClicked(EditorController& controller, const std::string& path) {
    controller.onExportDocument(path);
}

void onAddPrimitiveClicked(EditorController& controller, PrimitiveType type) {
    controller.onCreatePrimitive(type);
}

void onDeletePrimitiveClicked(EditorController& controller, int primitiveId) {
    controller.onRemovePrimitive(primitiveId);
}

void onRepaint(EditorController& controller) {
    controller.onShowDocument();
}

int main() {
    auto view = std::make_shared<ConsoleView>();
    auto model = std::make_shared<EditorModel>(std::make_shared<DefaultPrimitiveFactory>(),
                                               std::make_shared<FileDocumentStorage>());
    EditorController controller(model, view);

    onAddPrimitiveClicked(controller, PrimitiveType::Circle);  // ошибка: нет документа

    onNewDocumentClicked(controller);
    onAddPrimitiveClicked(controller, PrimitiveType::Line);
    onAddPrimitiveClicked(controller, PrimitiveType::Rectangle);
    onAddPrimitiveClicked(controller, PrimitiveType::Square);
    onAddPrimitiveClicked(controller, PrimitiveType::Circle);
    onRepaint(controller);

    onDeletePrimitiveClicked(controller, 2);
    onDeletePrimitiveClicked(controller, 42);  
    onRepaint(controller);

    onExportClicked(controller, "drawing.vec");
    onImportClicked(controller, "other.vec");
    onAddPrimitiveClicked(controller, PrimitiveType::Square);
    return 0;
}
