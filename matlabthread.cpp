#include "matlabthread.h"
#include "mainwindow.h"


// Object that creates this thread is the parent
matlabThread::matlabThread(QObject *parent) :
    QThread(parent), outA(1)
{
    //connect(this, &matlabThread::enableSubmitButton, parent, &MainWindow::onEnableSubmitButton);
}

matlabThread::~matlabThread(){

}

void matlabThread::run(){
    // Start matlab and add needed paths
    matlabPtr = startMATLAB();
    //matlab::data::CharArray newDir = factory.createCharArray(QDir::currentPath().toStdString()+"/XR_Repository");
    matlab::data::CharArray newDir = factory.createCharArray(QCoreApplication::applicationDirPath().toStdString()+"/XR_Repository");
    matlabPtr->feval(u"cd",newDir);
    matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
    matlabPtr->feval(u"addpath",newGen);
    while(true){
    std::cout << "Ready for new job" << std::endl;

    // Once outA is set to 0, we can start our matlab job
    while(outA){
        sleep(1);
    }

    // Start Matlab Job
    matlabPtr->feval(u"XR_microscopeAutomaticProcessing",outA,data);

    outA = 1;
    data.clear();
    emit enableSubmitButton();
    }

}

// Sets data and outA (given by the GUI signal) when a job is about to start. This will let the MATLAB thread instantly start that job.
void matlabThread::onJobStart(const size_t outA, const std::vector<matlab::data::Array> &data){
    std::cout << "Starting job" << std::endl;
    this->data = data;
    this->outA = outA;
}

