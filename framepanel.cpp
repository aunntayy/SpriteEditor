#include "framepanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

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

    connect(model, &Model::updateFrameList, this, &FramePanel::updateFrameList);

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
}

void FramePanel::onAddFrame() {
    qDebug() << "Add Frame button clicked";
    model->addFrame();
}

void FramePanel::onDuplicateFrame() {
    if (selectedFrameIndex >= 0 && selectedFrameIndex < frameButtons.size())
    {
        qDebug() << "Duplicate Frame button clicked";
        model->duplicateFrame(selectedFrameIndex);
    }
}

void FramePanel::onRemoveFrame() {
    if (selectedFrameIndex >= 0 && selectedFrameIndex < frameButtons.size()) {
        model->removeFrame(selectedFrameIndex);
        selectedFrameIndex = -1;  // Reset selection
        qDebug() << "Remove Frame button clicked";
    }
}

void FramePanel::updateFrameList() {
    // Clear existing buttons
    for (QPushButton* button : frameButtons) {
        frameLayout->removeWidget(button);
        delete button;
    }
    frameButtons.clear();

    for (int i = 0; i < model->getFrames().size(); ++i) {
        addFrameButton(i);
    }

    // Reset selection after updating the list
    selectedFrameIndex = -1;
}

void FramePanel::addFrameButton(int index) {
    // Create a new button for the frame
    QPushButton *button = new QPushButton(this);
    button->setText(QString::number(index + 1));
    button->setFixedSize(100, 100);

    connect(button, &QPushButton::clicked, this, [this, index]() {
        selectFrame(index);});

    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::gray);
    updateButtonIcon(button, pixmap);

    // Add button to layout and vector
    frameLayout->addWidget(button);
    frameButtons.push_back(button);
}

void FramePanel::updateButtonIcon(QPushButton *button, const QPixmap &pixmap) {
    QIcon icon(pixmap);
    button->setIcon(icon);
    button->setIconSize(pixmap.size());
}

void FramePanel::selectFrame(int index) {
    highlightSelectedFrame(index);
    selectedFrameIndex = index;
    qDebug() << "Selected frame index:" << selectedFrameIndex;
}

void FramePanel::highlightSelectedFrame(int index) {
    for (int i = 0; i < frameButtons.size(); ++i) {
        frameButtons[i]->setStyleSheet("");
    }

    if (index >= 0 && index < frameButtons.size()) {
        frameButtons[index]->setStyleSheet("border: 2px solid blue;");
    }
}
