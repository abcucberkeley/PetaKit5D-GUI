#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

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
    explicit consoleOutput(std::shared_ptr<SBuf> &output, QWidget *parent = nullptr);
    ~consoleOutput();

public slots:
    void readConsole();

private:
    std::shared_ptr<SBuf> *output;
    Ui::consoleOutput *ui;
};

#endif // CONSOLEOUTPUT_H
