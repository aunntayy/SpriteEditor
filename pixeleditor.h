/*
 * pixelEditor.h
 *
 * @brief Defines the pixelEditor class, which manages pixel-based drawing operations
 * on a Canvas. The class provides tools for editing, such as brush, erase, fill, move,
 * and undo functionality. It maintains an action history to allow undo operations and
 * manages color and pixel size for drawing operations.
 *
 * Author: Phuc Hoang - Trenton Stratton - Chanphone Visathip
 * Date: [Date]
 * Reviewed by: Phuc Hoang
 */

#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QStack>
class Canvas;

// pixelEditor class, a QObject-based class for managing pixel drawing tools and actions.
class pixelEditor : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a pixelEditor with an optional parent object.
     *
     * @param parent Optional parent QObject, defaults to nullptr.
     */
    explicit pixelEditor(QObject* parent = nullptr);

    /**
     * @brief Sets the Canvas instance where drawing actions will be applied.
     *
     * @param canvas Pointer to the Canvas object.
     */
    void setCanvasInstance(Canvas* canvas);

    /**
     * @brief Enum defining available tools for drawing and editing.
     */
    enum Tools {
        none,
        Brush,
        Erase,
        Fill,
        Move,
        Undo
    };

    /**
     * @brief Sets the active tool for drawing/editing.
     *
     * @param pickTool The tool to set as active.
     */
    void setTool(Tools pickTool);

    /**
     * @brief Sets the current brush color for drawing.
     *
     * @param color The QColor to use as the brush color.
     */
    void setBrushColor(const QColor &color);

    /**
     * @brief Sets the size of the pixels for drawing operations.
     *
     * @param size The size of the pixels.
     */
    void setPixelSize(int size);

    /**
     * @brief Draws a pixel at the specified (x, y) coordinates.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     */
    void drawPixel(int x, int y);

    /**
     * @brief Erases a pixel at the specified (x, y) coordinates.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     */
    void erasePixel(int x, int y);

    /**
     * @brief Fills an area starting from (x, y) with the current brush color.
     *
     * @param x The x-coordinate to start filling.
     * @param y The y-coordinate to start filling.
     */
    void fillColor(int x, int y);

    /**
     * @brief Moves the pixels by tracking positions from a start point.
     *
     * @param x The x-coordinate of the target position.
     * @param y The y-coordinate of the target position.
     */
    void movePixel(int x, int y);

    /**
     * @brief Adds an action to the history for undo purposes.
     *
     * @param x The x-coordinate of the action.
     * @param y The y-coordinate of the action.
     * @param prevColor The previous color at the specified coordinates.
     */
    void addActionToHistory(int x, int y, const QColor& prevColor);

    /**
     * @brief Reverts the last action performed on the canvas.
     */
    void undoLastAction();

public slots:
    /**
     * @brief Draws at a specified point using the current tool.
     *
     * @param point The QPoint to draw at.
     */
    void drawWithCurrTool(QPoint point);

private:
    /**
     * @brief Structure to store pixel data for drawing actions.
     */
    struct pixelData {
        QPoint pixelCoor;
        QColor currPixelColor;
        int currPixleSize;

        pixelData(const QPoint& pos, const QColor& col, int s)
            : pixelCoor(pos), currPixelColor(col), currPixleSize(s) {}
    };

    Tools currentTool;
    int pixelSize;
    Canvas* canvasInstance;
    QVector<pixelData> drawnPixels;
    QVector<pixelData> originalDrawnPixels;
    int originalPixelSize;
    QPoint startMovePoint;
    bool isMoving;
    QColor currentBrushColor;
    QList<pixelData> actionHistory;
};

#endif // PIXELEDITOR_H

