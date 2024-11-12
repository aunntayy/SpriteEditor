#include "frame.h"

Frame::Frame(int width, int height) : frameImage(width, height, QImage::Format_ARGB32) {
    frameImage.fill(Qt::white); // Default to a white background
}

Frame::Frame(const Frame& other) : frameImage(other.frameImage) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        frameImage = other.frameImage;
    }
    return *this;
}

Frame::~Frame() {}

QColor Frame::getPixelColor(int x, int y) const {
    return frameImage.pixelColor(x, y);
}

void Frame::setPixelColor(int x, int y, const QColor& color) {
    frameImage.setPixelColor(x, y, color);
}

const QImage& Frame::getImage() const {
    return frameImage;
}
void Frame::setImage(const QImage& newImage) {
    frameImage = newImage;
}
