#ifndef DATAPATHS_H
#define DATAPATHS_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <tuple>

namespace Ui {
class dataPaths;
}

class dataPaths : public QDialog
{
    Q_OBJECT

public:
    explicit dataPaths(std::vector<std::string> &dPaths, bool folder, QWidget *parent = nullptr);
    explicit dataPaths(std::vector<std::string> &dPaths, bool folder, std::string pathType, QWidget *parent = nullptr);
    ~dataPaths();

private slots:
    void on_addPathButton_clicked();

    void on_removePathButton_clicked();

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_dataPath1BrowseButton_clicked();

    void on_dataPath1LineEdit_textChanged(const QString &arg1);

    void on_dataPath2BrowseButton_clicked();

    void on_dataPath2LineEdit_textChanged(const QString &arg1);

    void on_dataPath3BrowseButton_clicked();

    void on_dataPath3LineEdit_textChanged(const QString &arg1);

    void on_dataPath4BrowseButton_clicked();

    void on_dataPath4LineEdit_textChanged(const QString &arg1);

    void on_dataPath5BrowseButton_clicked();

    void on_dataPath5LineEdit_textChanged(const QString &arg1);

    void on_dataPath6BrowseButton_clicked();

    void on_dataPath6LineEdit_textChanged(const QString &arg1);

private:
    Ui::dataPaths *ui;
    int activePaths;
    bool maxPaths;
    bool folder;
    std::vector<std::tuple<QLabel*, QLineEdit*, QPushButton*>> paths;
    std::vector<std::string> *dpHand;
};

#endif // DATAPATHS_H
