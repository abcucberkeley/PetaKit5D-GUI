#include "largescaleprocessingsettings.h"
#include "ui_largescaleprocessingsettings.h"
#include "maskfilenames.h"
#include <sstream>


largeScaleProcessingSettings::largeScaleProcessingSettings(GUIvals& guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::largeScaleProcessingSettings)
{
    // Pointer to hold the passed in vals
    gVals = &guiVals;

    ui->setupUi(this);

    // Connect signals
    connect(ui->InputCancelButton, &QPushButton::clicked, this, &largeScaleProcessingSettings::on_cancelButton_clicked);
    connect(ui->InputSubmitButton, &QPushButton::clicked, this, &largeScaleProcessingSettings::on_submitButton_clicked);
    connect(ui->OutputCancelButton, &QPushButton::clicked, this, &largeScaleProcessingSettings::on_cancelButton_clicked);
    connect(ui->OutputSubmitButton, &QPushButton::clicked, this, &largeScaleProcessingSettings::on_submitButton_clicked);
    connect(ui->XcorrCancelButton, &QPushButton::clicked, this, &largeScaleProcessingSettings::on_cancelButton_clicked);
    connect(ui->XcorrSubmitButton, &QPushButton::clicked, this, &largeScaleProcessingSettings::on_submitButton_clicked);

    // Set the vals in the window to the ones passed in
    ui->saveMIPCheckBox->setChecked(guiVals.SaveMIP);
    ui->batchSizeYSpinBox->setValue(std::stoi(guiVals.batchSize[0]));
    ui->batchSizeXSpinBox->setValue(std::stoi(guiVals.batchSize[1]));
    ui->batchSizeZSpinBox->setValue(std::stoi(guiVals.batchSize[2]));

    ui->multiLocCheckBox->setChecked(guiVals.multiLoc);
    ui->processedDirStringLineEdit->setText(guiVals.ProcessedDirStr);
    ui->ioScanCheckBox->setChecked(guiVals.IOScan);
    ui->blockSizeYSpinBox->setValue(std::stoi(guiVals.blockSize[0]));
    ui->blockSizeXSpinBox->setValue(std::stoi(guiVals.blockSize[1]));
    ui->blockSizeZSpinBox->setValue(std::stoi(guiVals.blockSize[2]));
    ui->shardSizeYSpinBox->setValue(std::stoi(guiVals.shardSize[0]));
    ui->shardSizeXSpinBox->setValue(std::stoi(guiVals.shardSize[1]));
    ui->shardSizeZSpinBox->setValue(std::stoi(guiVals.shardSize[2]));
    ui->inputBboxCheckBox->setChecked(guiVals.InputBboxCheckBox);
    if(ui->inputBboxCheckBox->isChecked()){
        ui->inputBboxYMinSpinBox->setValue(std::stoi(guiVals.InputBbox[0]));
        ui->inputBboxXMinSpinBox->setValue(std::stoi(guiVals.InputBbox[1]));
        ui->inputBboxZMinSpinBox->setValue(std::stoi(guiVals.InputBbox[2]));
        ui->inputBboxYMaxSpinBox->setValue(std::stoi(guiVals.InputBbox[3]));
        ui->inputBboxXMaxSpinBox->setValue(std::stoi(guiVals.InputBbox[4]));
        ui->inputBboxZMaxSpinBox->setValue(std::stoi(guiVals.InputBbox[5]));
    }
    ui->tileOutBboxCheckBox->setChecked(guiVals.tileOutBboxCheckBox);
    if(ui->tileOutBboxCheckBox->isChecked()){
        ui->tileOutBboxYMinSpinBox->setValue(std::stoi(guiVals.tileOutBbox[0]));
        ui->tileOutBboxXMinSpinBox->setValue(std::stoi(guiVals.tileOutBbox[1]));
        ui->tileOutBboxZMinSpinBox->setValue(std::stoi(guiVals.tileOutBbox[2]));
        ui->tileOutBboxYMaxSpinBox->setValue(std::stoi(guiVals.tileOutBbox[3]));
        ui->tileOutBboxXMaxSpinBox->setValue(std::stoi(guiVals.tileOutBbox[4]));
        ui->tileOutBboxZMaxSpinBox->setValue(std::stoi(guiVals.tileOutBbox[5]));
    }
    ui->axisWeightYSpinBox->setValue(std::stod(guiVals.axisWeight[0]));
    ui->axisWeightXSpinBox->setValue(std::stod(guiVals.axisWeight[1]));
    ui->axisWeightZSpinBox->setValue(std::stod(guiVals.axisWeight[2]));
    ui->usePrimaryCoordsCheckBox->setChecked(guiVals.usePrimaryCoords);
    ui->edgeArtifactsSpinBox->setValue(guiVals.EdgeArtifacts.toInt());
    ui->masterComputeCheckBox->setChecked(guiVals.masterCompute);

}

