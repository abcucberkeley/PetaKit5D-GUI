#include "deconadvanced.h"
#include "ui_deconadvanced.h"
#include <QFileInfo>
#include <QFileDialog>

deconAdvanced::deconAdvanced(GUIvals &guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deconAdvanced)
{
    ui->setupUi(this);

    // Pointer to hold the passed in vals
    gVals = &guiVals;

    // Set the vals in the window to the ones passed in
    if(guiVals.RLMethod == "original") ui->rlMethodOriginalRadioButton->setChecked(true);
    else if(guiVals.RLMethod == "simplified"){
        ui->rlMethodSimplifiedRadioButton->setChecked(true);
        ui->fixIterLabel->setEnabled(true);
        ui->fixIterCheckBox->setEnabled(true);
        ui->errThreshLabel->setEnabled(true);
        ui->errThreshLineEdit->setEnabled(true);
        ui->debugLabel->setEnabled(true);
        ui->debugCheckBox->setEnabled(true);
    }
    else if (guiVals.RLMethod == "OMW") ui->rlMethodOMWRadioButton->setChecked(true);
    ui->fixIterCheckBox->setChecked(guiVals.fixIter);
    ui->errThreshLineEdit->setText(QString::number(guiVals.errThresh));
    ui->debugCheckBox->setChecked(guiVals.debug);
    ui->gpuJobCheckBox->setChecked(guiVals.gpuJob);
    if(guiVals.RLMethod != "simplified"){
        ui->fixIterLabel->setEnabled(false);
        ui->fixIterCheckBox->setEnabled(false);
        ui->errThreshLabel->setEnabled(false);
        ui->errThreshLineEdit->setEnabled(false);
        ui->debugLabel->setEnabled(false);
        ui->debugCheckBox->setEnabled(false);
    }
    ui->largeMethodComboBox->setCurrentText(guiVals.largeMethod);
}

deconAdvanced::~deconAdvanced()
{
    delete ui;
}

// Close the window
void deconAdvanced::on_cancelButton_clicked()
{
    deconAdvanced::close();
}

// Close the window and save the current vals
void deconAdvanced::on_submitButton_clicked()
{
    if(ui->rlMethodOriginalRadioButton->isChecked()) gVals->RLMethod = "original";
    else if (ui->rlMethodSimplifiedRadioButton->isChecked()) gVals->RLMethod = "simplified";
    else if (ui->rlMethodOMWRadioButton->isChecked()) gVals->RLMethod = "OMW";
    gVals->fixIter = ui->fixIterCheckBox->isChecked();
    gVals->errThresh = ui->errThreshLineEdit->text().toDouble();
    gVals->debug = ui->debugCheckBox->isChecked();
    gVals->gpuJob = ui->gpuJobCheckBox->isChecked();
    gVals->largeMethod = ui->largeMethodComboBox->currentText();
    deconAdvanced::close();
}

// Disable extra options if simplified is not checked
void deconAdvanced::on_rlMethodSimplifiedRadioButton_toggled(bool checked)
{
    if(checked){
        ui->fixIterLabel->setEnabled(true);
        ui->fixIterCheckBox->setEnabled(true);
        ui->errThreshLabel->setEnabled(true);
        ui->errThreshLineEdit->setEnabled(true);
        ui->debugLabel->setEnabled(true);
        ui->debugCheckBox->setEnabled(true);
    }
    else{
        ui->fixIterLabel->setEnabled(false);
        ui->fixIterCheckBox->setEnabled(false);
        ui->errThreshLabel->setEnabled(false);
        ui->errThreshLineEdit->setEnabled(false);
        ui->debugLabel->setEnabled(false);
        ui->debugCheckBox->setEnabled(false);
    }
}

