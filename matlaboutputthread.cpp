#include "matlaboutputthread.h"

matlabOutputThread::matlabOutputThread(QObject *parent, std::shared_ptr<StringBuf> output, const std::string &mainPath, const unsigned int &mThreadID) :
    QThread(parent), output(output), mainPath(mainPath), mThreadID(mThreadID), jobFinished(false)
{

}

matlabOutputThread::~matlabOutputThread(){

}

void matlabOutputThread::run(){
    std::string nOut;
    QDir dir(QString::fromStdString(mainPath+"/jobOutput"));
    if (!dir.exists()) dir.mkpath(".");

    QString filename=dir.absolutePath()+QString::fromStdString("/job")+QString::number(mThreadID)+QDateTime::currentDateTime().toString("_yyyyMMdd_HH_mm_ss")+QString::fromStdString(".txt");

    // Collect string from matlab thread
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

        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QTextStream stream(&file);
            stream << QString::fromStdString(mString);
        }

        //std::cout << mString;
    }
}

void matlabOutputThread::onJobFinish(bool jobFinished){
    this->jobFinished = jobFinished;
}
