#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QtWidgets/qboxlayout.h>
#include <QWidget>
#include <QtWidgets/qlabel.h>
#include <QSlider>
#include <QPainter>
#include <QPixmap>

class Previewer : public QWidget
{
public:
    Previewer();
    // get framesPixmap everytime new frame is added
    // paint framePixmap

signals:
    void frameRateSliderValue();


};

#endif // PREVIEWER_H
