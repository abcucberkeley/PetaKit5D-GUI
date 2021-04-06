/********************************************************************************
** Form generated from reading UI file 'deconadvanced.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECONADVANCED_H
#define UI_DECONADVANCED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deconAdvanced
{
public:
    QLabel *deconAdvancedSettingsLabel;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *cppDeconPathLabel;
    QLineEdit *cppDeconPathLineEdit;
    QPushButton *cppDeconPathBrowseButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *loadModulesLabel;
    QLineEdit *loadModulesLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *cudaDeconPathLabel;
    QLineEdit *cudaDeconPathLineEdit;
    QPushButton *cudaDeconPathBrowseButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *otfgenPathLabel;
    QLineEdit *otfgenPathLineEdit;
    QPushButton *otfgenPathBrowseButton;

    void setupUi(QDialog *deconAdvanced)
    {
        if (deconAdvanced->objectName().isEmpty())
            deconAdvanced->setObjectName(QString::fromUtf8("deconAdvanced"));
        deconAdvanced->resize(640, 480);
        deconAdvancedSettingsLabel = new QLabel(deconAdvanced);
        deconAdvancedSettingsLabel->setObjectName(QString::fromUtf8("deconAdvancedSettingsLabel"));
        deconAdvancedSettingsLabel->setGeometry(QRect(140, 0, 431, 71));
        QFont font;
        font.setPointSize(24);
        deconAdvancedSettingsLabel->setFont(font);
        submitButton = new QPushButton(deconAdvanced);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(350, 380, 121, 61));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        submitButton->setFont(font1);
        cancelButton = new QPushButton(deconAdvanced);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(190, 380, 121, 61));
        cancelButton->setFont(font1);
        layoutWidget = new QWidget(deconAdvanced);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 100, 471, 241));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cppDeconPathLabel = new QLabel(layoutWidget);
        cppDeconPathLabel->setObjectName(QString::fromUtf8("cppDeconPathLabel"));
        cppDeconPathLabel->setFont(font1);

        horizontalLayout->addWidget(cppDeconPathLabel);

        cppDeconPathLineEdit = new QLineEdit(layoutWidget);
        cppDeconPathLineEdit->setObjectName(QString::fromUtf8("cppDeconPathLineEdit"));
        cppDeconPathLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(cppDeconPathLineEdit);

        cppDeconPathBrowseButton = new QPushButton(layoutWidget);
        cppDeconPathBrowseButton->setObjectName(QString::fromUtf8("cppDeconPathBrowseButton"));

        horizontalLayout->addWidget(cppDeconPathBrowseButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        loadModulesLabel = new QLabel(layoutWidget);
        loadModulesLabel->setObjectName(QString::fromUtf8("loadModulesLabel"));
        loadModulesLabel->setFont(font1);

        horizontalLayout_2->addWidget(loadModulesLabel);

        loadModulesLineEdit = new QLineEdit(layoutWidget);
        loadModulesLineEdit->setObjectName(QString::fromUtf8("loadModulesLineEdit"));
        loadModulesLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(loadModulesLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cudaDeconPathLabel = new QLabel(layoutWidget);
        cudaDeconPathLabel->setObjectName(QString::fromUtf8("cudaDeconPathLabel"));
        cudaDeconPathLabel->setFont(font1);

        horizontalLayout_3->addWidget(cudaDeconPathLabel);

        cudaDeconPathLineEdit = new QLineEdit(layoutWidget);
        cudaDeconPathLineEdit->setObjectName(QString::fromUtf8("cudaDeconPathLineEdit"));
        cudaDeconPathLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(cudaDeconPathLineEdit);

        cudaDeconPathBrowseButton = new QPushButton(layoutWidget);
        cudaDeconPathBrowseButton->setObjectName(QString::fromUtf8("cudaDeconPathBrowseButton"));

        horizontalLayout_3->addWidget(cudaDeconPathBrowseButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        otfgenPathLabel = new QLabel(layoutWidget);
        otfgenPathLabel->setObjectName(QString::fromUtf8("otfgenPathLabel"));
        otfgenPathLabel->setFont(font1);

        horizontalLayout_4->addWidget(otfgenPathLabel);

        otfgenPathLineEdit = new QLineEdit(layoutWidget);
        otfgenPathLineEdit->setObjectName(QString::fromUtf8("otfgenPathLineEdit"));
        otfgenPathLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(otfgenPathLineEdit);

        otfgenPathBrowseButton = new QPushButton(layoutWidget);
        otfgenPathBrowseButton->setObjectName(QString::fromUtf8("otfgenPathBrowseButton"));

        horizontalLayout_4->addWidget(otfgenPathBrowseButton);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(deconAdvanced);

        QMetaObject::connectSlotsByName(deconAdvanced);
    } // setupUi

    void retranslateUi(QDialog *deconAdvanced)
    {
        deconAdvanced->setWindowTitle(QCoreApplication::translate("deconAdvanced", "Decon Advanced Settings", nullptr));
        deconAdvancedSettingsLabel->setText(QCoreApplication::translate("deconAdvanced", " Decon Advanced Settings", nullptr));
        submitButton->setText(QCoreApplication::translate("deconAdvanced", "Submit", nullptr));
        cancelButton->setText(QCoreApplication::translate("deconAdvanced", "Cancel", nullptr));
        cppDeconPathLabel->setText(QCoreApplication::translate("deconAdvanced", "CPP Decon Path", nullptr));
        cppDeconPathBrowseButton->setText(QCoreApplication::translate("deconAdvanced", "Browse", nullptr));
        loadModulesLabel->setText(QCoreApplication::translate("deconAdvanced", "Load Modules", nullptr));
        cudaDeconPathLabel->setText(QCoreApplication::translate("deconAdvanced", "CUDA Decon Path", nullptr));
        cudaDeconPathBrowseButton->setText(QCoreApplication::translate("deconAdvanced", "Browse", nullptr));
        otfgenPathLabel->setText(QCoreApplication::translate("deconAdvanced", "OTFGEN Path", nullptr));
        otfgenPathBrowseButton->setText(QCoreApplication::translate("deconAdvanced", "Browse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deconAdvanced: public Ui_deconAdvanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECONADVANCED_H
