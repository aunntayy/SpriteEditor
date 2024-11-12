/**
 * NOTES:
 *
 *
 */


#include "filemanager.h"

FileManager::FileManager() {}

void FileManager::saveToFile(const Model &model)
{
    qDebug() << "save button clicked";


    QString fileName = showSaveDialog();

    if (fileName.isEmpty()) { /* show a warning */ } // file dialog cancelled

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument document(writeJson(model));
        QByteArray byteArray = document.toJson();

        file.write(byteArray);
        file.close();
    }
    else
    {
        qWarning() << "Error occurred when writing to the file:" << file.errorString();
    }

    // need to set file isSaved to true
}

Model* FileManager::loadFromFile(const Model &model)
{
    qDebug() << "load button clicked";


    if (!model.isFileSaved())
    {
        if(confirmSave() == true) { showSaveDialog(); }
    }

    QString filePath = showOpenDialog();
    if (filePath.isEmpty())              // case user cancelled
    {
        Model* newModel = new Model();
        return newModel;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) // case error opening file
    {
        QMessageBox::warning(nullptr, "Load Error", "Could not open the file for reading.");
        Model* newModel = new Model();
        return newModel;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(fileData);
    file.close();

    if (document.isNull())               // case bad json
    {
        QMessageBox::warning(nullptr, "Parse Error", "Failed to parse the JSON file.");
        Model* newModel = new Model();
        return newModel;
    }

    return readJson(document.object());
}

QJsonObject FileManager::writeJson(const Model &model)
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

    return json;
}

Model* FileManager::readJson(const QJsonObject &json)
{
    Model* model = new Model();

    model->setFrameRate(json["frameRate"].toInt());
    model->setResolution(json["resolution"].toInt());

    QJsonArray frameArray = json["frames"].toArray();
    QVector<Frame*> frameList;
    for (const QJsonValue &value : frameArray)
    {
        QJsonObject frameObj = value.toObject(); // deserialize frame object from JSON
        Frame* frame = new Frame();              // make a constructor that accepts JSON object?
        frameList.append(frame);
    }

    //model.frameList = frames; // need to be a friend or iterate

    // possibly load customized color palette as well

    return model;
}

QString FileManager::showSaveDialog()
{
    return QFileDialog::getSaveFileName(nullptr, "Save Sprite Project", "", "JSON Files (*.json);;All Files (*)");
}


QString FileManager::showOpenDialog()
{
    return QFileDialog::getOpenFileName(nullptr, "Open Sprite Project", "", "JSON Files (*.json);;All Files (*)");
}


bool FileManager::confirmSave()
{
    return QMessageBox::question(nullptr, "Confirm Save", "The current project is unsaved. Do you want to save this file?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

