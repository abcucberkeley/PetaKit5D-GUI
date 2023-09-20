#include "jobadvanced.h"
#include "ui_jobadvanced.h"
#include <QFileDialog>
#include <QFileInfo>
jobAdvanced::jobAdvanced(GUIvals &guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jobAdvanced)
{
    ui->setupUi(this);

    // pointer to hold the passed in vals
    gVals = &guiVals;

    // set the vals in the window to the ones passed in
    ui->largeFileCheckBox->setChecked(guiVals.largeFile);
    ui->jobLogDirLineEdit->setText(guiVals.jobLogDir);
    ui->uuidLineEdit->setText(guiVals.uuid);
    ui->maxTrialNumSpinBox->setValue(guiVals.maxTrialNum);
    ui->unitWaitTimeSpinBox->setValue(guiVals.unitWaitTime);
    ui->minModifyTimeSpinBox->setValue(guiVals.minModifyTime);
    ui->maxModifyTimeSpinBox->setValue(guiVals.maxModifyTime);
    ui->maxWaitLoopNumSpinBox->setValue(guiVals.maxWaitLoopNum);
}

jobAdvanced::~jobAdvanced()
{
    delete ui;
}

// Close the window
void jobAdvanced::on_cancelButton_clicked()
{
    jobAdvanced::close();
}

// Close the window and save the current vals
void jobAdvanced::on_submitButton_clicked()
{
    gVals->largeFile = ui->largeFileCheckBox->isChecked();
    gVals->jobLogDir = ui->jobLogDirLineEdit->text();
    gVals->uuid = ui->uuidLineEdit->text();
    gVals->maxTrialNum = ui->maxTrialNumSpinBox->value();
    gVals->unitWaitTime = ui->unitWaitTimeSpinBox->value();
    gVals->minModifyTime = ui->minModifyTimeSpinBox->value();
    gVals->maxModifyTime = ui->maxModifyTimeSpinBox->value();
    gVals->maxWaitLoopNum = ui->maxWaitLoopNumSpinBox->value();
    jobAdvanced::close();
}

void jobAdvanced::on_jobLogDirBrowseButton_clicked()
{
    QFileInfo folder_path(QFileDialog::getExistingDirectory(this,"Select or Make and Select the Results Folder",QDir::homePath()));
    if(!folder_path.absolutePath().isEmpty()) ui->jobLogDirLineEdit->setText(folder_path.absoluteFilePath());
}

void jobAdvanced::on_jobLogDirLineEdit_textChanged(const QString &arg1)
{
    ui->jobLogDirLineEdit->setToolTip(arg1);
}
