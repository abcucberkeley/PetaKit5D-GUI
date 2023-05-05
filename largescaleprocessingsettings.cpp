#include "largescaleprocessingsettings.h"
#include "ui_largescaleprocessingsettings.h"

largeScaleProcessingSettings::largeScaleProcessingSettings(GUIvals& guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::largeScaleProcessingSettings)
{
    // Pointer to hold the passed in vals
    gVals = &guiVals;

    ui->setupUi(this);

    // Set the vals in the window to the ones passed in
    ui->saveMIPCheckBox->setChecked(guiVals.SaveMIP);
    ui->batchSizeYSpinBox->setValue(std::stoi(guiVals.BatchSize[0]));
    ui->batchSizeXSpinBox->setValue(std::stoi(guiVals.BatchSize[1]));
    ui->batchSizeZSpinBox->setValue(std::stoi(guiVals.BatchSize[2]));

    ui->multiLocCheckBox->setChecked(guiVals.multiLoc);
    ui->processedDirStringLineEdit->setText(guiVals.ProcessedDirStr);
    ui->stitchInfoFullpathLineEdit->setText(guiVals.stitchInfoFullpath);
    ui->parseSettingFileCheckBox->setChecked(guiVals.parseSettingFile);
    ui->ioScanCheckBox->setChecked(guiVals.IOScan);
    ui->blockSizeCheckBox->setChecked(guiVals.blockSizeCheckBox);
    ui->blockSizeYSpinBox->setValue(std::stoi(guiVals.blockSize[0]));
    ui->blockSizeXSpinBox->setValue(std::stoi(guiVals.blockSize[1]));
    ui->blockSizeZSpinBox->setValue(std::stoi(guiVals.blockSize[2]));
    ui->zarrSubSizeCheckBox->setChecked(guiVals.zarrSubSizeCheckBox);
    ui->zarrSubSizeYSpinBox->setValue(std::stoi(guiVals.zarrSubSize[0]));
    ui->zarrSubSizeXSpinBox->setValue(std::stoi(guiVals.zarrSubSize[1]));
    ui->zarrSubSizeZSpinBox->setValue(std::stoi(guiVals.zarrSubSize[2]));
    ui->inputBboxCheckBox->setChecked(guiVals.InputBboxCheckBox);
    ui->inputBboxYMinSpinBox->setValue(std::stoi(guiVals.InputBbox[0]));
    ui->inputBboxXMinSpinBox->setValue(std::stoi(guiVals.InputBbox[1]));
    ui->inputBboxZMinSpinBox->setValue(std::stoi(guiVals.InputBbox[2]));
    ui->inputBboxYMaxSpinBox->setValue(std::stoi(guiVals.InputBbox[3]));
    ui->inputBboxXMaxSpinBox->setValue(std::stoi(guiVals.InputBbox[4]));
    ui->inputBboxZMaxSpinBox->setValue(std::stoi(guiVals.InputBbox[5]));
    ui->tileOutBboxCheckBox->setChecked(guiVals.tileOutBboxCheckBox);
    ui->tileOutBboxYMinSpinBox->setValue(std::stoi(guiVals.tileOutBbox[0]));
    ui->tileOutBboxXMinSpinBox->setValue(std::stoi(guiVals.tileOutBbox[1]));
    ui->tileOutBboxZMinSpinBox->setValue(std::stoi(guiVals.tileOutBbox[2]));
    ui->tileOutBboxYMaxSpinBox->setValue(std::stoi(guiVals.tileOutBbox[3]));
    ui->tileOutBboxXMaxSpinBox->setValue(std::stoi(guiVals.tileOutBbox[4]));
    ui->tileOutBboxZMaxSpinBox->setValue(std::stoi(guiVals.tileOutBbox[5]));
    ui->tileOffsetSpinBox->setValue(guiVals.TileOffset.toInt());
    ui->resolutionXYPixelSizeSpinBox->setValue(std::stod(guiVals.Resolution[0]));
    ui->resolutionDZSpinBox->setValue(std::stod(guiVals.Resolution[1]));
    ui->overlapTypeComboBox->setCurrentText(guiVals.overlapType);
    ui->xyMaxOffsetSpinBox->setValue(guiVals.xyMaxOffset.toInt());
    ui->zMaxOffsetSpinBox->setValue(guiVals.zMaxOffset.toInt());
    ui->xcorrDownsampleYSpinBox->setValue(std::stoi(guiVals.xcorrDownsample[0]));
    ui->xcorrDownsampleXSpinBox->setValue(std::stoi(guiVals.xcorrDownsample[1]));
    ui->xcorrDownsampleZSpinBox->setValue(std::stoi(guiVals.xcorrDownsample[2]));
    ui->xcorrThreshSpinBox->setValue(guiVals.xcorrThresh.toDouble());
    ui->zNormalizeCheckBox->setChecked(guiVals.zNormalize);
    std::string tString;
    for(std::string &i : guiVals.timepoints){
        tString.append(i);
        tString.append(",");
    }
    if(!tString.empty()){
        tString.pop_back();
        ui->timepointsLineEdit->setText(QString::fromStdString(tString));
    }
    ui->shiftMethodComboBox->setCurrentText(guiVals.shiftMethod);
    ui->axisWeightYSpinBox->setValue(std::stod(guiVals.axisWeight[0]));
    ui->axisWeightXSpinBox->setValue(std::stod(guiVals.axisWeight[1]));
    ui->axisWeightZSpinBox->setValue(std::stod(guiVals.axisWeight[2]));
    ui->groupFileLineEdit->setText(guiVals.groupFile);
    ui->usePrimaryCoordsCheckBox->setChecked(guiVals.usePrimaryCoords);
    ui->edgeArtifactsSpinBox->setValue(guiVals.EdgeArtifacts.toInt());
    ui->bigStitchDataCheckBox->setChecked(guiVals.bigStitchData);
    ui->processFunPathLineEdit->setText(guiVals.processFunPath);
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
    gVals->BatchSize[0] = ui->batchSizeYSpinBox->text().toStdString();
    gVals->BatchSize[1] = ui->batchSizeXSpinBox->text().toStdString();
    gVals->BatchSize[2] = ui->batchSizeZSpinBox->text().toStdString();

    gVals->multiLoc = ui->multiLocCheckBox->isChecked();
    gVals->ProcessedDirStr = ui->processedDirStringLineEdit->text();
    gVals->stitchInfoFullpath = ui->stitchInfoFullpathLineEdit->text();
    gVals->parseSettingFile = ui->parseSettingFileCheckBox->isChecked();
    gVals->IOScan = ui->ioScanCheckBox->isChecked();
    gVals->blockSizeCheckBox = ui->blockSizeCheckBox->isChecked();
    gVals->blockSize[0] = ui->blockSizeYSpinBox->text().toStdString();
    gVals->blockSize[1] = ui->blockSizeXSpinBox->text().toStdString();
    gVals->blockSize[2] = ui->blockSizeZSpinBox->text().toStdString();
    gVals->zarrSubSizeCheckBox = ui->zarrSubSizeCheckBox->isChecked();
    gVals->zarrSubSize[0] = ui->zarrSubSizeYSpinBox->text().toStdString();
    gVals->zarrSubSize[1] = ui->zarrSubSizeXSpinBox->text().toStdString();
    gVals->zarrSubSize[2] = ui->zarrSubSizeZSpinBox->text().toStdString();
    gVals->InputBboxCheckBox = ui->inputBboxCheckBox->isChecked();
    gVals->InputBbox[0] = ui->inputBboxYMinSpinBox->text().toStdString();
    gVals->InputBbox[1] = ui->inputBboxXMinSpinBox->text().toStdString();
    gVals->InputBbox[2] = ui->inputBboxZMinSpinBox->text().toStdString();
    gVals->InputBbox[3] = ui->inputBboxYMaxSpinBox->text().toStdString();
    gVals->InputBbox[4] = ui->inputBboxXMaxSpinBox->text().toStdString();
    gVals->InputBbox[5] = ui->inputBboxZMaxSpinBox->text().toStdString();
    gVals->tileOutBboxCheckBox = ui->tileOutBboxCheckBox->isChecked();
    gVals->tileOutBbox[0] = ui->tileOutBboxYMinSpinBox->text().toStdString();
    gVals->tileOutBbox[1] = ui->tileOutBboxXMinSpinBox->text().toStdString();
    gVals->tileOutBbox[2] = ui->tileOutBboxZMinSpinBox->text().toStdString();
    gVals->tileOutBbox[3] = ui->tileOutBboxYMaxSpinBox->text().toStdString();
    gVals->tileOutBbox[4] = ui->tileOutBboxXMaxSpinBox->text().toStdString();
    gVals->tileOutBbox[5] = ui->tileOutBboxZMaxSpinBox->text().toStdString();
    gVals->TileOffset = ui->tileOffsetSpinBox->text();
    gVals->Resolution[0] = ui->resolutionXYPixelSizeSpinBox->text().toStdString();
    gVals->Resolution[1] = ui->resolutionDZSpinBox->text().toStdString();
    gVals->overlapType = ui->overlapTypeComboBox->currentText();
    gVals->xyMaxOffset = ui->xyMaxOffsetSpinBox->text();
    gVals->zMaxOffset = ui->zMaxOffsetSpinBox->text();
    gVals->xcorrDownsample[0] = ui->xcorrDownsampleYSpinBox->text().toStdString();
    gVals->xcorrDownsample[1] = ui->xcorrDownsampleXSpinBox->text().toStdString();
    gVals->xcorrDownsample[2] = ui->xcorrDownsampleZSpinBox->text().toStdString();
    gVals->xcorrThresh = ui->xcorrThreshSpinBox->text();
    gVals->zNormalize = ui->zNormalizeCheckBox->isChecked();
    gVals->timepoints.clear();
    std::stringstream s_stream(ui->timepointsLineEdit->text().toStdString());
    while(s_stream.good()) {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        gVals->timepoints.push_back(substr);
    }
    gVals->shiftMethod = ui->shiftMethodComboBox->currentText();
    gVals->axisWeight[0] = ui->axisWeightYSpinBox->text().toStdString();
    gVals->axisWeight[1] = ui->axisWeightXSpinBox->text().toStdString();
    gVals->axisWeight[2] = ui->axisWeightZSpinBox->text().toStdString();
    gVals->groupFile = ui->groupFileLineEdit->text();
    gVals->usePrimaryCoords = ui->usePrimaryCoordsCheckBox->isChecked();
    gVals->EdgeArtifacts = ui->edgeArtifactsSpinBox->text();
    gVals->bigStitchData = ui->bigStitchDataCheckBox->isChecked();
    gVals->processFunPath = ui->processFunPathLineEdit->text();
    gVals->masterCompute = ui->masterComputeCheckBox->isChecked();
    largeScaleProcessingSettings::close();
}


void largeScaleProcessingSettings::on_blockSizeCheckBox_stateChanged(int arg1)
{
    ui->blockSizeYSpinBox->setEnabled(arg1);
    ui->blockSizeXSpinBox->setEnabled(arg1);
    ui->blockSizeZSpinBox->setEnabled(arg1);
}


void largeScaleProcessingSettings::on_zarrSubSizeCheckBox_stateChanged(int arg1)
{
    ui->zarrSubSizeYSpinBox->setEnabled(arg1);
    ui->zarrSubSizeXSpinBox->setEnabled(arg1);
    ui->zarrSubSizeZSpinBox->setEnabled(arg1);
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

