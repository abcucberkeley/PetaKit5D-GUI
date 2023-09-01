#include "submissionchecks.h"

void messageBoxError(const QString &errorText){
    QMessageBox messageBox;
    messageBox.warning(0,"Error",errorText);
    messageBox.setFixedSize(500,200);
    return;
}

void messageBoxSuccess(QWidget* parent, const QString &successText){
    QMessageBox messageBox(parent);
    messageBox.information(0,"Success",successText);
    messageBox.setFixedSize(500,200);
    return;
}

bool dataPathsAreSet(const std::vector<dataPath> &dPaths){
    if(!dPaths.size()){
        messageBoxError("No data paths are set. Please set at least one data path before continuing.");
        return false;
    }
    return true;
}

bool channelPatternsAreSet(const std::vector<std::pair<QLabel*,QCheckBox*>> &channelWidgets, const QCheckBox* customPatternsCheckBox, const QLineEdit* customPatternsLineEdit){
    if(!channelWidgets.size() && (!customPatternsCheckBox->isChecked() || customPatternsLineEdit->text().isEmpty())){
        messageBoxError("No channel patterns set. Please set at least one pattern before continuing.");
        return false;
    }
    for(size_t i = 0; i < channelWidgets.size(); i++){
        if(channelWidgets[i].second->isChecked()) break;
        if(i == channelWidgets.size()-1 && (!customPatternsCheckBox->isChecked() || customPatternsLineEdit->text().isEmpty())){
            messageBoxError("No channel patterns set. Please set at least one pattern before continuing.");
            return false;
        }
    }
    return true;
}
