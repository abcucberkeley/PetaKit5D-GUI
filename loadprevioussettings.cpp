#include "loadprevioussettings.h"
#include "ui_loadprevioussettings.h"
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

void loadPreviousSettings::getMatlabPath(){
    bool jobSuccess = true;
    std::string matlabCmd;
    std::string matlabPathTxt = QCoreApplication::applicationDirPath().toStdString()+"/matlabPath/matlabPath.txt";
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
    }
    else{
        ui->lpsUseMCCCheckBox->setChecked(true);
        ui->lpsMatlabPathLineEdit->setText(QString(defaultMCCPath.c_str()));
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
    getMatlabPath();
}

