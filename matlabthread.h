#ifndef MATLABTHREAD_H
#define MATLABTHREAD_H

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include "matlaboutputthread.h"
#include <QtCore>
#include <QThread>

using namespace matlab::engine;


class matlabThread : public QThread
{
    Q_OBJECT
public:
    matlabThread(QObject *parent, const QString &funcType, const size_t &outA, const std::vector<matlab::data::Array> &data, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID);
    ~matlabThread();
    void run();
public slots:

signals:
    void jobFinish(bool jobFinished);
private:
    matlabOutputThread* mOutThread;
    std::unique_ptr<MATLABEngine> matlabPtr;
    matlab::data::ArrayFactory factory;
    QString funcType;
    size_t outA;
    std::vector<matlab::data::Array> data;
    std::tuple<QString, QString, bool> mPathJNameParseCluster;
    unsigned int mThreadID;
};

#endif // MATLABTHREAD_H
