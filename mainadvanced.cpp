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
    ui->resampleTypeComboBox->setCurrentText(guiVals.resampleType);
    ui->resampleEnabledCheckBox->setChecked(guiVals.resampleEnabled);
    ui->resampleYSpinBox->setValue(guiVals.resample[0]);
    ui->resampleXSpinBox->setValue(guiVals.resample[1]);
    ui->resampleZSpinBox->setValue(guiVals.resample[2]);

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
    gVals->resampleType = ui->resampleTypeComboBox->currentText();
    gVals->resampleEnabled = ui->resampleEnabledCheckBox->isChecked();
    gVals->resample[0] = ui->resampleYSpinBox->value();
    gVals->resample[1] = ui->resampleXSpinBox->value();
    gVals->resample[2] = ui->resampleZSpinBox->value();
    mainAdvanced::close();
}

void mainAdvanced::on_resampleEnabledCheckBox_stateChanged(int arg1)
{
   ui->resampleYLabel->setEnabled(arg1);
   ui->resampleYSpinBox->setEnabled(arg1);
   ui->resampleXLabel->setEnabled(arg1);
   ui->resampleXSpinBox->setEnabled(arg1);
   ui->resampleZLabel->setEnabled(arg1);
   ui->resampleZSpinBox->setEnabled(arg1);
}

