#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(int width, int height, QWidget* parent)
    : QWidget(parent), brushColor(Qt::white) {
    image = QImage(width, height, QImage::Format_ARGB32);
    image.fill(Qt::white); // Initial canvas color
    setFixedSize(width, height); // Set the canvas size
    setAttribute(Qt::WA_StaticContents);
}

void Canvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void Canvas::mousePressEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        lastPoint = mouseEvent->pos();
        emit mousePressCanvas(lastPoint);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->buttons() & Qt::LeftButton) {
        lastPoint = mouseEvent->pos();
        emit mousePressCanvas(lastPoint);
    }
}

