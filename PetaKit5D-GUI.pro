######################################################################
# Automatically generated by qmake (3.0) Thu Feb 25 16:11:28 2021
######################################################################
TEMPLATE = app
TARGET = PetaKit5D-GUI
QT += widgets

CONFIG += c++17

# Input
HEADERS += \
        src/configfilecreator.h \
        src/configfilesettings.h \
        src/datapath.h \
        src/datapaths.h \
        src/datapathsrecursive.h \
        src/deconadvanced.h \
        src/dsradvanced.h \
        src/jobadvanced.h \
        src/jobtext.h \
        src/jobtextmanager.h \
        src/largescaleprocessingsettings.h \
        src/mainadvanced.h \
        src/mainwindow.h \
        src/mainwindowconsoleoutputwindow.h \
        src/maskfilenames.h \
        src/matlabhelperfunctions.h \
        src/matlaboutputwindow.h \
        src/matlaboutputwindowthread.h \
        src/matlabthread.h \
        src/matlabthreadmanager.h \
        src/loadprevioussettings.h \
        src/outputbox.h \
        src/simreconjobadvanced.h \
        src/simreconmainadvanced.h \
        src/simreconreconadvanced.h \
        src/stitchadvanced.h \
        src/submissionchecks.h

FORMS += \
        src/configfilecreator.ui \
        src/configfilesettings.ui \
        src/datapaths.ui \
        src/datapathsrecursive.ui \
        src/deconadvanced.ui \
        src/dsradvanced.ui \
        src/jobadvanced.ui \
        src/jobtext.ui \
        src/largescaleprocessingsettings.ui \
        src/mainadvanced.ui \
        src/mainwindow.ui \
        src/maskfilenames.ui \
        src/matlaboutputwindow.ui \
        src/loadprevioussettings.ui \
        src/simreconjobadvanced.ui \
        src/simreconmainadvanced.ui \
        src/simreconreconadvanced.ui \
        src/stitchadvanced.ui

SOURCES += \
        src/configfilecreator.cpp \
        src/configfilesettings.cpp \
        src/datapath.cpp \
        src/datapaths.cpp \
        src/datapathsrecursive.cpp \
        src/deconadvanced.cpp \
        src/dsradvanced.cpp \
        src/jobadvanced.cpp \
        src/jobtext.cpp \
        src/jobtextmanager.cpp \
        src/largescaleprocessingsettings.cpp \
        src/main.cpp \
        src/mainadvanced.cpp \
        src/mainwindow.cpp \
        src/mainwindowconsoleoutputwindow.cpp \
        src/maskfilenames.cpp \
        src/matlabhelperfunctions.cpp \
        src/matlaboutputwindow.cpp \
        src/matlaboutputwindowthread.cpp \
        src/matlabthread.cpp \
        src/matlabthreadmanager.cpp \
        src/loadprevioussettings.cpp \
        src/outputbox.cpp \
        src/simreconjobadvanced.cpp \
        src/simreconmainadvanced.cpp \
        src/simreconreconadvanced.cpp \
        src/stitchadvanced.cpp \
        src/submissionchecks.cpp

RESOURCES += \
    resources.qrc

TRANSLATIONS += PetaKit5D-GUI_en_US.ts

# Remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# Add -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3

unix:!macx {
CONFIG += static
QMAKE_CXXFLAGS += -static

QMAKE_LFLAGS += -Wl,-rpath=\'\$\$ORIGIN\'/../lib
#QMAKE_CXXFLAGS += "-fno-sized-deallocation"


}

macx{
ICON = icons/abcIcon.icns

}

win32 {
CONFIG += static
QMAKE_CXXFLAGS += -static
QMAKE_LFLAGS += -Wl,-rpath=\'\$\$ORIGIN\'/../lib

RC_ICONS = icons/abcIcon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
}


