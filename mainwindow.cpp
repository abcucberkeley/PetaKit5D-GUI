#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainadvanced.h"
#include "dsradvanced.h"
#include "deconadvanced.h"
#include "jobadvanced.h"
#include "datapaths.h"
#include "consoleoutput.h"


using namespace matlab::engine;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set the tabs widget as the main Widget
    this->setCentralWidget(ui->tabWidget);

    // Set a variable to see how many threads the user can use for matlab
    //QString maxCPU = QString::fromStdString(ui->maxCPUs->text().toStdString()+std::to_string(QThread::idealThreadCount()-1));
    //ui->maxCPUs->setText(maxCPU);

    // Threading and connecting signals/slots
    mThread = new matlabThread(this);
    connect(this, &MainWindow::jobStart, mThread, &matlabThread::onJobStart);
    connect(mThread, &matlabThread::enableSubmitButton, this, &MainWindow::onEnableSubmitButton);
    mThread->start(QThread::LowPriority);

    // Disable all tabs except the main one on startup
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->DSR),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Stitch),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Decon),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Job),false);

    // Restore previous settings
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;

    // If the thread is not done, kill it (This may have to change later because it can be dangerous)
    if(!mThread->isFinished()) mThread->terminate();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        writeSettings();
        event->accept();
}

