#include "framemanager.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

FrameManager::FrameManager() {}

void FrameManager::addFrame()
{
    QGraphicsView *newFrame = new QGraphicsView();
    framesStack.push_back(newFrame);
}

void FrameManager::duplicateFrame(int frameNumber)
{
    if (frameNumber < 0 || frameNumber >= framesStack.size())
    {
        return;
    }
    QGraphicsScene* originalFrame = framesStack[frameNumber]->scene();
    QGraphicsView *newFrame = new QGraphicsView(originalFrame);
    framesStack.push_back(newFrame);
}

int FrameManager::numberOfFrames() const
{
    return framesStack.size();
}

QGraphicsView* FrameManager::getFrame(int frameNumber) const
{
    if (frameNumber < 0 || frameNumber >= framesStack.size())
    {
        return nullptr;
    }
    return framesStack[frameNumber];
}
