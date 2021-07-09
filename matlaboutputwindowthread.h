#ifndef MATLABOUTPUTWINDOWTHREAD_H
#define MATLABOUTPUTWINDOWTHREAD_H

#include <QtCore>
#include <QThread>

class matlabOutputWindowThread : QThread
{
    Q_OBJECT
public:
    matlabOutputWindowThread(QObject *parent);
    void run();
};

#endif // MATLABOUTPUTWINDOWTHREAD_H
