#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainadvanced.h"
#include "dsradvanced.h"
#include "deconadvanced.h"
#include "jobadvanced.h"
#include "simreconmainadvanced.h"
#include "simreconreconadvanced.h"
#include "simreconjobadvanced.h"
#include "datapaths.h"
#include "loadprevioussettings.h"
#include "submissionchecks.h"
#include "matlabhelperfunctions.h"
#include <QTextDocument>
#include <QObjectList>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // check if using compiled scripts or matlab
    // isMcc = true;

    // Set the tabs widget as the main Widget
    this->setCentralWidget(ui->tabWidget);

    // Matlab Threading and connecting signals/slots
    mThreadManager = new matlabThreadManager(outputLock, this);
    connect(this, &MainWindow::jobStart, mThreadManager, &matlabThreadManager::onJobStart);
    connect(mThreadManager, &matlabThreadManager::enableSubmitButton, this, &MainWindow::onEnableSubmitButton);
    mThreadManager->start(QThread::HighestPriority);

    // Connect Sim Recon signals
    connect(ui->simReconAddPathsButton, &QPushButton::clicked, this, &MainWindow::on_addPathsButton_clicked);

    // Connect crop signals
    connect(ui->cropAddPathsButton, &QPushButton::clicked, this, &MainWindow::on_addPathsButton_clicked);
    connect(ui->cropResultPathBrowseButton, &QPushButton::clicked, this, &MainWindow::selectFolderPath);
    connect(ui->cropJobLogDirBrowseButton, &QPushButton::clicked, this, &MainWindow::selectFolderPath);
    //connect(ui->cropSubmitButton,&QPushButton::clicked, this, &MainWindow::on_submitButton_clicked);

    // Connect FSC Analysis signals
    connect(ui->fscAnalysisAddPathsButton, &QPushButton::clicked, this, &MainWindow::on_addPathsButton_clicked);

    // Connect mipGenerator signals
    connect(ui->mipGeneratorAddPathsButton, &QPushButton::clicked, this, &MainWindow::on_addPathsButton_clicked);

    // Connect psfDetectionAnalysis signals
    connect(ui->psfDetectionAnalysisAddPathsButton, &QPushButton::clicked, this, &MainWindow::on_addPathsButton_clicked);

    // Connect tiffZarrConverter signals
    connect(ui->tiffZarrConverterAddPathsButton,&QPushButton::clicked, this, &MainWindow::on_addPathsButton_clicked);

    // Output Window Threading
    mOutputWindow = new matlabOutputWindow(jobLogPaths,jobNames,this);
    //mOutputWindowThread = new matlabOutputWindowThread(jobLogPaths,this);
    //connect(mThreadManager, &matlabThreadManager::addOutputIDAndPath, mOutputWindowThread, &matlabOutputWindowThread::onAddOutputIDAndPath);

    // Disable all tabs except the main one on startup
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->DSR), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Stitch), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Decon), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Job), false);

    ui->simReconTab->setTabEnabled(ui->simReconTab->indexOf(ui->simReconDeskew),false);
    ui->simReconTab->setCurrentWidget(ui->simReconMain);

    // Set most recent Dir to Home initially
    mostRecentDir = QDir::homePath();

    // Check if version is up to date with what was last saved.
    //QSettings settings("ABC", "LLSM GUI");
    //settings.beginGroup("MainWindow");
    //QString savedVersion = settings.value("version").toString();
    //settings.endGroup();

    //QCoreApplication::setApplicationVersion(VERSION_STRING);
    //if(savedVersion == QCoreApplication::applicationVersion()){
    // Restore previous settings if user says yes
    readConfigSettings();
    checkLoadPrevSettings();
    if(loadSettings) readSettings();
    //}
    /*
    else{
        // If saved version is not the current version then reset values to avoid corruption
        outputLock.lock();
        std::cout << "New Version has been detected. Resetting saved settings to avoid corruption." << std::endl;
        outputLock.unlock();
        getMatlabPath(isMcc,pathToMatlab);
    }*/


    // Set current tab to the main tab
    ui->tabWidget->setCurrentWidget(ui->Main);

    // Job Output
    if(!mOutputWindow->isVisible()){
        mOutputWindow->setModal(false);
        mOutputWindow->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    // If the thread is not done, kill it (This may have to change later because it can be dangerous)
    if(!mThreadManager->isFinished()) mThreadManager->terminate();

}

// Event triggered when main window is closed
void MainWindow::closeEvent(QCloseEvent *event)
{
    // Write current user settings
    writeSettings();
    event->accept();

    // Close output window if visible
    if(mOutputWindow) mOutputWindow->close();
}

// Write user settings
void MainWindow::writeSettings()
{
    QSettings settings("ABC", "LLSM GUI");
    settings.beginGroup("MainWindow");
    settings.setValue("version", QCoreApplication::applicationVersion());

    // Config settings
    settings.setValue("configFile", cFileVals.configFile);
    settings.setValue("gpuConfigFile", cFileVals.gpuConfigFile);

    settings.beginWriteArray("dPaths");
    for(unsigned int i = 0; i < dPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("dPathsimasterPath", dPaths[i].masterPath);
        settings.setValue("dPathsiincludeMaster", dPaths[i].includeMaster);
        settings.setValue("dPathsipattern", dPaths[i].pattern);
        settings.setValue("dPathsimaxDepth", dPaths[i].maxDepth);
    }
    settings.endArray();

    for(unsigned int i = 0; i < dPaths.size(); i++)
    {
        settings.beginWriteArray(QString::number(i)+"bool");
        unsigned int j = 0;
        for(const auto &path : dPaths[i].subPaths){
            settings.setArrayIndex(j);
            settings.setValue("i"+QString::number(i)+"j"+QString::number(j)+"booli",path.second.first);
            j++;
        }
        settings.endArray();

        settings.beginWriteArray(QString::number(i)+"subPath");
        j = 0;
        for(const auto &path : dPaths[i].subPaths){
            settings.setArrayIndex(j);
            settings.setValue("i"+QString::number(i)+"j"+QString::number(j)+"subPathi",path.second.second);
            j++;
        }
        settings.endArray();
    }

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

    // Save custom patterns
    settings.setValue("customPatternsCheckBox",ui->customPatternsCheckBox->isChecked());
    settings.setValue("customPatterns", ui->customPatternsLineEdit->text());

    settings.setValue("skewAngle",guiVals.skewAngle);
    settings.setValue("dz",ui->dzLineEdit->text());
    settings.setValue("dzFromEncoder",ui->dzFromEncoderCheckBox->isChecked());
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

    // Decon Only Settings
    settings.setValue("deconOnly",ui->deconOnlyCheckBox->isChecked());
    settings.setValue("deconOnlyOnlyFirstTP",ui->deconOnlyOnlyFirstTPCheckBox->isChecked());
    settings.setValue("deconOnlyOverwriteData",ui->deconOnlyOverwriteDataCheckBox->isChecked());
    settings.setValue("deconOnlySave16Bit",ui->deconOnlySave16BitCheckBox->isChecked());

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
        settings.setValue("LSImagePathsi", lsImagePaths[i]);
    }
    settings.endArray();

    settings.beginWriteArray("BackgroundPaths");
    for(unsigned int i = 0; i < backgroundPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("BackgroundPathsi", backgroundPaths[i]);
    }
    settings.endArray();

    // Save DSR Advanced Settings
    settings.setValue("BKRemoval",guiVals.BKRemoval);
    settings.setValue("LowerLimit",guiVals.LowerLimit);
    settings.setValue("resampleType",guiVals.resampleType);
    settings.setValue("resampleEnabled",guiVals.resampleEnabled);
    settings.setValue("resampleY",QVariant::fromValue(guiVals.resample[0]));
    settings.setValue("resampleX",QVariant::fromValue(guiVals.resample[1]));
    settings.setValue("resampleZ",QVariant::fromValue(guiVals.resample[2]));

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

    settings.setValue("stitchMIPY", ui->stitchStitchMIPYSpinBox->value());
    settings.setValue("stitchMIPX", ui->stitchStitchMIPXSpinBox->value());
    settings.setValue("stitchMIPZ", ui->stitchStitchMIPZSpinBox->value());
    settings.setValue("onlineStitch", ui->stitchOnlineStitchCheckBox->isChecked());
    settings.setValue("generateImageList", ui->stitchGenerateImageListComboBox->currentText());

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
    settings.setValue("cppDeconPath",guiVals.cppDeconPath);
    settings.setValue("loadModules",guiVals.loadModules);
    settings.setValue("cudaDeconPath",guiVals.cudaDeconPath);
    settings.setValue("OTFGENPath",guiVals.OTFGENPath);
    settings.setValue("RLMethod",guiVals.RLMethod);
    settings.setValue("fixIter", guiVals.fixIter);
    settings.setValue("errThresh", guiVals.errThresh);
    settings.setValue("debug", guiVals.debug);
    settings.setValue("gpuJob", guiVals.gpuJob);

    settings.beginWriteArray("psfFullpaths");
    for(unsigned int i = 0; i < psfFullPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("psfFullpathsi", psfFullPaths[i]);
    }
    settings.endArray();

    settings.setValue("DeconIter", ui->deconIterationsLineEdit->text());
    settings.setValue("rotatedPSF", ui->rotatePSFCheckBox->isChecked());

    // Save Job Settings
    settings.setValue("parseCluster", ui->parseClusterCheckBox->isChecked());
    settings.setValue("cpusPerTask", ui->cpusPerTaskLineEdit->text());

    // Save Advanced Job Settings
    settings.setValue("largeFile",QVariant::fromValue(guiVals.largeFile));
    settings.setValue("largeMethod",QVariant::fromValue(guiVals.largeMethod));
    settings.setValue("zarrFile",QVariant::fromValue(guiVals.zarrFile));
    settings.setValue("saveZarr",QVariant::fromValue(guiVals.saveZarr));
    settings.setValue("save3DStack",QVariant::fromValue(guiVals.save3DStack));
    settings.setValue("jobLogDir",guiVals.jobLogDir);
    settings.setValue("uuid",guiVals.uuid);
    settings.setValue("maxTrialNum",QVariant::fromValue(guiVals.maxTrialNum));
    settings.setValue("unitWaitTime",QVariant::fromValue(guiVals.unitWaitTime));
    settings.setValue("minModifyTime",QVariant::fromValue(guiVals.minModifyTime));
    settings.setValue("maxModifyTime",QVariant::fromValue(guiVals.maxModifyTime));
    settings.setValue("maxWaitLoopNum",QVariant::fromValue(guiVals.maxWaitLoopNum));

    // ********* Save Sim Recon Settings *********
    settings.beginWriteArray("simReconDPaths");
    for(unsigned int i = 0; i < simReconDPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("simReconDPathsimasterPath", simReconDPaths[i].masterPath);
        settings.setValue("simReconDPathsiincludeMaster", simReconDPaths[i].includeMaster);
        settings.setValue("simReconDPathsipattern", simReconDPaths[i].pattern);
        settings.setValue("simReconDPathsimaxDepth", simReconDPaths[i].maxDepth);
    }
    settings.endArray();

    for(unsigned int i = 0; i < simReconDPaths.size(); i++)
    {
        settings.beginWriteArray("simRecon"+QString::number(i)+"bool");
        unsigned int j = 0;
        for(const auto &path : simReconDPaths[i].subPaths){
            settings.setArrayIndex(j);
            settings.setValue("simReconi"+QString::number(i)+"j"+QString::number(j)+"booli",path.second.first);
            j++;
        }
        settings.endArray();

        settings.beginWriteArray("simRecon"+QString::number(i)+"subPath");
        j = 0;
        for(const auto &path : simReconDPaths[i].subPaths){
            settings.setArrayIndex(j);
            settings.setValue("simReconi"+QString::number(i)+"j"+QString::number(j)+"subPathi",path.second.second);
            j++;
        }
        settings.endArray();
    }

    // Save Main Settings
    settings.setValue("simReconDeskew",ui->simReconDeskewCheckBox->isChecked());
    settings.setValue("simReconDeskewRecon",ui->simReconDeskewReconCheckBox->isChecked());
    settings.setValue("simReconDeskewOverwriteData",ui->simReconDeskewOverwriteDataCheckBox->isChecked());
    settings.setValue("simReconDeskewSave16Bit",ui->simReconDeskewSave16BitCheckBox->isChecked());
    settings.setValue("simReconDeskewOnlyFirstTP",ui->simReconDeskewOnlyFirstTPCheckBox->isChecked());

    settings.setValue("simReconReconOnly",ui->simReconReconOnlyCheckBox->isChecked());
    settings.setValue("simReconReconOnlyOverwriteData",ui->simReconReconOnlyOverwriteDataCheckBox->isChecked());
    settings.setValue("simReconReconOnlySave16Bit",ui->simReconReconOnlySave16BitCheckBox->isChecked());
    settings.setValue("simReconReconOnlyOnlyFirstTP",ui->simReconReconOnlyOnlyFirstTPCheckBox->isChecked());

    settings.setValue("simReconStreaming",ui->simReconStreamingCheckBox->isChecked());

    // SAVE FOR CHANNEL PATTERNS
    settings.beginWriteArray("simReconChannelLabels");
    for(unsigned int i = 0; i < simReconChannelWidgets.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("simReconChannelLabelsi", simReconChannelWidgets[i].first->text());
    }
    settings.endArray();

    settings.beginWriteArray("simReconChannelChecks");
    for(unsigned int i = 0; i < simReconChannelWidgets.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("simReconChannelChecksi", simReconChannelWidgets[i].second->isChecked());
    }
    settings.endArray();

    // Save custom patterns
    settings.setValue("simReconCustomPatternsCheckBox",ui->simReconCustomPatternsCheckBox->isChecked());
    settings.setValue("simReconCustomPatterns", ui->simReconCustomPatternsLineEdit->text());

    settings.setValue("simReconDZ",ui->simReconDZLineEdit->text());

    // Save Main Advanced settings
    settings.setValue("simReconskewAngle",simreconVals.skewAngle);
    settings.setValue("simReconxyPixelSize",simreconVals.xyPixelSize);
    settings.setValue("simReconReverse",simreconVals.Reverse);

    // Deskew settings (Empty for now)

    // Recon settings
    settings.setValue("simReconBackgroundIntensity",ui->simReconBackgroundIntensityLineEdit->text());
    settings.setValue("simReconDZPSF",ui->simReconDZPSFLineEdit->text());

    settings.beginWriteArray("simReconPsfFullPaths");
    for(unsigned int i = 0; i < simReconPsfFullPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("simReconPsfFullPathsi", simReconPsfFullPaths[i]);
    }
    settings.endArray();

    settings.setValue("simReconNPhases",ui->simReconNPhasesLineEdit->text());
    settings.setValue("simReconNOrientations",ui->simReconNOrientationsLineEdit->text());
    settings.setValue("simReconLatticePeriod",ui->simReconLatticePeriodLineEdit->text());
    settings.setValue("simReconEdgeErosion",ui->simReconEdgeErosionLineEdit->text());
    settings.setValue("simReconErodeBefore",ui->simReconErodeBeforeCheckBox->isChecked());
    settings.setValue("simReconErodeAfter",ui->simReconErodeAfterCheckBox->isChecked());
    settings.setValue("simReconApodize",ui->simReconApodizeCheckBox->isChecked());
    settings.setValue("simReconDeskewed",ui->simReconDeskewedCheckBox->isChecked());

    // Recon Advanced Settings
    settings.setValue("simReconislattice",simreconVals.islattice);
    settings.setValue("simReconNA_det",simreconVals.NA_det);
    settings.setValue("simReconNA_ext",simreconVals.NA_ext);
    settings.setValue("simReconnimm",simreconVals.nimm);
    settings.setValue("simReconwvl_em",simreconVals.wvl_em);
    settings.setValue("simReconwvl_ext",simreconVals.wvl_ext);
    settings.setValue("simReconw",simreconVals.w);
    settings.setValue("simReconnormalize_orientations",simreconVals.normalize_orientations);
    settings.setValue("simReconresultsDirName",simreconVals.resultsDirName);
    settings.setValue("simReconperdecomp",simreconVals.perdecomp);
    settings.setValue("simReconedgeTaper",simreconVals.edgeTaper);
    settings.setValue("simReconedgeTaperVal",simreconVals.edgeTaperVal);
    settings.setValue("simReconintThresh",simreconVals.intThresh);
    settings.setValue("simReconoccThresh",simreconVals.occThresh);
    settings.setValue("simReconuseGPU",simreconVals.useGPU);
    settings.setValue("simRecongpuPrecision",simreconVals.gpuPrecision);
    settings.setValue("simReconOverlap",simreconVals.Overlap);
    settings.setValue("simReconChunkSizeY",simreconVals.ChunkSize[0]);
    settings.setValue("simReconChunkSizeX",simreconVals.ChunkSize[1]);
    settings.setValue("simReconChunkSizeZ",simreconVals.ChunkSize[2]);
    settings.setValue("simReconreconBatchNum",simreconVals.reconBatchNum);

    // Job Settings
    settings.setValue("simReconParseCluster",ui->simReconParseClusterCheckBox->isChecked());
    settings.setValue("simReconCpusPerTask",ui->simReconCpusPerTaskLineEdit->text());

    // Job Advanced settings
    settings.setValue("simReconjobLogDir",simreconVals.jobLogDir);
    settings.setValue("simReconuuid",simreconVals.uuid);
    settings.setValue("simReconmaxTrialNum",QVariant::fromValue(simreconVals.maxTrialNum));
    settings.setValue("simReconunitWaitTime",QVariant::fromValue(simreconVals.unitWaitTime));
    settings.setValue("simReconparPoolSize",QVariant::fromValue(simreconVals.parPoolSize));
    settings.setValue("simReconmaxModifyTime",QVariant::fromValue(simreconVals.maxModifyTime));

    // ********* Save Crop Settings *********
    // Save Data Paths
    settings.beginWriteArray("cropDPaths");
    for(unsigned int i = 0; i < cropDPaths.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("cropDPathsimasterPath", cropDPaths[i].masterPath);
        settings.setValue("cropDPathsiincludeMaster", cropDPaths[i].includeMaster);
        settings.setValue("cropDPathsipattern", cropDPaths[i].pattern);
        settings.setValue("cropDPathsimaxDepth", cropDPaths[i].maxDepth);
    }
    settings.endArray();

    for(unsigned int i = 0; i < cropDPaths.size(); i++)
    {
        settings.beginWriteArray("crop"+QString::number(i)+"bool");
        unsigned int j = 0;
        for(const auto &path : cropDPaths[i].subPaths){
            settings.setArrayIndex(j);
            settings.setValue("cropi"+QString::number(i)+"j"+QString::number(j)+"booli",path.second.first);
            j++;
        }
        settings.endArray();

        settings.beginWriteArray("crop"+QString::number(i)+"subPath");
        j = 0;
        for(const auto &path : cropDPaths[i].subPaths){
            settings.setArrayIndex(j);
            settings.setValue("cropi"+QString::number(i)+"j"+QString::number(j)+"subPathi",path.second.second);
            j++;
        }
        settings.endArray();
    }

    // SAVE FOR CHANNEL PATTERNS
    settings.beginWriteArray("cropChannelLabels");
    for(unsigned int i = 0; i < cropChannelWidgets.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("cropChannelLabelsi", cropChannelWidgets[i].first->text());
    }
    settings.endArray();

    settings.beginWriteArray("cropChannelChecks");
    for(unsigned int i = 0; i < cropChannelWidgets.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("cropChannelChecksi", cropChannelWidgets[i].second->isChecked());
    }
    settings.endArray();

    // Save custom patterns
    settings.setValue("cropCustomPatternsCheckBox",ui->cropCustomPatternsCheckBox->isChecked());
    settings.setValue("cropCustomPatterns", ui->cropCustomPatternsLineEdit->text());

    settings.setValue("cropCropType",ui->cropCropTypeComboBox->currentText());

    settings.setValue("cropBoundBoxYMin",ui->cropBoundBoxYMinSpinBox->value());
    settings.setValue("cropBoundBoxXMin",ui->cropBoundBoxXMinSpinBox->value());
    settings.setValue("cropBoundBoxZMin",ui->cropBoundBoxZMinSpinBox->value());
    settings.setValue("cropBoundBoxYMax",ui->cropBoundBoxYMaxSpinBox->value());
    settings.setValue("cropBoundBoxXMax",ui->cropBoundBoxXMaxSpinBox->value());
    settings.setValue("cropBoundBoxZMax",ui->cropBoundBoxZMaxSpinBox->value());

    settings.setValue("cropLastStartY",ui->cropLastStartYSpinBox->value());
    settings.setValue("cropLastStartX",ui->cropLastStartYSpinBox->value());
    settings.setValue("cropLastStartZ",ui->cropLastStartYSpinBox->value());

    settings.setValue("cropSave16Bit",ui->cropSave16BitCheckBox->isChecked());
    settings.setValue("cropPad",ui->cropPadCheckBox->isChecked());

    settings.setValue("cropResultPath", ui->cropResultPathLineEdit->text());
    settings.setValue("cropParseCluster", ui->cropParseClusterCheckBox->isChecked());
    settings.setValue("cropCpusPerTask", ui->cropCpusPerTaskLineEdit->text());
    settings.setValue("cropMasterCompute",ui->cropMasterComputeCheckBox->isChecked());
    settings.setValue("cropJobLogDir",ui->cropJobLogDirLineEdit->text());
    settings.setValue("cropUuid",ui->cropUuidLineEdit->text());

    settings.endGroup();
}

