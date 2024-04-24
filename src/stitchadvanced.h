#ifndef STITCHADVANCED_H
#define STITCHADVANCED_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class stitchAdvanced;
}

class stitchAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit stitchAdvanced(GUIvals &guiVals, QWidget *parent = nullptr);
    ~stitchAdvanced();

private slots:

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_boundBoxCheckBox_stateChanged(int arg1);

private:
    Ui::stitchAdvanced *ui;
    GUIvals* gVals;
};

#endif // STITCHADVANCED_H
