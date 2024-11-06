#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QDockWidget>
#include <QVBoxLayout>

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
    QAction* action1 = new QAction("File Stuff", this);
    toolBar->addAction(action1);
    QAction* action2 = new QAction("Other Tools", this);
    toolBar->addAction(action2);



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
