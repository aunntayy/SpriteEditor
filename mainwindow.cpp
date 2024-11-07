#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include "framepanel.h"

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

    // window setup
    this->setWindowTitle("CS3505 Sprite Editor");
    this->setFixedSize(1200, 900);
    this->move(250, 50);
    this->setStatusBar(nullptr);

    // Instantiate the model
    model = new Model(this);

    // toolbar setup
    QToolBar* toolBar = addToolBar("Toolbar");
    toolBar->setFixedHeight(50);
    toolBar->setStyleSheet("background-color: rgb(100, 100, 100);");
    QAction* action1 = new QAction("File Stuff", this);
    toolBar->addAction(action1);
    QAction* action2 = new QAction("Other Tools", this);
    toolBar->addAction(action2);

    // panel setup
    QDockWidget* panel = new QDockWidget("Panel", this);
    panel->setFixedWidth(350);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setSizePolicy(sizePolicy);
    panel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // panel container
    QWidget* panelContainer = new QWidget();
    panelContainer->setStyleSheet("background-color: rgb(100, 100, 100);");
    panel->setWidget(panelContainer);

    // preview area
    QWidget* previewer = new QWidget();
    previewer->setFixedHeight(325);
    previewer->setStyleSheet("background-color: rgb(200, 200, 200);");

    // FramePanel - setup for managing frames
    framePanel = new FramePanel(model, this);  // Instantiate FramePanel with Model

    // Tab widget for Colors and Frames
    QTabWidget* tabWidget = new QTabWidget();
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->addTab(new QWidget(), "Colors");
    tabWidget->addTab(framePanel, "Frames"); // Use framePanel as the "Frames" tab

    // Styling for tab widget
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

    // Layout for panelContainer to hold previewer and tabWidget
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(previewer);
    layout->addWidget(tabWidget);
    panelContainer->setLayout(layout);

    // Add the panel as a dock widget
    addDockWidget(Qt::LeftDockWidgetArea, panel);

    // Canvas setup
    QWidget* canvas = new QWidget();
    canvas->setStyleSheet("background-color: rgb(0, 0, 0);");
    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
