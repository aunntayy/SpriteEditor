/*
 * MainWindow.h
 *
 * @brief Defines the MainWindow class, which is the main application window for
 * managing UI elements, color settings, and connections to core components such
 * as Canvas, PixelEditor, Model, and FramePanel. The MainWindow provides functionality
 * for saving/loading files, color selection, and frame management.
 *
 *
 * Author: Thu Ha - Phuc Hoang - Chanphone Visathip - Trenton Stratton
 * Date: 11/07/
 * Reviewed by: Chanphone Visathip
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>

#include "pixeleditor.h"
#include "canvas.h"
#include "model.h"
#include "framepanel.h"
#include "previewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// MainWindow class, inheriting QMainWindow to manage the main application interface.
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow with optional parent widget.
     *
     * @param parent Optional parent widget, defaults to nullptr.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow, responsible for cleanup.
     */
    ~MainWindow();

    /**
     * @brief Configures the color selection UI within the provided widget.
     *
     * @param colorsTab The widget to set up as the color selection tab.
     */
    void colorUI(QWidget *colorsTab);

    QAction* saveButton;
    QAction* loadButton;

private:
    Ui::MainWindow *ui;
    pixelEditor* editor;
    Previewer *previewer;
    Model *model;
    FramePanel *framePanel;
    Canvas *canvas;

    // Color Manager
    QVector<QVector<QPushButton *>> colorButtons;
    QSlider *redSlider;
    QSlider *blueSlider;
    QSlider *greenSlider;
    QLineEdit *hexLineEdit;
    QPushButton *brushColor;
    QMap<QPushButton*, QColor> customColors;

    /**
     * @brief Connects signals and slots within MainWindow and other components.
     */
    void connectSignals();

    /**
     * @brief Sets the brush resolution when loading, based on provided sizes.
     *
     * @param brushSize Vector of brush sizes to initialize upon load.
     */
    void setResolutionOnLoad(QVector<int> brushSize);

private slots:
    /**
     * @brief Updates the color displayed in the UI based on slider values for RGB.
     */
    void updateColorOnSlider();

    /**
     * @brief Updates the color displayed in the UI based on hex color code input.
     */
    void updateColorOnHexCode();

    /**
     * @brief Updates the custom color palette with newly selected colors.
     */
    void updateColorCustomPalette();

    /**
     * @brief Sends the selected color from the UI to the PixelEditor for drawing.
     */
    void sendColorToEditor();

signals:
    /**
     * @brief Emitted when the save button is clicked.
     */
    void saveButtonClicked();

    /**
     * @brief Emitted when the load button is clicked.
     */
    void loadButtonClicked();
};

#endif // MAINWINDOW_H

