#ifndef MATLABTHREADMANAGER_H
#define MATLABTHREADMANAGER_H

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include "matlabthread.h"
#include <unordered_map>
#include <QtCore>
#include <QThread>

using namespace matlab::engine;

class matlabThreadManager : public QThread
{
    Q_OBJECT
public:
    matlabThreadManager(QMutex &outputLock, QObject *parent = 0);
    ~matlabThreadManager();
    void run();
public slots:
    void onJobStart(size_t &outA, std::vector<matlab::data::Array> &data, std::string &funcType, std::tuple<std::string, std::string, bool> &mPathJNameParseCluster, std::unordered_map<int,std::pair<std::string,QDateTime>> &jobLogPaths);
signals:
    void enableSubmitButton();
    void addOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath);
private:
    std::unordered_map<unsigned int, matlabThread*> mThreads;
    std::unique_ptr<MATLABEngine> matlabPtr;
    matlab::data::ArrayFactory factory;
    QMutex *outputLock;
    std::tuple<std::string, std::string, bool> mPathJNameParseCluster;
    std::unordered_map<int,std::pair<std::string,QDateTime>> *jobLogPaths;
    size_t outA;
    std::vector<matlab::data::Array> data;
    std::string funcType;

};

#endif // MATLABTHREADMANAGER_H
