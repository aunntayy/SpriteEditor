#ifndef FRAMEPANEL_H
#define FRAMEPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <vector>
#include "model.h"

class FramePanel : public QWidget {
    Q_OBJECT

public:
    FramePanel(Model *model, QWidget *parent = nullptr);

private slots:
    void onAddFrame();
    void onDuplicateFrame();
    void onRemoveFrame();
    void updateFrameList();
    void selectFrame(int index);

private:
    Model *model;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *frameLayout;
    std::vector<QPushButton*> frameButtons;

    QPushButton *addButton;
    QPushButton *duplicateButton;
    QPushButton *removeButton;

    int selectedFrameIndex = -1;

    void addFrameButton(int index); // Helper to add a button to the layout
    void updateButtonIcon(QPushButton *button, const QPixmap &pixmap);
    void highlightSelectedFrame(int index);
};

#endif // FRAMEPANEL_H
