#ifndef STITCHADVANCED_H
#define STITCHADVANCED_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class stitchAdvanced;
}

class stitchAdvanced : public QDialog
{
    Q_OBJECT

public:
    explicit stitchAdvanced(GUIvals &guiVals, QString &mostRecentDir,
                            const std::vector<std::pair<QLabel*,QCheckBox*>> &channelWidgets,
                            const bool &customPatternsCheckBox, const QString &customPatternsLineEdit,
                            QWidget *parent = nullptr);
    ~stitchAdvanced();

private slots:

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_boundBoxCheckBox_stateChanged(int arg1);

    void on_distBboxesCheckBox_stateChanged(int arg1);

    void on_stitchInfoFullPathBrowseButton_clicked();

    void on_stitchFFImagePathsButton_clicked();

    void on_stitchBackgroundPathsButton_clicked();

    void on_processFunPathCheckBox_stateChanged(int arg1);

private:
    Ui::stitchAdvanced *ui;
    GUIvals* gVals;
    QString* mostRecentDir;
    const std::vector<std::pair<QLabel*,QCheckBox*>> channelWidgets;
    const bool customPatternsCheckBox;
    const QString customPatternsLineEdit;
};

#endif // STITCHADVANCED_H
