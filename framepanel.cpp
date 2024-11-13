#include "framepanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QIcon>

FramePanel::FramePanel(Model *model, QWidget *parent)
    : QWidget(parent), model(model) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget();
    frameLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(frameLayout);
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    // Buttons for Add, Duplicate, and Remove
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    addButton = new QPushButton("Add", this);
    connect(addButton, &QPushButton::clicked, this, &FramePanel::onAddFrame);
    buttonLayout->addWidget(addButton);

    duplicateButton = new QPushButton("Duplicate", this);
    connect(duplicateButton, &QPushButton::clicked, this, &FramePanel::onDuplicateFrame);
    buttonLayout->addWidget(duplicateButton);

    removeButton = new QPushButton("Remove", this);
    connect(removeButton, &QPushButton::clicked, this, &FramePanel::onRemoveFrame);
    buttonLayout->addWidget(removeButton);

    mainLayout->addLayout(buttonLayout);
    connect(model, &Model::updateFrameList, this, &FramePanel::updateFrameList);

    onAddFrame();
}

void FramePanel::onAddFrame() {
    model->addFrame();
    emit clearCanvas();
    qDebug() << "Add Frame triggered";
}

// FramePanel::onDuplicateFrame()
void FramePanel::onDuplicateFrame() {
    if (selectedFrameIndex >= 0 && selectedFrameIndex < model->getFrames().size()) {
        model->duplicateFrame(selectedFrameIndex);
        qDebug() << "Duplicate Frame triggered for index: " << selectedFrameIndex;
    }
}

// FramePanel::onRemoveFrame()
void FramePanel::onRemoveFrame() {
    if (selectedFrameIndex >= 0 && selectedFrameIndex < model->getFrames().size()) {
        model->removeFrame(selectedFrameIndex);
        qDebug() << "Remove Frame triggered for index: " << selectedFrameIndex;
    }
}

// FramePanel::selectFrame(int index)
void FramePanel::selectFrame(int index) {
    if (index >= 0 && index < model->getFrames().size()) {
        selectedFrameIndex = index;
        model->setCurrentFrameIndex(index);
        Frame* selectedFrame = model->getFrames()[index];
        emit frameSelected(selectedFrame);
        qDebug() << "Frame selected: " << index;
        highlightSelectedFrame(index);
    }
}
void FramePanel::addFrameButton(int index) {
    QPushButton *button = new QPushButton(QString::number(index + 1), this);
    button->setFixedSize(100, 100);
    connect(button, &QPushButton::clicked, [this, index]() { selectFrame(index); });
    frameLayout->addWidget(button);
    frameButtons.push_back(button);
    updateButtonIcon(button, index);
}

void FramePanel::updateButtonIcon(QPushButton *button, int frameIndex) {
    if (frameIndex >= 0 && frameIndex < model->getFrames().size()) {
        QImage frameImage = model->getFrames()[frameIndex]->getImage();
        QPixmap pixmap = QPixmap::fromImage(frameImage.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QIcon icon(pixmap);
        button->setIcon(icon);
        button->setIconSize(pixmap.rect().size());
    }
}

void FramePanel::highlightSelectedFrame(int index) {
    for (int i = 0; i < frameButtons.size(); ++i) {
        frameButtons[i]->setStyleSheet(i == index ? "border: 2px solid blue;" : "");
    }
}

void FramePanel::updateFrameList() {
    for (QPushButton* button : frameButtons) {
        frameLayout->removeWidget(button);
        delete button;
    }
    frameButtons.clear();
    for (int i = 0; i < model->getFrames().size(); ++i) {
        addFrameButton(i);
    }
    selectedFrameIndex = -1;
}

void FramePanel::updateButtonIconBasedOnFrame(Frame* frame) {
    int index = model->getFrames().indexOf(frame);
    if (index != -1) {
        updateButtonIcon(frameButtons[index], index);
    }
}
