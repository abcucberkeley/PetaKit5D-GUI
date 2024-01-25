#include <QJsonDocument>
#include "configfilecreator.h"
#include "ui_configfilecreator.h"
#include "submissionchecks.h"

configFileCreator::configFileCreator(configFileVals* cFileVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configFileCreator)
{
    this->cFileVals = cFileVals;
    ui->setupUi(this);
    ui->bashLaunchStrLineEdit->setText(cFileVals->BashLaunchStr);
    ui->gnuParallelCheckBox->setChecked(cFileVals->GNUparallel);
    ui->mccMasterStrLineEdit->setText(cFileVals->MCCMasterStr);
    ui->mcrParamLineEdit->setText(cFileVals->MCRParam);
    ui->memPerCPUDoubleSpinBox->setValue(cFileVals->MemPerCPU);
    ui->slurmParamLineEdit->setText(cFileVals->SlurmParam);
    ui->jobTimeLimitSpinBox->setValue(cFileVals->jobTimeLimit);
    ui->masterComputeCheckBox->setChecked(cFileVals->masterCompute);
    ui->maxCPUNumSpinBox->setValue(cFileVals->maxCPUNum);
    ui->maxJobNumSpinBox->setValue(cFileVals->maxJobNum);
    ui->minCPUNumSpinBox->setValue(cFileVals->minCPUNum);
    ui->wholeNodeJobCheckBox->setChecked(cFileVals->wholeNodeJob);
}

configFileCreator::~configFileCreator()
{
    cFileVals->BashLaunchStr = ui->bashLaunchStrLineEdit->text();
    cFileVals->GNUparallel = ui->gnuParallelCheckBox->isChecked();
    cFileVals->MCCMasterStr = ui->mccMasterStrLineEdit->text();
    cFileVals->MCRParam = ui->mcrParamLineEdit->text();
    cFileVals->MemPerCPU = ui->memPerCPUDoubleSpinBox->value();
    cFileVals->SlurmParam = ui->slurmParamLineEdit->text();
    cFileVals->jobTimeLimit  = ui->jobTimeLimitSpinBox->value();
    cFileVals->masterCompute = ui->masterComputeCheckBox->isChecked();
    cFileVals->maxCPUNum = ui->maxCPUNumSpinBox->value();
    cFileVals->maxJobNum = ui->maxJobNumSpinBox->value();
    cFileVals->minCPUNum = ui->minCPUNumSpinBox->value();
    cFileVals->wholeNodeJob = ui->wholeNodeJobCheckBox->isChecked();
    delete ui;
}

void configFileCreator::on_saveFileButton_clicked()
{
    if(!ui->jsonConfigFileNameLineEdit->text().endsWith(".json")){
        messageBoxError("The config filename must end in .json");
        return;
    }
    if(ui->jsonConfigFileNameLineEdit->text().isEmpty()){
        messageBoxError("Please set a config filename");
        return;
    }

    // Create a json object
    QJsonObject jsonObj;
    jsonObj["BashLaunchStr"] = ui->bashLaunchStrLineEdit->text();
    jsonObj["GNUparallel"] = ui->gnuParallelCheckBox->isChecked();
    jsonObj["MCCMasterStr"] = ui->mccMasterStrLineEdit->text();
    jsonObj["MCRParam"] = ui->mcrParamLineEdit->text();
    jsonObj["MemPerCPU"] = ui->memPerCPUDoubleSpinBox->value();
    jsonObj["SlurmParam"] = ui->slurmParamLineEdit->text();
    jsonObj["jobTimeLimit"] = ui->jobTimeLimitSpinBox->value();
    jsonObj["masterCompute"] = ui->masterComputeCheckBox->isChecked();
    jsonObj["maxCPUNum"] = ui->maxCPUNumSpinBox->value();
    jsonObj["maxJobNum"] = ui->maxJobNumSpinBox->value();
    jsonObj["minCPUNum"] = ui->minCPUNumSpinBox->value();
    jsonObj["wholeNodeJob"] = ui->wholeNodeJobCheckBox->isChecked();

    QJsonDocument jsonDoc(jsonObj);

    QFile file(ui->jsonConfigFileNameLineEdit->text());
    if (!file.open(QIODevice::WriteOnly)) {
        messageBoxError("Unable to open "+ui->jsonConfigFileNameLineEdit->text()+" for writing. Check your path and permissions.");
        return;
    }
    file.write(jsonDoc.toJson());
    file.close();

    messageBoxSuccess(this, "File succesfully saved to: "+ui->jsonConfigFileNameLineEdit->text());
}


void configFileCreator::on_exitButton_clicked()
{
    configFileCreator::close();
}


void configFileCreator::on_jsonConfigFileNameButton_clicked()
{
    QFileInfo file_path(QFileDialog::getSaveFileName(this,"Specify the full path to save the config file to"));
    if(!file_path.absoluteFilePath().isEmpty()){
        ui->jsonConfigFileNameLineEdit->setText(file_path.absoluteFilePath());
        //mostRecentDir = file_path.absolutePath();
    }
}

