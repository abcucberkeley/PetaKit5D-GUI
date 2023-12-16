#pragma once
#include <QApplication>
#include <QWidget>
#include <QDockWidget>
#include <vector>
#include <sstream>
#include <QProcess>
#include "matlaboutputwindow.h"
#include <QTextBrowser>
#include "matlabthread.h"

class mainwindowConsoleOutputWindow : public QDockWidget{
public:
    mainwindowConsoleOutputWindow() = default;
    mainwindowConsoleOutputWindow(const QString&& title,QMutex& outputLock, QWidget* parent=nullptr);
    ~mainwindowConsoleOutputWindow();

    void uploadJobLogs(matlabOutputWindow *jobLogsOutputWindow);

    void printLog(QString msg);
    void printLogStdString(std::string msg);

public slots:
    void printStdout(QString str);
    void printStdoutStdString(std::string str);

private:
    QTextBrowser* consoleEdit;
    QMutex* outputLock;
};

