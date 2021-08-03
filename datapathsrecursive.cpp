#include "datapathsrecursive.h"
#include "ui_datapathsrecursive.h"
#include <QDirIterator>
#include <iostream>

dataPathsRecursive::dataPathsRecursive(dataPath &currPaths, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPathsRecursive)
{
    ui->setupUi(this);
    this->currPaths = &currPaths.subPaths;
    this->currPath = currPaths.masterPath;
    this->maxDepth = currPaths.maxDepth;

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
        if(checkCount <= currPathDepth+maxDepth  && checkString.contains(QString::fromStdString(currPaths.pattern))){
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
    if(currPaths->find(currPath.toStdString()) != currPaths->end()){
        QCB->setChecked(currPaths->at(currPath.toStdString()).first);
    }
    //connect(QCB,&QCheckBox::stateChanged,this,&dataPaths::on_dataPathCheckBox_stateChanged);
    QHBox->addWidget(QCB);

    // Add the text box
    QLineEdit* QLE = new QLineEdit(this);
    QLE->setText(currPath);
    QLE->setReadOnly(true);
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


void dataPathsRecursive::on_submitButton_clicked()
{
    bool found = false;
    for(const auto &cPath : *currPaths){
        found = false;
        for(const auto &path : paths){
            if(cPath.second.second == std::get<3>(path)->text().toStdString()){
                found = true;
                break;
            }
        }
        if(!found) currPaths->erase(cPath.second.second);
        if(currPaths->empty()) break;
    }

    for(const auto &path : paths){
        if(currPaths->find(std::get<3>(path)->text().toStdString()) == currPaths->end()) currPaths->emplace(std::get<3>(path)->text().toStdString(),std::make_pair(std::get<2>(path)->isChecked(),std::get<3>(path)->text().toStdString()));
        else{
            currPaths->at(std::get<3>(path)->text().toStdString()).first = std::get<2>(path)->isChecked();
        }
    }
    dataPathsRecursive::close();
}


void dataPathsRecursive::on_searchUncheckButton_clicked()
{
    for(auto path : paths){
        if(std::get<3>(path)->text().contains(ui->patternLineEdit->text())){
            std::get<2>(path)->setChecked(false);
        }
    }
}