void MainWindow::readConfigSettings(){
    QSettings settings("ABC", "LLSM GUI");
    settings.beginGroup("MainWindow");
    cFileVals.configFile = settings.value("configFile").toString();
    cFileVals.gpuConfigFile = settings.value("gpuConfigFile").toString();
    settings.endGroup();
}

// Restore previous user settings
void MainWindow::readSettings()
{
    QSettings settings("ABC", "LLSM GUI");
    settings.beginGroup("MainWindow");

    // Read Data Paths
    int size = settings.beginReadArray("dPaths");
    for (int i = 0; i < size; i++){
        settings.setArrayIndex(i);
        dPaths.push_back(dataPath());
        dPaths[i].masterPath = settings.value("dPathsimasterPath").toString();
        dPaths[i].includeMaster = settings.value("dPathsiincludeMaster").toBool();
        dPaths[i].pattern = settings.value("dPathsipattern").toString();
        dPaths[i].maxDepth = settings.value("dPathsimaxDepth").toInt();
    }
    settings.endArray();

    for(size_t i = 0; i < dPaths.size(); i++){
        std::vector<QString> subPaths;
        std::vector<bool> include;

        size = settings.beginReadArray(QString::number(i)+"bool");
        for(int j = 0; j < size; j++){
            settings.setArrayIndex(j);
            include.push_back(settings.value("i"+QString::number(i)+"j"+QString::number(j)+"booli").toBool());
        }
        settings.endArray();

        size = settings.beginReadArray(QString::number(i)+"subPath");
        for(int j = 0; j < size; j++){
            settings.setArrayIndex(j);
            subPaths.push_back(settings.value("i"+QString::number(i)+"j"+QString::number(j)+"subPathi").toString());
        }
        settings.endArray();

        for(int j = 0; j < size; j++){
            dPaths[i].subPaths.emplace(subPaths[j],std::make_pair(include[j],subPaths[j]));
        }

    }

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
    for(int i = 0; i < size; i++){
        settings.setArrayIndex(i);
        tLabels.push_back(settings.value("channelLabelsi").toString());
    }
    settings.endArray();

    size = settings.beginReadArray("channelChecks");
    for(int i = 0; i < size; i++){
        settings.setArrayIndex(i);
        tChecks.push_back(settings.value("channelChecksi").toBool());
    }
    settings.endArray();

    // Read custom patterns
    ui->customPatternsCheckBox->setChecked(settings.value("customPatternsCheckBox").toBool());
    ui->customPatternsLineEdit->setText(settings.value("customPatterns").toString());

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
    ui->dzFromEncoderCheckBox->setChecked(settings.value("dzFromEncoder").toBool());
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

    ui->deconOnlyCheckBox->setChecked(settings.value("deconOnly").toBool());
    ui->deconOnlyOnlyFirstTPCheckBox->setChecked(settings.value("deconOnlyOnlyFirstTP").toBool());
    ui->deconOnlyOverwriteDataCheckBox->setChecked(settings.value("deconOnlyOverwriteData").toBool());
    ui->deconOnlySave16BitCheckBox->setChecked(settings.value("deconOnlySave16Bit").toBool());

    ui->deskewDeconCheckBox->setChecked(settings.value("deskewDecon").toBool());
    ui->rotateDeconCheckBox->setChecked(settings.value("rotateDecon").toBool());
    ui->deskewAndRotateDeconCheckBox->setChecked(settings.value("deskewAndRotateDecon").toBool());
    ui->stitchDeconCheckBox->setChecked(settings.value("stitchDecon").toBool());

    // Read DSR Settings

    ui->parseSettingsFileCheckBox->setChecked(settings.value("parseSettingFile").toBool());
    ui->flipZStackCheckBox->setChecked(settings.value("flipZstack").toBool());

    ui->llffCorrectionCheckBox->setChecked(settings.value("LLFFCorrection").toBool());

    size = settings.beginReadArray("LSImagePaths");
    for(int i = 0; i < size; i++){
        settings.setArrayIndex(i);
        lsImagePaths.push_back(settings.value("LSImagePathsi").toString());
    }
    settings.endArray();

    size = settings.beginReadArray("BackgroundPaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        backgroundPaths.push_back(settings.value("BackgroundPathsi").toString());
    }
    settings.endArray();

    // Read DSR Advanced Settings

    guiVals.BKRemoval = settings.value("BKRemoval").toBool();
    guiVals.LowerLimit = settings.value("LowerLimit").toDouble();
    guiVals.resampleType = settings.value("resampleType").toString();
    guiVals.resampleEnabled =settings.value("resampleEnabled").toBool();
    guiVals.resample[0] = settings.value("resampleY").toDouble();
    guiVals.resample[1] = settings.value("resampleX").toDouble();
    guiVals.resample[2] = settings.value("resampleZ").toDouble();

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

    ui->stitchStitchMIPYSpinBox->setValue(settings.value("stitchMIPY").toInt());
    ui->stitchStitchMIPXSpinBox->setValue(settings.value("stitchMIPX").toInt());
    ui->stitchStitchMIPZSpinBox->setValue(settings.value("stitchMIPZ").toInt());
    ui->stitchOnlineStitchCheckBox->setChecked(settings.value("onlineStitch").toBool());
    ui->stitchGenerateImageListComboBox->setCurrentText(settings.value("generateImageList").toString());


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

    guiVals.cppDeconPath = settings.value("cppDeconPath").toString();
    guiVals.loadModules = settings.value("loadModules").toString();
    guiVals.cudaDeconPath = settings.value("cudaDeconPath").toString();
    guiVals.OTFGENPath = settings.value("OTFGENPath").toString();
    guiVals.RLMethod = settings.value("RLMethod").toString();
    guiVals.fixIter = settings.value("fixIter").toBool();
    guiVals.errThresh = settings.value("errThresh").toDouble();
    guiVals.debug = settings.value("debug").toBool();
    guiVals.gpuJob = settings.value("gpuJob").toBool();

    size = settings.beginReadArray("psfFullpaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        psfFullPaths.push_back(settings.value("psfFullpathsi").toString());
    }
    settings.endArray();

    ui->deconIterationsLineEdit->setText(settings.value("DeconIter").toString());
    ui->rotatePSFCheckBox->setChecked(settings.value("rotatedPSF").toBool());

    // Read Job Settings
    ui->parseClusterCheckBox->setChecked(settings.value("parseCluster").toBool());
    ui->cpusPerTaskLineEdit->setText(settings.value("cpusPerTask").toString());

    // Read Advanced Job Settings
    guiVals.largeFile = settings.value("largeFile").toBool();
    guiVals.largeMethod = settings.value("largeMethod").toString();
    guiVals.zarrFile = settings.value("zarrFile").toBool();
    guiVals.saveZarr = settings.value("saveZarr").toBool();
    guiVals.save3DStack = settings.value("save3DStack").toBool();
    guiVals.jobLogDir = settings.value("jobLogDir").toString();
    guiVals.uuid = settings.value("uuid").toString();
    guiVals.maxTrialNum = settings.value("maxTrialNum").toULongLong();
    guiVals.unitWaitTime = settings.value("unitWaitTime").toULongLong();
    guiVals.minModifyTime = settings.value("minModifyTime").toULongLong();
    guiVals.maxModifyTime = settings.value("maxModifyTime").toULongLong();
    guiVals.maxWaitLoopNum = settings.value("maxWaitLoopNum").toULongLong();

    // ********* Read Sim Recon Settings *********

    // Read Data Paths
    size = settings.beginReadArray("simReconDPaths");
    for (int i = 0; i < size; i++){
        settings.setArrayIndex(i);
        simReconDPaths.push_back(dataPath());
        simReconDPaths[i].masterPath = settings.value("simReconDPathsimasterPath").toString();
        simReconDPaths[i].includeMaster = settings.value("simReconDPathsiincludeMaster").toBool();
        simReconDPaths[i].pattern = settings.value("simReconDPathsipattern").toString();
        simReconDPaths[i].maxDepth = settings.value("simReconDPathsimaxDepth").toInt();
    }
    settings.endArray();

    for(size_t i = 0; i < simReconDPaths.size(); i++){
        std::vector<QString> subPaths;
        std::vector<bool> include;

        size = settings.beginReadArray("simRecon"+QString::number(i)+"bool");
        for(int j = 0; j < size; j++){
            settings.setArrayIndex(j);
            include.push_back(settings.value("simReconi"+QString::number(i)+"j"+QString::number(j)+"booli").toBool());
        }
        settings.endArray();

        size = settings.beginReadArray("simRecon"+QString::number(i)+"subPath");
        for(int j = 0; j < size; j++){
            settings.setArrayIndex(j);
            subPaths.push_back(settings.value("simReconi"+QString::number(i)+"j"+QString::number(j)+"subPathi").toString());
        }
        settings.endArray();

        for(int j = 0; j < size; j++){
            simReconDPaths[i].subPaths.emplace(subPaths[j],std::make_pair(include[j],subPaths[j]));
        }

    }

    // Read Main Settings
    ui->simReconDeskewCheckBox->setChecked(settings.value("simReconDeskew").toBool());
    ui->simReconDeskewReconCheckBox->setChecked(settings.value("simReconDeskewRecon").toBool());
    ui->simReconDeskewOverwriteDataCheckBox->setChecked(settings.value("simReconDeskewOverwriteData").toBool());
    ui->simReconDeskewSave16BitCheckBox->setChecked(settings.value("simReconDeskewSave16Bit").toBool());
    ui->simReconDeskewOnlyFirstTPCheckBox->setChecked(settings.value("simReconDeskewOnlyFirstTP").toBool());

    ui->simReconReconOnlyCheckBox->setChecked(settings.value("simReconReconOnly").toBool());
    ui->simReconReconOnlyOverwriteDataCheckBox->setChecked(settings.value("simReconReconOnlyOverwriteData").toBool());
    ui->simReconReconOnlySave16BitCheckBox->setChecked(settings.value("simReconReconOnlySave16Bit").toBool());
    ui->simReconReconOnlyOnlyFirstTPCheckBox->setChecked(settings.value("simReconReconOnlyOnlyFirstTP").toBool());

    ui->simReconStreamingCheckBox->setChecked(settings.value("simReconStreaming").toBool());

    // READ FOR CHANNEL PATTERNS
    // temp vectors to hold labels and checkbox values
    std::vector<QString> simReconTLabels;
    std::vector<bool> simReconTChecks;

    // Read labels and checks into vectors
    size = settings.beginReadArray("simReconChannelLabels");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        simReconTLabels.push_back(settings.value("simReconChannelLabelsi").toString());
    }
    settings.endArray();

    size = settings.beginReadArray("simReconChannelChecks");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        simReconTChecks.push_back(settings.value("simReconChannelChecksi").toBool());
    }
    settings.endArray();

    // Read custom patterns
    ui->simReconCustomPatternsCheckBox->setChecked(settings.value("simReconCustomPatternsCheckBox").toBool());
    ui->simReconCustomPatternsLineEdit->setText(settings.value("simReconCustomPatterns").toString());

    // Create widgets and put them in channelWidgets
    for(size_t i = 0; i < simReconTLabels.size(); i++){
        QLabel* label = new QLabel(ui->simReconMain);
        label->setTextFormat(Qt::RichText);
        label->setText("<b>"+simReconTLabels[i]+"<\b>");
        ui->simReconChannelPatternsHorizontalLayout->addWidget(label);

        QCheckBox* checkBox = new QCheckBox(ui->simReconMain);
        checkBox->setChecked(simReconTChecks[i]);
        ui->simReconChannelPatternsHorizontalLayout->addWidget(checkBox);

        simReconChannelWidgets.push_back(std::make_pair(label,checkBox));
    }

    ui->simReconDZLineEdit->setText(settings.value("simReconDZ").toString());

    // Read Main Advanced settings
    simreconVals.skewAngle = settings.value("simReconskewAngle").toDouble();
    simreconVals.xyPixelSize = settings.value("simReconxyPixelSize").toDouble();
    simreconVals.Reverse = settings.value("simReconReverse").toBool();

    // Deskew settings (Empty for now)

    // Recon settings
    ui->simReconBackgroundIntensityLineEdit->setText(settings.value("simReconBackgroundIntensity").toString());
    ui->simReconDZPSFLineEdit->setText(settings.value("simReconDZPSF").toString());

    size = settings.beginReadArray("simReconPsfFullPaths");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        simReconPsfFullPaths.push_back(settings.value("simReconPsfFullPathsi").toString());
    }
    settings.endArray();

    ui->simReconNPhasesLineEdit->setText(settings.value("simReconNPhases").toString());
    ui->simReconNOrientationsLineEdit->setText(settings.value("simReconNOrientations").toString());
    ui->simReconLatticePeriodLineEdit->setText(settings.value("simReconLatticePeriod").toString());
    ui->simReconEdgeErosionLineEdit->setText(settings.value("simReconEdgeErosion").toString());
    ui->simReconErodeBeforeCheckBox->setChecked(settings.value("simReconErodeBefore").toBool());
    ui->simReconErodeAfterCheckBox->setChecked(settings.value("simReconErodeAfter").toBool());
    ui->simReconApodizeCheckBox->setChecked(settings.value("simReconApodize").toBool());
    ui->simReconDeskewedCheckBox->setChecked(settings.value("simReconDeskewed").toBool());

    // Recon Advanced Settings

    simreconVals.islattice = settings.value("simReconislattice").toBool();
    simreconVals.NA_det = settings.value("simReconNA_det").toDouble();
    simreconVals.NA_ext = settings.value("simReconNA_ext").toDouble();
    simreconVals.nimm = settings.value("simReconnimm").toDouble();
    simreconVals.wvl_em = settings.value("simReconwvl_em").toDouble();
    simreconVals.wvl_ext = settings.value("simReconwvl_ext").toDouble();
    simreconVals.w = settings.value("simReconw").toDouble();
    simreconVals.normalize_orientations = settings.value("simReconnormalize_orientations").toBool();
    simreconVals.resultsDirName = settings.value("simReconresultsDirName").toString();
    simreconVals.perdecomp = settings.value("simReconperdecomp").toBool();
    simreconVals.edgeTaper = settings.value("simReconedgeTaper").toBool();
    simreconVals.edgeTaperVal = settings.value("simReconedgeTaperVal").toBool();
    simreconVals.intThresh = settings.value("simReconintThresh").toDouble();
    simreconVals.occThresh = settings.value("simReconoccThresh").toDouble();
    simreconVals.useGPU = settings.value("simReconuseGPU").toBool();
    simreconVals.gpuPrecision = settings.value("simRecongpuPrecision").toString();
    simreconVals.Overlap = settings.value("simReconOverlap").toDouble();
    simreconVals.ChunkSize[0] = settings.value("simReconChunkSizeY").toDouble();
    simreconVals.ChunkSize[1] = settings.value("simReconChunkSizeX").toDouble();
    simreconVals.ChunkSize[2] = settings.value("simReconChunkSizeZ").toDouble();
    simreconVals.reconBatchNum = settings.value("simReconreconBatchNum").toDouble();

    // Job Settings
    ui->simReconParseClusterCheckBox->setChecked(settings.value("simReconParseCluster").toBool());
    ui->simReconCpusPerTaskLineEdit->setText(settings.value("simReconCpusPerTask").toString());

    // Job Advanced settings
    simreconVals.jobLogDir = settings.value("simReconjobLogDir").toString();
    simreconVals.uuid = settings.value("simReconuuid").toString();
    simreconVals.maxTrialNum = settings.value("simReconmaxTrialNum").toDouble();
    simreconVals.unitWaitTime = settings.value("simReconunitWaitTime").toDouble();
    simreconVals.parPoolSize = settings.value("simReconparPoolSize").toDouble();
    simreconVals.maxModifyTime = settings.value("simReconmaxModifyTime").toDouble();

    // ********* Read Crop Settings *********
    // Read Data Paths
    size = settings.beginReadArray("cropDPaths");
    for (int i = 0; i < size; i++){
        settings.setArrayIndex(i);
        cropDPaths.push_back(dataPath());
        cropDPaths[i].masterPath = settings.value("cropDPathsimasterPath").toString();
        cropDPaths[i].includeMaster = settings.value("cropDPathsiincludeMaster").toBool();
        cropDPaths[i].pattern = settings.value("cropDPathsipattern").toString();
        cropDPaths[i].maxDepth = settings.value("cropDPathsimaxDepth").toInt();
    }
    settings.endArray();

    for(size_t i = 0; i < cropDPaths.size(); i++){
        std::vector<QString> subPaths;
        std::vector<bool> include;

        size = settings.beginReadArray("crop"+QString::number(i)+"bool");
        for(int j = 0; j < size; j++){
            settings.setArrayIndex(j);
            include.push_back(settings.value("cropi"+QString::number(i)+"j"+QString::number(j)+"booli").toBool());
        }
        settings.endArray();

        size = settings.beginReadArray("crop"+QString::number(i)+"subPath");
        for(int j = 0; j < size; j++){
            settings.setArrayIndex(j);
            subPaths.push_back(settings.value("cropi"+QString::number(i)+"j"+QString::number(j)+"subPathi").toString());
        }
        settings.endArray();

        for(int j = 0; j < size; j++){
            cropDPaths[i].subPaths.emplace(subPaths[j],std::make_pair(include[j],subPaths[j]));
        }

    }

    // temp vectors to hold labels and checkbox values
    tLabels.clear();
    tChecks.clear();

    // READ FOR CHANNEL PATTERNS
    size = settings.beginReadArray("cropChannelLabels");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        tLabels.push_back(settings.value("cropChannelLabelsi").toString());
    }
    settings.endArray();

    size = settings.beginReadArray("cropChannelChecks");
    for(int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        tChecks.push_back(settings.value("cropChannelChecksi").toBool());
    }
    settings.endArray();

    // Create widgets and put them in channelWidgets
    for(size_t i = 0; i < tLabels.size(); i++){
        QLabel* label = new QLabel(ui->Crop);
        label->setTextFormat(Qt::RichText);
        label->setText("<b>"+tLabels[i]+"<\b>");
        ui->cropChannelPatternsHorizontalLayout->addWidget(label);

        QCheckBox* checkBox = new QCheckBox(ui->Crop);
        checkBox->setChecked(tChecks[i]);
        ui->cropChannelPatternsHorizontalLayout->addWidget(checkBox);

        cropChannelWidgets.push_back(std::make_pair(label,checkBox));
    }

    // Read custom patterns
    ui->cropCustomPatternsCheckBox->setChecked(settings.value("cropCustomPatternsCheckBox").toBool());
    ui->cropCustomPatternsLineEdit->setText(settings.value("cropCustomPatterns").toString());

    ui->cropCropTypeComboBox->setCurrentText(settings.value("cropCropType").toString());

    ui->cropBoundBoxYMinSpinBox->setValue(settings.value("cropBoundBoxYMin").toULongLong());
    ui->cropBoundBoxXMinSpinBox->setValue(settings.value("cropBoundBoxXMin").toULongLong());
    ui->cropBoundBoxZMinSpinBox->setValue(settings.value("cropBoundBoxZMin").toULongLong());
    ui->cropBoundBoxYMaxSpinBox->setValue(settings.value("cropBoundBoxYMax").toULongLong());
    ui->cropBoundBoxXMaxSpinBox->setValue(settings.value("cropBoundBoxXMax").toULongLong());
    ui->cropBoundBoxZMaxSpinBox->setValue(settings.value("cropBoundBoxZMax").toULongLong());

    ui->cropLastStartYSpinBox->setValue(settings.value("cropLastStartY").toULongLong());
    ui->cropLastStartXSpinBox->setValue(settings.value("cropLastStartX").toULongLong());
    ui->cropLastStartZSpinBox->setValue(settings.value("cropLastStartZ").toULongLong());

    ui->cropSave16BitCheckBox->setChecked(settings.value("cropSave16Bit").toBool());
    ui->cropPadCheckBox->setChecked(settings.value("cropPad").toBool());

    ui->cropResultPathLineEdit->setText(settings.value("cropResultPath").toString());
    ui->cropParseClusterCheckBox->setChecked(settings.value("cropParseCluster").toBool());
    ui->cropCpusPerTaskLineEdit->setText(settings.value("cropCpusPerTask").toString());
    ui->cropMasterComputeCheckBox->setChecked(settings.value("cropMasterCompute").toBool());
    ui->cropJobLogDirLineEdit->setText(settings.value("cropJobLogDir").toString());
    ui->cropUuidLineEdit->setText(settings.value("cropUuid").toString());

    settings.endGroup();
}

