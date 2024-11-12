#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include "frame.h"

class Model : public QObject {
    Q_OBJECT

public:
    Model(QObject *parent = nullptr);
    ~Model();

    void addFrame();
    void duplicateFrame(int index);
    void removeFrame(int index);
    bool isFileSaved() const;
    int getFrameRate() const;
    int getResolution() const;
    QVector<Frame*> getFrames() const;
    Frame* getCurrentFrame() const;
    void setCurrentFrameIndex(int index);
    void updateCurrentFrameImage(const QImage& img);
    void fileSaved();
    void fileNotSaved();
    void setFrameRate(int newFrameRate);
    void setResolution(int newResolution);

signals:
    void updateFrameList();
    void updateDrawingPanel(Frame* frame);
    void frameRemoved();

private:
    int toolSize;
    QColor toolColor;
    int selectedFrame;
    int resolution;
    int frameRate;
    bool isSaved;
    QVector<Frame*> frameList;
    int currentFrameIndex;

};

#endif // MODEL_H