void MainWindow::writeSettings()
{
    QSettings settings("ABC", "LLSM GUI");

    settings.beginGroup("MainWindow");
    //settings.setValue("size", size());
    //settings.setValue("pos", pos());

    // Save Data Paths
    settings.beginWriteArray("dPaths");
    for(unsigned int i = 0; i < dPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("dPathsi", QString::fromStdString(dPaths.at(i)));
    }
    settings.endArray();

    // Save Main Settings

    settings.setValue("deskewOverwrite",ui->deskewOverwriteDataCheckBox->isChecked());
    settings.setValue("rotateOverwrite",ui->rotateOverwriteDataCheckBox->isChecked());
    settings.setValue("deskewAndRotateOverwrite",ui->deskewAndRotateOverwriteDataCheckBox->isChecked());
    settings.setValue("stitchOverwrite",ui->stitchOverwriteDataCheckBox->isChecked());

    settings.setValue("Streaming",ui->streamingCheckBox->isChecked());

    // SAVE FOR CHANNEL PATTERNS
    settings.beginWriteArray("channelLabels");
    for(unsigned int i = 0; i < channelWidgets.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("channelLabelsi", channelWidgets[i].first->text());
    }
    settings.endArray();

    settings.beginWriteArray("channelChecks");
    for(unsigned int i = 0; i < channelWidgets.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("channelChecksi", channelWidgets[i].second->isChecked());
    }
    settings.endArray();

    settings.setValue("skewAngle",guiVals.skewAngle);
    settings.setValue("dz",ui->dzLineEdit->text());
    settings.setValue("xyPixelSize",guiVals.xyPixelSize);
    settings.setValue("Reverse",guiVals.Reverse);
    settings.setValue("objectiveScan",ui->objectiveScanCheckBox->isChecked());
    settings.setValue("sCMOSCameraFlip",guiVals.sCMOSCameraFlip);

    settings.setValue("deskewSave16Bit",ui->deskewSave16BitCheckBox->isChecked());
    settings.setValue("rotateSave16Bit",ui->rotateSave16BitCheckBox->isChecked());
    settings.setValue("deskewAndRotateSave16Bit",ui->deskewAndRotateSave16BitCheckBox->isChecked());
    settings.setValue("stitchSave16Bit",ui->stitchSave16BitCheckBox->isChecked());

    settings.setValue("deskewOnlyFirstTP",ui->deskewOnlyFirstTPCheckBox->isChecked());
    settings.setValue("rotateOnlyFirstTP",ui->rotateOnlyFirstTPCheckBox->isChecked());
    settings.setValue("deskewAndRotateOnlyFirstTP",ui->deskewAndRotateOnlyFirstTPCheckBox->isChecked());
    settings.setValue("stitchOnlyFirstTP",ui->stitchOnlyFirstTPCheckBox->isChecked());

    // Save Pipeline Settings

    settings.setValue("Deskew",ui->deskewCheckBox->isChecked());
    settings.setValue("Rotate",ui->rotateCheckBox->isChecked());
    settings.setValue("Stitch",ui->stitchCheckBox->isChecked());
    settings.setValue("deskewAndRotate",ui->deskewAndRotateCheckBox->isChecked());

    settings.setValue("deskewDecon",ui->deskewDeconCheckBox->isChecked());
    settings.setValue("rotateDecon",ui->rotateDeconCheckBox->isChecked());
    settings.setValue("deskewAndRotateDecon",ui->deskewAndRotateDeconCheckBox->isChecked());
    settings.setValue("stitchDecon",ui->stitchDeconCheckBox->isChecked());

    // Save DSR Settings

    settings.setValue("parseSettingFile",ui->parseSettingsFileCheckBox->isChecked());
    settings.setValue("flipZstack",ui->flipZStackCheckBox->isChecked());

    settings.setValue("LLFFCorrection",ui->llffCorrectionCheckBox->isChecked());

    settings.beginWriteArray("LSImagePaths");
    for(unsigned int i = 0; i < lsImagePaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("LSImagePathsi", QString::fromStdString(lsImagePaths.at(i)));
    }
    settings.endArray();

    settings.beginWriteArray("BackgroundPaths");
    for(unsigned int i = 0; i < backgroundPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("BackgroundPathsi", QString::fromStdString(backgroundPaths.at(i)));
    }
    settings.endArray();

    // Save DSR Advanced Settings

    settings.setValue("BKRemoval",guiVals.BKRemoval);
    settings.setValue("LowerLimit",guiVals.LowerLimit);
    settings.setValue("resampleType",QString::fromStdString(guiVals.resampleType));
    settings.setValue("resample",QVariant::fromValue(guiVals.resample));

    // Save Stitch Settings

    settings.setValue("stitchPipeline", ui->stitchPipelineComboBox->currentText());
    settings.setValue("stitchResultsDir", ui->resultsDirLineEdit->text());
    settings.setValue("imageListFullPaths", ui->imageListFullPathsLineEdit->text());
    settings.setValue("axisOrder", ui->axisOrderLineEdit->text());
    settings.setValue("blendMethod", ui->blendMethodComboBox->currentText());
    settings.setValue("xcorrShift", ui->xCorrShiftCheckBox->isChecked());
    settings.setValue("xcorrMode", ui->xCorrModeComboBox->currentText());

    settings.setValue("boundBox", ui->boundBoxCheckBox->isChecked());
    settings.setValue("bbYMin", ui->boundBoxYMinSpinBox->value());
    settings.setValue("bbXMin", ui->boundBoxXMinSpinBox->value());
    settings.setValue("bbZMin", ui->boundBoxZMinSpinBox->value());
    settings.setValue("bbYMax", ui->boundBoxYMaxSpinBox->value());
    settings.setValue("bbXMax", ui->boundBoxXMaxSpinBox->value());
    settings.setValue("bbZMax", ui->boundBoxZMaxSpinBox->value());

    settings.setValue("primaryCh", ui->primaryCHLineEdit->text());

    // Save Decon Settings

    settings.setValue("matlabDecon", ui->matlabDeconRadioButton->isChecked());
    settings.setValue("cudaDecon", ui->cudaDeconRadioButton->isChecked());
    settings.setValue("cppDecon", ui->cppDeconRadioButton->isChecked());
    settings.setValue("DS", ui->deskewDeconCheckBox->isChecked());
    settings.setValue("DSR", ui->deskewAndRotateDeconCheckBox->isChecked());
    settings.setValue("Background", ui->backgroundIntensityLineEdit->text());
    settings.setValue("dzPSF", ui->dzPSFLineEdit->text());
    settings.setValue("edgeErosion", ui->edgeErosionLineEdit->text());
    settings.setValue("ErodeByFTP", ui->erodeByFTPCheckBox->isChecked());
    settings.setValue("deconRotate", ui->deconRotateCheckBox->isChecked());


    // Save Decon Advaced Settings

    settings.setValue("cppDeconPath",QString::fromStdString(guiVals.cppDeconPath));
    settings.setValue("loadModules",QString::fromStdString(guiVals.loadModules));
    settings.setValue("cudaDeconPath",QString::fromStdString(guiVals.cudaDeconPath));
    settings.setValue("OTFGENPath",QString::fromStdString(guiVals.OTFGENPath));

    settings.beginWriteArray("psfFullpaths");
    for(unsigned int i = 0; i < psfFullPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("psfFullpathsi", QString::fromStdString(psfFullPaths.at(i)));
    }
    settings.endArray();

    settings.setValue("DeconIter", ui->deconIterationsLineEdit->text());
    settings.setValue("rotatedPSF", ui->rotatePSFCheckBox->isChecked());

    // Save Job Settings

    settings.setValue("parseCluster", ui->parseClusterCheckBox->isChecked());
    settings.setValue("cpusPerTask", ui->cpusPerTaskLineEdit->text());
    settings.setValue("cpuOnlyNodes", ui->cpuOnlyNodesCheckBox->isChecked());

    // Save Advanced Job Settings

    settings.setValue("largeFile",QVariant::fromValue(guiVals.largeFile));
    settings.setValue("jobLogDir",QString::fromStdString(guiVals.jobLogDir));
    settings.setValue("uuid",QString::fromStdString(guiVals.uuid));
    settings.setValue("maxTrialNum",QVariant::fromValue(guiVals.maxTrialNum));
    settings.setValue("unitWaitTime",QVariant::fromValue(guiVals.unitWaitTime));
    settings.setValue("minModifyTime",QVariant::fromValue(guiVals.minModifyTime));
    settings.setValue("maxModifyTime",QVariant::fromValue(guiVals.maxModifyTime));
    settings.setValue("maxWaitLoopNum",QVariant::fromValue(guiVals.maxWaitLoopNum));
    settings.setValue("MatlabLaunchStr",QString::fromStdString(guiVals.MatlabLaunchStr));
    settings.setValue("SlurmParam",QString::fromStdString(guiVals.SlurmParam));

    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("ABC", "LLSM GUI");

    settings.beginGroup("MainWindow");
    // resize(settings.value("size", QSize(400, 400)).toSize());
    //move(settings.value("pos", QPoint(200, 200)).toPoint());

    // Read Data Paths
    int size = settings.beginReadArray("dPaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        dPaths.push_back(settings.value("dPathsi").toString().toStdString());
    }
    settings.endArray();

    // Read Main Settings

    ui->deskewOverwriteDataCheckBox->setChecked(settings.value("deskewOverwrite").toBool());
    ui->rotateOverwriteDataCheckBox->setChecked(settings.value("rotateOverwrite").toBool());
    ui->deskewAndRotateOverwriteDataCheckBox->setChecked(settings.value("deskewAndRotateOverwrite").toBool());
    ui->stitchOverwriteDataCheckBox->setChecked(settings.value("stitchOverwrite").toBool());

    ui->streamingCheckBox->setChecked(settings.value("Streaming").toBool());

    // READ FOR CHANNEL PATTERNS

    // temp vectors to hold labels and checkbox values
    std::vector<QString> tLabels;
    std::vector<bool> tChecks;

    // Read labels and checks into vectors
    size = settings.beginReadArray("channelLabels");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        tLabels.push_back(settings.value("channelLabelsi").toString());
    }
    settings.endArray();

    size = settings.beginReadArray("channelChecks");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        tChecks.push_back(settings.value("channelChecksi").toBool());
    }
    settings.endArray();

    // Create widgets and put them in channelWidgets
    for(size_t i = 0; i < tLabels.size(); i++){
        QLabel* label = new QLabel(ui->Main);
        label->setTextFormat(Qt::RichText);
        label->setText("<b>"+tLabels[i]+"<\b>");
        ui->horizontalLayout_4->addWidget(label);

        QCheckBox* checkBox = new QCheckBox(ui->Main);
        checkBox->setChecked(tChecks[i]);
        ui->horizontalLayout_4->addWidget(checkBox);

        channelWidgets.push_back(std::make_pair(label,checkBox));

    }

    guiVals.skewAngle = settings.value("skewAngle").toDouble();
    ui->dzLineEdit->setText(settings.value("dz").toString());
    guiVals.xyPixelSize = settings.value("xyPixelSize").toDouble();
    guiVals.Reverse = settings.value("Reverse").toBool();
    ui->objectiveScanCheckBox->setChecked(settings.value("objectiveScan").toBool());
    guiVals.sCMOSCameraFlip = settings.value("sCMOSCameraFlip").toBool();

    ui->deskewSave16BitCheckBox->setChecked(settings.value("deskewSave16Bit").toBool());
    ui->rotateSave16BitCheckBox->setChecked(settings.value("rotateSave16Bit").toBool());
    ui->deskewAndRotateSave16BitCheckBox->setChecked(settings.value("deskewAndRotateSave16Bit").toBool());
    ui->stitchSave16BitCheckBox->setChecked(settings.value("stitchSave16Bit").toBool());

    ui->deskewOnlyFirstTPCheckBox->setChecked(settings.value("deskewOnlyFirstTP").toBool());
    ui->rotateOnlyFirstTPCheckBox->setChecked(settings.value("rotateOnlyFirstTP").toBool());
    ui->deskewAndRotateOnlyFirstTPCheckBox->setChecked(settings.value("deskewAndRotateOnlyFirstTP").toBool());
    ui->stitchOnlyFirstTPCheckBox->setChecked(settings.value("stitchOnlyFirstTP").toBool());

    // Read Pipeline Settings

    ui->deskewCheckBox->setChecked(settings.value("Deskew").toBool());
    ui->rotateCheckBox->setChecked(settings.value("Rotate").toBool());
    ui->stitchCheckBox->setChecked(settings.value("Stitch").toBool());
    ui->deskewAndRotateCheckBox->setChecked(settings.value("deskewAndRotate").toBool());

    ui->deskewDeconCheckBox->setChecked(settings.value("deskewDecon").toBool());
    ui->rotateDeconCheckBox->setChecked(settings.value("rotateDecon").toBool());
    ui->deskewAndRotateDeconCheckBox->setChecked(settings.value("deskewAndRotateDecon").toBool());
    ui->stitchDeconCheckBox->setChecked(settings.value("stitchDecon").toBool());

    // Read DSR Settings

    ui->parseSettingsFileCheckBox->setChecked(settings.value("parseSettingFile").toBool());
    ui->flipZStackCheckBox->setChecked(settings.value("flipZstack").toBool());

    ui->llffCorrectionCheckBox->setChecked(settings.value("LLFFCorrection").toBool());

    size = settings.beginReadArray("LSImagePaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        lsImagePaths.push_back(settings.value("LSImagePathsi").toString().toStdString());
    }
    settings.endArray();

    size = settings.beginReadArray("BackgroundPaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        backgroundPaths.push_back(settings.value("BackgroundPathsi").toString().toStdString());
    }
    settings.endArray();

    // Read DSR Advanced Settings

    guiVals.BKRemoval = settings.value("BKRemoval").toBool();
    guiVals.BKRemoval = settings.value("BKRemoval").toDouble();
    guiVals.resampleType = settings.value("resampleType").toString().toStdString();
    guiVals.resample = settings.value("resample").toULongLong();

    // Read Stitch Settings
    ui->stitchPipelineComboBox->setCurrentText(settings.value("stitchPipeline").toString());
    ui->resultsDirLineEdit->setText(settings.value("stitchResultsDir").toString());
    ui->imageListFullPathsLineEdit->setText(settings.value("imageListFullPaths").toString());
    ui->axisOrderLineEdit->setText(settings.value("axisOrder").toString());
    ui->blendMethodComboBox->setCurrentText(settings.value("blendMethod").toString());
    ui->xCorrShiftCheckBox->setChecked(settings.value("xcorrShift").toBool());
    ui->xCorrModeComboBox->setCurrentText(settings.value("xcorrMode").toString());

    ui->boundBoxCheckBox->setChecked(settings.value("boundBox").toBool());
    ui->boundBoxYMinSpinBox->setValue(settings.value("bbYMin").toInt());
    ui->boundBoxXMinSpinBox->setValue(settings.value("bbXMin").toInt());
    ui->boundBoxZMinSpinBox->setValue(settings.value("bbZMin").toInt());
    ui->boundBoxYMaxSpinBox->setValue(settings.value("bbYMax").toInt());
    ui->boundBoxXMinSpinBox->setValue(settings.value("bbXMax").toInt());
    ui->boundBoxZMinSpinBox->setValue(settings.value("bbZMin").toInt());

    ui->primaryCHLineEdit->setText(settings.value("primaryCh").toString());


    // Read Decon Settings

    ui->matlabDeconRadioButton->setChecked(settings.value("matlabDecon").toBool());
    ui->cudaDeconRadioButton->setChecked(settings.value("cudaDecon").toBool());
    ui->cppDeconRadioButton->setChecked(settings.value("cppDecon").toBool());
    ui->deskewDeconCheckBox->setChecked(settings.value("DS").toBool());
    ui->deskewAndRotateDeconCheckBox->setChecked(settings.value("DSR").toBool());
    ui->backgroundIntensityLineEdit->setText(settings.value("Background").toString());
    ui->dzPSFLineEdit->setText(settings.value("dzPSF").toString());
    ui->edgeErosionLineEdit->setText(settings.value("edgeErosion").toString());
    ui->erodeByFTPCheckBox->setChecked(settings.value("ErodeByFTP").toBool());
    ui->deconRotateCheckBox->setChecked(settings.value("deconRotate").toBool());

    // Read Decon Advaced Settings

    guiVals.cppDeconPath = settings.value("cppDeconPath").toString().toStdString();
    guiVals.loadModules = settings.value("loadModules").toString().toStdString();
    guiVals.cudaDeconPath = settings.value("cudaDeconPath").toString().toStdString();
    guiVals.OTFGENPath = settings.value("OTFGENPath").toString().toStdString();

    size = settings.beginReadArray("psfFullpaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        psfFullPaths.push_back(settings.value("psfFullpathsi").toString().toStdString());
    }
    settings.endArray();

    ui->deconIterationsLineEdit->setText(settings.value("DeconIter").toString());
    ui->rotatePSFCheckBox->setChecked(settings.value("rotatedPSF").toBool());

    // Read Job Settings
    ui->parseClusterCheckBox->setChecked(settings.value("parseCluster").toBool());
    ui->cpusPerTaskLineEdit->setText(settings.value("cpusPerTask").toString());
    ui->cpuOnlyNodesCheckBox->setChecked(settings.value("cpuOnlyNodes").toBool());


    // Save Advanced Job Settings

    guiVals.largeFile = settings.value("largeFile").toBool();
    guiVals.jobLogDir = settings.value("jobLogDir").toString().toStdString();
    guiVals.uuid = settings.value("uuid").toString().toStdString();
    guiVals.maxTrialNum = settings.value("maxTrialNum").toULongLong();
    guiVals.unitWaitTime = settings.value("unitWaitTime").toULongLong();
    guiVals.minModifyTime = settings.value("minModifyTime").toULongLong();
    guiVals.maxModifyTime = settings.value("maxModifyTime").toULongLong();
    guiVals.maxWaitLoopNum = settings.value("maxWaitLoopNum").toULongLong();
    guiVals.MatlabLaunchStr = settings.value("MatlabLaunchStr").toString().toStdString();
    guiVals.SlurmParam = settings.value("SlurmParam").toString().toStdString();

    settings.endGroup();
}

