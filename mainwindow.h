#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matlabthreadmanager.h"
#include "matlaboutputwindow.h"
#include "datapath.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QThread>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace matlab::engine;



// Class to hold options from the user
class GUIvals{
    public:

        // Main Advanced Settings
        double skewAngle;
        double xyPixelSize;
        bool Reverse;
        bool sCMOSCameraFlip;

        // DSR Advanced Settings
        bool BKRemoval;
        double LowerLimit;
        std::string resampleType;
        uint64_t resample;

        // Decon Advanced Settings
        std::string cppDeconPath;
        std::string loadModules;
        std::string cudaDeconPath;
        std::string OTFGENPath;
        std::string RLMethod;
        bool fixIter;
        double errThresh;
        bool debug;
        bool gpuJob;

        // Job Advanced Settings
        bool largeFile;
        std::string jobLogDir;
        std::string uuid;
        uint64_t maxTrialNum;
        uint64_t unitWaitTime;
        uint64_t minModifyTime;
        uint64_t maxModifyTime;
        uint64_t maxWaitLoopNum;
        std::string MatlabLaunchStr;
        std::string SlurmParam;

        GUIvals() : skewAngle{32.45},
                    xyPixelSize{.108},
                    Reverse{true},
                    sCMOSCameraFlip{false},
                    BKRemoval{false},
                    LowerLimit{.4},
                    resampleType{"isotropic"},
                    resample{0},
                    cppDeconPath{"/global/home/groups/software/sl-7.x86_64/modules/RLDecon_CPU/20200718/build-cluster/cpuDeconv"},
                    loadModules{"module load gcc/4.8.5; module load fftw/3.3.6-gcc; module load boost/1.65.1-gcc; module load libtiff/4.1.0; "},
                    cudaDeconPath{"/global/home/groups/software/sl-7.x86_64/modules/cudaDecon/bin/cudaDeconv"},
                    OTFGENPath{"/global/home/groups/software/sl-7.x86_64/modules/cudaDecon/bin/radialft"},
                    RLMethod{"simplified"},
                    fixIter{false},
                    errThresh{.00000001},
                    debug{false},
                    gpuJob{false},
                    largeFile{false},
                    jobLogDir{"../job_logs"},
                    uuid{""},
                    maxTrialNum{3},
                    unitWaitTime{1},
                    minModifyTime{1},
                    maxModifyTime{10},
                    maxWaitLoopNum{10},
                    MatlabLaunchStr{"module load matlab/r2020b; matlab -nodisplay -nosplash -nodesktop -nojvm -r"},
                    SlurmParam{"-p abc --qos abc_normal -n1 --mem-per-cpu=21418M"}
        {

        }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onEnableSubmitButton();
signals:
    void jobStart(size_t &outA, std::vector<matlab::data::Array> &data, std::string &funcType, std::string &mainPath);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void writeSettings();
    void readSettings();
    matlabThreadManager *mThreadManager;
    matlabOutputWindow *mOutputWindow;
    matlabOutputWindowThread *mOutputWindowThread;
    QMutex outputLock;
    GUIvals guiVals;
    std::vector<dataPath> dPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> channelWidgets;
    std::vector<dataPath> cropDPaths;
    std::vector<std::pair<QLabel*,QCheckBox*>> cropChannelWidgets;
    std::vector<std::string> lsImagePaths;
    std::vector<std::string> backgroundPaths;
    std::vector<std::string> psfFullPaths;
    bool loadSettings;
    void checkLoadPrevSettings();
    QString mostRecentDir;

private slots:
    void on_dsrAdvancedSettingsButton_clicked();

    void on_deconAdvancedSettingsButton_clicked();

    void on_jobAdvancedSettingsButton_clicked();

    void on_submitButton_clicked();

    void on_resultsDirBrowseButton_clicked();

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

    void on_boundBoxCheckBox_stateChanged(int arg1);

    void on_llffCorrectionCheckBox_stateChanged(int arg1);

    void on_lsImageAddPathsButton_clicked();

    void on_backgroundAddPathsButton_clicked();

    void on_psfFullAddPathsButton_2_clicked();

    void on_deconOnlyCheckBox_stateChanged(int arg1);

    void on_customPatternsCheckBox_stateChanged(int arg1);

    void on_cropSubmitButton_clicked();

    void selectFolderPath();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
