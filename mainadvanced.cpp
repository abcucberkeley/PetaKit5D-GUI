#include "mainadvanced.h"
#include "ui_mainadvanced.h"

mainAdvanced::mainAdvanced(GUIvals& guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainAdvanced)
{
    // pointer to hold the passed in vals
    gVals = &guiVals;

    ui->setupUi(this);

    // set the vals in the window to the ones passed in
    ui->skewAngleSpinBox->setValue(guiVals.skewAngle);
    ui->xyPixelSizeSpinBox->setValue(guiVals.xyPixelSize);
    ui->reverseCheckBox->setChecked(guiVals.Reverse);
    ui->sCMOSCameraFlipCheckBox->setChecked(guiVals.sCMOSCameraFlip);
}

mainAdvanced::~mainAdvanced()
{
    delete ui;
}

// Close the window
void mainAdvanced::on_cancelButton_clicked()
{
    mainAdvanced::close();
}

// Close the window and save the current vals
void mainAdvanced::on_submitButton_clicked()
{
    gVals->skewAngle = ui->skewAngleSpinBox->value();
    gVals->xyPixelSize = ui->xyPixelSizeSpinBox->value();
    gVals->Reverse = ui->reverseCheckBox->isChecked();
    gVals->sCMOSCameraFlip = ui->sCMOSCameraFlipCheckBox->isChecked();
    mainAdvanced::close();
}
