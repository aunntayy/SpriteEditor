#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"         // Include Model class
#include "framepanel.h"     // Include FramePanel class

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Model *model;             // Declare model as a member variable
    FramePanel *framePanel;   // Declare framePanel as a member variable
};

#endif // MAINWINDOW_H
