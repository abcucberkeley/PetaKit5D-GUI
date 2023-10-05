#ifndef MATLABTHREAD_H
#define MATLABTHREAD_H

#include <QtCore>
#include <QThread>
#include <QPlainTextEdit>

class matlabThread : public QThread
{
    Q_OBJECT
public:
    matlabThread(QObject *parent, const QString &funcType, const size_t &outA, const std::string &args, std::tuple<QString, QString, bool> &mPathJNameParseCluster, const unsigned int &mThreadID, bool isMcc, const std::string &pathToMatlab);
    ~matlabThread();
    void killMatlabThread();
    void run();
signals:
    void availableQProcessOutput(QString str);
    
public slots:

private:
    //matlabOutputThread* mOutThread;
    //std::unique_ptr<MATLABEngine> matlabPtr;
    //matlab::data::ArrayFactory factory;
    QString funcType;
    size_t outA;
    std::string args;
    //std::vector<matlab::data::Array> data;
    std::tuple<QString, QString, bool> mPathJNameParseCluster;
    unsigned int mThreadID;
    bool isMcc;
    std::string pathToMatlab;
    QProcess *job;
    bool killThread;
    bool jobSuccess;
    std::string matlabCmd;
};

#endif // MATLABTHREAD_H
