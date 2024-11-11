#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H

#include <QObject>
#include<QColor>
#include <QPoint>
#include <QStack>
class Canvas;



class pixelEditor : public QObject
{
    Q_OBJECT
public:
    explicit pixelEditor(QObject* parent = nullptr);

    void setCanvasInstance(Canvas* canvas);
    // Add in more tool after undo to keep the order right
    enum Tools {
        none,
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
    void fillColor(int x, int y, QColor color);
    void setBrushColor(const QColor &color);

    void addActionToHistory(int x, int y, const QColor& prevColor);
    void undoLastAction();
public slots:
    void drawWithCurrTool(QPoint point, QColor color);


private:
    struct PixelAction {
        int x, y;
        QColor prevColor;
    };

    Tools currentTool;
    int pixelSize;
    Canvas* canvasInstance;
    QColor currentBrushColor;
    QStack<PixelAction> actionHistory;

};

#endif // PIXELEDITOR_H
