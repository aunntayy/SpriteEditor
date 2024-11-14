/**
 * @file Previewer.h
 * @brief Header file for the Previewer class, a QWidget-based component for previewing a sequence of images as an animation.
 *
 * The Previewer class provides functionality to load a sequence of images, adjust playback speed, and animate the frames
 * similar to a preview tool like Piskel. It manages frame display and playback speed using a QLabel for frame rendering
 * and a QSlider for user-controlled speed adjustments. The animation is driven by a QTimer for frame transitions.
 *
 * Author: Thu Ha, Chanphone Visathip
 * Reviewer: Thu Ha
 */
#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QWidget>
#include <QVector>
#include <QImage>
#include <QTimer>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

class Previewer : public QWidget
{
    Q_OBJECT

public:
    explicit Previewer(QWidget *parent = nullptr);
    ~Previewer();

    void setImageSequence(const QVector<QImage>& images);
    void displayNextFrame();
    void setPlaybackSpeed(int framesPerSecond);
    void startAnimation();

private:
    QVector<QImage> frameSequence;
    QTimer animationTimer;

    QLabel* frameDisplay;
    QSlider* speedSlider;
    int playbackSpeed;
    int currentFrameIndex;
};

#endif // PREVIEWER_H
