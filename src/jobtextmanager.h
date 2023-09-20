#ifndef JOBTEXTMANAGER_H
#define JOBTEXTMANAGER_H
#include <QtCore>
#include <QThread>


class jobTextManager : public QThread
{
    Q_OBJECT
public:
    jobTextManager(QObject *parent = 0);
    void run();

public slots:
    void onCloseManager();

signals:
    void updateTextWindow();

private:
    QObject *parent;
    bool textWindowOpen;
};

#endif // JOBTEXTMANAGER_H
