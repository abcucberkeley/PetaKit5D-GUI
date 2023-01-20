#ifndef LOADPREVIOUSSETTINGS_H
#define LOADPREVIOUSSETTINGS_H

#include <QDialog>

namespace Ui {
class loadPreviousSettings;
}

class loadPreviousSettings : public QDialog
{
    Q_OBJECT

public:
    explicit loadPreviousSettings(bool &lPS, bool &isMcc, std::string &pathToMatlab, QWidget *parent = nullptr);
    ~loadPreviousSettings();
    bool *lPS;
    bool *isMcc;
    std::string *pathToMatlab;
    std::string defaultMCCPath;

private:
    void getMatlabPath();

private slots:
    void on_noButton_clicked();

    void on_yesButton_clicked();

    void on_lpsMatlabPathResetButton_clicked();

private:
    Ui::loadPreviousSettings *ui;
};

#endif // LOADPREVIOUSSETTINGS_H
