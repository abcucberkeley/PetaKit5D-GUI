#ifndef DATAPATHS_H
#define DATAPATHS_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <tuple>
#include <QCheckBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QBoxLayout>
#include <iostream>
#include <QSpinBox>
#include <QHash>
#include <QPair>
#include <map>
#include "datapath.h"

namespace Ui {
class dataPaths;
}

class dataPaths : public QDialog
{
    Q_OBJECT

public:
    explicit dataPaths(std::vector<dataPath> &dPaths, bool folder, QString &mostRecentDir, QWidget *parent = nullptr);
    explicit dataPaths(std::vector<QString> &psfPaths, bool folder, QString &mostRecentDir, const std::vector<QString> &channelNames, const bool allowStandardFilename = false, QString *standardFilename = nullptr, QWidget *parent = nullptr);
    dataPaths(std::vector<QString> &dPaths, bool folder, QString &mostRecentDir, const std::vector<QString> &channelNames, const QString &dataType, QWidget *parent = nullptr);
    dataPaths(std::vector<QString> &imageListGeneratorFilenames, std::vector<QString> &imageListGeneratorFileIndices, QWidget *parent = nullptr);
    ~dataPaths();

private slots:
    void on_dataPathAddPathButton_clicked();

    void on_dataPathAddPathButton_clickedOther();

    void on_cancelButton_clicked();

    void on_dataPathSubmitButton_clicked();

    void on_dataPathSubmitButton_clickedOther();

    void on_dataPathSubmitButton_clickedImageListGenerator();

    void on_dataPathBrowseButton_clicked();

    void on_dataPathLineEdit_textChanged(const QString &arg1);

    void on_dataPathFindButton_clicked();

    void on_dataPathRemoveButton_clicked();

    void makeNewPath(int i, dataPath currPath, bool psf = false, QString channelName = QString(), bool otherData = false);

    void makeNewPathImageListGenerator(QString currFilename, std::vector<QString> currIndices);

    int getCurrPathIndex(QString currWidgetName);

    void standardFilenameChecked(bool checked);
private:
    Ui::dataPaths *ui;
    QString *mostRecentDir;
    std::map<QString, dataPath> currPaths;
    int activePaths;
    bool maxPaths;
    bool folder;
    std::vector<std::tuple<QHBoxLayout*, QLabel*, QLineEdit*, QPushButton*, QPushButton*, QLabel*, QLineEdit*,  QLabel*, QSpinBox*, QLabel*, QCheckBox*, QPushButton*>> paths;
    std::vector<std::tuple<QHBoxLayout*, QLabel*, QLabel*, QLineEdit*, QLabel*, QLineEdit*, QLabel*, QLineEdit*, QLabel*, QLineEdit*, QLabel*, QLineEdit*>> pathsImageListGenerator;
    std::vector<dataPath> *dpHand;
    std::vector<QString> *dataHand;
    QString dataType;
    QString *standardFilename;
    std::tuple<QHBoxLayout*, QLabel*, QCheckBox*, QLineEdit*> standardFilenameTuple;
};

#endif // DATAPATHS_H
