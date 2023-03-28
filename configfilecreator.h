#ifndef CONFIGFILECREATOR_H
#define CONFIGFILECREATOR_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class configFileCreator;
}

class configFileCreator : public QDialog
{
    Q_OBJECT

public:
    explicit configFileCreator(configFileVals* cFileVals, QWidget *parent = nullptr);
    ~configFileCreator();

private slots:
    void on_saveFileButton_clicked();

    void on_exitButton_clicked();

    void on_jsonConfigFileNameButton_clicked();

private:
    Ui::configFileCreator *ui;
    configFileVals* cFileVals;
};

#endif // CONFIGFILECREATOR_H
