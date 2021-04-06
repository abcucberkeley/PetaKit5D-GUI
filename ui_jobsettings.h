/********************************************************************************
** Form generated from reading UI file 'jobsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOBSETTINGS_H
#define UI_JOBSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_jobSettings
{
public:

    void setupUi(QDialog *jobSettings)
    {
        if (jobSettings->objectName().isEmpty())
            jobSettings->setObjectName(QString::fromUtf8("jobSettings"));
        jobSettings->resize(640, 480);

        retranslateUi(jobSettings);

        QMetaObject::connectSlotsByName(jobSettings);
    } // setupUi

    void retranslateUi(QDialog *jobSettings)
    {
        jobSettings->setWindowTitle(QCoreApplication::translate("jobSettings", "Job Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class jobSettings: public Ui_jobSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOBSETTINGS_H
