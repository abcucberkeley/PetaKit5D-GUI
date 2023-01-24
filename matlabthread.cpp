#include <iostream>
#include <stdlib.h>
#include "matlabthread.h"

matlabThread::matlabThread(QObject *parent, const QString &funcType, const size_t &outA, const std::string &args, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID, bool isMcc, const std::string &pathToMatlab) :
    QThread(parent), funcType(funcType), outA(outA), args(args), mPathJNameParseCluster(mPathJNameParseCluster), mThreadID(mThreadID), isMcc(isMcc), pathToMatlab(pathToMatlab)
{

}

matlabThread::~matlabThread(){
    /*
    if(mOutThread){
        if(!mOutThread->isFinished()) {
            mOutThread->terminate();
        }
    }
    */
}

void matlabThread::run(){
    // Start matlab and add needed paths
    bool jobSuccess = true;

    // Try catch for matlab errors
    //try{
    std::string matlabCmd;

    // If the user has a matlab installation
    if(!isMcc){
        std::string matlabOptions = "-batch";

        matlabCmd.append("\""+pathToMatlab+"\" "+matlabOptions);
        //matlab -batch "cd('/clusterfs/nvme/matthewmueller/clusterBenchmarking');clusterBenchmarking;exit;"
        //matlabPtr = startMATLAB();

        // Add the LLSM3DTools Repository to the path
        std::string newDir = QCoreApplication::applicationDirPath().toStdString()+"/LLSM3DTools";
        matlabCmd.append(" \"cd(\'"+newDir+"\');");
        matlabCmd.append("addpath(genpath(\'"+newDir+"\'));");
        //matlab::data::CharArray newDir = factory.createCharArray(QCoreApplication::applicationDirPath().toStdString()+"/LLSM3DTools");
        //matlabPtr->feval(u"cd",newDir);
        //matlab::data::CharArray newGen = matlabPtr->feval(u"genpath",newDir);
        //matlabPtr->feval(u"addpath",newGen);

        // Add the setup cmd
        matlabCmd.append("setup([],true);");

        //TESTING
        /*
        std::vector<matlab::data::Array> setup;
        //size_t empty = 0;
        setup.push_back(factory.createEmptyArray());
        setup.push_back(factory.createScalar<bool>(true));
        //matlabPtr->feval(u"setup",factory.createArray<double>({0,0},{}),factory.createScalar<bool>(true));
        matlabPtr->feval(u"setup",0,setup);
        */

        // TODO: FIND A NEW WAY TO DO OUTPUT
        // Create string buffer for standard output
        /*
        std::shared_ptr<StringBuf> output = std::make_shared<StringBuf>();
        mOutThread = new matlabOutputThread(this, output, mPathJNameParseCluster, mThreadID);
        connect(this, &matlabThread::jobFinish, mOutThread, &matlabOutputThread::onJobFinish);
        mOutThread->start(QThread::NormalPriority);
        */


        if (funcType == "crop"){
            matlabCmd.append("XR_crop_dataset("+args+");");
        }
        else if(funcType == "DeconOnly"){
            matlabCmd.append("XR_decon_data_wrapper("+args+");");
        }
        else if(funcType == "simRecon"){
            matlabCmd.append("simReconAutomaticProcessing("+args+");");
        }
        else if(funcType == "mipGenerator"){
            matlabCmd.append("XR_MIP_wrapper("+args+");");
        }
        else if(funcType == "parallelRsync"){
            matlabCmd.append("XR_parallel_rsync_wrapper("+args+");");
        }
        else if(funcType == "fftAnalysis"){
            matlabCmd.append("XR_fftSpectrumComputingWrapper("+args+");");
        }
        else if(funcType == "fscAnalysis"){
            matlabCmd.append("XR_FSC_analysis_wrapper("+args+");");
        }
        else{
            matlabCmd.append("XR_microscopeAutomaticProcessing("+args+");");
        }
        matlabCmd.append("\"");
    }
    // If the user is using mcc
    else{
        std::string mccDir = "\""+QCoreApplication::applicationDirPath().toStdString()+"/mcc/run_mccMaster.sh\"";
        matlabCmd.append(mccDir);
        std::string matlabFunc;
        if (funcType == "crop"){
            matlabFunc = "XR_crop_dataset";
        }
        else if(funcType == "DeconOnly"){
            matlabFunc = "XR_decon_data_wrapper";
        }
        else if(funcType == "simRecon"){
            matlabFunc = "simReconAutomaticProcessing";
        }
        else if(funcType == "mipGenerator"){
            matlabFunc = "XR_MIP_wrapper";
        }
        else if(funcType == "parallelRsync"){
            matlabFunc = "XR_parallel_rsync_wrapper";
        }
        else if(funcType == "fftAnalysis"){
            matlabFunc = "XR_fftSpectrumComputingWrapper";
        }
        else if(funcType == "fscAnalysis"){
            matlabFunc = "XR_FSC_analysis_wrapper";
        }
        else{
            matlabFunc = "XR_microscopeAutomaticProcessing";
        }
        matlabCmd.append(" \""+pathToMatlab+"\" "+matlabFunc+" "+args);
    }
    //std::cout << matlabCmd << std::endl;
    jobSuccess = !system(matlabCmd.c_str());
    /*
    }
    catch(const matlab::engine::MATLABException& ex){
        jobSuccess = false;
        matlabPtr->feval(u"disp", 0, std::vector<matlab::data::Array>({factory.createScalar(ex.what())}));
    }

    // Close MATLAB session by deleting the unique pointer (Still testing)
    matlabPtr.reset();
    */
    /*
    if(mOutThread){
        emit jobFinish(true);
        mOutThread->wait();
    }*/

    if(jobSuccess) std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" Finished" << std::endl;
    else{
        //if(std::get<2>(mPathJNameParseCluster))
        std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION." << std::endl;
        //else std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION. Check job output file for details." << std::endl;
    }
}

