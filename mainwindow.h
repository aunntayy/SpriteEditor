#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>

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
