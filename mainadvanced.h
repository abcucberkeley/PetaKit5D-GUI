#ifndef MAINADVANCED_H
#define MAINADVANCED_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class mainAdvanced;
}

class mainAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit mainAdvanced(GUIvals& guiVals, QWidget *parent = nullptr);
    ~mainAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::mainAdvanced *ui;
    GUIvals* gVals;
};

#endif // MAINADVANCED_H