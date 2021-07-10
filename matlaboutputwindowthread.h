#ifndef MATLABOUTPUTWINDOWTHREAD_H
#define MATLABOUTPUTWINDOWTHREAD_H

#include <QtCore>
#include <QThread>
#include <unordered_map>

class matlabOutputWindowThread : public QThread
{
    Q_OBJECT
public:
    matlabOutputWindowThread(QObject *parent);
    void run();
public slots:
    void onAddOutputIDAndPath(const unsigned int mThreadID, const std::string mainPath);
private:
    std::unordered_map<unsigned int, std::pair<std::string,bool>> jobPaths;
};

#endif // MATLABOUTPUTWINDOWTHREAD_H
