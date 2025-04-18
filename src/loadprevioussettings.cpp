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
    mccInstallProgressString("First-time setup\nThis may take a while depending on your hardware.\nYou may be prompted for Admin privileges if necessary.\nThe GUI may close as the install finishes in the background."),
    mccInstallProgress(nullptr),
    installing(false),
    ui(new Ui::loadPreviousSettings)
{
    this->lPS = &lPS;
    this->kill = &kill;
    this->isMcc = &isMcc;
    this->pathToMatlab = &pathToMatlab;
    #ifdef __linux__
    this->defaultMCCPath = QCoreApplication::applicationDirPath().toStdString()+"/MATLAB_Runtime/R2024b";
    #elif _WIN32
    this->defaultMCCPath = "C:/Program Files/MATLAB/MATLAB Runtime/R2024b";
    #else
    this->defaultMCCPath = "/Applications/MATLAB/MATLAB_Runtime/R2024b";
    #endif
    this->homeCacheDir = QDir::homePath().toStdString()+"/.PetaKit5D-GUI";
    ui->setupUi(this);


    if(this->pathToMatlab->empty()){
        //getMatlabPath();
        // Prefer the mcc version always
        ui->lpsUseMCCCheckBox->setChecked(true);
        ui->lpsMatlabPathLineEdit->setText(QString::fromStdString(defaultMCCPath));
    }
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
    auto lambda = [this](){mccInstallProgress->setValue(75);};
    QFuture<void> f = QtConcurrent::run(lambda);
    auto lambda2 = [this](){mccInstallProgress->setLabelText(mccInstallProgressString+"\nInstalling the MCC Runtime.");};
    QFuture<void> f2 = QtConcurrent::run(lambda2);

    std::string installName;
    std::string installCmd;

    // The installer is called setup on Windows and install on Linux/Mac
    #ifdef _WIN32
    installName = "setup";
    installCmd.append("\"\""+tmpDir+"/"+installName+"\" -agreeToLicense yes -destinationFolder \"C:/Program Files/MATLAB/MATLAB Runtime\"\"");
    #elif __linux__
    installName = "install";
    installCmd.append("\""+tmpDir+"/"+installName+"\" -agreeToLicense yes -destinationFolder \""+QCoreApplication::applicationDirPath().toStdString()+"/MATLAB_Runtime\"");
    #else
    std::string matlabDmg = "MATLAB_Runtime_R2024b_Update_5_maci64.dmg";
    std::string matlabApp = "InstallForMacOSX.app";
    installCmd.append("unzip -o -q \""+QCoreApplication::applicationDirPath().toStdString()+"/PetaKit5D/mcc/mac/PetaKit5DMCC.zip\" -d /Applications/PetaKit5DMCC/;");
    installCmd.append("hdiutil attach \"\""+tmpDir+"/"+matlabDmg+"\"\";");
    installCmd.append("cp -r -f /Volumes/"+matlabDmg.substr(0,matlabDmg.size()-4)+"/"+matlabApp+" \"\""+tmpDir+"\"\""+";");
    installCmd.append("hdiutil detach /Volumes/"+matlabDmg.substr(0,matlabDmg.size()-4)+";");
    installCmd.append("open -W -n \"\""+tmpDir+"/"+matlabApp+"\"\"");
    #endif

    system(installCmd.c_str());

    #ifndef __APPLE__
    mccInstallProgress->setValue(100);
    #else
    //QCoreApplication::quit();
    //qApp->quit();
    exit(0);
    #endif

    //QDialog::reject();
}

void loadPreviousSettings::unzipMCC(){
    auto lambda = [this](){mccInstallProgress->setLabelText(mccInstallProgressString+"\nUnzipping the MCC Runtime.");};
    QFuture<void> f = QtConcurrent::run(lambda);

    std::string unzipCmd;

    // Make the tmp dir if it doesn't exist
    QDir dir(QString::fromStdString(tmpDir));
    if (!dir.exists())
        dir.mkpath(".");

    #ifdef _WIN32
    unzipCmd = "tar -xf \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" -C \""+tmpDir+"\"";
    #elif __linux__
    // Linux and Mac can use unzip (Check if installed for Linux)
    if(!system("which unzip")) unzipCmd = "unzip -o -q "+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip -d "+tmpDir;
    else unzipCmd = "\""+QCoreApplication::applicationDirPath().toStdString()+"/7zzs\" x \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" -o \""+tmpDir+"\"";
    #else
    unzipCmd = "unzip -o -q \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" -d \""+tmpDir+"\"";
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
    auto lambda = [this](){mccInstallProgress->setLabelText(mccInstallProgressString+"\nDownloading the MCC Runtime.");};
    QFuture<void> f = QtConcurrent::run(lambda);

    std::string downloadCmd = "curl -o \""+QCoreApplication::applicationDirPath().toStdString()+"/matlabRuntime.zip\" ";
    #ifdef _WIN32
    downloadCmd.append("https://ssd.mathworks.com/supportfiles/downloads/R2024b/Release/5/deployment_files/installer/complete/win64/MATLAB_Runtime_R2024b_Update_5_win64.zip");
    #elif __linux__
    downloadCmd.append("https://ssd.mathworks.com/supportfiles/downloads/R2024b/Release/5/deployment_files/installer/complete/glnxa64/MATLAB_Runtime_R2024b_Update_5_glnxa64.zip");
    #else
    downloadCmd.append("https://ssd.mathworks.com/supportfiles/downloads/R2024b/Release/5/deployment_files/installer/complete/maci64/MATLAB_Runtime_R2024b_Update_5_maci64.dmg.zip");
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
                    return;
                }
                else if(userText == mccSL[1]){
                    ui->lpsUseMCCCheckBox->setChecked(false);
                    checkPath();
                    return;
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
    std::string chmodCmd = "chmod 777 -R "+homeCacheDir+"/matlabPath";

    // Make path if it does not exist
    QDir dir(QString::fromStdString(homeCacheDir)+"/matlabPath");
    if (!dir.exists())
        dir.mkpath(".");
    std::string matlabPathTxt = homeCacheDir+"/matlabPath/matlabPath.txt";

    if(ui->lpsUseMCCCheckBox->isChecked()){
        ui->lpsMatlabPathLineEdit->setText(QString(defaultMCCPath.c_str()));
        return 0;
    }
    #ifdef __linux__
    matlabCmd = "which matlab > "+matlabPathTxt;
    jobSuccess = !system(matlabCmd.c_str());
    system(chmodCmd.c_str());
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
    system(chmodCmd.c_str());
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

