#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include <QColor>

class Frame {
public:
    Frame(int width = 800, int height = 800); // Default resolution
    Frame(const Frame& other);
    Frame& operator=(const Frame& other);
    ~Frame();

    QColor getPixelColor(int x, int y) const;
    void setPixelColor(int x, int y, const QColor& color);
    const QImage& getImage() const;
    void setImage(const QImage& newImage);

private:
    QImage frameImage;
};

#endif // FRAME_H
