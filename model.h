#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include "frame.h"

class Model : public QObject {
    Q_OBJECT

public:
    Model(QObject *parent = nullptr);
    void addFrame();
    void duplicateFrame(int index);
    void removeFrame(int index);
    QVector<Frame*> getFrames() const;

signals:
    void updateFrameList();

private:
    QVector<Frame*> frameList;
};

#endif // MODEL_H
