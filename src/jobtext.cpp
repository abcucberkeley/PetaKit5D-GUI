#include "jobtext.h"
#include "ui_jobtext.h"
#include "jobtextmanager.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>

jobText::jobText(QString textFile, QWidget *parent) :
    QDialog(parent), ui(new Ui::jobText), textFile(textFile), reading(false)
{
    ui->setupUi(this);

    // Delete the windows when they are closed to save memory
    setAttribute(Qt::WA_DeleteOnClose);

    // Set the window title to the file path
    setWindowTitle(textFile);
    QFile file(textFile);
    this->textFile = textFile;

    // Read the file into the textbox
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line.append(stream.readLine()+"\n");
        }
        // testing
        ui->jobTextOutput->setText(line);
    }
    file.close();

    jTextManager = new jobTextManager(this);
    connect(this, &jobText::closeManager, jTextManager, &jobTextManager::onCloseManager);
    connect(jTextManager, &jobTextManager::updateTextWindow, this, &jobText::onUpdateTextWindow);
    jTextManager->start(QThread::NormalPriority);

}

// Event triggered when main window is closed
void jobText::closeEvent(QCloseEvent *event)
{
    // When the window is closed also end the text window manager
    emit closeManager();
    event->accept();
}

jobText::~jobText()
{
    delete ui;
}

void jobText::onUpdateTextWindow(){
    if(!reading){
        reading = true;
        QFile file(textFile);
        QString line;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
            while (!stream.atEnd()){
                line.append(stream.readLine()+"\n");
            }
            ui->jobTextOutput->setText(line);
            /*
            QString appText = line.simplified().remove(ui->jobTextOutput->toPlainText().simplified());
            if(!appText.simplified().isEmpty()){
                ui->jobTextOutput->append(appText.simplified());
            }*/
            // try appending here instead
        }
        file.close();
        reading = false;
    }
}
