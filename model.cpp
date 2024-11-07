#include "model.h"
#include <QDebug>

Model::Model(QObject *parent) : QObject(parent) {}

void Model::addFrame() {
    frameList.append(new Frame());
    emit updateFrameList();
    qDebug() << "Frame added. Total frames:" << frameList.size();
}

void Model::duplicateFrame(int index) {
    if (index >= 0 && index < frameList.size()) {
         frameList.insert(index + 1, new Frame(*frameList[index]));
        qDebug() << "Frame duplicated at index" << index << ". Total frames:" << frameList.size();
        emit updateFrameList();
    }
}

void Model::removeFrame(int index) {
    if (index >= 0 && index < frameList.size()) {
        delete frameList[index];
        frameList.removeAt(index);
        qDebug() << "Frame removed at index" << index << ". Total frames:" << frameList.size();
        emit updateFrameList();
    }
}

QVector<Frame*> Model::getFrames() const {
    return frameList;
}
