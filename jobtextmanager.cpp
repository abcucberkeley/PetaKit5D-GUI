#include "jobtextmanager.h"

jobTextManager::jobTextManager(QObject *parent) :
    QThread(parent), parent(parent), textWindowOpen(true)
{

}

void jobTextManager::run(){
    while(textWindowOpen && parent){
            emit updateTextWindow();
            sleep(5);
    }
}

void jobTextManager::onCloseManager(){
    textWindowOpen = false;
}
