#include "previewer.h"

Previewer::Previewer ()
{
    QVBoxLayout* container = new QVBoxLayout(this);

    QWidget* previewWindow = new QLabel();
    previewWindow->setFixedHeight(300);
    previewWindow->setStyleSheet("background-color: rgb(200, 200, 200);");

    QSlider* frameRateSlider = new QSlider(Qt::Horizontal);
    frameRateSlider->setRange(1, 60);
    frameRateSlider->setValue(20);
    frameRateSlider->setTickPosition(QSlider::TicksBelow);  // Or TicksAbove, TicksLeft, etc.
    frameRateSlider->setTickInterval(5);

    container->addWidget(previewWindow);
    container->addWidget(frameRateSlider);

    setLayout(container);
}


