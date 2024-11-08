#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QGraphicsItem>
#include "pixeleditor.h"

class Canvas : public QWidget
{ Q_OBJECT
public:
    explicit Canvas(pixelEditor* editor, int width, int height, int pixelSize, QWidget* parent = nullptr);
    void drawPixel(int x, int y, const QColor& color, int size); // Test
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

private:
    QVector<QVector<QGraphicsRectItem*>> pixels;
    int pixelSize;
    QImage image;
    QPoint lastPoint;
    int brushSize = 10;
    QColor brushColor;
    int currentTool;

    pixelEditor* editor;
};

#endif // CANVAS_H
