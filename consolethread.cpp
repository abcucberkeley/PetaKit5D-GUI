#include "consolethread.h"

consoleThread::consoleThread()
{

}

void consoleThread::run(){
    while(true){
        StdCapture console;
        console.BeginCapture();
        sleep(1);
        console.EndCapture();
        std::string output = console.GetCapture();
        if(!output.empty()) emit sendOutput(QString::fromStdString(output));
    }
}
