#ifndef SUBMISSIONCHECKS_H
#define SUBMISSIONCHECKS_H
#include "mainwindow.h"
#include <QString>
#include <QDir>
#include <QFileDevice>
#include <QCheckBox>
#include <QLineEdit>
#include <QSettings>
#include <iostream>

void checkJobLogDir(QString &jobLogDir, QString &mainPath, const QString &timeJobName);

void messageBoxError(const QString &errorText);

void messageBoxSuccess(QWidget* parent, const QString &successText);

bool messageBoxParseClusterWarning(QWidget* parent, const bool parseCluster, bool &enabled, const configFileVals &cFileVals);

bool messageBoxSameJobSubmittedWarning(QWidget* parent,
                                       std::pair<std::string,std::string> &prevFuncTypeArgs,
                                       const std::string &funcType, const std::string &args, bool &enabled);

bool dataPathsAreSet(const std::vector<dataPath> &dPaths);

bool channelPatternsAreSet(const std::vector<std::pair<QLabel*,QCheckBox*>> &channelWidgets, const QCheckBox* customPatternsCheckBox, const QLineEdit* customPatternsLineEdit);

bool pathsFound(dataPath& path);

bool settingsFileExists();

#endif // SUBMISSIONCHECKS_H
