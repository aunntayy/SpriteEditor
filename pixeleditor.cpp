#include "pixeleditor.h"
#include<QDebug>
pixelEditor::pixelEditor(QObject *parent) : QObject(parent) {}

void pixelEditor::setTool(Tools pickTool){
    currentTool = pickTool;

}

int pixelEditor::setToolSize(int toolSize){
    emit brushSizeChanged(currentToolSize);
    return currentToolSize = toolSize;
    qDebug() << "Tool set to:" << currentToolSize;
}