// Reenable submit button for new jobs
void MainWindow::onEnableSubmitButton()
{
    ui->mipGeneratorSubmitButton->setEnabled(true);
    ui->parallelRsyncSubmitButton->setEnabled(true);
    ui->fftAnalysisSubmitButton->setEnabled(true);
    ui->fscAnalysisSubmitButton->setEnabled(true);
    ui->simReconSubmitButton->setEnabled(true);
    ui->cropSubmitButton->setEnabled(true);
    ui->submitButton->setEnabled(true);
    ui->tiffZarrConverterSubmitButton->setEnabled(true);
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
    // Testing object list. Looping through all widgets
    /*
    QList<QWidget *> widgetList = ui->tabWidget->findChildren<QWidget *>();
    std::cout << "Amount of c " << std::endl;
    std::cout << "Amount of children found : " << widgetList.count() << std::endl;
    for(auto widget : widgetList){
        if(widget->objectName().toStdString().find("CheckBox") != QString::npos){
            std::cout << widget->objectName().toStdString() << std::endl;
        }
    }
    return;
    */

    // Save settings in case of crash
    writeSettings();

    // TODO: Seperate functions for error checking

    // Error if data path does not exist when submit is pressed
    for(size_t i = 0; i < dPaths.size(); i++){
        if(dPaths[i].includeMaster){
            if(!QFileInfo::exists(dPaths[i].masterPath)){
                messageBoxError("Data path \"" + dPaths[i].masterPath + "\" does not exist!");
                return;
            }
        }
        for (const auto &subPath : dPaths[i].subPaths){
            if(subPath.second.first){
                if(!QFileInfo::exists(subPath.second.second)){
                    messageBoxError("Data path \"" + subPath.second.second + "\" does not exist!");
                    return;
                }
            }
        }
    }

    // Error if decon is set but no psf paths are set
    if((ui->deconOnlyCheckBox->isChecked() || ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked()) && !psfFullPaths.size()){
        messageBoxError("Decon is set but there are no psf paths set");
        return;
    }
    else if((ui->deconOnlyCheckBox->isChecked() || ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked())){
        for(const QString &path : psfFullPaths){
            if(path.isEmpty()){
                messageBoxError("One of the PSF paths is empty!");
                return;
            }
            else if(!QFileInfo::exists(path)){
                messageBoxError("Psf path \"" + path + "\" does not exist!");
                return;
            }
        }
    }

    // Make it so the user can't submit another job while we are submitting this one
    ui->submitButton->setEnabled(false);

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    //
    // TODO: GOING TO REDO THIS PORTION AND MAKE A FUNCTION SO I CAN SUPPORT MULTIPLE SCRIPTS EASIER
    //

    // Set main path. This is where all the output files made by the GUI will be stored if a job log dir does not exist.
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd_HHmm_");
    QString timeJobName = dateTime+QString(ui->jobNameLineEdit->text()).replace(" ","_");
    QString mainPath = dPaths[0].masterPath+"/job_logs/"+timeJobName;

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }

    // We reset jobLogDir to what it was before at the end of this function
    QString jobLogCopy = guiVals.jobLogDir;

    // Check for job log directory for main job
    checkJobLogDir(guiVals, mainPath, timeJobName);


    if(ui->deconOnlyCheckBox->isChecked()){
        // Data Paths
        addDataPathsToArgs(args,firstPrependedString,dPaths,isMcc);

        // Main Settings
        // TODO: Logic (in bool array 4th value is all decon, 5th value is rotate after decon)
        // TODO: FIX LOGIC FOR DECON ONLY
        addCharArrayToArgs(args,"Overwrite",prependedString,isMcc);
        if(ui->deconOnlyCheckBox->isChecked()) addBoolToArgs(args,false,prependedString);
        else if(ui->deskewOverwriteDataCheckBox->isChecked() && ui->rotateOverwriteDataCheckBox->isChecked() && ui->deskewAndRotateOverwriteDataCheckBox->isChecked() && ui->stitchOverwriteDataCheckBox->isChecked()) addBoolToArgs(args,true,prependedString);
        else{
            std::vector<std::string> OverwriteV = {btosM(ui->deskewOverwriteDataCheckBox->isChecked()),btosM(ui->rotateOverwriteDataCheckBox->isChecked()),btosM(ui->stitchOverwriteDataCheckBox->isChecked()),btosM(false),btosM(false)};
            addArrayToArgs(args,OverwriteV,false,prependedString,"[]",isMcc);
        }

        // Channel Patterns
        addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
        addChannelPatternsToArgs(args,channelWidgets,ui->customPatternsCheckBox->isChecked(),ui->customPatternsLineEdit->text(),prependedString,isMcc);

        // Currently not used
        //data.push_back(factory.createCharArray("Channels"));
        //data.push_back(factory.createArray<uint64_t>({1,3},{488,560,642}));

        addCharArrayToArgs(args,"SkewAngle",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.skewAngle),prependedString);

        addCharArrayToArgs(args,"dz",prependedString,isMcc);
        addScalarToArgs(args,ui->dzLineEdit->text().toStdString(),prependedString);

        //**** For when dzFromEncoder is implemented into the decon wrapper ****
        //data.push_back(factory.createCharArray("dzFromEncoder"));
        //data.push_back(factory.createScalar<bool>(ui->dzFromEncoderCheckBox->isChecked()));

        addCharArrayToArgs(args,"xyPixelSize",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.xyPixelSize),prependedString);

        addCharArrayToArgs(args,"Reverse",prependedString,isMcc);
        addBoolToArgs(args,guiVals.Reverse,prependedString);

        addCharArrayToArgs(args,"ObjectiveScan",prependedString,isMcc);
        addBoolToArgs(args,ui->objectiveScanCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"sCMOSCameraFlip",prependedString,isMcc);
        addBoolToArgs(args,guiVals.sCMOSCameraFlip,prependedString);

        // This needs to change FIX
        // TODO: FIX LOGIC FOR DECON ONLY
        addCharArrayToArgs(args,"Save16bit",prependedString,isMcc);
        if (ui->deconOnlySave16BitCheckBox->isChecked()) addBoolToArgs(args,true,prependedString);
        else addBoolToArgs(args,false,prependedString);

        // This needs to change FIX
        addCharArrayToArgs(args,"onlyFirstTP",prependedString,isMcc);
        addBoolToArgs(args,ui->deskewOnlyFirstTPCheckBox->isChecked() || ui->rotateOnlyFirstTPCheckBox->isChecked() || ui->deskewAndRotateOnlyFirstTPCheckBox->isChecked() || ui->stitchOnlyFirstTPCheckBox->isChecked(),prependedString);

        // Pipeline Setting
        addCharArrayToArgs(args,"Decon",prependedString,isMcc);
        addBoolToArgs(args,ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked(),prependedString);

        // Change later
        //data.push_back(factory.createCharArray("RotateAfterDecon"));
        //data.push_back(factory.createScalar<bool>(ui->rotateAfterDeconCheckBox->isChecked()));

        // Decon Settings
        addCharArrayToArgs(args,"cudaDecon",prependedString,isMcc);
        addBoolToArgs(args,ui->cudaDeconRadioButton->isChecked(),prependedString);

        addCharArrayToArgs(args,"cppDecon",prependedString,isMcc);
        addBoolToArgs(args,ui->cppDeconRadioButton->isChecked(),prependedString);

        addCharArrayToArgs(args,"Background",prependedString,isMcc);
        addScalarToArgs(args,ui->backgroundIntensityLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"dzPSF",prependedString,isMcc);
        addScalarToArgs(args,ui->dzPSFLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"EdgeErosion",prependedString,isMcc);
        addScalarToArgs(args,ui->edgeErosionLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"ErodeByFTP",prependedString,isMcc);
        addBoolToArgs(args,ui->erodeByFTPCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"deconRotate",prependedString,isMcc);
        addBoolToArgs(args,ui->deconRotateCheckBox->isChecked(),prependedString);

        // Decon Advanced settings
        if(!guiVals.cppDeconPath.isEmpty()){
            addCharArrayToArgs(args,"cppDeconPath",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.cppDeconPath.toStdString(),prependedString,isMcc);
        }
        if(!guiVals.loadModules.isEmpty()){
            addCharArrayToArgs(args,"loadModules",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.loadModules.toStdString(),prependedString,isMcc);
        }
        if(!guiVals.cudaDeconPath.isEmpty()){
            addCharArrayToArgs(args,"cudaDeconPath",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.cudaDeconPath.toStdString(),prependedString,isMcc);
        }
        if(!guiVals.OTFGENPath.isEmpty()){
            addCharArrayToArgs(args,"OTFGENPath",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.OTFGENPath.toStdString(),prependedString,isMcc);
        }

        if(psfFullPaths.size()){
            addCharArrayToArgs(args,"psfFullpaths",prependedString,isMcc);
            std::vector<std::string> psfMPaths;
            for(size_t i = 0; i < psfFullPaths.size(); i++){
                psfMPaths.push_back(psfFullPaths[i].toStdString());
            }
            addArrayToArgs(args,psfMPaths,true,prependedString,"{}",isMcc);
        }
        addCharArrayToArgs(args,"RLMethod",prependedString,isMcc);
        addCharArrayToArgs(args,guiVals.RLMethod.toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"fixIter",prependedString,isMcc);
        addBoolToArgs(args,guiVals.fixIter,prependedString);

        addCharArrayToArgs(args,"errThresh",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.errThresh),prependedString);

        addCharArrayToArgs(args,"debug",prependedString,isMcc);
        addBoolToArgs(args,guiVals.debug,prependedString);

        addCharArrayToArgs(args,"GPUJob",prependedString,isMcc);
        addBoolToArgs(args,guiVals.gpuJob,prependedString);

        addCharArrayToArgs(args,"DeconIter",prependedString,isMcc);
        addScalarToArgs(args,ui->deconIterationsLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"rotatePSF",prependedString,isMcc);
        addBoolToArgs(args,ui->rotatePSFCheckBox->isChecked(),prependedString);

        // Job Settings
        addCharArrayToArgs(args,"parseCluster",prependedString,isMcc);
        addBoolToArgs(args,ui->parseClusterCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"cpusPerTask",prependedString,isMcc);
        addScalarToArgs(args,ui->cpusPerTaskLineEdit->text().toStdString(),prependedString);

        // Advanced Job Settings
        addCharArrayToArgs(args,"largeFile",prependedString,isMcc);
        addBoolToArgs(args,guiVals.largeFile,prependedString);

        addCharArrayToArgs(args,"largeMethod",prependedString,isMcc);
        addCharArrayToArgs(args,guiVals.largeMethod.toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"zarrFile",prependedString,isMcc);
        addBoolToArgs(args,guiVals.zarrFile,prependedString);

        addCharArrayToArgs(args,"saveZarr",prependedString,isMcc);
        addBoolToArgs(args,guiVals.saveZarr,prependedString);

        if(!guiVals.jobLogDir.isEmpty()){
            addCharArrayToArgs(args,"jobLogDir",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.jobLogDir.toStdString(),prependedString,isMcc);
        }

        if(!guiVals.uuid.isEmpty()){
            addCharArrayToArgs(args,"uuid",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.uuid.toStdString(),prependedString,isMcc);
        }

        addCharArrayToArgs(args,"maxTrialNum",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.maxTrialNum),prependedString);

        addCharArrayToArgs(args,"unitWaitTime",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.unitWaitTime),prependedString);

        addCharArrayToArgs(args,"maxWaitLoopNum",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.maxWaitLoopNum),prependedString);

        addCharArrayToArgs(args,"mccMode",prependedString,isMcc);
        addBoolToArgs(args,isMcc,prependedString);

        addCharArrayToArgs(args,"ConfigFile",prependedString,isMcc);
        addCharArrayToArgs(args,cFileVals.configFile.toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"GPUConfigFile",prependedString,isMcc);
        addCharArrayToArgs(args,cFileVals.gpuConfigFile.toStdString(),prependedString,isMcc);

    }
    else{
        // Data Paths
        addDataPathsToArgs(args,firstPrependedString,dPaths,isMcc);

        // Main Settings
        // TODO: Logic (in bool array 4th value is all decon, 5th value is rotate after decon)
        // TODO: FIX LOGIC FOR DECON ONLY
        addCharArrayToArgs(args,"Overwrite",prependedString,isMcc);
        if(ui->deconOnlyCheckBox->isChecked()) addBoolToArgs(args,false,prependedString);
        else if(ui->deskewOverwriteDataCheckBox->isChecked() && ui->rotateOverwriteDataCheckBox->isChecked() && ui->deskewAndRotateOverwriteDataCheckBox->isChecked() && ui->stitchOverwriteDataCheckBox->isChecked()) addBoolToArgs(args,true,prependedString);
        else{
            std::vector<std::string> OverwriteV = {btosM(ui->deskewOverwriteDataCheckBox->isChecked()),btosM(ui->rotateOverwriteDataCheckBox->isChecked()),btosM(ui->stitchOverwriteDataCheckBox->isChecked()),btosM(false),btosM(false)};
            addArrayToArgs(args,OverwriteV,false,prependedString,"[]",isMcc);
        }

        addCharArrayToArgs(args,"Streaming",prependedString,isMcc);
        addBoolToArgs(args,ui->streamingCheckBox->isChecked(),prependedString);

        // Channel Patterns
        addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
        addChannelPatternsToArgs(args,channelWidgets,ui->customPatternsCheckBox->isChecked(),ui->customPatternsLineEdit->text(),prependedString,isMcc);

        // Currently not used
        //data.push_back(factory.createCharArray("Channels"));
        //data.push_back(factory.createArray<uint64_t>({1,3},{488,560,642}));

        addCharArrayToArgs(args,"SkewAngle",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.skewAngle),prependedString);

        addCharArrayToArgs(args,"dz",prependedString,isMcc);
        addScalarToArgs(args,ui->dzLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"dzFromEncoder",prependedString,isMcc);
        addBoolToArgs(args,ui->dzFromEncoderCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"xyPixelSize",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.xyPixelSize),prependedString);

        addCharArrayToArgs(args,"Reverse",prependedString,isMcc);
        addBoolToArgs(args,guiVals.Reverse,prependedString);

        addCharArrayToArgs(args,"ObjectiveScan",prependedString,isMcc);
        addBoolToArgs(args,ui->objectiveScanCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"sCMOSCameraFlip",prependedString,isMcc);
        addBoolToArgs(args,guiVals.sCMOSCameraFlip,prependedString);

        addCharArrayToArgs(args,"resampleType",prependedString,isMcc);
        addCharArrayToArgs(args,guiVals.resampleType.toStdString(),prependedString,isMcc);



        if(guiVals.resampleEnabled){
            addCharArrayToArgs(args,"resample",prependedString,isMcc);
            std::vector<std::string> resampleV = {std::to_string(guiVals.resample[0]),std::to_string(guiVals.resample[1]),std::to_string(guiVals.resample[2])};
            addArrayToArgs(args,resampleV,false,prependedString,"[]",isMcc);
       }

        // This needs to change FIX
        // TODO: FIX LOGIC FOR DECON ONLY
        addCharArrayToArgs(args,"Save16bit",prependedString,isMcc);
        std::vector<std::string> Save16bitV = {btosM(ui->deskewSave16BitCheckBox->isChecked() || ui->rotateSave16BitCheckBox->isChecked() || ui->deskewAndRotateSave16BitCheckBox->isChecked()),btosM(ui->stitchSave16BitCheckBox->isChecked()),btosM(false),btosM(false)};
        addArrayToArgs(args,Save16bitV,false,prependedString,"[]",isMcc);

        // This needs to change FIX
        addCharArrayToArgs(args,"onlyFirstTP",prependedString,isMcc);
        addBoolToArgs(args,ui->deskewOnlyFirstTPCheckBox->isChecked() || ui->rotateOnlyFirstTPCheckBox->isChecked() || ui->deskewAndRotateOnlyFirstTPCheckBox->isChecked() || ui->stitchOnlyFirstTPCheckBox->isChecked(),prependedString);


        addCharArrayToArgs(args,"zarrFile",prependedString,isMcc);
        addBoolToArgs(args,guiVals.zarrFile,prependedString);

        addCharArrayToArgs(args,"saveZarr",prependedString,isMcc);
        addBoolToArgs(args,guiVals.saveZarr,prependedString);

        addCharArrayToArgs(args,"save3DStack",prependedString,isMcc);
        addBoolToArgs(args,guiVals.save3DStack,prependedString);

        // Pipeline Settings
        // TODO: Test this Logic more
        if(!(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked()) && ui->deskewAndRotateCheckBox->isChecked()){
            addCharArrayToArgs(args,"DSRCombined",prependedString,isMcc);
            addBoolToArgs(args,true,prependedString);

            addCharArrayToArgs(args,"Deskew",prependedString,isMcc);
            addBoolToArgs(args,true,prependedString);

            addCharArrayToArgs(args,"Rotate",prependedString,isMcc);
            addBoolToArgs(args,true,prependedString);
        }
        else{
            addCharArrayToArgs(args,"DSRCombined",prependedString,isMcc);
            addBoolToArgs(args,false,prependedString);

            addCharArrayToArgs(args,"Deskew",prependedString,isMcc);
            addBoolToArgs(args,ui->deskewCheckBox->isChecked(),prependedString);

            addCharArrayToArgs(args,"Rotate",prependedString,isMcc);
            addBoolToArgs(args,ui->rotateCheckBox->isChecked(),prependedString);
        }

        addCharArrayToArgs(args,"Stitch",prependedString,isMcc);
        addBoolToArgs(args,ui->stitchCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"Decon",prependedString,isMcc);
        addBoolToArgs(args,ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked(),prependedString);

        // Change later
        //data.push_back(factory.createCharArray("RotateAfterDecon"));
        //data.push_back(factory.createScalar<bool>(ui->rotateAfterDeconCheckBox->isChecked()));

        // DSR Settings
        addCharArrayToArgs(args,"parseSettingFile",prependedString,isMcc);
        addBoolToArgs(args,ui->parseSettingsFileCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"flipZstack",prependedString,isMcc);
        addBoolToArgs(args,ui->flipZStackCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"LLFFCorrection",prependedString,isMcc);
        addBoolToArgs(args,ui->llffCorrectionCheckBox->isChecked(),prependedString);

        if(lsImagePaths.size()){
            addCharArrayToArgs(args,"LSImagePaths",prependedString,isMcc);
            std::vector<std::string> lsImageMPaths;
            for(size_t i = 0; i < lsImagePaths.size(); i++){
                lsImageMPaths.push_back(lsImagePaths[i].toStdString());
            }
            addArrayToArgs(args,lsImageMPaths,true,prependedString,"{}",isMcc);
        }

        if(backgroundPaths.size()){
            addCharArrayToArgs(args,"BackgroundPaths",prependedString,isMcc);
            std::vector<std::string> backgroundMPaths;
            for(size_t i = 0; i < backgroundPaths.size(); i++){
                backgroundMPaths.push_back(backgroundPaths[i].toStdString());
            }
            addArrayToArgs(args,backgroundMPaths,true,prependedString,"{}",isMcc);
        }

        // DSR Advanced Settings
        addCharArrayToArgs(args,"BKRemoval",prependedString,isMcc);
        addBoolToArgs(args,guiVals.BKRemoval,prependedString);

        addCharArrayToArgs(args,"LowerLimit",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.LowerLimit),prependedString);

        // Stitch Settings
        addCharArrayToArgs(args,"stitchPipeline",prependedString,isMcc);
        addCharArrayToArgs(args,ui->stitchPipelineComboBox->currentText().toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"stitchResultDir",prependedString,isMcc);
        addCharArrayToArgs(args,ui->resultsDirLineEdit->text().toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"imageListFullpaths",prependedString,isMcc);
        std::vector<std::string> imageListFullpathsV = {ui->imageListFullPathsLineEdit->text().toStdString()};
        addArrayToArgs(args,imageListFullpathsV,true,prependedString,"{}",isMcc);

        if(!ui->axisOrderLineEdit->text().isEmpty()){
            addCharArrayToArgs(args,"axisOrder",prependedString,isMcc);
            addCharArrayToArgs(args,ui->axisOrderLineEdit->text().toStdString(),prependedString,isMcc);
        }

        addCharArrayToArgs(args,"BlendMethod",prependedString,isMcc);
        addCharArrayToArgs(args,ui->blendMethodComboBox->currentText().toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"xcorrShift",prependedString,isMcc);
        addBoolToArgs(args,ui->xCorrShiftCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"xcorrMode",prependedString,isMcc);
        addCharArrayToArgs(args,ui->xCorrModeComboBox->currentText().toStdString(),prependedString,isMcc);

        if(ui->boundBoxCheckBox->isChecked()){
            addCharArrayToArgs(args,"boundboxCrop",prependedString,isMcc);
            std::vector<std::string> boundboxCropV = {ui->boundBoxYMinSpinBox->text().toStdString(),ui->boundBoxXMinSpinBox->text().toStdString(),ui->boundBoxZMinSpinBox->text().toStdString(),ui->boundBoxYMaxSpinBox->text().toStdString(), ui->boundBoxXMaxSpinBox->text().toStdString(), ui->boundBoxZMaxSpinBox->text().toStdString()};
            addArrayToArgs(args,boundboxCropV,false,prependedString,"[]",isMcc);
        }

        if(!ui->primaryCHLineEdit->text().isEmpty()){
            addCharArrayToArgs(args,"primaryCh",prependedString,isMcc);
            addCharArrayToArgs(args,ui->primaryCHLineEdit->text().toStdString(),prependedString,isMcc);
        }

        addCharArrayToArgs(args,"stitchMIP",prependedString,isMcc);
        std::vector<std::string> stitchMIPV = {btosM(ui->stitchStitchMIPYSpinBox->value()),btosM(ui->stitchStitchMIPXSpinBox->value()),btosM(ui->stitchStitchMIPZSpinBox->value())};
        addArrayToArgs(args,stitchMIPV,false,prependedString,"[]",isMcc);

        addCharArrayToArgs(args,"onlineStitch",prependedString,isMcc);
        addBoolToArgs(args,ui->stitchOnlineStitchCheckBox->isChecked(),prependedString);

        if(ui->stitchGenerateImageListComboBox->currentText().toStdString() != "none"){
            addCharArrayToArgs(args,"generateImageList",prependedString,isMcc);
            addCharArrayToArgs(args,ui->stitchGenerateImageListComboBox->currentText().toStdString(),prependedString,isMcc);
        }

        // Decon Settings
        addCharArrayToArgs(args,"cudaDecon",prependedString,isMcc);
        addBoolToArgs(args,ui->cudaDeconRadioButton->isChecked(),prependedString);

        addCharArrayToArgs(args,"cppDecon",prependedString,isMcc);
        addBoolToArgs(args,ui->cppDeconRadioButton->isChecked(),prependedString);

        addCharArrayToArgs(args,"DS",prependedString,isMcc);
        addBoolToArgs(args,ui->deskewDeconCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"DSR",prependedString,isMcc);
        addBoolToArgs(args,ui->deskewAndRotateDeconCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"Background",prependedString,isMcc);
        addScalarToArgs(args,ui->backgroundIntensityLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"dzPSF",prependedString,isMcc);
        addScalarToArgs(args,ui->dzPSFLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"EdgeErosion",prependedString,isMcc);
        addScalarToArgs(args,ui->edgeErosionLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"ErodeByFTP",prependedString,isMcc);
        addBoolToArgs(args,ui->erodeByFTPCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"deconRotate",prependedString,isMcc);
        addBoolToArgs(args,ui->deconRotateCheckBox->isChecked(),prependedString);

        // Decon Advanced settings
        if(!guiVals.cppDeconPath.isEmpty()){
            addCharArrayToArgs(args,"cppDeconPath",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.cppDeconPath.toStdString(),prependedString,isMcc);
        }
        if(!guiVals.loadModules.isEmpty()){
            addCharArrayToArgs(args,"loadModules",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.loadModules.toStdString(),prependedString,isMcc);
        }
        if(!guiVals.cudaDeconPath.isEmpty()){
            addCharArrayToArgs(args,"cudaDeconPath",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.cudaDeconPath.toStdString(),prependedString,isMcc);
        }
        if(!guiVals.OTFGENPath.isEmpty()){
            addCharArrayToArgs(args,"OTFGENPath",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.OTFGENPath.toStdString(),prependedString,isMcc);
        }

        if(psfFullPaths.size()){
            addCharArrayToArgs(args,"psfFullpaths",prependedString,isMcc);
            std::vector<std::string> psfMPaths;
            for(size_t i = 0; i < psfFullPaths.size(); i++){
                psfMPaths.push_back(psfFullPaths[i].toStdString());
            }
            addArrayToArgs(args,psfMPaths,true,prependedString,"{}",isMcc);
        }

        addCharArrayToArgs(args,"RLMethod",prependedString,isMcc);
        addCharArrayToArgs(args,guiVals.RLMethod.toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"fixIter",prependedString,isMcc);
        addBoolToArgs(args,guiVals.fixIter,prependedString);

        addCharArrayToArgs(args,"errThresh",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.errThresh),prependedString);

        addCharArrayToArgs(args,"debug",prependedString,isMcc);
        addBoolToArgs(args,guiVals.debug,prependedString);

        addCharArrayToArgs(args,"GPUJob",prependedString,isMcc);
        addBoolToArgs(args,guiVals.gpuJob,prependedString);

        addCharArrayToArgs(args,"DeconIter",prependedString,isMcc);
        addScalarToArgs(args,ui->deconIterationsLineEdit->text().toStdString(),prependedString);

        addCharArrayToArgs(args,"rotatedPSF",prependedString,isMcc);
        addBoolToArgs(args,ui->rotatePSFCheckBox->isChecked(),prependedString);



        // Job Settings
        addCharArrayToArgs(args,"parseCluster",prependedString,isMcc);
        addBoolToArgs(args,ui->parseClusterCheckBox->isChecked(),prependedString);

        addCharArrayToArgs(args,"cpusPerTask",prependedString,isMcc);
        addScalarToArgs(args,ui->cpusPerTaskLineEdit->text().toStdString(),prependedString);

        // Advanced Job Settings
        addCharArrayToArgs(args,"largeFile",prependedString,isMcc);
        addBoolToArgs(args,guiVals.largeFile,prependedString);

        if(!guiVals.jobLogDir.isEmpty()){
            addCharArrayToArgs(args,"jobLogDir",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.jobLogDir.toStdString(),prependedString,isMcc);
        }

        if(!guiVals.uuid.isEmpty()){
            addCharArrayToArgs(args,"uuid",prependedString,isMcc);
            addCharArrayToArgs(args,guiVals.uuid.toStdString(),prependedString,isMcc);
        }

        addCharArrayToArgs(args,"maxTrialNum",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.maxTrialNum),prependedString);

        addCharArrayToArgs(args,"unitWaitTime",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.unitWaitTime),prependedString);

        addCharArrayToArgs(args,"minModifyTime",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.minModifyTime),prependedString);

        addCharArrayToArgs(args,"maxModifyTime",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.maxModifyTime),prependedString);

        addCharArrayToArgs(args,"maxWaitLoopNum",prependedString,isMcc);
        addScalarToArgs(args,std::to_string(guiVals.maxWaitLoopNum),prependedString);

        addCharArrayToArgs(args,"mccMode",prependedString,isMcc);
        addBoolToArgs(args,isMcc,prependedString);

        addCharArrayToArgs(args,"ConfigFile",prependedString,isMcc);
        addCharArrayToArgs(args,cFileVals.configFile.toStdString(),prependedString,isMcc);

        addCharArrayToArgs(args,"GPUConfigFile",prependedString,isMcc);
        addCharArrayToArgs(args,cFileVals.gpuConfigFile.toStdString(),prependedString,isMcc);

    }
    QString funcType;

    if(ui->deconOnlyCheckBox->isChecked()){
        funcType="DeconOnly";
    }

    // Send data to the MATLAB thread
    auto mPJNPC = std::make_tuple(mainPath, timeJobName,ui->parseClusterCheckBox->isChecked());
    emit jobStart(args, funcType, mPJNPC, jobLogPaths, isMcc, pathToMatlab);

    // Still deciding which name I want to show to the user
    size_t currJob = jobNames.size()+1;
    jobNames.emplace(currJob,timeJobName);

    QString currJobText = ui->jobNameLineEdit->text();
    if(currJobText.contains("Job ") && currJobText.back().isDigit()){
        for(int i = currJobText.size()-1; i >= 0; i--){
            if(currJobText.back().isDigit()){
                currJobText.chop(1);
            }
            else{
                currJobText.append(QString::number(currJob+1));
                ui->jobNameLineEdit->setText(currJobText);
                break;
            }
        }
    }

    // Reset jobLogDir
    guiVals.jobLogDir = jobLogCopy;
}

