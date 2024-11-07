#include "pixeleditor.h"
#include<QDebug>
pixelEditor::pixelEditor(QObject *parent) : QObject(parent) {}

void pixelEditor::setTool(Tools pickTool){
    currentTool = pickTool;
    qDebug() << "Tool set to:" << currentTool;
}

int pixelEditor::setToolSize(int toolSize){
    return currentToolSize = toolSize;
    qDebug() << "Tool set to:" << currentToolSize;
}
