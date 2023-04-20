#include <QtTest/QtTest>
//"../LLSM_Processing_GUI/mainwindow.h"
#include<mainwindow.h>

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void testDefaultWindowTitle()
    {
        MainWindow mainWindow;
        QCOMPARE(mainWindow.windowTitle(), QString("LLSM Processing GUI"));
    }

    void testSetWindowTitle()
    {
        MainWindow mainWindow;
        mainWindow.setWindowTitle("New Window Title");
        QCOMPARE(mainWindow.windowTitle(), QString("New Window Title"));
    }
    void testDefaultWindowTitle()
    {
        MainWindow mainWindow;
        QCOMPARE(mainWindow.windowTitle(), QString("LLSM Processing GUI"));
    }

    void testSetWindowTitle()
    {
        MainWindow mainWindow;
        mainWindow.setWindowTitle("New Window Title");
        QCOMPARE(mainWindow.windowTitle(), QString("New Window Title"));
    }

    void testLoadDataButton()
    {
        MainWindow mainWindow;
        QSignalSpy spy(&mainWindow, SIGNAL(loadDataButtonClicked()));
        QPushButton* loadDataButton = mainWindow.findChild<QPushButton*>("loadDataButton");
        QTest::mouseClick(loadDataButton, Qt::LeftButton);
        QCOMPARE(spy.count(), 1);
    }

    void testProcessDataButton()
    {
        MainWindow mainWindow;
        QSignalSpy spy(&mainWindow, SIGNAL(processDataButtonClicked()));
        QPushButton* processDataButton = mainWindow.findChild<QPushButton*>("processDataButton");
        QTest::mouseClick(processDataButton, Qt::LeftButton);
        QCOMPARE(spy.count(), 1);
    }
    void testDefaultWindowTitle()
    {
        MainWindow mainWindow;
        QCOMPARE(mainWindow.windowTitle(), QString("LLSM Processing GUI"));
    }

    void testSetWindowTitle()
    {
        MainWindow mainWindow;
        mainWindow.setWindowTitle("New Window Title");
        QCOMPARE(mainWindow.windowTitle(), QString("New Window Title"));
    }

    void testLoadDataButton()
    {
        MainWindow mainWindow;
        QSignalSpy spy(&mainWindow, SIGNAL(loadDataButtonClicked()));
        QPushButton* loadDataButton = mainWindow.findChild<QPushButton*>("loadDataButton");
        QTest::mouseClick(loadDataButton, Qt::LeftButton);
        QCOMPARE(spy.count(), 1);
    }

    void testProcessDataButton()
    {
        MainWindow mainWindow;
        QSignalSpy spy(&mainWindow, SIGNAL(processDataButtonClicked()));
        QPushButton* processDataButton = mainWindow.findChild<QPushButton*>("processDataButton");
        QTest::mouseClick(processDataButton, Qt::LeftButton);
        QCOMPARE(spy.count(), 1);
    }

    void testFileMenu()
    {
        MainWindow mainWindow;
        QMenu* fileMenu = mainWindow.findChild<QMenu*>("menuFile");
        QAction* openAction = fileMenu->findChild<QAction*>("actionOpen");
        QVERIFY(openAction != nullptr);
        QAction* saveAction = fileMenu->findChild<QAction*>("actionSave");
        QVERIFY(saveAction != nullptr);
        QAction* exitAction = fileMenu->findChild<QAction*>("actionExit");
        QVERIFY(exitAction != nullptr);
    }

    void testHelpMenu()
    {
        MainWindow mainWindow;
        QMenu* helpMenu = mainWindow.findChild<QMenu*>("menuHelp");
        QAction* aboutAction = helpMenu->findChild<QAction*>("actionAbout");
        QVERIFY(aboutAction != nullptr);
    }
    void testProcessingOptionsGroupBox()
    {
        MainWindow mainWindow;
        QGroupBox* processingOptionsGroupBox = mainWindow.findChild<QGroupBox*>("processingOptionsGroupBox");
        QVERIFY(processingOptionsGroupBox != nullptr);
        QCOMPARE(processingOptionsGroupBox->title(), QString("Processing Options"));
    }

    void testShowIntermediateResultsCheckBox()
    {
        MainWindow mainWindow;
        QCheckBox* showIntermediateResultsCheckBox = mainWindow.findChild<QCheckBox*>("showIntermediateResultsCheckBox");
        QVERIFY(showIntermediateResultsCheckBox != nullptr);
        QCOMPARE(showIntermediateResultsCheckBox->text(), QString("Show Intermediate Results"));
    }

    void testLogFileLineEdit()
    {
        MainWindow mainWindow;
        QLineEdit* logFileLineEdit = mainWindow.findChild<QLineEdit*>("logFileLineEdit");
        QVERIFY(logFileLineEdit != nullptr);
        QCOMPARE(logFileLineEdit->text(), QString(""));
    }
};
