#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainadvanced.h"
#include "dsradvanced.h"
#include "deconadvanced.h"
#include "jobadvanced.h"
#include "datapaths.h"
#include "consoleoutput.h"
#include <thread>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QThread>
#include <QMessageBox>
#include <QTimer>

using namespace matlab::engine;
using SBuf = std::basic_stringbuf<char16_t>;

void printFromBuf(const std::shared_ptr<SBuf> buf)
{
    //Get text from buf
    auto text_ = buf->str();
    std::cout << "*" << convertUTF16StringToUTF8String(text_)
        << "*" << std::endl;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set the tabs widget as the main Widget
    this->setCentralWidget(ui->tabWidget);

    // Set a variable to see how many threads the user can use for matlab
    QString maxCPU = QString::fromStdString(ui->maxCPUs->text().toStdString()+std::to_string(QThread::idealThreadCount()-1));
    ui->maxCPUs->setText(maxCPU);

    // Threading
    mThread = new matlabThread(this);
    connect(this, &MainWindow::jobStart, mThread, &matlabThread::onJobStart);
    mThread->start(QThread::LowPriority);

    // Disable all tabs except the main one on startup
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->DSR),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Stitch),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Decon),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Job),false);

    // Make the progress bar for the MATLAB job invisible initially
    ui->jobProgressBar->setVisible(false);
    ui->jobProgressBarLabel->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;

    // If the thread is not done, kill it (This will have to change later because it is dangerous)
    if(!mThread->isFinished()) mThread->terminate();
}

// Open DSR Advanced Settings
void MainWindow::on_dsrAdvancedSettingsButton_clicked()
{
    DSRadvanced dsrAdvanced(guiVals);
    dsrAdvanced.setModal(true);
    dsrAdvanced.exec();
}

// Open Decon Advanced Settings
void MainWindow::on_deconAdvancedSettingsButton_clicked()
{
    deconAdvanced dAdvanced(guiVals);
    dAdvanced.setModal(true);
    dAdvanced.exec();
}

// Open Job Advanced Settings
void MainWindow::on_jobAdvancedSettingsButton_clicked()
{
   jobAdvanced jAdvanced(guiVals);
   jAdvanced.setModal(true);
   jAdvanced.exec();
}

