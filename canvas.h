/*
 * Canvas.h
 *
 * Description:
 * This header file defines the Canvas class, a QWidget-derived component for drawing
 * and interacting with a pixel-based image. The Canvas class supports mouse-based drawing,
 * frame updating, and color management. It also provides signals to notify other components
 * when the canvas has been modified.
 *
 * Author: Phuc Hoang - Trenton Stratton
 * Date: 11/7/2024
 * Reviewed by: Phuc Hoang
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include "frame.h"

// Canvas class, a QWidget-derived class that manages drawing and interaction on an image.
class Canvas : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Canvas class.
     *
     * @param width  Width of the canvas in pixels.
     * @param height Height of the canvas in pixels.
     * @param parent Optional parent widget, defaults to nullptr.
     */
    explicit Canvas(int width, int height, QWidget* parent = nullptr);

    /**
     * @brief Clears the canvas by filling it with a background color (typically white).
     * This prepares the canvas for new drawing operations.
     */
    void clear();

    /**
     * @brief Updates the current canvas image with content from an external frame source.
     *
     * @param frame  A pointer to the Frame object that contains the image data
     *               to be copied to the canvas.
     */
    void updateFrameFromCanvas(Frame* frame);

    /**
     * @brief Draws content from the specified frame onto the canvas, resizing if necessary.
     *
     * @param frame  A pointer to the Frame object that provides the image data.
     */
    void drawFromFrame(Frame* frame);

    // Public image object representing the canvas's current state.
    QImage image;

signals:
    /**
     * @brief Signal emitted when the mouse is pressed on the canvas.
     *
     * @param point  The QPoint where the mouse press event occurred.
     */
    void mousePressCanvas(QPoint point);

    /**
     * @brief Sends the current image after modifications.
     *
     * @param img  The QImage containing the current state of the canvas.
     */
    void sendCurrentImage(const QImage& img);

    /**
     * @brief Emitted when the canvas has been modified.
     *
     * @param image  The QImage containing the modified state of the canvas.
     */
    void canvasModified(const QImage& image);

private:
    // Last point on the canvas where the mouse was pressed or moved.
    QPoint lastPoint;

    // Current brush color for drawing on the canvas.
    QColor brushColor;

protected:
    /**
     * @brief Paints the current canvas image onto the widget.
     * Overrides QWidget::paintEvent.
     *
     * @param event  The QPaintEvent that provides painting parameters.
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief Handles mouse press events on the canvas for drawing actions.
     *
     * @param mouseEvent  The QMouseEvent that contains event details.
     */
    void mousePressEvent(QMouseEvent* mouseEvent) override;

    /**
     * @brief Handles mouse move events on the canvas to allow continuous drawing as the mouse moves.
     *
     * @param mouseEvent  The QMouseEvent containing details of the mouse movement.
     */
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;

    /**
     * @brief Handles mouse release events to complete drawing actions.
     *
     * @param mouseEvent  The QMouseEvent that contains event details for the release.
     */
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
};

#endif // CANVAS_H

