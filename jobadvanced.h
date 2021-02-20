#ifndef JOBADVANCED_H
#define JOBADVANCED_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class jobAdvanced;
}

class jobAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit jobAdvanced(GUIvals &guiVals, QWidget *parent = nullptr);
    ~jobAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_jobLogDirBrowseButton_clicked();

    void on_jobLogDirLineEdit_textChanged(const QString &arg1);

private:
    Ui::jobAdvanced *ui;
    GUIvals* gVals;
};

#endif // JOBADVANCED_H