// Submit settings
void MainWindow::on_submitButton_clicked()
{
    if(dPaths.size() == 0){
    QMessageBox messageBox;
    messageBox.warning(0,"Error","No data paths are set");
    messageBox.setFixedSize(500,200);
    return;
    }

    // Make it so the user can't change tabs while the job is running
    //ui->jobPreviousButton->setEnabled(false);
    ui->submitButton->setEnabled(false);
    ui->jobAdvancedSettingsButton->setEnabled(false);

    // Turn on progress bar
    //ui->jobProgressBar->setVisible(true);
    //ui->jobProgressBarLabel->setVisible(true);

    // Update Progress Bar
    ui->jobProgressBar->setValue(20);
    ui->jobProgressBarLabel->setText("Moving Data");

    // We need this to convert C++ vars to MATLAB vars
    matlab::data::ArrayFactory factory;

    // outA is the number of outputs (always zero) and data is the structure to hold the pipeline settings
    const size_t outA = 0;
    std::vector<matlab::data::Array> data;

    // We have to push a lot of things into our data array one at a time
    // As far as I know there is no way around this, it's just the nature of how this API and our current pipeline are setup

    // Data Paths
    matlab::data::CellArray dataPaths_exps = factory.createCellArray({1,dPaths.size()});
    for(size_t i = 0; i < dPaths.size(); i++){
        dataPaths_exps[i] = factory.createCharArray(dPaths.at(i));
    }
    data.push_back(dataPaths_exps);

    // Main Settings
    data.push_back(factory.createCharArray("Overwrite"));
    data.push_back(factory.createScalar<bool>(ui->deskewOverwriteDataCheckBox->isChecked() || ui->rotateOverwriteDataCheckBox->isChecked() || ui->deskewAndRotateOverwriteDataCheckBox->isChecked() || ui->stitchOverwriteDataCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Streaming"));
    data.push_back(factory.createScalar<bool>(ui->streamingCheckBox->isChecked()));

    data.push_back(factory.createCharArray("ChannelPatterns"));
    data.push_back(factory.createCellArray({1,3},factory.createCharArray("CamA_ch0"),factory.createCharArray("CamB_ch1"),factory.createCharArray("CamB_ch1")));

    // Currently not used
    //data.push_back(factory.createCharArray("Channels"));
    //data.push_back(factory.createArray<uint64_t>({1,3},{488,560,642}));

    data.push_back(factory.createCharArray("SkewAngle"));
    data.push_back(factory.createScalar<double>(guiVals.skewAngle));

    data.push_back(factory.createCharArray("dz"));
    data.push_back(factory.createScalar<double>(ui->dzLineEdit->text().toDouble()));

    data.push_back(factory.createCharArray("xyPixelSize"));
    data.push_back(factory.createScalar<double>(guiVals.xyPixelSize));

    data.push_back(factory.createCharArray("Reverse"));
    data.push_back(factory.createScalar<bool>(guiVals.Reverse));

    data.push_back(factory.createCharArray("ObjectiveScan"));
    data.push_back(factory.createScalar<bool>(ui->objectiveScanCheckBox->isChecked()));

    data.push_back(factory.createCharArray("sCMOSCameraFlip"));
    data.push_back(factory.createScalar<bool>(guiVals.sCMOSCameraFlip));

    // This needs to change
    data.push_back(factory.createCharArray("Save16bit"));
    data.push_back(factory.createArray<bool>({1,4},{true,ui->stitchSave16BitCheckBox->isChecked(),true,true}));

    // This needs to change
    //data.push_back(factory.createCharArray("onlyFirstTP"));
    //data.push_back(factory.createScalar<bool>(ui->onlyFirstTPCheckBox->isChecked()));


    // Pipeline Settings
    data.push_back(factory.createCharArray("Deskew"));
    data.push_back(factory.createScalar<bool>(ui->deskewCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Rotate"));
    data.push_back(factory.createScalar<bool>(ui->rotateCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Stitch"));
    data.push_back(factory.createScalar<bool>(ui->stitchCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Decon"));
    data.push_back(factory.createScalar<bool>(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked()));

    //data.push_back(factory.createCharArray("RotateAfterDecon"));
    //data.push_back(factory.createScalar<bool>(ui->rotateAfterDeconCheckBox->isChecked()));


    // DSR Settings
    data.push_back(factory.createCharArray("parseSettingFile"));
    data.push_back(factory.createScalar<bool>(ui->parseSettingsFileCheckBox->isChecked()));

    data.push_back(factory.createCharArray("flipZstack"));
    data.push_back(factory.createScalar<bool>(ui->flipZStackCheckBox->isChecked()));

    // Probably removing this
    //data.push_back(factory.createCharArray("DSRCombined"));
    //data.push_back(factory.createScalar<bool>(ui->dsrCombinedCheckBox->isChecked()));

    data.push_back(factory.createCharArray("LLFFCorrection"));
    data.push_back(factory.createScalar<bool>(ui->llffCorrectionCheckBox->isChecked()));

    // Change these next two to not be hardcoded
    //data.push_back(factory.createCharArray("LSImagePaths"));
    //data.push_back(factory.createCellArray({1,3},guiVals.LSImagePaths.at(0),guiVals.LSImagePaths.at(1),guiVals.LSImagePaths.at(2)));

    //data.push_back(factory.createCharArray("BackgroundPaths"));
    //data.push_back(factory.createCellArray({1,3},guiVals.BackgroundPaths.at(0),guiVals.BackgroundPaths.at(1),guiVals.BackgroundPaths.at(2)));


    // DSR Advanced Settings
    data.push_back(factory.createCharArray("BKRemoval"));
    data.push_back(factory.createScalar<bool>(guiVals.BKRemoval));

    data.push_back(factory.createCharArray("LowerLimit"));
    data.push_back(factory.createScalar<double>(guiVals.LowerLimit));

    guiVals.resampleType = "xy_isotropic";
    data.push_back(factory.createCharArray("resampleType"));
    data.push_back(factory.createCharArray(guiVals.resampleType));

    //data.push_back(factory.createCharArray("resample"));
    //data.push_back(factory.createScalar<uint64_t>(guiVals.resample));

    // Stitch Settings

    data.push_back(factory.createCharArray("stitchPipeline"));
    data.push_back(factory.createCharArray(ui->stitchPipelineComboBox->currentText().toStdString()));

    data.push_back(factory.createCharArray("stitchResultDir"));
    data.push_back(factory.createCharArray(ui->resultsDirLineEdit->text().toStdString()));

    data.push_back(factory.createCharArray("imageListFullpaths"));
    data.push_back(factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/ImageList_18s_tailbud_dhb_mScarlet_lck_mNeon_h2b_miRFP670.csv"/*ui->imageListFullPathsLineEdit->text().toStdString()*/));

    if(!ui->axisOrderLineEdit->text().toStdString().empty()){
    data.push_back(factory.createCharArray("axisOrder"));
    data.push_back(factory.createCharArray(ui->axisOrderLineEdit->text().toStdString()));
    }

    data.push_back(factory.createCharArray("BlendMethod"));
    data.push_back(factory.createCharArray(ui->blendMethodComboBox->currentText().toStdString()));

    data.push_back(factory.createCharArray("xcorrShift"));
    data.push_back(factory.createScalar<bool>(ui->xCorrShiftCheckBox->isChecked()));

    data.push_back(factory.createCharArray("xcorrMode"));
    data.push_back(factory.createCharArray(ui->xCorrModeComboBox->currentText().toStdString()));

    // Bound box crop
    if(ui->boundBoxCheckBox->isChecked()){
        data.push_back(factory.createArray<int>({1,6},{ui->boundBoxYMinSpinBox->value(),ui->boundBoxXMinSpinBox->value(),ui->boundBoxZMinSpinBox->value(),ui->boundBoxYMaxSpinBox->value(), ui->boundBoxXMaxSpinBox->value(), ui->boundBoxZMaxSpinBox->value()}));
    }

    //guiVals.primaryCh = "camA_ch0";
    //data.push_back(factory.createCharArray("primaryCh"));
    //data.push_back(factory.createCharArray(guiVals.primaryCh));

    // Decon Settings

    data.push_back(factory.createCharArray("cudaDecon"));
    data.push_back(factory.createScalar<bool>(ui->cudaDeconRadioButton->isChecked()));

    data.push_back(factory.createCharArray("cppDecon"));
    data.push_back(factory.createScalar<bool>(ui->cppDeconRadioButton->isChecked()));

    data.push_back(factory.createCharArray("DS"));
    data.push_back(factory.createScalar<bool>(ui->deskewDeconCheckBox->isChecked()));

    data.push_back(factory.createCharArray("DSR"));
    data.push_back(factory.createScalar<bool>(ui->deskewAndRotateDeconCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Background"));
    data.push_back(factory.createScalar<uint64_t>(ui->backgroundIntensityLineEdit->text().toULongLong()));

    data.push_back(factory.createCharArray("dzPSF"));
    data.push_back(factory.createScalar<double>(ui->dzPSFLineEdit->text().toDouble()));

    data.push_back(factory.createCharArray("EdgeErosion"));
    data.push_back(factory.createScalar<uint64_t>(ui->edgeErosionLineEdit->text().toULongLong()));

    data.push_back(factory.createCharArray("ErodeByFTP"));
    data.push_back(factory.createScalar<bool>(ui->erodeByFTPCheckBox->isChecked()));

    data.push_back(factory.createCharArray("deconRotate"));
    data.push_back(factory.createScalar<bool>(ui->deconRotateCheckBox->isChecked()));

    // Decon Advanced settings

    if(!guiVals.cppDeconPath.empty()){
        data.push_back(factory.createCharArray("cppDeconPath"));
        data.push_back(factory.createCharArray(guiVals.cppDeconPath));
    }
    if(!guiVals.loadModules.empty()){
        data.push_back(factory.createCharArray("loadModules"));
        data.push_back(factory.createCharArray(guiVals.loadModules));
    }
    if(!guiVals.cudaDeconPath.empty()){
        data.push_back(factory.createCharArray("cudaDeconPath"));
        data.push_back(factory.createCharArray(guiVals.cudaDeconPath));
    }
    if(!guiVals.OTFGENPath.empty()){
        data.push_back(factory.createCharArray("OTFGENPath"));
        data.push_back(factory.createCharArray(guiVals.OTFGENPath));
    }

    // Make this not hard coded later---
    data.push_back(factory.createCharArray("psfFullpaths"));
    data.push_back(factory.createCellArray({1,3},factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/PSF/488nm.tif"),factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/PSF/560nm.tif"),factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/PSF/642nm.tif")));

    data.push_back(factory.createCharArray("DeconIter"));
    data.push_back(factory.createScalar<uint64_t>(ui->deconIterationsLineEdit->text().toULongLong()));

    data.push_back(factory.createCharArray("rotatedPSF"));
    data.push_back(factory.createScalar<bool>(ui->rotatePSFCheckBox->isChecked()));

    // Job Settings

    data.push_back(factory.createCharArray("parseCluster"));
    data.push_back(factory.createScalar<bool>(ui->parseClusterCheckBox->isChecked()));

    data.push_back(factory.createCharArray("cpusPerTask"));
    data.push_back(factory.createScalar<uint64_t>(ui->cpusPerTaskLineEdit->text().toULongLong()));

    data.push_back(factory.createCharArray("cpuOnlyNodes"));
    data.push_back(factory.createScalar<bool>(ui->cpuOnlyNodesCheckBox->isChecked()));

    // Advanced Job Settings

    data.push_back(factory.createCharArray("largeFile"));
    data.push_back(factory.createScalar<bool>(guiVals.largeFile));

    if(!guiVals.jobLogDir.empty()){
        data.push_back(factory.createCharArray("jobLogDir"));
        data.push_back(factory.createCharArray(guiVals.jobLogDir));
    }

    if(!guiVals.uuid.empty()){
        data.push_back(factory.createCharArray("uuid"));
        data.push_back(factory.createCharArray(guiVals.uuid));
    }

    data.push_back(factory.createCharArray("maxTrialNum"));
    data.push_back(factory.createScalar<uint64_t>(guiVals.maxTrialNum));

    data.push_back(factory.createCharArray("unitWaitTime"));
    data.push_back(factory.createScalar<uint64_t>(guiVals.unitWaitTime));

    data.push_back(factory.createCharArray("minModifyTime"));
    data.push_back(factory.createScalar<uint64_t>(guiVals.minModifyTime));

    data.push_back(factory.createCharArray("maxModifyTime"));
    data.push_back(factory.createScalar<uint64_t>(guiVals.maxModifyTime));

    data.push_back(factory.createCharArray("maxWaitLoopNum"));
    data.push_back(factory.createScalar<uint64_t>(guiVals.maxWaitLoopNum));

    if(!guiVals.MatlabLaunchStr.empty()){
    data.push_back(factory.createCharArray("MatlabLaunchStr"));
    data.push_back(factory.createCharArray(guiVals.MatlabLaunchStr));
    }


    if(!guiVals.SlurmParam.empty()){
    data.push_back(factory.createCharArray("SlurmParam"));
    data.push_back(factory.createCharArray(guiVals.SlurmParam));
    }

     // Update Progress bar
     ui->jobProgressBar->setValue(40);
     ui->jobProgressBarLabel->setText("Running Job");

    //auto outBuf = std::make_shared<SBuf>();
    //auto errBuf = std::make_shared<SBuf>();

    // Create string buffer for standard output
    //typedef std::basic_stringbuf<char16_t> StringBuf;
    //auto output = std::make_shared<SBuf>();

    // Send data to the MATLAB thread
    emit jobStart(outA, data);

    // Output Console text to another window (Work in Progress)
    consoleOutput cOutput;
    cOutput.setModal(true);
    cOutput.exec();
}

// Browse Stitch Result Dir Folder
void MainWindow::on_resultsDirBrowseButton_clicked()
{
    QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select or Make and Select the Results Folder",QDir::homePath());
    if(folder_path.baseName().toStdString() != "") ui->resultsDirLineEdit->setText(folder_path.baseName());
}

// Set tool tip for Stitch Result Dir line
void MainWindow::on_resultsDirLineEdit_textChanged(const QString &arg1)
{
    ui->resultsDirLineEdit->setToolTip(arg1);
}


// Open Main Window Advanced Settings
void MainWindow::on_mainAdvancedSettingsButton_clicked()
{
    mainAdvanced mAdvanced(guiVals);
    mAdvanced.setModal(true);
    mAdvanced.exec();
}

// If Deskew is checked, enable first row and Rotate checkbox
// If Deskew is unchecked, disable first row and Rotate checkbox and remove all their current checks
void MainWindow::on_deskewCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->deskewDeconCheckBox->setEnabled(true);
        ui->deskewOverwriteDataCheckBox->setEnabled(true);
        ui->deskewSave16BitCheckBox->setEnabled(true);
        ui->deskewOnlyFirstTPCheckBox->setEnabled(true);

        // Enable the Next Button
        ui->mainNextButton->setEnabled(true);
    }
    else{
        ui->deskewDeconCheckBox->setEnabled(false);
        ui->deskewOverwriteDataCheckBox->setEnabled(false);
        ui->deskewSave16BitCheckBox->setEnabled(false);
        ui->deskewOnlyFirstTPCheckBox->setEnabled(false);

        ui->deskewDeconCheckBox->setChecked(false);
        ui->deskewOverwriteDataCheckBox->setChecked(false);
        ui->deskewSave16BitCheckBox->setChecked(false);
        ui->deskewOnlyFirstTPCheckBox->setChecked(false);

        // If none of the other main boxes are checked then disable the next button
        if(!(ui->stitchCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked())){
            ui->mainNextButton->setEnabled(false);
        }
    }
}

// If Rotate is checked, enable second row
// If Rotate is unchecked, disable second row and remove all their current checks
void MainWindow::on_rotateCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->rotateDeconCheckBox->setEnabled(true);
        ui->rotateOverwriteDataCheckBox->setEnabled(true);
        ui->rotateSave16BitCheckBox->setEnabled(true);
        ui->rotateOnlyFirstTPCheckBox->setEnabled(true);

        // Enable the Next Button
        ui->mainNextButton->setEnabled(true);

    }
    else{
        ui->rotateDeconCheckBox->setEnabled(false);
        ui->rotateOverwriteDataCheckBox->setEnabled(false);
        ui->rotateSave16BitCheckBox->setEnabled(false);
        ui->rotateOnlyFirstTPCheckBox->setEnabled(false);

        ui->rotateDeconCheckBox->setChecked(false);
        ui->rotateOverwriteDataCheckBox->setChecked(false);
        ui->rotateSave16BitCheckBox->setChecked(false);
        ui->rotateOnlyFirstTPCheckBox->setChecked(false);

        // If none of the other main boxes are checked then disable the next button
        if(!(ui->stitchCheckBox->isChecked() || ui->deskewCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked())){
            ui->mainNextButton->setEnabled(false);
        }
    }

}

// If Deskew and Rotate is checked, enable third row
// If Deskew and Rotate is unchecked, disable third row and remove all their current checks
void MainWindow::on_deskewAndRotateCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->deskewAndRotateDeconCheckBox->setEnabled(true);
        ui->deskewAndRotateOverwriteDataCheckBox->setEnabled(true);
        ui->deskewAndRotateSave16BitCheckBox->setEnabled(true);
        ui->deskewAndRotateOnlyFirstTPCheckBox->setEnabled(true);

        // Enable the Next Button
        ui->mainNextButton->setEnabled(true);

    }
    else{
        ui->deskewAndRotateDeconCheckBox->setEnabled(false);
        ui->deskewAndRotateOverwriteDataCheckBox->setEnabled(false);
        ui->deskewAndRotateSave16BitCheckBox->setEnabled(false);
        ui->deskewAndRotateOnlyFirstTPCheckBox->setEnabled(false);

        ui->deskewAndRotateDeconCheckBox->setChecked(false);
        ui->deskewAndRotateOverwriteDataCheckBox->setChecked(false);
        ui->deskewAndRotateSave16BitCheckBox->setChecked(false);
        ui->deskewAndRotateOnlyFirstTPCheckBox->setChecked(false);

        // If none of the other main boxes are checked then disable the next button
        if(!(ui->stitchCheckBox->isChecked() || ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked())){
            ui->mainNextButton->setEnabled(false);
        }
    }
}

// If Stitch is checked, enable fourth row
// If Stitch is unchecked, disable fourth row and remove all their current checks
void MainWindow::on_stitchCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->stitchDeconCheckBox->setEnabled(true);
        ui->stitchOverwriteDataCheckBox->setEnabled(true);
        ui->stitchSave16BitCheckBox->setEnabled(true);
        ui->stitchOnlyFirstTPCheckBox->setEnabled(true);

        // Enable the Next Button
        ui->mainNextButton->setEnabled(true);
    }
    else{
        ui->stitchDeconCheckBox->setEnabled(false);
        ui->stitchOverwriteDataCheckBox->setEnabled(false);
        ui->stitchSave16BitCheckBox->setEnabled(false);
        ui->stitchOnlyFirstTPCheckBox->setEnabled(false);

        ui->stitchDeconCheckBox->setChecked(false);
        ui->stitchOverwriteDataCheckBox->setChecked(false);
        ui->stitchSave16BitCheckBox->setChecked(false);
        ui->stitchOnlyFirstTPCheckBox->setChecked(false);

        // If none of the other main boxes are checked then disable the next button
        if(!(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked())){
            ui->mainNextButton->setEnabled(false);
        }
    }
}

// Functionality for the Next button on the main page
void MainWindow::on_mainNextButton_clicked()
{
    // Set the checkmark and disable the tab
    ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->Main),QString::fromStdString("Main ✔"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Main),false);

    // Logic of which tab is next
    if(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->DSR);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->Stitch);
    }

}

