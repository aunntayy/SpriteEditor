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


#include "filemanager.h"
#include <QDebug>

FileManager::FileManager() {}

void FileManager::saveToFile(const Model &model)
{
    qDebug() << "save button clicked";
    qDebug() << "Model address in filemanager:" << &model;


    QString fileName = showSaveDialog();

    if (fileName.isEmpty()) { /* show a warning */ } // file dialog cancelled

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument document(writeJson(model));
        qDebug() << "3";
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
    int count = 0;
    qDebug() << "writing json";
    int num_frames = model.getFrames().count();
    qDebug() << num_frames;

    QJsonObject json;

    qDebug() << model.getResolution();
    qDebug() << "Model address in filemanager:" << &model;
    json.insert("frameRate", model.getFrameRate());
    json.insert("resolution", model.getResolution());

    QJsonArray frameArray;
    for (Frame* frame : model.getFrames())
    {
        count++;
        qDebug() << count;

        int height = frame->getImage().height();
        int width = frame->getImage().width();

        QJsonObject frameObj;
        frameObj.insert("width", width);
        frameObj.insert("height", height);

        QJsonArray pixelData;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                QColor color = frame->getPixelColor(x, y);

                QJsonObject colorObj;
                colorObj.insert("r", color.red());
                colorObj.insert("g", color.green());
                colorObj.insert("b", color.blue());
                colorObj.insert("a", color.alpha());

                pixelData.append(colorObj);
            }
        }
        frameObj.insert("pixels", pixelData);

        frameArray.append(frameObj);
    }

    json.insert("frames", frameArray);

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

    // model.frameList = frames; // need to be a friend or iterate

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

