#include "matlaboutputwindowthread.h"
#include <iostream>


matlabOutputWindowThread::matlabOutputWindowThread(std::unordered_map<int,std::string> &jobLogPaths, QObject *parent) :
    QThread(parent)
{
    this->jobLogPaths = &jobLogPaths;
}

void matlabOutputWindowThread::run(){
    //Q_DECLARE_METATYPE(std::map);
    //qRegisterMetaType<fNameMapMap>();
    fNameMapMap fNames;
    while(true){
        sleep(5);
        //QMap<int,QMap<QString,QString>> fNames;
        //std::map<int,std::map<std::string,std::string>> fNames;
        //fNames.clear();
        for(auto &path : *jobLogPaths){
            fileNamesLock.lock();
            fNames.emplace(path.first,std::map<std::string,std::string>());
            //fNames.insert(path.first,QMap<QString,QString>());
            QDirIterator it(QString::fromStdString(path.second),{QDir::NoDotAndDotDot,QDir::Files});
            while(it.hasNext()){
                std::string nFile = it.next().toStdString();
                fNames.at(path.first).emplace(nFile,nFile);
            }
            //while(it.hasNext()) fNames[path.first].insert(it.next(),it.next());
            fileNamesLock.unlock();
        }
        QString test = "testing";
        emit updateOutputForm(&fNames,&fileNamesLock);
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath){
    //jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}

