#ifndef MATLABTHREAD_H
#define MATLABTHREAD_H

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include <QtCore>
#include <QThread>

using namespace matlab::engine;

class matlabThread : public QThread
{
public:
    matlabThread(QObject *parent = 0);
    ~matlabThread();
    void run();
public slots:
    void onJobStart(const size_t outA, const std::vector<matlab::data::Array> &data);
private:
    std::unique_ptr<MATLABEngine> matlabPtr;
    matlab::data::ArrayFactory factory;
    size_t outA;
    std::vector<matlab::data::Array> data;
};

#endif // MATLABTHREAD_H
