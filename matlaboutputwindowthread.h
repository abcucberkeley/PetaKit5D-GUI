#ifndef MATLABOUTPUTWINDOWTHREAD_H
#define MATLABOUTPUTWINDOWTHREAD_H

#include <QtCore>
#include <QThread>
#include <unordered_map>

class matlabOutputWindowThread : public QThread
{
    Q_OBJECT
public:
    matlabOutputWindowThread(std::unordered_map<int,std::string> &jobLogPaths, QObject *parent = nullptr);
    void run();
public slots:
    void onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath);
signals:
    void updateOutputForm();
private:
    std::unordered_map<unsigned int, std::pair<std::string,bool>> jobPaths;
    std::unordered_map<int,std::string> *jobLogPaths;
};

#endif // MATLABOUTPUTWINDOWTHREAD_H
