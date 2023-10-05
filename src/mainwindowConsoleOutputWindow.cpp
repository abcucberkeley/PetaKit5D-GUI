#include "mainwindowConsoleOutputWindow.h"
#include <QTextStream>
#include <fstream>
#include <array>
#include <QProcess>
#include <QFile>
#include <QTextStream>

mainwindowConsoleOutputWindow::mainwindowConsoleOutputWindow(const QString&& title, QMutex& outputLock, QWidget* parent) 
        : QDockWidget(parent),
          outputLock(&outputLock){
    
    setWindowTitle(title);
    consoleEdit = new QTextBrowser(this);
    setWidget(consoleEdit);
}

mainwindowConsoleOutputWindow::~mainwindowConsoleOutputWindow(){
    delete consoleEdit;
}

void mainwindowConsoleOutputWindow::printLog(QString msg){
    outputLock->lock();
    consoleEdit->append(msg);
    outputLock->unlock();
}

void mainwindowConsoleOutputWindow::printLogStdString(std::string msg){
    outputLock->lock();
    consoleEdit->append(QString::fromUtf8(msg));
    outputLock->unlock();

    QFile file("test.out");

    QTextStream stream(&file);
    if(file.open(QIODeviceBase::WriteOnly)){
        // stream >> str;
        stream >> "This is taking output into this file";
    }

    file.close();
}

// This is where we add the jobs to the QDockWidget
void mainwindowConsoleOutputWindow::uploadJobLogs(matlabOutputWindow *jobLogsOutputWindow){
    this->setWidget(jobLogsOutputWindow);

    if(!jobLogsOutputWindow->isVisible()){
        jobLogsOutputWindow->setModal(false);
        jobLogsOutputWindow->show();
    }
}

void mainwindowConsoleOutputWindow::printStdout(QString str){
    outputLock->lock();
    consoleEdit->insertPlainText(str);
    outputLock->unlock();

    QFile file("temp.out");
}


void mainwindowConsoleOutputWindow::printStdoutStdString(std::string output){
    outputLock->lock();
    consoleEdit->append(QString::fromUtf8(output));
    outputLock->unlock();
}