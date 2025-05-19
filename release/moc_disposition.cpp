/****************************************************************************
** Meta object code from reading C++ file 'disposition.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uncommon/disposition.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'disposition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Disposition_t {
    QByteArrayData data[12];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Disposition_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Disposition_t qt_meta_stringdata_Disposition = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Disposition"
QT_MOC_LITERAL(1, 12, 12), // "onstart_burn"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 18), // "handleDataReceived"
QT_MOC_LITERAL(4, 45, 8), // "dataType"
QT_MOC_LITERAL(5, 54, 6), // "buffer"
QT_MOC_LITERAL(6, 61, 6), // "islen_"
QT_MOC_LITERAL(7, 68, 6), // "ismd5_"
QT_MOC_LITERAL(8, 75, 21), // "handleConnected_state"
QT_MOC_LITERAL(9, 97, 15), // "connected_state"
QT_MOC_LITERAL(10, 113, 16), // "onstart_savejson"
QT_MOC_LITERAL(11, 130, 18) // "Generate_cmd_start"

    },
    "Disposition\0onstart_burn\0\0handleDataReceived\0"
    "dataType\0buffer\0islen_\0ismd5_\0"
    "handleConnected_state\0connected_state\0"
    "onstart_savejson\0Generate_cmd_start"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Disposition[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    4,   40,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,
      10,    0,   52,    2, 0x08 /* Private */,
      11,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray, QMetaType::Bool, QMetaType::Bool,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Disposition::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Disposition *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onstart_burn(); break;
        case 1: _t->handleDataReceived((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: _t->handleConnected_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onstart_savejson(); break;
        case 4: _t->Generate_cmd_start(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Disposition::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Disposition.data,
    qt_meta_data_Disposition,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Disposition::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Disposition::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Disposition.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Disposition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
