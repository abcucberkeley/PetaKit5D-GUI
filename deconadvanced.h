#ifndef DECONADVANCED_H
#define DECONADVANCED_H

#include <QDialog>
#include "mainwindow.h"

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

    void on_cppDeconPathBrowseButton_clicked();

    void on_cppDeconPathLineEdit_textChanged(const QString &arg1);

    void on_cudaDeconPathBrowseButton_clicked();

    void on_cudaDeconPathLineEdit_textChanged(const QString &arg1);

    void on_otfgenPathBrowseButton_clicked();

    void on_otfgenPathLineEdit_textChanged(const QString &arg1);

private:
    Ui::deconAdvanced *ui;
    GUIvals* gVals;
};

#endif // DECONADVANCED_H