// Functionality for the Previous button on the dsr page
void MainWindow::on_dsrPreviousButton_clicked()
{
    // Enable the main tab and disable dsr tab
    ui->tabWidget->setCurrentWidget(ui->Main);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->DSR),false);
}

// Functionality for the Next button on the dsr page
void MainWindow::on_dsrNextButton_clicked()
{
    // Set the checkmark and disable the tab
    ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->DSR),QString::fromStdString("DSR ✔"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->DSR),false);

    // Logic of which tab is next
    if(ui->stitchCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Stitch);
    }
    else if(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Decon);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->Job);
    }
}

// When going to a new tab, enable it and remove checkmark if it has one
void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->tabWidget->setTabEnabled(index, true);

    if(ui->tabWidget->tabText(index).contains(' ')){
        QString temp = ui->tabWidget->tabText(index);
        temp.remove(' ');
        temp.remove("✔");
        ui->tabWidget->setTabText(index,temp);
    }
}

// Disallow Deskew if Objective Scan is true
void MainWindow::on_objectiveScanCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->deskewCheckBox->setChecked(false);
        ui->deskewCheckBox->setEnabled(false);
        ui->deskewLabel->setEnabled(false);
    }
    else{
        ui->deskewCheckBox->setEnabled(true);
        ui->deskewLabel->setEnabled(true);
    }
}

