#include "simreconmainadvanced.h"
#include "ui_simreconmainadvanced.h"

simReconMainAdvanced::simReconMainAdvanced(simReconVals& simreconVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::simReconMainAdvanced)
{
    // pointer to hold the passed in vals
    srVals = &simreconVals;

    ui->setupUi(this);

    // set the vals in the window to the ones passed in
    ui->skewAngleSpinBox->setValue(simreconVals.skewAngle);
    ui->xyPixelSizeSpinBox->setValue(simreconVals.xyPixelSize);
    ui->reverseCheckBox->setChecked(simreconVals.Reverse);
}

simReconMainAdvanced::~simReconMainAdvanced()
{
    delete ui;
}

void simReconMainAdvanced::on_cancelButton_clicked()
{
    simReconMainAdvanced::close();
}


void simReconMainAdvanced::on_submitButton_clicked()
{
    srVals->skewAngle = ui->skewAngleSpinBox->value();
    srVals->xyPixelSize = ui->xyPixelSizeSpinBox->value();
    srVals->Reverse = ui->reverseCheckBox->isChecked();
    simReconMainAdvanced::close();
}

