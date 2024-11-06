#include "framestab.h"
#include <QScrollBar>

FramesTab::FramesTab(FrameManager* frameManager, QWidget *parent)
    : QWidget(parent), frameManager(frameManager)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    scrollArea = new QScrollArea(this);
    framesList = new QWidget();
    framePanel = new QVBoxLayout(framesList);

    scrollArea -> setWidget(framesList);
    mainLayout -> addWidget(scrollArea);

    addFrameButton = new QPushButton("Add Frame", this);
    duplicateButton = new QPushButton("Duplicate Frame", this);

    connectSignalsAndSlots();

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons -> addWidget(addFrameButton);
    buttons -> addWidget(duplicateButton);
    mainLayout -> addLayout(buttons);

    updateFrameList();
}

void FramesTab::connectSignalsAndSlots()
{
    connect(addFrameButton, &QPushButton::clicked, this, &FramesTab::onAddFrameClicked);
    connect(duplicateButton, &QPushButton::clicked, this, &FramesTab::onDuplicateFrameClicked);
}

void FramesTab::onAddFrameClicked()
{
    frameManager -> addFrame();
    updateFrameList();
}

void FramesTab::onDuplicateFrameClicked()
{
    int currFrameIndex = scrollArea -> verticalScrollBar() -> value();
    if(currFrameIndex != -1)
    {
        frameManager -> duplicateFrame(currFrameIndex);
        updateFrameList();
    }
}

void FramesTab::updateFrameList()
{
    QLayoutItem *leftOverItem;
    while((leftOverItem = framePanel->itemAt(0)) != nullptr)
    {
        delete leftOverItem->widget();
        delete leftOverItem;
    }

    for (int i = 0; i < frameManager->numberOfFrames(); i++)
    {
        QGraphicsView *frame = frameManager->getFrame(i);

        QWidget *frameWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(frameWidget);

        frame->setParent(frameWidget);
        layout->addWidget(frame);
        framePanel->addWidget(frameWidget);
    }
    framesList->setLayout(framePanel);
}

