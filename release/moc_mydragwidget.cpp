/****************************************************************************
** Meta object code from reading C++ file 'mydragwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uncommon/mydragwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydragwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyDragWidget_t {
    QByteArrayData data[10];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyDragWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyDragWidget_t qt_meta_stringdata_MyDragWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyDragWidget"
QT_MOC_LITERAL(1, 13, 9), // "Tipsevent"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "text"
QT_MOC_LITERAL(4, 29, 13), // "Tipsleavevent"
QT_MOC_LITERAL(5, 43, 15), // "myselect_Device"
QT_MOC_LITERAL(6, 59, 13), // "fun_switching"
QT_MOC_LITERAL(7, 73, 13), // "ondevice_name"
QT_MOC_LITERAL(8, 87, 19), // "onLabelMouseEntered"
QT_MOC_LITERAL(9, 107, 16) // "onLabelMouseLeft"

    },
    "MyDragWidget\0Tipsevent\0\0text\0Tipsleavevent\0"
    "myselect_Device\0fun_switching\0"
    "ondevice_name\0onLabelMouseEntered\0"
    "onLabelMouseLeft"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyDragWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   56,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
       9,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void MyDragWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyDragWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Tipsevent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->Tipsleavevent(); break;
        case 2: _t->myselect_Device((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->fun_switching((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ondevice_name((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onLabelMouseEntered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onLabelMouseLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyDragWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyDragWidget::Tipsevent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyDragWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyDragWidget::Tipsleavevent)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyDragWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyDragWidget::myselect_Device)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyDragWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MyDragWidget.data,
    qt_meta_data_MyDragWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyDragWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyDragWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyDragWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyDragWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MyDragWidget::Tipsevent(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyDragWidget::Tipsleavevent()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyDragWidget::myselect_Device(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
