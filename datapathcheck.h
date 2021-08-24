#ifndef DATAPATHCHECK_H
#define DATAPATHCHECK_H

#include <QDialog>
#include <QLineEdit>
#include <QDirIterator>
#include <iostream>
#include "datapath.h"
#include "outputbox.h"


namespace Ui {
class dataPathCheck;
}

class dataPathCheck : public QDialog
{
    Q_OBJECT

public:
    explicit dataPathCheck(const std::vector<dataPath> &dPaths, const std::vector<QString> &patterns, const QString stepSize, QWidget *parent = nullptr);
    ~dataPathCheck();

private slots:
    void on_cancelPushButton_clicked();

    void on_submitPushButton_clicked();

private:
    //void makeNewPathName(const QString &pathName);
    void makeNewPath(const QString &dPathName, const QString &stepSize);

    Ui::dataPathCheck *ui;
    outputBox mainBox;
    //std::vector<dataPath> *dPaths;
};

#endif // DATAPATHCHECK_H
