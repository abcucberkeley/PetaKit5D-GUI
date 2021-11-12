#ifndef SIMRECONRECONADVANCED_H
#define SIMRECONRECONADVANCED_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class simReconReconAdvanced;
}

class simReconReconAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit simReconReconAdvanced(simReconVals& simreconVals, QWidget *parent = nullptr);
    ~simReconReconAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    simReconVals *srVals;
    Ui::simReconReconAdvanced *ui;
};

#endif // SIMRECONRECONADVANCED_H
