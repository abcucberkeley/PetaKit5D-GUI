#include "datapaths.h"
#include "ui_datapaths.h"
#include "datapathsrecursive.h"
#include <QMessageBox>




//*** This form is too hardcoded. Qt has better ways to handle what we need here
// but this is a quick solution to help get things running.

// folder dicatates whether we are getting folders or files so I can use this form for 2 different situations.
dataPaths::dataPaths(std::vector<dataPath> &dPaths, bool folder, QString &mostRecentDir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPaths)
{
    ui->setupUi(this);
    this->folder = folder;

    // Most recent folder for browsing
    this->mostRecentDir = &mostRecentDir;

    // pointer to hold the passed in paths vector
    dpHand = &dPaths;

    //***********************NEW*******************
    ui->dataPathsVerticalLayout->addStretch();
    for(size_t i = 0; i < dPaths.size(); i++){
        makeNewPath(i,dpHand->at(i));
    }

    //ui->dataPathsVerticalLayout->addStretch();

}

// For PSF data paths
dataPaths::dataPaths(std::vector<std::string> &dPaths, bool folder, QString &mostRecentDir, const size_t &channels, const std::vector<QString> &channelNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPaths)
{
    ui->setupUi(this);
    this->folder = folder;

    // Most recent folder for browsing
    this->mostRecentDir = &mostRecentDir;

    delete ui->addPathButton;
    //delete ui->removePathButton;


    // pointer to hold the passed in paths vector
    //dpHand = &dPaths;

    // if there are no current data paths in the vector set it to 1
    // else its the size of how data paths there are
    if(!channels) activePaths = 1;
    else activePaths = channels;

    // Check if max paths
    if(activePaths < 6) maxPaths = false;
    else maxPaths = true;

    // structure to hold widgets on the screen so we can turn them on and off
    //paths.push_back(std::make_tuple(ui->dataPath1Label,ui->dataPath1LineEdit,ui->dataPath1BrowseButton));

}

dataPaths::~dataPaths()
{
    delete ui;
}

// Add a path to the window
void dataPaths::on_addPathButton_clicked()
{
    makeNewPath(paths.size(),dataPath());
    //ui->dataPathsVerticalLayout->addStretch();
}

// Close the window
void dataPaths::on_cancelButton_clicked()
{
    dataPaths::close();
}

// Close the window and save the values currently in the boxes (even if they are empty currently)
void dataPaths::on_submitButton_clicked()
{

    bool found = false;
    for(const auto &cPath : currPaths){
        if(cPath.second.masterPath.empty()) continue;

        found = false;
        for(const auto &path : paths){
            if(cPath.second.masterPath == std::get<2>(path)->text().toStdString()){
                found = true;
                break;
            }
        }
        if(!found) currPaths.erase(cPath.second.masterPath);
    }


    for(const auto &path : paths){
        if(std::get<2>(path)->text().isEmpty()) continue;
        if(currPaths.find(std::get<2>(path)->text().toStdString()) == currPaths.end()){
            currPaths.emplace(std::get<2>(path)->text().toStdString(),dataPath(std::get<2>(path)->text().toStdString(),std::get<10>(path)->isChecked(),std::get<6>(path)->text().toStdString(),std::get<8>(path)->value(),std::unordered_map<std::string,std::pair<bool,std::string>>()));
        }
    }

    // TODO: Add handling for multiple paths that have the same name****************

    dpHand->clear();
    for(const auto &path : currPaths){
        dpHand->push_back(path.second);
    }
    std::sort(dpHand->begin(),dpHand->end());

    dataPaths::close();
}

// Can probably optimize all these later
// All of these set the data paths based on the selected folder and set the tool tips to the data path
void dataPaths::on_dataPathBrowseButton_clicked()
{
    // Get last char of senders string so we can access it.
    QLineEdit* currQLE = std::get<2>(paths.at(QString(((QPushButton*)sender())->objectName().back()).toInt()));

    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",*mostRecentDir);
        if(folder_path.absoluteFilePath().toStdString() != ""){
            currQLE->setText(folder_path.absoluteFilePath());
            *mostRecentDir = folder_path.absoluteFilePath();
        }
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",*mostRecentDir);
        if(file_path.absoluteFilePath().toStdString() != ""){
           currQLE->setText(file_path.absoluteFilePath());
            *mostRecentDir = file_path.absolutePath();
        }
    }
}

