/****************************************************************************
** Meta object code from reading C++ file 'test_case_qwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uncommon/test_case_qwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_case_qwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Test_case_qwidget_t {
    QByteArrayData data[17];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Test_case_qwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Test_case_qwidget_t qt_meta_stringdata_Test_case_qwidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Test_case_qwidget"
QT_MOC_LITERAL(1, 18, 19), // "home_file_switching"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 12), // "startclicked"
QT_MOC_LITERAL(4, 52, 5), // "start"
QT_MOC_LITERAL(5, 58, 18), // "handleDataReceived"
QT_MOC_LITERAL(6, 77, 8), // "dataType"
QT_MOC_LITERAL(7, 86, 6), // "buffer"
QT_MOC_LITERAL(8, 93, 6), // "islen_"
QT_MOC_LITERAL(9, 100, 6), // "ismd5_"
QT_MOC_LITERAL(10, 107, 21), // "handleConnected_state"
QT_MOC_LITERAL(11, 129, 15), // "connected_state"
QT_MOC_LITERAL(12, 145, 24), // "acceptSelectItemsChanged"
QT_MOC_LITERAL(13, 170, 17), // "QVector<QVariant>"
QT_MOC_LITERAL(14, 188, 17), // "m_debugChanged_ch"
QT_MOC_LITERAL(15, 206, 15), // "handleSelection"
QT_MOC_LITERAL(16, 222, 13) // "selectedItems"

    },
    "Test_case_qwidget\0home_file_switching\0"
    "\0startclicked\0start\0handleDataReceived\0"
    "dataType\0buffer\0islen_\0ismd5_\0"
    "handleConnected_state\0connected_state\0"
    "acceptSelectItemsChanged\0QVector<QVariant>\0"
    "m_debugChanged_ch\0handleSelection\0"
    "selectedItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Test_case_qwidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       3,    1,   52,    2, 0x08 /* Private */,
       5,    4,   55,    2, 0x08 /* Private */,
      10,    1,   64,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,
      14,    0,   70,    2, 0x08 /* Private */,
      15,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray, QMetaType::Bool, QMetaType::Bool,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   16,

       0        // eod
};

void Test_case_qwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Test_case_qwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->home_file_switching((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->startclicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->handleDataReceived((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 3: _t->handleConnected_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->acceptSelectItemsChanged((*reinterpret_cast< QVector<QVariant>(*)>(_a[1]))); break;
        case 5: _t->m_debugChanged_ch(); break;
        case 6: _t->handleSelection((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVariant> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Test_case_qwidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Test_case_qwidget.data,
    qt_meta_data_Test_case_qwidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Test_case_qwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Test_case_qwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Test_case_qwidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Test_case_qwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
