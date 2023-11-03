#include "matlaboutputwindowthread.h"
#include <iostream>


matlabOutputWindowThread::matlabOutputWindowThread(std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, QObject *parent) :
    QThread(parent), killThread(0)
{
    this->jobLogPaths = &jobLogPaths;
}

matlabOutputWindowThread::~matlabOutputWindowThread(){
    killThread = 1;
    this->wait();
}

void matlabOutputWindowThread::run(){
    fNameMapMap fNames;
    std::unordered_map<QString,QString> existingPaths;
    while(true){
        if(killThread) return;
        sleep(2);
        for(auto &path : *jobLogPaths){
            fileNamesLock.lock();
            fNames.emplace(path.first,std::map<QString,QString>());
            QDirIterator it(path.second.first,{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()){
                QString nFile = it.next();
                if(existingPaths.find(nFile) != existingPaths.end()) continue;

                // offset time by a minutes in case the time is the same
                QDateTime timeOffset = path.second.second;
                timeOffset = timeOffset.addSecs(-60);

                if(QFileInfo(nFile).birthTime().isValid()){
                    if(timeOffset <= QFileInfo(nFile).birthTime()){
                        fNames[path.first].emplace(nFile,nFile);
                        existingPaths.emplace(nFile,nFile);
                        emit updateOutputForm(&fNames,&fileNamesLock);
                    }
                }
                else{
                    if(timeOffset <= QFileInfo(nFile).lastModified()){
                        fNames[path.first].emplace(nFile,nFile);
                        existingPaths.emplace(nFile,nFile);
                        emit updateOutputForm(&fNames,&fileNamesLock);
                    }
                }
            }
            fileNamesLock.unlock();
        }
    }
}

/*
void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const QString mainPath){
    jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}
*/
