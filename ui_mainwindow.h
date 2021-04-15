/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Main;
    QLabel *mainSettingsLabel;
    QLabel *dataPathsLabel;
    QPushButton *mainAdvancedSettingsButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *dzLabel;
    QLineEdit *dzLineEdit;
    QPushButton *mainNextButton;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *objectiveScanLabel;
    QCheckBox *objectiveScanCheckBox;
    QPushButton *addPathsButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *streamingLabel;
    QCheckBox *streamingCheckBox;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *channelPatternsLabel;
    QSpacerItem *horizontalSpacer_8;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_46;
    QLabel *deskewLabel;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *deskewCheckBox;
    QCheckBox *deskewDeconCheckBox;
    QCheckBox *deskewOverwriteDataCheckBox;
    QCheckBox *deskewSave16BitCheckBox;
    QCheckBox *deskewOnlyFirstTPCheckBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_16;
    QHBoxLayout *horizontalLayout_44;
    QLabel *rotateLabel;
    QSpacerItem *horizontalSpacer;
    QCheckBox *rotateCheckBox;
    QCheckBox *rotateDeconCheckBox;
    QCheckBox *rotateOverwriteDataCheckBox;
    QCheckBox *rotateSave16BitCheckBox;
    QCheckBox *rotateOnlyFirstTPCheckBox;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_17;
    QHBoxLayout *horizontalLayout_47;
    QLabel *deskewAndRotateLabel;
    QCheckBox *deskewAndRotateCheckBox;
    QCheckBox *deskewAndRotateDeconCheckBox;
    QCheckBox *deskewAndRotateOverwriteDataCheckBox;
    QCheckBox *deskewAndRotateSave16BitCheckBox;
    QCheckBox *deskewAndRotateOnlyFirstTPCheckBox;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_45;
    QLabel *stitchLabel;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *stitchCheckBox;
    QCheckBox *stitchDeconCheckBox;
    QCheckBox *stitchOverwriteDataCheckBox;
    QCheckBox *stitchSave16BitCheckBox;
    QCheckBox *stitchOnlyFirstTPCheckBox;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_32;
    QLabel *deconLabel;
    QSpacerItem *horizontalSpacer_7;
    QLabel *overwriteDataLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *save16BitLabel;
    QSpacerItem *horizontalSpacer_5;
    QLabel *onlyFirstTPLabel;
    QSpacerItem *horizontalSpacer_6;
    QWidget *DSR;
    QLabel *dsrSettingsLabel;
    QPushButton *dsrAdvancedSettingsButton;
    QPushButton *dsrNextButton;
    QPushButton *dsrPreviousButton;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *backgroundPathsLabel;
    QPushButton *backgroundAddPathsButton;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *lsImagePathsLabel;
    QPushButton *lsImageAddPathsButton;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_18;
    QLabel *parseSettingsFileLabel;
    QCheckBox *parseSettingsFileCheckBox;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_19;
    QLabel *flipZStackLabel;
    QCheckBox *flipZStackCheckBox;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_21;
    QLabel *llffCorrectionLabel;
    QCheckBox *llffCorrectionCheckBox;
    QWidget *Stitch;
    QLabel *stitchSettingsLabel;
    QPushButton *stitchPreviousButton;
    QPushButton *stitchNextButton;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *boundBoxCropLabel;
    QCheckBox *boundBoxCheckBox;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *primaryCHLabel;
    QLineEdit *primaryCHLineEdit;
    QWidget *layoutWidget_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *boundBoxXMinLabel;
    QSpinBox *boundBoxXMinSpinBox;
    QWidget *layoutWidget_12;
    QHBoxLayout *horizontalLayout_11;
    QLabel *boundBoxZMinLabel;
    QSpinBox *boundBoxZMinSpinBox;
    QWidget *layoutWidget_13;
    QHBoxLayout *horizontalLayout_12;
    QLabel *boundBoxYMaxLabel;
    QSpinBox *boundBoxYMaxSpinBox;
    QWidget *layoutWidget_14;
    QHBoxLayout *horizontalLayout_13;
    QLabel *boundBoxXMaxLabel;
    QSpinBox *boundBoxXMaxSpinBox;
    QWidget *layoutWidget_15;
    QHBoxLayout *horizontalLayout_14;
    QLabel *boundBoxZMaxLabel;
    QSpinBox *boundBoxZMaxSpinBox;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_23;
    QLabel *resultsDirLabel;
    QLineEdit *resultsDirLineEdit;
    QPushButton *resultsDirBrowseButton;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_24;
    QLabel *imageListFullPathsLabel;
    QLineEdit *imageListFullPathsLineEdit;
    QPushButton *imageListFullPathsBrowseButton;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_25;
    QLabel *axisOrderLabel;
    QLineEdit *axisOrderLineEdit;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_26;
    QLabel *blendMethodLabel;
    QComboBox *blendMethodComboBox;
    QWidget *layoutWidget10;
    QHBoxLayout *horizontalLayout_27;
    QLabel *xCorrShiftLabel;
    QCheckBox *xCorrShiftCheckBox;
    QWidget *layoutWidget11;
    QHBoxLayout *horizontalLayout_28;
    QLabel *xCorrModeLabel;
    QComboBox *xCorrModeComboBox;
    QWidget *layoutWidget12;
    QHBoxLayout *horizontalLayout_22;
    QLabel *stitchPipelineLabel;
    QComboBox *stitchPipelineComboBox;
    QWidget *layoutWidget13;
    QHBoxLayout *horizontalLayout;
    QLabel *boundBoxYMinLabel;
    QSpinBox *boundBoxYMinSpinBox;
    QWidget *Decon;
    QLabel *deconSettingsLabel;
    QPushButton *deconAdvancedSettingsButton;
    QPushButton *deconPreviousButton;
    QPushButton *deconNextButton;
    QWidget *layoutWidget_10;
    QHBoxLayout *horizontalLayout_31;
    QLabel *matlabDeconLabel;
    QRadioButton *matlabDeconRadioButton;
    QWidget *layoutWidget14;
    QHBoxLayout *horizontalLayout_29;
    QLabel *cudaDeconLabel;
    QRadioButton *cudaDeconRadioButton;
    QWidget *layoutWidget15;
    QHBoxLayout *horizontalLayout_30;
    QLabel *cppDeconLabel;
    QRadioButton *cppDeconRadioButton;
    QWidget *layoutWidget16;
    QHBoxLayout *horizontalLayout_33;
    QLabel *backgroundIntensityLabel;
    QLineEdit *backgroundIntensityLineEdit;
    QWidget *layoutWidget17;
    QHBoxLayout *horizontalLayout_34;
    QLabel *dzPSFLabel;
    QLineEdit *dzPSFLineEdit;
    QWidget *layoutWidget18;
    QHBoxLayout *horizontalLayout_37;
    QLabel *deconRotateLabel;
    QCheckBox *deconRotateCheckBox;
    QWidget *layoutWidget19;
    QHBoxLayout *horizontalLayout_38;
    QLabel *psfFullPathsLabel;
    QPushButton *psfFullAddPathsButton_2;
    QWidget *layoutWidget20;
    QHBoxLayout *horizontalLayout_39;
    QLabel *deconIterationsLabel;
    QLineEdit *deconIterationsLineEdit;
    QWidget *layoutWidget21;
    QHBoxLayout *horizontalLayout_40;
    QLabel *rotatePSFLabel;
    QCheckBox *rotatePSFCheckBox;
    QWidget *layoutWidget22;
    QHBoxLayout *horizontalLayout_35;
    QLabel *edgeErosionLabel;
    QLineEdit *edgeErosionLineEdit;
    QWidget *layoutWidget23;
    QHBoxLayout *horizontalLayout_36;
    QLabel *erodeByFTPLabel;
    QCheckBox *erodeByFTPCheckBox;
    QWidget *Job;
    QLabel *jobSettingsLabel;
    QPushButton *jobAdvancedSettingsButton;
    QPushButton *submitButton;
    QPushButton *jobPreviousButton;
    QLabel *maxCPUs;
    QWidget *layoutWidget24;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_41;
    QLabel *parseClusterLabel;
    QCheckBox *parseClusterCheckBox;
    QHBoxLayout *horizontalLayout_42;
    QLabel *cpusPerTaskLabel;
    QLineEdit *cpusPerTaskLineEdit;
    QHBoxLayout *horizontalLayout_43;
    QLabel *cpuOnlyNodesLabel;
    QCheckBox *cpuOnlyNodesCheckBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *deconTypeButtonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(801, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 0, 801, 562));
        Main = new QWidget();
        Main->setObjectName(QString::fromUtf8("Main"));
        QFont font;
        font.setStrikeOut(false);
        font.setKerning(true);
        Main->setFont(font);
        mainSettingsLabel = new QLabel(Main);
        mainSettingsLabel->setObjectName(QString::fromUtf8("mainSettingsLabel"));
        mainSettingsLabel->setGeometry(QRect(270, 10, 231, 51));
        QFont font1;
        font1.setPointSize(24);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        mainSettingsLabel->setFont(font1);
        dataPathsLabel = new QLabel(Main);
        dataPathsLabel->setObjectName(QString::fromUtf8("dataPathsLabel"));
        dataPathsLabel->setGeometry(QRect(270, 70, 90, 19));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        dataPathsLabel->setFont(font2);
        mainAdvancedSettingsButton = new QPushButton(Main);
        mainAdvancedSettingsButton->setObjectName(QString::fromUtf8("mainAdvancedSettingsButton"));
        mainAdvancedSettingsButton->setGeometry(QRect(620, 10, 161, 23));
        layoutWidget = new QWidget(Main);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(290, 160, 146, 25));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        dzLabel = new QLabel(layoutWidget);
        dzLabel->setObjectName(QString::fromUtf8("dzLabel"));
        dzLabel->setFont(font2);

        horizontalLayout_6->addWidget(dzLabel);

        dzLineEdit = new QLineEdit(layoutWidget);
        dzLineEdit->setObjectName(QString::fromUtf8("dzLineEdit"));
        dzLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(dzLineEdit);

        mainNextButton = new QPushButton(Main);
        mainNextButton->setObjectName(QString::fromUtf8("mainNextButton"));
        mainNextButton->setEnabled(false);
        mainNextButton->setGeometry(QRect(440, 420, 111, 61));
        mainNextButton->setFont(font2);
        layoutWidget_8 = new QWidget(Main);
        layoutWidget_8->setObjectName(QString::fromUtf8("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(290, 190, 156, 21));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_8);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        objectiveScanLabel = new QLabel(layoutWidget_8);
        objectiveScanLabel->setObjectName(QString::fromUtf8("objectiveScanLabel"));
        objectiveScanLabel->setFont(font2);

        horizontalLayout_9->addWidget(objectiveScanLabel);

        objectiveScanCheckBox = new QCheckBox(layoutWidget_8);
        objectiveScanCheckBox->setObjectName(QString::fromUtf8("objectiveScanCheckBox"));
        objectiveScanCheckBox->setAutoFillBackground(false);

        horizontalLayout_9->addWidget(objectiveScanCheckBox);

        addPathsButton = new QPushButton(Main);
        addPathsButton->setObjectName(QString::fromUtf8("addPathsButton"));
        addPathsButton->setGeometry(QRect(370, 70, 111, 23));
        layoutWidget1 = new QWidget(Main);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(270, 100, 213, 21));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        streamingLabel = new QLabel(layoutWidget1);
        streamingLabel->setObjectName(QString::fromUtf8("streamingLabel"));
        streamingLabel->setFont(font2);

        horizontalLayout_3->addWidget(streamingLabel);

        streamingCheckBox = new QCheckBox(layoutWidget1);
        streamingCheckBox->setObjectName(QString::fromUtf8("streamingCheckBox"));

        horizontalLayout_3->addWidget(streamingCheckBox);

        layoutWidget2 = new QWidget(Main);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(160, 130, 571, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        channelPatternsLabel = new QLabel(layoutWidget2);
        channelPatternsLabel->setObjectName(QString::fromUtf8("channelPatternsLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(channelPatternsLabel->sizePolicy().hasHeightForWidth());
        channelPatternsLabel->setSizePolicy(sizePolicy);
        channelPatternsLabel->setFont(font2);

        horizontalLayout_4->addWidget(channelPatternsLabel);

        horizontalSpacer_8 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        horizontalLayoutWidget = new QWidget(Main);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 250, 711, 31));
        horizontalLayout_15 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        deskewLabel = new QLabel(horizontalLayoutWidget);
        deskewLabel->setObjectName(QString::fromUtf8("deskewLabel"));
        deskewLabel->setFont(font2);

        horizontalLayout_46->addWidget(deskewLabel);

        horizontalSpacer_2 = new QSpacerItem(45, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_2);

        deskewCheckBox = new QCheckBox(horizontalLayoutWidget);
        deskewCheckBox->setObjectName(QString::fromUtf8("deskewCheckBox"));
        deskewCheckBox->setEnabled(true);
        deskewCheckBox->setAutoFillBackground(false);
        deskewCheckBox->setCheckable(true);

        horizontalLayout_46->addWidget(deskewCheckBox);

        deskewDeconCheckBox = new QCheckBox(horizontalLayoutWidget);
        deskewDeconCheckBox->setObjectName(QString::fromUtf8("deskewDeconCheckBox"));
        deskewDeconCheckBox->setEnabled(false);
        deskewDeconCheckBox->setAutoFillBackground(false);
        deskewDeconCheckBox->setCheckable(true);

        horizontalLayout_46->addWidget(deskewDeconCheckBox);

        deskewOverwriteDataCheckBox = new QCheckBox(horizontalLayoutWidget);
        deskewOverwriteDataCheckBox->setObjectName(QString::fromUtf8("deskewOverwriteDataCheckBox"));
        deskewOverwriteDataCheckBox->setEnabled(false);
        deskewOverwriteDataCheckBox->setAutoFillBackground(false);
        deskewOverwriteDataCheckBox->setCheckable(true);

        horizontalLayout_46->addWidget(deskewOverwriteDataCheckBox);

        deskewSave16BitCheckBox = new QCheckBox(horizontalLayoutWidget);
        deskewSave16BitCheckBox->setObjectName(QString::fromUtf8("deskewSave16BitCheckBox"));
        deskewSave16BitCheckBox->setEnabled(false);
        deskewSave16BitCheckBox->setAutoFillBackground(false);

        horizontalLayout_46->addWidget(deskewSave16BitCheckBox);

        deskewOnlyFirstTPCheckBox = new QCheckBox(horizontalLayoutWidget);
        deskewOnlyFirstTPCheckBox->setObjectName(QString::fromUtf8("deskewOnlyFirstTPCheckBox"));
        deskewOnlyFirstTPCheckBox->setEnabled(false);
        deskewOnlyFirstTPCheckBox->setAutoFillBackground(false);

        horizontalLayout_46->addWidget(deskewOnlyFirstTPCheckBox);


        horizontalLayout_15->addLayout(horizontalLayout_46);

        horizontalLayoutWidget_2 = new QWidget(Main);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(50, 290, 711, 31));
        horizontalLayout_16 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        rotateLabel = new QLabel(horizontalLayoutWidget_2);
        rotateLabel->setObjectName(QString::fromUtf8("rotateLabel"));
        rotateLabel->setEnabled(true);
        rotateLabel->setFont(font2);

        horizontalLayout_44->addWidget(rotateLabel);

        horizontalSpacer = new QSpacerItem(45, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer);

        rotateCheckBox = new QCheckBox(horizontalLayoutWidget_2);
        rotateCheckBox->setObjectName(QString::fromUtf8("rotateCheckBox"));
        rotateCheckBox->setEnabled(true);
        rotateCheckBox->setAutoFillBackground(false);

        horizontalLayout_44->addWidget(rotateCheckBox);

        rotateDeconCheckBox = new QCheckBox(horizontalLayoutWidget_2);
        rotateDeconCheckBox->setObjectName(QString::fromUtf8("rotateDeconCheckBox"));
        rotateDeconCheckBox->setEnabled(false);
        rotateDeconCheckBox->setAutoFillBackground(false);

        horizontalLayout_44->addWidget(rotateDeconCheckBox);

        rotateOverwriteDataCheckBox = new QCheckBox(horizontalLayoutWidget_2);
        rotateOverwriteDataCheckBox->setObjectName(QString::fromUtf8("rotateOverwriteDataCheckBox"));
        rotateOverwriteDataCheckBox->setEnabled(false);
        rotateOverwriteDataCheckBox->setAutoFillBackground(false);

        horizontalLayout_44->addWidget(rotateOverwriteDataCheckBox);

        rotateSave16BitCheckBox = new QCheckBox(horizontalLayoutWidget_2);
        rotateSave16BitCheckBox->setObjectName(QString::fromUtf8("rotateSave16BitCheckBox"));
        rotateSave16BitCheckBox->setEnabled(false);
        rotateSave16BitCheckBox->setAutoFillBackground(false);

        horizontalLayout_44->addWidget(rotateSave16BitCheckBox);

        rotateOnlyFirstTPCheckBox = new QCheckBox(horizontalLayoutWidget_2);
        rotateOnlyFirstTPCheckBox->setObjectName(QString::fromUtf8("rotateOnlyFirstTPCheckBox"));
        rotateOnlyFirstTPCheckBox->setEnabled(false);
        rotateOnlyFirstTPCheckBox->setAutoFillBackground(false);

        horizontalLayout_44->addWidget(rotateOnlyFirstTPCheckBox);


        horizontalLayout_16->addLayout(horizontalLayout_44);

        horizontalLayoutWidget_3 = new QWidget(Main);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(50, 330, 711, 31));
        horizontalLayout_17 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        deskewAndRotateLabel = new QLabel(horizontalLayoutWidget_3);
        deskewAndRotateLabel->setObjectName(QString::fromUtf8("deskewAndRotateLabel"));
        deskewAndRotateLabel->setFont(font2);

        horizontalLayout_47->addWidget(deskewAndRotateLabel);

        deskewAndRotateCheckBox = new QCheckBox(horizontalLayoutWidget_3);
        deskewAndRotateCheckBox->setObjectName(QString::fromUtf8("deskewAndRotateCheckBox"));
        deskewAndRotateCheckBox->setEnabled(true);
        deskewAndRotateCheckBox->setAutoFillBackground(false);
        deskewAndRotateCheckBox->setCheckable(true);

        horizontalLayout_47->addWidget(deskewAndRotateCheckBox);

        deskewAndRotateDeconCheckBox = new QCheckBox(horizontalLayoutWidget_3);
        deskewAndRotateDeconCheckBox->setObjectName(QString::fromUtf8("deskewAndRotateDeconCheckBox"));
        deskewAndRotateDeconCheckBox->setEnabled(false);
        deskewAndRotateDeconCheckBox->setAutoFillBackground(false);
        deskewAndRotateDeconCheckBox->setCheckable(true);

        horizontalLayout_47->addWidget(deskewAndRotateDeconCheckBox);

        deskewAndRotateOverwriteDataCheckBox = new QCheckBox(horizontalLayoutWidget_3);
        deskewAndRotateOverwriteDataCheckBox->setObjectName(QString::fromUtf8("deskewAndRotateOverwriteDataCheckBox"));
        deskewAndRotateOverwriteDataCheckBox->setEnabled(false);
        deskewAndRotateOverwriteDataCheckBox->setAutoFillBackground(false);
        deskewAndRotateOverwriteDataCheckBox->setCheckable(true);

        horizontalLayout_47->addWidget(deskewAndRotateOverwriteDataCheckBox);

        deskewAndRotateSave16BitCheckBox = new QCheckBox(horizontalLayoutWidget_3);
        deskewAndRotateSave16BitCheckBox->setObjectName(QString::fromUtf8("deskewAndRotateSave16BitCheckBox"));
        deskewAndRotateSave16BitCheckBox->setEnabled(false);
        deskewAndRotateSave16BitCheckBox->setAutoFillBackground(false);

        horizontalLayout_47->addWidget(deskewAndRotateSave16BitCheckBox);

        deskewAndRotateOnlyFirstTPCheckBox = new QCheckBox(horizontalLayoutWidget_3);
        deskewAndRotateOnlyFirstTPCheckBox->setObjectName(QString::fromUtf8("deskewAndRotateOnlyFirstTPCheckBox"));
        deskewAndRotateOnlyFirstTPCheckBox->setEnabled(false);
        deskewAndRotateOnlyFirstTPCheckBox->setAutoFillBackground(false);

        horizontalLayout_47->addWidget(deskewAndRotateOnlyFirstTPCheckBox);


        horizontalLayout_17->addLayout(horizontalLayout_47);

        horizontalLayoutWidget_4 = new QWidget(Main);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(50, 370, 711, 31));
        horizontalLayout_20 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        stitchLabel = new QLabel(horizontalLayoutWidget_4);
        stitchLabel->setObjectName(QString::fromUtf8("stitchLabel"));
        stitchLabel->setFont(font2);

        horizontalLayout_45->addWidget(stitchLabel);

        horizontalSpacer_3 = new QSpacerItem(45, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_3);

        stitchCheckBox = new QCheckBox(horizontalLayoutWidget_4);
        stitchCheckBox->setObjectName(QString::fromUtf8("stitchCheckBox"));
        stitchCheckBox->setAutoFillBackground(false);

        horizontalLayout_45->addWidget(stitchCheckBox);

        stitchDeconCheckBox = new QCheckBox(horizontalLayoutWidget_4);
        stitchDeconCheckBox->setObjectName(QString::fromUtf8("stitchDeconCheckBox"));
        stitchDeconCheckBox->setEnabled(false);
        stitchDeconCheckBox->setAutoFillBackground(false);

        horizontalLayout_45->addWidget(stitchDeconCheckBox);

        stitchOverwriteDataCheckBox = new QCheckBox(horizontalLayoutWidget_4);
        stitchOverwriteDataCheckBox->setObjectName(QString::fromUtf8("stitchOverwriteDataCheckBox"));
        stitchOverwriteDataCheckBox->setEnabled(false);
        stitchOverwriteDataCheckBox->setAutoFillBackground(false);

        horizontalLayout_45->addWidget(stitchOverwriteDataCheckBox);

        stitchSave16BitCheckBox = new QCheckBox(horizontalLayoutWidget_4);
        stitchSave16BitCheckBox->setObjectName(QString::fromUtf8("stitchSave16BitCheckBox"));
        stitchSave16BitCheckBox->setEnabled(false);
        stitchSave16BitCheckBox->setAutoFillBackground(false);

        horizontalLayout_45->addWidget(stitchSave16BitCheckBox);

        stitchOnlyFirstTPCheckBox = new QCheckBox(horizontalLayoutWidget_4);
        stitchOnlyFirstTPCheckBox->setObjectName(QString::fromUtf8("stitchOnlyFirstTPCheckBox"));
        stitchOnlyFirstTPCheckBox->setEnabled(false);
        stitchOnlyFirstTPCheckBox->setAutoFillBackground(false);

        horizontalLayout_45->addWidget(stitchOnlyFirstTPCheckBox);


        horizontalLayout_20->addLayout(horizontalLayout_45);

        horizontalLayoutWidget_5 = new QWidget(Main);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(300, 220, 441, 31));
        horizontalLayout_32 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(0, 0, 0, 0);
        deconLabel = new QLabel(horizontalLayoutWidget_5);
        deconLabel->setObjectName(QString::fromUtf8("deconLabel"));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        deconLabel->setFont(font3);

        horizontalLayout_32->addWidget(deconLabel);

        horizontalSpacer_7 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_7);

        overwriteDataLabel = new QLabel(horizontalLayoutWidget_5);
        overwriteDataLabel->setObjectName(QString::fromUtf8("overwriteDataLabel"));
        overwriteDataLabel->setFont(font3);

        horizontalLayout_32->addWidget(overwriteDataLabel);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_4);

        save16BitLabel = new QLabel(horizontalLayoutWidget_5);
        save16BitLabel->setObjectName(QString::fromUtf8("save16BitLabel"));
        save16BitLabel->setFont(font3);

        horizontalLayout_32->addWidget(save16BitLabel);

        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_5);

        onlyFirstTPLabel = new QLabel(horizontalLayoutWidget_5);
        onlyFirstTPLabel->setObjectName(QString::fromUtf8("onlyFirstTPLabel"));
        onlyFirstTPLabel->setFont(font3);

        horizontalLayout_32->addWidget(onlyFirstTPLabel);

        horizontalSpacer_6 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_6);

        tabWidget->addTab(Main, QString());
        DSR = new QWidget();
        DSR->setObjectName(QString::fromUtf8("DSR"));
        dsrSettingsLabel = new QLabel(DSR);
        dsrSettingsLabel->setObjectName(QString::fromUtf8("dsrSettingsLabel"));
        dsrSettingsLabel->setGeometry(QRect(190, 20, 471, 71));
        QFont font4;
        font4.setPointSize(24);
        dsrSettingsLabel->setFont(font4);
        dsrAdvancedSettingsButton = new QPushButton(DSR);
        dsrAdvancedSettingsButton->setObjectName(QString::fromUtf8("dsrAdvancedSettingsButton"));
        dsrAdvancedSettingsButton->setGeometry(QRect(620, 10, 161, 23));
        dsrNextButton = new QPushButton(DSR);
        dsrNextButton->setObjectName(QString::fromUtf8("dsrNextButton"));
        dsrNextButton->setGeometry(QRect(440, 420, 111, 61));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setWeight(75);
        dsrNextButton->setFont(font5);
        dsrPreviousButton = new QPushButton(DSR);
        dsrPreviousButton->setObjectName(QString::fromUtf8("dsrPreviousButton"));
        dsrPreviousButton->setGeometry(QRect(240, 420, 111, 61));
        dsrPreviousButton->setFont(font5);
        layoutWidget_6 = new QWidget(DSR);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(270, 240, 273, 25));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        backgroundPathsLabel = new QLabel(layoutWidget_6);
        backgroundPathsLabel->setObjectName(QString::fromUtf8("backgroundPathsLabel"));
        backgroundPathsLabel->setEnabled(false);
        backgroundPathsLabel->setFont(font5);

        horizontalLayout_7->addWidget(backgroundPathsLabel);

        backgroundAddPathsButton = new QPushButton(layoutWidget_6);
        backgroundAddPathsButton->setObjectName(QString::fromUtf8("backgroundAddPathsButton"));
        backgroundAddPathsButton->setEnabled(false);

        horizontalLayout_7->addWidget(backgroundAddPathsButton);

        layoutWidget_7 = new QWidget(DSR);
        layoutWidget_7->setObjectName(QString::fromUtf8("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(280, 210, 249, 25));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        lsImagePathsLabel = new QLabel(layoutWidget_7);
        lsImagePathsLabel->setObjectName(QString::fromUtf8("lsImagePathsLabel"));
        lsImagePathsLabel->setEnabled(false);
        lsImagePathsLabel->setFont(font5);

        horizontalLayout_8->addWidget(lsImagePathsLabel);

        lsImageAddPathsButton = new QPushButton(layoutWidget_7);
        lsImageAddPathsButton->setObjectName(QString::fromUtf8("lsImageAddPathsButton"));
        lsImageAddPathsButton->setEnabled(false);

        horizontalLayout_8->addWidget(lsImageAddPathsButton);

        layoutWidget3 = new QWidget(DSR);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(300, 100, 187, 21));
        horizontalLayout_18 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        parseSettingsFileLabel = new QLabel(layoutWidget3);
        parseSettingsFileLabel->setObjectName(QString::fromUtf8("parseSettingsFileLabel"));
        parseSettingsFileLabel->setFont(font5);

        horizontalLayout_18->addWidget(parseSettingsFileLabel);

        parseSettingsFileCheckBox = new QCheckBox(layoutWidget3);
        parseSettingsFileCheckBox->setObjectName(QString::fromUtf8("parseSettingsFileCheckBox"));
        parseSettingsFileCheckBox->setAutoFillBackground(false);

        horizontalLayout_18->addWidget(parseSettingsFileCheckBox);

        layoutWidget4 = new QWidget(DSR);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(330, 140, 129, 21));
        horizontalLayout_19 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        flipZStackLabel = new QLabel(layoutWidget4);
        flipZStackLabel->setObjectName(QString::fromUtf8("flipZStackLabel"));
        flipZStackLabel->setFont(font5);

        horizontalLayout_19->addWidget(flipZStackLabel);

        flipZStackCheckBox = new QCheckBox(layoutWidget4);
        flipZStackCheckBox->setObjectName(QString::fromUtf8("flipZStackCheckBox"));
        flipZStackCheckBox->setAutoFillBackground(false);

        horizontalLayout_19->addWidget(flipZStackCheckBox);

        layoutWidget5 = new QWidget(DSR);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(310, 180, 165, 21));
        horizontalLayout_21 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(0, 0, 0, 0);
        llffCorrectionLabel = new QLabel(layoutWidget5);
        llffCorrectionLabel->setObjectName(QString::fromUtf8("llffCorrectionLabel"));
        llffCorrectionLabel->setFont(font5);

        horizontalLayout_21->addWidget(llffCorrectionLabel);

        llffCorrectionCheckBox = new QCheckBox(layoutWidget5);
        llffCorrectionCheckBox->setObjectName(QString::fromUtf8("llffCorrectionCheckBox"));
        llffCorrectionCheckBox->setAutoFillBackground(false);

        horizontalLayout_21->addWidget(llffCorrectionCheckBox);

        tabWidget->addTab(DSR, QString());
        Stitch = new QWidget();
        Stitch->setObjectName(QString::fromUtf8("Stitch"));
        stitchSettingsLabel = new QLabel(Stitch);
        stitchSettingsLabel->setObjectName(QString::fromUtf8("stitchSettingsLabel"));
        stitchSettingsLabel->setGeometry(QRect(280, 10, 251, 71));
        stitchSettingsLabel->setFont(font4);
        stitchPreviousButton = new QPushButton(Stitch);
        stitchPreviousButton->setObjectName(QString::fromUtf8("stitchPreviousButton"));
        stitchPreviousButton->setGeometry(QRect(240, 420, 111, 61));
        stitchPreviousButton->setFont(font5);
        stitchNextButton = new QPushButton(Stitch);
        stitchNextButton->setObjectName(QString::fromUtf8("stitchNextButton"));
        stitchNextButton->setGeometry(QRect(440, 420, 111, 61));
        stitchNextButton->setFont(font5);
        layoutWidget_4 = new QWidget(Stitch);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(430, 190, 167, 21));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        boundBoxCropLabel = new QLabel(layoutWidget_4);
        boundBoxCropLabel->setObjectName(QString::fromUtf8("boundBoxCropLabel"));
        boundBoxCropLabel->setFont(font5);

        horizontalLayout_2->addWidget(boundBoxCropLabel);

        boundBoxCheckBox = new QCheckBox(layoutWidget_4);
        boundBoxCheckBox->setObjectName(QString::fromUtf8("boundBoxCheckBox"));

        horizontalLayout_2->addWidget(boundBoxCheckBox);

        layoutWidget_5 = new QWidget(Stitch);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 320, 221, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        primaryCHLabel = new QLabel(layoutWidget_5);
        primaryCHLabel->setObjectName(QString::fromUtf8("primaryCHLabel"));
        primaryCHLabel->setEnabled(true);
        primaryCHLabel->setFont(font5);

        horizontalLayout_5->addWidget(primaryCHLabel);

        primaryCHLineEdit = new QLineEdit(layoutWidget_5);
        primaryCHLineEdit->setObjectName(QString::fromUtf8("primaryCHLineEdit"));
        primaryCHLineEdit->setEnabled(true);
        primaryCHLineEdit->setMaxLength(32763);
        primaryCHLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(primaryCHLineEdit);

        layoutWidget_11 = new QWidget(Stitch);
        layoutWidget_11->setObjectName(QString::fromUtf8("layoutWidget_11"));
        layoutWidget_11->setGeometry(QRect(560, 230, 111, 26));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        boundBoxXMinLabel = new QLabel(layoutWidget_11);
        boundBoxXMinLabel->setObjectName(QString::fromUtf8("boundBoxXMinLabel"));
        boundBoxXMinLabel->setEnabled(false);
        boundBoxXMinLabel->setFont(font5);

        horizontalLayout_10->addWidget(boundBoxXMinLabel);

        boundBoxXMinSpinBox = new QSpinBox(layoutWidget_11);
        boundBoxXMinSpinBox->setObjectName(QString::fromUtf8("boundBoxXMinSpinBox"));
        boundBoxXMinSpinBox->setEnabled(false);

        horizontalLayout_10->addWidget(boundBoxXMinSpinBox);

        layoutWidget_12 = new QWidget(Stitch);
        layoutWidget_12->setObjectName(QString::fromUtf8("layoutWidget_12"));
        layoutWidget_12->setGeometry(QRect(680, 230, 111, 26));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_12);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        boundBoxZMinLabel = new QLabel(layoutWidget_12);
        boundBoxZMinLabel->setObjectName(QString::fromUtf8("boundBoxZMinLabel"));
        boundBoxZMinLabel->setEnabled(false);
        boundBoxZMinLabel->setFont(font5);

        horizontalLayout_11->addWidget(boundBoxZMinLabel);

        boundBoxZMinSpinBox = new QSpinBox(layoutWidget_12);
        boundBoxZMinSpinBox->setObjectName(QString::fromUtf8("boundBoxZMinSpinBox"));
        boundBoxZMinSpinBox->setEnabled(false);

        horizontalLayout_11->addWidget(boundBoxZMinSpinBox);

        layoutWidget_13 = new QWidget(Stitch);
        layoutWidget_13->setObjectName(QString::fromUtf8("layoutWidget_13"));
        layoutWidget_13->setGeometry(QRect(430, 270, 121, 26));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget_13);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        boundBoxYMaxLabel = new QLabel(layoutWidget_13);
        boundBoxYMaxLabel->setObjectName(QString::fromUtf8("boundBoxYMaxLabel"));
        boundBoxYMaxLabel->setEnabled(false);
        boundBoxYMaxLabel->setFont(font5);

        horizontalLayout_12->addWidget(boundBoxYMaxLabel);

        boundBoxYMaxSpinBox = new QSpinBox(layoutWidget_13);
        boundBoxYMaxSpinBox->setObjectName(QString::fromUtf8("boundBoxYMaxSpinBox"));
        boundBoxYMaxSpinBox->setEnabled(false);

        horizontalLayout_12->addWidget(boundBoxYMaxSpinBox);

        layoutWidget_14 = new QWidget(Stitch);
        layoutWidget_14->setObjectName(QString::fromUtf8("layoutWidget_14"));
        layoutWidget_14->setGeometry(QRect(560, 270, 113, 26));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget_14);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        boundBoxXMaxLabel = new QLabel(layoutWidget_14);
        boundBoxXMaxLabel->setObjectName(QString::fromUtf8("boundBoxXMaxLabel"));
        boundBoxXMaxLabel->setEnabled(false);
        boundBoxXMaxLabel->setFont(font5);

        horizontalLayout_13->addWidget(boundBoxXMaxLabel);

        boundBoxXMaxSpinBox = new QSpinBox(layoutWidget_14);
        boundBoxXMaxSpinBox->setObjectName(QString::fromUtf8("boundBoxXMaxSpinBox"));
        boundBoxXMaxSpinBox->setEnabled(false);

        horizontalLayout_13->addWidget(boundBoxXMaxSpinBox);

        layoutWidget_15 = new QWidget(Stitch);
        layoutWidget_15->setObjectName(QString::fromUtf8("layoutWidget_15"));
        layoutWidget_15->setGeometry(QRect(680, 270, 112, 26));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget_15);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        boundBoxZMaxLabel = new QLabel(layoutWidget_15);
        boundBoxZMaxLabel->setObjectName(QString::fromUtf8("boundBoxZMaxLabel"));
        boundBoxZMaxLabel->setEnabled(false);
        boundBoxZMaxLabel->setFont(font5);

        horizontalLayout_14->addWidget(boundBoxZMaxLabel);

        boundBoxZMaxSpinBox = new QSpinBox(layoutWidget_15);
        boundBoxZMaxSpinBox->setObjectName(QString::fromUtf8("boundBoxZMaxSpinBox"));
        boundBoxZMaxSpinBox->setEnabled(false);

        horizontalLayout_14->addWidget(boundBoxZMaxSpinBox);

        layoutWidget6 = new QWidget(Stitch);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(20, 140, 311, 31));
        horizontalLayout_23 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        resultsDirLabel = new QLabel(layoutWidget6);
        resultsDirLabel->setObjectName(QString::fromUtf8("resultsDirLabel"));
        resultsDirLabel->setFont(font5);

        horizontalLayout_23->addWidget(resultsDirLabel);

        resultsDirLineEdit = new QLineEdit(layoutWidget6);
        resultsDirLineEdit->setObjectName(QString::fromUtf8("resultsDirLineEdit"));
        resultsDirLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_23->addWidget(resultsDirLineEdit);

        resultsDirBrowseButton = new QPushButton(layoutWidget6);
        resultsDirBrowseButton->setObjectName(QString::fromUtf8("resultsDirBrowseButton"));

        horizontalLayout_23->addWidget(resultsDirBrowseButton);

        layoutWidget7 = new QWidget(Stitch);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(20, 190, 401, 25));
        horizontalLayout_24 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(0, 0, 0, 0);
        imageListFullPathsLabel = new QLabel(layoutWidget7);
        imageListFullPathsLabel->setObjectName(QString::fromUtf8("imageListFullPathsLabel"));
        imageListFullPathsLabel->setFont(font5);

        horizontalLayout_24->addWidget(imageListFullPathsLabel);

        imageListFullPathsLineEdit = new QLineEdit(layoutWidget7);
        imageListFullPathsLineEdit->setObjectName(QString::fromUtf8("imageListFullPathsLineEdit"));
        imageListFullPathsLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_24->addWidget(imageListFullPathsLineEdit);

        imageListFullPathsBrowseButton = new QPushButton(layoutWidget7);
        imageListFullPathsBrowseButton->setObjectName(QString::fromUtf8("imageListFullPathsBrowseButton"));

        horizontalLayout_24->addWidget(imageListFullPathsBrowseButton);

        layoutWidget8 = new QWidget(Stitch);
        layoutWidget8->setObjectName(QString::fromUtf8("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(20, 230, 251, 25));
        horizontalLayout_25 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(0, 0, 0, 0);
        axisOrderLabel = new QLabel(layoutWidget8);
        axisOrderLabel->setObjectName(QString::fromUtf8("axisOrderLabel"));
        axisOrderLabel->setFont(font5);

        horizontalLayout_25->addWidget(axisOrderLabel);

        axisOrderLineEdit = new QLineEdit(layoutWidget8);
        axisOrderLineEdit->setObjectName(QString::fromUtf8("axisOrderLineEdit"));
        axisOrderLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_25->addWidget(axisOrderLineEdit);

        layoutWidget9 = new QWidget(Stitch);
        layoutWidget9->setObjectName(QString::fromUtf8("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(20, 270, 231, 29));
        horizontalLayout_26 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(0, 0, 0, 0);
        blendMethodLabel = new QLabel(layoutWidget9);
        blendMethodLabel->setObjectName(QString::fromUtf8("blendMethodLabel"));
        blendMethodLabel->setFont(font5);

        horizontalLayout_26->addWidget(blendMethodLabel);

        blendMethodComboBox = new QComboBox(layoutWidget9);
        blendMethodComboBox->addItem(QString());
        blendMethodComboBox->addItem(QString());
        blendMethodComboBox->addItem(QString());
        blendMethodComboBox->addItem(QString());
        blendMethodComboBox->addItem(QString());
        blendMethodComboBox->setObjectName(QString::fromUtf8("blendMethodComboBox"));
        blendMethodComboBox->setFont(font5);
        blendMethodComboBox->setEditable(false);

        horizontalLayout_26->addWidget(blendMethodComboBox);

        layoutWidget10 = new QWidget(Stitch);
        layoutWidget10->setObjectName(QString::fromUtf8("layoutWidget10"));
        layoutWidget10->setGeometry(QRect(430, 90, 127, 31));
        horizontalLayout_27 = new QHBoxLayout(layoutWidget10);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(0, 0, 0, 0);
        xCorrShiftLabel = new QLabel(layoutWidget10);
        xCorrShiftLabel->setObjectName(QString::fromUtf8("xCorrShiftLabel"));
        xCorrShiftLabel->setFont(font5);

        horizontalLayout_27->addWidget(xCorrShiftLabel);

        xCorrShiftCheckBox = new QCheckBox(layoutWidget10);
        xCorrShiftCheckBox->setObjectName(QString::fromUtf8("xCorrShiftCheckBox"));

        horizontalLayout_27->addWidget(xCorrShiftCheckBox);

        layoutWidget11 = new QWidget(Stitch);
        layoutWidget11->setObjectName(QString::fromUtf8("layoutWidget11"));
        layoutWidget11->setGeometry(QRect(430, 140, 261, 31));
        horizontalLayout_28 = new QHBoxLayout(layoutWidget11);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(0, 0, 0, 0);
        xCorrModeLabel = new QLabel(layoutWidget11);
        xCorrModeLabel->setObjectName(QString::fromUtf8("xCorrModeLabel"));
        xCorrModeLabel->setFont(font5);

        horizontalLayout_28->addWidget(xCorrModeLabel);

        xCorrModeComboBox = new QComboBox(layoutWidget11);
        xCorrModeComboBox->addItem(QString());
        xCorrModeComboBox->addItem(QString());
        xCorrModeComboBox->addItem(QString());
        xCorrModeComboBox->setObjectName(QString::fromUtf8("xCorrModeComboBox"));
        xCorrModeComboBox->setFont(font5);
        xCorrModeComboBox->setEditable(false);

        horizontalLayout_28->addWidget(xCorrModeComboBox);

        layoutWidget12 = new QWidget(Stitch);
        layoutWidget12->setObjectName(QString::fromUtf8("layoutWidget12"));
        layoutWidget12->setGeometry(QRect(20, 90, 232, 29));
        horizontalLayout_22 = new QHBoxLayout(layoutWidget12);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        stitchPipelineLabel = new QLabel(layoutWidget12);
        stitchPipelineLabel->setObjectName(QString::fromUtf8("stitchPipelineLabel"));
        stitchPipelineLabel->setFont(font5);

        horizontalLayout_22->addWidget(stitchPipelineLabel);

        stitchPipelineComboBox = new QComboBox(layoutWidget12);
        stitchPipelineComboBox->addItem(QString());
        stitchPipelineComboBox->addItem(QString());
        stitchPipelineComboBox->setObjectName(QString::fromUtf8("stitchPipelineComboBox"));
        stitchPipelineComboBox->setFont(font5);
        stitchPipelineComboBox->setEditable(false);

        horizontalLayout_22->addWidget(stitchPipelineComboBox);

        layoutWidget13 = new QWidget(Stitch);
        layoutWidget13->setObjectName(QString::fromUtf8("layoutWidget13"));
        layoutWidget13->setGeometry(QRect(430, 230, 121, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget13);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        boundBoxYMinLabel = new QLabel(layoutWidget13);
        boundBoxYMinLabel->setObjectName(QString::fromUtf8("boundBoxYMinLabel"));
        boundBoxYMinLabel->setEnabled(false);
        boundBoxYMinLabel->setFont(font5);

        horizontalLayout->addWidget(boundBoxYMinLabel);

        boundBoxYMinSpinBox = new QSpinBox(layoutWidget13);
        boundBoxYMinSpinBox->setObjectName(QString::fromUtf8("boundBoxYMinSpinBox"));
        boundBoxYMinSpinBox->setEnabled(false);

        horizontalLayout->addWidget(boundBoxYMinSpinBox);

        tabWidget->addTab(Stitch, QString());
        Decon = new QWidget();
        Decon->setObjectName(QString::fromUtf8("Decon"));
        deconSettingsLabel = new QLabel(Decon);
        deconSettingsLabel->setObjectName(QString::fromUtf8("deconSettingsLabel"));
        deconSettingsLabel->setGeometry(QRect(280, 10, 261, 71));
        deconSettingsLabel->setFont(font4);
        deconAdvancedSettingsButton = new QPushButton(Decon);
        deconAdvancedSettingsButton->setObjectName(QString::fromUtf8("deconAdvancedSettingsButton"));
        deconAdvancedSettingsButton->setGeometry(QRect(610, 10, 171, 23));
        deconPreviousButton = new QPushButton(Decon);
        deconPreviousButton->setObjectName(QString::fromUtf8("deconPreviousButton"));
        deconPreviousButton->setGeometry(QRect(240, 420, 111, 61));
        deconPreviousButton->setFont(font5);
        deconNextButton = new QPushButton(Decon);
        deconNextButton->setObjectName(QString::fromUtf8("deconNextButton"));
        deconNextButton->setGeometry(QRect(440, 420, 111, 61));
        deconNextButton->setFont(font5);
        layoutWidget_10 = new QWidget(Decon);
        layoutWidget_10->setObjectName(QString::fromUtf8("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(90, 180, 157, 21));
        horizontalLayout_31 = new QHBoxLayout(layoutWidget_10);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        horizontalLayout_31->setContentsMargins(0, 0, 0, 0);
        matlabDeconLabel = new QLabel(layoutWidget_10);
        matlabDeconLabel->setObjectName(QString::fromUtf8("matlabDeconLabel"));
        matlabDeconLabel->setFont(font5);

        horizontalLayout_31->addWidget(matlabDeconLabel);

        matlabDeconRadioButton = new QRadioButton(layoutWidget_10);
        deconTypeButtonGroup = new QButtonGroup(MainWindow);
        deconTypeButtonGroup->setObjectName(QString::fromUtf8("deconTypeButtonGroup"));
        deconTypeButtonGroup->addButton(matlabDeconRadioButton);
        matlabDeconRadioButton->setObjectName(QString::fromUtf8("matlabDeconRadioButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(matlabDeconRadioButton->sizePolicy().hasHeightForWidth());
        matlabDeconRadioButton->setSizePolicy(sizePolicy1);
        matlabDeconRadioButton->setAutoFillBackground(false);

        horizontalLayout_31->addWidget(matlabDeconRadioButton);

        layoutWidget14 = new QWidget(Decon);
        layoutWidget14->setObjectName(QString::fromUtf8("layoutWidget14"));
        layoutWidget14->setGeometry(QRect(91, 120, 151, 21));
        horizontalLayout_29 = new QHBoxLayout(layoutWidget14);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(0, 0, 0, 0);
        cudaDeconLabel = new QLabel(layoutWidget14);
        cudaDeconLabel->setObjectName(QString::fromUtf8("cudaDeconLabel"));
        cudaDeconLabel->setFont(font5);

        horizontalLayout_29->addWidget(cudaDeconLabel);

        cudaDeconRadioButton = new QRadioButton(layoutWidget14);
        deconTypeButtonGroup->addButton(cudaDeconRadioButton);
        cudaDeconRadioButton->setObjectName(QString::fromUtf8("cudaDeconRadioButton"));
        sizePolicy1.setHeightForWidth(cudaDeconRadioButton->sizePolicy().hasHeightForWidth());
        cudaDeconRadioButton->setSizePolicy(sizePolicy1);
        cudaDeconRadioButton->setAutoFillBackground(false);

        horizontalLayout_29->addWidget(cudaDeconRadioButton);

        layoutWidget15 = new QWidget(Decon);
        layoutWidget15->setObjectName(QString::fromUtf8("layoutWidget15"));
        layoutWidget15->setGeometry(QRect(90, 150, 151, 21));
        horizontalLayout_30 = new QHBoxLayout(layoutWidget15);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(0, 0, 0, 0);
        cppDeconLabel = new QLabel(layoutWidget15);
        cppDeconLabel->setObjectName(QString::fromUtf8("cppDeconLabel"));
        cppDeconLabel->setFont(font5);

        horizontalLayout_30->addWidget(cppDeconLabel);

        cppDeconRadioButton = new QRadioButton(layoutWidget15);
        deconTypeButtonGroup->addButton(cppDeconRadioButton);
        cppDeconRadioButton->setObjectName(QString::fromUtf8("cppDeconRadioButton"));
        sizePolicy1.setHeightForWidth(cppDeconRadioButton->sizePolicy().hasHeightForWidth());
        cppDeconRadioButton->setSizePolicy(sizePolicy1);
        cppDeconRadioButton->setAutoFillBackground(false);

        horizontalLayout_30->addWidget(cppDeconRadioButton);

        layoutWidget16 = new QWidget(Decon);
        layoutWidget16->setObjectName(QString::fromUtf8("layoutWidget16"));
        layoutWidget16->setGeometry(QRect(90, 210, 241, 25));
        horizontalLayout_33 = new QHBoxLayout(layoutWidget16);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_33->setContentsMargins(0, 0, 0, 0);
        backgroundIntensityLabel = new QLabel(layoutWidget16);
        backgroundIntensityLabel->setObjectName(QString::fromUtf8("backgroundIntensityLabel"));
        backgroundIntensityLabel->setFont(font5);

        horizontalLayout_33->addWidget(backgroundIntensityLabel);

        backgroundIntensityLineEdit = new QLineEdit(layoutWidget16);
        backgroundIntensityLineEdit->setObjectName(QString::fromUtf8("backgroundIntensityLineEdit"));
        backgroundIntensityLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_33->addWidget(backgroundIntensityLineEdit);

        layoutWidget17 = new QWidget(Decon);
        layoutWidget17->setObjectName(QString::fromUtf8("layoutWidget17"));
        layoutWidget17->setGeometry(QRect(90, 240, 181, 25));
        horizontalLayout_34 = new QHBoxLayout(layoutWidget17);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(0, 0, 0, 0);
        dzPSFLabel = new QLabel(layoutWidget17);
        dzPSFLabel->setObjectName(QString::fromUtf8("dzPSFLabel"));
        dzPSFLabel->setFont(font5);

        horizontalLayout_34->addWidget(dzPSFLabel);

        dzPSFLineEdit = new QLineEdit(layoutWidget17);
        dzPSFLineEdit->setObjectName(QString::fromUtf8("dzPSFLineEdit"));
        dzPSFLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_34->addWidget(dzPSFLineEdit);

        layoutWidget18 = new QWidget(Decon);
        layoutWidget18->setObjectName(QString::fromUtf8("layoutWidget18"));
        layoutWidget18->setGeometry(QRect(410, 177, 144, 21));
        horizontalLayout_37 = new QHBoxLayout(layoutWidget18);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalLayout_37->setContentsMargins(0, 0, 0, 0);
        deconRotateLabel = new QLabel(layoutWidget18);
        deconRotateLabel->setObjectName(QString::fromUtf8("deconRotateLabel"));
        deconRotateLabel->setFont(font5);

        horizontalLayout_37->addWidget(deconRotateLabel);

        deconRotateCheckBox = new QCheckBox(layoutWidget18);
        deconRotateCheckBox->setObjectName(QString::fromUtf8("deconRotateCheckBox"));
        deconRotateCheckBox->setAutoFillBackground(false);

        horizontalLayout_37->addWidget(deconRotateCheckBox);

        layoutWidget19 = new QWidget(Decon);
        layoutWidget19->setObjectName(QString::fromUtf8("layoutWidget19"));
        layoutWidget19->setGeometry(QRect(410, 204, 238, 25));
        horizontalLayout_38 = new QHBoxLayout(layoutWidget19);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        horizontalLayout_38->setContentsMargins(0, 0, 0, 0);
        psfFullPathsLabel = new QLabel(layoutWidget19);
        psfFullPathsLabel->setObjectName(QString::fromUtf8("psfFullPathsLabel"));
        psfFullPathsLabel->setFont(font5);

        horizontalLayout_38->addWidget(psfFullPathsLabel);

        psfFullAddPathsButton_2 = new QPushButton(layoutWidget19);
        psfFullAddPathsButton_2->setObjectName(QString::fromUtf8("psfFullAddPathsButton_2"));

        horizontalLayout_38->addWidget(psfFullAddPathsButton_2);

        layoutWidget20 = new QWidget(Decon);
        layoutWidget20->setObjectName(QString::fromUtf8("layoutWidget20"));
        layoutWidget20->setGeometry(QRect(410, 232, 202, 25));
        horizontalLayout_39 = new QHBoxLayout(layoutWidget20);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        horizontalLayout_39->setContentsMargins(0, 0, 0, 0);
        deconIterationsLabel = new QLabel(layoutWidget20);
        deconIterationsLabel->setObjectName(QString::fromUtf8("deconIterationsLabel"));
        deconIterationsLabel->setFont(font5);

        horizontalLayout_39->addWidget(deconIterationsLabel);

        deconIterationsLineEdit = new QLineEdit(layoutWidget20);
        deconIterationsLineEdit->setObjectName(QString::fromUtf8("deconIterationsLineEdit"));
        deconIterationsLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_39->addWidget(deconIterationsLineEdit);

        layoutWidget21 = new QWidget(Decon);
        layoutWidget21->setObjectName(QString::fromUtf8("layoutWidget21"));
        layoutWidget21->setGeometry(QRect(410, 260, 122, 21));
        horizontalLayout_40 = new QHBoxLayout(layoutWidget21);
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        horizontalLayout_40->setContentsMargins(0, 0, 0, 0);
        rotatePSFLabel = new QLabel(layoutWidget21);
        rotatePSFLabel->setObjectName(QString::fromUtf8("rotatePSFLabel"));
        rotatePSFLabel->setFont(font5);

        horizontalLayout_40->addWidget(rotatePSFLabel);

        rotatePSFCheckBox = new QCheckBox(layoutWidget21);
        rotatePSFCheckBox->setObjectName(QString::fromUtf8("rotatePSFCheckBox"));
        rotatePSFCheckBox->setAutoFillBackground(false);

        horizontalLayout_40->addWidget(rotatePSFCheckBox);

        layoutWidget22 = new QWidget(Decon);
        layoutWidget22->setObjectName(QString::fromUtf8("layoutWidget22"));
        layoutWidget22->setGeometry(QRect(410, 122, 171, 25));
        horizontalLayout_35 = new QHBoxLayout(layoutWidget22);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        horizontalLayout_35->setContentsMargins(0, 0, 0, 0);
        edgeErosionLabel = new QLabel(layoutWidget22);
        edgeErosionLabel->setObjectName(QString::fromUtf8("edgeErosionLabel"));
        edgeErosionLabel->setFont(font5);

        horizontalLayout_35->addWidget(edgeErosionLabel);

        edgeErosionLineEdit = new QLineEdit(layoutWidget22);
        edgeErosionLineEdit->setObjectName(QString::fromUtf8("edgeErosionLineEdit"));
        edgeErosionLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_35->addWidget(edgeErosionLineEdit);

        layoutWidget23 = new QWidget(Decon);
        layoutWidget23->setObjectName(QString::fromUtf8("layoutWidget23"));
        layoutWidget23->setGeometry(QRect(410, 150, 142, 21));
        horizontalLayout_36 = new QHBoxLayout(layoutWidget23);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        horizontalLayout_36->setContentsMargins(0, 0, 0, 0);
        erodeByFTPLabel = new QLabel(layoutWidget23);
        erodeByFTPLabel->setObjectName(QString::fromUtf8("erodeByFTPLabel"));
        erodeByFTPLabel->setFont(font5);

        horizontalLayout_36->addWidget(erodeByFTPLabel);

        erodeByFTPCheckBox = new QCheckBox(layoutWidget23);
        erodeByFTPCheckBox->setObjectName(QString::fromUtf8("erodeByFTPCheckBox"));
        erodeByFTPCheckBox->setAutoFillBackground(false);

        horizontalLayout_36->addWidget(erodeByFTPCheckBox);

        tabWidget->addTab(Decon, QString());
        Job = new QWidget();
        Job->setObjectName(QString::fromUtf8("Job"));
        jobSettingsLabel = new QLabel(Job);
        jobSettingsLabel->setObjectName(QString::fromUtf8("jobSettingsLabel"));
        jobSettingsLabel->setGeometry(QRect(310, 0, 201, 71));
        jobSettingsLabel->setFont(font4);
        jobAdvancedSettingsButton = new QPushButton(Job);
        jobAdvancedSettingsButton->setObjectName(QString::fromUtf8("jobAdvancedSettingsButton"));
        jobAdvancedSettingsButton->setGeometry(QRect(630, 10, 151, 23));
        submitButton = new QPushButton(Job);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(440, 420, 111, 61));
        submitButton->setFont(font5);
        jobPreviousButton = new QPushButton(Job);
        jobPreviousButton->setObjectName(QString::fromUtf8("jobPreviousButton"));
        jobPreviousButton->setGeometry(QRect(240, 420, 111, 61));
        jobPreviousButton->setFont(font5);
        maxCPUs = new QLabel(Job);
        maxCPUs->setObjectName(QString::fromUtf8("maxCPUs"));
        maxCPUs->setEnabled(true);
        maxCPUs->setGeometry(QRect(510, 160, 151, 61));
        maxCPUs->setFont(font5);
        layoutWidget24 = new QWidget(Job);
        layoutWidget24->setObjectName(QString::fromUtf8("layoutWidget24"));
        layoutWidget24->setGeometry(QRect(310, 110, 191, 161));
        verticalLayout_4 = new QVBoxLayout(layoutWidget24);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        parseClusterLabel = new QLabel(layoutWidget24);
        parseClusterLabel->setObjectName(QString::fromUtf8("parseClusterLabel"));
        parseClusterLabel->setFont(font5);

        horizontalLayout_41->addWidget(parseClusterLabel);

        parseClusterCheckBox = new QCheckBox(layoutWidget24);
        parseClusterCheckBox->setObjectName(QString::fromUtf8("parseClusterCheckBox"));
        parseClusterCheckBox->setAutoFillBackground(false);
        parseClusterCheckBox->setChecked(false);

        horizontalLayout_41->addWidget(parseClusterCheckBox);


        verticalLayout_4->addLayout(horizontalLayout_41);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        cpusPerTaskLabel = new QLabel(layoutWidget24);
        cpusPerTaskLabel->setObjectName(QString::fromUtf8("cpusPerTaskLabel"));
        cpusPerTaskLabel->setFont(font5);

        horizontalLayout_42->addWidget(cpusPerTaskLabel);

        cpusPerTaskLineEdit = new QLineEdit(layoutWidget24);
        cpusPerTaskLineEdit->setObjectName(QString::fromUtf8("cpusPerTaskLineEdit"));
        cpusPerTaskLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_42->addWidget(cpusPerTaskLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_42);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        cpuOnlyNodesLabel = new QLabel(layoutWidget24);
        cpuOnlyNodesLabel->setObjectName(QString::fromUtf8("cpuOnlyNodesLabel"));
        cpuOnlyNodesLabel->setFont(font5);

        horizontalLayout_43->addWidget(cpuOnlyNodesLabel);

        cpuOnlyNodesCheckBox = new QCheckBox(layoutWidget24);
        cpuOnlyNodesCheckBox->setObjectName(QString::fromUtf8("cpuOnlyNodesCheckBox"));
        cpuOnlyNodesCheckBox->setAutoFillBackground(false);

        horizontalLayout_43->addWidget(cpuOnlyNodesCheckBox);


        verticalLayout_4->addLayout(horizontalLayout_43);

        tabWidget->addTab(Job, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 801, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        mainSettingsLabel->setText(QCoreApplication::translate("MainWindow", "Main Settings", nullptr));
        dataPathsLabel->setText(QCoreApplication::translate("MainWindow", "Data Paths", nullptr));
        mainAdvancedSettingsButton->setText(QCoreApplication::translate("MainWindow", "Main Advanced Settings", nullptr));
        dzLabel->setText(QCoreApplication::translate("MainWindow", "Step Size", nullptr));
        dzLineEdit->setText(QCoreApplication::translate("MainWindow", ".5", nullptr));
        mainNextButton->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        objectiveScanLabel->setText(QCoreApplication::translate("MainWindow", "Objective Scan", nullptr));
        objectiveScanCheckBox->setText(QString());
        addPathsButton->setText(QCoreApplication::translate("MainWindow", "Add/View Paths", nullptr));
        streamingLabel->setText(QCoreApplication::translate("MainWindow", "Real-time Processing", nullptr));
        streamingCheckBox->setText(QString());
        channelPatternsLabel->setText(QCoreApplication::translate("MainWindow", "Channel Patterns", nullptr));
        deskewLabel->setText(QCoreApplication::translate("MainWindow", "Deskew", nullptr));
        deskewCheckBox->setText(QString());
        deskewDeconCheckBox->setText(QString());
        deskewOverwriteDataCheckBox->setText(QString());
        deskewSave16BitCheckBox->setText(QString());
        deskewOnlyFirstTPCheckBox->setText(QString());
        rotateLabel->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        rotateCheckBox->setText(QString());
        rotateDeconCheckBox->setText(QString());
        rotateOverwriteDataCheckBox->setText(QString());
        rotateSave16BitCheckBox->setText(QString());
        rotateOnlyFirstTPCheckBox->setText(QString());
        deskewAndRotateLabel->setText(QCoreApplication::translate("MainWindow", "Deskew & Rotate", nullptr));
        deskewAndRotateCheckBox->setText(QString());
        deskewAndRotateDeconCheckBox->setText(QString());
        deskewAndRotateOverwriteDataCheckBox->setText(QString());
        deskewAndRotateSave16BitCheckBox->setText(QString());
        deskewAndRotateOnlyFirstTPCheckBox->setText(QString());
        stitchLabel->setText(QCoreApplication::translate("MainWindow", "Stitch", nullptr));
        stitchCheckBox->setText(QString());
        stitchDeconCheckBox->setText(QString());
        stitchOverwriteDataCheckBox->setText(QString());
        stitchSave16BitCheckBox->setText(QString());
        stitchOnlyFirstTPCheckBox->setText(QString());
        deconLabel->setText(QCoreApplication::translate("MainWindow", "Decon", nullptr));
        overwriteDataLabel->setText(QCoreApplication::translate("MainWindow", "Overwrite Data", nullptr));
        save16BitLabel->setText(QCoreApplication::translate("MainWindow", "Save 16 Bit", nullptr));
        onlyFirstTPLabel->setText(QCoreApplication::translate("MainWindow", "Only First TP", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Main), QCoreApplication::translate("MainWindow", "Main", nullptr));
        dsrSettingsLabel->setText(QCoreApplication::translate("MainWindow", " Deskew and Rotate Settings", nullptr));
        dsrAdvancedSettingsButton->setText(QCoreApplication::translate("MainWindow", "DSR Advanced Settings", nullptr));
        dsrNextButton->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        dsrPreviousButton->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        backgroundPathsLabel->setText(QCoreApplication::translate("MainWindow", "Background Paths", nullptr));
        backgroundAddPathsButton->setText(QCoreApplication::translate("MainWindow", "Add/View Paths", nullptr));
        lsImagePathsLabel->setText(QCoreApplication::translate("MainWindow", "LS Image Paths", nullptr));
        lsImageAddPathsButton->setText(QCoreApplication::translate("MainWindow", "Add/View Paths", nullptr));
        parseSettingsFileLabel->setText(QCoreApplication::translate("MainWindow", "Read Settings File", nullptr));
        parseSettingsFileCheckBox->setText(QString());
        flipZStackLabel->setText(QCoreApplication::translate("MainWindow", "Flip Z Stack", nullptr));
        flipZStackCheckBox->setText(QString());
        llffCorrectionLabel->setText(QCoreApplication::translate("MainWindow", "LLFF Correction", nullptr));
        llffCorrectionCheckBox->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(DSR), QCoreApplication::translate("MainWindow", "DSR", nullptr));
        stitchSettingsLabel->setText(QCoreApplication::translate("MainWindow", " Stitch Settings", nullptr));
        stitchPreviousButton->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        stitchNextButton->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        boundBoxCropLabel->setText(QCoreApplication::translate("MainWindow", "Bound Box Crop", nullptr));
        boundBoxCheckBox->setText(QString());
        primaryCHLabel->setText(QCoreApplication::translate("MainWindow", "Primary Ch", nullptr));
        primaryCHLineEdit->setText(QString());
        primaryCHLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "EX: camA_ch0", nullptr));
        boundBoxXMinLabel->setText(QCoreApplication::translate("MainWindow", "X Min:", nullptr));
        boundBoxZMinLabel->setText(QCoreApplication::translate("MainWindow", "Z Min:", nullptr));
        boundBoxYMaxLabel->setText(QCoreApplication::translate("MainWindow", "Y Max:", nullptr));
        boundBoxXMaxLabel->setText(QCoreApplication::translate("MainWindow", "X Max:", nullptr));
        boundBoxZMaxLabel->setText(QCoreApplication::translate("MainWindow", "Z Max:", nullptr));
        resultsDirLabel->setText(QCoreApplication::translate("MainWindow", "Results Dir", nullptr));
        resultsDirLineEdit->setText(QString());
        resultsDirBrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        imageListFullPathsLabel->setText(QCoreApplication::translate("MainWindow", "Image List Full Paths", nullptr));
        imageListFullPathsBrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        axisOrderLabel->setText(QCoreApplication::translate("MainWindow", "Axis Order", nullptr));
        axisOrderLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "EX: xyz OR -xyz OR yxz etc.", nullptr));
        blendMethodLabel->setText(QCoreApplication::translate("MainWindow", "Blend Method", nullptr));
        blendMethodComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "none", nullptr));
        blendMethodComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "mean", nullptr));
        blendMethodComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "median", nullptr));
        blendMethodComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "max", nullptr));
        blendMethodComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "feather", nullptr));

        blendMethodComboBox->setCurrentText(QCoreApplication::translate("MainWindow", "none", nullptr));
        xCorrShiftLabel->setText(QCoreApplication::translate("MainWindow", "X Corr Shift", nullptr));
        xCorrShiftCheckBox->setText(QString());
        xCorrModeLabel->setText(QCoreApplication::translate("MainWindow", "X Corr Mode", nullptr));
        xCorrModeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "primaryFirst", nullptr));
        xCorrModeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "primary", nullptr));
        xCorrModeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "all", nullptr));

        xCorrModeComboBox->setCurrentText(QCoreApplication::translate("MainWindow", "primaryFirst", nullptr));
        stitchPipelineLabel->setText(QCoreApplication::translate("MainWindow", "Stitch Pipeline", nullptr));
        stitchPipelineComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "matlab", nullptr));
        stitchPipelineComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "zarr", nullptr));

        stitchPipelineComboBox->setCurrentText(QCoreApplication::translate("MainWindow", "matlab", nullptr));
        boundBoxYMinLabel->setText(QCoreApplication::translate("MainWindow", "Y Min:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Stitch), QCoreApplication::translate("MainWindow", "Stitch", nullptr));
        deconSettingsLabel->setText(QCoreApplication::translate("MainWindow", " Decon Settings", nullptr));
        deconAdvancedSettingsButton->setText(QCoreApplication::translate("MainWindow", "Decon Advanced Settings", nullptr));
        deconPreviousButton->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        deconNextButton->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        matlabDeconLabel->setText(QCoreApplication::translate("MainWindow", "MATLAB Decon", nullptr));
        matlabDeconRadioButton->setText(QString());
        cudaDeconLabel->setText(QCoreApplication::translate("MainWindow", "CUDA Decon", nullptr));
        cudaDeconRadioButton->setText(QString());
        cppDeconLabel->setText(QCoreApplication::translate("MainWindow", "CPP Decon", nullptr));
        cppDeconRadioButton->setText(QString());
        backgroundIntensityLabel->setText(QCoreApplication::translate("MainWindow", "Background Intensity", nullptr));
        backgroundIntensityLineEdit->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        dzPSFLabel->setText(QCoreApplication::translate("MainWindow", "PSF Step Size", nullptr));
        dzPSFLineEdit->setText(QCoreApplication::translate("MainWindow", ".1", nullptr));
        deconRotateLabel->setText(QCoreApplication::translate("MainWindow", "Decon Rotate", nullptr));
        deconRotateCheckBox->setText(QString());
        psfFullPathsLabel->setText(QCoreApplication::translate("MainWindow", "PSF Full Paths", nullptr));
        psfFullAddPathsButton_2->setText(QCoreApplication::translate("MainWindow", "Add/View Paths", nullptr));
        deconIterationsLabel->setText(QCoreApplication::translate("MainWindow", "Decon Iterations", nullptr));
        deconIterationsLineEdit->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
        rotatePSFLabel->setText(QCoreApplication::translate("MainWindow", "Rotate PSF", nullptr));
        rotatePSFCheckBox->setText(QString());
        edgeErosionLabel->setText(QCoreApplication::translate("MainWindow", "Edge Erosion", nullptr));
        edgeErosionLineEdit->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        erodeByFTPLabel->setText(QCoreApplication::translate("MainWindow", "Erode By FTP", nullptr));
        erodeByFTPCheckBox->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(Decon), QCoreApplication::translate("MainWindow", "Decon", nullptr));
        jobSettingsLabel->setText(QCoreApplication::translate("MainWindow", "Job Settings", nullptr));
        jobAdvancedSettingsButton->setText(QCoreApplication::translate("MainWindow", "Job Advanced Settings", nullptr));
        submitButton->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        jobPreviousButton->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        maxCPUs->setText(QCoreApplication::translate("MainWindow", "Max Allowed: ", nullptr));
        parseClusterLabel->setText(QCoreApplication::translate("MainWindow", "Parse Cluster", nullptr));
        parseClusterCheckBox->setText(QString());
        cpusPerTaskLabel->setText(QCoreApplication::translate("MainWindow", "CPUs Per Task", nullptr));
        cpusPerTaskLineEdit->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        cpuOnlyNodesLabel->setText(QCoreApplication::translate("MainWindow", "CPU Only Nodes", nullptr));
        cpuOnlyNodesCheckBox->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(Job), QCoreApplication::translate("MainWindow", "Job", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
