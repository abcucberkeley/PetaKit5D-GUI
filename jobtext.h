#ifndef JOBTEXT_H
#define JOBTEXT_H

#include <QDialog>

namespace Ui {
class jobText;
}

class jobText : public QDialog
{
    Q_OBJECT

public:
    explicit jobText(QString textFile, QWidget *parent = nullptr);
    ~jobText();

private:
    Ui::jobText *ui;
};

#endif // JOBTEXT_H
