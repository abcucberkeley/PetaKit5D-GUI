#ifndef SIMRECONRECONADVANCED_H
#define SIMRECONRECONADVANCED_H

#include <QDialog>

namespace Ui {
class simReconReconAdvanced;
}

class simReconReconAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit simReconReconAdvanced(QWidget *parent = nullptr);
    ~simReconReconAdvanced();

private:
    Ui::simReconReconAdvanced *ui;
};

#endif // SIMRECONRECONADVANCED_H
