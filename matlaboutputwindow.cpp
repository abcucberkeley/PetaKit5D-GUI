#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QScrollArea>
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

    for(int i = 0; i < 6; i++){
    QWidget* container = new QWidget(this);
    outputBox nBox(new QScrollArea(this),container,new QVBoxLayout(container));

    for(int j = 0; j < 80; j++){
    QPushButton* button = new QPushButton(this);
    button->setText("job"+QString::number(j));
    //nBox.vBox->addWidget(button);
    nBox.addToVBox(button);
    }

    container->setLayout(nBox.vBox);
    nBox.scrollArea->setWidget(container);

    //ui->verticalLayout_2->addWidget(new QLabel("Something else", this));
    mainBox.vBox->addWidget(new QLabel("Job"+QString::number(i),this));
    mainBox.vBox->addWidget(nBox.scrollArea);
    }

    containerMain->setLayout(mainBox.vBox);
    mainBox.scrollArea->setWidget(containerMain);

    ui->verticalLayout_2->addWidget(mainBox.scrollArea);

}

matlabOutputWindow::~matlabOutputWindow()
{
    delete ui;
}

void matlabOutputWindow::closeEvent(QCloseEvent *event){
    event->ignore();
}

void matlabOutputWindow::onUpdateOutputForm(){

}
