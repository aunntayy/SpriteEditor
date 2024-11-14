#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "canvas.h"
#include "framepanel.h"
#include "model.h"
#include "previewer.h"

#include <QToolBar>

#include <QDockWidget>
#include <QToolBar>
#include <QVBoxLayout>

#include <QActionGroup>
#include <QColorDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>
#include <QSplitter>
#include <QToolButton>
void MainWindow::colorUI(QWidget *colorsTab) {
    QVBoxLayout *colorsLayout = new QVBoxLayout();

    // Hex text block and Brush color
    QHBoxLayout *displayColor = new QHBoxLayout();

    hexLineEdit->setPlaceholderText("#FFFFFF");

    brushColor->setStyleSheet("background-color: rgb(255,255,255);");
    brushColor->setFixedSize(30, 30);

    displayColor->addWidget(hexLineEdit);
    displayColor->addWidget(brushColor);
    colorsLayout->addLayout(displayColor);

    // RGB slider
    QVBoxLayout *rgbBlock = new QVBoxLayout();
    redSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #999999;"
        "    height: 8px;"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "    stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 0, 0, 255));"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #ff0000;"
        "    border: 1px solid #ffffff;"
        "    width: 8px;"
        "    height: 8px;"
        "    border-radius: 4px;"
        "}");
    redSlider->setRange(0, 255);

    blueSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #999999;"
        "    height: 8px;"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "    stop:0 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 255, 255));"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #0000ff;"
        "    border: 1px solid #ffffff;"
        "    width: 8px;"
        "    height: 8px;"
        "    border-radius: 4px;"
        "}");
    blueSlider->setRange(0, 255);

    greenSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #999999;"
        "    height: 8px;"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "    stop:0 rgba(0, 0, 0, 255), stop:1 rgba(0, 255, 0, 255));"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #00ff00;"
        "    border: 1px solid #ffffff;"
        "    width: 8px;"
        "    height: 8px;"
        "    border-radius: 4px;"
        "}");
    greenSlider->setRange(0, 255);

    rgbBlock->addWidget(redSlider);
    rgbBlock->addWidget(blueSlider);
    rgbBlock->addWidget(greenSlider);

    colorsLayout->addLayout(rgbBlock);
    // Create and populate the 6x6 grid of buttons
    for (int i = 0; i < 6; ++i) {
        QHBoxLayout *customColorRow = new QHBoxLayout(); // Create a new row

        for (int j = 0; j < 6; ++j) {
            QPushButton *colorButton = new QPushButton();
            colorButton->setStyleSheet("background-color: rgb(255,255,255);");
            colorButton->setFixedSize(20, 20);

            // Store the button in the QVector using indices [i][j]
            colorButtons[i][j] = colorButton;

            // Add the button to the current row
            customColorRow->addWidget(colorButton);

            connect(colorButton, &QPushButton::clicked, [this, i, j]() {
                qDebug() << "Button at position (" << i << "," << j << ") clicked!";
            });
        }

        // Add the row to the main vertical layout
        colorsLayout->addLayout(customColorRow);
    }

    // Set the layout for the "Colors" tab
    colorsTab->setLayout(colorsLayout);
}

