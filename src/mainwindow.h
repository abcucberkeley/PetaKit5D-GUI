#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matlabthreadmanager.h"
#include "matlaboutputwindow.h"
#include "datapath.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QThread>
#include <QMessageBox>
#include "mainwindowconsoleoutputwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Class to hold advanced options from the user
class GUIvals{
    public:
        // Main Advanced Settings
        double skewAngle;
        bool dzFromEncoder;
        bool Reverse;
        bool parseSettingFile;

        // DSR Advanced Settings
        bool flipZStack;
        bool BKRemoval;
        double LowerLimit;
        QString resampleType;
        bool resampleEnabled;
        std::vector<double> resample;
        bool zarrFile;
        bool saveZarr;
        bool save3DStack;

        // Stitch Advanced Settings
        bool boundboxCropCheckBox;
        std::vector<std::string> boundboxCrop;
        std::vector<bool> stitchMIP;
        QString stitchInfoFullpath;
        bool processFunPath;
        std::vector <QString> stitchFFImagePaths;
        std::vector <QString> stitchBackgroundPaths;
        QString TileOffset;
        QString stitchLowerLimit;
        bool stitchFFBackground;
        QString shiftMethod;
        QString overlapType;
        bool distBboxesCheckBox;
        std::vector<std::string> distBboxes;

        // Decon Advanced Settings
        QString RLMethod;
        bool debug;
        QString saveStep;
        QString largeMethod;
        double dampFactor;
        std::vector<std::string> scaleFactor;
        uint64_t deconOffset;
        std::vector<std::string> deconMaskFns;
        QString edgeErosion;
        bool erodeByFTP;
        bool deconRotate;

        // Job Advanced Settings
        bool largeFile;
        QString jobLogDir;
        QString uuid;
        uint64_t maxTrialNum;
        uint64_t unitWaitTime;
        uint64_t minModifyTime;
        uint64_t maxModifyTime;
        uint64_t maxWaitLoopNum;

        // DSR Large Scale Processing Settings
        bool SaveMIP;
        std::vector<std::string> batchSize;

        // Stitch Large Scale Processing Settings
        bool multiLoc;
        QString ProcessedDirStr;
        bool IOScan;
        std::vector<std::string> blockSize;
        std::vector<std::string> shardSize;
        bool InputBboxCheckBox;
        std::vector<std::string> InputBbox;
        bool tileOutBboxCheckBox;
        std::vector<std::string> tileOutBbox;
        std::vector<std::string> axisWeight;
        QString groupFile;
        bool usePrimaryCoords;
        QString EdgeArtifacts;
        bool masterCompute;
        std::vector<std::string> maskFns;

        GUIvals() : skewAngle{32.45},
                    dzFromEncoder{false},
                    Reverse{true},
                    parseSettingFile{false},
                    flipZStack{false},
                    BKRemoval{false},
                    LowerLimit{.4},
                    resampleType{"isotropic"},
                    resampleEnabled{false},
                    resample{1.0,1.0,1.0},
                    zarrFile{false},
                    saveZarr{false},
                    save3DStack{true},
                    boundboxCropCheckBox{false},
                    boundboxCrop{},
                    stitchMIP{false,false,false},
                    stitchInfoFullpath{""},
                    processFunPath{false},
                    stitchFFImagePaths{},
                    stitchBackgroundPaths{},
                    TileOffset{"0"},
                    stitchLowerLimit{".4"},
                    stitchFFBackground{false},
                    shiftMethod{"grid"},
                    overlapType{""},
                    distBboxesCheckBox{false},
                    distBboxes{"0","0","0","0","0","0"},
                    RLMethod{"OMW"},
                    debug{false},
                    saveStep{"5"},
                    largeMethod{"inmemory"},
                    dampFactor{1.0},
                    scaleFactor{},
                    deconOffset{0},
                    deconMaskFns{"","",""},
                    edgeErosion{"8"},
                    erodeByFTP{true},
                    deconRotate{false},
                    largeFile{false},
                    jobLogDir{"../job_logs"},
                    uuid{""},
                    maxTrialNum{3},
                    unitWaitTime{1},
                    minModifyTime{1},
                    maxModifyTime{10},
                    maxWaitLoopNum{10},
                    SaveMIP{true},
                    batchSize{"1024","1024","1024"},
                    multiLoc{false},
                    ProcessedDirStr{""},
                    IOScan{false},
                    blockSize{"256","256","256"},
                    shardSize{"0","0","0"},
                    InputBboxCheckBox{false},
                    InputBbox{},
                    tileOutBboxCheckBox{false},
                    tileOutBbox{},
                    axisWeight{"1",".1","10"},
                    groupFile{""},
                    usePrimaryCoords{false},
                    EdgeArtifacts{"2"},
                    masterCompute{true},
                    maskFns{"","",""}
        {}
};

