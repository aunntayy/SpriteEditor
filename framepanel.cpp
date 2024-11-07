#include "framepanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPixmap>
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
    int index = frameButtons.size() - 1;
    if (index >= 0)
    {
        qDebug() << "Duplicate Frame button clicked";
        model->duplicateFrame(index);
    }
}

void FramePanel::onRemoveFrame() {
    int index = frameButtons.size() - 1;
    if (index >= 0)
    {
        qDebug() << "Remove Frame button clicked";
        model->removeFrame(index);
    }
}

void FramePanel::updateFrameList() {
    // Clear existing buttons
    for (QPushButton* button : frameButtons) {
        frameLayout->removeWidget(button);
        delete button;
    }
    frameButtons.clear();

    // Recreate buttons based on model frames
    for (int i = 0; i < model->getFrames().size(); ++i) {
        addFrameButton(i);
    }
}

void FramePanel::addFrameButton(int index) {
    // Create a new button for the frame
    QPushButton *button = new QPushButton(this);
    button->setText(QString::number(index + 1));
    button->setFixedSize(100, 100); // Set size for button thumbnails

    // Get a placeholder or real pixmap for frame (using a dummy here)
    QPixmap pixmap(100, 100); // Placeholder size
    pixmap.fill(Qt::gray); // Replace this with actual frame content
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
