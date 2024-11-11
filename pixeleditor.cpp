#include "pixeleditor.h"
#include "canvas.h"
#include<QDebug>
#include<QPoint>
#include<QColor>
#include<QPainter>
#include<QStack>

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
        drawPixel(point.x(), point.y(), currentBrushColor);
    }
    if (currentTool == 2) {
        erasePixel(point.x(), point.y(), currentBrushColor);
    }
    if (currentTool == 3) {
        fillColor(point.x(), point.y(), currentBrushColor);
    }

    if(currentTool == 5){
        undoLastAction();
    }
}

void pixelEditor::drawPixel(int x, int y, QColor color) {
    if (canvasInstance) {
        // Get nearest grid point based on pixel size
        int gridX = (x / pixelSize) * pixelSize;
        int gridY = (y / pixelSize) * pixelSize;

        QColor prevColor = canvasInstance->image.pixelColor(gridX, gridY);
        addActionToHistory(gridX, gridY, prevColor);

        QPainter painter(&canvasInstance->image);
        painter.setPen(Qt::NoPen); // Set no border
        painter.setBrush(currentBrushColor); // Test color for now

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

        QColor prevColor = canvasInstance->image.pixelColor(gridX, gridY);
        addActionToHistory(gridX, gridY, prevColor);

        QPainter painter(&canvasInstance->image);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));

        // Draw rect
        painter.drawRect(gridX, gridY, pixelSize, pixelSize);

        canvasInstance->update();
        qDebug() << "Pixel drawn at grid(" << gridX << "," << gridY << ") with color" << color << "and size" << pixelSize;
    }
}

void pixelEditor::fillColor(int x, int y, QColor color){
    // Getting the image maybe ???
    QImage& image = canvasInstance->image;
    if (x < 0 || y < 0 || x >= image.width() || y >= image.height()) {
        return; // Out of bounds check
        qDebug() <<"Out of bound";
    }

    QStack<QPoint> points;
    points.push(QPoint(x, y));
    // Algo for fill isnt working
    while (!points.isEmpty()) {
        QPoint currentPoint = points.pop();
        int cx = currentPoint.x();
        int cy = currentPoint.y();

        if (cx < 0 || cy < 0 || cx >= image.width() || cy >= image.height()) {
            continue; // Skip out-of-bounds points
        }

        if (image.pixelColor(cx, cy) == Qt::red) {
            image.setPixelColor(cx, cy, Qt::red);

            // Color the neighboor point
            points.push(QPoint(cx + 1, cy));
            points.push(QPoint(cx - 1, cy));
            points.push(QPoint(cx, cy + 1));
            points.push(QPoint(cx, cy - 1));
        }
    }

    canvasInstance->update();
}

void pixelEditor::setBrushColor(const QColor &color) {
    currentBrushColor = color;
    qDebug() << "Brush color set to:" << currentBrushColor.name();
}

void pixelEditor::addActionToHistory(int x, int y, const QColor& prevColor){
    qDebug() << "Adding action to history:" << "X:" << x << "Y:" << y << "PrevColor:" << prevColor.name();
    actionHistory.push({x,y,prevColor});
}

void pixelEditor::undoLastAction() {
    if (actionHistory.isEmpty() || !canvasInstance) return;
    PixelAction lastAction = actionHistory.pop();
    qDebug() << "Undoing last action at X:" << lastAction.x << "Y:" << lastAction.y << "PrevColor:" << lastAction.prevColor.name();


    QImage& image = canvasInstance->image;
    image.setPixelColor(lastAction.x, lastAction.y, lastAction.prevColor);

    canvasInstance->update();
}
