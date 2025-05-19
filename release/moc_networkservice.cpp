/****************************************************************************
** Meta object code from reading C++ file 'networkservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcpserver/networkservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkService_t {
    QByteArrayData data[17];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkService_t qt_meta_stringdata_NetworkService = {
    {
QT_MOC_LITERAL(0, 0, 14), // "NetworkService"
QT_MOC_LITERAL(1, 15, 9), // "connected"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "errorOccurred"
QT_MOC_LITERAL(4, 40, 11), // "errorString"
QT_MOC_LITERAL(5, 52, 15), // "connected_state"
QT_MOC_LITERAL(6, 68, 5), // "state"
QT_MOC_LITERAL(7, 74, 15), // "commandReceived"
QT_MOC_LITERAL(8, 90, 8), // "dataType"
QT_MOC_LITERAL(9, 99, 6), // "buffer"
QT_MOC_LITERAL(10, 106, 6), // "islen_"
QT_MOC_LITERAL(11, 113, 6), // "ismd5_"
QT_MOC_LITERAL(12, 120, 11), // "onConnected"
QT_MOC_LITERAL(13, 132, 15), // "onErrorOccurred"
QT_MOC_LITERAL(14, 148, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(15, 177, 11), // "socketError"
QT_MOC_LITERAL(16, 189, 11) // "onReadyRead"

    },
    "NetworkService\0connected\0\0errorOccurred\0"
    "errorString\0connected_state\0state\0"
    "commandReceived\0dataType\0buffer\0islen_\0"
    "ismd5_\0onConnected\0onErrorOccurred\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkService[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       7,    4,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   65,    2, 0x08 /* Private */,
      13,    1,   66,    2, 0x08 /* Private */,
      16,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray, QMetaType::Bool, QMetaType::Bool,    8,    9,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

       0        // eod
};

void NetworkService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkService *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->errorOccurred((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->connected_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->commandReceived((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkService::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkService::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkService::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkService::errorOccurred)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetworkService::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkService::connected_state)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NetworkService::*)(quint8 , const QByteArray & , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkService::commandReceived)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetworkService::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NetworkService.data,
    qt_meta_data_NetworkService,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void NetworkService::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NetworkService::errorOccurred(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkService::connected_state(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetworkService::commandReceived(quint8 _t1, const QByteArray & _t2, bool _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