// Browse for Result Dir Folder
void MainWindow::on_resultsDirBrowseButton_clicked()
{
    QFileInfo folder_path(QFileDialog::getExistingDirectory(this,"Select or Create and Select the Results Folder",mostRecentDir));
    if(!folder_path.baseName().isEmpty()){
        ui->resultsDirLineEdit->setText(folder_path.baseName());
        mostRecentDir = folder_path.absoluteFilePath();
    }
}

// Set tool tip for Stitch Result Dir line
void MainWindow::on_resultsDirLineEdit_textChanged(const QString &arg1)
{
    ui->resultsDirLineEdit->setToolTip(arg1);
}

// Open Main Window Advanced Settings
void MainWindow::on_mainAdvancedSettingsButton_clicked()
{
    mainAdvanced mAdvanced(guiVals, cFileVals);
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
        if(!(ui->stitchCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked())){
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
        if(!(ui->stitchCheckBox->isChecked() || ui->deskewCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked())){
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
        if(!(ui->stitchCheckBox->isChecked() || ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked())){
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
        if(!(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked())){
            ui->mainNextButton->setEnabled(false);
        }
    }
}

// Functionality for the Next button on the main page
void MainWindow::on_mainNextButton_clicked()
{
    // Error if no data paths set
    if(!dPaths.size()){
        messageBoxError("No data paths are set. Please set at least one data path before continuing.");
        return;
    }

    // Error if no channel patterns set
    if(!channelWidgets.size() && (!ui->customPatternsCheckBox->isChecked() || ui->customPatternsLineEdit->text().isEmpty())){
        messageBoxError("No channel patterns set. Please set at least one pattern before continuing.");
        return;
    }
    for(size_t i = 0; i < channelWidgets.size(); i++){
        if(channelWidgets[i].second->isChecked()) break;
        if(i == channelWidgets.size()-1 && (!ui->customPatternsCheckBox->isChecked() || ui->customPatternsLineEdit->text().isEmpty())){
            messageBoxError("No channel patterns set. Please set at least one pattern before continuing.");
            return;
        }
    }

    // Set the checkmark and disable the tab
    ui->tabWidget->setTabText(ui->tabWidget->indexOf(ui->Main),QString::fromStdString("Main ✔"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->Main),false);

    // Logic of which tab is next
    if(ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->DSR);
    }
    else if (ui->deconOnlyCheckBox->isChecked()){
        ui->tabWidget->setCurrentWidget(ui->Decon);
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
    else if(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked()){
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
    if(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked()){
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
    else if((ui->deskewCheckBox->isChecked() || ui->rotateCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked())){
        ui->tabWidget->setCurrentWidget(ui->DSR);
    }
    else{
        ui->tabWidget->setCurrentWidget(ui->Main);
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
    if(ui->deskewDeconCheckBox->isChecked() || ui->rotateDeconCheckBox->isChecked() || ui->deskewAndRotateDeconCheckBox->isChecked() || ui->stitchDeconCheckBox->isChecked() || ui->deconOnlyCheckBox->isChecked()){
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

// Opens a seperate window to add the data paths for the job
void MainWindow::on_addPathsButton_clicked()
{
    // Default behavior is for the main Data Paths
    std::vector<dataPath>* addPathsDataPaths = &dPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>>* addPathsChannelWidgets = &channelWidgets;
    QWidget* addPathsCurrWidget = ui->Main;
    QHBoxLayout* addPathsCurrLayout = ui->horizontalLayout_4;

    // Data Paths for other modules
    if(((QPushButton *)sender())->objectName().contains("simRecon")){
        addPathsDataPaths = &simReconDPaths;
        addPathsChannelWidgets = &simReconChannelWidgets;
        addPathsCurrWidget = ui->simRecon;
        addPathsCurrLayout = ui->simReconChannelPatternsHorizontalLayout;
    }
    else if(((QPushButton *)sender())->objectName().contains("crop")){
        addPathsDataPaths = &cropDPaths;
        addPathsChannelWidgets = &cropChannelWidgets;
        addPathsCurrWidget = ui->Crop;
        addPathsCurrLayout = ui->cropChannelPatternsHorizontalLayout;
    }
    else if(((QPushButton *)sender())->objectName().contains("fscAnalysis")){
        addPathsDataPaths = &fscAnalysisDPaths;
        addPathsChannelWidgets = &fscAnalysisChannelWidgets;
        addPathsCurrWidget = ui->fscAnalysis;
        addPathsCurrLayout = ui->fscAnalysisChannelPatternsHorizontalLayout;
    }
    else if(((QPushButton *)sender())->objectName().contains("mipGenerator")){
        addPathsDataPaths = &mipGeneratorDPaths;
        addPathsChannelWidgets = &mipGeneratorChannelWidgets;
        addPathsCurrWidget = ui->mipGenerator;
        addPathsCurrLayout = ui->mipGeneratorChannelPatternsHorizontalLayout;
    }
    else if(((QPushButton *)sender())->objectName().contains("psfDetectionAnalysis")){
        addPathsDataPaths = &psfDetectionAnalysisDPaths;
        addPathsChannelWidgets = &psfDetectionAnalysisChannelWidgets;
        addPathsCurrWidget = ui->psfDetectionAnalysis;
        addPathsCurrLayout = ui->psfDetectionAnalysisChannelPatternsHorizontalLayout;
    }
    else if(((QPushButton *)sender())->objectName().contains("tiffZarrConverter")){
        addPathsDataPaths = &tiffZarrConverterDPaths;
        addPathsChannelWidgets = &tiffZarrConverterChannelWidgets;
        addPathsCurrWidget = ui->tiffZarrConverter;
        addPathsCurrLayout = ui->tiffZarrConverterChannelPatternsHorizontalLayout;
    }


    dataPaths daPaths(*addPathsDataPaths, true, mostRecentDir);
    daPaths.setModal(true);
    daPaths.exec();

    // Find all possible channels
    if(addPathsChannelWidgets->size()){
        for(auto &i : *addPathsChannelWidgets){
            if(i.first) delete i.first;
            if(i.second) delete i.second;
        }
    }
    addPathsChannelWidgets->clear();
    if(!addPathsDataPaths->size()) return;
    std::vector<QString> channels;
    for(const auto &path : *addPathsDataPaths){
        if(path.includeMaster){
            // Looking for channel patterns in the given directory
            QDirIterator cPath(path.masterPath);
            QString c;
            QRegularExpression re("Cam\\w_ch\\d");
            QRegularExpressionMatch rmatch;
            while(cPath.hasNext()){
                c = cPath.next();
                rmatch = re.match(c);
                // Check if there is a match and that it is not already in the vector
                if (!rmatch.captured(0).isEmpty() && !(std::count(channels.begin(),channels.end(),rmatch.captured(0)))) channels.push_back(rmatch.captured(0));
            }
        }
        for(const auto &subPath : path.subPaths){
            if(subPath.second.first){
                // Looking for channel patterns in the given directory
                QDirIterator cPath(subPath.second.second);
                QString c;
                QRegularExpression re("Cam\\w_ch\\d");
                QRegularExpressionMatch rmatch;
                while(cPath.hasNext()){
                    c = cPath.next();
                    rmatch = re.match(c);
                    // Check if there is a match and that it is not already in the vector
                    if (!rmatch.captured(0).isEmpty() && !(std::count(channels.begin(),channels.end(),rmatch.captured(0)))) channels.push_back(rmatch.captured(0));
                }
            }
        }
    }
    for(const QString &ch : channels){
        QLabel* label = new QLabel(addPathsCurrWidget);
        label->setTextFormat(Qt::RichText);
        label->setText("<b>"+ch+"<\b>");
        addPathsCurrLayout->addWidget(label);

        QCheckBox* checkBox = new QCheckBox(addPathsCurrWidget);
        addPathsCurrLayout->addWidget(checkBox);
        addPathsChannelWidgets->push_back(std::make_pair(label,checkBox));
    }
}

void MainWindow::on_imageListFullPathsBrowseButton_clicked()
{
    QFileInfo file_path(QFileDialog::getOpenFileName(this,"Select the Image List Full Paths File",mostRecentDir));
    if(!file_path.absoluteFilePath().isEmpty()){
        ui->imageListFullPathsLineEdit->setText(file_path.absoluteFilePath());
        mostRecentDir = file_path.absolutePath();
    }
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
    dataPaths daPaths(lsImagePaths, false, mostRecentDir);
    daPaths.setModal(true);
    daPaths.exec();
}

// Open window for adding background Paths
void MainWindow::on_backgroundAddPathsButton_clicked()
{
    dataPaths daPaths(backgroundPaths, false, mostRecentDir);
    daPaths.setModal(true);
    daPaths.exec();
}

// Open window for adding PSF Paths
void MainWindow::on_psfFullAddPathsButton_2_clicked()
{
    std::vector<QString> channelNames;
    if(!ui->customPatternsCheckBox->isChecked()){
        for(auto i : channelWidgets){
            if(i.second->isChecked()){
                channelNames.push_back(i.first->text());
            }
        }
    }
    else{
        QString patternLine = ui->customPatternsLineEdit->text();
        QString pattern;
        for(int i = 0; i < patternLine.size(); i++){
            if(patternLine[i] == ','){
                channelNames.push_back(pattern);
                pattern.clear();
            }
            else{
                pattern.push_back(patternLine[i]);
            }
        }
        if(pattern.size()){
            channelNames.push_back(pattern);
        }
    }
    dataPaths daPaths(psfFullPaths, false, mostRecentDir, channelNames);
    daPaths.setModal(true);
    daPaths.exec();
}

// Check if the user wants to load previous settings
void MainWindow::checkLoadPrevSettings()
{
    loadSettings = false;

    loadPreviousSettings lPSettings(loadSettings,isMcc,pathToMatlab);
    lPSettings.setModal(true);
    lPSettings.exec();
}

// Enable next button if deconOnly is checked
void MainWindow::on_deconOnlyCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->mainNextButton->setEnabled(true);
    }
    else{
        if(!(ui->stitchCheckBox->isChecked() || ui->deskewCheckBox->isChecked() || ui->deskewAndRotateCheckBox->isChecked() || ui->rotateCheckBox->isChecked())){
            ui->mainNextButton->setEnabled(false);
        }
    }
}

// Enable or Disable custom pattern writing
void MainWindow::on_customPatternsCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->customPatternsLineEdit->setEnabled(true);
    }
    else{
        ui->customPatternsLineEdit->setEnabled(false);
    }
}

void MainWindow::on_simReconSubmitButton_clicked()
{
    writeSettings();

    // TODO: Seperate functions for error checking

    // Error if no data paths are set
    if(!simReconDPaths.size()){
        messageBoxError("There are no data paths set.");
        return;
    }

    // Error if data path does not exist when submit is pressed
    for(size_t i = 0; i < simReconDPaths.size(); i++){
        if(simReconDPaths[i].includeMaster){
            if(!QFileInfo::exists(simReconDPaths[i].masterPath)){
                messageBoxError("Data path \"" + simReconDPaths[i].masterPath + "\" does not exist!");
                return;
            }
        }
        for (const auto &subPath : simReconDPaths[i].subPaths){
            if(subPath.second.first){
                if(!QFileInfo::exists(subPath.second.second)){
                    messageBoxError("Data path \"" + subPath.second.second + "\" does not exist!");
                    return;
                }
            }
        }
    }

    // Error if decon is set but no psf paths are set
    if((ui->simReconReconOnlyCheckBox->isChecked() || ui->simReconDeskewReconCheckBox->isChecked()) && !simReconPsfFullPaths.size()){
        messageBoxError("Recon is set but there are no psf paths set");
        return;
    }
    else if((ui->simReconReconOnlyCheckBox->isChecked() || ui->simReconDeskewReconCheckBox->isChecked())){
        for(const QString &path : simReconPsfFullPaths){
            if(path.isEmpty()){
                messageBoxError("One of the PSF paths is empty!");
                return;
            }
            else if(!QFileInfo::exists(path)){
                messageBoxError("Psf path \"" + path + "\" does not exist!");
                return;
            }
        }
    }

    // Make it so the user can't submit another job while we are submitting this one
    ui->submitButton->setEnabled(false);

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    //
    // TODO: GOING TO REDO THIS PORTION AND MAKE A FUNCTION SO I CAN SUPPORT MULTIPLE SCRIPTS EASIER
    //

    // Set main path. This is where all the output files made by the GUI will be stored if a job log dir does not exist.
    //QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_");
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd_HHmm_");
    QString timeJobName = dateTime+QString(ui->simReconJobNameLineEdit->text()).replace(" ","_");
    QString mainPath = simReconDPaths[0].masterPath+"/job_logs/"+timeJobName;

    // Check for job log directory for main job
    QString jobLogCopy = simreconVals.jobLogDir;
    QDir dir(simreconVals.jobLogDir);
    if (!dir.exists()){
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
        simreconVals.jobLogDir = mainPath;
        std::cout << "Chosen job log directory does not exist! Using " << simreconVals.jobLogDir.toStdString()<< " as the job log directory instead." << std::endl;
    }
    else{
        mainPath = simreconVals.jobLogDir+"/"+timeJobName;
        QDir mDir(mainPath);
        if(!mDir.exists()){
            mDir.mkpath(".");
        }
    }

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }

    addDataPathsToArgs(args,firstPrependedString,simReconDPaths,isMcc);

    // Main Settings
    // TODO: Logic (in bool array 4th value is all decon, 5th value is rotate after decon)
    // TODO: FIX LOGIC FOR DECON ONLY

    addCharArrayToArgs(args,"Overwrite",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconDeskewOverwriteDataCheckBox->isChecked() || ui->simReconReconOnlyOverwriteDataCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
    addChannelPatternsToArgs(args,simReconChannelWidgets,ui->simReconCustomPatternsCheckBox->isChecked(),ui->simReconCustomPatternsLineEdit->text(),prependedString,isMcc);

    addCharArrayToArgs(args,"Streaming",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconStreamingCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"dz",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconDZLineEdit->text().toStdString(),prependedString);

    // This needs to change FIX
    addCharArrayToArgs(args,"Save16bit",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconDeskewSave16BitCheckBox->isChecked() || ui->simReconReconOnlySave16BitCheckBox->isChecked(),prependedString);

    // This needs to change FIX
    //data.push_back(factory.createCharArray("onlyFirstTP"));
    //data.push_back(factory.createScalar<bool>(ui->deskewOnlyFirstTPCheckBox->isChecked() || ui->rotateOnlyFirstTPCheckBox->isChecked() || ui->deskewAndRotateOnlyFirstTPCheckBox->isChecked() || ui->stitchOnlyFirstTPCheckBox->isChecked()));

    // Main Advanced Settings

    addCharArrayToArgs(args,"SkewAngle",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.skewAngle),prependedString);

    addCharArrayToArgs(args,"xyPixelSize",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.xyPixelSize),prependedString);

    addCharArrayToArgs(args,"Reverse",prependedString,isMcc);
    addBoolToArgs(args,simreconVals.Reverse,prependedString);

    // Pipeline Setting
    addCharArrayToArgs(args,"Deskew",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconDeskewCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"Recon",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconReconOnlyCheckBox->isChecked() || ui->simReconDeskewReconCheckBox->isChecked(),prependedString);

    // Deskew Settings
    // None for now

    // Recon Settings

    addCharArrayToArgs(args,"Background",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconBackgroundIntensityLineEdit->text().toStdString(),prependedString);

    //data.push_back(factory.createCharArray("dzPSF"));
    //data.push_back(factory.createScalar<double>(ui->simReconDZPSFLineEdit->text().toDouble()));

    if(simReconPsfFullPaths.size()){
        addCharArrayToArgs(args,"PSFs",prependedString,isMcc);
        std::vector<std::string> psfMPaths;
        for(size_t i = 0; i < simReconPsfFullPaths.size(); i++){
            psfMPaths.push_back(simReconPsfFullPaths[i].toStdString());
        }
        addArrayToArgs(args,psfMPaths,true,prependedString,"{}",isMcc);
    }

    // calculate pxl dim data/psf
    addCharArrayToArgs(args,"pxl_dim_data",prependedString,isMcc);
    std::vector<std::string> pxl_dim_dataV = {std::to_string(simreconVals.xyPixelSize),std::to_string(simreconVals.xyPixelSize),std::to_string((ui->simReconDZLineEdit->text().toDouble())*qSin(qDegreesToRadians(simreconVals.skewAngle)))};
    addArrayToArgs(args,pxl_dim_dataV,false,prependedString,"[]",isMcc);

    addCharArrayToArgs(args,"pxl_dim_PSF",prependedString,isMcc);
    std::vector<std::string> pxl_dim_PSFV = {std::to_string(simreconVals.xyPixelSize),std::to_string(simreconVals.xyPixelSize),std::to_string((ui->simReconDZPSFLineEdit->text().toDouble())*qSin(qDegreesToRadians(simreconVals.skewAngle)))};
    addArrayToArgs(args,pxl_dim_PSFV,false,prependedString,"[]",isMcc);

    addCharArrayToArgs(args,"nphases",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconNPhasesLineEdit->text().toStdString(),prependedString);

    // Number of orders matches number of phases for now
    addCharArrayToArgs(args,"norders",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconNPhasesLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"norientations",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconNOrientationsLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"lattice_period",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconLatticePeriodLineEdit->text().toStdString(),prependedString);

    // calculate phase step
    addCharArrayToArgs(args,"phase_step",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(ui->simReconLatticePeriodLineEdit->text().toDouble()/ui->simReconNPhasesLineEdit->text().toDouble()),prependedString);

    addCharArrayToArgs(args,"EdgeErosion",prependedString,isMcc);
    addScalarToArgs(args,ui->edgeErosionLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"ErodeBefore",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconErodeBeforeCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"ErodeAfter",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconErodeAfterCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"apodize",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconApodizeCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"DS",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconDeskewedCheckBox->isChecked(),prependedString);

    // Recon Advanced settings
    addCharArrayToArgs(args,"islattice",prependedString,isMcc);
    addBoolToArgs(args,simreconVals.islattice,prependedString);

    addCharArrayToArgs(args,"NA_det",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.NA_det),prependedString);

    addCharArrayToArgs(args,"NA_ext",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.NA_ext),prependedString);

    addCharArrayToArgs(args,"nimm",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.nimm),prependedString);

    addCharArrayToArgs(args,"wvl_em",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.wvl_em),prependedString);

    addCharArrayToArgs(args,"wvl_ext",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.wvl_ext),prependedString);

    addCharArrayToArgs(args,"w",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.w),prependedString);

    addCharArrayToArgs(args,"normalize_orientations",prependedString,isMcc);
    addBoolToArgs(args,simreconVals.normalize_orientations,prependedString);

    addCharArrayToArgs(args,"resultsDirName",prependedString,isMcc);
    addCharArrayToArgs(args,simreconVals.resultsDirName.toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"perdecomp",prependedString,isMcc);
    addBoolToArgs(args,simreconVals.perdecomp,prependedString);

    addCharArrayToArgs(args,"edgeTaper",prependedString,isMcc);
    addBoolToArgs(args,simreconVals.edgeTaper,prependedString);

    addCharArrayToArgs(args,"edgeTaperVal",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.edgeTaperVal),prependedString);

    addCharArrayToArgs(args,"intThresh",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.intThresh),prependedString);

    addCharArrayToArgs(args,"occThresh",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.occThresh),prependedString);

    addCharArrayToArgs(args,"useGPU",prependedString,isMcc);
    addBoolToArgs(args,simreconVals.useGPU,prependedString);

    addCharArrayToArgs(args,"gpuPrecision",prependedString,isMcc);
    addCharArrayToArgs(args,simreconVals.gpuPrecision.toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"Overlap",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.Overlap),prependedString);

    addCharArrayToArgs(args,"ChunkSize",prependedString,isMcc);
    std::vector<std::string> ChunkSizeV = {std::to_string(simreconVals.ChunkSize[0]),std::to_string(simreconVals.ChunkSize[1]),std::to_string(simreconVals.ChunkSize[2])};
    addArrayToArgs(args,ChunkSizeV,false,prependedString,"[]",isMcc);

    addCharArrayToArgs(args,"reconBatchNum",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.reconBatchNum),prependedString);

    // Job Settings
    addCharArrayToArgs(args,"parseCluster",prependedString,isMcc);
    addBoolToArgs(args,ui->simReconParseClusterCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"cpusPerTask",prependedString,isMcc);
    addScalarToArgs(args,ui->simReconCpusPerTaskLineEdit->text().toStdString(),prependedString);

    // Advanced Job Settings
    if(!simreconVals.jobLogDir.isEmpty()){
        addCharArrayToArgs(args,"jobLogDir",prependedString,isMcc);
        addCharArrayToArgs(args,simreconVals.jobLogDir.toStdString(),prependedString,isMcc);
    }

    if(!simreconVals.uuid.isEmpty()){
        addCharArrayToArgs(args,"uuid",prependedString,isMcc);
        addCharArrayToArgs(args,simreconVals.uuid.toStdString(),prependedString,isMcc);
    }

    addCharArrayToArgs(args,"maxTrialNum",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.maxTrialNum),prependedString);

    addCharArrayToArgs(args,"unitWaitTime",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.unitWaitTime),prependedString);

    addCharArrayToArgs(args,"parPoolSize",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.parPoolSize),prependedString);

    addCharArrayToArgs(args,"maxModifyTime",prependedString,isMcc);
    addScalarToArgs(args,std::to_string(simreconVals.maxModifyTime),prependedString);

    QString funcType = "simRecon";
    // Send data to the MATLAB thread
    auto mPJNPC = std::make_tuple(mainPath, timeJobName,ui->simReconParseClusterCheckBox->isChecked());
    emit jobStart(args, funcType, mPJNPC, jobLogPaths, isMcc, pathToMatlab);

    // Still deciding which name I want to show to the user
    size_t currJob = jobNames.size()+1;
    jobNames.emplace(currJob,timeJobName);

    QString currJobText = ui->simReconJobNameLineEdit->text();
    if(currJobText.contains("Job ") && currJobText.back().isDigit()){
        for(int i = currJobText.size()-1; i >= 0; i--){
            if(currJobText.back().isDigit()){
                currJobText.chop(1);
            }
            else{
                currJobText.append(QString::number(currJob+1));
                ui->simReconJobNameLineEdit->setText(currJobText);
                break;
            }
        }
    }

    // Reset jobLogDir
    simreconVals.jobLogDir = jobLogCopy;
}

