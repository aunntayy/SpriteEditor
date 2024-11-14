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
}

void pixelEditor::drawPixel(int x, int y) {
    if (canvasInstance) {
        QColor prevColor = canvasInstance->image.pixelColor(x, y);
        if(prevColor != currentBrushColor){
            addActionToHistory(x, y, prevColor);
        }

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

        // Only proceed if the pixel is not already white
        if (prevColor != Qt::white) {

            // Save the current color for undo
            addActionToHistory(x, y, prevColor);

            // Set up the painter to draw the erase color (white)
            QPainter painter(&canvasInstance->image);
            painter.setPen(Qt::NoPen);
            painter.setBrush(Qt::white);

            // Draw a white rectangle at the specified grid position
            painter.drawRect(x, y, pixelSize, pixelSize);

            // Append the action to drawnPixels as white to represent the erase action
            pixelData erasedPixel = {QPoint(x, y), Qt::white, pixelSize};
            drawnPixels.append(erasedPixel);

            // Update the canvas to show the erased area
            canvasInstance->update();
        }
    }
}

void pixelEditor::fillColor(int x, int y) {
    QImage& currImage = canvasInstance->image;
    QColor targetAreaColor = currImage.pixelColor(x, y);

    // Prevent infinite loop if the target color is the same as the fill color
    if (targetAreaColor == currentBrushColor) {
        return;
    }

    // Stack for fill algorithm
    QStack<QPoint> points;
    points.push(QPoint(x, y));

    // Temporary list to store all affected pixels for this fill action
    QVector<pixelData> fillAction;

    while (!points.isEmpty()) {
        QPoint currentPoint = points.pop();
        int cx = (currentPoint.x() / pixelSize) * pixelSize;
        int cy = (currentPoint.y() / pixelSize) * pixelSize;

        // Range check
        if (cx < 0 || cx >= canvasInstance->width() || cy < 0 || cy >= canvasInstance->height()) {
            continue;
        }

        // Check if the pixel at the grid position matches the target color
        if (currImage.pixelColor(cx, cy) == targetAreaColor) {
            // Save the current color and grid position to fillAction before filling
            fillAction.append({QPoint(cx, cy), targetAreaColor, pixelSize});

            // Track the filled pixel in drawnPixels
            pixelData fillPixel = {QPoint(cx, cy), currentBrushColor, pixelSize};
            drawnPixels.append(fillPixel);

            // Set the pixel color to the fill color within the grid cell
            QPainter painter(&currImage);
            painter.setPen(Qt::NoPen);
            painter.setBrush(currentBrushColor);
            painter.drawRect(cx, cy, pixelSize, pixelSize);

            // Add neighboring grid points to the stack
            points.push(QPoint(cx + pixelSize, cy));
            points.push(QPoint(cx - pixelSize, cy));
            points.push(QPoint(cx, cy + pixelSize));
            points.push(QPoint(cx, cy - pixelSize));
        }
    }

    // Save the entire fill action as a single entry in the action history
    actionHistory.append(fillAction);
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
        // Track the moved pixel in drawnPixels
        addActionToHistory(newPoint.x(), newPoint.y(),  originalPoint.currPixleSize);
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
    // Track the undo pixel in drawnPixels
    pixelData undoPixel = {QPoint(lastAction.pixelCoor.x(), lastAction.pixelCoor.y()), lastAction.currPixelColor, lastAction.currPixleSize};
    drawnPixels.append(undoPixel);
    canvasInstance->update();
}

