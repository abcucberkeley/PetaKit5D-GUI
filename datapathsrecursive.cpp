#include "datapathsrecursive.h"
#include "ui_datapathsrecursive.h"
#include <QDirIterator>
#include <iostream>

dataPathsRecursive::dataPathsRecursive(std::unordered_map<std::string,std::unordered_map<std::string,std::string>> *currPaths, const std::string &currPath, const QString &currPatttern,int maxDepth, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPathsRecursive)
{
    ui->setupUi(this);
    this->currPaths = currPaths;
    this->currPath = currPath;
    this->maxDepth = maxDepth;

    if(currPath.empty()){
        return;
    }
    QString currPathQ = QString::fromStdString(currPath);
    currPathQ.replace('\\','/');
    while(currPathQ.back() == '/') currPathQ.chop(1);
    int currPathDepth = currPathQ.count('/');
    QDirIterator it(currPathQ,{QDir::NoDotAndDotDot,QDir::Dirs},QDirIterator::Subdirectories);

    ui->dataPathsRecursiveVerticalLayout->addStretch();
    int i = 0;
    while(it.hasNext()){
        QString checkString = it.next();
        int checkCount = checkString.count('/');
        if(checkCount <= currPathDepth+maxDepth  && checkString.contains(currPatttern)){
            makeNewPath(i,checkString);
            i++;
        }

    }


}

dataPathsRecursive::~dataPathsRecursive()
{
    delete ui;
}

void dataPathsRecursive::on_dataPathRecursiveLineEdit_textChanged(const QString &arg1)
{
    ((QLineEdit*)sender())->setToolTip(arg1);
}

void dataPathsRecursive::makeNewPath(int i, QString currPath){

    // Add a horizontal layout to the form
    QHBoxLayout* QHBox = new QHBoxLayout(this);
    ui->dataPathsRecursiveVerticalLayout->insertLayout(ui->dataPathsRecursiveVerticalLayout->count()-1,QHBox);

    // Add the Add Path label
    QLabel* QLAP = new QLabel(this);
    QLAP->setTextFormat(Qt::RichText);
    QLAP->setText("<b>Add Path:<\b>");
    QHBox->addWidget(QLAP);

    // Add Checkbox
    QCheckBox* QCB = new QCheckBox(this);
    QCB->setObjectName(QString("dataPathRecursiveCheckBox")+QString::number(i));
    //connect(QCB,&QCheckBox::stateChanged,this,&dataPaths::on_dataPathCheckBox_stateChanged);
    QHBox->addWidget(QCB);

    // Add the text box
    QLineEdit* QLE = new QLineEdit(this);
    QLE->setText(currPath);
    connect(QLE,&QLineEdit::textChanged,this,&dataPathsRecursive::on_dataPathRecursiveLineEdit_textChanged);
    QHBox->addWidget(QLE);

    paths.push_back(std::make_tuple(QHBox,QLAP,QCB,QLE));
}

void dataPathsRecursive::on_searchButton_clicked()
{
    for(auto path : paths){
        if(std::get<3>(path)->text().contains(ui->patternLineEdit->text())){
            std::get<2>(path)->setChecked(true);
        }
    }
}


void dataPathsRecursive::on_cancelButton_clicked()
{
    dataPathsRecursive::close();
}