void MainWindow::on_cropSubmitButton_clicked()
{
    // Write settings in case of crash
    writeSettings();

    if(ui->cropResultPathLineEdit->text().toStdString().empty()){
        messageBoxError("Cropping requires a result path!");
    }

    // Disable submit button
    ui->cropSubmitButton->setEnabled(false);

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = cropDPaths[0].masterPath;

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }

    // Data Path
    std::vector<std::string> datapathV = {mainPath.toStdString()};
    addArrayToArgs(args,datapathV,true,firstPrependedString,"{}",isMcc);

    // Result Path
    std::vector<std::string> resultpathV = {ui->cropResultPathLineEdit->text().toStdString()};
    addArrayToArgs(args,resultpathV,true,prependedString,"{}",isMcc);

    // bbox
    std::vector<std::string> bboxV = {ui->cropBoundBoxYMinSpinBox->text().toStdString(),ui->cropBoundBoxXMinSpinBox->text().toStdString(),ui->cropBoundBoxZMinSpinBox->text().toStdString(),ui->cropBoundBoxYMaxSpinBox->text().toStdString(),ui->cropBoundBoxXMaxSpinBox->text().toStdString(),ui->cropBoundBoxZMaxSpinBox->text().toStdString()};
    addArrayToArgs(args,bboxV,false,prependedString,"[]",isMcc);

    addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
    addChannelPatternsToArgs(args,cropChannelWidgets,ui->cropCustomPatternsCheckBox->isChecked(),ui->cropCustomPatternsLineEdit->text(),prependedString,isMcc);

    addCharArrayToArgs(args,"Save16bit",prependedString,isMcc);
    addBoolToArgs(args,ui->cropSave16BitCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"pad",prependedString,isMcc);
    addBoolToArgs(args,ui->cropPadCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"cropType",prependedString,isMcc);
    addCharArrayToArgs(args,ui->cropCropTypeComboBox->currentText().toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"lastStart",prependedString,isMcc);
    std::vector<std::string> laststartV = {ui->cropLastStartYSpinBox->text().toStdString(),ui->cropLastStartXSpinBox->text().toStdString(),ui->cropLastStartZSpinBox->text().toStdString()};
    addArrayToArgs(args,laststartV,false,prependedString,"[]",isMcc);

    // Job Settings
    addCharArrayToArgs(args,"parseCluster",prependedString,isMcc);
    addBoolToArgs(args,ui->cropParseClusterCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"masterCompute",prependedString,isMcc);
    addBoolToArgs(args,ui->cropMasterComputeCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"cpusPerTask",prependedString,isMcc);
    addScalarToArgs(args,ui->cropCpusPerTaskLineEdit->text().toStdString(),prependedString);

    // Advanced Job Settings
    if(!ui->cropJobLogDirLineEdit->text().isEmpty()){
        addCharArrayToArgs(args,"jobLogDir",prependedString,isMcc);
        addCharArrayToArgs(args,ui->cropJobLogDirLineEdit->text().toStdString(),prependedString,isMcc);
    }

    if(!ui->cropUuidLineEdit->text().isEmpty()){
        addCharArrayToArgs(args,"uuid",prependedString,isMcc);
        addCharArrayToArgs(args,ui->cropUuidLineEdit->text().toStdString(),prependedString,isMcc);
    }

    addCharArrayToArgs(args,"mccMode",prependedString,isMcc);
    addBoolToArgs(args,isMcc,prependedString);

    // Config File Settings
    addCharArrayToArgs(args,"ConfigFile",prependedString,isMcc);
    addCharArrayToArgs(args,cFileVals.configFile.toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"GPUConfigFile",prependedString,isMcc);
    addCharArrayToArgs(args,cFileVals.gpuConfigFile.toStdString(),prependedString,isMcc);

    QString funcType = "crop";

    // Send data to the MATLAB thread
    auto cMPJNPC = std::make_tuple(mainPath, QString("Crop Job"),ui->cropParseClusterCheckBox->isChecked());
    emit jobStart(args, funcType, cMPJNPC, jobLogPaths, isMcc, pathToMatlab);
}

