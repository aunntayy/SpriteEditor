/*
 * Frame.h
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

#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include <QColor>

// Frame class, representing a drawable image frame.
class Frame {
public:
    /**
     * @brief Constructs a Frame with specified width and height.
     * Defaults to 800x800 pixels if no dimensions are provided.
     *
     * @param width  Width of the frame in pixels.
     * @param height Height of the frame in pixels.
     */
    Frame(int width = 800, int height = 800);

    /**
     * @brief Copy constructor for Frame, enabling deep copying of frame data.
     *
     * @param other  Another Frame object to copy from.
     */
    Frame(const Frame& other);

    /**
     * @brief Assignment operator for Frame, enabling deep assignment of frame data.
     *
     * @param other  Another Frame object to assign from.
     * @return       Reference to this Frame after assignment.
     */
    Frame& operator=(const Frame& other);

    /**
     * @brief Destructor for Frame, releases resources held by the frame.
     */
    ~Frame();

    /**
     * @brief Retrieves the color of the pixel at the specified coordinates.
     *
     * @param x      X-coordinate of the pixel.
     * @param y      Y-coordinate of the pixel.
     * @return       The QColor of the pixel at (x, y).
     */
    QColor getPixelColor(int x, int y) const;

    /**
     * @brief Sets the color of the pixel at the specified coordinates.
     *
     * @param x      X-coordinate of the pixel.
     * @param y      Y-coordinate of the pixel.
     * @param color  The QColor to set at (x, y).
     */
    void setPixelColor(int x, int y, const QColor& color);

    /**
     * @brief Provides access to the frame's current image data as a QImage.
     *
     * @return       Constant reference to the frame's QImage.
     */
    const QImage& getImage() const;

    /**
     * @brief Replaces the frame's current image with the specified QImage.
     *
     * @param newImage  The QImage to set as the frame's current image.
     */
    void setImage(const QImage& newImage);

private:
    // The image data representing the frame's pixel data.
    QImage frameImage;
};

#endif // FRAME_H

