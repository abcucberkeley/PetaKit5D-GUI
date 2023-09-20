#ifndef SIMRECONJOBADVANCED_H
#define SIMRECONJOBADVANCED_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class simReconJobAdvanced;
}

class simReconJobAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit simReconJobAdvanced(simReconVals& simreconVals, QWidget *parent = nullptr);
    ~simReconJobAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    simReconVals *srVals;
    Ui::simReconJobAdvanced *ui;
};

#endif // SIMRECONJOBADVANCED_H