// Reenable submit button for new jobs
void MainWindow::onEnableSubmitButton(){
    ui->submitButton->setEnabled(true);
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
    // Error if no data paths set
    if(dPaths.size() == 0){
    QMessageBox messageBox;
    messageBox.warning(0,"Error","No data paths are set");
    messageBox.setFixedSize(500,200);
    return;
    }

    // Make it so the user can't change tabs while the job is running (In Progress)
    //ui->jobPreviousButton->setEnabled(false);
    ui->submitButton->setEnabled(false);
    //ui->jobAdvancedSettingsButton->setEnabled(false);

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
        dataPaths_exps[i] = factory.createCharArray(dPaths[i]);
    }
    data.push_back(dataPaths_exps);

    // Main Settings

    // TODO: Logic (in bool array 4th value is all decon, 5th value is rotate after decon)
    data.push_back(factory.createCharArray("Overwrite"));
    if(ui->deskewOverwriteDataCheckBox->isChecked() && ui->rotateOverwriteDataCheckBox->isChecked() && ui->deskewAndRotateOverwriteDataCheckBox->isChecked() && ui->stitchOverwriteDataCheckBox->isChecked()) data.push_back(factory.createScalar<bool>(true));
    else data.push_back(factory.createArray<bool>({1,5},{ui->deskewOverwriteDataCheckBox->isChecked(),ui->rotateOverwriteDataCheckBox->isChecked(),ui->stitchOverwriteDataCheckBox->isChecked(),false,false}));

    data.push_back(factory.createCharArray("Streaming"));
    data.push_back(factory.createScalar<bool>(ui->streamingCheckBox->isChecked()));

    // Channel Patterns
    if(channelWidgets.size()){
        data.push_back(factory.createCharArray("ChannelPatterns"));
        // Grab indexes of checked boxes
        std::vector<int> indexes;
        for(size_t i = 0; i < channelWidgets.size(); i++){
            if(channelWidgets[i].second->isChecked()) indexes.push_back(i);
        }
        matlab::data::CellArray channelPatterns = factory.createCellArray({1,indexes.size()});
        int cpi = 0;
        // Go through checked indexes and the label text (channel pattern) in the cell array
        for(int i : indexes){
            channelPatterns[cpi] = factory.createCharArray(channelWidgets[i].first->text().toStdString());
            cpi++;
        }
        data.push_back(channelPatterns);
    }

    //data.push_back(factory.createCellArray({1,3},factory.createCharArray(ui->channelPatternsLineEdit->text().toStdString()),factory.createCharArray("CamB_ch1"),factory.createCharArray("CamB_ch1")));

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

    // This needs to change FIX
    data.push_back(factory.createCharArray("Save16bit"));
    data.push_back(factory.createArray<bool>({1,4},{ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked(),ui->stitchSave16BitCheckBox->isChecked(),false,false}));

    // This needs to change FIX
    data.push_back(factory.createCharArray("onlyFirstTP"));
    data.push_back(factory.createScalar<bool>(ui->deskewOnlyFirstTPCheckBox->isChecked() || ui->rotateOnlyFirstTPCheckBox->isChecked() || ui->deskewAndRotateOnlyFirstTPCheckBox->isChecked() || ui->stitchOnlyFirstTPCheckBox->isChecked()));


    // Pipeline Settings

    //
    // TODO: Test this Logic more
    if(!(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked()) && ui->deskewAndRotateCheckBox->isChecked()){
        data.push_back(factory.createCharArray("DSRCombined"));
        data.push_back(factory.createScalar<bool>(true));

        data.push_back(factory.createCharArray("Deskew"));
        data.push_back(factory.createScalar<bool>(true));

        data.push_back(factory.createCharArray("Rotate"));
        data.push_back(factory.createScalar<bool>(true));

    }
    else{
    data.push_back(factory.createCharArray("DSRCombined"));
    data.push_back(factory.createScalar<bool>(false));

    data.push_back(factory.createCharArray("Deskew"));
    data.push_back(factory.createScalar<bool>(ui->deskewCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Rotate"));
    data.push_back(factory.createScalar<bool>(ui->rotateCheckBox->isChecked()));
    }

    data.push_back(factory.createCharArray("Stitch"));
    data.push_back(factory.createScalar<bool>(ui->stitchCheckBox->isChecked()));

    data.push_back(factory.createCharArray("Decon"));
    data.push_back(factory.createScalar<bool>(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked()));

    // Change later
    //data.push_back(factory.createCharArray("RotateAfterDecon"));
    //data.push_back(factory.createScalar<bool>(ui->rotateAfterDeconCheckBox->isChecked()));


    // DSR Settings

    data.push_back(factory.createCharArray("parseSettingFile"));
    data.push_back(factory.createScalar<bool>(ui->parseSettingsFileCheckBox->isChecked()));

    data.push_back(factory.createCharArray("flipZstack"));
    data.push_back(factory.createScalar<bool>(ui->flipZStackCheckBox->isChecked()));

    data.push_back(factory.createCharArray("LLFFCorrection"));
    data.push_back(factory.createScalar<bool>(ui->llffCorrectionCheckBox->isChecked()));

    if(lsImagePaths.size()){
        data.push_back(factory.createCharArray("LSImagePaths"));
        matlab::data::CellArray lsImageMPaths = factory.createCellArray({1,lsImagePaths.size()});
        for(size_t i = 0; i < lsImagePaths.size(); i++){
            lsImageMPaths[i] = factory.createCharArray(lsImagePaths[i]);
        }
        data.push_back(lsImageMPaths);
    }

    if(backgroundPaths.size()){
        data.push_back(factory.createCharArray("BackgroundPaths"));
        matlab::data::CellArray backgroundMPaths = factory.createCellArray({1,backgroundPaths.size()});
        for(size_t i = 0; i < backgroundPaths.size(); i++){
            backgroundMPaths[i] = factory.createCharArray(backgroundPaths[i]);
        }
        data.push_back(backgroundMPaths);
    }

    // DSR Advanced Settings

    data.push_back(factory.createCharArray("BKRemoval"));
    data.push_back(factory.createScalar<bool>(guiVals.BKRemoval));

    data.push_back(factory.createCharArray("LowerLimit"));
    data.push_back(factory.createScalar<double>(guiVals.LowerLimit));

    //guiVals.resampleType = "xy_isotropic";
    data.push_back(factory.createCharArray("resampleType"));
    data.push_back(factory.createCharArray(guiVals.resampleType));

    if(guiVals.resample){
        data.push_back(factory.createCharArray("resample"));
        data.push_back(factory.createScalar<uint64_t>(guiVals.resample));
    }

    // Stitch Settings

    data.push_back(factory.createCharArray("stitchPipeline"));
    data.push_back(factory.createCharArray(ui->stitchPipelineComboBox->currentText().toStdString()));

    data.push_back(factory.createCharArray("stitchResultDir"));
    data.push_back(factory.createCharArray(ui->resultsDirLineEdit->text().toStdString()));

    data.push_back(factory.createCharArray("imageListFullpaths"));
    data.push_back(factory.createCharArray(ui->imageListFullPathsLineEdit->text().toStdString()));

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

    //EX: "camA_ch0";
    if(!ui->primaryCHLineEdit->text().isEmpty()){
        data.push_back(factory.createCharArray("primaryCh"));
        data.push_back(factory.createCharArray(ui->primaryCHLineEdit->text().toStdString()));
    }

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

    if(psfFullPaths.size()){
        data.push_back(factory.createCharArray("psfFullpaths"));
        matlab::data::CellArray psfMPaths = factory.createCellArray({1,psfFullPaths.size()});
        for(size_t i = 0; i < psfFullPaths.size(); i++){
            std::cout << psfFullPaths[i] << std::endl;
            psfMPaths[i] = factory.createCharArray(psfFullPaths[i]);
        }
        data.push_back(psfMPaths);
    }
    // Line below is for testing purposes
    //data.push_back(factory.createCellArray({1,3},factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/PSF/488nm.tif"),factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/PSF/560nm.tif"),factory.createCharArray("C:/Users/Matt/Desktop/Play_with_data/20191114_Imaging/ZF_TailbudDevelopment/PSF/642nm.tif")));

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

    // Send data to the MATLAB thread
    emit jobStart(outA, data);

    // Output Console text to another window (Work in Progress) (For Windows only most likely)
    /*
    (consoleOutput cOutput;
    cOutput.setModal(true);
    cOutput.exec();
    */
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
    dataPaths daPaths(dPaths, true);
    daPaths.setModal(true);
    daPaths.exec();

    // Find all possible channels
    if(dPaths.size()){
        if(channelWidgets.size()){
            for(auto &i : channelWidgets){
                if(i.first) delete i.first;
                if(i.second) delete i.second;
            }
        }
        channelWidgets.clear();
        std::vector<QString> channels;
        for(const std::string &i : dPaths){
            QDirIterator cPath(QString::fromStdString(i),QDirIterator::Subdirectories);
            QString c;
            QRegularExpression re("Cam\\w_ch\\d");
            QRegularExpressionMatch rmatch;
            while(cPath.hasNext()){
                c = cPath.next();
                //qDebug() << c;
                rmatch = re.match(c);
                if (!rmatch.captured(0).isEmpty()) channels.push_back(rmatch.captured(0));
                //qDebug() << rmatch.captured(0);

            }
        }
        for(const QString &ch : channels){

            QLabel* label = new QLabel(ui->Main);
            label->setTextFormat(Qt::RichText);
            label->setText("<b>"+ch+"<\b>");
            ui->horizontalLayout_4->addWidget(label);

            QCheckBox* checkBox = new QCheckBox(ui->Main);
            ui->horizontalLayout_4->addWidget(checkBox);
            channelWidgets.push_back(std::make_pair(label,checkBox));
        }
    }


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
        ui->lsImageAddPathsButton->setEnabled(true);
        ui->backgroundPathsLabel->setEnabled(true);
        ui->backgroundAddPathsButton->setEnabled(true);
    }
    else{
        ui->lsImagePathsLabel->setEnabled(false);
        ui->lsImageAddPathsButton->setEnabled(false);
        ui->backgroundPathsLabel->setEnabled(false);
        ui->backgroundAddPathsButton->setEnabled(false);

        lsImagePaths.clear();
        backgroundPaths.clear();
    }
}

// Open window for adding lsImage Paths
void MainWindow::on_lsImageAddPathsButton_clicked()
{
    dataPaths daPaths(lsImagePaths, false);
    daPaths.setModal(true);
    daPaths.exec();
}

// Open window for adding background Paths
void MainWindow::on_backgroundAddPathsButton_clicked()
{
    dataPaths daPaths(backgroundPaths, false);
    daPaths.setModal(true);
    daPaths.exec();
}

// Open window for adding PSF Paths
void MainWindow::on_psfFullAddPathsButton_2_clicked()
{
    dataPaths daPaths(psfFullPaths, false);
    daPaths.setModal(true);
    daPaths.exec();
}
