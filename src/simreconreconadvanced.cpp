#include "simreconreconadvanced.h"
#include "ui_simreconreconadvanced.h"

simReconReconAdvanced::simReconReconAdvanced(simReconVals& simreconVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::simReconReconAdvanced)
{
    ui->setupUi(this);
    srVals = &simreconVals;
    ui->isLatticeCheckBox->setChecked(simreconVals.islattice);
    ui->naDetLineEdit->setText(QString::number(simreconVals.NA_det));
    ui->naExtLineEdit->setText(QString::number(simreconVals.NA_ext));
    ui->nimmLineEdit->setText(QString::number(simreconVals.nimm));
    ui->wvlEmLineEdit->setText(QString::number(simreconVals.wvl_em));
    ui->wvlExtLineEdit->setText(QString::number(simreconVals.wvl_ext));
    ui->wLineEdit->setText(QString::number(simreconVals.w));
    ui->normalizeOrientationsCheckBox->setChecked(simreconVals.normalize_orientations);
    ui->resultsDirNameLineEdit->setText(simreconVals.resultsDirName);
    ui->perdecompCheckBox->setChecked(simreconVals.perdecomp);
    ui->edgeTaperCheckBox->setChecked(simreconVals.edgeTaper);
    ui->edgeTaperValLineEdit->setText(QString::number(simreconVals.edgeTaperVal));
    ui->intThreshLineEdit->setText(QString::number(simreconVals.intThresh));
    ui->occThreshLineEdit->setText(QString::number(simreconVals.occThresh));
    ui->useGPUCheckBox->setChecked(simreconVals.useGPU);
    ui->gpuPrecisionComboBox->setCurrentText(simreconVals.gpuPrecision);
    ui->overlapLineEdit->setText(QString::number(simreconVals.Overlap));
    ui->chunkSizeYSpinBox->setValue(simreconVals.ChunkSize[0]);
    ui->chunkSizeXSpinBox->setValue(simreconVals.ChunkSize[1]);
    ui->chunkSizeZSpinBox->setValue(simreconVals.ChunkSize[2]);
    ui->reconBatchNumLineEdit->setText(QString::number(simreconVals.reconBatchNum));
}

simReconReconAdvanced::~simReconReconAdvanced()
{
    delete ui;
}

void simReconReconAdvanced::on_cancelButton_clicked()
{
    simReconReconAdvanced::close();
}


void simReconReconAdvanced::on_submitButton_clicked()
{
    srVals->islattice = ui->isLatticeCheckBox->isChecked();
    srVals->NA_det = ui->naDetLineEdit->text().toDouble();
    srVals->NA_ext = ui->naExtLineEdit->text().toDouble();
    srVals->nimm = ui->nimmLineEdit->text().toDouble();
    srVals->wvl_em = ui->wvlEmLineEdit->text().toDouble();
    srVals->wvl_ext = ui->wvlExtLineEdit->text().toDouble();
    srVals->w = ui->wLineEdit->text().toDouble();
    srVals->normalize_orientations = ui->normalizeOrientationsCheckBox->isChecked();
    srVals->resultsDirName = ui->resultsDirNameLineEdit->text();
    srVals->perdecomp = ui->perdecompCheckBox->isChecked();
    srVals->edgeTaper = ui->edgeTaperCheckBox->isChecked();
    srVals->edgeTaperVal = ui->edgeTaperValLineEdit->text().toDouble();
    srVals->intThresh = ui->intThreshLineEdit->text().toDouble();
    srVals->occThresh = ui->occThreshLineEdit->text().toDouble();
    srVals->useGPU = ui->useGPUCheckBox->isChecked();
    srVals->gpuPrecision = ui->gpuPrecisionComboBox->currentText();
    srVals->Overlap = ui->overlapLineEdit->text().toDouble();
    srVals->ChunkSize[0] = ui->chunkSizeYSpinBox->value();
    srVals->ChunkSize[1] = ui->chunkSizeXSpinBox->value();
    srVals->ChunkSize[2] = ui->chunkSizeZSpinBox->value();
    srVals->reconBatchNum = ui->reconBatchNumLineEdit->text().toDouble();

    simReconReconAdvanced::close();
}

