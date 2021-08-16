#include "matlaboutputwindowthread.h"
#include <iostream>


matlabOutputWindowThread::matlabOutputWindowThread(std::unordered_map<int,std::pair<std::string,QDateTime>> &jobLogPaths, QObject *parent) :
    QThread(parent)
{
    this->jobLogPaths = &jobLogPaths;
}

void matlabOutputWindowThread::run(){
    fNameMapMap fNames;
    std::unordered_map<std::string,std::string> existingPaths;
    while(true){
        sleep(3);
        for(auto &path : *jobLogPaths){
            fileNamesLock.lock();
            fNames.emplace(path.first,std::map<std::string,std::string>());
            QDirIterator it(QString::fromStdString(path.second.first),{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()){
                QString nFile = it.next();
                if(existingPaths.find(nFile.toStdString()) != existingPaths.end()) continue;

                if(QFileInfo(nFile).birthTime().isValid()){
                    if(path.second.second < QFileInfo(nFile).birthTime()){
                        fNames.at(path.first).emplace(nFile.toStdString(),nFile.toStdString());
                        existingPaths.emplace(nFile.toStdString(),nFile.toStdString());
                    }
                }
                else{
                    if(path.second.second < QFileInfo(nFile).lastModified()){
                        fNames.at(path.first).emplace(nFile.toStdString(),nFile.toStdString());
                        existingPaths.emplace(nFile.toStdString(),nFile.toStdString());
                    }
                }
            }
            fileNamesLock.unlock();
        }
        emit updateOutputForm(&fNames,&fileNamesLock);
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath){
    //jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}

