/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[38];
    char stringdata0[1037];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "jobStart"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "size_t"
QT_MOC_LITERAL(4, 28, 4), // "outA"
QT_MOC_LITERAL(5, 33, 32), // "std::vector<matlab::data::Array>"
QT_MOC_LITERAL(6, 66, 4), // "data"
QT_MOC_LITERAL(7, 71, 36), // "on_dsrAdvancedSettingsButton_..."
QT_MOC_LITERAL(8, 108, 38), // "on_deconAdvancedSettingsButto..."
QT_MOC_LITERAL(9, 147, 36), // "on_jobAdvancedSettingsButton_..."
QT_MOC_LITERAL(10, 184, 23), // "on_submitButton_clicked"
QT_MOC_LITERAL(11, 208, 33), // "on_resultsDirBrowseButton_cli..."
QT_MOC_LITERAL(12, 242, 33), // "on_resultsDirLineEdit_textCha..."
QT_MOC_LITERAL(13, 276, 4), // "arg1"
QT_MOC_LITERAL(14, 281, 37), // "on_mainAdvancedSettingsButton..."
QT_MOC_LITERAL(15, 319, 30), // "on_deskewCheckBox_stateChanged"
QT_MOC_LITERAL(16, 350, 30), // "on_rotateCheckBox_stateChanged"
QT_MOC_LITERAL(17, 381, 39), // "on_deskewAndRotateCheckBox_st..."
QT_MOC_LITERAL(18, 421, 30), // "on_stitchCheckBox_stateChanged"
QT_MOC_LITERAL(19, 452, 25), // "on_mainNextButton_clicked"
QT_MOC_LITERAL(20, 478, 28), // "on_dsrPreviousButton_clicked"
QT_MOC_LITERAL(21, 507, 24), // "on_dsrNextButton_clicked"
QT_MOC_LITERAL(22, 532, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(23, 560, 5), // "index"
QT_MOC_LITERAL(24, 566, 37), // "on_objectiveScanCheckBox_stat..."
QT_MOC_LITERAL(25, 604, 31), // "on_stitchPreviousButton_clicked"
QT_MOC_LITERAL(26, 636, 27), // "on_stitchNextButton_clicked"
QT_MOC_LITERAL(27, 664, 30), // "on_deconPreviousButton_clicked"
QT_MOC_LITERAL(28, 695, 26), // "on_deconNextButton_clicked"
QT_MOC_LITERAL(29, 722, 28), // "on_jobPreviousButton_clicked"
QT_MOC_LITERAL(30, 751, 25), // "on_addPathsButton_clicked"
QT_MOC_LITERAL(31, 777, 41), // "on_imageListFullPathsBrowseBu..."
QT_MOC_LITERAL(32, 819, 41), // "on_imageListFullPathsLineEdit..."
QT_MOC_LITERAL(33, 861, 32), // "on_boundBoxCheckBox_stateChanged"
QT_MOC_LITERAL(34, 894, 38), // "on_llffCorrectionCheckBox_sta..."
QT_MOC_LITERAL(35, 933, 32), // "on_lsImageAddPathsButton_clicked"
QT_MOC_LITERAL(36, 966, 35), // "on_backgroundAddPathsButton_c..."
QT_MOC_LITERAL(37, 1002, 34) // "on_psfFullAddPathsButton_2_cl..."

    },
    "MainWindow\0jobStart\0\0size_t\0outA\0"
    "std::vector<matlab::data::Array>\0data\0"
    "on_dsrAdvancedSettingsButton_clicked\0"
    "on_deconAdvancedSettingsButton_clicked\0"
    "on_jobAdvancedSettingsButton_clicked\0"
    "on_submitButton_clicked\0"
    "on_resultsDirBrowseButton_clicked\0"
    "on_resultsDirLineEdit_textChanged\0"
    "arg1\0on_mainAdvancedSettingsButton_clicked\0"
    "on_deskewCheckBox_stateChanged\0"
    "on_rotateCheckBox_stateChanged\0"
    "on_deskewAndRotateCheckBox_stateChanged\0"
    "on_stitchCheckBox_stateChanged\0"
    "on_mainNextButton_clicked\0"
    "on_dsrPreviousButton_clicked\0"
    "on_dsrNextButton_clicked\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_objectiveScanCheckBox_stateChanged\0"
    "on_stitchPreviousButton_clicked\0"
    "on_stitchNextButton_clicked\0"
    "on_deconPreviousButton_clicked\0"
    "on_deconNextButton_clicked\0"
    "on_jobPreviousButton_clicked\0"
    "on_addPathsButton_clicked\0"
    "on_imageListFullPathsBrowseButton_clicked\0"
    "on_imageListFullPathsLineEdit_textChanged\0"
    "on_boundBoxCheckBox_stateChanged\0"
    "on_llffCorrectionCheckBox_stateChanged\0"
    "on_lsImageAddPathsButton_clicked\0"
    "on_backgroundAddPathsButton_clicked\0"
    "on_psfFullAddPathsButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  164,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  169,    2, 0x08 /* Private */,
       8,    0,  170,    2, 0x08 /* Private */,
       9,    0,  171,    2, 0x08 /* Private */,
      10,    0,  172,    2, 0x08 /* Private */,
      11,    0,  173,    2, 0x08 /* Private */,
      12,    1,  174,    2, 0x08 /* Private */,
      14,    0,  177,    2, 0x08 /* Private */,
      15,    1,  178,    2, 0x08 /* Private */,
      16,    1,  181,    2, 0x08 /* Private */,
      17,    1,  184,    2, 0x08 /* Private */,
      18,    1,  187,    2, 0x08 /* Private */,
      19,    0,  190,    2, 0x08 /* Private */,
      20,    0,  191,    2, 0x08 /* Private */,
      21,    0,  192,    2, 0x08 /* Private */,
      22,    1,  193,    2, 0x08 /* Private */,
      24,    1,  196,    2, 0x08 /* Private */,
      25,    0,  199,    2, 0x08 /* Private */,
      26,    0,  200,    2, 0x08 /* Private */,
      27,    0,  201,    2, 0x08 /* Private */,
      28,    0,  202,    2, 0x08 /* Private */,
      29,    0,  203,    2, 0x08 /* Private */,
      30,    0,  204,    2, 0x08 /* Private */,
      31,    0,  205,    2, 0x08 /* Private */,
      32,    1,  206,    2, 0x08 /* Private */,
      33,    1,  209,    2, 0x08 /* Private */,
      34,    1,  212,    2, 0x08 /* Private */,
      35,    0,  215,    2, 0x08 /* Private */,
      36,    0,  216,    2, 0x08 /* Private */,
      37,    0,  217,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->jobStart((*reinterpret_cast< const size_t(*)>(_a[1])),(*reinterpret_cast< const std::vector<matlab::data::Array>(*)>(_a[2]))); break;
        case 1: _t->on_dsrAdvancedSettingsButton_clicked(); break;
        case 2: _t->on_deconAdvancedSettingsButton_clicked(); break;
        case 3: _t->on_jobAdvancedSettingsButton_clicked(); break;
        case 4: _t->on_submitButton_clicked(); break;
        case 5: _t->on_resultsDirBrowseButton_clicked(); break;
        case 6: _t->on_resultsDirLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_mainAdvancedSettingsButton_clicked(); break;
        case 8: _t->on_deskewCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_rotateCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_deskewAndRotateCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_stitchCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_mainNextButton_clicked(); break;
        case 13: _t->on_dsrPreviousButton_clicked(); break;
        case 14: _t->on_dsrNextButton_clicked(); break;
        case 15: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_objectiveScanCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_stitchPreviousButton_clicked(); break;
        case 18: _t->on_stitchNextButton_clicked(); break;
        case 19: _t->on_deconPreviousButton_clicked(); break;
        case 20: _t->on_deconNextButton_clicked(); break;
        case 21: _t->on_jobPreviousButton_clicked(); break;
        case 22: _t->on_addPathsButton_clicked(); break;
        case 23: _t->on_imageListFullPathsBrowseButton_clicked(); break;
        case 24: _t->on_imageListFullPathsLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: _t->on_boundBoxCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_llffCorrectionCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_lsImageAddPathsButton_clicked(); break;
        case 28: _t->on_backgroundAddPathsButton_clicked(); break;
        case 29: _t->on_psfFullAddPathsButton_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const size_t , const std::vector<matlab::data::Array> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::jobStart)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::jobStart(const size_t _t1, const std::vector<matlab::data::Array> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
