/*
 * FramePanel.h
 *
 * Description:
 * This header file defines the FramePanel class, which represents a UI panel
 * for managing frames within a scrollable list. FramePanel allows users to add,
 * duplicate, select, and remove frames, and it emits signals for frame selection
 * and canvas clearing. Each frame is displayed as a button, and the currently
 * selected frame is visually highlighted.
 *
 * Author: Thu Ha - Phuc Hoang
 * Date: 11/07/2024
 * Reviewed by: Thu Ha
 */

#ifndef FRAMEPANEL_H
#define FRAMEPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <vector>
#include "model.h"

// FramePanel class, a QWidget-based class for managing a list of frames in a UI panel.
class FramePanel : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the FramePanel, initializing it with a model and optional parent widget.
     *
     * @param model Pointer to the Model object for managing frames.
     * @param parent Optional parent widget, defaults to nullptr.
     */
    FramePanel(Model *model, QWidget *parent = nullptr);

    /**
     * @brief Updates the list of frame buttons in the panel based on the current frames in the model.
     */
    void updateFrameList();

    /**
     * @brief Updates the button icon based on the content of a specific frame.
     *
     * @param frame Pointer to the Frame object to base the icon update on.
     */
    void updateButtonIconBasedOnFrame(Frame* frame);

signals:
    /**
     * @brief Emitted when the canvas should be cleared.
     */
    void clearCanvas();

    /**
     * @brief Emitted when a frame is selected by the user.
     *
     * @param frame Pointer to the selected Frame object.
     */
    void frameSelected(Frame* frame);

private slots:
    /**
     * @brief Slot for adding a new frame to the panel.
     */
    void onAddFrame();

    /**
     * @brief Slot for duplicating the currently selected frame.
     */
    void onDuplicateFrame();

    /**
     * @brief Slot for removing the currently selected frame from the panel.
     */
    void onRemoveFrame();

    /**
     * @brief Slot for selecting a frame based on its index in the list.
     *
     * @param index The index of the frame to select.
     */
    void selectFrame(int index);

private:
    Model *model;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *frameLayout;
    std::vector<QPushButton*> frameButtons;

    QPushButton *addButton;
    QPushButton *duplicateButton;
    QPushButton *removeButton;

    int selectedFrameIndex = -1;

    /**
     * @brief Adds a button for a new frame at the specified index.
     *
     * @param index The index position to add the frame button.
     */
    void addFrameButton(int index);

    /**
     * @brief Updates the icon of a specified button based on the frame's index.
     *
     * @param button Pointer to the QPushButton representing the frame.
     * @param frameIndex Index of the frame to set the icon for.
     */
    void updateButtonIcon(QPushButton *button, int frameIndex);

    /**
     * @brief Highlights the button representing the currently selected frame.
     *
     * @param index The index of the frame to highlight.
     */
    void highlightSelectedFrame(int index);
};

#endif // FRAMEPANEL_H

