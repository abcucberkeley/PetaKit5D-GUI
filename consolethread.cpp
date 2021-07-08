#include "consolethread.h"

consoleThread::consoleThread()
{

}

// Constantly listen for new text coming into std streams
// Emits new text it to the GUI console every second (if there is any)
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
