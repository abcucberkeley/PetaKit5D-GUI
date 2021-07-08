#include "loadprevioussettings.h"
#include "ui_loadprevioussettings.h"

loadPreviousSettings::loadPreviousSettings(bool &lPS, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadPreviousSettings)
{
    this->lPS = &lPS;
    ui->setupUi(this);
}

loadPreviousSettings::~loadPreviousSettings()
{
    delete ui;
}
void loadPreviousSettings::on_noButton_clicked()
{
    *lPS = false;
    loadPreviousSettings::close();
}

void loadPreviousSettings::on_yesButton_clicked()
{
    *lPS = true;
    loadPreviousSettings::close();
}