void MainWindow::selectFolderPath(){
    QLineEdit* result = nullptr;

    if(((QPushButton *)sender())->objectName().contains("cropResult")){
        result = ui->cropResultPathLineEdit;
    }
    else{
        result = ui->cropJobLogDirLineEdit;
    }

    QFileInfo folder_path(QFileDialog::getExistingDirectory(this,"Select or Create and Select the Folder",mostRecentDir));
    if(!folder_path.absoluteFilePath().isEmpty()){
        result->setText(folder_path.absoluteFilePath());
        mostRecentDir = folder_path.absoluteFilePath();
    }
}

void MainWindow::on_simReconPsfFullAddPathsButton_clicked()
{
    std::vector<QString> channelNames;
    if(!ui->simReconCustomPatternsCheckBox->isChecked()){
        for(auto i : simReconChannelWidgets){
            if(i.second->isChecked()){
                channelNames.push_back(i.first->text());
            }
        }
    }
    else{
        QString patternLine = ui->simReconCustomPatternsLineEdit->text();
        QString pattern;
        for(int i = 0; i < patternLine.size(); i++){
            if(patternLine[i] == ','){
                channelNames.push_back(pattern);
                pattern.clear();
            }
            else{
                pattern.push_back(patternLine[i]);
            }
        }
        if(pattern.size()){
            channelNames.push_back(pattern);
        }
    }
    dataPaths daPaths(simReconPsfFullPaths, false, mostRecentDir, channelNames);
    daPaths.setModal(true);
    daPaths.exec();
}


