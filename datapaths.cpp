#include "datapaths.h"
#include "ui_datapaths.h"
#include "datapathsrecursive.h"
#include <QMessageBox>

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

    for(size_t i = 0; i < dpHand->size(); i++){
        currPaths.emplace(dpHand->operator[](i).masterPath,dpHand->operator[](i));
    }
    connect(ui->addPathButton, &QPushButton::clicked, this, &dataPaths::on_dataPathAddPathButton_clicked);
    connect(ui->submitButton, &QPushButton::clicked, this ,&dataPaths::on_dataPathSubmitButton_clicked);

    ui->dataPathsVerticalLayout->addStretch();
    for(size_t i = 0; i < dPaths.size(); i++){
        makeNewPath(i, dpHand->operator[](i));
    }

}

// For PSF data paths
dataPaths::dataPaths(std::vector<QString> &psfPaths, bool folder, QString &mostRecentDir, const std::vector<QString> &channelNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPaths)
{
    ui->setupUi(this);
    this->folder = folder;

    // Most recent folder for browsing
    this->mostRecentDir = &mostRecentDir;

    delete ui->addPathButton;

    // connect slot for psf
    connect(ui->submitButton,&QPushButton::clicked,this,&dataPaths::on_dataPathSubmitButton_clickedOther);

    // pointer to hold the passed in paths vector
    dataHand = &psfPaths;

    ui->dataPathsVerticalLayout->addStretch();
    for(size_t i = 0; i < channelNames.size(); i++){
        makeNewPath(i, dataPath(), true, channelNames[i]);
    }

}

// For other data paths
dataPaths::dataPaths(std::vector<QString> &dPaths, bool folder, QString &mostRecentDir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPaths)
{
    ui->setupUi(this);
    this->folder = folder;

    // Most recent folder for browsing
    this->mostRecentDir = &mostRecentDir;

    // connect slot for data
    connect(ui->submitButton,&QPushButton::clicked,this,&dataPaths::on_dataPathSubmitButton_clickedOther);
    connect(ui->addPathButton,&QPushButton::clicked,this,&dataPaths::on_dataPathAddPathButton_clickedOther);

    // pointer to hold the passed in paths vector
    dataHand = &dPaths;

    ui->dataPathsVerticalLayout->addStretch();
    for(size_t i = 0; i < dPaths.size(); i++){
        makeNewPath(i,dataPath(),false,QString(),true);
    }

}

dataPaths::~dataPaths()
{
    delete ui;
}

// Add a path to the window
void dataPaths::on_dataPathAddPathButton_clicked()
{
    makeNewPath(paths.size(),dataPath());
}

// Add a path to the window (for data other than the main data paths)
void dataPaths::on_dataPathAddPathButton_clickedOther()
{
    makeNewPath(paths.size(),dataPath(),false,QString(),true);
}

// Close the window
void dataPaths::on_cancelButton_clicked()
{
    dataPaths::close();
}

