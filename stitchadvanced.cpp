#include "stitchadvanced.h"
#include "ui_stitchadvanced.h"

stitchAdvanced::stitchAdvanced(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stitchAdvanced)
{
    ui->setupUi(this);
}

stitchAdvanced::~stitchAdvanced()
{
    delete ui;
}

void stitchAdvanced::on_cancelButton_clicked()
{
    stitchAdvanced::close();
}

void stitchAdvanced::on_submitButton_clicked()
{
    stitchAdvanced::close();
}
