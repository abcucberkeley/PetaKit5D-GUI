#include "matlabthreadmanager.h"
#include "matlabthread.h"
#include <iostream>

// Object that creates this thread is the parent
matlabThreadManager::matlabThreadManager(QMutex &outputLock, QObject *parent) :
    QThread(parent), outputLock(&outputLock), jobLogPaths(nullptr), outA(1), killThread(0)
{
    _stdout = std::cout.rdbuf(jobsOutput.rdbuf());
    _stderr = std::cerr.rdbuf(jobsOutput.rdbuf());
    // Start IDs at 1
    mThreadID = 1;
}

matlabThreadManager::~matlabThreadManager(){

    // Terminate all unfinished threads
    for(auto &thread : mThreads){
        if(!thread.second->isFinished()) {
            //thread.second->terminate();
            thread.second->killMatlabThread();
            thread.second->wait();
        }
    }
    killThread = 1;
    std::cout.rdbuf(_stdout);
    std::cerr.rdbuf(jobsOutput.rdbuf());
    fflush(stdout);
    fflush(stderr);
    this->wait();
}

void matlabThreadManager::killMatlabThreadManager(){
    killThread = 1;
}

void matlabThreadManager::run(){
    
    while(true){

    // Once outA is set to 0, we can create a new matlab thread for the job
    while(outA){
        if(killThread) return;
        sleep(1);
    }

    // Create new matlab thread
    mThreads.emplace(mThreadID, new matlabThread(this, funcType, outA, args, mPathJNameParseCluster, mThreadID, isMcc, pathToMatlab));
    outputLock->lock();
    std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" Submitted" << std::endl;
    std::cout << "Ready for new job!" << std::endl;
    jobLogPaths->emplace(mThreadID,std::make_pair(std::get<0>(mPathJNameParseCluster),QDateTime::currentDateTime()));
    outputLock->unlock();
    mThreads[mThreadID]->start(QThread::TimeCriticalPriority);
    // Add path/button to Output Window
    //emit addOutputIDAndPath(mThreadID, mainPath);

    // This is how we continously redirect output from the threads to the QDockWidget
    outputLock->lock();
    connect(mThreads[mThreadID], &matlabThread::availableQProcessOutput, this, &matlabThreadManager::availableQProcessOutput);
    outputLock->unlock();
    mThreadID++;
    outA = 1;
    
    emit data(jobsOutput.str());
    jobsOutput.str(std::string()); // This is to reset the buffer. So we just keep track of the current job being read.
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