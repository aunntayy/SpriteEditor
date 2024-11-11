/**
 * NOTES:
 *
 *  - need to get isFileSaved from Model
 *
 */


#include "filemanager.h"
#include <QDebug>

FileManager::FileManager() {}

bool FileManager::save()
{
    qDebug() << "save button clicked";

    // handle save confirmations/warnings
    //serialize()
    showSaveDialog();
    return true;
}

//bool FileManager::load(bool isCurrentFileSaved
bool FileManager::load()
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

bool FileManager::serialize()
{
    // serialize
    // save

    return true;
}

bool FileManager::deserialize()
{
    // deserialize
    // validate
    // load

    return true;
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


// slots

void FileManager::onSaveButtonClicked()
{
    save();
}

//void FileManager::onLoadButtonClicked(bool isCurrentFileSaved)
void FileManager::onLoadButtonClicked()
{
    //load(isCurrentFileSaved);
    load();
}
