#include "deconadvanced.h"
#include "ui_deconadvanced.h"
#include "maskfilenames.h"
#include <QFileInfo>
#include <QFileDialog>

deconAdvanced::deconAdvanced(GUIvals &guiVals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deconAdvanced)
{
    ui->setupUi(this);

    // Pointer to hold the passed in vals
    gVals = &guiVals;

    // Set the vals in the window to the ones passed in
    ui->debugCheckBox->setChecked(guiVals.debug);
    if(guiVals.RLMethod == "original"){
        ui->debugLabel->setEnabled(false);
        ui->debugCheckBox->setEnabled(false);
        ui->saveStepLabel->setEnabled(false);
        ui->saveStepLineEdit->setEnabled(false);
    }
    else on_debugCheckBox_clicked(ui->debugCheckBox->isChecked());
    ui->saveStepLineEdit->setText(guiVals.saveStep);
    ui->largeMethodComboBox->setCurrentText(guiVals.largeMethod);
    ui->edgeErosionLineEdit->setText(guiVals.edgeErosion);
    ui->erodeByFTPCheckBox->setChecked(guiVals.erodeByFTP);
    ui->deconRotateCheckBox->setChecked(guiVals.deconRotate);
    ui->damperSpinBox->setValue(guiVals.dampFactor);
    if(!guiVals.scaleFactor.empty()){
        std::string scaleFactorString;
        for(const std::string &currScaleFactor : guiVals.scaleFactor) scaleFactorString.append(currScaleFactor+",");
        scaleFactorString.pop_back();
        ui->deconScaleFactorLineEdit->setText(QString::fromStdString(scaleFactorString));
    }
    ui->deconOffsetSpinBox->setValue(guiVals.deconOffset);
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
    gVals->debug = ui->debugCheckBox->isChecked();
    gVals->saveStep = ui->saveStepLineEdit->text();
    gVals->largeMethod = ui->largeMethodComboBox->currentText();
    gVals->edgeErosion = ui->edgeErosionLineEdit->text();
    gVals->erodeByFTP = ui->erodeByFTPCheckBox->isChecked();
    gVals->deconRotate = ui->deconRotateCheckBox->isChecked();
    gVals->dampFactor = ui->damperSpinBox->value();
    if(!ui->deconScaleFactorLineEdit->text().isEmpty()){
        gVals->scaleFactor.clear();
        std::stringstream s_stream(ui->deconScaleFactorLineEdit->text().toStdString());
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma
            gVals->scaleFactor.push_back(substr);
        }
    }
    gVals->deconOffset = ui->deconOffsetSpinBox->value();
    deconAdvanced::close();
}

void deconAdvanced::on_pushButton_clicked()
{
    maskFilenames mFilenames(gVals->deconMaskFns);
    mFilenames.setModal(true);
    mFilenames.exec();
}


void deconAdvanced::on_debugCheckBox_clicked(bool checked)
{
    ui->saveStepLabel->setEnabled(checked);
    ui->saveStepLineEdit->setEnabled(checked);
}

