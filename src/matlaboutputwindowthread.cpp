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
        sleep(3);
        for(auto &path : *jobLogPaths){
            fileNamesLock.lock();
            fNames.emplace(path.first,std::map<QString,QString>());
            QDirIterator it(path.second.first,{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()){
                QString nFile = it.next();
                if(existingPaths.find(nFile) != existingPaths.end()) continue;

                if(QFileInfo(nFile).birthTime().isValid()){
                    if(path.second.second < QFileInfo(nFile).birthTime()){
                        fNames[path.first].emplace(nFile,nFile);
                        existingPaths.emplace(nFile,nFile);
                    }
                }
                else{
                    if(path.second.second < QFileInfo(nFile).lastModified()){
                        fNames[path.first].emplace(nFile,nFile);
                        existingPaths.emplace(nFile,nFile);
                    }
                }
            }
            fileNamesLock.unlock();
        }
        emit updateOutputForm(&fNames,&fileNamesLock);
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const QString mainPath){
    //jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}