void MainWindow::setResolutionOnLoad(QVector<int> brushSize) {
    QMessageBox::StandardButton reply;
    QMessageBox msgBox(this);

    msgBox.setWindowTitle("Sprite Editor");
    msgBox.setText("Choose the resolution:");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *bttn32x32 = msgBox.addButton("32x32", QMessageBox::AcceptRole);
    QPushButton *bttn64x64 = msgBox.addButton("64x64", QMessageBox::AcceptRole);
    QPushButton *bttn128x128 =
        msgBox.addButton("128x128", QMessageBox::AcceptRole);

    reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

    if (msgBox.clickedButton() == bttn32x32) {
        editor->setPixelSize(brushSize[2]);
    } else if (msgBox.clickedButton() == bttn64x64) {
        editor->setPixelSize(brushSize[1]);
    } else if (msgBox.clickedButton() == bttn128x128) {
        editor->setPixelSize(brushSize[0]);
    }
    this->resize(1920, 1080);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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
    QToolBar *toolBar = addToolBar("Toolbar");
    toolBar->setFixedHeight(50);

    toolBar->setStyleSheet(
        "background-color: rgb(100, 100, 100);"); // change color
    QAction *action1 = new QAction("File Stuff", this);
    saveButton = new QAction("Save", this);
    loadButton = new QAction("Load", this);
    toolBar->addAction(action1);
    toolBar->addAction(saveButton);
    toolBar->addAction(loadButton);

    // connect(&saveButton, &QAction::triggered, &fileManager,
    // &FileManager::onSaveButtonClicked());

    // panel
    QDockWidget *panel = new QDockWidget("Panel", this);

    toolBar->setStyleSheet(
        "background-color: rgb(100, 100, 100);"); // change color

    // tool bar buttons
    // Spacer widget to push actions to the right
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacer->setFixedWidth(400); // Adjust this width to control the spacing
    toolBar->addWidget(spacer); // Add spacer to toolbar

    // Create an action group for mutually exclusive checkable actions
    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->setExclusive(true); // Only one action can be checked at a time

    // --++Checkable actions for Brush, Erase, and Fill with icons++--

    // brush size slider
    QLabel *brushSizeLabel = new QLabel("20 px", this);

    QSlider *brushSizeSlider = new QSlider(Qt::Horizontal, this);

    brushSizeSlider->setFixedWidth(100);
    QVector<int> brushSize = {20, 40, 60, 80, 100}; // adjust brush size here
    brushSizeSlider->setRange(0, 4);                // 4 different brush size

    connect(brushSizeSlider, &QSlider::valueChanged, this, [=](int value) {
        int currentBrushSize = brushSize[value];
        brushSizeLabel->setText(QString::number(currentBrushSize) +
                                " px"); // Update label
    });

    // set default starting slider to 20px
    brushSizeSlider->setValue(0);
    editor->setPixelSize(brushSize[0]);
    toolBar->addWidget(brushSizeLabel);
    toolBar->addSeparator();
    toolBar->addWidget(brushSizeSlider);

    // brush button
    QAction *brushAction =
        new QAction(QIcon(":/img/img/brush.png"), "Brush", this);
    brushAction->setCheckable(true);
    toolGroup->addAction(brushAction);
    toolBar->addAction(brushAction);
    // set default brush color to black
    editor->setBrushColor(Qt::black);

    // erase button
    QAction *eraseAction =
        new QAction(QIcon(":/img/img/erase.png"), "Erase", this);
    eraseAction->setCheckable(true);
    toolGroup->addAction(eraseAction);
    toolBar->addAction(eraseAction);

    // fill button
    QAction *fillAction = new QAction(QIcon(":/img/img/fill.png"), "Fill", this);
    fillAction->setCheckable(true);
    toolGroup->addAction(fillAction);
    toolBar->addAction(fillAction);

    // move button
    QAction *moveAction = new QAction(QIcon(":/img/img/move.png"), "Move", this);
    moveAction->setCheckable(true);
    toolGroup->addAction(moveAction);
    toolBar->addAction(moveAction);

    // connect actions to setTool
    connect(brushSizeSlider, &QSlider::valueChanged, this, [=](int index) {
        editor->setPixelSize(brushSize[index]);
        qDebug() << "Current brush size:" << brushSize[index];
    });
    connect(brushAction, &QAction::triggered, this,
            [=]() { editor->setTool(pixelEditor::Brush); });
    connect(eraseAction, &QAction::triggered, this,
            [=]() { editor->setTool(pixelEditor::Erase); });
    connect(fillAction, &QAction::triggered, this,
            [=]() { editor->setTool(pixelEditor::Fill); });

    connect(moveAction, &QAction::triggered, this, [=]() {
        editor->setTool(pixelEditor::Move);
        editor->drawWithCurrTool(QPoint());
    });

    // Add a separator between the move and undo buttons
    toolBar->addSeparator();

    // undo button
    QAction *undoAction = new QAction(QIcon(":/img/img/undo.png"),"Undo", this);

    undoAction->setCheckable(true);
    toolGroup->addAction(undoAction);
    toolBar->addAction(undoAction);

    connect(undoAction, &QAction::triggered, this,
            [=]() { editor->undoLastAction(); });

    // set icon size here
    toolBar->setIconSize(QSize(32, 32));
    // --++End of checkable actions for Brush, Erase, and Fill with icons++--

    panel->setFixedWidth(350);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setSizePolicy(sizePolicy);
    panel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget *colorsTab = new QWidget();

    // panel - tabs
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->addTab(colorsTab, "Colors");

    tabWidget->setStyleSheet("QTabWidget::pane {"
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
                             "}");

    // Create layout for the "Colors" tab (parent)
    hexLineEdit = new QLineEdit();
    brushColor = new QPushButton();
    redSlider = new QSlider(Qt::Horizontal);
    blueSlider = new QSlider(Qt::Horizontal);
    greenSlider = new QSlider(Qt::Horizontal);
    colorButtons = QVector<QVector<QPushButton *>>(6, QVector<QPushButton *>(6));
    customColors = {};
    colorUI(colorsTab);

    // update color based on slider
    connect(redSlider, &QSlider::valueChanged, this,
            &MainWindow::sendColorToEditor);
    connect(greenSlider, &QSlider::valueChanged, this,
            &MainWindow::sendColorToEditor);
    connect(blueSlider, &QSlider::valueChanged, this,
            &MainWindow::sendColorToEditor);

    connect(redSlider, &QSlider::valueChanged, this,
            &MainWindow::updateColorOnSlider);
    connect(greenSlider, &QSlider::valueChanged, this,
            &MainWindow::updateColorOnSlider);
    connect(blueSlider, &QSlider::valueChanged, this,
            &MainWindow::updateColorOnSlider);

    updateColorOnSlider();

    // update color based on hex code
    connect(hexLineEdit, &QLineEdit::textChanged, this,
            &MainWindow::updateColorOnHexCode);
    updateColorOnHexCode();

    //  update color cust om
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            connect(colorButtons[i][j], &QPushButton::clicked, this,
                    &MainWindow::updateColorCustomPalette);
        }
    }

    // panel - layout to hold previewer and tabs
    QVBoxLayout *layout = new QVBoxLayout();

    // panel container
    QWidget *panelContainer = new QWidget();
    panelContainer->setStyleSheet("background-color: rgb(100, 100, 100);");
    panel->setWidget(panelContainer);

    // preview area
    previewer = new Previewer();
    previewer->setFixedHeight(325);
    previewer->setStyleSheet("background-color: rgb(200, 200, 200);");
    // Connect Previewer to Model
    connect(model, &Model::updateFrameList, this, [this]() {
        QVector<QImage> imageList;
        for (Frame* frame : model->getFrames()) {
            if (frame) {
                imageList.append(frame->getImage());
            }
        }
        previewer->getImageListFromModel(imageList);
        previewer->activateAnimation();
    });

    // FramePanel - setup for managing frames
    framePanel = new FramePanel(model, this); // Instantiate FramePanel with Model

    // Tab widget for Colors and Frames
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->addTab(framePanel, "Frames"); // Use framePanel as the "Frames" tab

    // Styling for tab widget
    tabWidget->setStyleSheet("QTabWidget::pane {"
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
                             "}");

    // Layout for panelContainer to hold previewer and tabWidget

    layout->addWidget(previewer);
    layout->addWidget(tabWidget);
    panelContainer->setLayout(layout);

    // Add the panel as a dock widget
    addDockWidget(Qt::LeftDockWidgetArea, panel);

    // Canvas setup
    // Create the Canvas instance and set it as the central widget
    int canvasWidth = 800;  // Example width
    int canvasHeight = 800; // Example height

    canvas = new Canvas(canvasWidth, canvasHeight, this);
    qDebug() << "canvas created";
    editor->setCanvasInstance(canvas);
    setCentralWidget(canvas);

    setResolutionOnLoad(brushSize);

    connectSignals();
}

