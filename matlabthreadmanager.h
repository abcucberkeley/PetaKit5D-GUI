#ifndef MATLABTHREADMANAGER_H
#define MATLABTHREADMANAGER_H

//#include "MatlabEngine.hpp"
//#include "MatlabDataArray.hpp"
#include "matlabthread.h"
#include <unordered_map>
#include <QtCore>
#include <QThread>

//using namespace matlab::engine;

class matlabThreadManager : public QThread
{
    Q_OBJECT
public:
    matlabThreadManager(QMutex &outputLock, QObject *parent = 0);
    ~matlabThreadManager();
    void run();
public slots:
    void onJobStart(std::string &args, QString &funcType, std::tuple<QString, QString, bool> &mPathJNameParseCluster, std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, bool isMcc, const std::string &pathToMatlab);
signals:
    void enableSubmitButton();
    void addOutputIDAndPath(const unsigned int mThreadID, const QString mainPath);
private:
    std::string args;
    std::unordered_map<unsigned int, matlabThread*> mThreads;
    //std::unique_ptr<MATLABEngine> matlabPtr;
    //matlab::data::ArrayFactory factory;
    QMutex *outputLock;
    std::tuple<QString, QString, bool> mPathJNameParseCluster;
    std::unordered_map<int,std::pair<QString,QDateTime>> *jobLogPaths;
    size_t outA;
    //std::vector<matlab::data::Array> data;
    QString funcType;
    bool isMcc;
    std::string pathToMatlab;

    bool killThread;

};

#endif // MATLABTHREADMANAGER_H
