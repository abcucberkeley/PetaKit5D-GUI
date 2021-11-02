#include "simreconreconadvanced.h"
#include "ui_simreconreconadvanced.h"

simReconReconAdvanced::simReconReconAdvanced(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::simReconReconAdvanced)
{
    ui->setupUi(this);
}

simReconReconAdvanced::~simReconReconAdvanced()
{
    delete ui;
}
