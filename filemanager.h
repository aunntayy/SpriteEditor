#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFileDialog>
#include <QObject>
#include <QMessageBox>
#include "Model.h"

class FileManager : public QObject
{
    Q_OBJECT

public:

    FileManager();

    /**
     * @brief Saves a serialized model.
     */
    bool save();

    /**
     * @brief Loads a deserialized file.
     */
    //bool load(bool isCurrentFileSaved);
    bool load();

private:

    /**
     * @brief Serializes a model.
     */
    bool serialize();

    /**
     * @brief Deserializes a file.
     */
    bool deserialize();

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
    void onSaveButtonClicked();

    //void onLoadButtonClicked(bool isCurrentFileSaved);
    void onLoadButtonClicked();

};

#endif // FILEMANAGER_H
