/****************************************************************************
** Meta object code from reading C++ file 'caselinetimelabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ble_time_line/caselinetimelabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'caselinetimelabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TimelineTimeLabel_t {
    QByteArrayData data[8];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimelineTimeLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimelineTimeLabel_t qt_meta_stringdata_TimelineTimeLabel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TimelineTimeLabel"
QT_MOC_LITERAL(1, 18, 13), // "signalClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "signalDoubleClicked"
QT_MOC_LITERAL(4, 53, 17), // "signalSizeChanged"
QT_MOC_LITERAL(5, 71, 4), // "size"
QT_MOC_LITERAL(6, 76, 14), // "slotMenuShowed"
QT_MOC_LITERAL(7, 91, 3) // "pos"

    },
    "TimelineTimeLabel\0signalClicked\0\0"
    "signalDoubleClicked\0signalSizeChanged\0"
    "size\0slotMenuShowed\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimelineTimeLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    7,

       0        // eod
};

void TimelineTimeLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimelineTimeLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalClicked(); break;
        case 1: _t->signalDoubleClicked(); break;
        case 2: _t->signalSizeChanged((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 3: _t->slotMenuShowed((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimelineTimeLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTimeLabel::signalClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TimelineTimeLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTimeLabel::signalDoubleClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TimelineTimeLabel::*)(QSize );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTimeLabel::signalSizeChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TimelineTimeLabel::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_TimelineTimeLabel.data,
    qt_meta_data_TimelineTimeLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimelineTimeLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimelineTimeLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimelineTimeLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int TimelineTimeLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TimelineTimeLabel::signalClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TimelineTimeLabel::signalDoubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TimelineTimeLabel::signalSizeChanged(QSize _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
