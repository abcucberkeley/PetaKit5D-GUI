#include "submissionchecks.h"

void messageBoxError(QString errorText){
    QMessageBox messageBox;
    messageBox.warning(0,"Error",errorText);
    messageBox.setFixedSize(500,200);
    return;
}

void messageBoxSuccess(QString successText){
    QMessageBox messageBox;
    messageBox.information(0,"Success",successText);
    messageBox.setFixedSize(500,200);
    return;
}
