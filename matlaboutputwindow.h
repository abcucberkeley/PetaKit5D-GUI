#ifndef MATLABOUTPUTWINDOW_H
#define MATLABOUTPUTWINDOW_H

#include <QDialog>
#include <QThread>
#include <QMessageBox>
#include <QHBoxLayout>
#include <unordered_map>
#include "matlaboutputwindowthread.h"

namespace Ui {
class matlabOutputWindow;
}

class matlabOutputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit matlabOutputWindow(QWidget *parent = nullptr);
    ~matlabOutputWindow();
public slots:
    //void onAddButton();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::matlabOutputWindow *ui;
    matlabOutputWindowThread *mOWThread;
    std::vector<std::pair<QHBoxLayout*,QPushButton*>> outputWidgets;
};

#endif // MATLABOUTPUTWINDOW_H
