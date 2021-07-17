#include "matlabthread.h"

matlabThread::matlabThread(QObject *parent, const std::string &funcType, const size_t &outA, const std::vector<matlab::data::Array> &data, const std::string &mainPath, const unsigned int &mThreadID) :
    QThread(parent), funcType(funcType), outA(outA), data(data), mainPath(mainPath), mThreadID(mThreadID)
{

}

matlabThread::~matlabThread(){
    if(!mOutThread->isFinished()) mOutThread->terminate();
}

void matlabThread::run(){
    // Start matlab and add needed paths
    matlabPtr = startMATLAB();

    // Check if Windows or Cluster then add Repo to the path
    if(QSysInfo::productType().contains("win",Qt::CaseInsensitive)){
        matlab::data::CharArray newDir = factory.createCharArray(QCoreApplication::applicationDirPath().toStdString()+"/XR_Repository");
        matlabPtr->feval(u"cd",newDir);
        matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
        matlabPtr->feval(u"addpath",newGen);
    }
    else{
        matlab::data::CharArray newDir = factory.createCharArray("/clusterfs/fiona/ABCcode/XR_Repository");
        matlabPtr->feval(u"cd",newDir);
        matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
        matlabPtr->feval(u"addpath",newGen);
    }

    //TESTING
    //std::vector<matlab::data::Array> setup;
    //setup.push_back(factory.createStructArray({0,0},{}));
    //setup.push_back(factory.createScalar<bool>(true));
    //matlabPtr->feval(u"setup",([],true));

    // Create string buffer for standard output
    std::shared_ptr<StringBuf> output = std::make_shared<StringBuf>();
    mOutThread = new matlabOutputThread(this, output, mainPath,mThreadID);
    connect(this, &matlabThread::jobFinish, mOutThread, &matlabOutputThread::onJobFinish);
    mOutThread->start(QThread::NormalPriority);

    if (funcType == "crop"){
        matlabPtr->feval(u"XR_crop_dataset",outA,data,output);
    }
    else if(funcType == "DeconOnly"){
        matlabPtr->feval(u"XR_decon_data_wrapper",outA,data,output);
    }
    else{
        matlabPtr->feval(u"XR_microscopeAutomaticProcessing",outA,data,output);
    }

    // Close MATLAB session by deleting the unique pointer (Still testing)
    matlabPtr.reset();

    emit jobFinish(true);
    mOutThread->wait();


    std::cout << "Matlab Job " << mThreadID << " Finished" << std::endl;
}

