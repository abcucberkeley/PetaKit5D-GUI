#ifndef MATLABTHREADMANAGER_H
#define MATLABTHREADMANAGER_H

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include "matlabthread.h"
#include "matlabjobsettings.h"
#include <unordered_map>
#include <deque>
#include <QtCore>
#include <QThread>

using namespace matlab::engine;

class matlabThreadManager : public QThread
{
    Q_OBJECT
public:
    matlabThreadManager(std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, QMutex &outputLock, QObject *parent = 0);
    ~matlabThreadManager();
    void run();
public slots:
    void onJobStart(const matlabJobSettings &newJob);
signals:
    void enableSubmitButton();
    void addOutputIDAndPath(const unsigned int mThreadID, const QString mainPath);
private:
    std::unordered_map<unsigned int, matlabThread*> mThreads;
    QMutex *outputLock;
    QMutex jobQueueLock;
    std::unordered_map<int,std::pair<QString,QDateTime>> *jobLogPaths;
    std::deque<matlabJobSettings> jobQueue;

};

#endif // MATLABTHREADMANAGER_H
