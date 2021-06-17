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
    ui->cppDeconPathLineEdit->setText(QString::fromStdString(guiVals.cppDeconPath));
    ui->loadModulesLineEdit->setText(QString::fromStdString(guiVals.loadModules));
    ui->cudaDeconPathLineEdit->setText(QString::fromStdString(guiVals.cudaDeconPath));
    ui->otfgenPathLineEdit->setText(QString::fromStdString(guiVals.OTFGENPath));
    if(guiVals.RLMethod == "original") ui->rlMethodOriginalRadioButton->setChecked(true);
    else if(guiVals.RLMethod == "simplified") ui->rlMethodSimplifiedRadioButton->setChecked(true);
    else if (guiVals.RLMethod == "cudagen") ui->rlMethodCudaGenRadioButton->setChecked(true);
    ui->fixIterCheckBox->setChecked(guiVals.fixIter);
    ui->errThreshLineEdit->setText(QString::number(guiVals.errThresh));
    ui->debugCheckBox->setChecked(guiVals.debug);
    ui->gpuJobCheckBox->setChecked(guiVals.gpuJob);

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
    gVals->cppDeconPath = ui->cppDeconPathLineEdit->text().toStdString();
    gVals->loadModules = ui->loadModulesLineEdit->text().toStdString();
    gVals->cudaDeconPath = ui->cudaDeconPathLineEdit->text().toStdString();
    gVals->OTFGENPath = ui->otfgenPathLineEdit->text().toStdString();
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
    if(file_path.absoluteFilePath().toStdString() != "") ui->cppDeconPathLineEdit->setText(file_path.absoluteFilePath());
}

void deconAdvanced::on_cppDeconPathLineEdit_textChanged(const QString &arg1)
{
    ui->cppDeconPathLineEdit->setToolTip(arg1);
}

void deconAdvanced::on_cudaDeconPathBrowseButton_clicked()
{
    QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the CUDA Decon File",QDir::homePath());
    if(file_path.absoluteFilePath().toStdString() != "") ui->cudaDeconPathLineEdit->setText(file_path.absoluteFilePath());
}

void deconAdvanced::on_cudaDeconPathLineEdit_textChanged(const QString &arg1)
{
    ui->cudaDeconPathLineEdit->setToolTip(arg1);
}

void deconAdvanced::on_otfgenPathBrowseButton_clicked()
{
    QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the OTFGEN File",QDir::homePath());
    if(file_path.absoluteFilePath().toStdString() != "") ui->otfgenPathLineEdit->setText(file_path.absoluteFilePath());
}

void deconAdvanced::on_otfgenPathLineEdit_textChanged(const QString &arg1)
{
    ui->otfgenPathLineEdit->setToolTip(arg1);
}
