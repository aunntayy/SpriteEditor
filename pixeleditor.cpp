#include "pixeleditor.h"
#include "canvas.h"
#include<QDebug>
#include<QPoint>
#include<QColor>
#include<QPainter>
#include<QStack>

pixelEditor::pixelEditor(QObject* parent) : QObject(parent), canvasInstance(nullptr) {

}

void pixelEditor::setTool(Tools pickTool){
    currentTool = pickTool;
}
void pixelEditor::setCanvasInstance(Canvas* canvas) {
    canvasInstance = canvas;
}

void pixelEditor::setPixelSize(int size){
    pixelSize = size;
}

void pixelEditor::drawWithCurrTool(QPoint point) {
    int gridX = (point.x() / pixelSize) * pixelSize;
    int gridY = (point.y() / pixelSize) * pixelSize;

    // Brush tool
    if (currentTool == 1) {
        drawPixel(gridX, gridY);
    }
    // Erase tool
    if (currentTool == 2) {
        erasePixel(gridX, gridY);
    }
    // Fill tool
    if (currentTool == 3) {
        fillColor(gridX, gridY);
    }
    // Move tool
    if (currentTool == 4) {
        if (!isMoving) {
            startMovePoint = point;
            originalDrawnPixels = drawnPixels;  // Capture original positions
            isMoving = true;
        } else {
            // Now move since it's a move event, not just setup
            movePixel(gridX, gridY);
        }
    } else {
        isMoving = false;
    }
    if(currentTool == 5){
        undoLastAction();
    }
}

void pixelEditor::drawPixel(int x, int y) {
    if (canvasInstance) {
        QColor prevColor = canvasInstance->image.pixelColor(x, y);
        addActionToHistory(x, y, prevColor);

        // range check
        if (x < 0 || x >= canvasInstance->width() || y < 0 || y >= canvasInstance->height()) {
            return;
        }

        QPainter painter(&canvasInstance->image);
        painter.setPen(Qt::NoPen); // Set no border
        painter.setBrush(currentBrushColor);

        // track the draw pixel
        QPoint newPoint(x, y);
        drawnPixels.append(newPoint);

        // Draw rect
        painter.drawRect(x, y, pixelSize, pixelSize);
        canvasInstance->update();
    }
}

void pixelEditor::erasePixel(int x, int y) {
    if (canvasInstance) {
        QColor prevColor = canvasInstance->image.pixelColor(x, y);
        addActionToHistory(x, y, prevColor);

        // range check
        if (x < 0 || x >= canvasInstance->width() || y < 0 || y >= canvasInstance->height()) {
            return;
        }

        QPainter painter(&canvasInstance->image);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));

        // Remove the erased pixel from `drawnPixels`
        QPoint pointToErase(x, y);
        drawnPixels.removeAll(pointToErase);

        // Draw rect
        painter.drawRect(x, y, pixelSize, pixelSize);
        canvasInstance->update();
    }
}

void pixelEditor::fillColor(int x, int y) {
    // take the current image object to modify directly
    QImage& currImage = canvasInstance->image;
    // get the clicked spot color
    QColor targetAreaColor = currImage.pixelColor(x, y);

    // if the fill color is the same color with the area that need to be fill
    if (targetAreaColor == currentBrushColor) {
        return; // Prevent infinite loop if the target color is the same as the fill color
    }
    // have a stack and put all the points in
    QStack<QPoint> points;
    points.push(QPoint(x, y));
    // fill Algo
    while (!points.isEmpty()) {
        QPoint currentPoint = points.pop();
        int cx = currentPoint.x();
        int cy = currentPoint.y();

        // range check
        if (cx < 0 || cx >= canvasInstance->width() || cy < 0 || cy >= canvasInstance->height()) {
            continue;  // Skip point out of bounds
        }

        // condition to fill all the points that is not the same color with the brush color
        if (currImage.pixelColor(cx, cy) == targetAreaColor) {
            currImage.setPixelColor(cx, cy, currentBrushColor);

            // Track filled pixel
            QPoint filledPoint((cx / pixelSize) * pixelSize, (cy / pixelSize) * pixelSize);
            drawnPixels.append(filledPoint);

            points.push(QPoint(cx + 1, cy));
            points.push(QPoint(cx - 1, cy));
            points.push(QPoint(cx, cy + 1));
            points.push(QPoint(cx, cy - 1));
        }
    }

    canvasInstance->update();
}

void pixelEditor::movePixel(int x, int y) {
    if (!canvasInstance || !isMoving) return;

    int dx = x - startMovePoint.x();
    int dy = y - startMovePoint.y();

    // Clear canvas to prepare for redrawing
    canvasInstance->image.fill(Qt::white);  // Fill with background color

    QPainter painter(&canvasInstance->image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(currentBrushColor);

    // Move and redraw each pixel from originalDrawnPixels
    drawnPixels.clear();  // Clear drawnPixels to store new positions
    for (const QPoint &originalPoint : originalDrawnPixels) {
        QPoint newPoint = originalPoint + QPoint(dx, dy);  // Apply offset

        // Draw at the new position
        painter.drawRect(newPoint.x(), newPoint.y(), pixelSize, pixelSize);

        // Track new position
        drawnPixels.append(newPoint);
    }

    // Update canvas with moved pixels
    canvasInstance->update();
}

void pixelEditor::setBrushColor(const QColor &color) {
    currentBrushColor = color;
}

void pixelEditor::addActionToHistory(int x, int y, const QColor& prevColor){
    actionHistory.push({x,y,prevColor});
}

void pixelEditor::undoLastAction() {
    if (actionHistory.isEmpty() || !canvasInstance) return;
    PixelAction lastAction = actionHistory.pop();
    QImage& image = canvasInstance->image;
    image.setPixelColor(lastAction.x, lastAction.y, lastAction.prevColor);

    canvasInstance->update();
}
