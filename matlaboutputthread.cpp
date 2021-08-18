#include "matlaboutputthread.h"

matlabOutputThread::matlabOutputThread(QObject *parent, std::shared_ptr<StringBuf> output, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID) :
    QThread(parent), output(output), mPathJNameParseCluster(mPathJNameParseCluster), mThreadID(mThreadID), jobFinished(false)
{

}

matlabOutputThread::~matlabOutputThread(){

}

void matlabOutputThread::run(){
    std::string nOut;
    QString jobFileName;
    // Collect string from matlab thread
    if(!std::get<2>(mPathJNameParseCluster)){
        jobFileName = std::get<0>(mPathJNameParseCluster)+"/"+QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_")+std::get<1>(mPathJNameParseCluster)+".out";
        jobFileName.replace(" ", "_");
    }
    while(!jobFinished || nOut.size() != convertUTF16StringToUTF8String(output.get()->str()).size()){
        sleep(2);
        std::string mString = convertUTF16StringToUTF8String(output.get()->str());
        if(nOut.size() == mString.size()) continue;
        else if(nOut.empty()){
            nOut = mString;
        }
        else{
            size_t pos = mString.find(nOut);
            if (pos != std::string::npos)
            {
                size_t nOutLen = nOut.size();
                nOut = mString;
                mString.erase(pos, nOutLen);
            }
        }

        // Code for job logs
        if(!std::get<2>(mPathJNameParseCluster) && !jobFileName.isEmpty()){
            QFile file(jobFileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream stream(&file);
                stream << QString::fromStdString(mString);
            }
        }
        else std::cout << mString;
    }
}

void matlabOutputThread::onJobFinish(bool jobFinished){
    this->jobFinished = jobFinished;
}
