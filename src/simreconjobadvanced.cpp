#include "simreconjobadvanced.h"
#include "ui_simreconjobadvanced.h"

simReconJobAdvanced::simReconJobAdvanced(simReconVals& simreconVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::simReconJobAdvanced)
{
    ui->setupUi(this);

    srVals = &simreconVals;
    ui->jobLogDirLineEdit->setText(simreconVals.jobLogDir);
    ui->uuidLineEdit->setText(simreconVals.uuid);
    ui->maxTrialNumSpinBox->setValue(simreconVals.maxTrialNum);
    ui->unitWaitTimeSpinBox->setValue(simreconVals.unitWaitTime);
    ui->parPoolSizeSpinBox->setValue(simreconVals.parPoolSize);
}

simReconJobAdvanced::~simReconJobAdvanced()
{
    delete ui;
}

void simReconJobAdvanced::on_cancelButton_clicked()
{
    simReconJobAdvanced::close();
}


void simReconJobAdvanced::on_submitButton_clicked()
{
    srVals->jobLogDir = ui->jobLogDirLineEdit->text();
    srVals->uuid = ui->uuidLineEdit->text();
    srVals->maxTrialNum = ui->maxTrialNumSpinBox->value();
    srVals->unitWaitTime = ui->unitWaitTimeSpinBox->value();
    srVals->parPoolSize = ui->parPoolSizeSpinBox->value();
    srVals->maxModifyTime = ui->maxModifyTimeSpinBox->value();
    simReconJobAdvanced::close();
}

