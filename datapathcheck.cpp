#include "datapathcheck.h"
#include "ui_datapathcheck.h"

dataPathCheck::dataPathCheck(std::unordered_map<QString,std::vector<dataPath>>& jobSplitter, const std::vector<dataPath> &dPaths, const std::vector<QString> &patterns, const QString stepSize, bool &cancel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPathCheck),
    jobSplitter(&jobSplitter),
    cancel(&cancel)
{
    ui->setupUi(this);

    QWidget* containerMain = new QWidget(this);
    mainBox = outputBox(new QScrollArea(this),containerMain,new QVBoxLayout(containerMain));
    mainBox.vBox->addStretch();

    //bool addedPathName = false;
    for(const auto &path : dPaths){
        if(path.includeMaster){
            QDirIterator it(path.masterPath,QDir::Files);
            //addedPathName = false;
            if(it.hasNext()){
                makeNewPath(path.masterPath,stepSize);
                /*
                while(it.hasNext()){
                    QString cFile = it.next();
                    for(const QString &cPattern : patterns){
                        if(cFile.contains(cPattern)){
                            if(!addedPathName){
                            addedPathName = true;
                            makeNewPathName(path.masterPath);
                            }
                            makeNewPath(cFile,stepSize);
                            break;
                        }
                        //QRegularExpression(".*\\.tif");
                    }
                }*/
                //dataPaths_exps[currPath] = factory.createCharArray(path.masterPath.toStdString());
            }
            else std::cout << "WARNING: Data Path: " << path.masterPath.toStdString() << " not included because it contains no files. Continuing." << std::endl;
        }
        for(const auto &subPath : path.subPaths){
            if(subPath.second.first){
                QDirIterator it(subPath.second.second,QDir::Files);
                //addedPathName = false;
                if(it.hasNext()){
                    makeNewPath(path.masterPath,stepSize);
                    /*
                    while(it.hasNext()){
                        QString cFile = it.next();
                        for(const QString &cPattern : patterns){
                            if(cFile.contains(cPattern)){
                                if(!addedPathName){
                                addedPathName = true;
                                makeNewPathName(subPath.second.second);
                                }
                                makeNewPath(cFile,stepSize);
                                break;
                            }
                            //QRegularExpression(".*\\.tif");
                        }
                    }*/
                    //dataPaths_exps[currPath] = factory.createCharArray(subPath.second.second.toStdString());
                }
                else std::cout << "WARNING: Data Path: " << subPath.second.second.toStdString() << " not included because it contains no files. Continuing." << std::endl;
            }
        }
    }



    mainBox.container->setLayout(mainBox.vBox);
    mainBox.scrollArea->setWidget(mainBox.container);

    ui->mainVerticalLayout->addWidget(mainBox.scrollArea);
}

dataPathCheck::~dataPathCheck()
{
    delete ui;
}

/*
void dataPathCheck::makeNewPathName(const QString &pathName){
    QHBoxLayout* nHBox = new QHBoxLayout(this);
    mainBox.vBox->insertLayout(mainBox.vBox->count()-1,nHBox);

    QLabel* dataPathLabel = new QLabel(this);
    dataPathLabel->setText("<b>Main Folder: "+QFileInfo(pathName).baseName()+"<\b>");
    nHBox->addWidget(dataPathLabel);
}*/

void dataPathCheck::makeNewPath(const QString &dPathName, const QString &stepSize){
    QHBoxLayout* nHBox = new QHBoxLayout(this);
    mainBox.vBox->insertLayout(mainBox.vBox->count()-1,nHBox);

    QLabel* dataPathLabel = new QLabel(this);
    dataPathLabel->setText("<b>Data Path<\b>");
    nHBox->addWidget(dataPathLabel);

    QLineEdit* dataPathLineEdit = new QLineEdit(this);
    dataPathLineEdit->setText(dPathName);
    nHBox->addWidget(dataPathLineEdit);

    QLabel* stepSizeLabel = new QLabel(this);
    stepSizeLabel->setText("<b>Step Size<\b>");
    nHBox->addWidget(stepSizeLabel);

    QLineEdit* stepSizeLineEdit = new QLineEdit(this);
    stepSizeLineEdit->setMaximumWidth(40);
    stepSizeLineEdit->setText(stepSize);
    nHBox->addWidget(stepSizeLineEdit);

    lineEdits.push_back(std::make_pair(dataPathLineEdit,stepSizeLineEdit));
}





void dataPathCheck::on_cancelPushButton_clicked()
{
    *cancel = true;
    dataPathCheck::close();
}


void dataPathCheck::on_submitPushButton_clicked()
{
    jobSplitter->clear();
    for(auto &lE : lineEdits){
        if(jobSplitter->find(lE.second->text()) == jobSplitter->end()){
            jobSplitter->emplace(lE.second->text(),std::vector<dataPath>());
        }
        jobSplitter->operator[](lE.second->text()).push_back(dataPath(lE.first->text(),true,QString(),1,std::unordered_map<QString,std::pair<bool, QString>>()));
    }
    dataPathCheck::close();
}

