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

    std::string matlabCmd;

    // If the user has a matlab installation
    if(!isMcc){
        std::string matlabOptions = "-batch";

        matlabCmd.append("\""+pathToMatlab+"\" "+matlabOptions);
        //matlab -batch "cd('/clusterfs/nvme/matthewmueller/clusterBenchmarking');clusterBenchmarking;exit;"

        // Add the LLSM5DTools Repository to the path
        std::string newDir = QCoreApplication::applicationDirPath().toStdString()+"/LLSM5DTools";
        matlabCmd.append(" \"cd(\'"+newDir+"\');");
        matlabCmd.append("addpath(genpath(\'"+newDir+"\'));");

        // Add the setup cmd
        matlabCmd.append("setup([],true);");

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
        #ifdef __linux__
        std::string mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/LLSM5DTools/mcc/linux/run_mccMaster.sh\"";
        #elif _WIN32
        std::string mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/LLSM5DTools/mcc/windows/mccMaster\"";
        #else

        #endif
        matlabCmd.append(mccLoc);
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
        #ifndef _WIN32
        matlabCmd.append(" \""+pathToMatlab+"\"");
        #endif
        matlabCmd.append(" "+matlabFunc+" "+args);
    }
    //std::cout << matlabCmd << std::endl;
    jobSuccess = !system(matlabCmd.c_str());

    if(jobSuccess) std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" Finished" << std::endl;
    else{
        //if(std::get<2>(mPathJNameParseCluster))
        std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION." << std::endl;
        //else std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION. Check job output file for details." << std::endl;
    }
}

