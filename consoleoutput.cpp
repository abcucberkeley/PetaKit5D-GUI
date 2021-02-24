#include "consoleoutput.h"
#include "ui_consoleoutput.h"

consoleOutput::consoleOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleOutput)
{

    ui->setupUi(this);

    // Setup thread for capturing MATLAB output
    cThread = new consoleThread;
    connect(cThread, &consoleThread::sendOutput, this, &consoleOutput::getOutput);
    cThread->start(QThread::LowPriority);
}

consoleOutput::~consoleOutput()
{
    delete ui;

    // delete the thread we made (will have to change though because this is dangerous)
    if(!cThread->isFinished()) cThread->terminate();
}

// Listens for output from the console thread and appends it to the text box
void consoleOutput::getOutput(const QString &output){
    ui->outputTextEdit->appendPlainText(output);
}
