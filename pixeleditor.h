#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H
#include <QObject>
#include<QColor>
#include<QPoint>
#include <QStack>
class Canvas;

class pixelEditor : public QObject
{
    Q_OBJECT
public:
    explicit pixelEditor(QObject* parent = nullptr);

    void setCanvasInstance(Canvas* canvas);
    
    // Add in more tool after the last to keep the order right
    enum Tools {
        none,
        Brush,
        Erase,
        Fill,
        Move,
        Undo
    };
    // setting up tool spec
    void setTool(Tools pickTool);
    void setBrushColor(const QColor &color);
    void setPixelSize(int size);

    // Editing pixel
    void drawPixel(int x, int y);
    void erasePixel(int x, int y);
    void fillColor(int x, int y);
    void movePixel(int x, int y);

    void addActionToHistory(int x, int y, const QColor& prevColor);
    void undoLastAction();

public slots:
    void drawWithCurrTool(QPoint point);

private:
    struct PixelAction {
        int x, y;
        QColor prevColor;
    };

    Tools currentTool;
    int pixelSize;
    Canvas* canvasInstance;

    QVector<QPoint> drawnPixels;
    QVector<QPoint> originalDrawnPixels;
    QPoint startMovePoint;
    bool isMoving;
    QColor currentBrushColor;
    QStack<PixelAction> actionHistory;
};

#endif // PIXELEDITOR_H
