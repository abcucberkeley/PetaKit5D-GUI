#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include "matlaboutputwindow.h"
#include "ui_matlaboutputwindow.h"


matlabOutputWindow::matlabOutputWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matlabOutputWindow)
{
    ui->setupUi(this);

    mOWThread = new matlabOutputWindowThread(this);

    QVBoxLayout* VBox = new QVBoxLayout(this);
    QHBoxLayout* HBox = new QHBoxLayout(this);

    VBox->addLayout(HBox);
    QPushButton* button = new QPushButton(this);
    button->setText("job1");
    HBox->addWidget(button);
    VBox->addStretch();

}

matlabOutputWindow::~matlabOutputWindow()
{
    delete ui;
}

void matlabOutputWindow::closeEvent(QCloseEvent *event){
    event->ignore();
}
