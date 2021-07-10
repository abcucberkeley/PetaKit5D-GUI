#include "matlabthreadmanager.h"
#include "mainwindow.h"




// Object that creates this thread is the parent
matlabThreadManager::matlabThreadManager(QObject *parent) :
    QThread(parent), outA(1)
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
    std::cout << "Ready for new job!" << std::endl;

    // Once outA is set to 0, we can create a new matlab thread for the job
    while(outA){
        sleep(1);
    }

    // Create new matlab thread
    mThreads.emplace(mThreadID, new matlabThread(this, funcType, outA, data, mainPath, mThreadID));
    mThreads.at(mThreadID)->start(QThread::TimeCriticalPriority);
    std::cout << "Matlab Job " << mThreadID << " Submitted" << std::endl;

    // Add path/button to Output Window
    emit addOutputIDAndPath(mThreadID, mainPath);

    mThreadID++;
    outA = 1;
    data.clear();
    emit enableSubmitButton();
    }

}

// Sets data and outA (given by the GUI signal) when a job is about to start. This will let the MATLAB thread instantly start that job.
void matlabThreadManager::onJobStart(size_t &outA, std::vector<matlab::data::Array> &data, std::string &funcType, std::string &mainPath){
    std::cout << "Starting job" << std::endl;
    this->data = std::move(data);
    this->funcType = std::move(funcType);
    this->mainPath = std::move(mainPath);
    this->outA = std::move(outA);
}

