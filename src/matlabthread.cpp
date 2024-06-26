#include <iostream>
#include <stdlib.h>
#include <regex>
#include "matlabthread.h"
#include <sstream>

matlabThread::matlabThread(QObject *parent, const QString &funcType, const size_t &outA, const std::string &args, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID, bool isMcc, const std::string &pathToMatlab) :
    QThread(parent), funcType(funcType), outA(outA), args(args), mPathJNameParseCluster(mPathJNameParseCluster), mThreadID(mThreadID), isMcc(isMcc), pathToMatlab(pathToMatlab)
{
    job = nullptr;
    killThread = 0;
}

matlabThread::~matlabThread(){
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

        // Add the PetaKit5D Repository to the path
        std::string newDir = QCoreApplication::applicationDirPath().toStdString()+"/PetaKit5D";
        matlabCmd.append(" \"cd(\'"+newDir+"\');");
        matlabCmd.append("addpath(genpath(\'"+newDir+"\'));");

        // Add the setup cmd
        matlabCmd.append("setup;");

        matlabCmd.append(funcType.toStdString()+"("+args+");");
        matlabCmd.append("\"");
    }
    // If the user is using mcc
    else{
        // We do not use the jvm because of the overhead unless it is required by the function
        #ifdef __linux__
        std::string mccLoc;
        if(funcType.toStdString() != "XR_visualize_OTF_mask_segmentation" && funcType.toStdString() != "XR_FSC_analysis_wrapper" && funcType.toStdString() != "XR_psf_analysis_wrapper" && funcType.toStdString() != "XR_psf_detection_and_analysis_wrapper"){
            mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/PetaKit5D/mcc/linux/run_mccMaster.sh\"";
        }
        else{
            mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/PetaKit5D/mcc/linux_with_jvm/run_mccMaster.sh\"";
        }
        #elif _WIN32
        std::string mccLoc;
        if(funcType.toStdString() != "XR_visualize_OTF_mask_segmentation" && funcType.toStdString() != "XR_FSC_analysis_wrapper" && funcType.toStdString() != "XR_psf_analysis_wrapper" && funcType.toStdString() != "XR_psf_detection_and_analysis_wrapper"){
            mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/PetaKit5D/mcc/windows/mccMaster\"";
        }
        else{
            mccLoc = "\""+QCoreApplication::applicationDirPath().toStdString()+"/PetaKit5D/mcc/windows_with_jvm/mccMaster\"";
        }
        #else
        std::string mccLoc;
        if(funcType.toStdString() != "XR_visualize_OTF_mask_segmentation" && funcType.toStdString() != "XR_FSC_analysis_wrapper" && funcType.toStdString() != "XR_psf_analysis_wrapper" && funcType.toStdString() != "XR_psf_detection_and_analysis_wrapper"){
            mccLoc = "\"/Applications/PetaKit5DMCC/mac/run_mccMaster.sh\"";
        }
        else{
            mccLoc = "\"/Applications/PetaKit5DMCC/mac_with_jvm/run_mccMaster.sh\"";
        }
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
    job->startCommand(QString::fromStdString(matlabCmd));
    std::stringstream ss;

    QString filename = std::get<0>(mPathJNameParseCluster) + "/master.out";
    QFile file(filename);
    QTextStream stream(&file);

    // Error checking
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
        ss << QString("Could not open filepath: " + filename).toStdString();
        ss << QString("ERROR: " + file.errorString()).toStdString();
        emit availableQProcessOutput(QString::fromStdString(ss.str()));
        ss.str(""); // resets stringstream
        stream.setStatus(QTextStream::WriteFailed);
    }

    while(job->state() != QProcess::NotRunning){
        QCoreApplication::processEvents(); // This is used when we have pending jobs running, will give us the current output from the process running. (not after)
        QString output = QString(job->readAll());

        // We only want to emit output if there are any data coming through QProcess
        if(!output.isEmpty()){
            emit availableQProcessOutput(output);

            // checking if any failure occurs when writing from QTextStream
            if(stream.status() != QTextStream::WriteFailed){
                stream << output;
                stream.flush(); // pushes data to disc
            }
        }

        sleep(2);
    }
    file.close();

    jobSuccess = !(job->exitCode());

    if(job->atEnd()){ // When the job has finished then we let the user know when this specific job has finished.
        if(jobSuccess){
            ss << std::string("Matlab Job \"" + std::get<1>(mPathJNameParseCluster).toStdString() + "\" Finished\n");
        }
        else{
            ss << std::string("Matlab Job \"" + std::get<1>(mPathJNameParseCluster).toStdString() + "\" has Failed. MATLAB EXCEPTION.\n");
        }
        emit availableQProcessOutput(QString::fromStdString(ss.str()));
		ss.str("");
    }
}
