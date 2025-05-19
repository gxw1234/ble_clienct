/****************************************************************************
** Meta object code from reading C++ file 'tcpapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcpserver/tcpapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tcpapp_t {
    QByteArrayData data[16];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tcpapp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tcpapp_t qt_meta_stringdata_Tcpapp = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Tcpapp"
QT_MOC_LITERAL(1, 7, 12), // "connectedapp"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "errorOccurredapp"
QT_MOC_LITERAL(4, 38, 11), // "errorString"
QT_MOC_LITERAL(5, 50, 18), // "commandReceivedapp"
QT_MOC_LITERAL(6, 69, 8), // "dataType"
QT_MOC_LITERAL(7, 78, 6), // "buffer"
QT_MOC_LITERAL(8, 85, 6), // "islen_"
QT_MOC_LITERAL(9, 92, 6), // "ismd5_"
QT_MOC_LITERAL(10, 99, 17), // "m_connected_state"
QT_MOC_LITERAL(11, 117, 5), // "state"
QT_MOC_LITERAL(12, 123, 14), // "onConnectedapp"
QT_MOC_LITERAL(13, 138, 18), // "onErrorOccurredapp"
QT_MOC_LITERAL(14, 157, 23), // "onhandleDataReceivedapp"
QT_MOC_LITERAL(15, 181, 17) // "onconnected_state"

    },
    "Tcpapp\0connectedapp\0\0errorOccurredapp\0"
    "errorString\0commandReceivedapp\0dataType\0"
    "buffer\0islen_\0ismd5_\0m_connected_state\0"
    "state\0onConnectedapp\0onErrorOccurredapp\0"
    "onhandleDataReceivedapp\0onconnected_state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tcpapp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       5,    4,   58,    2, 0x06 /* Public */,
      10,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   70,    2, 0x08 /* Private */,
      13,    1,   71,    2, 0x08 /* Private */,
      14,    4,   74,    2, 0x08 /* Private */,
      15,    1,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray, QMetaType::Bool, QMetaType::Bool,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray, QMetaType::Bool, QMetaType::Bool,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

void Tcpapp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tcpapp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectedapp(); break;
        case 1: _t->errorOccurredapp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->commandReceivedapp((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 3: _t->m_connected_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->onConnectedapp(); break;
        case 5: _t->onErrorOccurredapp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->onhandleDataReceivedapp((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 7: _t->onconnected_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Tcpapp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tcpapp::connectedapp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Tcpapp::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tcpapp::errorOccurredapp)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Tcpapp::*)(quint8 , const QByteArray & , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tcpapp::commandReceivedapp)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Tcpapp::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tcpapp::m_connected_state)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tcpapp::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Tcpapp.data,
    qt_meta_data_Tcpapp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tcpapp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tcpapp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tcpapp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Tcpapp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Tcpapp::connectedapp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Tcpapp::errorOccurredapp(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Tcpapp::commandReceivedapp(quint8 _t1, const QByteArray & _t2, bool _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Tcpapp::m_connected_state(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
