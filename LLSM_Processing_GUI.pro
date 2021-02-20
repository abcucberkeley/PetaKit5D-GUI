QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    consoleoutput.cpp \
    datapaths.cpp \
    deconadvanced.cpp \
    dsradvanced.cpp \
    jobadvanced.cpp \
    main.cpp \
    mainadvanced.cpp \
    mainwindow.cpp \
    matlabthread.cpp

HEADERS += \
    consoleoutput.h \
    datapaths.h \
    deconadvanced.h \
    dsradvanced.h \
    jobadvanced.h \
    mainadvanced.h \
    mainwindow.h \
    matlabthread.h

FORMS += \
    consoleoutput.ui \
    datapaths.ui \
    deconadvanced.ui \
    dsradvanced.ui \
    jobadvanced.ui \
    mainadvanced.ui \
    mainwindow.ui

LIBS += -L"C:/Program Files/MATLAB/R2020b/extern/lib/win64/mingw64" -llibeng \
        -L"C:/Program Files/MATLAB/R2020b/extern/lib/win64/mingw64" -llibmx \
        -L"C:/Program Files/MATLAB/R2020b/extern/lib/win64/mingw64" -llibMatlabEngine \
        -L"C:/Program Files/MATLAB/R2020b/extern/lib/win64/mingw64" -llibMatlabDataArray


INCLUDEPATH += "C:/Program Files/MATLAB/R2020b/extern/include"


TRANSLATIONS += \
    GUI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
