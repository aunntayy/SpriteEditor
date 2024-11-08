#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>

#include "pixeleditor.h"

class Canvas : public QWidget
{ Q_OBJECT
public:
    explicit Canvas(pixelEditor* editor, int width, int height, int pixelSize, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    int pixelSize;
    QImage image;
    QPoint lastPoint;
    int brushSize;
    QColor brushColor;
    int currentTool;

    pixelEditor* editor;
};

#endif // CANVAS_H
