/********************************************************************************
** Form generated from reading UI file 'jobadvanced.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOBADVANCED_H
#define UI_JOBADVANCED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jobAdvanced
{
public:
    QLabel *jobAdvancedSettingsLabel;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *largeFileLabel;
    QCheckBox *largeFileCheckBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *uuidLabel;
    QLineEdit *uuidLineEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *maxTrialNumLabel;
    QSpinBox *maxTrialNumSpinBox;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *unitWaitTimeLabel;
    QSpinBox *unitWaitTimeSpinBox;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *jobLogDirLabel;
    QLineEdit *jobLogDirLineEdit;
    QPushButton *jobLogDirBrowseButton;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *minModifyTimeLabel;
    QSpinBox *minModifyTimeSpinBox;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *maxModifyTimeLabel;
    QSpinBox *maxModifyTimeSpinBox;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *maxWaitLoopNumLabel;
    QSpinBox *maxWaitLoopNumSpinBox;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *matlabLaunchStrLabel;
    QLineEdit *matlabLaunchStrLineEdit;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_10;
    QLabel *slurmParamLabel;
    QLineEdit *slurmParamLineEdit;

    void setupUi(QDialog *jobAdvanced)
    {
        if (jobAdvanced->objectName().isEmpty())
            jobAdvanced->setObjectName(QString::fromUtf8("jobAdvanced"));
        jobAdvanced->resize(640, 480);
        jobAdvancedSettingsLabel = new QLabel(jobAdvanced);
        jobAdvancedSettingsLabel->setObjectName(QString::fromUtf8("jobAdvancedSettingsLabel"));
        jobAdvancedSettingsLabel->setGeometry(QRect(160, 10, 361, 71));
        QFont font;
        font.setPointSize(24);
        jobAdvancedSettingsLabel->setFont(font);
        submitButton = new QPushButton(jobAdvanced);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(340, 370, 121, 61));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        submitButton->setFont(font1);
        cancelButton = new QPushButton(jobAdvanced);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(180, 370, 121, 61));
        cancelButton->setFont(font1);
        layoutWidget = new QWidget(jobAdvanced);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 90, 112, 21));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        largeFileLabel = new QLabel(layoutWidget);
        largeFileLabel->setObjectName(QString::fromUtf8("largeFileLabel"));
        largeFileLabel->setFont(font1);

        horizontalLayout->addWidget(largeFileLabel);

        largeFileCheckBox = new QCheckBox(layoutWidget);
        largeFileCheckBox->setObjectName(QString::fromUtf8("largeFileCheckBox"));
        largeFileCheckBox->setAutoFillBackground(false);

        horizontalLayout->addWidget(largeFileCheckBox);

        layoutWidget1 = new QWidget(jobAdvanced);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 150, 140, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        uuidLabel = new QLabel(layoutWidget1);
        uuidLabel->setObjectName(QString::fromUtf8("uuidLabel"));
        uuidLabel->setFont(font1);

        horizontalLayout_2->addWidget(uuidLabel);

        uuidLineEdit = new QLineEdit(layoutWidget1);
        uuidLineEdit->setObjectName(QString::fromUtf8("uuidLineEdit"));

        horizontalLayout_2->addWidget(uuidLineEdit);

        layoutWidget2 = new QWidget(jobAdvanced);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(40, 180, 224, 26));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        maxTrialNumLabel = new QLabel(layoutWidget2);
        maxTrialNumLabel->setObjectName(QString::fromUtf8("maxTrialNumLabel"));
        maxTrialNumLabel->setFont(font1);

        horizontalLayout_3->addWidget(maxTrialNumLabel);

        maxTrialNumSpinBox = new QSpinBox(layoutWidget2);
        maxTrialNumSpinBox->setObjectName(QString::fromUtf8("maxTrialNumSpinBox"));

        horizontalLayout_3->addWidget(maxTrialNumSpinBox);

        layoutWidget3 = new QWidget(jobAdvanced);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(40, 210, 228, 26));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        unitWaitTimeLabel = new QLabel(layoutWidget3);
        unitWaitTimeLabel->setObjectName(QString::fromUtf8("unitWaitTimeLabel"));
        unitWaitTimeLabel->setFont(font1);

        horizontalLayout_4->addWidget(unitWaitTimeLabel);

        unitWaitTimeSpinBox = new QSpinBox(layoutWidget3);
        unitWaitTimeSpinBox->setObjectName(QString::fromUtf8("unitWaitTimeSpinBox"));

        horizontalLayout_4->addWidget(unitWaitTimeSpinBox);

        layoutWidget4 = new QWidget(jobAdvanced);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(40, 120, 301, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        jobLogDirLabel = new QLabel(layoutWidget4);
        jobLogDirLabel->setObjectName(QString::fromUtf8("jobLogDirLabel"));
        jobLogDirLabel->setFont(font1);

        horizontalLayout_5->addWidget(jobLogDirLabel);

        jobLogDirLineEdit = new QLineEdit(layoutWidget4);
        jobLogDirLineEdit->setObjectName(QString::fromUtf8("jobLogDirLineEdit"));
        jobLogDirLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(jobLogDirLineEdit);

        jobLogDirBrowseButton = new QPushButton(layoutWidget4);
        jobLogDirBrowseButton->setObjectName(QString::fromUtf8("jobLogDirBrowseButton"));

        horizontalLayout_5->addWidget(jobLogDirBrowseButton);

        layoutWidget5 = new QWidget(jobAdvanced);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(350, 90, 239, 26));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        minModifyTimeLabel = new QLabel(layoutWidget5);
        minModifyTimeLabel->setObjectName(QString::fromUtf8("minModifyTimeLabel"));
        minModifyTimeLabel->setFont(font1);

        horizontalLayout_6->addWidget(minModifyTimeLabel);

        minModifyTimeSpinBox = new QSpinBox(layoutWidget5);
        minModifyTimeSpinBox->setObjectName(QString::fromUtf8("minModifyTimeSpinBox"));

        horizontalLayout_6->addWidget(minModifyTimeSpinBox);

        layoutWidget6 = new QWidget(jobAdvanced);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(350, 120, 244, 26));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        maxModifyTimeLabel = new QLabel(layoutWidget6);
        maxModifyTimeLabel->setObjectName(QString::fromUtf8("maxModifyTimeLabel"));
        maxModifyTimeLabel->setFont(font1);

        horizontalLayout_7->addWidget(maxModifyTimeLabel);

        maxModifyTimeSpinBox = new QSpinBox(layoutWidget6);
        maxModifyTimeSpinBox->setObjectName(QString::fromUtf8("maxModifyTimeSpinBox"));

        horizontalLayout_7->addWidget(maxModifyTimeSpinBox);

        layoutWidget7 = new QWidget(jobAdvanced);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(350, 150, 268, 26));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        maxWaitLoopNumLabel = new QLabel(layoutWidget7);
        maxWaitLoopNumLabel->setObjectName(QString::fromUtf8("maxWaitLoopNumLabel"));
        maxWaitLoopNumLabel->setFont(font1);

        horizontalLayout_8->addWidget(maxWaitLoopNumLabel);

        maxWaitLoopNumSpinBox = new QSpinBox(layoutWidget7);
        maxWaitLoopNumSpinBox->setObjectName(QString::fromUtf8("maxWaitLoopNumSpinBox"));

        horizontalLayout_8->addWidget(maxWaitLoopNumSpinBox);

        layoutWidget8 = new QWidget(jobAdvanced);
        layoutWidget8->setObjectName(QString::fromUtf8("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(350, 180, 281, 25));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        matlabLaunchStrLabel = new QLabel(layoutWidget8);
        matlabLaunchStrLabel->setObjectName(QString::fromUtf8("matlabLaunchStrLabel"));
        matlabLaunchStrLabel->setFont(font1);

        horizontalLayout_9->addWidget(matlabLaunchStrLabel);

        matlabLaunchStrLineEdit = new QLineEdit(layoutWidget8);
        matlabLaunchStrLineEdit->setObjectName(QString::fromUtf8("matlabLaunchStrLineEdit"));
        matlabLaunchStrLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(matlabLaunchStrLineEdit);

        layoutWidget9 = new QWidget(jobAdvanced);
        layoutWidget9->setObjectName(QString::fromUtf8("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(350, 210, 281, 25));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        slurmParamLabel = new QLabel(layoutWidget9);
        slurmParamLabel->setObjectName(QString::fromUtf8("slurmParamLabel"));
        slurmParamLabel->setFont(font1);

        horizontalLayout_10->addWidget(slurmParamLabel);

        slurmParamLineEdit = new QLineEdit(layoutWidget9);
        slurmParamLineEdit->setObjectName(QString::fromUtf8("slurmParamLineEdit"));
        slurmParamLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(slurmParamLineEdit);


        retranslateUi(jobAdvanced);

        QMetaObject::connectSlotsByName(jobAdvanced);
    } // setupUi

    void retranslateUi(QDialog *jobAdvanced)
    {
        jobAdvanced->setWindowTitle(QCoreApplication::translate("jobAdvanced", "Job Advanced Settings", nullptr));
        jobAdvancedSettingsLabel->setText(QCoreApplication::translate("jobAdvanced", "Job Advanced Settings", nullptr));
        submitButton->setText(QCoreApplication::translate("jobAdvanced", "Submit", nullptr));
        cancelButton->setText(QCoreApplication::translate("jobAdvanced", "Cancel", nullptr));
        largeFileLabel->setText(QCoreApplication::translate("jobAdvanced", "Large File", nullptr));
        largeFileCheckBox->setText(QString());
        uuidLabel->setText(QCoreApplication::translate("jobAdvanced", "uuid", nullptr));
        maxTrialNumLabel->setText(QCoreApplication::translate("jobAdvanced", "Max Trial Num", nullptr));
        unitWaitTimeLabel->setText(QCoreApplication::translate("jobAdvanced", "Unit Wait Time", nullptr));
        jobLogDirLabel->setText(QCoreApplication::translate("jobAdvanced", "Job Log Dir", nullptr));
        jobLogDirBrowseButton->setText(QCoreApplication::translate("jobAdvanced", "Browse", nullptr));
        minModifyTimeLabel->setText(QCoreApplication::translate("jobAdvanced", "Min Modify Time", nullptr));
        maxModifyTimeLabel->setText(QCoreApplication::translate("jobAdvanced", "Max Modify Time", nullptr));
        maxWaitLoopNumLabel->setText(QCoreApplication::translate("jobAdvanced", "Max Wait Loop Num", nullptr));
        matlabLaunchStrLabel->setText(QCoreApplication::translate("jobAdvanced", "Matlab Launch Str", nullptr));
        slurmParamLabel->setText(QCoreApplication::translate("jobAdvanced", "Slurm Param", nullptr));
    } // retranslateUi

};

namespace Ui {
    class jobAdvanced: public Ui_jobAdvanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOBADVANCED_H
