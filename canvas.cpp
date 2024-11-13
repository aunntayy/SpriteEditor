#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(int width, int height, QWidget* parent)
    : QWidget(parent) {
    brushColor = QColor(Qt::black);
    image = QImage(width, height, QImage::Format_RGB888);
    image.fill(Qt::white);
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
        update();
        emit sendCurrentImage(image);  // Emit the updated image
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        emit canvasModified(image);
    }
}

void Canvas::drawFromFrame(Frame* frame) {
    if (!frame) return;
    const QImage& frameImage = frame->getImage();
    if (image.size() != frameImage.size()) {
        image = frameImage.scaled(image.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    } else {
        image = frameImage;
    }

    update();
}

void Canvas::updateFrameFromCanvas(Frame* frame) {
    image = QImage(800, 800, QImage::Format_RGB888);
    image.fill(Qt::white);
    drawFromFrame(frame);
    repaint();
    emit sendCurrentImage(image);
}

void Canvas::clear() {
    image.fill(Qt::white);
    update();
}
