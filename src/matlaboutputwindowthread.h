#ifndef MATLABOUTPUTWINDOWTHREAD_H
#define MATLABOUTPUTWINDOWTHREAD_H

#include <QtCore>
#include <QThread>
#include <unordered_map>
#include <QMetaType>

typedef std::map<int,std::map<QString,QString>> fNameMapMap;
//Q_DECLARE_METATYPE(fNameMapMap)

class matlabOutputWindowThread : public QThread
{
    Q_OBJECT
public:
    matlabOutputWindowThread(std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, QObject *parent = nullptr);
    ~matlabOutputWindowThread();
    void run();
public slots:
    //void onAddOutputIDAndPath(const unsigned int mThreadID, const QString mainPath);
signals:
    void updateOutputForm(std::map<int,std::map<QString,QString>> *fNames, QMutex *fileNamesLock);
private:
    std::unordered_map<unsigned int, std::pair<QString,bool>> jobPaths;
    std::unordered_map<int,std::pair<QString,QDateTime>> *jobLogPaths;
    QMutex fileNamesLock;

    bool killThread = 0;
};

#endif // MATLABOUTPUTWINDOWTHREAD_H
