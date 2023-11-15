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
    ui->fixIterCheckBox->setChecked(guiVals.fixIter);
    ui->errThreshLineEdit->setText(QString::number(guiVals.errThresh));
    ui->debugCheckBox->setChecked(guiVals.debug);
    ui->gpuJobCheckBox->setChecked(guiVals.gpuJob);
    if(guiVals.RLMethod != "simplified"){
        ui->fixIterLabel->setEnabled(false);
        ui->fixIterCheckBox->setEnabled(false);
        ui->errThreshLabel->setEnabled(false);
        ui->errThreshLineEdit->setEnabled(false);
        ui->debugLabel->setEnabled(false);
        ui->debugCheckBox->setEnabled(false);
    }
    ui->largeMethodComboBox->setCurrentText(guiVals.largeMethod);
    ui->deconRotateCheckBox->setChecked(guiVals.deconRotate);
    ui->rotatePSFCheckBox->setChecked(guiVals.rotatePSF);
    ui->damperSpinBox->setValue(guiVals.damper);
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
    gVals->fixIter = ui->fixIterCheckBox->isChecked();
    gVals->errThresh = ui->errThreshLineEdit->text().toDouble();
    gVals->debug = ui->debugCheckBox->isChecked();
    gVals->gpuJob = ui->gpuJobCheckBox->isChecked();
    gVals->largeMethod = ui->largeMethodComboBox->currentText();
    gVals->deconRotate = ui->deconRotateCheckBox->isChecked();
    gVals->rotatePSF = ui->rotatePSFCheckBox->isChecked();
    gVals->damper = ui->damperSpinBox->value();
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

