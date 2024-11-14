/**
 * @class FileManager
 * @brief The FileManager class handles file operations for saving and loading
 *        a Model object in JSON format. It provides functions to serialize and
 *        deserialize the model data, as well as to interact with the file system
 *        using dialogs.
 *
 * This class offers an interface to save the current state of a Model object
 * to a file or to load a previously saved Model from a file. The data is saved
 * and loaded in JSON format, allowing for easy reading and writing of structured
 * data. The FileManager relies on Qt's QFileDialog to prompt the user for file
 * selection and QMessageBox for confirmations.
 */

/*
 * FileManager.h
 *
 * Description:
 * The FileManager class handles file operations for saving and loading
 * a Model object in JSON format. It provides functions to serialize and
 * deserialize the model data, as well as to interact with the file system
 * using dialogs.
 *
 * Author: Phuc Hoang - Trenton Stratton
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFileDialog>
#include <QObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QColor>
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
