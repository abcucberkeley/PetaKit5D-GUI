#ifndef SUBMISSIONCHECKS_H
#define SUBMISSIONCHECKS_H
#include "mainwindow.h"
#include <QString>
#include <QDir>
#include <QFileDevice>
#include <QCheckBox>
#include <QLineEdit>
#include <iostream>


template <typename T>
void checkJobLogDir(T &submissionVals, QString &mainPath, const QString &timeJobName){
    // Check for job log directory for main job
    QDir dir(submissionVals.jobLogDir);
    if (!dir.exists()){
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
        QFile setP(mainPath);
        setP.setPermissions({QFileDevice::Permission::ReadUser,QFileDevice::Permission::WriteUser,QFileDevice::Permission::ExeUser,QFileDevice::Permission::ReadGroup,QFileDevice::Permission::WriteGroup,QFileDevice::Permission::ExeGroup,QFileDevice::Permission::ReadOther,QFileDevice::Permission::ExeOther});
        submissionVals.jobLogDir = mainPath;
        std::cout << "Chosen job log directory does not exist! Using " << submissionVals.jobLogDir.toStdString()<< " as the job log directory instead." << std::endl;
    }
    else{
        mainPath = submissionVals.jobLogDir+"/"+timeJobName;
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
        QFile setP(mainPath);
        setP.setPermissions({QFileDevice::Permission::ReadUser,QFileDevice::Permission::WriteUser,QFileDevice::Permission::ExeUser,QFileDevice::Permission::ReadGroup,QFileDevice::Permission::WriteGroup,QFileDevice::Permission::ExeGroup,QFileDevice::Permission::ReadOther,QFileDevice::Permission::ExeOther});
        submissionVals.jobLogDir = mainPath;
    }
}

void messageBoxError(const QString &errorText);

void messageBoxSuccess(QWidget* parent, const QString &successText);

bool dataPathsAreSet(const std::vector<dataPath> &dPaths);

bool channelPatternsAreSet(const std::vector<std::pair<QLabel*,QCheckBox*>> &channelWidgets, const QCheckBox* customPatternsCheckBox, const QLineEdit* customPatternsLineEdit);

#endif // SUBMISSIONCHECKS_H
