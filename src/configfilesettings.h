#ifndef CONFIGFILESETTINGS_H
#define CONFIGFILESETTINGS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class configFileSettings;
}

class configFileSettings : public QDialog
{
    Q_OBJECT

public:
    explicit configFileSettings(configFileVals* cFileVals, QWidget *parent = nullptr);
    ~configFileSettings();

private slots:
    void on_submitButton_clicked();

    void on_cancelButton_clicked();

    void on_createAConfigFileButton_clicked();

private:
    Ui::configFileSettings *ui;
    configFileVals* cFileVals;
};

#endif // CONFIGFILESETTINGS_H
