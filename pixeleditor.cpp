#include "pixeleditor.h"
#include "canvas.h"
#include<QDebug>
#include<QPoint>
#include<QColor>
#include<QPainter>

pixelEditor::pixelEditor(QObject* parent) : QObject(parent), canvasInstance(nullptr) {}

void pixelEditor::setTool(Tools pickTool){
    currentTool = pickTool;


}
void pixelEditor::setCanvasInstance(Canvas* canvas) {
    canvasInstance = canvas;
}

int pixelEditor::setPixelSize(int size){
    return pixelSize = size;
    qDebug() << "Tool set to:" << pixelSize;
}

void pixelEditor::drawWithCurrTool(QPoint point, QColor color) {

    qDebug() << "Drawing at" << point << "using tool" << currentTool;
    // Brush tool
    if (currentTool == 1) {
        drawPixel(point.x(), point.y(), color);
    }
    if (currentTool == 2) {
        erasePixel(point.x(), point.y(), color);
    }
}

void pixelEditor::drawPixel(int x, int y, QColor color) {
    if (canvasInstance) {
        // Get nearest grid point based on pixel size
        int gridX = (x / pixelSize) * pixelSize;
        int gridY = (y / pixelSize) * pixelSize;

        QPainter painter(&canvasInstance->image);
        painter.setPen(Qt::NoPen); // Set no border
        painter.setBrush(QBrush(Qt::red)); // Test color for now

        // Draw rect
        painter.drawRect(gridX, gridY, pixelSize, pixelSize);

        canvasInstance->update();
        qDebug() << "Pixel drawn at grid(" << gridX << "," << gridY << ") with color" << color << "and size" << pixelSize;
    }
}

void pixelEditor::erasePixel(int x, int y, QColor color) {
    if (canvasInstance) {
        // Get nearest grid point based on pixel size
        int gridX = (x / pixelSize) * pixelSize;
        int gridY = (y / pixelSize) * pixelSize;

        QPainter painter(&canvasInstance->image);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));

        // Draw rect
        painter.drawRect(gridX, gridY, pixelSize, pixelSize);

        canvasInstance->update();
        qDebug() << "Pixel drawn at grid-aligned (" << gridX << "," << gridY << ") with color" << color << "and size" << pixelSize;
    }
}
