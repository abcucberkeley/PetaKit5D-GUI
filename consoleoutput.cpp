#include "consoleoutput.h"
#include "ui_consoleoutput.h"
#include <iostream>
#include <string>

consoleOutput::consoleOutput(std::shared_ptr<SBuf> &output, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleOutput)
{
    ui->setupUi(this);
    this->output = &output;
    //QString out(output->readAllStandardOutput());
    //ui->outputTextEdit->appendPlainText(out);
    //std::shared_ptr<SBuf> test = output.get();
    //this->output->str();
    //ui->outputTextEdit->appendPlainText(this->output->get());
    //connect(this->output,&QProcess::readyReadStandardOutput,this,&consoleOutput::readConsole);
    std::cout << "huh" << std::endl;
    //output->start();
    //connect(this, &MainWindow::jobStart, mThread, &matlabThread::onJobStart);
}

consoleOutput::~consoleOutput()
{
    delete ui;

    //This ui will clean this up because we were given it from the main window
    delete output;
}

void consoleOutput::readConsole(){

}
