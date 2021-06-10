#ifndef STITCHADVANCED_H
#define STITCHADVANCED_H

#include <QDialog>

namespace Ui {
class stitchAdvanced;
}

class stitchAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit stitchAdvanced(QWidget *parent = nullptr);
    ~stitchAdvanced();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::stitchAdvanced *ui;
};

#endif // STITCHADVANCED_H
