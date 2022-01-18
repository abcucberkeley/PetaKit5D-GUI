#include "matlabthread.h"

matlabThread::matlabThread(QObject *parent, const QString &funcType, const size_t &outA, const std::vector<matlab::data::Array> &data, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID) :
    QThread(parent), mOutThread(nullptr), funcType(funcType), outA(outA), data(data), mPathJNameParseCluster(mPathJNameParseCluster), mThreadID(mThreadID)
{

}

matlabThread::~matlabThread(){
    if(mOutThread){
        if(!mOutThread->isFinished()) {
            mOutThread->terminate();
        }
    }
}

void matlabThread::run(){
    // Start matlab and add needed paths
    bool jobSuccess = true;

    // Try catch for matlab errors
    try{
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
    std::vector<matlab::data::Array> setup;
    //size_t empty = 0;
    setup.push_back(factory.createEmptyArray());
    setup.push_back(factory.createScalar<bool>(true));
    //matlabPtr->feval(u"setup",factory.createArray<double>({0,0},{}),factory.createScalar<bool>(true));
    matlabPtr->feval(u"setup",0,setup);

    // Create string buffer for standard output
    std::shared_ptr<StringBuf> output = std::make_shared<StringBuf>();
    mOutThread = new matlabOutputThread(this, output, mPathJNameParseCluster, mThreadID);
    connect(this, &matlabThread::jobFinish, mOutThread, &matlabOutputThread::onJobFinish);
    mOutThread->start(QThread::NormalPriority);



    if (funcType == "crop"){
        matlabPtr->feval(u"XR_crop_dataset",outA,data,output);
    }
    else if(funcType == "DeconOnly"){
        matlabPtr->feval(u"XR_decon_data_wrapper",outA,data,output);
    }
    else if(funcType == "simRecon"){
        matlabPtr->feval(u"simReconAutomaticProcessing",outA,data,output);
    }
    else if(funcType == "parallelRsync"){
        matlabPtr->feval(u"XR_parallel_rsync_wrapper",outA,data,output);
    }
    else if(funcType == "fftAnalysis"){
        matlabPtr->feval(u"XR_fftSpectrumComputingWrapper",outA,data,output);
    }
    else if(funcType == "fscAnalysis"){
        matlabPtr->feval(u"XR_FSC_analysis_wrapper",outA,data,output);
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

    if(mOutThread){
        emit jobFinish(true);
        mOutThread->wait();
    }

    if(jobSuccess) std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" Finished" << std::endl;
    else{
        //if(std::get<2>(mPathJNameParseCluster))
        std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION." << std::endl;
        //else std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION. Check job output file for details." << std::endl;
    }
}

