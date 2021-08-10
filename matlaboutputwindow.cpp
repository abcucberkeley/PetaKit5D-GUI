#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QScrollArea>
#include "matlaboutputwindow.h"
#include "ui_matlaboutputwindow.h"


matlabOutputWindow::matlabOutputWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matlabOutputWindow)
{
    ui->setupUi(this);

    mOWThread = new matlabOutputWindowThread(this);

    QScrollArea* QSAMain = new QScrollArea(this);
    QSAMain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QSAMain->setWidgetResizable(true);

    QWidget* containerMain = new QWidget(this);
    QVBoxLayout* VBoxMain = new QVBoxLayout(containerMain);

    //VBoxMain->addWidget(new QLabel("Something else", this));

    for(int i = 0; i < 6; i++){
    QScrollArea* QSA = new QScrollArea(this);
    QSA->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //QSA->setAlignment(Qt::AlignTop);
    QSA->setWidgetResizable(true);


    //QHBoxLayout* HBox = new QHBoxLayout(QSA);
    QWidget* container = new QWidget(this);
    QVBoxLayout* VBox = new QVBoxLayout(container);

    for(int j = 0; j < 80; j++){
    QPushButton* button = new QPushButton(this);
    button->setText("job"+QString::number(j));
    VBox->addWidget(button);
    }

    container->setLayout(VBox);
    QSA->setWidget(container);

    //ui->verticalLayout_2->addWidget(new QLabel("Something else", this));
    VBoxMain->addWidget(new QLabel("Job"+QString::number(i),this));
    VBoxMain->addWidget(QSA);
    }

    containerMain->setLayout(VBoxMain);
    QSAMain->setWidget(containerMain);

    //VBoxMain->addWidget(new QLabel("Something else 3", this));

    ui->verticalLayout_2->addWidget(QSAMain);
    //ui->verticalLayout_2->addLayout(VBox);

    //QSA->addLayout(HBox);
    //VBox->addStretch();

}

matlabOutputWindow::~matlabOutputWindow()
{
    delete ui;
}

void matlabOutputWindow::closeEvent(QCloseEvent *event){
    event->ignore();
}
