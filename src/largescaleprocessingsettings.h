#ifndef LARGESCALEPROCESSINGSETTINGS_H
#define LARGESCALEPROCESSINGSETTINGS_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class largeScaleProcessingSettings;
}

class largeScaleProcessingSettings : public QDialog
{
    Q_OBJECT

public:
    explicit largeScaleProcessingSettings(GUIvals& guiVals, QWidget *parent = nullptr);
    ~largeScaleProcessingSettings();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_blockSizeCheckBox_stateChanged(int arg1);

    void on_inputBboxCheckBox_stateChanged(int arg1);

    void on_tileOutBboxCheckBox_stateChanged(int arg1);

private:
    Ui::largeScaleProcessingSettings *ui;
    GUIvals *gVals;
};

#endif // LARGESCALEPROCESSINGSETTINGS_H
