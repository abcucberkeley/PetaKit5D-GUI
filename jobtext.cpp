#include "jobtext.h"
#include "ui_jobtext.h"
#include <QFile>
#include <QTextStream>

jobText::jobText(QString textFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jobText)
{
    ui->setupUi(this);

    // Delete the windows when they are closed to save memory
    setAttribute(Qt::WA_DeleteOnClose);

    // Set the window title to the file path
    setWindowTitle(textFile);
    QFile file(textFile);

    // Read the file into the textbox
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line.append(stream.readLine()+"\n");
        }
        ui->jobTextOutput->setText(line);
    }
    file.close();

}

jobText::~jobText()
{
    delete ui;
}
