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
    ui->cppDeconPathLineEdit->setText(guiVals.cppDeconPath);
    ui->loadModulesLineEdit->setText(guiVals.loadModules);
    ui->cudaDeconPathLineEdit->setText(guiVals.cudaDeconPath);
    ui->otfgenPathLineEdit->setText(guiVals.OTFGENPath);
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
    else if (guiVals.RLMethod == "cudagen") ui->rlMethodCudaGenRadioButton->setChecked(true);
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
    gVals->cppDeconPath = ui->cppDeconPathLineEdit->text();
    gVals->loadModules = ui->loadModulesLineEdit->text();
    gVals->cudaDeconPath = ui->cudaDeconPathLineEdit->text();
    gVals->OTFGENPath = ui->otfgenPathLineEdit->text();
    if(ui->rlMethodOriginalRadioButton->isChecked()) gVals->RLMethod = "original";
    else if (ui->rlMethodSimplifiedRadioButton->isChecked()) gVals->RLMethod = "simplified";
    else if (ui->rlMethodCudaGenRadioButton->isChecked()) gVals->RLMethod = "cudagen";
    gVals->fixIter = ui->fixIterCheckBox->isChecked();
    gVals->errThresh = ui->errThreshLineEdit->text().toDouble();
    gVals->debug = ui->debugCheckBox->isChecked();
    gVals->gpuJob = ui->gpuJobCheckBox->isChecked();
    deconAdvanced::close();
}

void deconAdvanced::on_cppDeconPathBrowseButton_clicked()
{
    QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the CPP Decon File",QDir::homePath());
    if(!file_path.absoluteFilePath().isEmpty()) ui->cppDeconPathLineEdit->setText(file_path.absoluteFilePath());
}

void deconAdvanced::on_cppDeconPathLineEdit_textChanged(const QString &arg1)
{
    ui->cppDeconPathLineEdit->setToolTip(arg1);
}

void deconAdvanced::on_cudaDeconPathBrowseButton_clicked()
{
    QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the CUDA Decon File",QDir::homePath());
    if(!file_path.absoluteFilePath().isEmpty()) ui->cudaDeconPathLineEdit->setText(file_path.absoluteFilePath());
}

void deconAdvanced::on_cudaDeconPathLineEdit_textChanged(const QString &arg1)
{
    ui->cudaDeconPathLineEdit->setToolTip(arg1);
}

void deconAdvanced::on_otfgenPathBrowseButton_clicked()
{
    QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the OTFGEN File",QDir::homePath());
    if(!file_path.absoluteFilePath().isEmpty()) ui->otfgenPathLineEdit->setText(file_path.absoluteFilePath());
}

void deconAdvanced::on_otfgenPathLineEdit_textChanged(const QString &arg1)
{
    ui->otfgenPathLineEdit->setToolTip(arg1);
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

