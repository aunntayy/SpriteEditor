/**
 * NOTES:
 *
 *  - need to get isFileSaved from Model
 *
 */


#include "filemanager.h"

FileManager::FileManager() {}

bool FileManager::saveToFile(const Model &model)
{
    qDebug() << "save button clicked";
    //showSaveDialog();


    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save File", "", "JSON Files (*.json);;All Files (*)");

    if (fileName.isEmpty()) { return false; } // file dialog cancelled

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument document(writeJSON());
        QByteArray byteArray = document.toJson();

        file.write(byteArray);
        file.close();
    }
    else
    {
        qWarning() << "Error occurred when writing to the file:" << file.errorString();
    }

    return true;
}

//bool FileManager::load(bool isCurrentFileSaved
bool FileManager::loadFromFile(const Model &model)
{
    qDebug() << "load button clicked";


    //if (!isCurrentFileSaved)
    if (true)
    {
        if(confirmSave() == true) { showSaveDialog(); }
    }

    //deserialize()
    showOpenDialog();
    return true;
}

QJsonObject FileManager::writeJSON(const Model &model)
{
    QJsonObject json;

    json.insert("frameRate", model.getFrameRate());
    json.insert("resolution", model.getResolution());

    QJsonArray frameArray;
    for (Frame* frame : model.getFrames())
    {
        QJsonObject frameObj;
        frameArray.append(frameObj);
    }
    json.insert("frames", frameArray);

    // possibly save customized color palette as well
}

void FileManager::readJSON()
{

}

QString FileManager::showSaveDialog()
{
    return QFileDialog::getSaveFileName(nullptr, "Save Sprite Project", "", "Sprite Editor File (*.sef);;All Files (*)");
}


QString FileManager::showOpenDialog()
{
    return QFileDialog::getOpenFileName(nullptr, "Open Sprite Project", "", "Sprite Editor File (*.sef);;All Files (*)");
}


bool FileManager::confirmSave()
{
    return QMessageBox::question(nullptr, "Confirm Save", "The current project is unsaved. Do you want to save this file?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

