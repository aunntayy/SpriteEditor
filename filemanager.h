#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFileDialog>
#include <QObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Model.h"

#include <QDebug>

class FileManager : public QObject
{
    Q_OBJECT

public:

    FileManager();

private:

    /**
     * @brief Serializes a model.
     */
    bool serialize();

    QJsonObject writeJSON();

    /**
     * @brief Deserializes a file.
     */
    bool deserialize();

    void readJSON();

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
    bool saveToFile(const Model &model);

    /**
     * @brief Loads a deserialized file.
     */
    //bool load(bool isCurrentFileSaved);
    bool loadFromFile(const Model &model);

};

#endif // FILEMANAGER_H
