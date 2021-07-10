#include "matlaboutputwindowthread.h"

matlabOutputWindowThread::matlabOutputWindowThread(QObject *parent) :
    QThread(parent)
{

}

void matlabOutputWindowThread::run(){

    while(true){
        sleep(5);
        for(auto &path : jobPaths){
            if(path.second.second == false){

            }
            else{

            }
        }
    }
}

void matlabOutputWindowThread::onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath){
    jobPaths.emplace(mThreadID,std::make_pair(mainPath,false));
}
