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
        std::unordered_map<int,std::unordered_map<std::string,std::string>> fNames;
        for(auto &path : *jobLogPaths){
            QDirIterator it(QString::fromStdString(path.second),{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()) std::cout << it.next().toStdString() << std::endl;
        }
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath){
    //jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}

