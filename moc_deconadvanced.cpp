/****************************************************************************
** Meta object code from reading C++ file 'deconadvanced.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "deconadvanced.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deconadvanced.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_deconAdvanced_t {
    QByteArrayData data[11];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_deconAdvanced_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_deconAdvanced_t qt_meta_stringdata_deconAdvanced = {
    {
QT_MOC_LITERAL(0, 0, 13), // "deconAdvanced"
QT_MOC_LITERAL(1, 14, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 23), // "on_submitButton_clicked"
QT_MOC_LITERAL(4, 63, 35), // "on_cppDeconPathBrowseButton_c..."
QT_MOC_LITERAL(5, 99, 35), // "on_cppDeconPathLineEdit_textC..."
QT_MOC_LITERAL(6, 135, 4), // "arg1"
QT_MOC_LITERAL(7, 140, 36), // "on_cudaDeconPathBrowseButton_..."
QT_MOC_LITERAL(8, 177, 36), // "on_cudaDeconPathLineEdit_text..."
QT_MOC_LITERAL(9, 214, 33), // "on_otfgenPathBrowseButton_cli..."
QT_MOC_LITERAL(10, 248, 33) // "on_otfgenPathLineEdit_textCha..."

    },
    "deconAdvanced\0on_cancelButton_clicked\0"
    "\0on_submitButton_clicked\0"
    "on_cppDeconPathBrowseButton_clicked\0"
    "on_cppDeconPathLineEdit_textChanged\0"
    "arg1\0on_cudaDeconPathBrowseButton_clicked\0"
    "on_cudaDeconPathLineEdit_textChanged\0"
    "on_otfgenPathBrowseButton_clicked\0"
    "on_otfgenPathLineEdit_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_deconAdvanced[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    1,   61,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void deconAdvanced::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<deconAdvanced *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cancelButton_clicked(); break;
        case 1: _t->on_submitButton_clicked(); break;
        case 2: _t->on_cppDeconPathBrowseButton_clicked(); break;
        case 3: _t->on_cppDeconPathLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_cudaDeconPathBrowseButton_clicked(); break;
        case 5: _t->on_cudaDeconPathLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_otfgenPathBrowseButton_clicked(); break;
        case 7: _t->on_otfgenPathLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject deconAdvanced::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_deconAdvanced.data,
    qt_meta_data_deconAdvanced,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *deconAdvanced::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *deconAdvanced::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_deconAdvanced.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int deconAdvanced::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
