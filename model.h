/*
 * Model.h
 *
 * @brief Defines the Model class, which manages the application's core data,
 * including frames, resolution, frame rate, and file save status. Model provides
 * functions to add, duplicate, and remove frames, as well as update the current
 * frame's image. It emits signals to update the frame list and drawing panel when
 * changes occur.
 *
 * Author: Thu Ha - Phuc Hoang
 * Date: 11/07/2024
 * Reviewed by: Thu Ha
 */

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include "frame.h"

// Model class, a QObject-based class for managing core application data.
class Model : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs the Model with an optional parent object.
     *
     * @param parent Optional parent QObject, defaults to nullptr.
     */
    Model(QObject *parent = nullptr);

    /**
     * @brief Destructor for Model, responsible for cleanup of frames.
     */
    ~Model();

    /**
     * @brief Adds a new frame to the model.
     */
    void addFrame();

    /**
     * @brief Duplicates an existing frame at the specified index.
     *
     * @param index Index of the frame to duplicate.
     */
    void duplicateFrame(int index);

    /**
     * @brief Removes a frame at the specified index.
     *
     * @param index Index of the frame to remove.
     */
    void removeFrame(int index);

    /**
     * @brief Checks if the current file has been saved.
     *
     * @return True if the file is saved; otherwise, false.
     */
    bool isFileSaved() const;

    /**
     * @brief Gets the current frame rate.
     *
     * @return The current frame rate as an integer.
     */
    int getFrameRate() const;

    /**
     * @brief Gets the current resolution setting.
     *
     * @return The current resolution as an integer.
     */
    int getResolution() const;

    /**
     * @brief Provides access to the list of frames.
     *
     * @return QVector of pointers to Frame objects.
     */
    QVector<Frame*> getFrames() const;

    /**
     * @brief Gets the currently selected frame.
     *
     * @return Pointer to the current Frame object.
     */
    Frame* getCurrentFrame() const;

    /**
     * @brief Sets the index of the currently selected frame.
     *
     * @param index Index to set as the current frame.
     */
    void setCurrentFrameIndex(int index);

    /**
     * @brief Updates the image of the currently selected frame.
     *
     * @param img The QImage to set for the current frame.
     */
    void updateCurrentFrameImage(const QImage& img);

    /**
     * @brief Marks the current file as saved.
     */
    void fileSaved();

    /**
     * @brief Marks the current file as unsaved.
     */
    void fileNotSaved();

    /**
     * @brief Sets the new frame rate.
     *
     * @param newFrameRate Integer value for the new frame rate.
     */
    void setFrameRate(int newFrameRate);

    /**
     * @brief Sets the new resolution.
     *
     * @param newResolution Integer value for the new resolution.
     */
    void setResolution(int newResolution);

signals:
    /**
     * @brief Emitted when the frame list needs updating.
     */
    void updateFrameList();

    /**
     * @brief Emitted to update the drawing panel with a specific frame.
     *
     * @param frame Pointer to the Frame object for updating.
     */
    void updateDrawingPanel(Frame* frame);

    /**
     * @brief Emitted when a frame is removed.
     */
    void frameRemoved();

private:
    int toolSize;
    QColor toolColor;
    int selectedFrame;
    int resolution;
    int frameRate;
    bool isSaved;
    QVector<Frame*> frameList;
    int currentFrameIndex;
};

#endif // MODEL_H

