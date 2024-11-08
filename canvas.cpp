#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget* parent)
    : QWidget(parent), drawing(false), brushSize(5), brushColor(Qt::white), currentTool(0) {
    image = QImage(size(), QImage::Format_ARGB32);
    image.fill(Qt::black); // Initial canvas color
    setAttribute(Qt::WA_StaticContents);
}

void Canvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = event->pos();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if (drawing && event->buttons() & Qt::LeftButton) {
        if (currentTool == 1) { // Assuming 1 is Brush from pixelEditor
            QPainter painter(&image);
            painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}