void MainWindow::updateColorOnSlider() {
    int redValue = redSlider->value();
    int blueValue = blueSlider->value();
    int greenValue = greenSlider->value();

    // Create a QColor from the RGB values
    QColor color(redValue, greenValue, blueValue);

    // Update the color of the button
    brushColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                                  .arg(redValue)
                                  .arg(greenValue)
                                  .arg(blueValue));

    // Update the hex code in the QLineEdit
    QString hexCode = color.name(); // Get the hex representation of the color
    hexLineEdit->setText(hexCode);
}

void MainWindow::updateColorOnHexCode() {
    QString hexCode = hexLineEdit->text().trimmed();
    if (hexCode.startsWith("#") && hexCode.length() == 7) {
        QColor color(hexCode);
        if (color.isValid()) {
            redSlider->setValue(color.red());
            greenSlider->setValue(color.green());
            blueSlider->setValue(color.blue());
            brushColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                                          .arg(color.red())
                                          .arg(color.green())
                                          .arg(color.blue()));
        }
    }
}

void MainWindow::updateColorCustomPalette() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    if (customColors.contains(clickedButton)) {
        // Set the button's color to the stored custom color
        clickedButton->setStyleSheet(QString("background-color: %1;")
                                         .arg(customColors[clickedButton].name()));
        brushColor->setStyleSheet(QString("background-color: %1;")
                                      .arg(customColors[clickedButton].name()));
        hexLineEdit->setText(customColors[clickedButton].name());
    } else {
        // Open a color dialog to let the user choose a color
        QColorDialog colorDialog;
        colorDialog.setWindowTitle("Choose Color");
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.selectedColor();

            // Set the button's color and store it in the map
            clickedButton->setStyleSheet(
                QString("background-color: %1;").arg(color.name()));
            brushColor->setStyleSheet(
                QString("background-color: %1;").arg(color.name()));
            customColors[clickedButton] = color;
            hexLineEdit->setText(color.name());
        }
    }
}

void MainWindow::sendColorToEditor() {
    int redValue = redSlider->value();
    int greenValue = greenSlider->value();
    int blueValue = blueSlider->value();

    QColor color(redValue, greenValue, blueValue);
    editor->setBrushColor(color);
}

void MainWindow::connectSignals() {
    connect(canvas, &Canvas::mousePressCanvas, editor,
            &pixelEditor::drawWithCurrTool);
    connect(canvas, &Canvas::sendCurrentImage, model,
            &Model::updateCurrentFrameImage);
    connect(model, &Model::updateDrawingPanel, framePanel,
            &FramePanel::updateButtonIconBasedOnFrame);
    connect(framePanel, &FramePanel::clearCanvas, canvas, &Canvas::clear);
    connect(framePanel, &FramePanel::frameSelected, canvas,
            &Canvas::drawFromFrame);
    connect(canvas, &Canvas::canvasModified, model,
            &Model::updateCurrentFrameImage);
    connect(model, &Model::updateFrameList, framePanel,
            &FramePanel::updateFrameList);
}

MainWindow::~MainWindow() {
    delete ui;
    delete editor;
    delete canvas;
}
