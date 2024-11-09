#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QGraphicsItem>

class Canvas : public QWidget{
    Q_OBJECT

public:
    explicit Canvas(int width, int height, int pixelSize, QWidget* parent = nullptr);
    QImage image;
    QPoint lastPoint;
    QColor brushColor;

signals:
    void mousePressCanvas(QPoint point, QColor color);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
};

#endif // CANVAS_H
