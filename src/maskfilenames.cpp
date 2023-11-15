#include "maskfilenames.h"
#include "ui_maskfilenames.h"

maskFilenames::maskFilenames(std::vector<std::string> &maskNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maskFilenames)
{
    ui->setupUi(this);

    // Pointer to hold the passed in vals
    this->maskNames = &maskNames;

    // Connect button signals
    connect(ui->maskFilenamesXYButton, &QPushButton::clicked, this, &maskFilenames::on_browseButton_clicked);
    connect(ui->maskFilenamesXZButton, &QPushButton::clicked, this, &maskFilenames::on_browseButton_clicked);
    connect(ui->maskFilenamesYZButton,&QPushButton::clicked, this, &maskFilenames::on_browseButton_clicked);

    ui->maskFilenamesXYLineEdit->setText(QString::fromStdString(maskNames.at(0)));
    ui->maskFilenamesXZLineEdit->setText(QString::fromStdString(maskNames.at(1)));
    ui->maskFilenamesYZLineEdit->setText(QString::fromStdString(maskNames.at(2)));
}

maskFilenames::~maskFilenames()
{
    delete ui;
}

void maskFilenames::on_browseButton_clicked()
{
    QFileInfo file_path(QFileDialog::getOpenFileName(this,"Select the File",mostRecentDir));
    if(!file_path.absoluteFilePath().isEmpty()){
        if(((QPushButton *)sender())->objectName().contains("XY")){
            ui->maskFilenamesXYLineEdit->setText(file_path.absoluteFilePath());
        }
        else if(((QPushButton *)sender())->objectName().contains("XZ")){
            ui->maskFilenamesXZLineEdit->setText(file_path.absoluteFilePath());
        }
        else if(((QPushButton *)sender())->objectName().contains("YZ")){
            ui->maskFilenamesYZLineEdit->setText(file_path.absoluteFilePath());
        }
        mostRecentDir = file_path.absolutePath();
    }
}

void maskFilenames::on_cancelButton_clicked()
{
    maskFilenames::close();
}


void maskFilenames::on_submitButton_clicked()
{
    maskNames->at(0) = ui->maskFilenamesXYLineEdit->text().toStdString();
    maskNames->at(1) = ui->maskFilenamesXZLineEdit->text().toStdString();
    maskNames->at(2) = ui->maskFilenamesYZLineEdit->text().toStdString();
    maskFilenames::close();
}

