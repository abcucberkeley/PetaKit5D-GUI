#include "matlaboutputwindow.h"
#include "ui_matlaboutputwindow.h"

matlabOutputWindow::matlabOutputWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matlabOutputWindow)
{
    ui->setupUi(this);
}

matlabOutputWindow::~matlabOutputWindow()
{
    delete ui;
}

/*
QLabel* label = new QLabel(ui->Main);
label->setTextFormat(Qt::RichText);
label->setText("<b>"+ch+"<\b>");
ui->horizontalLayout_4->addWidget(label);

QCheckBox* checkBox = new QCheckBox(ui->Main);
ui->horizontalLayout_4->addWidget(checkBox);
channelWidgets.push_back(std::make_pair(label,checkBox));
*/
