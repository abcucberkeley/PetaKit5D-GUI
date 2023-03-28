#include "loadprevioussettings.h"
#include "ui_loadprevioussettings.h"
#include "submissionchecks.h"
#include <QDir>
#include <iostream>
#include <fstream>

loadPreviousSettings::loadPreviousSettings(bool &lPS, bool &isMcc, std::string &pathToMatlab, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadPreviousSettings)
{
    this->lPS = &lPS;
    this->isMcc = &isMcc;
    this->pathToMatlab = &pathToMatlab;
    this->defaultMCCPath = QCoreApplication::applicationDirPath().toStdString()+"/MATLAB_Runtime/R2022b";

    ui->setupUi(this);
    getMatlabPath();
}

loadPreviousSettings::~loadPreviousSettings()
{
    *isMcc = ui->lpsUseMCCCheckBox->isChecked();
    *pathToMatlab = ui->lpsMatlabPathLineEdit->text().toStdString();
    delete ui;
}

int loadPreviousSettings::getMatlabPath(){
    bool jobSuccess = true;
    std::string matlabCmd;
    // Make path if it does not exist
    QDir dir(QCoreApplication::applicationDirPath()+"/matlabPath");
    if (!dir.exists())
        dir.mkpath(".");
    std::string matlabPathTxt = QCoreApplication::applicationDirPath().toStdString()+"/matlabPath/matlabPath.txt";

    if(ui->lpsUseMCCCheckBox->isChecked()){
        ui->lpsMatlabPathLineEdit->setText(QString(defaultMCCPath.c_str()));
        return 0;
    }
    #ifdef __linux__
    matlabCmd = "which matlab > "+matlabPathTxt;
    jobSuccess = !system(matlabCmd.c_str());
    #elif _WIN32
    matlabCmd = "where matlab > "+matlabPathTxt;
    jobSuccess = !system(matlabCmd.c_str());
    #else // MAC
    jobSuccess = !system("ls /Applications | grep MATLAB");
    if(jobSuccess){
        matlabCmd = "printf %s \"/Applications/\" > "+matlabPathTxt+";";
        matlabCmd.append("ls /Applications | grep MATLAB | tail -1  | xargs printf %s >> "+matlabPathTxt+";");
        matlabCmd.append("echo \"/bin/matlab\" >> "+matlabPathTxt+";");
        std::cout << matlabCmd << std::endl;
        jobSuccess = !system(matlabCmd.c_str());
    }
    #endif

    if(jobSuccess){
        std::ifstream ifs(matlabPathTxt);
        std::string matlabPath;
        getline(ifs,matlabPath);
        ui->lpsUseMCCCheckBox->setChecked(false);
        ui->lpsMatlabPathLineEdit->setText(QString(matlabPath.c_str()));
        return 0;
    }
    else{
        ui->lpsUseMCCCheckBox->setChecked(true);
        ui->lpsMatlabPathLineEdit->setText(QString(defaultMCCPath.c_str()));
        return 1;
    }
}

void loadPreviousSettings::on_noButton_clicked()
{
    *lPS = false;
    loadPreviousSettings::close();
}

void loadPreviousSettings::on_yesButton_clicked()
{
    *lPS = true;
    loadPreviousSettings::close();
}

void loadPreviousSettings::on_lpsMatlabPathResetButton_clicked()
{
    int err = getMatlabPath();
    if(ui->lpsUseMCCCheckBox->isChecked() && err) messageBoxSuccess("Path reset to the default MCC path. We were unable to find your MATLAB installation. If you have one, it may be at a custom location. You can provide the full path to the executable here and uncheck the Use MCC checkbox if you wish to use it.");
    else if(ui->lpsUseMCCCheckBox->isChecked()) messageBoxSuccess("Path reset to the default MCC path. If you would like the path to reset to your default MATLAB path. Uncheck the Use MCC checkbox and click the reset path button again.");
    else messageBoxSuccess("Path reset to your default MATLAB path. If you would like the path to reset to the default MCC path. Check the Use MCC checkbox and click the reset path button again.");
}

