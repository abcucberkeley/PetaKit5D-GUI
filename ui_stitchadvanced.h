/********************************************************************************
** Form generated from reading UI file 'stitchadvanced.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STITCHADVANCED_H
#define UI_STITCHADVANCED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stitchAdvanced
{
public:
    QLabel *stitchAdvancedSettingsLabel;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *boundBoxCropLabel;
    QLineEdit *boundBoxCropLineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *primaryCHLabel;
    QLineEdit *primaryCHLineEdit;

    void setupUi(QDialog *stitchAdvanced)
    {
        if (stitchAdvanced->objectName().isEmpty())
            stitchAdvanced->setObjectName(QString::fromUtf8("stitchAdvanced"));
        stitchAdvanced->resize(640, 480);
        stitchAdvancedSettingsLabel = new QLabel(stitchAdvanced);
        stitchAdvancedSettingsLabel->setObjectName(QString::fromUtf8("stitchAdvancedSettingsLabel"));
        stitchAdvancedSettingsLabel->setGeometry(QRect(130, 10, 421, 71));
        QFont font;
        font.setPointSize(24);
        stitchAdvancedSettingsLabel->setFont(font);
        submitButton = new QPushButton(stitchAdvanced);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(330, 370, 121, 61));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        submitButton->setFont(font1);
        cancelButton = new QPushButton(stitchAdvanced);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(170, 370, 121, 61));
        cancelButton->setFont(font1);
        layoutWidget = new QWidget(stitchAdvanced);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 80, 321, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        boundBoxCropLabel = new QLabel(layoutWidget);
        boundBoxCropLabel->setObjectName(QString::fromUtf8("boundBoxCropLabel"));
        boundBoxCropLabel->setFont(font1);

        horizontalLayout->addWidget(boundBoxCropLabel);

        boundBoxCropLineEdit = new QLineEdit(layoutWidget);
        boundBoxCropLineEdit->setObjectName(QString::fromUtf8("boundBoxCropLineEdit"));
        boundBoxCropLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(boundBoxCropLineEdit);

        layoutWidget1 = new QWidget(stitchAdvanced);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(160, 110, 211, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        primaryCHLabel = new QLabel(layoutWidget1);
        primaryCHLabel->setObjectName(QString::fromUtf8("primaryCHLabel"));
        primaryCHLabel->setFont(font1);

        horizontalLayout_2->addWidget(primaryCHLabel);

        primaryCHLineEdit = new QLineEdit(layoutWidget1);
        primaryCHLineEdit->setObjectName(QString::fromUtf8("primaryCHLineEdit"));
        primaryCHLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(primaryCHLineEdit);


        retranslateUi(stitchAdvanced);

        QMetaObject::connectSlotsByName(stitchAdvanced);
    } // setupUi

    void retranslateUi(QDialog *stitchAdvanced)
    {
        stitchAdvanced->setWindowTitle(QCoreApplication::translate("stitchAdvanced", "Stitch Advanced Settings", nullptr));
        stitchAdvancedSettingsLabel->setText(QCoreApplication::translate("stitchAdvanced", " Stitch Advanced Settings", nullptr));
        submitButton->setText(QCoreApplication::translate("stitchAdvanced", "Submit", nullptr));
        cancelButton->setText(QCoreApplication::translate("stitchAdvanced", "Cancel", nullptr));
        boundBoxCropLabel->setText(QCoreApplication::translate("stitchAdvanced", "Bound Box Crop", nullptr));
        primaryCHLabel->setText(QCoreApplication::translate("stitchAdvanced", "Primary Ch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stitchAdvanced: public Ui_stitchAdvanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STITCHADVANCED_H
