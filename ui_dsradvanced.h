/********************************************************************************
** Form generated from reading UI file 'dsradvanced.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DSRADVANCED_H
#define UI_DSRADVANCED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DSRadvanced
{
public:
    QLabel *dsrAdvancedSettingsLabel;
    QPushButton *cancelButton;
    QPushButton *submitButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *resampleTypeLabel;
    QComboBox *resampleTypeComboBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *resampleLabel;
    QSpinBox *resampleSpinBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *bkRemovalLabel;
    QCheckBox *bkRemovalCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lowerLimitLabel;
    QDoubleSpinBox *lowerLimitSpinBox;

    void setupUi(QDialog *DSRadvanced)
    {
        if (DSRadvanced->objectName().isEmpty())
            DSRadvanced->setObjectName(QString::fromUtf8("DSRadvanced"));
        DSRadvanced->resize(640, 480);
        dsrAdvancedSettingsLabel = new QLabel(DSRadvanced);
        dsrAdvancedSettingsLabel->setObjectName(QString::fromUtf8("dsrAdvancedSettingsLabel"));
        dsrAdvancedSettingsLabel->setGeometry(QRect(10, 10, 631, 71));
        QFont font;
        font.setPointSize(24);
        dsrAdvancedSettingsLabel->setFont(font);
        cancelButton = new QPushButton(DSRadvanced);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(190, 360, 121, 61));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        cancelButton->setFont(font1);
        submitButton = new QPushButton(DSRadvanced);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(350, 360, 121, 61));
        submitButton->setFont(font1);
        layoutWidget = new QWidget(DSRadvanced);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 150, 280, 29));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        resampleTypeLabel = new QLabel(layoutWidget);
        resampleTypeLabel->setObjectName(QString::fromUtf8("resampleTypeLabel"));
        resampleTypeLabel->setFont(font1);

        horizontalLayout_5->addWidget(resampleTypeLabel);

        resampleTypeComboBox = new QComboBox(layoutWidget);
        resampleTypeComboBox->addItem(QString());
        resampleTypeComboBox->addItem(QString());
        resampleTypeComboBox->setObjectName(QString::fromUtf8("resampleTypeComboBox"));
        resampleTypeComboBox->setFont(font1);
        resampleTypeComboBox->setEditable(false);

        horizontalLayout_5->addWidget(resampleTypeComboBox);

        layoutWidget1 = new QWidget(DSRadvanced);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(230, 190, 185, 26));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        resampleLabel = new QLabel(layoutWidget1);
        resampleLabel->setObjectName(QString::fromUtf8("resampleLabel"));
        resampleLabel->setFont(font1);

        horizontalLayout_6->addWidget(resampleLabel);

        resampleSpinBox = new QSpinBox(layoutWidget1);
        resampleSpinBox->setObjectName(QString::fromUtf8("resampleSpinBox"));

        horizontalLayout_6->addWidget(resampleSpinBox);

        layoutWidget2 = new QWidget(DSRadvanced);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(230, 90, 239, 55));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        bkRemovalLabel = new QLabel(layoutWidget2);
        bkRemovalLabel->setObjectName(QString::fromUtf8("bkRemovalLabel"));
        bkRemovalLabel->setFont(font1);

        horizontalLayout->addWidget(bkRemovalLabel);

        bkRemovalCheckBox = new QCheckBox(layoutWidget2);
        bkRemovalCheckBox->setObjectName(QString::fromUtf8("bkRemovalCheckBox"));
        bkRemovalCheckBox->setAutoFillBackground(false);

        horizontalLayout->addWidget(bkRemovalCheckBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lowerLimitLabel = new QLabel(layoutWidget2);
        lowerLimitLabel->setObjectName(QString::fromUtf8("lowerLimitLabel"));
        lowerLimitLabel->setFont(font1);

        horizontalLayout_2->addWidget(lowerLimitLabel);

        lowerLimitSpinBox = new QDoubleSpinBox(layoutWidget2);
        lowerLimitSpinBox->setObjectName(QString::fromUtf8("lowerLimitSpinBox"));
        lowerLimitSpinBox->setDecimals(1);
        lowerLimitSpinBox->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(lowerLimitSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(DSRadvanced);

        QMetaObject::connectSlotsByName(DSRadvanced);
    } // setupUi

    void retranslateUi(QDialog *DSRadvanced)
    {
        DSRadvanced->setWindowTitle(QCoreApplication::translate("DSRadvanced", "DSR Advanced Settings", nullptr));
        dsrAdvancedSettingsLabel->setText(QCoreApplication::translate("DSRadvanced", " Deskew and Rotate Advanced Settings", nullptr));
        cancelButton->setText(QCoreApplication::translate("DSRadvanced", "Cancel", nullptr));
        submitButton->setText(QCoreApplication::translate("DSRadvanced", "Submit", nullptr));
        resampleTypeLabel->setText(QCoreApplication::translate("DSRadvanced", "Resample Type", nullptr));
        resampleTypeComboBox->setItemText(0, QCoreApplication::translate("DSRadvanced", "isotropic", nullptr));
        resampleTypeComboBox->setItemText(1, QCoreApplication::translate("DSRadvanced", "xy_isotropic", nullptr));

        resampleTypeComboBox->setCurrentText(QCoreApplication::translate("DSRadvanced", "isotropic", nullptr));
        resampleLabel->setText(QCoreApplication::translate("DSRadvanced", "Resample", nullptr));
        bkRemovalLabel->setText(QCoreApplication::translate("DSRadvanced", "BK Removal", nullptr));
        bkRemovalCheckBox->setText(QString());
        lowerLimitLabel->setText(QCoreApplication::translate("DSRadvanced", "Lower Limit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DSRadvanced: public Ui_DSRadvanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DSRADVANCED_H
