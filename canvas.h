#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>

class Canvas : public QWidget
{ Q_OBJECT
public:
    explicit Canvas(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QImage image; // Image for drawing
    bool drawing; // Indicates if the mouse is pressed for drawing
    QPoint lastPoint; // Last mouse position for drawing lines
    int brushSize; // Brush size
    QColor brushColor; // Brush color
    int currentTool; // Current tool selected (integrated with pixelEditor)
};

#endif // CANVAS_H
