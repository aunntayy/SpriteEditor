#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include "frame.h"

class Canvas : public QWidget{
    Q_OBJECT

public:
    explicit Canvas(int width, int heigh, QWidget* parent = nullptr);
    void clear();
    void updateFrameFromCanvas(Frame* frame);
    void drawFromFrame(Frame* frame);
    QImage image;

signals:
    void mousePressCanvas(QPoint point);
    void sendCurrentImage(const QImage& img);
    void canvasModified(const QImage& image);

private:
    QPoint lastPoint;
    QColor brushColor;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
};

#endif // CANVAS_H
