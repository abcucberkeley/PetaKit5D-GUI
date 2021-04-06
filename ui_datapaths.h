/********************************************************************************
** Form generated from reading UI file 'datapaths.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAPATHS_H
#define UI_DATAPATHS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dataPaths
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *dataPath1Label;
    QLineEdit *dataPath1LineEdit;
    QPushButton *dataPath1BrowseButton;
    QPushButton *addPathButton;
    QPushButton *removePathButton;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *dataPath2Label;
    QLineEdit *dataPath2LineEdit;
    QPushButton *dataPath2BrowseButton;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *dataPath3Label;
    QLineEdit *dataPath3LineEdit;
    QPushButton *dataPath3BrowseButton;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *dataPath4Label;
    QLineEdit *dataPath4LineEdit;
    QPushButton *dataPath4BrowseButton;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *dataPath5Label;
    QLineEdit *dataPath5LineEdit;
    QPushButton *dataPath5BrowseButton;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *dataPath6Label;
    QLineEdit *dataPath6LineEdit;
    QPushButton *dataPath6BrowseButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *dataPaths)
    {
        if (dataPaths->objectName().isEmpty())
            dataPaths->setObjectName(QString::fromUtf8("dataPaths"));
        dataPaths->resize(480, 360);
        layoutWidget = new QWidget(dataPaths);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 40, 441, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        dataPath1Label = new QLabel(layoutWidget);
        dataPath1Label->setObjectName(QString::fromUtf8("dataPath1Label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        dataPath1Label->setFont(font);

        horizontalLayout->addWidget(dataPath1Label);

        dataPath1LineEdit = new QLineEdit(layoutWidget);
        dataPath1LineEdit->setObjectName(QString::fromUtf8("dataPath1LineEdit"));
        dataPath1LineEdit->setEnabled(true);
        dataPath1LineEdit->setFrame(true);
        dataPath1LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dataPath1LineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(dataPath1LineEdit);

        dataPath1BrowseButton = new QPushButton(layoutWidget);
        dataPath1BrowseButton->setObjectName(QString::fromUtf8("dataPath1BrowseButton"));
        dataPath1BrowseButton->setAutoDefault(true);

        horizontalLayout->addWidget(dataPath1BrowseButton);

        addPathButton = new QPushButton(dataPaths);
        addPathButton->setObjectName(QString::fromUtf8("addPathButton"));
        addPathButton->setGeometry(QRect(280, 10, 91, 23));
        removePathButton = new QPushButton(dataPaths);
        removePathButton->setObjectName(QString::fromUtf8("removePathButton"));
        removePathButton->setGeometry(QRect(380, 10, 101, 23));
        layoutWidget_2 = new QWidget(dataPaths);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 80, 441, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        dataPath2Label = new QLabel(layoutWidget_2);
        dataPath2Label->setObjectName(QString::fromUtf8("dataPath2Label"));
        dataPath2Label->setFont(font);

        horizontalLayout_2->addWidget(dataPath2Label);

        dataPath2LineEdit = new QLineEdit(layoutWidget_2);
        dataPath2LineEdit->setObjectName(QString::fromUtf8("dataPath2LineEdit"));
        dataPath2LineEdit->setEnabled(true);
        dataPath2LineEdit->setFrame(true);
        dataPath2LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dataPath2LineEdit->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(dataPath2LineEdit);

        dataPath2BrowseButton = new QPushButton(layoutWidget_2);
        dataPath2BrowseButton->setObjectName(QString::fromUtf8("dataPath2BrowseButton"));

        horizontalLayout_2->addWidget(dataPath2BrowseButton);

        layoutWidget_3 = new QWidget(dataPaths);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 120, 441, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        dataPath3Label = new QLabel(layoutWidget_3);
        dataPath3Label->setObjectName(QString::fromUtf8("dataPath3Label"));
        dataPath3Label->setFont(font);

        horizontalLayout_3->addWidget(dataPath3Label);

        dataPath3LineEdit = new QLineEdit(layoutWidget_3);
        dataPath3LineEdit->setObjectName(QString::fromUtf8("dataPath3LineEdit"));
        dataPath3LineEdit->setEnabled(true);
        dataPath3LineEdit->setFrame(true);
        dataPath3LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dataPath3LineEdit->setClearButtonEnabled(false);

        horizontalLayout_3->addWidget(dataPath3LineEdit);

        dataPath3BrowseButton = new QPushButton(layoutWidget_3);
        dataPath3BrowseButton->setObjectName(QString::fromUtf8("dataPath3BrowseButton"));

        horizontalLayout_3->addWidget(dataPath3BrowseButton);

        layoutWidget_4 = new QWidget(dataPaths);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 160, 441, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        dataPath4Label = new QLabel(layoutWidget_4);
        dataPath4Label->setObjectName(QString::fromUtf8("dataPath4Label"));
        dataPath4Label->setFont(font);

        horizontalLayout_4->addWidget(dataPath4Label);

        dataPath4LineEdit = new QLineEdit(layoutWidget_4);
        dataPath4LineEdit->setObjectName(QString::fromUtf8("dataPath4LineEdit"));
        dataPath4LineEdit->setEnabled(true);
        dataPath4LineEdit->setFrame(true);
        dataPath4LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dataPath4LineEdit->setClearButtonEnabled(false);

        horizontalLayout_4->addWidget(dataPath4LineEdit);

        dataPath4BrowseButton = new QPushButton(layoutWidget_4);
        dataPath4BrowseButton->setObjectName(QString::fromUtf8("dataPath4BrowseButton"));

        horizontalLayout_4->addWidget(dataPath4BrowseButton);

        layoutWidget_5 = new QWidget(dataPaths);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 200, 441, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        dataPath5Label = new QLabel(layoutWidget_5);
        dataPath5Label->setObjectName(QString::fromUtf8("dataPath5Label"));
        dataPath5Label->setFont(font);

        horizontalLayout_5->addWidget(dataPath5Label);

        dataPath5LineEdit = new QLineEdit(layoutWidget_5);
        dataPath5LineEdit->setObjectName(QString::fromUtf8("dataPath5LineEdit"));
        dataPath5LineEdit->setEnabled(true);
        dataPath5LineEdit->setFrame(true);
        dataPath5LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dataPath5LineEdit->setClearButtonEnabled(false);

        horizontalLayout_5->addWidget(dataPath5LineEdit);

        dataPath5BrowseButton = new QPushButton(layoutWidget_5);
        dataPath5BrowseButton->setObjectName(QString::fromUtf8("dataPath5BrowseButton"));

        horizontalLayout_5->addWidget(dataPath5BrowseButton);

        layoutWidget_6 = new QWidget(dataPaths);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(20, 240, 441, 25));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        dataPath6Label = new QLabel(layoutWidget_6);
        dataPath6Label->setObjectName(QString::fromUtf8("dataPath6Label"));
        dataPath6Label->setFont(font);

        horizontalLayout_6->addWidget(dataPath6Label);

        dataPath6LineEdit = new QLineEdit(layoutWidget_6);
        dataPath6LineEdit->setObjectName(QString::fromUtf8("dataPath6LineEdit"));
        dataPath6LineEdit->setEnabled(true);
        dataPath6LineEdit->setFrame(true);
        dataPath6LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dataPath6LineEdit->setClearButtonEnabled(false);

        horizontalLayout_6->addWidget(dataPath6LineEdit);

        dataPath6BrowseButton = new QPushButton(layoutWidget_6);
        dataPath6BrowseButton->setObjectName(QString::fromUtf8("dataPath6BrowseButton"));

        horizontalLayout_6->addWidget(dataPath6BrowseButton);

        submitButton = new QPushButton(dataPaths);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(270, 290, 121, 61));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        submitButton->setFont(font1);
        cancelButton = new QPushButton(dataPaths);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(110, 290, 121, 61));
        cancelButton->setFont(font1);

        retranslateUi(dataPaths);

        QMetaObject::connectSlotsByName(dataPaths);
    } // setupUi

    void retranslateUi(QDialog *dataPaths)
    {
        dataPaths->setWindowTitle(QCoreApplication::translate("dataPaths", "Dialog", nullptr));
        dataPath1Label->setText(QCoreApplication::translate("dataPaths", "Data Path 1", nullptr));
        dataPath1LineEdit->setText(QString());
        dataPath1BrowseButton->setText(QCoreApplication::translate("dataPaths", "Browse", nullptr));
        addPathButton->setText(QCoreApplication::translate("dataPaths", "+ Add Path", nullptr));
        removePathButton->setText(QCoreApplication::translate("dataPaths", "- Remove Path", nullptr));
        dataPath2Label->setText(QCoreApplication::translate("dataPaths", "Data Path 2", nullptr));
        dataPath2LineEdit->setText(QString());
        dataPath2BrowseButton->setText(QCoreApplication::translate("dataPaths", "Browse", nullptr));
        dataPath3Label->setText(QCoreApplication::translate("dataPaths", "Data Path 3", nullptr));
        dataPath3LineEdit->setText(QString());
        dataPath3BrowseButton->setText(QCoreApplication::translate("dataPaths", "Browse", nullptr));
        dataPath4Label->setText(QCoreApplication::translate("dataPaths", "Data Path 4", nullptr));
        dataPath4LineEdit->setText(QString());
        dataPath4BrowseButton->setText(QCoreApplication::translate("dataPaths", "Browse", nullptr));
        dataPath5Label->setText(QCoreApplication::translate("dataPaths", "Data Path 5", nullptr));
        dataPath5LineEdit->setText(QString());
        dataPath5BrowseButton->setText(QCoreApplication::translate("dataPaths", "Browse", nullptr));
        dataPath6Label->setText(QCoreApplication::translate("dataPaths", "Data Path 6", nullptr));
        dataPath6LineEdit->setText(QString());
        dataPath6BrowseButton->setText(QCoreApplication::translate("dataPaths", "Browse", nullptr));
        submitButton->setText(QCoreApplication::translate("dataPaths", "Submit", nullptr));
        cancelButton->setText(QCoreApplication::translate("dataPaths", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dataPaths: public Ui_dataPaths {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAPATHS_H
