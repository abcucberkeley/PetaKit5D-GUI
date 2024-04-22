#include "mainadvanced.h"
#include "ui_mainadvanced.h"
#include "configfilesettings.h"

mainAdvanced::mainAdvanced(GUIvals& guiVals, configFileVals& cFileVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainAdvanced)
{
    // pointer to hold the passed in vals
    gVals = &guiVals;
    this->cFileVals = &cFileVals;

    ui->setupUi(this);

    // set the vals in the window to the ones passed in
    ui->skewAngleSpinBox->setValue(guiVals.skewAngle);
    ui->dzFromEncoderCheckBox->setChecked(guiVals.dzFromEncoder);
    ui->reverseCheckBox->setChecked(guiVals.Reverse);
    ui->sCMOSCameraFlipCheckBox->setChecked(guiVals.sCMOSCameraFlip);
    ui->resampleTypeComboBox->setCurrentText(guiVals.resampleType);
    ui->resampleEnabledCheckBox->setChecked(guiVals.resampleEnabled);
    ui->resampleYSpinBox->setValue(guiVals.resample[0]);
    ui->resampleXSpinBox->setValue(guiVals.resample[1]);
    ui->resampleZSpinBox->setValue(guiVals.resample[2]);
    ui->zarrFileCheckBox->setChecked(guiVals.zarrFile);
    ui->saveZarrCheckBox->setChecked(guiVals.saveZarr);
    ui->save3DStackCheckBox->setChecked(guiVals.save3DStack);

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
    gVals->dzFromEncoder = ui->dzFromEncoderCheckBox->isChecked();
    gVals->Reverse = ui->reverseCheckBox->isChecked();
    gVals->sCMOSCameraFlip = ui->sCMOSCameraFlipCheckBox->isChecked();
    gVals->resampleType = ui->resampleTypeComboBox->currentText();
    gVals->resampleEnabled = ui->resampleEnabledCheckBox->isChecked();
    gVals->resample[0] = ui->resampleYSpinBox->value();
    gVals->resample[1] = ui->resampleXSpinBox->value();
    gVals->resample[2] = ui->resampleZSpinBox->value();
    gVals->zarrFile = ui->zarrFileCheckBox->isChecked();
    gVals->saveZarr = ui->saveZarrCheckBox->isChecked();
    gVals->save3DStack = ui->save3DStackCheckBox->isChecked();
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


void mainAdvanced::on_configFileSettingsButton_clicked()
{
    configFileSettings cFileSettings(cFileVals);
    cFileSettings.setModal(true);
    cFileSettings.exec();
}

