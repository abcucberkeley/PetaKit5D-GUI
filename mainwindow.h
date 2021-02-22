#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matlabthread.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include <QMainWindow>



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
                    cppDeconPath{""},
                    loadModules{""},
                    cudaDeconPath{""},
                    OTFGENPath{""},
                    largeFile{false},
                    jobLogDir{""},
                    uuid{""},
                    maxTrialNum{3},
                    unitWaitTime{1},
                    minModifyTime{1},
                    maxModifyTime{10},
                    maxWaitLoopNum{10},
                    MatlabLaunchStr{""},
                    SlurmParam{""}
        {

        }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void jobStart(const size_t outA, const std::vector<matlab::data::Array> &data);

private:
    matlabThread *mThread;
    GUIvals guiVals;
    std::vector<std::string> dPaths;

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
