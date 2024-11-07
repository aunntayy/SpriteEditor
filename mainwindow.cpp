#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model.h"
#include "framepanel.h"

#include <QToolBar>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QSplitter>
#include <QLabel>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    editor = new pixelEditor(this);

    // window setup
    this->setWindowTitle("CS3505 Sprite Editor");
    this->setFixedSize(1200, 900);
    this->move(250, 50);
    this->setStatusBar(nullptr);

    // Instantiate the model
    model = new Model(this);


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
    spacer->setFixedWidth(400); // Adjust this width to control the spacing
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


    // brush size slider
    QSlider* brushSizeSlider = new QSlider(Qt::Horizontal, this);
    brushSizeSlider->setFixedWidth(150);
    brushSizeSlider->setRange(1, 10); // Brush size range from 1 to 100
    brushSizeSlider->setValue(10); // Default value
    toolBar->addWidget(brushSizeSlider);

    // brush button
    QAction* brushAction = new QAction(QIcon(":/img/img/brush.png"), "Brush", this);
    brushAction->setCheckable(true);
    toolGroup->addAction(brushAction);
    toolBar->addAction(brushAction);

    // erase button
    QAction* eraseAction = new QAction(QIcon(":/img/img/erase.png"), "Erase", this);
    eraseAction->setCheckable(true);
    toolGroup->addAction(eraseAction);
    toolBar->addAction(eraseAction);

    // fill button
    QAction* fillAction = new QAction(QIcon(":/img/img/fill.png"), "Fill", this);
    fillAction->setCheckable(true);
    toolGroup->addAction(fillAction);
    toolBar->addAction(fillAction);

    // connect actions to setTool
    connect(brushSizeSlider, &QSlider::valueChanged, this, [=](int value) {
        editor->setToolSize(value);
        qDebug() << "Brush size set to:" << value;
    });
    connect(brushAction, &QAction::triggered, this, [=]() {
        editor->setTool(pixelEditor::Brush);
    });
    connect(eraseAction, &QAction::triggered, this, [=]() {
        editor->setTool(pixelEditor::Erase);
    });
    connect(fillAction, &QAction::triggered, this, [=]() {
        editor->setTool(pixelEditor::Fill);
    });

    // Add a separator between the move and undo buttons
    toolBar->addSeparator();

    // move button
    QAction* moveAction = new QAction(QIcon(":/img/img/move.png"), "Move", this);
    moveAction->setCheckable(true);
    toolGroup->addAction(moveAction);
    toolBar->addAction(moveAction);

    // undo button
    QAction* undoAction = new QAction(QIcon(":/img/img/undo.png"), "Undo", this);
    undoAction->setCheckable(true);
    toolGroup->addAction(undoAction);
    toolBar->addAction(undoAction);

    // set icon size here
    toolBar->setIconSize(QSize(32, 32));




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
    delete editor;
}