void dataPaths::on_dataPathLineEdit_textChanged(const QString &arg1)
{
    ((QLineEdit*)sender())->setToolTip(arg1);
}

void dataPaths::on_dataPathFindButton_clicked(){
    //int elemsInTuple = 9;
    int currTuple = QString(((QPushButton*)sender())->objectName().back()).toInt();

    if(std::get<2>(paths.at(currTuple))->text().isEmpty()){
        QMessageBox messageBox;
        messageBox.warning(0,"Error",QString::fromStdString("Cannot search because the data path box is empty!"));
        messageBox.setFixedSize(500,200);
        return;
    }

    if(currPaths.find(std::get<2>(paths.at(currTuple))->text().toStdString()) == currPaths.end()){
        currPaths.emplace(std::get<2>(paths.at(currTuple))->text().toStdString(),dataPath(std::get<2>(paths.at(currTuple))->text().toStdString(),std::get<10>(paths.at(currTuple))->isChecked(),std::get<6>(paths.at(currTuple))->text().toStdString(),std::get<8>(paths.at(currTuple))->value(),std::unordered_map<std::string,std::pair<bool,std::string>>()));
    }
    else{
        currPaths.at(std::get<2>(paths.at(currTuple))->text().toStdString()).includeMaster = std::get<10>(paths.at(currTuple))->isChecked();
        currPaths.at(std::get<2>(paths.at(currTuple))->text().toStdString()).pattern = std::get<6>(paths.at(currTuple))->text().toStdString();
        currPaths.at(std::get<2>(paths.at(currTuple))->text().toStdString()).maxDepth = std::get<8>(paths.at(currTuple))->value();

    }
    dataPathsRecursive dPR(currPaths.at(std::get<2>(paths.at(currTuple))->text().toStdString()),this);
    dPR.setModal(true);
    dPR.exec();
}

void dataPaths::on_dataPathRemoveButton_clicked(){
    //int elemsInTuple = 9;
    int currTuple = QString(((QPushButton*)sender())->objectName().back()).toInt();
    // Delete elems in Tuple
    std::get<0>(paths.at(currTuple))->deleteLater();
    std::get<1>(paths.at(currTuple))->deleteLater();
    std::get<2>(paths.at(currTuple))->deleteLater();
    std::get<3>(paths.at(currTuple))->deleteLater();
    std::get<4>(paths.at(currTuple))->deleteLater();
    std::get<5>(paths.at(currTuple))->deleteLater();
    std::get<6>(paths.at(currTuple))->deleteLater();
    std::get<7>(paths.at(currTuple))->deleteLater();
    std::get<8>(paths.at(currTuple))->deleteLater();
    std::get<9>(paths.at(currTuple))->deleteLater();
    std::get<10>(paths.at(currTuple))->deleteLater();
    std::get<11>(paths.at(currTuple))->deleteLater();

    // Erase it from our vector
    paths.erase(paths.begin()+currTuple);

    // Change names of the other tuples
    for(size_t i = currTuple; i < paths.size(); i++){
        std::get<1>(paths.at(i))->setText(QString("<b>")+QString("Data Path ")+QString::number(i+1)+QString("<\b>"));
        std::get<3>(paths.at(i))->setObjectName(QString("dataPathBrowseButton")+QString::number(i));
        std::get<4>(paths.at(i))->setObjectName(QString("dataPathFindButton")+QString::number(i));
        std::get<10>(paths.at(i))->setObjectName(QString("dataPathCheckBox")+QString::number(i));
        std::get<11>(paths.at(i))->setObjectName(QString("dataPathRemoveButton")+QString::number(i));
    }

}

void dataPaths::on_dataPathCheckBox_stateChanged(int checked){
    // Enable or disable recurse widgets
    int currTuple = QString(((QCheckBox*)sender())->objectName().back()).toInt();
    std::get<3>(paths.at(currTuple))->setEnabled(checked);
    std::get<4>(paths.at(currTuple))->setEnabled(checked);
}