largeScaleProcessingSettings::~largeScaleProcessingSettings()
{
    delete ui;
}

void largeScaleProcessingSettings::on_cancelButton_clicked()
{
    largeScaleProcessingSettings::close();
}

void largeScaleProcessingSettings::on_submitButton_clicked()
{
    gVals->SaveMIP = ui->saveMIPCheckBox->isChecked();
    gVals->batchSize[0] = ui->batchSizeYSpinBox->text().toStdString();
    gVals->batchSize[1] = ui->batchSizeXSpinBox->text().toStdString();
    gVals->batchSize[2] = ui->batchSizeZSpinBox->text().toStdString();

    gVals->multiLoc = ui->multiLocCheckBox->isChecked();
    gVals->ProcessedDirStr = ui->processedDirStringLineEdit->text();
    gVals->IOScan = ui->ioScanCheckBox->isChecked();
    gVals->blockSize[0] = ui->blockSizeYSpinBox->text().toStdString();
    gVals->blockSize[1] = ui->blockSizeXSpinBox->text().toStdString();
    gVals->blockSize[2] = ui->blockSizeZSpinBox->text().toStdString();
    gVals->shardSize[0] = ui->shardSizeYSpinBox->text().toStdString();
    gVals->shardSize[1] = ui->shardSizeXSpinBox->text().toStdString();
    gVals->shardSize[2] = ui->shardSizeZSpinBox->text().toStdString();
    gVals->InputBboxCheckBox = ui->inputBboxCheckBox->isChecked();
    if(ui->inputBboxCheckBox->isChecked()){
        gVals->InputBbox = {ui->inputBboxYMinSpinBox->text().toStdString(),
                            ui->inputBboxXMinSpinBox->text().toStdString(),
                            ui->inputBboxZMinSpinBox->text().toStdString(),
                            ui->inputBboxYMaxSpinBox->text().toStdString(),
                            ui->inputBboxXMaxSpinBox->text().toStdString(),
                            ui->inputBboxZMaxSpinBox->text().toStdString()};
    }
    gVals->tileOutBboxCheckBox = ui->tileOutBboxCheckBox->isChecked();
    if(ui->tileOutBboxCheckBox->isChecked()){
        gVals->tileOutBbox = {ui->tileOutBboxYMinSpinBox->text().toStdString(),
                              ui->tileOutBboxXMinSpinBox->text().toStdString(),
                              ui->tileOutBboxZMinSpinBox->text().toStdString(),
                              ui->tileOutBboxYMaxSpinBox->text().toStdString(),
                              ui->tileOutBboxXMaxSpinBox->text().toStdString(),
                              ui->tileOutBboxZMaxSpinBox->text().toStdString()};
    }
    gVals->axisWeight[0] = ui->axisWeightYSpinBox->text().toStdString();
    gVals->axisWeight[1] = ui->axisWeightXSpinBox->text().toStdString();
    gVals->axisWeight[2] = ui->axisWeightZSpinBox->text().toStdString();
    gVals->usePrimaryCoords = ui->usePrimaryCoordsCheckBox->isChecked();
    gVals->EdgeArtifacts = ui->edgeArtifactsSpinBox->text();
    gVals->masterCompute = ui->masterComputeCheckBox->isChecked();
    largeScaleProcessingSettings::close();
}

void largeScaleProcessingSettings::on_blockSizeCheckBox_stateChanged(int arg1)
{
    ui->blockSizeYSpinBox->setEnabled(arg1);
    ui->blockSizeXSpinBox->setEnabled(arg1);
    ui->blockSizeZSpinBox->setEnabled(arg1);
}

void largeScaleProcessingSettings::on_inputBboxCheckBox_stateChanged(int arg1)
{
    ui->inputBboxYMinSpinBox->setEnabled(arg1);
    ui->inputBboxXMinSpinBox->setEnabled(arg1);
    ui->inputBboxZMinSpinBox->setEnabled(arg1);
    ui->inputBboxYMaxSpinBox->setEnabled(arg1);
    ui->inputBboxXMaxSpinBox->setEnabled(arg1);
    ui->inputBboxZMaxSpinBox->setEnabled(arg1);
}

void largeScaleProcessingSettings::on_tileOutBboxCheckBox_stateChanged(int arg1)
{
    ui->tileOutBboxYMinSpinBox->setEnabled(arg1);
    ui->tileOutBboxXMinSpinBox->setEnabled(arg1);
    ui->tileOutBboxZMinSpinBox->setEnabled(arg1);
    ui->tileOutBboxYMaxSpinBox->setEnabled(arg1);
    ui->tileOutBboxXMaxSpinBox->setEnabled(arg1);
    ui->tileOutBboxZMaxSpinBox->setEnabled(arg1);
}


void largeScaleProcessingSettings::on_maskFilenamesButton_clicked()
{
    maskFilenames mFilenames(gVals->maskFns);
    mFilenames.setModal(true);
    mFilenames.exec();
}

