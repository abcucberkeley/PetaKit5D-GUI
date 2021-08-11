#include "matlaboutputwindowthread.h"
#include <iostream>

matlabOutputWindowThread::matlabOutputWindowThread(std::unordered_map<int,std::string> &jobLogPaths, QObject *parent) :
    QThread(parent)
{
    this->jobLogPaths = &jobLogPaths;
}

void matlabOutputWindowThread::run(){
    while(true){
        sleep(5);
        std::map<int,std::map<std::string,std::string>> fNames;
        for(auto &path : *jobLogPaths){
            fNames.emplace(path.first,std::map<std::string,std::string>());
            QDirIterator it(QString::fromStdString(path.second),{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()) fNames.at(path.first).emplace(it.next().toStdString(),it.next().toStdString());
        }
        std::string test = "testing";
        emit updateOutputForm();
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath){
    //jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}

