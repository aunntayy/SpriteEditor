#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H

#include <QObject>
#include<QColor>
#include <QPoint>

class Canvas;

class pixelEditor : public QObject
{
    Q_OBJECT
public:
    explicit pixelEditor(QObject* parent = nullptr);

    void setCanvasInstance(Canvas* canvas);
    enum Tools {
        ColorPicker,
        Brush,
        Erase,
        Fill,
        Move,
        Undo
    };

    void setTool(Tools pickTool);
    int setPixelSize(int size);

    void drawPixel(int x, int y, QColor color);
    void erasePixel(int x, int y, QColor color);

public slots:
    void drawWithCurrTool(QPoint point, QColor color);


private:
    Tools currentTool;
    int pixelSize;
    Canvas* canvasInstance;
};

#endif // PIXELEDITOR_H
