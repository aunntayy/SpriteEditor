#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QGraphicsView>

class FrameManager
{
public:
    FrameManager();

    void addFrame();
    void  duplicateFrame(int frameIndex);
    int numberOfFrames() const;
    QGraphicsView* getFrame(int index) const;

private:
    std::vector<QGraphicsView*> framesStack;
};

#endif // FRAMEMANAGER_H
