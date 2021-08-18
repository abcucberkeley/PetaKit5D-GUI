#include "dsradvanced.h"
#include "ui_dsradvanced.h"

DSRadvanced::DSRadvanced(GUIvals &guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DSRadvanced)
{
    ui->setupUi(this);

    // pointer to hold the passed in vals
    gVals = &guiVals;

    // set the vals in the window to the ones passed in
    ui->bkRemovalCheckBox->setChecked(guiVals.BKRemoval);
    ui->lowerLimitSpinBox->setValue(guiVals.LowerLimit);
    ui->resampleTypeComboBox->setCurrentText(guiVals.resampleType);
    ui->resampleSpinBox->setValue(guiVals.resample);

}

DSRadvanced::~DSRadvanced()
{
    delete ui;
}

// Close the window
void DSRadvanced::on_cancelButton_clicked()
{
    DSRadvanced::close();
}

// Close the window and save the current vals
void DSRadvanced::on_submitButton_clicked()
{
    gVals->BKRemoval = ui->bkRemovalCheckBox->isChecked();
    gVals->LowerLimit = ui->lowerLimitSpinBox->value();
    gVals->resampleType = ui->resampleTypeComboBox->currentText();
    gVals->resample = ui->resampleSpinBox->value();
    DSRadvanced::close();
}
