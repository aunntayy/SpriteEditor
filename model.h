#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QColor>
#include "frame.h"

class Model : public QObject {
    Q_OBJECT

public:
    Model(QObject *parent = nullptr);
    ~Model();
    void addFrame();
    void duplicateFrame(int index);
    void removeFrame(int index);
    QVector<Frame*> getFrames() const;

private:
    //Tool selectedTool;
    int toolSize;
    QColor toolColor;
    int selectedFrame;
    int resolution;
    int frameRate;
    QVector<Frame*> frameList;

signals:
    void updateFrameList();

};

#endif // MODEL_H
