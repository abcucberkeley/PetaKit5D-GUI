/********************************************************************************
** Form generated from reading UI file 'mainadvanced.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINADVANCED_H
#define UI_MAINADVANCED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainAdvanced
{
public:
    QPushButton *cancelButton;
    QPushButton *submitButton;
    QLabel *mainAdvancedSettingsLabel;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *sCMOSCameraFlipLabel;
    QCheckBox *sCMOSCameraFlipCheckBox;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *reverseDataLabel;
    QCheckBox *reverseCheckBox;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *xyPixelSizeLabel;
    QDoubleSpinBox *xyPixelSizeSpinBox;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *skewAngleLabel;
    QDoubleSpinBox *skewAngleSpinBox;

    void setupUi(QDialog *mainAdvanced)
    {
        if (mainAdvanced->objectName().isEmpty())
            mainAdvanced->setObjectName(QString::fromUtf8("mainAdvanced"));
        mainAdvanced->resize(640, 480);
        cancelButton = new QPushButton(mainAdvanced);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(180, 370, 121, 61));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        cancelButton->setFont(font);
        submitButton = new QPushButton(mainAdvanced);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(340, 370, 121, 61));
        submitButton->setFont(font);
        mainAdvancedSettingsLabel = new QLabel(mainAdvanced);
        mainAdvancedSettingsLabel->setObjectName(QString::fromUtf8("mainAdvancedSettingsLabel"));
        mainAdvancedSettingsLabel->setGeometry(QRect(140, 10, 391, 71));
        QFont font1;
        font1.setPointSize(24);
        mainAdvancedSettingsLabel->setFont(font1);
        layoutWidget_2 = new QWidget(mainAdvanced);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(220, 170, 198, 21));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        sCMOSCameraFlipLabel = new QLabel(layoutWidget_2);
        sCMOSCameraFlipLabel->setObjectName(QString::fromUtf8("sCMOSCameraFlipLabel"));
        sCMOSCameraFlipLabel->setFont(font);

        horizontalLayout_10->addWidget(sCMOSCameraFlipLabel);

        sCMOSCameraFlipCheckBox = new QCheckBox(layoutWidget_2);
        sCMOSCameraFlipCheckBox->setObjectName(QString::fromUtf8("sCMOSCameraFlipCheckBox"));
        sCMOSCameraFlipCheckBox->setAutoFillBackground(false);

        horizontalLayout_10->addWidget(sCMOSCameraFlipCheckBox);

        layoutWidget_3 = new QWidget(mainAdvanced);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(220, 140, 95, 21));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        reverseDataLabel = new QLabel(layoutWidget_3);
        reverseDataLabel->setObjectName(QString::fromUtf8("reverseDataLabel"));
        reverseDataLabel->setFont(font);

        horizontalLayout_8->addWidget(reverseDataLabel);

        reverseCheckBox = new QCheckBox(layoutWidget_3);
        reverseCheckBox->setObjectName(QString::fromUtf8("reverseCheckBox"));
        reverseCheckBox->setChecked(true);

        horizontalLayout_8->addWidget(reverseCheckBox);

        layoutWidget_4 = new QWidget(mainAdvanced);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(220, 110, 191, 26));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        xyPixelSizeLabel = new QLabel(layoutWidget_4);
        xyPixelSizeLabel->setObjectName(QString::fromUtf8("xyPixelSizeLabel"));
        xyPixelSizeLabel->setFont(font);

        horizontalLayout_7->addWidget(xyPixelSizeLabel);

        xyPixelSizeSpinBox = new QDoubleSpinBox(layoutWidget_4);
        xyPixelSizeSpinBox->setObjectName(QString::fromUtf8("xyPixelSizeSpinBox"));
        xyPixelSizeSpinBox->setDecimals(3);
        xyPixelSizeSpinBox->setSingleStep(0.001000000000000);
        xyPixelSizeSpinBox->setStepType(QAbstractSpinBox::DefaultStepType);
        xyPixelSizeSpinBox->setValue(0.108000000000000);

        horizontalLayout_7->addWidget(xyPixelSizeSpinBox);

        layoutWidget_5 = new QWidget(mainAdvanced);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(220, 80, 181, 26));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        skewAngleLabel = new QLabel(layoutWidget_5);
        skewAngleLabel->setObjectName(QString::fromUtf8("skewAngleLabel"));
        skewAngleLabel->setFont(font);

        horizontalLayout_5->addWidget(skewAngleLabel);

        skewAngleSpinBox = new QDoubleSpinBox(layoutWidget_5);
        skewAngleSpinBox->setObjectName(QString::fromUtf8("skewAngleSpinBox"));
        skewAngleSpinBox->setSingleStep(0.010000000000000);
        skewAngleSpinBox->setValue(32.450000000000003);

        horizontalLayout_5->addWidget(skewAngleSpinBox);


        retranslateUi(mainAdvanced);

        QMetaObject::connectSlotsByName(mainAdvanced);
    } // setupUi

    void retranslateUi(QDialog *mainAdvanced)
    {
        mainAdvanced->setWindowTitle(QCoreApplication::translate("mainAdvanced", "Dialog", nullptr));
        cancelButton->setText(QCoreApplication::translate("mainAdvanced", "Cancel", nullptr));
        submitButton->setText(QCoreApplication::translate("mainAdvanced", "Submit", nullptr));
        mainAdvancedSettingsLabel->setText(QCoreApplication::translate("mainAdvanced", "Main Advanced Settings", nullptr));
        sCMOSCameraFlipLabel->setText(QCoreApplication::translate("mainAdvanced", "sCMOS Camera Flip", nullptr));
        sCMOSCameraFlipCheckBox->setText(QString());
        reverseDataLabel->setText(QCoreApplication::translate("mainAdvanced", "Reverse", nullptr));
        reverseCheckBox->setText(QString());
        xyPixelSizeLabel->setText(QCoreApplication::translate("mainAdvanced", "xy Pixel Size", nullptr));
        skewAngleLabel->setText(QCoreApplication::translate("mainAdvanced", "Skew Angle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainAdvanced: public Ui_mainAdvanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINADVANCED_H