void dataPaths::makeNewPath(int i, dataPath currPath){
    // Add a horizontal layout to the form
    QHBoxLayout* QHBox = new QHBoxLayout(this);
    ui->dataPathsVerticalLayout->insertLayout(ui->dataPathsVerticalLayout->count()-1,QHBox);
    //ui->dataPathsVerticalLayout->addLayout(QHBox);

    // Add the Path label
    QLabel* QL = new QLabel(this);
    QL->setTextFormat(Qt::RichText);
    QL->setText(QString("<b>")+QString("Data Path ")+QString::number(i+1)+QString("<\b>"));
    QHBox->addWidget(QL);

    // Add the text box
    QLineEdit* QLE = new QLineEdit(this);
    QLE->setText(QString::fromStdString(currPath.masterPath));
    QLE->setMinimumWidth(150);
    connect(QLE,&QLineEdit::textChanged,this,&dataPaths::on_dataPathLineEdit_textChanged);
    QHBox->addWidget(QLE);

    // Add browse button
    QPushButton* QPB = new QPushButton(this);
    QPB->setObjectName(QString("dataPathBrowseButton")+QString::number(i));
    QPB->setText("Browse");
    //QPB->setMaximumWidth(50);
    connect(QPB,&QPushButton::clicked,this,&dataPaths::on_dataPathBrowseButton_clicked);
    QHBox->addWidget(QPB);

    // Add Find button
    QPushButton* QPBF = new QPushButton(this);
    QPBF->setObjectName(QString("dataPathFindButton")+QString::number(i));
    QPBF->setText("Find/View SubDirs");
    connect(QPBF,&QPushButton::clicked,this,&dataPaths::on_dataPathFindButton_clicked);
    QHBox->addWidget(QPBF);

    // Add the Pattern label
    QLabel* QLP = new QLabel(this);
    QLP->setTextFormat(Qt::RichText);
    QLP->setText("<b>Pattern<\b>");
    QHBox->addWidget(QLP);

    // Add the text box for Pattern
    QLineEdit* QLEP = new QLineEdit(this);
    QLEP->setText(QString::fromStdString(currPath.pattern));
    //QLEP->setMinimumWidth(150);
    connect(QLEP,&QLineEdit::textChanged,this,&dataPaths::on_dataPathLineEdit_textChanged);
    QHBox->addWidget(QLEP);

    // Add the Max Depth label
    QLabel* QLMD = new QLabel(this);
    QLMD->setTextFormat(Qt::RichText);
    QLMD->setText("<b>Max Depth<\b>");
    QHBox->addWidget(QLMD);

    // Add the Max Depth SpinBox
    QSpinBox* QSB = new QSpinBox(this);
    QSB->setValue(currPath.maxDepth);
    QSB->setMinimum(1);
    QHBox->addWidget(QSB);

    // Add the Recurse label
    QLabel* QLR = new QLabel(this);
    QLR->setTextFormat(Qt::RichText);
    QLR->setText("<b>Include Master<\b>");
    QLR->setToolTip("Checking this option will also include this Master folder as a path");
    QHBox->addWidget(QLR);

    // Add Checkbox
    QCheckBox* QCB = new QCheckBox(this);
    QCB->setObjectName(QString("dataPathCheckBox")+QString::number(i));
    QCB->setChecked(currPath.includeMaster);
    //connect(QCB,&QCheckBox::stateChanged,this,&dataPaths::on_dataPathCheckBox_stateChanged);
    QLR->setToolTip("Checking this option will also include this Master folder as a path");
    QHBox->addWidget(QCB);

    // Add Remove button
    QPushButton* QPBR = new QPushButton(this);
    QPBR->setObjectName(QString("dataPathRemoveButton")+QString::number(i));
    QPBR->setText("Remove Path");
    connect(QPBR,&QPushButton::clicked,this,&dataPaths::on_dataPathRemoveButton_clicked);
    QHBox->addWidget(QPBR);

    paths.push_back(std::make_tuple(QHBox,QL,QLE,QPB,QPBF,QLP,QLEP,QLMD,QSB,QLR,QCB,QPBR));
}
