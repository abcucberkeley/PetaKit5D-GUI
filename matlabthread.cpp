#include "matlabthread.h"
#include "mainwindow.h"


// Object that creates this thread is the parent
matlabThread::matlabThread(QObject *parent) :
    QThread(parent), outA(1)
{

}

matlabThread::~matlabThread(){

}

void matlabThread::run(){
    //std::vector<std::string> options;
    matlabPtr = startMATLAB();
    matlab::data::CharArray newDir = factory.createCharArray("C:/Users/Matt/Documents/GitHub/XR_Repository");
    matlabPtr->feval(u"cd",newDir);
    matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
    matlabPtr->feval(u"addpath",newGen);
    //isInterruptionRequested()
    qDebug() << "MATLAB READY";

    // Once outA is set to 0, we can start our matlab job
    while(outA){
        sleep(1);
        //if(isInterruptionRequested()){
            //break;
        //}
    }
    qDebug() << this->outA;

    // Start Matlab Job
    matlabPtr->feval(u"XR_microscopeAutomaticProcessing",outA,data);

}

void matlabThread::onJobStart(const size_t outA, const std::vector<matlab::data::Array> &data){
    qDebug() << "main job";
    this->outA = outA;
    this->data = data;
    qDebug() << this->outA;
}