// Class to hold advanced options for Sim Recon
class simReconVals{
    public:
        // Main Advanced Settings
        double skewAngle;
        double xyPixelSize;
        bool Reverse;

        // Recon Advanced Settings
        bool islattice;
        double NA_det;
        double NA_ext;
        double nimm;
        double wvl_em;
        double wvl_ext;
        double w;
        bool normalize_orientations;
        QString resultsDirName;
        bool perdecomp;
        bool edgeTaper;
        double edgeTaperVal;
        double intThresh;
        double occThresh;
        bool useGPU;
        QString gpuPrecision;
        double Overlap;
        std::vector<double> ChunkSize;
        double reconBatchNum;

        // Job Advanced Settings
        QString jobLogDir;
        QString uuid;
        uint64_t maxTrialNum;
        uint64_t unitWaitTime;
        uint64_t parPoolSize;
        uint64_t maxModifyTime;

        simReconVals(): skewAngle{32.45},
                        xyPixelSize{.108},
                        Reverse{true},
                        islattice{true},
                        NA_det{1.0},
                        NA_ext{0.55},
                        nimm{1.33},
                        wvl_em{0.605},
                        wvl_ext{0.560},
                        w{5e-3},
                        normalize_orientations{false},
                        resultsDirName{"sim_recon"},
                        perdecomp{true},
                        edgeTaper{false},
                        edgeTaperVal{0.1},
                        intThresh{1},
                        occThresh{0.8},
                        useGPU{true},
                        gpuPrecision{"single"},
                        Overlap{128},
                        ChunkSize{32,32,32},
                        reconBatchNum{5},
                        jobLogDir{"../job_logs"},
                        uuid{""},
                        maxTrialNum{3},
                        unitWaitTime{2},
                        parPoolSize{24},
                        maxModifyTime{10}

        {}
};

// Class to hold settings for config files
class configFileVals{
public:
    // Config File Locations
    QString configFile;
    QString gpuConfigFile;
    QString jvmConfigFile;

    // Config File Settings
    QString BashLaunchStr;
    bool GNUparallel;
    QString MCCMasterStr;
    QString MCRParam;
    double MemPerCPU;
    QString SlurmParam;
    qint64 jobTimeLimit;
    bool masterCompute;
    qint64 minCPUNum;
    qint64 maxCPUNum;
    qint64 maxJobNum;
    bool wholeNodeJob;

    configFileVals(): configFile{""},
        gpuConfigFile{""},
        jvmConfigFile{""},
        BashLaunchStr(""),
        GNUparallel(false),
        MCCMasterStr(""),
        MCRParam(""),
        MemPerCPU(4),
        SlurmParam(""),
        jobTimeLimit(12),
        masterCompute(true),
        minCPUNum(1),
        maxCPUNum(1),
        maxJobNum(5000),
        wholeNodeJob(false)

