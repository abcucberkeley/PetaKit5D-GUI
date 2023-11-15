#ifndef MASKFILENAMES_H
#define MASKFILENAMES_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class maskFilenames;
}

class maskFilenames : public QDialog
{
    Q_OBJECT

public:
    explicit maskFilenames(std::vector<std::string> &maskNames, QWidget *parent = nullptr);
    ~maskFilenames();

private slots:
    void on_browseButton_clicked();

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::maskFilenames *ui;
    std::vector<std::string> *maskNames;
    QString mostRecentDir;
};

#endif // MASKFILENAMES_H
