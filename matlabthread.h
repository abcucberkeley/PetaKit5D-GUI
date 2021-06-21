#ifndef MATLABTHREAD_H
#define MATLABTHREAD_H

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include "matlabthread.h"
#include <QtCore>
#include <QThread>

using namespace matlab::engine;

class matlabThread : public QThread
{
    Q_OBJECT
public:
    matlabThread(QObject *parent, const std::string &funcType, const size_t &outA, const std::vector<matlab::data::Array> &data, const unsigned int &mThreadID);
    ~matlabThread();
    void run();
public slots:

signals:
  //void enableSubmitButton();
private:
    std::unique_ptr<MATLABEngine> matlabPtr;
    matlab::data::ArrayFactory factory;
    size_t outA;
    std::vector<matlab::data::Array> data;
    std::string funcType;
    unsigned int mThreadID;
};

#endif // MATLABTHREAD_H

/*class matlabThreadManager : public QThread
{
    Q_OBJECT
public:
    matlabThreadManager(QObject *parent = 0);
    ~matlabThreadManager();
    void run();
public slots:
    void onJobStart(const size_t outA, const std::vector<matlab::data::Array> &data, const std::string funcType);
signals:
    void enableSubmitButton();
private:
    std::unique_ptr<MATLABEngine> matlabPtr;
    matlab::data::ArrayFactory factory;
    size_t outA;
    std::vector<matlab::data::Array> data;
    std::string funcType;
};*/
