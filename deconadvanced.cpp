#include "deconadvanced.h"
#include "ui_deconadvanced.h"
#include <QFileInfo>
#include <QFileDialog>

deconAdvanced::deconAdvanced(GUIvals &guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deconAdvanced)
{
    ui->setupUi(this);

    // pointer to hold the passed in vals
    gVals = &guiVals;

    // set the vals in the window to the ones passed in
    ui->cppDeconPathLineEdit->setText(QString::fromStdString(guiVals.cppDeconPath));
    ui->loadModulesLineEdit->setText(QString::fromStdString(guiVals.loadModules));
    ui->cudaDeconPathLineEdit->setText(QString::fromStdString(guiVals.cudaDeconPath));
    ui->otfgenPathLineEdit->setText(QString::fromStdString(guiVals.OTFGENPath));

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
