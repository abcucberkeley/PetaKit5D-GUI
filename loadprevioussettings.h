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
    explicit loadPreviousSettings(bool &lPS, QWidget *parent = nullptr);
    ~loadPreviousSettings();
    bool *lPS;

private slots:
    void on_noButton_clicked();

    void on_yesButton_clicked();

private:
    Ui::loadPreviousSettings *ui;
};

#endif // LOADPREVIOUSSETTINGS_H
