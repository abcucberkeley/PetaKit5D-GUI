#include "matlabthread.h"

matlabThread::matlabThread(QObject *parent, const std::string &funcType, const size_t &outA, const std::vector<matlab::data::Array> &data, const unsigned int &mThreadID) :
    QThread(parent), funcType(funcType), outA(outA), data(data), mThreadID(mThreadID)
{

}

matlabThread::~matlabThread(){

}

void matlabThread::run(){
    // Start matlab and add needed paths
    matlabPtr = startMATLAB();

    // TODO: Check if cluster
    //matlab::data::CharArray newDir = factory.createCharArray(QCoreApplication::applicationDirPath().toStdString()+"/XR_Repository");
    matlab::data::CharArray newDir = factory.createCharArray("/clusterfs/fiona/ABCcode/XR_Repository");

    matlabPtr->feval(u"cd",newDir);
    matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
    matlabPtr->feval(u"addpath",newGen);

    //TESTING
    //std::vector<matlab::data::Array> setup;
    //setup.push_back(factory.createStructArray({0,0},{}));
    //setup.push_back(factory.createScalar<bool>(true));
    //matlabPtr->feval(u"setup",([],true));

    if(funcType == "DeconOnly"){
        matlabPtr->feval(u"XR_decon_data_wrapper",outA,data);
    }
    else{
        matlabPtr->feval(u"XR_microscopeAutomaticProcessing",outA,data);
    }
    std::cout << "Matlab Job " << mThreadID << " Finished" << std::endl;
}

