#ifndef LOADPREVIOUSSETTINGS_H
#define LOADPREVIOUSSETTINGS_H

#include <QFuture>
#include <QDialog>
#include <QProgressDialog>

namespace Ui {
class loadPreviousSettings;
}

class loadPreviousSettings : public QDialog
{
    Q_OBJECT

public:
    explicit loadPreviousSettings(bool &lPS, bool &kill, bool &isMcc, std::string &pathToMatlab, QWidget *parent = nullptr);
    ~loadPreviousSettings();
    bool *lPS;
    bool *kill;
    bool *isMcc;
    std::string *pathToMatlab;
    std::string defaultMCCPath;
    std::string tmpDir;
    QString mccInstallProgressString;
    QProgressDialog *mccInstallProgress;
    bool installing;
    QMutex futuresLock;

private:
    std::vector<QFuture<void>> futures;

    void runInstallScriptMCC();

    void unzipMCC();

    void createMccInstallProgress(int initialVal);

    int installMCC();

    void curlMCC();

    int downloadMCC();

    void checkPath();

    void reject();

    int getMatlabPath();

private slots:
    void on_noButton_clicked();

    void on_yesButton_clicked();

    void on_lpsMatlabPathResetButton_clicked();

private:
    Ui::loadPreviousSettings *ui;
};

#endif // LOADPREVIOUSSETTINGS_H
