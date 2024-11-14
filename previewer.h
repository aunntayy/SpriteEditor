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

    void getImageListFromModel(QVector<QImage> imgList);  // Sets image list from model
    void showPreviewAnimation();                          // Displays each frame in sequence
    void setFramePerSecond(int framesPerSecond);          // Adjusts the animation speed
    void activateAnimation();              // Adjusts the animation speed

private:                           // Starts the animation

    QVector<QImage> imageListFromModel;                   // Holds the list of frames
    QTimer delayTimer;                                    // Timer to control frame display rate

    QLabel* previewLabel;                                 // Label to display each frame
    QSlider* frameRateSlider;                             // Slider to adjust FPS
    int FPS;                                              // Frames per second
    int currentIndex;                                     // Tracks the current frame
};

#endif // PREVIEWER_H
