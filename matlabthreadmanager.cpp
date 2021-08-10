#include "matlabthreadmanager.h"
#include "mainwindow.h"




// Object that creates this thread is the parent
matlabThreadManager::matlabThreadManager(QMutex &outputLock, QObject *parent) :
    QThread(parent), outputLock(&outputLock), jobLogPaths(nullptr), outA(1)
{

}

matlabThreadManager::~matlabThreadManager(){

    // Terminate all unfinished threads
    for(auto &thread : mThreads){
        if(!thread.second->isFinished()) thread.second->terminate();
    }
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
        sleep(1);
    }

    // Create new matlab thread
    mThreads.emplace(mThreadID, new matlabThread(this, funcType, outA, data, mainPath, mThreadID));
    mThreads.at(mThreadID)->start(QThread::TimeCriticalPriority);

    outputLock->lock();
    std::cout << "Matlab Job " << mThreadID << " Submitted" << std::endl;
    jobLogPaths->emplace(mThreadID,mainPath);
    outputLock->unlock();

    // Add path/button to Output Window
    //emit addOutputIDAndPath(mThreadID, mainPath);

    mThreadID++;
    outA = 1;
    data.clear();
    emit enableSubmitButton();
    }

}

// Sets data and outA (given by the GUI signal) when a job is about to start. This will let the MATLAB thread instantly start that job.
void matlabThreadManager::onJobStart(size_t &outA, std::vector<matlab::data::Array> &data, std::string &funcType, std::string &mainPath,std::unordered_map<int,std::string> &jobLogPaths){
    std::cout << "Starting job" << std::endl;
    this->data = std::move(data);
    this->funcType = std::move(funcType);
    this->mainPath = std::move(mainPath);
    if(!this->jobLogPaths) this->jobLogPaths = &jobLogPaths;
    this->outA = std::move(outA);
}

