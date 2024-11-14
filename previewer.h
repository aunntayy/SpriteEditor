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
