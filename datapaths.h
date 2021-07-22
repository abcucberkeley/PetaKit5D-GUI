#ifndef DATAPATHS_H
#define DATAPATHS_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <tuple>
#include <QCheckBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QBoxLayout>

namespace Ui {
class dataPaths;
}

class dataPaths : public QDialog
{
    Q_OBJECT

public:
    explicit dataPaths(std::vector<std::string> &dPaths, bool folder, QString &mostRecentDir, QWidget *parent = nullptr);
    explicit dataPaths(std::vector<std::string> &dPaths, bool folder, QString &mostRecentDir, const size_t &channels, const std::vector<QString> &channelNames, QWidget *parent = nullptr);
    ~dataPaths();

private slots:
    void on_addPathButton_clicked();

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_dataPathBrowseButton_clicked();

    void on_dataPathLineEdit_textChanged(const QString &arg1);

    void on_dataPathRemoveButton_clicked();

    void on_dataPathCheckBox_stateChanged(int checked);

    void makeNewPath(int i);

private:
    Ui::dataPaths *ui;
    QString *mostRecentDir;
    int activePaths;
    bool maxPaths;
    bool folder;
    std::vector<std::tuple<QHBoxLayout*, QLabel*, QLabel*, QCheckBox*, QLineEdit*, QPushButton*, QPushButton*>> paths;
    std::vector<std::string> *dpHand;
};

#endif // DATAPATHS_H