// Close the window and save the values currently in the boxes (even if they are empty currently)
void dataPaths::on_dataPathSubmitButton_clicked()
{
    bool found = false;
    for(const auto &cPath : currPaths){
        if(cPath.second.masterPath.isEmpty()) continue;

        found = false;
        for(const auto &path : paths){
            if(cPath.second.masterPath == std::get<2>(path)->text()){
                found = true;
                break;
            }
        }
        if(!found) currPaths.erase(cPath.second.masterPath);
        if(currPaths.empty()) break;
    }

    for(const auto &path : paths){
        if(std::get<2>(path)->text().isEmpty()) continue;
        if(currPaths.find(std::get<2>(path)->text()) == currPaths.end()){
            currPaths.emplace(std::get<2>(path)->text(),dataPath(std::get<2>(path)->text(),std::get<10>(path)->isChecked(),std::get<6>(path)->text(),std::get<8>(path)->value(),std::unordered_map<QString,std::pair<bool,QString>>()));
        }
        else{
            currPaths[std::get<2>(path)->text()].includeMaster = std::get<10>(path)->isChecked();
            currPaths[std::get<2>(path)->text()].pattern = std::get<6>(path)->text();
            currPaths[std::get<2>(path)->text()].maxDepth = std::get<8>(path)->value();
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

// Close the window and save the values currently in the boxes). Case for PSF/LLFF submitting.
void dataPaths::on_dataPathSubmitButton_clickedOther(){
    dataHand->clear();
    for(const auto &path : paths){
        dataHand->push_back(std::get<2>(path)->text());
    }
    dataPaths::close();
}

// Can probably optimize all these later
// All of these set the data paths based on the selected folder and set the tool tips to the data path
void dataPaths::on_dataPathBrowseButton_clicked()
{
    QLineEdit* currQLE = std::get<2>(paths[getCurrPathIndex(((QPushButton*)sender())->objectName())]);

    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",*mostRecentDir);
        if(!folder_path.absoluteFilePath().isEmpty()){
            currQLE->setText(folder_path.absoluteFilePath());
            *mostRecentDir = folder_path.absoluteFilePath();
        }
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",*mostRecentDir);
        if(!file_path.absoluteFilePath().isEmpty()){
            currQLE->setText(file_path.absoluteFilePath());
            *mostRecentDir = file_path.absolutePath();
        }
    }
}

// Changes the tooltip to be the current text in the LineEdit whenever it is changed
void dataPaths::on_dataPathLineEdit_textChanged(const QString &arg1)
{
    ((QLineEdit*)sender())->setToolTip(arg1);
}

// Searchs for possible subDirs. Opens up a seperate form.
void dataPaths::on_dataPathFindButton_clicked()
{
    int currTuple = getCurrPathIndex(((QPushButton*)sender())->objectName());

    if(std::get<2>(paths[currTuple])->text().isEmpty()){
        QMessageBox messageBox;
        messageBox.warning(0,"Error",QString::fromStdString("Cannot search because the data path box is empty!"));
        messageBox.setFixedSize(500,200);
        return;
    }

    if(currPaths.find(std::get<2>(paths[currTuple])->text()) == currPaths.end()){
        currPaths.emplace(std::get<2>(paths[currTuple])->text(),dataPath(std::get<2>(paths[currTuple])->text(),std::get<10>(paths[currTuple])->isChecked(),std::get<6>(paths[currTuple])->text(),std::get<8>(paths[currTuple])->value(),std::unordered_map<QString,std::pair<bool,QString>>()));
    }
    else{
        currPaths[std::get<2>(paths[currTuple])->text()].includeMaster = std::get<10>(paths[currTuple])->isChecked();
        currPaths[std::get<2>(paths[currTuple])->text()].pattern = std::get<6>(paths[currTuple])->text();
        currPaths[std::get<2>(paths[currTuple])->text()].maxDepth = std::get<8>(paths[currTuple])->value();

    }
    dataPathsRecursive dPR(currPaths[std::get<2>(paths[currTuple])->text()],this);
    dPR.setModal(true);
    dPR.exec();
}

void dataPaths::on_dataPathRemoveButton_clicked()
{
    int currTuple = getCurrPathIndex(((QPushButton*)sender())->objectName());

    // Delete elems in Tuple
    std::get<0>(paths[currTuple])->deleteLater();
    std::get<1>(paths[currTuple])->deleteLater();
    std::get<2>(paths[currTuple])->deleteLater();
    std::get<3>(paths[currTuple])->deleteLater();
    std::get<4>(paths[currTuple])->deleteLater();
    std::get<5>(paths[currTuple])->deleteLater();
    std::get<6>(paths[currTuple])->deleteLater();
    std::get<7>(paths[currTuple])->deleteLater();
    std::get<8>(paths[currTuple])->deleteLater();
    std::get<9>(paths[currTuple])->deleteLater();
    std::get<10>(paths[currTuple])->deleteLater();
    std::get<11>(paths[currTuple])->deleteLater();

    // Erase it from our vector
    paths.erase(paths.begin()+currTuple);

    // Change names of the other tuples
    for(size_t i = currTuple; i < paths.size(); i++){
        std::get<1>(paths[i])->setText(QString("<b>")+QString("Data Path ")+QString::number(i+1)+QString("<\b>"));
        std::get<3>(paths[i])->setObjectName(QString("dataPathBrowseButton")+QString::number(i));
        std::get<4>(paths[i])->setObjectName(QString("dataPathFindButton")+QString::number(i));
        std::get<10>(paths[i])->setObjectName(QString("dataPathCheckBox")+QString::number(i));
        std::get<11>(paths[i])->setObjectName(QString("dataPathRemoveButton")+QString::number(i));
    }

}

void dataPaths::makeNewPath(int i, dataPath currPath, bool psf, QString channelName, bool otherData)
{
    // Add a horizontal layout to the form
    QHBoxLayout* QHBox = new QHBoxLayout(this);
    ui->dataPathsVerticalLayout->insertLayout(ui->dataPathsVerticalLayout->count()-1,QHBox);

    // Add the Path label
    QLabel* QL = new QLabel(this);
    QL->setTextFormat(Qt::RichText);
    if(!psf) QL->setText(QString("<b>")+QString("Data Path ")+QString::number(i+1)+QString("<\b>"));
    else QL->setText(QString("<b>")+channelName+QString("<\b>"));
    QHBox->addWidget(QL);

    // Add the text box
    QLineEdit* QLE = new QLineEdit(this);
    if(!psf && !otherData) QLE->setText(currPath.masterPath);
    else if(size_t(i) < dataHand->size() && !dataHand->operator[](i).isEmpty()) QLE->setText(dataHand->operator[](i));
    QLE->setMinimumWidth(150);
    connect(QLE,&QLineEdit::textChanged,this,&dataPaths::on_dataPathLineEdit_textChanged);
    QHBox->addWidget(QLE);

    // Add browse button
    QPushButton* QPB = new QPushButton(this);
    QPB->setObjectName(QString("dataPathBrowseButton")+QString::number(i));
    QPB->setText("Browse");
    connect(QPB,&QPushButton::clicked,this,&dataPaths::on_dataPathBrowseButton_clicked);
    QHBox->addWidget(QPB);

    // Add Find button
    QPushButton* QPBF = new QPushButton(this);
    QPBF->setObjectName(QString("dataPathFindButton")+QString::number(i));
    QPBF->setText("Find/View SubDirs");
    connect(QPBF,&QPushButton::clicked,this,&dataPaths::on_dataPathFindButton_clicked);
    if(psf || otherData) QPBF->setVisible(false);
    QHBox->addWidget(QPBF);

    // Add the Pattern label
    QLabel* QLP = new QLabel(this);
    QLP->setTextFormat(Qt::RichText);
    QLP->setText("<b>Pattern<\b>");
    if(psf || otherData) QLP->setVisible(false);
    QHBox->addWidget(QLP);

    // Add the text box for Pattern
    QLineEdit* QLEP = new QLineEdit(this);
    QLEP->setText(currPath.pattern);
    //QLEP->setMinimumWidth(150);
    connect(QLEP,&QLineEdit::textChanged,this,&dataPaths::on_dataPathLineEdit_textChanged);
    if(psf || otherData) QLEP->setVisible(false);
    QHBox->addWidget(QLEP);

    // Add the Max Depth label
    QLabel* QLMD = new QLabel(this);
    QLMD->setTextFormat(Qt::RichText);
    QLMD->setText("<b>Max Depth<\b>");
    if(psf || otherData) QLMD->setVisible(false);
    QHBox->addWidget(QLMD);

    // Add the Max Depth SpinBox
    QSpinBox* QSB = new QSpinBox(this);
    QSB->setValue(currPath.maxDepth);
    QSB->setMinimum(1);
    if(psf || otherData) QSB->setVisible(false);
    QHBox->addWidget(QSB);

    // Add the Recurse label
    QLabel* QLR = new QLabel(this);
    QLR->setTextFormat(Qt::RichText);
    QLR->setText("<b>Include Master<\b>");
    QLR->setToolTip("Checking this option will also include this Master folder as a path");
    if(psf || otherData) QLR->setVisible(false);
    QHBox->addWidget(QLR);

    // Add Checkbox
    QCheckBox* QCB = new QCheckBox(this);
    QCB->setObjectName(QString("dataPathCheckBox")+QString::number(i));
    QCB->setChecked(currPath.includeMaster);
    QLR->setToolTip("Checking this option will also include this Master folder as a path");
    if(psf || otherData) QCB->setVisible(false);
    QHBox->addWidget(QCB);

    // Add Remove button
    QPushButton* QPBR = new QPushButton(this);
    QPBR->setObjectName(QString("dataPathRemoveButton")+QString::number(i));
    QPBR->setText("Remove Path");
    connect(QPBR,&QPushButton::clicked,this,&dataPaths::on_dataPathRemoveButton_clicked);
    if(psf) QPBR->setVisible(false);
    QHBox->addWidget(QPBR);

    paths.push_back(std::make_tuple(QHBox,QL,QLE,QPB,QPBF,QLP,QLEP,QLMD,QSB,QLR,QCB,QPBR));
}

int dataPaths::getCurrPathIndex(QString currWidgetName)
{
    int currChar = currWidgetName.size()-1;
    QString currIndexString;
    while(currChar >= 0){
        if(currWidgetName[currChar].isDigit()){
            currIndexString.push_front(currWidgetName[currChar]);
        }
        else break;
        currChar--;
    }
    return currIndexString.toInt();
}
