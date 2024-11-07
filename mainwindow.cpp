#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QToolBar>
#include <QVBoxLayout>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSplitter>
#include <QColorDialog>

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // window
    this->setWindowTitle("CS3505 Sprite Editor");
    this->setFixedSize(1200, 900);
    this->move(250, 50);
    this->setStatusBar(nullptr);

    // toolbar
    QToolBar *toolBar = addToolBar("Toolbar");
    toolBar->setFixedHeight(50);
    toolBar->setStyleSheet(
        "background-color: rgb(100, 100, 100);"); // change color
    QAction *action1 = new QAction("File Stuff", this);
    toolBar->addAction(action1);
    QAction *action2 = new QAction("Other Tools", this);
    toolBar->addAction(action2);

    // panel
    QDockWidget *panel = new QDockWidget("Panel", this);
    panel->setFixedWidth(350);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setSizePolicy(sizePolicy);
    panel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // panel - widget to hold layout
    QWidget *panelContainer = new QWidget();
    panelContainer->setStyleSheet(
        "background-color: rgb(100, 100, 100);"); // change color
    panel->setWidget(panelContainer);

    // panel - previewer
    QWidget *previewer = new QWidget();
    previewer->setFixedHeight(325);
    previewer->setStyleSheet(
        "background-color: rgb(200, 200, 200);"); // change color

    QWidget *colorsTab = new QWidget();

    // panel - tabs
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->addTab(colorsTab, "Colors");
    tabWidget->addTab(new QWidget(), "Frames");

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
    for(int i = 0; i < 6;i++){
        for(int j = 0; j < 6;j++){
            connect(colorButtons[i][j], &QPushButton::clicked, this,
                    &MainWindow::updateColorCustomPalette);
        }
    }

    // panel - layout to hold previewer and tabs
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(previewer);
    layout->addWidget(tabWidget);
    panelContainer->setLayout(layout);

    addDockWidget(Qt::LeftDockWidgetArea, panel);

    // canvas
    QWidget *canvas = new QWidget();
    canvas->setStyleSheet("background-color: rgb(0, 0, 0);");
    setCentralWidget(canvas);
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

void MainWindow::updateColorCustomPalette(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());

    if (customColors.contains(clickedButton)) {
        // Set the button's color to the stored custom color
        clickedButton->setStyleSheet(QString("background-color: %1;").arg(customColors[clickedButton].name()));
        brushColor->setStyleSheet(QString("background-color: %1;").arg(customColors[clickedButton].name()));
         hexLineEdit->setText(customColors[clickedButton].name());
    } else {
        // Open a color dialog to let the user choose a color
        QColorDialog colorDialog;
        colorDialog.setWindowTitle("Choose Color");
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.selectedColor();

            // Set the button's color and store it in the map
            clickedButton->setStyleSheet(QString("background-color: %1;").arg(color.name()));
            brushColor->setStyleSheet(QString("background-color: %1;").arg(color.name()));
            customColors[clickedButton] = color;
            hexLineEdit->setText(color.name());
        }
    }
}

MainWindow::~MainWindow() { delete ui; }
