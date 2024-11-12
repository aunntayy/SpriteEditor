#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFileDialog>
#include <QObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include "Model.h"

#include <QDebug>

class FileManager : public QObject
{
    Q_OBJECT

public:

    FileManager();

private:

    QJsonObject writeJson(const Model &model);

    Model* readJson(const QJsonObject &json);

    /**
     * @brief Show a dialog to save a file
     */
    QString showSaveDialog();

    /**
     * @brief Show a dialog to select a file to load the model
     */
    QString showOpenDialog();

    /**
     * @brief Confirmation dialog for saving the file
     * @return
     */
    bool confirmSave();


public slots:

    /**
     * @brief Saves a serialized model.
     */
    void saveToFile(const Model &model);

    /**
     * @brief Loads a deserialized file.
     */
    Model* loadFromFile(const Model &model);

};

#endif // FILEMANAGER_H
