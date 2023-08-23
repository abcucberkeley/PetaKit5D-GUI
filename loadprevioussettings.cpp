#include "loadprevioussettings.h"
#include "ui_loadprevioussettings.h"
#include "submissionchecks.h"
#include <stdlib.h>
#include <QDir>
#include <QInputDialog>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrent>
#include <iostream>
#include <fstream>
#include <thread>
#include <functional>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

loadPreviousSettings::loadPreviousSettings(bool &lPS, bool &kill, bool &isMcc, std::string &pathToMatlab, QWidget *parent) :
    QDialog(parent),
    tmpDir(QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntimeTmp"),
    mccInstallProgressString("First-time setup.\nThis may take a few minutes depending on your hardware."),
    mccInstallProgress(nullptr),
    installing(false),
    ui(new Ui::loadPreviousSettings)
{
    this->lPS = &lPS;
    this->kill = &kill;
    this->isMcc = &isMcc;
    this->pathToMatlab = &pathToMatlab;
    this->defaultMCCPath = QCoreApplication::applicationDirPath().toStdString()+"/MATLAB_Runtime/R2022b";

    ui->setupUi(this);


    if(this->pathToMatlab->empty()) getMatlabPath();
    else{
        ui->lpsUseMCCCheckBox->setChecked(*(this->isMcc));
        ui->lpsMatlabPathLineEdit->setText(QString(this->pathToMatlab->c_str()));
    }
}

loadPreviousSettings::~loadPreviousSettings()
{
    for(auto future : futures) future.waitForFinished();
    delete ui;
}

void loadPreviousSettings::runInstallScriptMCC(){
    mccInstallProgress->setValue(75);
    mccInstallProgress->setLabelText(mccInstallProgressString+"\nInstalling the MCC Runtime.");

    std::string installName;
    // The installer is called setup on Windows and install on Linux/Mac
    #ifdef _WIN32
    installName = "setup";
    #else
    installName = "install";
    #endif

    //std::string installCmd = "\"\""+tmpDir+"/"+installName+"\"\" -agreeToLicense yes -destinationFolder \""+QCoreApplication::applicationDirPath().toStdString()+"/MATLAB_Runtime\"";
    std::string installCmd = "\"\""+tmpDir+"/"+installName+"\" -agreeToLicense yes -destinationFolder \""+QCoreApplication::applicationDirPath().toStdString()+"/MATLAB_Runtime\"\"";
    //std::cout << installCmd << std::endl;
    /*
    QString filename = "C:/Users/matt/Desktop/LLSM_Processing_GUI_releases/LLSM_Processing_GUI - Copy/out.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << QString(installCmd.c_str());
    }
    */
    system(installCmd.c_str());

    // Remove tmpDir
    //mccInstallProgress->setValue(99);
    //QDir dir(QString::fromStdString(tmpDir));
    //dir.removeRecursively();

    messageBoxSuccess(this->parentWidget(), "First-time setup complete.\nThe MCC Runtime will continute to install in the background.\nPlease press ok and restart the GUI now.\n");
    mccInstallProgress->setValue(100);
    //QDialog::reject();
}

void loadPreviousSettings::unzipMCC(){
    mccInstallProgress->setLabelText(mccInstallProgressString+"\nUnzipping the MCC Runtime.");

    std::string unzipCmd;

    // Make the tmp dir if it doesn't exist
    QDir dir(QString::fromStdString(tmpDir));
    if (!dir.exists())
        dir.mkpath(".");

    #ifdef _WIN32
    unzipCmd = "tar -xf \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" -C \""+tmpDir+"\"";
    #elif __linux__
    // Linux and Mac can use unzip (Check if installed for Linux)
    if(!system("which unzip")) unzipCmd = "unzip -q "+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip -d "+tmpDir;
    else unzipCmd = "\""+QCoreApplication::applicationDirPath().toStdString()+"/7zzs\" x \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" -o \""+tmpDir+"\"";
    #else
    unzipCmd = "unzip -q \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" -d \""+tmpDir+"\"";
    #endif
    system(unzipCmd.c_str());
    runInstallScriptMCC();
}

void loadPreviousSettings::createMccInstallProgress(int initialVal){
    mccInstallProgress = new QProgressDialog(mccInstallProgressString, QString(), 0, 100, this, Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    mccInstallProgress->setWindowModality(Qt::WindowModal);
    mccInstallProgress->setValue(initialVal);
    mccInstallProgress->show();
}

int loadPreviousSettings::installMCC(){
    if(!mccInstallProgress) createMccInstallProgress(50);

    QFuture<void> future = QtConcurrent::run(&loadPreviousSettings::unzipMCC,this);
    futuresLock.lock();
    futures.push_back(future);
    futuresLock.unlock();

    return 0;
}

void loadPreviousSettings::curlMCC(){
    mccInstallProgress->setLabelText(mccInstallProgressString+"\nDownloading the MCC Runtime.");
    mccInstallProgress->repaint();
    std::string downloadCmd = "curl -o \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" ";
    #ifdef _WIN32
    downloadCmd.append("https://ssd.mathworks.com/supportfiles/downloads/R2022b/Release/6/deployment_files/installer/complete/win64/MATLAB_Runtime_R2022b_Update_6_win64.zip");
    #elif __linux__
    downloadCmd.append("https://ssd.mathworks.com/supportfiles/downloads/R2022b/Release/6/deployment_files/installer/complete/glnxa64/MATLAB_Runtime_R2022b_Update_6_glnxa64.zip");
    #else
    downloadCmd.append("https://ssd.mathworks.com/supportfiles/downloads/R2022b/Release/6/deployment_files/installer/complete/maci64/MATLAB_Runtime_R2022b_Update_6_maci64.zip");
    #endif
    system(downloadCmd.c_str());
    mccInstallProgress->setValue(50);

    installMCC();
}

int loadPreviousSettings::downloadMCC(){
    if(!mccInstallProgress) createMccInstallProgress(25);

    QFuture<void> future = QtConcurrent::run(&loadPreviousSettings::curlMCC,this);
    futuresLock.lock();
    futures.push_back(future);
    futuresLock.unlock();
    return 0;
}

void loadPreviousSettings::checkPath(){
    *isMcc = ui->lpsUseMCCCheckBox->isChecked();
    *pathToMatlab = ui->lpsMatlabPathLineEdit->text().toStdString();
    if(*isMcc){
        // Check if the path to the default MCC is correct
        if(*pathToMatlab != defaultMCCPath){
            bool ok = false;
            QStringList mccSL({"Change the path to the default MCC path and continue",
                               "Uncheck MCC and continue",
                               "Take me back to the previous menu",
                               "Continue anyway (NOT RECOMMENDED)",
                               "Exit"});
            QString userText = QInputDialog::getItem(this, "MCC Path does not match the default path",
                                                     "The MCC box is checked but the path does not match the default "
                                                     "MCC path.\nYou may have accidentally checked the Use MCC box,\nbut "
                                                     "if this was intended then using the non default is NOT officially "
                                                     "supported due to versioning issues.\nPlease select an option:", mccSL,
                                                     0, false, &ok, Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint
                                                     | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
            if(ok){
                if(userText == mccSL[0]){
                    ui->lpsMatlabPathLineEdit->setText(QString::fromStdString(defaultMCCPath));
                    checkPath();
                }
                else if(userText == mccSL[1]){
                    ui->lpsUseMCCCheckBox->setChecked(false);
                    checkPath();
                }
                else if(userText == mccSL[2]) return;
                else if(userText == mccSL[3]){
                    QDialog::reject();
                    return;
                }
                else if(userText == mccSL[4]){
                    *kill = true;
                    QDialog::reject();
                    return;
                }
            }
            else{
                *kill = true;
                QDialog::reject();
                return;
            }
        }
        if(*pathToMatlab == defaultMCCPath){
            QDir dir(QString::fromStdString(defaultMCCPath+"/bin"));
            if (!dir.exists()){
                if (QFileInfo::exists(QString::fromStdString(QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip"))){
                    bool ok = false;
                    QStringList mccSL({"Install the MCC Runtime",
                                       "Take me back to the previous menu",
                                       "Exit"});
                    QString userText = QInputDialog::getItem(this, "MCC Runtime First-time Setup",
                                                             "The MCC box is checked and set to the default path.\nA first-time "
                                                             "setup is required to install the MCC Runtime.\n"
                                                             "WARNING: Clicking cancel will exit the Application\n"
                                                             "Please select an option:", mccSL,
                                                             0, false, &ok, Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint
                                                             | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
                    if (ok){
                        if(userText == mccSL[0]){
                            installMCC();
                            return;
                        }
                        else if(userText == mccSL[1]){
                            return;
                        }
                        else if(userText == mccSL[2]){
                            *kill = true;
                            QDialog::reject();
                            return;
                        }
                        else return;
                    }
                    else{
                        *kill = true;
                        QDialog::reject();
                        return;
                    }
                }
                else{
                    bool ok = false;
                    QStringList mccSL({"Download and Install the MCC Runtime (Internet connection required)",
                                       "Take me back to the previous menu",
                                       "Exit"});
                    QString userText = QInputDialog::getItem(this, "MCC Runtime First-time Setup",
                                                             "The MCC box is checked and set to the default path\nA first-time "
                                                             "setup is required to install the MCC Runtime\n"
                                                             "A download is also required because the package cannot be found on your system\n"
                                                             "WARNING: Clicking cancel will exit the Application\n"
                                                             "Please select an option:", mccSL,
                                                             0, false, &ok, Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint
                                                             | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
                    if (ok){
                        if(userText == mccSL[0]){
                            downloadMCC();
                            return;
                        }
                        else if(userText == mccSL[1]){
                            return;
                        }
                        else if(userText == mccSL[2]){
                            *kill = true;
                            QDialog::reject();
                            return;
                        }
                        else return;
                    }
                    else{
                        *kill = true;
                        QDialog::reject();
                    }
                }
            }
            else QDialog::reject();
        }

    }
    else{
        if(!QFileInfo::exists(QString::fromStdString(*pathToMatlab))){
            bool ok = false;
            QStringList mccSL({"Switch to MCC and continue",
                               "Take me back to the previous menu",
                               "Exit"});
            QString userText = QInputDialog::getItem(this, "Matlab Installation not found",
                                                     "An installation of matlab cannot be found at the location you specified\n"
                                                     "Check that the path you provided is correct and that you have access to it\n"
                                                     "WARNING: Clicking cancel will exit the Application\n"
                                                     "Please select an option:", mccSL,
                                                     0, false, &ok, Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint
                                                     | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
            if (ok){
                if(userText == mccSL[0]){
                    ui->lpsMatlabPathLineEdit->setText(QString::fromStdString(defaultMCCPath));
                    ui->lpsUseMCCCheckBox->setChecked(true);
                    checkPath();
                }
                else if(userText == mccSL[1]){
                    return;
                }
                else if(userText == mccSL[2]){
                    *kill = true;
                    QDialog::reject();
                    return;
                }
                else return;
            }
            else{
                *kill = true;
                QDialog::reject();
                return;
            }
        }
        else QDialog::reject();
    }
}

void loadPreviousSettings::reject(){
    //QFuture<void> future = QtConcurrent::run(&loadPreviousSettings::checkPath,this);
    checkPath();
    //futuresLock.lock();
    //futures.push_back(future);
    //futuresLock.unlock();

    //int ret = checkPath();
    //if(ret) return;
    //QDialog::reject();
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
    if(ui->lpsUseMCCCheckBox->isChecked() && err) messageBoxSuccess(this, "Path reset to the default MCC path. We were unable to find your MATLAB installation. If you have one, it may be at a custom location. You can provide the full path to the executable here and uncheck the Use MCC checkbox if you wish to use it.");
    else if(ui->lpsUseMCCCheckBox->isChecked()) messageBoxSuccess(this, "Path reset to the default MCC path. If you would like the path to reset to your default MATLAB path. Uncheck the Use MCC checkbox and click the reset path button again.");
    else messageBoxSuccess(this, "Path reset to your default MATLAB path. If you would like the path to reset to the default MCC path. Check the Use MCC checkbox and click the reset path button again.");
}

