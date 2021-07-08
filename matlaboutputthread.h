#ifndef MATLABOUTPUTTHREAD_H
#define MATLABOUTPUTTHREAD_H

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include <QtCore>
#include <QThread>

using namespace matlab::engine;
typedef std::basic_stringbuf<char16_t> StringBuf;

class matlabOutputThread : public QThread
{
    Q_OBJECT
public:
    matlabOutputThread(QObject *parent, std::shared_ptr<StringBuf> output, const std::string &mainPath);
    ~matlabOutputThread();
    void run();
public slots:
    void onJobFinish(bool jobFinished);
private:
    std::shared_ptr<StringBuf> output;
    std::string mainPath;
    bool jobFinished;
};

#endif // MATLABOUTPUTTHREAD_H
