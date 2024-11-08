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


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void colorUI(QWidget *colorsTab);

private:
    Ui::MainWindow *ui;
    pixelEditor* editor;
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


private slots:
    void updateColorOnSlider();
    void updateColorOnHexCode();
    void updateColorCustomPalette();
 


};

#endif // MAINWINDOW_H
