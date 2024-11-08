#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H

#include <QObject>

class pixelEditor : public QObject
{
    Q_OBJECT
public:
    explicit pixelEditor(QObject* parent = nullptr);

    enum Tools {
        ColorPicker,
        Brush,
        Erase,
        Fill,
        Move,
        Undo
    };

    void setTool(Tools pickTool);
    int setToolSize(int toolSize);
signals:
    void toolChanged();
    void brushSizeChanged(int size);
private:
    Tools currentTool;
    int currentToolSize;
};

#endif // PIXELEDITOR_H
