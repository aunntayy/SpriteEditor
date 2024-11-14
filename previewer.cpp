#include "previewer.h"

Previewer::Previewer(QWidget *parent)
    : QWidget(parent), FPS(10), currentIndex(0)
{
    // Initialize preview label to display frames
    previewLabel = new QLabel(this);
    previewLabel->setFixedSize(300, 300);  // Set size or adjust as needed
    previewLabel->setAlignment(Qt::AlignCenter);
    previewLabel->setStyleSheet("background-color: rgb(200, 200, 200);");

    // Initialize frame rate slider to adjust playback speed
    frameRateSlider = new QSlider(Qt::Horizontal, this);
    frameRateSlider->setRange(1, 60);
    frameRateSlider->setValue(FPS);  // Default FPS
    frameRateSlider->setTickPosition(QSlider::TicksBelow);
    frameRateSlider->setTickInterval(5);

    // Connect frame rate slider to the slot to change FPS
    connect(frameRateSlider, &QSlider::valueChanged, this, &Previewer::setFramePerSecond);
    connect(&delayTimer, &QTimer::timeout, this, &Previewer::showPreviewAnimation);

    // Layout to arrange the label and slider
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(previewLabel);
    layout->addWidget(frameRateSlider);
    setLayout(layout);
}

Previewer::~Previewer()
{}

void Previewer::getImageListFromModel(QVector<QImage> imgList)
{
    imageListFromModel = imgList;
    currentIndex = 0;  // Reset frame index for new animation
}

void Previewer::showPreviewAnimation()
{
    if (imageListFromModel.isEmpty()) return;

    // Display current frame in the preview label
    previewLabel->setPixmap(QPixmap::fromImage(imageListFromModel[currentIndex])
                                .scaled(previewLabel->size(), Qt::KeepAspectRatio));

    // Move to the next frame, looping back to the first frame if necessary
    currentIndex = (currentIndex + 1) % imageListFromModel.size();
}

void Previewer::setFramePerSecond(int framesPerSecond)
{
    FPS = framesPerSecond;
    if (delayTimer.isActive()) {
        delayTimer.setInterval(1000 / FPS);  // Adjust timer interval based on new FPS
    }
}

void Previewer::activateAnimation()
{
    if (!delayTimer.isActive() && !imageListFromModel.isEmpty()) {
        delayTimer.start(1000 / FPS);  // Start the animation timer with the set FPS
    }
}
