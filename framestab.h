#ifndef FRAMESTAB_H
#define FRAMESTAB_H

#include <QWidget>
#include "framemanager.h"
#include <QTabWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

class FramesTab : public QWidget
{
    Q_OBJECT

public:
    FramesTab(FrameManager* frameManager, QWidget *parent = nullptr);

private slots:
    void onAddFrameClicked();
    void onDuplicateFrameClicked();
    void updateFrameList();
    void connectSignalsAndSlots();

private:
    FrameManager *frameManager;
    QScrollArea *scrollArea;
    QVBoxLayout* framePanel;
    QWidget* framesList;
    QPushButton *addFrameButton;
    QPushButton *duplicateButton;
};

#endif // FRAMESTAB_H
