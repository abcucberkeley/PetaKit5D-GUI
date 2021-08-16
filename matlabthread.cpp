#include "matlabthread.h"

matlabThread::matlabThread(QObject *parent, const std::string &funcType, const size_t &outA, const std::vector<matlab::data::Array> &data, std::tuple<std::string, std::string, bool> &mPathJNameParseCluster, const unsigned int &mThreadID) :
    QThread(parent), funcType(funcType), outA(outA), data(data), mPathJNameParseCluster(mPathJNameParseCluster), mThreadID(mThreadID)
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
    mOutThread = new matlabOutputThread(this, output, mPathJNameParseCluster, mThreadID);
    connect(this, &matlabThread::jobFinish, mOutThread, &matlabOutputThread::onJobFinish);
    mOutThread->start(QThread::NormalPriority);

    bool jobSuccess = true;
    try{
    if (funcType == "crop"){
        matlabPtr->feval(u"XR_crop_dataset",outA,data,output);
    }
    else if(funcType == "DeconOnly"){
        matlabPtr->feval(u"XR_decon_data_wrapper",outA,data,output);
    }
    else{
        matlabPtr->feval(u"XR_microscopeAutomaticProcessing",outA,data,output);
    }
    }
    catch(const matlab::engine::MATLABException& ex){
        jobSuccess = false;
        matlabPtr->feval(u"disp", 0, std::vector<matlab::data::Array>({factory.createScalar(ex.what())}));
    }

    // Close MATLAB session by deleting the unique pointer (Still testing)
    matlabPtr.reset();

    emit jobFinish(true);
    mOutThread->wait();

    if(jobSuccess) std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster) << "\" Finished" << std::endl;
    else{
        if(std::get<2>(mPathJNameParseCluster)) std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster) << "\" has Failed. MATLAB EXCEPTION." << std::endl;
        else std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster) << "\" has Failed. MATLAB EXCEPTION. Check job output file for details." << std::endl;
    }
}

