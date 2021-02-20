#ifndef JOBSETTINGS_H
#define JOBSETTINGS_H

#include <QDialog>

namespace Ui {
class jobSettings;
}

class jobSettings : public QDialog
{
    Q_OBJECT

public:
    explicit jobSettings(QWidget *parent = nullptr);
    ~jobSettings();

private:
    Ui::jobSettings *ui;
};

#endif // JOBSETTINGS_H
