#include "matlaboutputwindowthread.h"
#include <iostream>


matlabOutputWindowThread::matlabOutputWindowThread(std::unordered_map<int,std::string> &jobLogPaths, QObject *parent) :
    QThread(parent)
{
    this->jobLogPaths = &jobLogPaths;
}

void matlabOutputWindowThread::run(){
    fNameMapMap fNames;
    while(true){
        sleep(5);
        for(auto &path : *jobLogPaths){
            fileNamesLock.lock();
            fNames.emplace(path.first,std::map<std::string,std::string>());
            QDirIterator it(QString::fromStdString(path.second),{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()){
                std::string nFile = it.next().toStdString();
                fNames.at(path.first).emplace(nFile,nFile);
            }
            fileNamesLock.unlock();
        }
        emit updateOutputForm(&fNames,&fileNamesLock);
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath){
    //jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}

