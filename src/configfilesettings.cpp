#include "configfilesettings.h"
#include "ui_configfilesettings.h"
#include "configfilecreator.h"

configFileSettings::configFileSettings(configFileVals* cFileVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configFileSettings)
{
    this->cFileVals = cFileVals;
    ui->setupUi(this);
    ui->configFileLineEdit->setText(cFileVals->configFile);
    ui->gpuConfigFileLineEdit->setText(cFileVals->gpuConfigFile);
    ui->jvmConfigLineEdit->setText(cFileVals->jvmConfigFile);
}

configFileSettings::~configFileSettings()
{
    delete ui;
}

void configFileSettings::on_submitButton_clicked()
{
    cFileVals->configFile = ui->configFileLineEdit->text();
    cFileVals->gpuConfigFile = ui->gpuConfigFileLineEdit->text();
    cFileVals->jvmConfigFile = ui->jvmConfigLineEdit->text();
    configFileSettings::close();
}


void configFileSettings::on_cancelButton_clicked()
{
    configFileSettings::close();
}


void configFileSettings::on_createAConfigFileButton_clicked()
{
    configFileCreator cFileCreator(cFileVals);
    cFileCreator.setModal(true);
    cFileCreator.exec();
}

