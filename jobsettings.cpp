#include "jobsettings.h"
#include "ui_jobsettings.h"

jobSettings::jobSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jobSettings)
{
    ui->setupUi(this);
}

jobSettings::~jobSettings()
{
    delete ui;
}
