#ifndef SUBMISSIONCHECKS_H
#define SUBMISSIONCHECKS_H
#include "mainwindow.h"
#include <QString>
#include <QDir>

template <typename T>
void checkJobLogDir(T &submissionVals, QString &mainPath, const QString &timeJobName){
    // Check for job log directory for main job
    QDir dir(submissionVals.jobLogDir);
    if (!dir.exists()){
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
        submissionVals.jobLogDir = mainPath;
        std::cout << "Chosen job log directory does not exist! Using " << submissionVals.jobLogDir.toStdString()<< " as the job log directory instead." << std::endl;
    }
    else{
        mainPath = submissionVals.jobLogDir+"/"+timeJobName;
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
    }
}

void messageBoxError(QString errorText);

#endif // SUBMISSIONCHECKS_H
