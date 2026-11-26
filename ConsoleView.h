#pragma once

#include <iostream>

#include "IRenderer.h"
#include "IView.h"

class ConsoleRenderer : public IRenderer {
public:
    void drawLine(const Point& from, const Point& to) override {
        std::cout << "  линия (" << from.x << ", " << from.y << ") -> (" << to.x << ", "
                  << to.y << ")\n";
    }
    void drawRectangle(const Point& topLeft, double width, double height) override {
        std::cout << "  прямоугольник (" << topLeft.x << ", " << topLeft.y << ") " << width
                  << "x" << height << "\n";
    }
    void drawCircle(const Point& center, double radius) override {
        std::cout << "  окружность (" << center.x << ", " << center.y << ") r=" << radius
                  << "\n";
    }
};

class ConsoleView : public IView {
public:
    void onDocumentCreated(const Document& document) override {
        std::cout << "создан документ №" << document.id() << '\n';
    }
    void onDocumentImported(const Document& document, const std::string& path) override {
        std::cout << "документ №" << document.id() << " импортирован из файла \"" << path
                  << "\"\n";
    }
    void onDocumentExported(const Document& document, const std::string& path) override {
        std::cout << "документ №" << document.id() << " экспортирован в файл \"" << path
                  << "\"\n";
    }
    void onPrimitiveAdded(const Document& document, const Primitive& primitive) override {
        std::cout << "в документ №" << document.id() << " добавлен примитив \""
                  << primitive.title() << "\"\n";
    }
    void onPrimitiveRemoved(const Document& document, const Primitive& primitive) override {
        std::cout << "из документа №" << document.id() << " удалён примитив \""
                  << primitive.title() << "\"\n";
    }
    void render(const Document& document) override {
        std::cout << "отрисовка документа №" << document.id() << " (примитивов: "
                  << document.size() << ")\n";
        ConsoleRenderer renderer;
        document.draw(renderer);
    }
    void showError(const std::string& message) override {
        std::cout << "ошибка: " << message << '\n';
    }
};
