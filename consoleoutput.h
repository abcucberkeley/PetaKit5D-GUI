#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include "consolethread.h"
#include <QDialog>
#include <QProcess>
using SBuf = std::basic_stringbuf<char16_t>;

namespace Ui {
class consoleOutput;
}

class consoleOutput : public QDialog
{
    Q_OBJECT

public:
    explicit consoleOutput(QWidget *parent = nullptr);
    ~consoleOutput();

public slots:
    void getOutput(const QString &output);

private:
    consoleThread *cThread;
    Ui::consoleOutput *ui;
};

#endif // CONSOLEOUTPUT_H
