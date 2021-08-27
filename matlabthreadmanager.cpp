#include "matlabthreadmanager.h"
#include "mainwindow.h"




// Object that creates this thread is the parent
matlabThreadManager::matlabThreadManager(std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, QMutex &outputLock, QObject *parent) :
    QThread(parent), outputLock(&outputLock), jobLogPaths(&jobLogPaths)
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

    // When the job queue is not empty, we can create a new matlab thread for the job
    while(jobQueue.empty()){
        sleep(1);
    }

    // Create new matlab thread
    mThreads.emplace(mThreadID, new matlabThread(this, jobQueue.front().funcType, jobQueue.front().outA, jobQueue.front().data, jobQueue.front().mPathJNameParseCluster, mThreadID));

    outputLock->lock();
    std::cout << "Matlab Job \"" << std::get<1>(jobQueue.front().mPathJNameParseCluster).toStdString() << "\" Submitted" << std::endl;
    jobLogPaths->emplace(mThreadID,std::make_pair(std::get<0>(jobQueue.front().mPathJNameParseCluster),QDateTime::currentDateTime()));
    outputLock->unlock();

    mThreads[mThreadID]->start(QThread::TimeCriticalPriority);



    // Add path/button to Output Window
    //emit addOutputIDAndPath(mThreadID, mainPath);

    mThreadID++;
    jobQueueLock.lock();
    jobQueue.pop_front();
    jobQueueLock.unlock();

    emit enableSubmitButton();
    }

}

// Sets data and outA (given by the GUI signal) when a job is about to start. This will let the MATLAB thread instantly start that job.
void matlabThreadManager::onJobStart(const matlabJobSettings &newJob){
    std::cout << "Starting job" << std::endl;
    jobQueueLock.lock();
    jobQueue.push_back(newJob);
    jobQueueLock.unlock();
}

