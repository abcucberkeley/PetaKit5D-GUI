#ifndef SIMRECONMAINADVANCED_H
#define SIMRECONMAINADVANCED_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class simReconMainAdvanced;
}

class simReconMainAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit simReconMainAdvanced(simReconVals& simreconVals, QWidget *parent = nullptr);
    ~simReconMainAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    simReconVals *srVals;
    Ui::simReconMainAdvanced *ui;
};

#endif // SIMRECONMAINADVANCED_H
