#ifndef MATLABOUTPUTWINDOWTHREAD_H
#define MATLABOUTPUTWINDOWTHREAD_H

#include <QtCore>
#include <QThread>
#include <unordered_map>
#include <QMetaType>

typedef std::map<int,std::map<std::string,std::string>> fNameMapMap;
//Q_DECLARE_METATYPE(fNameMapMap)

class matlabOutputWindowThread : public QThread
{
    Q_OBJECT
public:
    matlabOutputWindowThread(std::unordered_map<int,std::string> &jobLogPaths, QObject *parent = nullptr);
    void run();
public slots:
    void onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath);
signals:
    void updateOutputForm(std::map<int,std::map<std::string,std::string>> *fNames, QMutex *fileNamesLock);
    //void updateOutputForm(QMap<int,QMap<QString,QString>> fNames);
    //void updateOutputForm(QString &test);
private:
    std::unordered_map<unsigned int, std::pair<std::string,bool>> jobPaths;
    std::unordered_map<int,std::string> *jobLogPaths;
    QMutex fileNamesLock;
};

#endif // MATLABOUTPUTWINDOWTHREAD_H
