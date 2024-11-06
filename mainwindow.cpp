#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QSplitter>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // window
    this->setWindowTitle("CS3505 Sprite Editor");
    this->setFixedSize(1200, 900);
    this->move(250, 50);
    this->setStatusBar(nullptr);



    // toolbar
    QToolBar* toolBar = addToolBar("Toolbar");
    toolBar->setFixedHeight(50);
    toolBar->setStyleSheet("background-color: rgb(100, 100, 100);"); //change color

    // File action
    QAction* action1 = new QAction("File Stuff", this);
    toolBar->addAction(action1);

    // tool bar buttons
    // Spacer widget to push actions to the right
    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacer->setFixedWidth(600); // Adjust this width to control the spacing
    toolBar->addWidget(spacer); // Add spacer to toolbar

    // Create an action group for mutually exclusive checkable actions
    QActionGroup* toolGroup = new QActionGroup(this);
    toolGroup->setExclusive(true); // Only one action can be checked at a time

    // Checkable actions for Color Picker, Brush, Erase, and Fill with icons

    // color picker button
    QAction* colorPickerAction = new QAction(QIcon(""), "Color", this);
    colorPickerAction->setCheckable(true);
    toolGroup->addAction(colorPickerAction);
    toolBar->addAction(colorPickerAction);

    // brush button
    QAction* brushAction = new QAction(QIcon(":/img/brush.png"), "Brush", this);
    brushAction->setCheckable(true);
    toolGroup->addAction(brushAction);
    toolBar->addAction(brushAction);

    // erase button
    QAction* eraseAction = new QAction(QIcon(":/img/erase.png"), "Erase", this);
    eraseAction->setCheckable(true);
    toolGroup->addAction(eraseAction);
    toolBar->addAction(eraseAction);

    // fill button
    QAction* fillAction = new QAction(QIcon(":/img/fill.png"), "Fill", this);
    fillAction->setCheckable(true);
    toolGroup->addAction(fillAction);
    toolBar->addAction(fillAction);

    // Add a separator between the move and undo buttons
    toolBar->addSeparator();

    // move button
    QAction* moveAction = new QAction(QIcon(":/img/move.png"), "Move", this);
    moveAction->setCheckable(true);
    toolGroup->addAction(moveAction);
    toolBar->addAction(moveAction);

    // undo button
    QAction* undoAction = new QAction(QIcon(":/img/undo.png"), "Undo", this);
    undoAction->setCheckable(true);
    toolGroup->addAction(undoAction);
    toolBar->addAction(undoAction);

    // set icon size here
    toolBar->setIconSize(QSize(32, 32));






    // panel
    QDockWidget* panel = new QDockWidget("Panel", this);
    panel->setFixedWidth(350);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setSizePolicy(sizePolicy);
    panel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // panel - widget to hold layout
    QWidget* panelContainer = new QWidget();
    panelContainer->setStyleSheet("background-color: rgb(100, 100, 100);"); //change color
    panel->setWidget(panelContainer);

    // panel - previewer
    QWidget* previewer = new QWidget();
    previewer->setFixedHeight(325);
    previewer->setStyleSheet("background-color: rgb(200, 200, 200);"); //change color

    // panel - tabs
    QTabWidget* tabWidget = new QTabWidget();
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->addTab(new QWidget(), "Colors");
    tabWidget->addTab(new QWidget(), "Frames");

    tabWidget->setStyleSheet(
        "QTabWidget::pane {"
        "    border: 1px solid #ccc;"
        "    background: #fafafa;"
        "}"
        "QTabBar::tab {"
        "    background: #e0e0e0;"
        "    border: 1px solid #ccc;"
        "    padding: 3px;"
        "    min-width: 80px;"
        "}"
        "QTabBar::tab:selected {"
        "    background: #aaaaaa;"
        "    color: white;"
        "}"
        "QTabBar::tab:hover {"
        "    background: #ddd;"
        "}"
    );

    // panel - layout to hold previewer and tabs
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(previewer);
    layout->addWidget(tabWidget);
    panelContainer->setLayout(layout);

    addDockWidget(Qt::LeftDockWidgetArea, panel);



    // canvas
    QWidget* canvas = new QWidget();
    canvas->setStyleSheet("background-color: rgb(0, 0, 0);");
    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
