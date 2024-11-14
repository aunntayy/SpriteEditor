#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include <QAction>
#include "Model.h"
#include "FileManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Model model;
    // FileManager fileManager;

    //QObject::connect(w.saveButton, &QAction::triggered, &fileManager, &FileManager::onSaveButtonClicked);
    //QObject::connect(w.loadButton, &QAction::triggered, &fileManager, &FileManager::onLoadButtonClicked);

    // QObject::connect(w.saveButton, &QAction::triggered, [&fileManager, &model]() {
    //     fileManager.saveToFile(model);
    // });

    // QObject::connect(w.loadButton, &QAction::triggered, [&fileManager, &model]() {
    //     fileManager.loadFromFile(model);
    // });

    w.show();
    return a.exec();
}
