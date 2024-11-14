/*
 * Model.h
 *
 * @brief Defines the Model class, which manages the application's core data,
 * including frames, resolution, frame rate, and file save status. Model provides
 * functions to add, duplicate, and remove frames, as well as update the current
 * frame's image. It emits signals to update the frame list and drawing panel when
 * changes occur.
 *
 * Author: Thu Ha - Phuc Hoang
 * Date: 11/07/2024
 * Reviewed by: Thu Ha
 */

#include "model.h"
#include <QDebug>

Model::Model(QObject *parent) : QObject(parent), currentFrameIndex(-1) {
    isSaved = false;

    resolution = 128;
    frameRate = 25;

    // default tool settings
    //selectedTool = brush;
    toolSize = 5;
    toolColor = QColor(0, 0, 0);

    qDebug() << "NEW MODEL CREATED";
}

Model::~Model() {
    qDeleteAll(frameList);
    frameList.clear();
}

void Model::addFrame() {
    Frame* newFrame = new Frame(800, 800);
    frameList.append(newFrame);
    currentFrameIndex = frameList.size() - 1;
    emit updateFrameList();
    emit updateDrawingPanel(newFrame);
    qDebug() << "Frame added. Total frames:" << frameList.size();
}

void Model::duplicateFrame(int index) {
    if (index >= 0 && index < frameList.size()) {
        Frame* newFrame = new Frame(*frameList[index]);
        frameList.insert(index + 1, newFrame);
        emit updateFrameList();
        emit updateDrawingPanel(newFrame);
        qDebug() << "Frame duplicated at index" << index << ". Total frames:" << frameList.size();
    }
}

void Model::removeFrame(int index) {
    if (index >= 0 && index < frameList.size()) {
        delete frameList[index];
        frameList.removeAt(index);
        currentFrameIndex = (index == frameList.size()) ? index - 1 : index;
        emit updateFrameList();
        emit frameRemoved();
        qDebug() << "Frame removed at index" << index << ". Total frames:" << frameList.size();
    }
}

QVector<Frame*> Model::getFrames() const {
    return frameList;
}

Frame* Model::getCurrentFrame() const {
    return (currentFrameIndex >= 0 && currentFrameIndex < frameList.size()) ? frameList[currentFrameIndex] : nullptr;
}

void Model::setCurrentFrameIndex(int index) {
    if (index >= 0 && index < frameList.size()) {
        currentFrameIndex = index;
        emit updateDrawingPanel(frameList[index]);
    }
}
void Model::updateCurrentFrameImage(const QImage& img) {
    if (currentFrameIndex >= 0 && currentFrameIndex < frameList.size()) {
        qDebug() << "Updating frame at index:" << currentFrameIndex;
        frameList[currentFrameIndex]->setImage(img);
        emit updateFrameList();
    }
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
