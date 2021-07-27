#ifndef DATAPATHSRECURSIVE_H
#define DATAPATHSRECURSIVE_H

#include <QDialog>
#include <unordered_map>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include "datapath.h"

namespace Ui {
class dataPathsRecursive;
}

class dataPathsRecursive : public QDialog
{
    Q_OBJECT

public:
    explicit dataPathsRecursive(dataPath &currPaths, QWidget *parent = nullptr);
    ~dataPathsRecursive();

    void makeNewPath(int i, QString currPath);

private slots:
    void on_dataPathRecursiveLineEdit_textChanged(const QString &arg1);
    void on_searchButton_clicked();

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::dataPathsRecursive *ui;
    std::unordered_map<std::string,std::pair<bool, std::string>>* currPaths;
    std::string currPath;
    int maxDepth;
    std::vector<std::tuple<QHBoxLayout*, QLabel*, QCheckBox*, QLineEdit*>> paths;
};

#endif // DATAPATHSRECURSIVE_H
