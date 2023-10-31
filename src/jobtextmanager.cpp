#include "jobtextmanager.h"

jobTextManager::jobTextManager(QObject *parent) :
    QThread(parent), textWindowOpen(true)
{

}

jobTextManager::~jobTextManager(){
    this->wait();
}

void jobTextManager::run(){
    uint8_t currSecond = 0;
    while(textWindowOpen){
        emit updateTextWindow();
        while (textWindowOpen && currSecond < 60){
            sleep(2);
            currSecond+=2;
        }
        currSecond = 0;
    }
}

void jobTextManager::onCloseManager(){
    textWindowOpen = false;
}
