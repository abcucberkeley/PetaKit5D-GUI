#include "submissionchecks.h"

void checkJobLogDir(QString &jobLogDir, QString &mainPath, const QString &timeJobName){
    // Check for job log directory for main job
    QDir dir(jobLogDir);
    if (!dir.exists()){
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
        QFile setP(mainPath);
        setP.setPermissions({QFileDevice::Permission::ReadUser,QFileDevice::Permission::WriteUser,QFileDevice::Permission::ExeUser,QFileDevice::Permission::ReadGroup,QFileDevice::Permission::WriteGroup,QFileDevice::Permission::ExeGroup,QFileDevice::Permission::ReadOther,QFileDevice::Permission::ExeOther});
        jobLogDir = mainPath;
        std::cout << "Chosen job log directory does not exist! Using " << jobLogDir.toStdString()<< " as the job log directory instead." << std::endl;
    }
    else{
        mainPath = jobLogDir+"/"+timeJobName;
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
        QFile setP(mainPath);
        setP.setPermissions({QFileDevice::Permission::ReadUser,QFileDevice::Permission::WriteUser,QFileDevice::Permission::ExeUser,QFileDevice::Permission::ReadGroup,QFileDevice::Permission::WriteGroup,QFileDevice::Permission::ExeGroup,QFileDevice::Permission::ReadOther,QFileDevice::Permission::ExeOther});
        jobLogDir = mainPath;
    }
}

void messageBoxError(const QString &errorText){
    QMessageBox messageBox;
    messageBox.warning(0,"Error",errorText);
    messageBox.setFixedSize(500,200);
    return;
}

void messageBoxSuccess(QWidget* parent, const QString &successText){
    QMessageBox messageBox(parent);
    messageBox.information(0,"Success",successText);
    messageBox.setFixedSize(500,200);
    return;
}

bool usingDefaultConfigFile(const configFileVals &cFileVals){
    QString defaultString = "_default_config";
    if (cFileVals.configFile.contains(defaultString) ||
        cFileVals.gpuConfigFile.contains(defaultString) ||
        cFileVals.jvmConfigFile.contains(defaultString)){
        return true;
    }
    return false;
}

bool messageBoxParseClusterWarning(QWidget* parent, const bool parseCluster, bool &enabled, const configFileVals &cFileVals){
    if(!(enabled && parseCluster && usingDefaultConfigFile(cFileVals))) return true;

    QMessageBox messageBox(parent);
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setWindowTitle("Warning");
    messageBox.setText("It looks like you are trying to use a cluster but you may be using one of the default config files. "
                       "You should create your own config files for cluster jobs. "
                       "You can do so inside the Config File Settings in the Main Advanced Settings."
                       "For more infomation about creating a config files and creating them, please visit this wiki page: "
                       "<a href='https://github.com/abcucberkeley/PetaKit5D-GUI/wiki/3.-Main-Settings#3-config-file-settings-located-in-main-advanced-settings'>Config File Settings</a>");
    messageBox.setFixedSize(600,400);
    messageBox.addButton("I Understand, Continue Anyway", QMessageBox::AcceptRole);
    QAbstractButton* cancelButton = messageBox.addButton("Cancel Job", QMessageBox::RejectRole);
    QCheckBox* checkBox = new QCheckBox("Do not ask me again");
    messageBox.setCheckBox(checkBox);
    messageBox.exec();

    if(checkBox->isChecked()){
        enabled = false;
    }

    if(messageBox.clickedButton() == cancelButton){
        return false;
    }
    return true;
}

bool messageBoxSameJobSubmittedWarning(QWidget* parent,
                                       std::pair<std::string,std::string> &prevFuncTypeArgs,
                                       const std::string &funcType, const std::string &args, bool &enabled){
    if(!enabled || prevFuncTypeArgs.first != funcType || prevFuncTypeArgs.second != args){
        prevFuncTypeArgs.first = funcType;
        prevFuncTypeArgs.second = args;
        return true;
    }

    QMessageBox messageBox(parent);
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setWindowTitle("Warning");
    messageBox.setText("It looks the job you are submitting is exactly the same as the last job submitted. "
                       "Are you sure you want to submit it again?");
    messageBox.setFixedSize(600,400);
    messageBox.addButton("I Understand, Continue Anyway", QMessageBox::AcceptRole);
    QAbstractButton* cancelButton = messageBox.addButton("Cancel Job", QMessageBox::RejectRole);
    QCheckBox* checkBox = new QCheckBox("Do not ask me again");
    messageBox.setCheckBox(checkBox);
    messageBox.exec();

    if(checkBox->isChecked()){
        enabled = false;
    }

    if(messageBox.clickedButton() == cancelButton){
        ((MainWindow*)parent)->onEnableSubmitButton();
        return false;
    }
    return true;
}

bool dataPathsAreSet(const std::vector<dataPath> &dPaths){
    if(!dPaths.size()){
        messageBoxError("No data paths are set. Please set at least one data path before continuing.");
        return false;
    }
    return true;
}

bool channelPatternsAreSet(const std::vector<std::pair<QLabel*,QCheckBox*>> &channelWidgets, const QCheckBox* customPatternsCheckBox, const QLineEdit* customPatternsLineEdit){
    if(!channelWidgets.size() && (!customPatternsCheckBox->isChecked() || customPatternsLineEdit->text().isEmpty())){
        messageBoxError("No channel patterns set. Please set at least one pattern before continuing.");
        return false;
    }
    for(size_t i = 0; i < channelWidgets.size(); i++){
        if(channelWidgets[i].second->isChecked()) break;
        if(i == channelWidgets.size()-1 && (!customPatternsCheckBox->isChecked() || customPatternsLineEdit->text().isEmpty())){
            messageBoxError("No channel patterns set. Please set at least one pattern before continuing.");
            return false;
        }
    }
    return true;
}

void onlyRotateCheckboxIsChecked(){
    messageBoxError("Currently a Rotate cannot be performed by only checking the Rotate checkbox. "
                    "You can perform a rotation only job by unchecking the Rotate checkbox, "
                    "checking the Deskew & Rotate checkbox as true, "
                    "and checking Objective Scan checkbox as true. Keep in mind you will also have to change your Step "
                    "Size accordingly.");
    return;
}

bool pathsFound(dataPath& path){
    if(path.includeMaster){
        if(!QFileInfo::exists(path.masterPath)){
            messageBoxError("Data path \"" + path.masterPath + "\" does not exist!");
            return false;
        }
    }
    for (const auto &subPath : path.subPaths){
        if(subPath.second.first){
            if(!QFileInfo::exists(subPath.second.second)){
                messageBoxError("Data path \"" + subPath.second.second + "\" does not exist!");
                return false;
            }
        }
    }
    
    return true;
}

bool settingsFileExists(){
    QSettings settings("ABC", "PetaKit5D-GUI");
    #ifndef _WIN32
    return QFile::exists(settings.fileName());
    #else
    settings.beginGroup("MainWindow");
    QStringList keys = settings.allKeys();
    settings.endGroup();
    return !keys.isEmpty();
    #endif
}
