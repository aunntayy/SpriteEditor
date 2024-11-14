/*
 * Previewer.h
 *
 * @brief Defines the pixelEditor class, which manages pixel-based drawing operations
 * on a Canvas. The class provides tools for editing, such as brush, erase, fill, move,
 * and undo functionality. It maintains an action history to allow undo operations and
 * manages color and pixel size for drawing operations.
 *
 * Author: Phuc Hoang - Trenton Stratton
 * Reviewed by: Phuc Hoang
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
