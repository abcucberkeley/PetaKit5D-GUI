#include "datapaths.h"
#include "ui_datapaths.h"
#include <QFileInfo>
#include <QFileDialog>


//*** This form is too hardcoded. Qt has better ways to handle what we need here
// but this is a quick solution to help get things running.

// folder dicatates whether we are getting folders or files so I can use this form for 2 different situations.
dataPaths::dataPaths(std::vector<std::string> &dPaths, bool folder, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPaths)
{
    ui->setupUi(this);
    this->folder = folder;

    // pointer to hold the passed in paths vector
    dpHand = &dPaths;

    // if there are no current data paths in the vector set it to 1
    // else its the size of how data paths there are
    if(dPaths.size() == 0) activePaths = 1;
    else activePaths = dPaths.size();

    // Check if max paths
    if(activePaths < 6) maxPaths = false;
    else maxPaths = true;

    // structure to hold widgets on the screen so we can turn them on and off
    paths.push_back(std::make_tuple(ui->dataPath1Label,ui->dataPath1LineEdit,ui->dataPath1BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath2Label,ui->dataPath2LineEdit,ui->dataPath2BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath3Label,ui->dataPath3LineEdit,ui->dataPath3BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath4Label,ui->dataPath4LineEdit,ui->dataPath4BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath5Label,ui->dataPath5LineEdit,ui->dataPath5BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath6Label,ui->dataPath6LineEdit,ui->dataPath6BrowseButton));

    // Initial visibility of the widgets
    for(size_t i = 0; i < paths.size(); i++){
        if(i == 0 && dPaths.size() == 0) continue;
        else if(i < dPaths.size()){
            std::get<1>(paths.at(i))->setText(QString::fromStdString(dPaths.at(i)));
        }
        else{
            std::get<0>(paths.at(i))->setVisible(false);
            std::get<1>(paths.at(i))->setVisible(false);
            std::get<2>(paths.at(i))->setVisible(false);
        }
    }
}

// For PSF data paths
dataPaths::dataPaths(std::vector<std::string> &dPaths, bool folder, const size_t &channels, const std::vector<QString> &channelNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPaths)
{
    ui->setupUi(this);
    this->folder = folder;

    delete ui->addPathButton;
    delete ui->removePathButton;


    // pointer to hold the passed in paths vector
    dpHand = &dPaths;

    // if there are no current data paths in the vector set it to 1
    // else its the size of how data paths there are
    if(dPaths.size() == 0) activePaths = 1;
    else activePaths = channels;

    // Check if max paths
    if(activePaths < 6) maxPaths = false;
    else maxPaths = true;

    // structure to hold widgets on the screen so we can turn them on and off
    paths.push_back(std::make_tuple(ui->dataPath1Label,ui->dataPath1LineEdit,ui->dataPath1BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath2Label,ui->dataPath2LineEdit,ui->dataPath2BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath3Label,ui->dataPath3LineEdit,ui->dataPath3BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath4Label,ui->dataPath4LineEdit,ui->dataPath4BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath5Label,ui->dataPath5LineEdit,ui->dataPath5BrowseButton));
    paths.push_back(std::make_tuple(ui->dataPath6Label,ui->dataPath6LineEdit,ui->dataPath6BrowseButton));

    // Initial visibility of the widgets
    for(size_t i = 0; i < paths.size(); i++){
        if(i == 0 && channels == 0) continue;
        else if(i < channels){
            std::get<0>(paths.at(i))->setTextFormat(Qt::RichText);
            std::get<0>(paths.at(i))->setText(channelNames.at(i));
            if(i < dPaths.size()) std::get<1>(paths.at(i))->setText(QString::fromStdString(dPaths.at(i)));
        }
        else{
            std::get<0>(paths.at(i))->setVisible(false);
            std::get<1>(paths.at(i))->setVisible(false);
            std::get<2>(paths.at(i))->setVisible(false);
        }
    }
}

dataPaths::~dataPaths()
{
    delete ui;
}

// Add a path to the window
void dataPaths::on_addPathButton_clicked()
{

    if(maxPaths) return;

    std::get<0>(paths.at(activePaths))->setVisible(true);
    std::get<1>(paths.at(activePaths))->setVisible(true);
    std::get<2>(paths.at(activePaths))->setVisible(true);
    activePaths++;

    if((size_t)activePaths == paths.size()){
        maxPaths = true;
    }

}