void MainWindow::on_simReconCustomPatternsCheckBox_stateChanged(int arg1)
{
    ui->simReconCustomPatternsLineEdit->setEnabled(arg1);
}

void MainWindow::on_simReconMainAdvancedSettingsButton_clicked()
{
    simReconMainAdvanced srmAdvanced(simreconVals);
    srmAdvanced.setModal(true);
    srmAdvanced.exec();
}

void MainWindow::on_simReconReconAdvancedSettingsButton_clicked()
{
    simReconReconAdvanced srrAdvanced(simreconVals);
    srrAdvanced.setModal(true);
    srrAdvanced.exec();
}

void MainWindow::on_simReconJobAdvancedSettingsButton_clicked()
{
    simReconJobAdvanced srjAdvanced(simreconVals);
    srjAdvanced.setModal(true);
    srjAdvanced.exec();
}

void MainWindow::on_simReconMainNextButton_clicked()
{
    ui->simReconTab->setCurrentWidget(ui->simReconRecon);
}

void MainWindow::on_simReconReconPreviousButton_clicked()
{
    ui->simReconTab->setCurrentWidget(ui->simReconMain);
}

void MainWindow::on_simReconReconNextButton_clicked()
{
    ui->simReconTab->setCurrentWidget(ui->simReconJob);
}

void MainWindow::on_simReconJobPreviousButton_clicked()
{
    ui->simReconTab->setCurrentWidget(ui->simReconRecon);
}

void MainWindow::on_parallelRsyncSubmitButton_clicked()
{
    // Write settings in case of crash
    writeSettings();

    // Disable submit button
    ui->parallelRsyncSubmitButton->setEnabled(false);

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = ui->parallelRsyncSourceLineEdit->text();

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }
    // Source
    addCharArrayToArgs(args,ui->parallelRsyncSourceLineEdit->text().toStdString(), firstPrependedString, isMcc);

    // Destination
    addCharArrayToArgs(args,ui->parallelRsyncDestLineEdit->text().toStdString(), prependedString, isMcc);

    addCharArrayToArgs(args,"cpusPerTask", prependedString, isMcc);
    addScalarToArgs(args,ui->parallelRsyncCpusPerTaskLineEdit->text().toStdString(), prependedString);

    addCharArrayToArgs(args,"numStream", prependedString, isMcc);
    addScalarToArgs(args,ui->parallelRsyncNumStreamLineEdit->text().toStdString(), prependedString);

    QString funcType = "parallelRsync";
    // Send data to the MATLAB thread
    auto cMPJNPC = std::make_tuple(mainPath, QString("Parallel Rsync"),true);
    emit jobStart(args, funcType, cMPJNPC, jobLogPaths, isMcc, pathToMatlab);
}


void MainWindow::on_parallelRsyncSourceBrowseButton_clicked()
{
    QFileInfo folder_path(QFileDialog::getExistingDirectory(this,"Select the Source Folder",mostRecentDir));
    if(!folder_path.absoluteFilePath().isEmpty()){
        ui->parallelRsyncSourceLineEdit->setText(folder_path.absoluteFilePath());
        mostRecentDir = folder_path.absoluteFilePath();
    }
}


void MainWindow::on_parallelRsyncDestBrowseButton_clicked()
{
    QFileInfo folder_path(QFileDialog::getExistingDirectory(this,"Select the Destination Folder",mostRecentDir));
    if(!folder_path.absoluteFilePath().isEmpty()){
        ui->parallelRsyncDestLineEdit->setText(folder_path.absoluteFilePath());
        mostRecentDir = folder_path.absoluteFilePath();
    }
}


void MainWindow::on_fftAnalysisSubmitButton_clicked()
{
    // Write settings in case of crash
    writeSettings();

    // Disable submit button
    ui->fftAnalysisSubmitButton->setEnabled(false);

    if(!fftAnalysisDPaths.size()) return;

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = fftAnalysisDPaths[0].masterPath;

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }

    addDataPathsToArgs(args,firstPrependedString,fftAnalysisDPaths,isMcc);

    // TODO: ADD SUPPORT FOR CUSTOM CHANNEL PATTERNS

    addCharArrayToArgs(args,"Overwrite",prependedString,isMcc);
    addBoolToArgs(args,ui->fftAnalysisOverwriteCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"xyPixelSize",prependedString,isMcc);
    addScalarToArgs(args,ui->fftAnalysisXyPixelSizeSpinBox->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"dz",prependedString,isMcc);
    addScalarToArgs(args,ui->fftAnalysisDzLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"N",prependedString,isMcc);
    std::vector<std::string> nV = {ui->fftAnalysisNYSpinBox->text().toStdString(),ui->fftAnalysisNXSpinBox->text().toStdString(),ui->fftAnalysisNZSpinBox->text().toStdString()};
    addArrayToArgs(args,nV,false,prependedString,"[]",isMcc);

    addCharArrayToArgs(args,"save3DStack",prependedString,isMcc);
    addBoolToArgs(args,ui->fftAnalysisSave3DStackCheckBox->isChecked(),prependedString);

    QString funcType = "fftAnalysis";

    // Send data to the MATLAB thread
    auto cMPJNPC = std::make_tuple(mainPath, QString("FFT Analysis"),true);
    emit jobStart(args, funcType, cMPJNPC, jobLogPaths, isMcc, pathToMatlab);
}


void MainWindow::on_fftAnalysisAddPathsButton_clicked()
{
    dataPaths daPaths(fftAnalysisDPaths, true, mostRecentDir);
    daPaths.setModal(true);
    daPaths.exec();
}