// Functionality for the Previous button on the stitch page
void MainWindow::on_stitchPreviousButton_clicked()
{
    // Logic for which tab to go to
    if(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->DSR);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->Main);
    }

    // Disable the stitch tab
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Stitch),false);
}

// Functionality for the Next button on the stitch page
void MainWindow::on_stitchNextButton_clicked()
{
    // Set the checkmark and disable the tab
    ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->Stitch),QString::fromStdString("Stitch ✔"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Stitch),false);

    // Logic of which tab is next
    if(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Decon);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->Job);
    }
}

// Functionality for the Previous button on the Decon page
void MainWindow::on_deconPreviousButton_clicked()
{
    // Logic for which tab to go to
    if(ui->stitchCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Stitch);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->DSR);
    }

    // Disable the Decon tab
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Decon),false);
}

// Functionality for the Next button on the Decon page
void MainWindow::on_deconNextButton_clicked()
{
    // Set the checkmark and disable the tab
    ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->Decon),QString::fromStdString("Decon ✔"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Decon),false);

    // Job is the only possible tab to go to next from decon
    ui->tabWidget->setCurrentWidget(ui->Job);
}

// Functionality for the Previous button on the job page
void MainWindow::on_jobPreviousButton_clicked()
{
    // Logic for which tab to go to
    if(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Decon);
    }
    else if (ui->stitchCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Stitch);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->DSR);
    }

    // Disable the Job tab
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Job),false);
}

