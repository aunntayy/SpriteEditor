/*
 * Frame.cpp
 *
 * Description:
 * This header file defines the Frame class, which represents an individual frame
 * as a pixel-based image. The Frame class provides functionality for managing
 * pixel colors, image dimensions, and image data. It also includes methods for
 * copying and assignment operations, enabling multiple frames to be managed independently.
 *
 *
 * Author: Thu Ha - Phuc Hoang
 * Date: 11/06/2024
 * Reviewed by: Thu Ha
 */

#include "frame.h"

Frame::Frame(int width, int height) : frameImage(width, height, QImage::Format_ARGB32) {
    frameImage.fill(Qt::white);
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