void MainWindow::on_fscAnalysisSubmitButton_clicked()
{
    // TODO: Write a function for this stuff

    // Write settings in case of crash
    writeSettings();

    // Disable submit button
    ui->fscAnalysisSubmitButton->setEnabled(false);

    if(!fscAnalysisDPaths.size()) return;

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = fscAnalysisDPaths[0].masterPath;

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }

    addDataPathsToArgs(args,firstPrependedString,fscAnalysisDPaths,isMcc);

    addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
    addChannelPatternsToArgs(args,fscAnalysisChannelWidgets,ui->fscAnalysisCustomPatternsCheckBox->isChecked(),ui->fscAnalysisCustomPatternsLineEdit->text(),prependedString,isMcc);

    addCharArrayToArgs(args,"xyPixelSize",prependedString,isMcc);
    addScalarToArgs(args,ui->fscAnalysisXyPixelSizeSpinBox->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"dz",prependedString,isMcc);
    addScalarToArgs(args,ui->fscAnalysisDzLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"dr",prependedString,isMcc);
    addScalarToArgs(args,ui->fscAnalysisDrLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"dtheta",prependedString,isMcc);
    addScalarToArgs(args,ui->fscAnalysisDthetaLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"resThreshMethod",prependedString,isMcc);
    addCharArrayToArgs(args,ui->fscAnalysisResThreshMethodLineEdit->text().toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"resThresh",prependedString,isMcc);
    addScalarToArgs(args,ui->fscAnalysisResTheshLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"resAxis",prependedString,isMcc);
    addCharArrayToArgs(args,ui->fscAnalysisResAxisLineEdit->text().toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"N",prependedString,isMcc);
    std::vector<std::string> nV = {ui->fscAnalysisNYSpinBox->text().toStdString(),ui->fscAnalysisNXSpinBox->text().toStdString(),ui->fscAnalysisNZSpinBox->text().toStdString()};
    addArrayToArgs(args,nV,false,prependedString,"[]",isMcc);

    if(ui->fscAnalysisBoundBoxCheckBox->isChecked()){
        addCharArrayToArgs(args,"bbox",prependedString,isMcc);
        std::vector<std::string> bboxV = {ui->fscAnalysisBoundBoxYMinSpinBox->text().toStdString(),ui->fscAnalysisBoundBoxXMinSpinBox->text().toStdString(),ui->fscAnalysisBoundBoxZMinSpinBox->text().toStdString(),ui->fscAnalysisBoundBoxYMaxSpinBox->text().toStdString(),ui->fscAnalysisBoundBoxXMaxSpinBox->text().toStdString(),ui->fscAnalysisBoundBoxZMaxSpinBox->text().toStdString()};
        addArrayToArgs(args,bboxV,false,prependedString,"[]",isMcc);
    }

    addCharArrayToArgs(args,"suffix",prependedString,isMcc);
    addCharArrayToArgs(args,ui->fscAnalysisSuffixLineEdit->text().toStdString(),prependedString,isMcc);

    addCharArrayToArgs(args,"iterInterval",prependedString,isMcc);
    addScalarToArgs(args,ui->fscAnalysisIterIntervalLineEdit->text().toStdString(),prependedString);

    addCharArrayToArgs(args,"masterCompute",prependedString,isMcc);
    addBoolToArgs(args,ui->fscAnalysisMasterComputeCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"mccMode",prependedString,isMcc);
    addBoolToArgs(args,isMcc,prependedString);

    // Config File Settings
    addCharArrayToArgs(args,"ConfigFile",prependedString,isMcc);
    addCharArrayToArgs(args,cFileVals.configFile.toStdString(),prependedString,isMcc);

    // TODO: ADD PARSE CLUSTER


    QString funcType = "fscAnalysis";
    // Send data to the MATLAB thread
    auto cMPJNPC = std::make_tuple(mainPath, QString("FSC Analysis"),true);
    emit jobStart(args, funcType, cMPJNPC, jobLogPaths, isMcc, pathToMatlab);
}


void MainWindow::on_psfDetectionAnalysisSubmitButton_clicked()
{
    messageBoxError("This feature is currently still being developed!");
    return;
    // TODO: FINISH IMPLEMENTING THIS

    // TODO: Write a function for this stuff

    // Write settings in case of crash
    writeSettings();

    // Disable submit button
    ui->psfDetectionAnalysisSubmitButton->setEnabled(false);

    if(!psfDetectionAnalysisDPaths.size()) return;

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = psfDetectionAnalysisDPaths[0].masterPath;

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }


    addDataPathsToArgs(args,firstPrependedString,psfDetectionAnalysisDPaths,isMcc);

    addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
    addChannelPatternsToArgs(args,psfDetectionAnalysisChannelWidgets,ui->psfDetectionAnalysisCustomPatternsCheckBox->isChecked(),ui->psfDetectionAnalysisCustomPatternsLineEdit->text(),prependedString,isMcc);
    /*
    data.push_back(factory.createCharArray("Channels"));
    QString patternLine = ui->psfDetectionAnalysisChannelsLineEdit->text();
    QString pattern;
    std::vector<QString> patterns;
    for(int i = 0; i < patternLine.size(); i++){
        if(patternLine[i] == ','){
            patterns.push_back(pattern);
            pattern.clear();
        }
        else{
            pattern.push_back(patternLine[i]);
        }
    }
    if(pattern.size()) patterns.push_back(pattern);

    matlab::data::Array channelPatterns = factory.createArray<double>({1,patterns.size()});
    for(size_t i = 0; i < patterns.size(); i++){
        channelPatterns[i] = patterns[i].toDouble();
    }
    data.push_back(channelPatterns);

    data.push_back(factory.createCharArray("RWFn"));
    QString RWFnpatternLine = ui->psfDetectionAnalysisRWFnLineEdit->text();
    QString RWFnpattern;
    std::vector<QString> RWFnpatterns;
    for(int i = 0; i < RWFnpatternLine.size(); i++){
        if(RWFnpatternLine[i] == ','){
            RWFnpatterns.push_back(pattern);
            RWFnpattern.clear();
        }
        else{
            RWFnpattern.push_back(patternLine[i]);
        }
    }
    if(RWFnpattern.size()) RWFnpatterns.push_back(pattern);

    matlab::data::CellArray RWFnPatternsF = factory.createCellArray({1,RWFnpatterns.size()});
    for(size_t i = 0; i < RWFnpatterns.size(); i++){
        RWFnPatternsF[i] = RWFnpatterns[i].toStdString();
    }
    data.push_back(RWFnPatternsF);

    data.push_back(factory.createCharArray("xyPixelSize"));
    data.push_back(factory.createScalar<double>(ui->psfDetectionAnalysisXyPixelSizeSpinBox->value()));

    data.push_back(factory.createCharArray("dz"));
    data.push_back(factory.createScalar<double>(ui->psfDetectionAnalysisDzLineEdit->text().toDouble()));

    data.push_back(factory.createCharArray("angle"));
    data.push_back(factory.createScalar<double>(ui->psfDetectionAnalysisSkewAngleSpinBox->text().toDouble()));

    data.push_back(factory.createCharArray("sourceStr"));
    data.push_back(factory.createCharArray(ui->psfDetectionAnalysisSourceStrLineEdit->text().toStdString()));

    if(ui->psfDetectionAnalysisAnalysisOnlyRadioButton->isChecked()){
        data.push_back(factory.createCharArray("Deskew"));
        data.push_back(factory.createScalar<bool>(ui->psfDetectionAnalysisDeskewCheckBox->isChecked()));

        data.push_back(factory.createCharArray("flipZstack"));
        data.push_back(factory.createScalar<bool>(ui->psfDetectionAnalysisFlipZStackCheckBox->isChecked()));

        data.push_back(factory.createCharArray("ObjectiveScan"));
        data.push_back(factory.createScalar<bool>(ui->psfDetectionAnalysisObjectiveScanCheckBox->isChecked()));

        data.push_back(factory.createCharArray("ZstageScan"));
        data.push_back(factory.createScalar<bool>(ui->psfDetectionAnalysisZStageScanCheckBox->isChecked()));

        data.push_back(factory.createCharArray("Save16bit"));
        data.push_back(factory.createScalar<bool>(ui->psfDetectionAnalysisSave16BitCheckBox->isChecked()));

        data.push_back(factory.createCharArray("masterCompute"));
        data.push_back(factory.createScalar<bool>(ui->psfDetectionAnalysisMasterComputeCheckBox->isChecked()));
    }
    else{
        data.push_back(factory.createCharArray("cropSize"));
        data.push_back(factory.createArray<double>({1,3},{ui->psfDetectionAnalysisCropSizeYDoubleSpinBox->value(),ui->psfDetectionAnalysisCropSizeXDoubleSpinBox->value(),ui->psfDetectionAnalysisCropSizeZDoubleSpinBox->value()}));

        data.push_back(factory.createCharArray("distThresh"));
        data.push_back(factory.createArray<double>({1,3},{ui->psfDetectionAnalysisDistThreshYDoubleSpinBox->value(),ui->psfDetectionAnalysisDistThreshXDoubleSpinBox->value(),ui->psfDetectionAnalysisDistThreshZDoubleSpinBox->value()}));
    }
    */
}


void MainWindow::on_tiffZarrConverterSubmitButton_clicked()
{
    messageBoxError("This feature is currently still being developed!");
    return;
    // Write settings in case of crash
    writeSettings();

    // Disable submit button
    ui->tiffZarrConverterSubmitButton->setEnabled(false);

    if(!tiffZarrConverterDPaths.size()) return;

    // We need this to convert C++ vars to MATLAB vars
    //matlab::data::ArrayFactory factory;

    // outA is the number of outputs (always zero) and data is the structure to hold the pipeline settings
    //size_t outA = 0;
    //std::vector<matlab::data::Array> data;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = tiffZarrConverterDPaths[0].masterPath;

    // Data Paths
    /*
    unsigned long long numPaths = 0;
    for(const auto &path : tiffZarrConverterDPaths){
        if(path.includeMaster){
            QDirIterator it(path.masterPath,QDir::Files);
            if(it.hasNext()) numPaths++;
        }
        for(const auto &subPath : path.subPaths){
            if(subPath.second.first){
                QDirIterator it(subPath.second.second,QDir::Files);
                if(it.hasNext()) numPaths++;
            }
        }
    }
    matlab::data::CellArray dataPaths_exps = factory.createCellArray({1,numPaths});
    size_t currPath = 0;
    for(const auto &path : tiffZarrConverterDPaths){
        if(path.includeMaster){
            QDirIterator it(path.masterPath,QDir::Files);
            if(it.hasNext()){
                dataPaths_exps[currPath] = factory.createCharArray(path.masterPath.toStdString());
                currPath++;
            }
            else std::cout << "WARNING: Data Path: " << path.masterPath.toStdString() << " not included because it contains no files. Continuing." << std::endl;
        }
        for(const auto &subPath : path.subPaths){
            if(subPath.second.first){
                QDirIterator it(subPath.second.second,QDir::Files);
                if(it.hasNext()){
                    dataPaths_exps[currPath] = factory.createCharArray(subPath.second.second.toStdString());
                    currPath++;
                }
                else std::cout << "WARNING: Data Path: " << subPath.second.second.toStdString() << " not included because it contains no files. Continuing." << std::endl;
            }
        }
    }
    data.push_back(dataPaths_exps);

    // Channel Patterns
    data.push_back(factory.createCharArray("ChannelPatterns"));
    if(!ui->psfDetectionAnalysisCustomPatternsCheckBox->isChecked()){
        if(psfDetectionAnalysisChannelWidgets.size()){
            // Grab indexes of checked boxes
            std::vector<int> indexes;
            for(size_t i = 0; i < psfDetectionAnalysisChannelWidgets.size(); i++){
                if(psfDetectionAnalysisChannelWidgets[i].second->isChecked()) indexes.push_back(i);
            }
            matlab::data::CellArray channelPatterns = factory.createCellArray({1,indexes.size()});
            int cpi = 0;
            // Go through checked indexes and the label text (channel pattern) in the cell array
            for(int i : indexes){
                // Convert from rich text to plain text
                QTextDocument toPlain;
                toPlain.setHtml(psfDetectionAnalysisChannelWidgets[i].first->text());
                channelPatterns[cpi] = factory.createCharArray(toPlain.toPlainText().toStdString());
                cpi++;
            }
            data.push_back(channelPatterns);
        }
    }
    // Use custom patterns
    else{
        QString patternLine = ui->psfDetectionAnalysisCustomPatternsLineEdit->text();
        QString pattern;
        std::vector<QString> patterns;
        for(int i = 0; i < patternLine.size(); i++){
            if(patternLine[i] == ','){
                patterns.push_back(pattern);
                pattern.clear();
            }
            else{
                pattern.push_back(patternLine[i]);
            }
        }
        if(pattern.size()) patterns.push_back(pattern);

        matlab::data::CellArray channelPatterns = factory.createCellArray({1,patterns.size()});
        for(size_t i = 0; i < patterns.size(); i++){
            channelPatterns[i] = factory.createCharArray(patterns[i].toStdString());
        }
        data.push_back(channelPatterns);
    }

    if(ui->tiffZarrConverterTiffToZarrRadioButton->isChecked()){

    }
    else{

    }
    */
}


void MainWindow::on_mipGeneratorSubmitButton_clicked()
{
    // Write settings in case of crash
    writeSettings();

    // Disable submit button
    ui->mipGeneratorSubmitButton->setEnabled(false);

    std::string args;

    // NOTE: We have to push a lot of things into our data array one at a time
    // Potentially in the future I can loop through the widgets and do this in fewer lines

    // Set main path. This is where all the output files made by the GUI will be stored.
    QString mainPath = mipGeneratorDPaths[0].masterPath;

    const std::string firstPrependedString = "";
    std::string prependedString;
    if(isMcc){
        prependedString = " ";
    }
    else{
        prependedString = ",";
    }

    addDataPathsToArgs(args,firstPrependedString,mipGeneratorDPaths,isMcc);

    addCharArrayToArgs(args,"ChannelPatterns",prependedString,isMcc);
    addChannelPatternsToArgs(args,mipGeneratorChannelWidgets,ui->mipGeneratorCustomPatternsCheckBox->isChecked(),ui->mipGeneratorCustomPatternsLineEdit->text(),prependedString,isMcc);

    addCharArrayToArgs(args,"axis",prependedString,isMcc);
    std::vector<std::string> axisV = {ui->mipGeneratorAxisYSpinBox->text().toStdString(),ui->mipGeneratorAxisXSpinBox->text().toStdString(),ui->mipGeneratorAxisZSpinBox->text().toStdString()};
    addArrayToArgs(args,axisV,false,prependedString,"[]",isMcc);

    addCharArrayToArgs(args,"zarrFile",prependedString,isMcc);
    addBoolToArgs(args,ui->mipGeneratorZarrFileCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"largeZarr",prependedString,isMcc);
    addBoolToArgs(args,ui->mipGeneratorLargeZarrCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"Save16bit",prependedString,isMcc);
    addBoolToArgs(args,ui->mipGeneratorSave16BitCheckBox->isChecked(),prependedString);

    // Job Settings
    addCharArrayToArgs(args,"parseCluster",prependedString,isMcc);
    addBoolToArgs(args,ui->mipGeneratorParseClusterCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"masterCompute",prependedString,isMcc);
    addBoolToArgs(args,ui->mipGeneratorMasterComputeCheckBox->isChecked(),prependedString);

    addCharArrayToArgs(args,"cpusPerTask",prependedString,isMcc);
    addScalarToArgs(args,ui->mipGeneratorCpusPerTaskLineEdit->text().toStdString(),prependedString);

    // Advanced Job Settings
    if(!ui->mipGeneratorJobLogDirLineEdit->text().isEmpty()){
        addCharArrayToArgs(args,"jobLogDir",prependedString,isMcc);
        addCharArrayToArgs(args,ui->mipGeneratorJobLogDirLineEdit->text().toStdString(),prependedString,isMcc);
    }

    if(!ui->mipGeneratorUuidLineEdit->text().isEmpty()){
        addCharArrayToArgs(args,"uuid",prependedString,isMcc);
        addCharArrayToArgs(args,ui->mipGeneratorUuidLineEdit->text().toStdString(),prependedString,isMcc);
    }

    addCharArrayToArgs(args,"mccMode",prependedString,isMcc);
    addBoolToArgs(args,isMcc,prependedString);

    // Config File Settings
    addCharArrayToArgs(args,"ConfigFile",prependedString,isMcc);
    addCharArrayToArgs(args,cFileVals.configFile.toStdString(),prependedString,isMcc);

    QString funcType = "mipGenerator";
    // Send data to the MATLAB thread
    auto cMPJNPC = std::make_tuple(mainPath, QString("MIP Generator Job"),ui->mipGeneratorParseClusterCheckBox->isChecked());
    emit jobStart(args, funcType, cMPJNPC, jobLogPaths, isMcc, pathToMatlab);
}
