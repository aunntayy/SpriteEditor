#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(pixelEditor* editor, int width, int height, int pixelSize, QWidget* parent)
    : QWidget(parent), editor(editor), pixelSize(pixelSize), brushSize(5), brushColor(Qt::white), currentTool(0) {
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
        qDebug() << "Mouse pressed at position:" << lastPoint << "with brush size:" << brushSize << "and color:" << brushColor;


    }
}

void Canvas::mouseMoveEvent(QMouseEvent* mouseEvent) {

}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {

}
