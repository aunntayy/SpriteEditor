#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QColor>
#include <QPixmap>
#include "frame.h"

class Model : public QObject
{
    Q_OBJECT

public:
    Model(QObject *parent = nullptr);
    ~Model();

    bool isFileSaved() const;
    int getFrameRate() const;
    int getResolution() const;
    QVector<Frame*> getFrames() const;

    void fileSaved();
    void fileNotSaved();
    void setFrameRate(int newFrameRate);
    void setResolution(int newResolution);
    void addFrame();
    void duplicateFrame(int index);
    void removeFrame(int index);


private:
    //Tools selectedTool;
    int toolSize;
    QColor toolColor;
    int selectedFrame;
    int resolution;
    int frameRate;
    bool isSaved;

    QVector<Frame*> frameList;     // need to delete
    QVector<QPixmap> framesPixmap; // for displaying (preview and frames tab)
    QVector<QImage> framesImage;   // for the canvas

signals:
    void updateFrameList();

};

#endif // MODEL_H
