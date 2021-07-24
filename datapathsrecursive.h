#ifndef DATAPATHSRECURSIVE_H
#define DATAPATHSRECURSIVE_H

#include <QDialog>
#include <unordered_map>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>

namespace Ui {
class dataPathsRecursive;
}

class dataPathsRecursive : public QDialog
{
    Q_OBJECT

public:
    explicit dataPathsRecursive(std::unordered_map<std::string,std::unordered_map<std::string,std::string>> *currPaths, const std::string &currPath, const QString &currPattern,int maxDepth, QWidget *parent = nullptr);
    ~dataPathsRecursive();

    void makeNewPath(int i, QString currPath);

private slots:
    void on_dataPathRecursiveLineEdit_textChanged(const QString &arg1);
    void on_searchButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::dataPathsRecursive *ui;
    std::unordered_map<std::string,std::unordered_map<std::string,std::string>>* currPaths;
    std::string currPath;
    int maxDepth;
    std::vector<std::tuple<QHBoxLayout*, QLabel*, QCheckBox*, QLineEdit*>> paths;
};

#endif // DATAPATHSRECURSIVE_H
