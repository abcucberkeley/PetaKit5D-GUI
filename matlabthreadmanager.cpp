#include "matlabthreadmanager.h"
#include "matlabthread.h"
#include <iostream>




// Object that creates this thread is the parent
matlabThreadManager::matlabThreadManager(QMutex &outputLock, QObject *parent) :
    QThread(parent), outputLock(&outputLock), jobLogPaths(nullptr), outA(1), killThread(0)
{

}

matlabThreadManager::~matlabThreadManager(){

    // Terminate all unfinished threads
    for(auto &thread : mThreads){
        if(!thread.second->isFinished()) thread.second->terminate();
    }
    killThread = 1;
    this->wait();
}

void matlabThreadManager::run(){

    // Start IDs at 1
    unsigned int mThreadID = 1;
    while(true){
    outputLock->lock();
    std::cout << "Ready for new job!" << std::endl;
    outputLock->unlock();

    // Once outA is set to 0, we can create a new matlab thread for the job
    while(outA){
        if(killThread) return;
        sleep(1);
    }

    // Create new matlab thread
    mThreads.emplace(mThreadID, new matlabThread(this, funcType, outA, args, mPathJNameParseCluster, mThreadID, isMcc, pathToMatlab));

    outputLock->lock();
    std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" Submitted" << std::endl;
    jobLogPaths->emplace(mThreadID,std::make_pair(std::get<0>(mPathJNameParseCluster),QDateTime::currentDateTime()));
    outputLock->unlock();

    mThreads[mThreadID]->start(QThread::TimeCriticalPriority);



    // Add path/button to Output Window
    //emit addOutputIDAndPath(mThreadID, mainPath);

    mThreadID++;
    outA = 1;
    //data.clear();
    emit enableSubmitButton();
    }

}

// Sets data and outA (given by the GUI signal) when a job is about to start. This will let the MATLAB thread instantly start that job.
void matlabThreadManager::onJobStart(std::string &args, QString &funcType, std::tuple<QString, QString, bool> &mPathJNameParseCluster, std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, bool isMcc, const std::string &pathToMatlab){
    std::cout << "Starting job" << std::endl;
    this->args = std::move(args);
    this->funcType = std::move(funcType);
    this->mPathJNameParseCluster = std::move(mPathJNameParseCluster);
    if(!this->jobLogPaths) this->jobLogPaths = &jobLogPaths;
    this->outA = 0;
    this->isMcc = isMcc;
    this->pathToMatlab = pathToMatlab;
}