// Opens a  seperate window to add the data paths for the job
void MainWindow::on_addPathsButton_clicked()
{
    dataPaths daPaths(dPaths);
    daPaths.setModal(true);
    daPaths.exec();
}

void MainWindow::on_imageListFullPathsBrowseButton_clicked()
{
    QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Image List Full Paths File",QDir::homePath());
    if(file_path.absoluteFilePath().toStdString() != "") ui->imageListFullPathsLineEdit->setText(file_path.absoluteFilePath());
}

void MainWindow::on_imageListFullPathsLineEdit_textChanged(const QString &arg1)
{
    ui->imageListFullPathsLineEdit->setToolTip(arg1);
}

// Enable bound box options or disable them
void MainWindow::on_boundBoxCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->boundBoxYMinLabel->setEnabled(true);
        ui->boundBoxYMinSpinBox->setEnabled(true);
        ui->boundBoxXMinLabel->setEnabled(true);
        ui->boundBoxXMinSpinBox->setEnabled(true);
        ui->boundBoxZMinLabel->setEnabled(true);
        ui->boundBoxZMinSpinBox->setEnabled(true);
        ui->boundBoxYMaxLabel->setEnabled(true);
        ui->boundBoxYMaxSpinBox->setEnabled(true);
        ui->boundBoxXMaxLabel->setEnabled(true);
        ui->boundBoxXMaxSpinBox->setEnabled(true);
        ui->boundBoxZMaxLabel->setEnabled(true);
        ui->boundBoxZMaxSpinBox->setEnabled(true);
    }
    else{
        ui->boundBoxYMinLabel->setEnabled(false);
        ui->boundBoxYMinSpinBox->setEnabled(false);
        ui->boundBoxXMinLabel->setEnabled(false);
        ui->boundBoxXMinSpinBox->setEnabled(false);
        ui->boundBoxZMinLabel->setEnabled(false);
        ui->boundBoxZMinSpinBox->setEnabled(false);
        ui->boundBoxYMaxLabel->setEnabled(false);
        ui->boundBoxYMaxSpinBox->setEnabled(false);
        ui->boundBoxXMaxLabel->setEnabled(false);
        ui->boundBoxXMaxSpinBox->setEnabled(false);
        ui->boundBoxZMaxLabel->setEnabled(false);
        ui->boundBoxZMaxSpinBox->setEnabled(false);

        ui->boundBoxYMinSpinBox->setValue(0);
        ui->boundBoxXMinSpinBox->setValue(0);
        ui->boundBoxZMinSpinBox->setValue(0);
        ui->boundBoxYMaxSpinBox->setValue(0);
        ui->boundBoxXMaxSpinBox->setValue(0);
        ui->boundBoxZMaxSpinBox->setValue(0);
    }
}

// Enable or Disable settings associated with LLFF
void MainWindow::on_llffCorrectionCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->lsImagePathsLabel->setEnabled(true);
        ui->lsImagePathsLineEdit->setEnabled(true);
        ui->backgroundPathsLabel->setEnabled(true);
        ui->backgroundPathsLineEdit->setEnabled(true);
    }
    else{
        ui->lsImagePathsLabel->setEnabled(false);
        ui->lsImagePathsLineEdit->setEnabled(false);
        ui->backgroundPathsLabel->setEnabled(false);
        ui->backgroundPathsLineEdit->setEnabled(false);

        ui->backgroundPathsLineEdit->setText("");
        ui->lsImagePathsLineEdit->setText("");
    }
}
