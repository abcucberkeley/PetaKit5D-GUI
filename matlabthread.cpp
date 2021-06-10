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
    
    // Check if cluster TESTING
    //matlab::data::CharArray newDir = factory.createCharArray(QCoreApplication::applicationDirPath().toStdString()+"/XR_Repository");
    matlab::data::CharArray newDir = factory.createCharArray("/clusterfs/fiona/ABCcode/XR_Repository");
    
    matlabPtr->feval(u"cd",newDir);
    matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
    matlabPtr->feval(u"addpath",newGen);

    //TESTING
    std::vector<matlab::data::Array> setup;
    setup.push_back(factory.createStructArray({0,0},{}));
    setup.push_back(factory.createScalar<bool>(true));
    
    //matlabPtr->feval(u"setup",([],true));
    while(true){
    std::cout << "Ready for new job" << std::endl;

    // Once outA is set to 0, we can start our matlab job
    while(outA){
        sleep(1);
    }

    // Start Matlab Job

    if(funcType == "DeconOnly"){
        matlabPtr->feval(u"XR_decon_data_wrapper",outA,data);
    }
    else{
        matlabPtr->feval(u"XR_microscopeAutomaticProcessing",outA,data);
    }
    outA = 1;
    data.clear();
    emit enableSubmitButton();
    }

}

// Sets data and outA (given by the GUI signal) when a job is about to start. This will let the MATLAB thread instantly start that job.
void matlabThread::onJobStart(const size_t outA, const std::vector<matlab::data::Array> &data, const std::string funcType){
    std::cout << "Starting job" << std::endl;
    this->data = data;
    this->funcType = funcType;
    this->outA = outA;
}

