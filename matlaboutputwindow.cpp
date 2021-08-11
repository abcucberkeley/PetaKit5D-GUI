#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QScrollArea>
#include <iostream>
#include "matlaboutputwindow.h"
#include "ui_matlaboutputwindow.h"


matlabOutputWindow::matlabOutputWindow(std::unordered_map<int,std::string> &jobLogPaths, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matlabOutputWindow)
{
    ui->setupUi(this);

    this->jobLogPaths = &jobLogPaths;

    mOWThread = new matlabOutputWindowThread(jobLogPaths,this);
    connect(mOWThread,&matlabOutputWindowThread::updateOutputForm,this,&matlabOutputWindow::onUpdateOutputForm);
    mOWThread->start(QThread::NormalPriority);

    QWidget* containerMain = new QWidget(this);
    mainBox = outputBox(new QScrollArea(this),containerMain,new QVBoxLayout(containerMain));

    //VBoxMain->addWidget(new QLabel("Something else", this));

    /*
    for(int i = 0; i < 6; i++){
    QWidget* container = new QWidget(this);
    outputBox nBox(new QScrollArea(this),container,new QVBoxLayout(container));

    for(int j = 0; j < 80; j++){
    QPushButton* button = new QPushButton(this);
    button->setText("job"+QString::number(j));
    //nBox.vBox->addWidget(button);
    nBox.addToVBox(button);
    }

    nBox.container->setLayout(nBox.vBox);
    nBox.scrollArea->setWidget(nBox.container);

    //ui->verticalLayout_2->addWidget(new QLabel("Something else", this));
    mainBox.vBox->addWidget(new QLabel("Job"+QString::number(i),this));
    mainBox.vBox->addWidget(nBox.scrollArea);
    }*/

    mainBox.container->setLayout(mainBox.vBox);
    mainBox.scrollArea->setWidget(mainBox.container);

    ui->verticalLayout_2->addWidget(mainBox.scrollArea);

}

matlabOutputWindow::~matlabOutputWindow()
{
    delete ui;
}

void matlabOutputWindow::closeEvent(QCloseEvent *event){
    event->ignore();
}

void matlabOutputWindow::onUpdateOutputForm(std::map<int,std::map<std::string,std::string>> fNames){
    for(auto &path : fNames){
        QWidget* container = new QWidget(this);
        outputBox nBox(new QScrollArea(this),container,new QVBoxLayout(container));

        for(auto &subPath : path.second){
           QPushButton* button = new QPushButton(this);
           QFileInfo filePath(QString::fromStdString(subPath.second));
           button->setText(filePath.baseName());
           button->setObjectName(filePath.absoluteFilePath());
           connect(button,&QPushButton::clicked,this,&matlabOutputWindow::onJobButtonClicked);
           nBox.vBox->addWidget(button);
        }

        nBox.container->setLayout(nBox.vBox);
        nBox.scrollArea->setWidget(nBox.container);

        mainBox.vBox->addWidget(new QLabel("Job"+QString::number(path.first),this));
        mainBox.vBox->addWidget(nBox.scrollArea);
    }

}

void matlabOutputWindow::onJobButtonClicked(){
    QString button = ((QPushButton*)sender())->objectName();
    std::cout << button.toStdString() << std::endl;
}
