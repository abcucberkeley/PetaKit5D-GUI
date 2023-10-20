#include <iostream>
#include <stdlib.h>
#include <regex>
#include "matlabthread.h"
#include "mainwindowConsoleOutputWindow.h"
#include <sstream>

matlabThread::matlabThread(QObject *parent, const QString &funcType, const size_t &outA, const std::string &args, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID, bool isMcc, const std::string &pathToMatlab) :
    QThread(parent), funcType(funcType), outA(outA), args(args), mPathJNameParseCluster(mPathJNameParseCluster), mThreadID(mThreadID), isMcc(isMcc), pathToMatlab(pathToMatlab)
{
    job = nullptr;
    killThread = 0;
}

matlabThread::~matlabThread(){
    /*
    if(mOutThread){
        if(!mOutThread->isFinished()) {
            mOutThread->terminate();
        }
    }
    */
    if(job){
        job->kill();
        job->terminate();
    }
    killThread = 1;
}

void matlabThread::killMatlabThread(){
    killThread = 1;
}

void matlabThread::run(){
    // Start matlab and add needed paths
    jobSuccess = true;

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
        matlabCmd.append("setup;");

        matlabCmd.append(funcType.toStdString()+"("+args+");");
        matlabCmd.append("\"");
    }
    // If the user is using mcc
    else{
        #ifdef __linux__
        std::string mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/LLSM5DTools/mcc/linux/run_mccMaster.sh\"";
        #elif _WIN32
        std::string mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/LLSM5DTools/mcc/windows/mccMaster\"";
        #else
        std::string mccLoc = "/Applications/LLSM5DToolsMCC/run_mccMaster.sh";
        #endif
        matlabCmd.append(mccLoc);

        #ifndef _WIN32
        matlabCmd.append(" \""+pathToMatlab+"\"");
        #endif
        matlabCmd.append(" "+funcType.toStdString()+" "+args);
        // Replace all instances of "" with """""" to conform with QProcess
        // Later we can change the setup functions to account for this
        matlabCmd = std::regex_replace(matlabCmd, std::regex(" \"\""), " \"\"\"\"\"\"");
    }

    job = new QProcess(this);
    job->setProcessChannelMode(QProcess::MergedChannels);
    job->startCommand(QString::fromUtf8(matlabCmd));
    
    std::stringstream ss;
    while(job->state() != QProcess::NotRunning){
        QCoreApplication::processEvents(); // This is used when we have pending jobs running, will give us the current output from the process running. (not after)
        QString output = QString(job->readAll());
        emit availableQProcessOutput(output);
        sleep(2);
    }

    jobSuccess = !(job->exitCode());

    if(job->atEnd()){ // When the job has finished then we let the user know when this specific job has finished.
        ss.str(std::string());
        if(jobSuccess) ss << std::string("Matlab Job \"" + std::get<1>(mPathJNameParseCluster).toStdString() + "\" Finished\n");
        else{
            //if(std::get<2>(mPathJNameParseCluster))
            ss << std::string("Matlab Job \"" + std::get<1>(mPathJNameParseCluster).toStdString() + "\" has Failed. MATLAB EXCEPTION.\n");
            //else std::cout << "Matlab Job \"" << std::get<1>(mPathJNameParseCluster).toStdString() << "\" has Failed. MATLAB EXCEPTION. Check job output file for details." << std::endl;
        }
    }
    
    emit availableQProcessOutput(QString::fromUtf8(ss.str()));
}
