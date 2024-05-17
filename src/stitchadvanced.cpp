#include "stitchadvanced.h"
#include "ui_stitchadvanced.h"

stitchAdvanced::stitchAdvanced(GUIvals &guiVals, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::stitchAdvanced)
{
    ui->setupUi(this);

    // Pointer to hold the passed in vals
    gVals = &guiVals;
    ui->boundBoxCheckBox->setChecked(guiVals.boundboxCropCheckBox);
    if(guiVals.boundboxCropCheckBox){
        ui->boundBoxYMinSpinBox->setValue(std::stoi(guiVals.boundboxCrop[0]));
        ui->boundBoxXMinSpinBox->setValue(std::stoi(guiVals.boundboxCrop[1]));
        ui->boundBoxZMinSpinBox->setValue(std::stoi(guiVals.boundboxCrop[2]));
        ui->boundBoxYMaxSpinBox->setValue(std::stoi(guiVals.boundboxCrop[3]));
        ui->boundBoxXMaxSpinBox->setValue(std::stoi(guiVals.boundboxCrop[4]));
        ui->boundBoxZMaxSpinBox->setValue(std::stoi(guiVals.boundboxCrop[5]));
    }
    ui->stitchStitchMIPYCheckBox->setChecked(guiVals.stitchMIP[0]);
    ui->stitchStitchMIPXCheckBox->setChecked(guiVals.stitchMIP[1]);
    ui->stitchStitchMIPZCheckBox->setChecked(guiVals.stitchMIP[2]);
    ui->stitchInfoFullpathLineEdit->setText(guiVals.stitchInfoFullpath);
    ui->distBboxesCheckBox->setChecked(guiVals.distBboxesCheckBox);
    if(ui->distBboxesCheckBox->isChecked()){
        ui->distBboxesYMinSpinBox->setValue(std::stoi(guiVals.distBboxes[0]));
        ui->distBboxesXMinSpinBox->setValue(std::stoi(guiVals.distBboxes[1]));
        ui->distBboxesZMinSpinBox->setValue(std::stoi(guiVals.distBboxes[2]));
        ui->distBboxesYMaxSpinBox->setValue(std::stoi(guiVals.distBboxes[3]));
        ui->distBboxesXMaxSpinBox->setValue(std::stoi(guiVals.distBboxes[4]));
        ui->distBboxesZMaxSpinBox->setValue(std::stoi(guiVals.distBboxes[5]));
    }
    ui->overlapTypeComboBox->setCurrentText(guiVals.overlapType);
    ui->shiftMethodComboBox->setCurrentText(guiVals.shiftMethod);
    ui->groupFileLineEdit->setText(guiVals.groupFile);
    ui->processFunPathLineEdit->setText(guiVals.processFunPath);

}

stitchAdvanced::~stitchAdvanced()
{
    delete ui;
}

void stitchAdvanced::on_cancelButton_clicked()
{
    stitchAdvanced::close();
}


void stitchAdvanced::on_submitButton_clicked()
{
    gVals->boundboxCropCheckBox = ui->boundBoxCheckBox->isChecked();
    if(ui->boundBoxCheckBox->isChecked()){
        gVals->boundboxCrop = {ui->boundBoxYMinSpinBox->text().toStdString(),
                               ui->boundBoxXMinSpinBox->text().toStdString(),
                               ui->boundBoxZMinSpinBox->text().toStdString(),
                               ui->boundBoxYMaxSpinBox->text().toStdString(),
                               ui->boundBoxXMaxSpinBox->text().toStdString(),
                               ui->boundBoxZMaxSpinBox->text().toStdString()};
    }
    gVals->stitchMIP[0] = ui->stitchStitchMIPYCheckBox->isChecked();
    gVals->stitchMIP[1] = ui->stitchStitchMIPXCheckBox->isChecked();
    gVals->stitchMIP[2] = ui->stitchStitchMIPZCheckBox->isChecked();
    gVals->stitchInfoFullpath = ui->stitchInfoFullpathLineEdit->text();
    gVals->distBboxesCheckBox = ui->distBboxesCheckBox->isChecked();
    if(ui->distBboxesCheckBox->isChecked()){
        gVals->distBboxes = {ui->distBboxesYMinSpinBox->text().toStdString(),
                             ui->distBboxesXMinSpinBox->text().toStdString(),
                             ui->distBboxesZMinSpinBox->text().toStdString(),
                             ui->distBboxesYMaxSpinBox->text().toStdString(),
                             ui->distBboxesXMaxSpinBox->text().toStdString(),
                             ui->distBboxesZMaxSpinBox->text().toStdString()};
    }
    gVals->overlapType = ui->overlapTypeComboBox->currentText();
    gVals->shiftMethod = ui->shiftMethodComboBox->currentText();
    gVals->groupFile = ui->groupFileLineEdit->text();
    gVals->processFunPath = ui->processFunPathLineEdit->text();
    stitchAdvanced::close();
}


void stitchAdvanced::on_boundBoxCheckBox_stateChanged(int arg1)
{
    ui->boundBoxYMinLabel->setEnabled(arg1);
    ui->boundBoxYMinSpinBox->setEnabled(arg1);
    ui->boundBoxXMinLabel->setEnabled(arg1);
    ui->boundBoxXMinSpinBox->setEnabled(arg1);
    ui->boundBoxZMinLabel->setEnabled(arg1);
    ui->boundBoxZMinSpinBox->setEnabled(arg1);
    ui->boundBoxYMaxLabel->setEnabled(arg1);
    ui->boundBoxYMaxSpinBox->setEnabled(arg1);
    ui->boundBoxXMaxLabel->setEnabled(arg1);
    ui->boundBoxXMaxSpinBox->setEnabled(arg1);
    ui->boundBoxZMaxLabel->setEnabled(arg1);
    ui->boundBoxZMaxSpinBox->setEnabled(arg1);

    if(!arg1){
        ui->boundBoxYMinSpinBox->setValue(0);
        ui->boundBoxXMinSpinBox->setValue(0);
        ui->boundBoxZMinSpinBox->setValue(0);
        ui->boundBoxYMaxSpinBox->setValue(0);
        ui->boundBoxXMaxSpinBox->setValue(0);
        ui->boundBoxZMaxSpinBox->setValue(0);
    }
}


void stitchAdvanced::on_distBboxesCheckBox_stateChanged(int arg1)
{
    ui->distBboxesYMinLabel->setEnabled(arg1);
    ui->distBboxesYMinSpinBox->setEnabled(arg1);
    ui->distBboxesXMinLabel->setEnabled(arg1);
    ui->distBboxesXMinSpinBox->setEnabled(arg1);
    ui->distBboxesZMinLabel->setEnabled(arg1);
    ui->distBboxesZMinSpinBox->setEnabled(arg1);
    ui->distBboxesYMaxLabel->setEnabled(arg1);
    ui->distBboxesYMaxSpinBox->setEnabled(arg1);
    ui->distBboxesXMaxLabel->setEnabled(arg1);
    ui->distBboxesXMaxSpinBox->setEnabled(arg1);
    ui->distBboxesZMaxLabel->setEnabled(arg1);
    ui->distBboxesZMaxSpinBox->setEnabled(arg1);

    if(!arg1){
        ui->distBboxesYMinSpinBox->setValue(0);
        ui->distBboxesXMinSpinBox->setValue(0);
        ui->distBboxesZMinSpinBox->setValue(0);
        ui->distBboxesYMaxSpinBox->setValue(0);
        ui->distBboxesXMaxSpinBox->setValue(0);
        ui->distBboxesZMaxSpinBox->setValue(0);
    }
}

