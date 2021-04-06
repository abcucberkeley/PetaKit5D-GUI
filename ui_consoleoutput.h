/********************************************************************************
** Form generated from reading UI file 'consoleoutput.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLEOUTPUT_H
#define UI_CONSOLEOUTPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_consoleOutput
{
public:
    QPlainTextEdit *outputTextEdit;

    void setupUi(QDialog *consoleOutput)
    {
        if (consoleOutput->objectName().isEmpty())
            consoleOutput->setObjectName(QString::fromUtf8("consoleOutput"));
        consoleOutput->resize(400, 300);
        outputTextEdit = new QPlainTextEdit(consoleOutput);
        outputTextEdit->setObjectName(QString::fromUtf8("outputTextEdit"));
        outputTextEdit->setGeometry(QRect(30, 20, 341, 251));
        outputTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        outputTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        outputTextEdit->setReadOnly(true);

        retranslateUi(consoleOutput);

        QMetaObject::connectSlotsByName(consoleOutput);
    } // setupUi

    void retranslateUi(QDialog *consoleOutput)
    {
        consoleOutput->setWindowTitle(QCoreApplication::translate("consoleOutput", "Job Output", nullptr));
        outputTextEdit->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class consoleOutput: public Ui_consoleOutput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLEOUTPUT_H
