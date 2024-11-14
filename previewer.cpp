/*
 * Previewer.cpp
 *
 * @brief Defines the pixelEditor class, which manages pixel-based drawing operations
 * on a Canvas. The class provides tools for editing, such as brush, erase, fill, move,
 * and undo functionality. It maintains an action history to allow undo operations and
 * manages color and pixel size for drawing operations.
 *
 * Author: Phuc Hoang - Trenton Stratton
 * Reviewed by: Phuc Hoang
 */

#include "previewer.h"

Previewer::Previewer(QWidget *parent)
    : QWidget(parent), playbackSpeed(10), currentFrameIndex(0)
{
    frameDisplay = new QLabel(this);
    frameDisplay->setFixedSize(300, 300);
    frameDisplay->setAlignment(Qt::AlignCenter);
    frameDisplay->setStyleSheet("background-color: rgb(200, 200, 200);");

    speedSlider = new QSlider(Qt::Horizontal, this);
    speedSlider->setRange(1, 60);
    speedSlider->setValue(playbackSpeed);  // Default playback speed
    speedSlider->setTickPosition(QSlider::TicksBelow);
    speedSlider->setTickInterval(5);

    connect(speedSlider, &QSlider::valueChanged, this, &Previewer::setPlaybackSpeed);
    connect(&animationTimer, &QTimer::timeout, this, &Previewer::displayNextFrame);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(frameDisplay);
    layout->addWidget(speedSlider);
    setLayout(layout);
}

Previewer::~Previewer() {}

void Previewer::setImageSequence(const QVector<QImage>& images)
{
    frameSequence = images;
    currentFrameIndex = 0;
}

void Previewer::displayNextFrame()
{
    if (frameSequence.isEmpty()) return;

    frameDisplay->setPixmap(QPixmap::fromImage(frameSequence[currentFrameIndex])
                                .scaled(frameDisplay->size(), Qt::KeepAspectRatio));

    currentFrameIndex = (currentFrameIndex + 1) % frameSequence.size();
}

void Previewer::setPlaybackSpeed(int framesPerSecond)
{
    playbackSpeed = framesPerSecond;
    if (animationTimer.isActive()) {
        animationTimer.setInterval(1000 / playbackSpeed);
    }
}

void Previewer::startAnimation()
{
    if (!animationTimer.isActive() && !frameSequence.isEmpty()) {
        animationTimer.start(1000 / playbackSpeed);
    }
}
