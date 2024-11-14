/**
 * @file Previewer.cpp
 * @brief Header file for the Previewer class, a QWidget-based component for previewing a sequence of images as an animation.
 *
 * The Previewer class provides functionality to load a sequence of images, adjust playback speed, and animate the frames
 * similar to a preview tool like Piskel. It manages frame display and playback speed using a QLabel for frame rendering
 * and a QSlider for user-controlled speed adjustments. The animation is driven by a QTimer for frame transitions.
 *
 * Author: Thu Ha, Chanphone Visathip
 * Reviewer: Thu Ha
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
