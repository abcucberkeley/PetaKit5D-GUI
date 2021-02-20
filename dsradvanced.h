#ifndef DSRADVANCED_H
#define DSRADVANCED_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DSRadvanced;
}

class DSRadvanced : public QDialog
{
    Q_OBJECT

public:
    explicit DSRadvanced(GUIvals &guiVals, QWidget *parent = nullptr);
    ~DSRadvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::DSRadvanced *ui;
    GUIvals* gVals;
};

#endif // DSRADVANCED_H