    {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool kill;

public slots:
    void onEnableSubmitButton();

signals:
    void jobStart(std::string &args, QString &funcType, std::tuple<QString, QString, bool> &mPathJNameParseCluster, std::unordered_map<int,std::pair<QString,QDateTime>> &jobLogPaths, bool isMcc, const std::string &pathToMatlab);
    void processingOutput(QByteArray data);
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // Using compiled scripts or matlab
    bool isMcc;
    std::string pathToMatlab;

    void writeSettings();
    void readMatlabPathSettings();
    void readConfigSettings();
    void readSettings();
    matlabThreadManager *mThreadManager;
    matlabOutputWindow *mOutputWindow;
    matlabOutputWindowThread *mOutputWindowThread;
    QMutex outputLock;
    GUIvals guiVals;
    std::vector<dataPath> dPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> channelWidgets;

    // Config Vals
    configFileVals cFileVals;

    // Sim Recon
    simReconVals simreconVals;
    std::vector<QString> simReconPsfFullPaths;
    std::vector<dataPath> simReconDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> simReconChannelWidgets;

    // Crop
    std::vector<dataPath> cropDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> cropChannelWidgets;

    // FFT Analysis
    std::vector<dataPath> fftAnalysisDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> fftAnalysisChannelWidgets;

    // FSC Analysis
    std::vector<dataPath> fscAnalysisDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> fscAnalysisChannelWidgets;

    // Image List Generator
    std::vector<dataPath> imageListGeneratorDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> imageListGeneratorChannelWidgets;

    // Imaris Converter
    std::vector<dataPath> imarisConverterDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> imarisConverterChannelWidgets;

    // mipGenerator
    std::vector<dataPath> mipGeneratorDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> mipGeneratorChannelWidgets;

    // psfDetectionAnalysis
    std::vector<dataPath> psfDetectionAnalysisDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> psfDetectionAnalysisChannelWidgets;
    std::vector<QString> rwfnPaths;

    // resample
    std::vector<dataPath> resampleDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> resampleChannelWidgets;

    // tiffZarrConverter
    std::vector<dataPath> tiffZarrConverterDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> tiffZarrConverterChannelWidgets;

    std::vector<QString> lsImagePaths;
    std::vector<QString> backgroundPaths;
    std::vector<QString> psfFullPaths;

    QString wienerAlphaDefaultValue;
    std::vector<QString> wienerAlphaValues;

    QString otfCumThreshDefaultValue;
    std::vector<QString> otfCumThreshValues;

    std::unordered_map<int,std::pair<QString,QDateTime>> jobLogPaths;
    std::unordered_map<int,QString> jobNames;

    bool loadSettings;
    void checkLoadPrevSettings();
    QString mostRecentDir;

    // Warnings
    bool parseClusterWarning;

    std::pair<std::string,std::string> prevFuncTypeArgs;
    bool sameJobSubmittedWarning;

private slots:
    void on_dsrAdvancedSettingsButton_clicked();

    void on_deconAdvancedSettingsButton_clicked();

    void on_jobAdvancedSettingsButton_clicked();

    void on_submitButton_clicked();

    void on_resultsDirLineEdit_textChanged(const QString &arg1);

    void on_mainAdvancedSettingsButton_clicked();

    void on_deskewCheckBox_stateChanged(int arg1);

    void on_rotateCheckBox_stateChanged(int arg1);

    void on_deskewAndRotateCheckBox_stateChanged(int arg1);

    void on_stitchCheckBox_stateChanged(int arg1);

    void on_mainNextButton_clicked();

    void on_dsrPreviousButton_clicked();

    void on_dsrNextButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_objectiveScanCheckBox_stateChanged(int arg1);

    void on_stitchPreviousButton_clicked();

    void on_stitchNextButton_clicked();

    void on_deconPreviousButton_clicked();

    void on_deconNextButton_clicked();

    void on_jobPreviousButton_clicked();

    void on_addPathsButton_clicked();

    void on_imageListFullPathsBrowseButton_clicked();

    void on_imageListFullPathsLineEdit_textChanged(const QString &arg1);

    void on_llffCorrectionCheckBox_stateChanged(int arg1);

    void on_lsImageAddPathsButton_clicked();

    void on_backgroundAddPathsButton_clicked();

    void on_psfFullAddPathsButton_2_clicked();

    void on_deconOnlyCheckBox_stateChanged(int arg1);

    void on_customPatternsCheckBox_stateChanged(int arg1);

    void on_simReconSubmitButton_clicked();

    void on_cropSubmitButton_clicked();

    void selectFolderPath();

    void on_simReconPsfFullAddPathsButton_clicked();

    void on_simReconCustomPatternsCheckBox_stateChanged(int arg1);

    void on_simReconMainAdvancedSettingsButton_clicked();

    void on_simReconReconAdvancedSettingsButton_clicked();

    void on_simReconJobAdvancedSettingsButton_clicked();

    void on_simReconMainNextButton_clicked();

    void on_simReconReconPreviousButton_clicked();

    void on_simReconReconNextButton_clicked();

    void on_simReconJobPreviousButton_clicked();

    void on_fftAnalysisSubmitButton_clicked();

    void on_fscAnalysisSubmitButton_clicked();

    void on_psfDetectionAnalysisSubmitButton_clicked();

    void on_tiffZarrConverterSubmitButton_clicked();

    void on_mipGeneratorSubmitButton_clicked();

    void on_cropCustomPatternsCheckBox_stateChanged(int arg1);

    void on_fscAnalysisCustomPatternsCheckBox_stateChanged(int arg1);

    void on_mipGeneratorCustomPatternsCheckBox_stateChanged(int arg1);

    void on_psfDetectionAnalysisCustomPatternsCheckBox_stateChanged(int arg1);

    void on_tiffZarrConverterCustomPatternsCheckBox_stateChanged(int arg1);

    void on_resampleSubmitButton_clicked();

    void on_largeScaleProcessingButton_clicked();

    void on_imarisConverterSubmitButton_clicked();

    void on_rlMethodButton_clicked();

    void on_skewedManualCheckBox_stateChanged(int arg1);

    void on_otfMaskingPSFFilenameBrowseButton_clicked();

    void on_otfMaskingSkewedManualCheckBox_stateChanged(int arg1);

    void on_otfMaskingSubmitButton_clicked();

    void on_stitchAdvancedSettingsButton_clicked();

    void on_stitchOnlineStitchCheckBox_stateChanged(int arg1);

    void on_wienerAlphaButton_clicked();

    void on_otfCumThreshButton_clicked();

    void on_tiffZarrConverterTiffToZarrRadioButton_toggled(bool checked);

    void on_imarisConverterBBoxCheckBox_stateChanged(int arg1);

    void on_resampleBBoxCheckBox_stateChanged(int arg1);

    void on_fscAnalysisBoundBoxCheckBox_stateChanged(int arg1);

    void on_fscAnalysisResThreshMethodComboBox_currentTextChanged(const QString &arg1);

    void on_resampleZarrFileCheckBox_stateChanged(int arg1);

    void on_AnalysisModeButton_clicked();

    void on_psfDetectionAnalysisRWFnButton_clicked();

    void on_imageListGeneratorSubmitButton_clicked();

    void on_fftAnalysisCustomPatternsCheckBox_stateChanged(int arg1);

    void on_imageListGeneratorCustomPatternsCheckBox_stateChanged(int arg1);

    void on_imarisConverterCustomPatternsCheckBox_stateChanged(int arg1);

    void on_resampleCustomPatternsCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    mainwindowConsoleOutputWindow* matlabJobLogsOutputWindow;
    mainwindowConsoleOutputWindow* terminalConsoleOutput;
};
#endif // MAINWINDOW_H
