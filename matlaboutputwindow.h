#ifndef MATLABOUTPUTWINDOW_H
#define MATLABOUTPUTWINDOW_H

#include <QDialog>
#include <QThread>
#include <QMessageBox>
#include <QHBoxLayout>

namespace Ui {
class matlabOutputWindow;
}

class matlabOutputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit matlabOutputWindow(QWidget *parent = nullptr);
    ~matlabOutputWindow();

private:
    Ui::matlabOutputWindow *ui;
    std::vector<std::pair<QHBoxLayout*,QPushButton*>> outputWidgets;
};

#endif // MATLABOUTPUTWINDOW_H