// Remove a path from the window
void dataPaths::on_removePathButton_clicked()
{
    if(activePaths == 1) return;

    if(maxPaths) maxPaths = false;
    activePaths--;

    std::get<0>(paths.at(activePaths))->setVisible(false);
    std::get<1>(paths.at(activePaths))->setVisible(false);
    std::get<2>(paths.at(activePaths))->setVisible(false);

}

// Close the window
void dataPaths::on_cancelButton_clicked()
{
    dataPaths::close();
}

// Close the window and save the values currently in the boxes (even if they are empty currently)
void dataPaths::on_submitButton_clicked()
{
    if(dpHand->size() != (size_t)activePaths){
        dpHand->resize(activePaths);
    }
    for(size_t i = 0; i < dpHand->size(); i++){
        dpHand->at(i) = std::get<1>(paths.at(i))->text().toStdString();
    }
    dataPaths::close();
}

// Can probably optimize all these later
// All of these set the data paths based on the selected folder and set the tool tips to the data path
void dataPaths::on_dataPath1BrowseButton_clicked()
{
    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",QDir::homePath());
        if(folder_path.absoluteFilePath().toStdString() != "") ui->dataPath1LineEdit->setText(folder_path.absoluteFilePath());
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",QDir::homePath());
        if(file_path.absoluteFilePath().toStdString() != "") ui->dataPath1LineEdit->setText(file_path.absoluteFilePath());
    }
}

void dataPaths::on_dataPath1LineEdit_textChanged(const QString &arg1)
{
    ui->dataPath1LineEdit->setToolTip(arg1);
}

void dataPaths::on_dataPath2BrowseButton_clicked()
{
    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",QDir::homePath());
        if(folder_path.absoluteFilePath().toStdString() != "") ui->dataPath2LineEdit->setText(folder_path.absoluteFilePath());
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",QDir::homePath());
        if(file_path.absoluteFilePath().toStdString() != "") ui->dataPath2LineEdit->setText(file_path.absoluteFilePath());
    }
}

void dataPaths::on_dataPath2LineEdit_textChanged(const QString &arg1)
{
    ui->dataPath2LineEdit->setToolTip(arg1);
}

void dataPaths::on_dataPath3BrowseButton_clicked()
{
    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",QDir::homePath());
        if(folder_path.absoluteFilePath().toStdString() != "") ui->dataPath3LineEdit->setText(folder_path.absoluteFilePath());
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",QDir::homePath());
        if(file_path.absoluteFilePath().toStdString() != "") ui->dataPath3LineEdit->setText(file_path.absoluteFilePath());
    }
}

void dataPaths::on_dataPath3LineEdit_textChanged(const QString &arg1)
{
    ui->dataPath3LineEdit->setToolTip(arg1);
}

void dataPaths::on_dataPath4BrowseButton_clicked()
{
    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",QDir::homePath());
        if(folder_path.absoluteFilePath().toStdString() != "") ui->dataPath4LineEdit->setText(folder_path.absoluteFilePath());
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",QDir::homePath());
        if(file_path.absoluteFilePath().toStdString() != "") ui->dataPath4LineEdit->setText(file_path.absoluteFilePath());
    }
}

void dataPaths::on_dataPath4LineEdit_textChanged(const QString &arg1)
{
    ui->dataPath4LineEdit->setToolTip(arg1);
}

void dataPaths::on_dataPath5BrowseButton_clicked()
{
    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",QDir::homePath());
        if(folder_path.absoluteFilePath().toStdString() != "") ui->dataPath5LineEdit->setText(folder_path.absoluteFilePath());
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",QDir::homePath());
        if(file_path.absoluteFilePath().toStdString() != "") ui->dataPath5LineEdit->setText(file_path.absoluteFilePath());
    }
}

void dataPaths::on_dataPath5LineEdit_textChanged(const QString &arg1)
{
    ui->dataPath5LineEdit->setToolTip(arg1);
}

void dataPaths::on_dataPath6BrowseButton_clicked()
{
    if(folder){
        QFileInfo folder_path = QFileDialog::getExistingDirectory(this,"Select the Data Folder",QDir::homePath());
        if(folder_path.absoluteFilePath().toStdString() != "") ui->dataPath6LineEdit->setText(folder_path.absoluteFilePath());
    }
    else{
        QFileInfo file_path = QFileDialog::getOpenFileName(this,"Select the Data File",QDir::homePath());
        if(file_path.absoluteFilePath().toStdString() != "") ui->dataPath6LineEdit->setText(file_path.absoluteFilePath());
    }
}

void dataPaths::on_dataPath6LineEdit_textChanged(const QString &arg1)
{
    ui->dataPath6LineEdit->setToolTip(arg1);
}
