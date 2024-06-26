#ifndef MATLABTHREADMANAGER_H
#define MATLABTHREADMANAGER_H

#include "matlabthread.h"
#include <unordered_map>
#include <QtCore>
#include <QThread>
#include "mainwindowconsoleoutputwindow.h"

class matlabThreadManager : public QThread
{
    Q_OBJECT
public:
    matlabThreadManager(QMutex &outputLock, QObject *parent = 0);
    ~matlabThreadManager();
    void killMatlabThreadManager();
    void run();
public slots:
    void onJobStart(std::string &args, QString &funcType, std::tuple<QString, QString, bool> &mPathJNameParseCluster, std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, bool isMcc, const std::string &pathToMatlab);
signals:
    void enableSubmitButton();
    void data(std::string output);
    void availableQProcessOutput(QString str);
private:
    std::string args;
    std::unordered_map<unsigned int, matlabThread*> mThreads;
    QMutex *outputLock;
    std::tuple<QString, QString, bool> mPathJNameParseCluster;
    std::unordered_map<int,std::pair<QString,QDateTime>> *jobLogPaths;
    size_t outA;
    QString funcType;
    bool isMcc;
    std::string pathToMatlab;

    bool killThread;
    std::ostringstream jobsOutput;
    std::streambuf* _stdout;
    std::streambuf* _stderr;


    // Some variables to test
    unsigned int mThreadID;
};

#endif // MATLABTHREADMANAGER_H
