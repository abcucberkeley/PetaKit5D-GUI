#ifndef JOBTEXT_H
#define JOBTEXT_H

#include <QDialog>
#include "jobtextmanager.h"

namespace Ui {
class jobText;
}

class jobText : public QDialog
{
    Q_OBJECT

public:
    explicit jobText(QString textFile, QWidget *parent = nullptr);
    ~jobText();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void onUpdateTextWindow();

signals:
    void closeManager();

private:
    Ui::jobText *ui;
    jobTextManager *jTextManager;
    QString textFile;
    bool reading;
};

#endif // JOBTEXT_H
