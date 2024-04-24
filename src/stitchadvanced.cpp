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

