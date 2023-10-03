#ifndef DECONADVANCED_H
#define DECONADVANCED_H

#include "mainwindow.h"
#include <QDialog>


namespace Ui {
class deconAdvanced;
}

class deconAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit deconAdvanced(GUIvals &guiVals, QWidget *parent = nullptr);
    ~deconAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_rlMethodSimplifiedRadioButton_toggled(bool checked);

private:
    Ui::deconAdvanced *ui;
    GUIvals* gVals;
};

#endif // DECONADVANCED_H
