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
            startMovePoint = QPoint(gridX, gridY);
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
        pixelData newPixel = {QPoint(x, y), currentBrushColor, pixelSize};
        drawnPixels.append(newPixel);

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

        // Remove the pixel from drawnPixels
        for (int i = 0; i < drawnPixels.size(); ++i) {
            if (drawnPixels[i].pixelCoor == QPoint(x, y)) {
                drawnPixels.removeAt(i);
                break;
            }
        }

        // Also remove the pixel from originalDrawnPixels
        for (int i = 0; i < originalDrawnPixels.size(); ++i) {
            if (originalDrawnPixels[i].pixelCoor == QPoint(x, y)) {
                originalDrawnPixels.removeAt(i);
                break;
            }
        }

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
            pixelData filledPoint = {QPoint((cx / pixelSize) * pixelSize, (cy / pixelSize) * pixelSize), currentBrushColor, pixelSize};
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

    // Move and redraw each pixel from originalDrawnPixels
    drawnPixels.clear();  // Clear drawnPixels to store new positions
    for (const pixelData &originalPoint : originalDrawnPixels) {
        QPoint newPoint = originalPoint.pixelCoor + QPoint(dx, dy);  // Apply offset

        // Set the brush to the pixel's original color
        painter.setBrush(originalPoint.currPixelColor);

        // Draw the pixel at the new position with its original size
        painter.drawRect(newPoint.x(), newPoint.y(), originalPoint.currPixleSize, originalPoint.currPixleSize);

        // Track the new position, color, and size in drawnPixels
        drawnPixels.append({newPoint, originalPoint.currPixelColor, originalPoint.currPixleSize});
    }

    // Update canvas with moved pixels
    canvasInstance->update();
}


void pixelEditor::setBrushColor(const QColor &color) {
    currentBrushColor = color;
}

void pixelEditor::addActionToHistory(int x, int y, const QColor& prevColor){
    actionHistory.push_back({QPoint(x, y), prevColor, pixelSize});
}

void pixelEditor::undoLastAction() {

    if (actionHistory.isEmpty() || !canvasInstance) return;
    pixelData lastAction = actionHistory.takeLast();

    QPainter painter(&canvasInstance->image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(lastAction.currPixelColor);
    painter.drawRect(lastAction.pixelCoor.x(), lastAction.pixelCoor.y(),lastAction.currPixleSize,lastAction.currPixleSize);
    canvasInstance->update();
}

