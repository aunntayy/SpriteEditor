#include "model.h"
#include <QDebug>
#include <QColor>

Model::Model(QObject *parent) : QObject(parent)
{
    isSaved = false;

    addFrame();
    resolution = 128;
    frameRate = 25;

    // default tool settings
    //selectedTool = brush;
    toolSize = 5;
    toolColor = QColor(0, 0, 0);

}

Model::~Model()
{
    qDeleteAll(frameList);
    frameList.clear();
}


void Model::addFrame()
{
    frameList.append(new Frame());
    emit updateFrameList();
    //selectedFrame =       // need to set selected frame to this new frame
    qDebug() << "Frame added. Total frames:" << frameList.size();
}

void Model::duplicateFrame(int index)
{
    if (index >= 0 && index < frameList.size())
    {
        frameList.insert(index + 1, new Frame(*frameList[index]));
        qDebug() << "Frame duplicated at index" << index << ". Total frames:" << frameList.size();
        emit updateFrameList();
    }
}

void Model::removeFrame(int index)
{
    if (index >= 0 && index < frameList.size())
    {
        delete frameList[index];
        frameList.removeAt(index);
        qDebug() << "Frame removed at index" << index << ". Total frames:" << frameList.size();
        emit updateFrameList();
    }
}

QVector<Frame*> Model::getFrames() const
{
    return frameList;
}

int Model::getFrameRate() const
{
    return frameRate;
}

void Model::setFrameRate(int newFrameRate)
{
    frameRate = newFrameRate;
}

int Model::getResolution() const
{
    return resolution;
}

void Model::setResolution(int newResolution)
{
    resolution = newResolution;
}

bool Model::isFileSaved() const
{
    return isSaved;
}

void Model::fileSaved()
{
    isSaved = true;
}

void Model::fileNotSaved()
{
    isSaved = false;
}
