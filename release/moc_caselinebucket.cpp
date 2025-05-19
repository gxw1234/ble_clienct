/****************************************************************************
** Meta object code from reading C++ file 'caselinebucket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ble_time_line/caselinebucket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'caselinebucket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TimelineBucket_t {
    QByteArrayData data[24];
    char stringdata0[407];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimelineBucket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimelineBucket_t qt_meta_stringdata_TimelineBucket = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TimelineBucket"
QT_MOC_LITERAL(1, 15, 21), // "signalSizeHintChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "size"
QT_MOC_LITERAL(4, 43, 25), // "signalBucketWidgetPressed"
QT_MOC_LITERAL(5, 69, 25), // "signalBucketWidgetClicked"
QT_MOC_LITERAL(6, 95, 23), // "signalTimeWidgetClicked"
QT_MOC_LITERAL(7, 119, 18), // "TimelineTimeLabel*"
QT_MOC_LITERAL(8, 138, 5), // "label"
QT_MOC_LITERAL(9, 144, 23), // "signalTextWidgetClicked"
QT_MOC_LITERAL(10, 168, 18), // "TimelineTextLabel*"
QT_MOC_LITERAL(11, 187, 29), // "signalTimeWidgetDoubleClicked"
QT_MOC_LITERAL(12, 217, 29), // "signalTextWidgetDoubleClicked"
QT_MOC_LITERAL(13, 247, 21), // "signalDroppedAndMoved"
QT_MOC_LITERAL(14, 269, 15), // "TimelineBucket*"
QT_MOC_LITERAL(15, 285, 6), // "bucket"
QT_MOC_LITERAL(16, 292, 27), // "signalBucketContentsChanged"
QT_MOC_LITERAL(17, 320, 16), // "actionInsertLeft"
QT_MOC_LITERAL(18, 337, 17), // "actionInsertRight"
QT_MOC_LITERAL(19, 355, 12), // "actionDelete"
QT_MOC_LITERAL(20, 368, 19), // "actionMoveTextLabel"
QT_MOC_LITERAL(21, 388, 4), // "from"
QT_MOC_LITERAL(22, 393, 2), // "to"
QT_MOC_LITERAL(23, 396, 10) // "water_prop"

    },
    "TimelineBucket\0signalSizeHintChanged\0"
    "\0size\0signalBucketWidgetPressed\0"
    "signalBucketWidgetClicked\0"
    "signalTimeWidgetClicked\0TimelineTimeLabel*\0"
    "label\0signalTextWidgetClicked\0"
    "TimelineTextLabel*\0signalTimeWidgetDoubleClicked\0"
    "signalTextWidgetDoubleClicked\0"
    "signalDroppedAndMoved\0TimelineBucket*\0"
    "bucket\0signalBucketContentsChanged\0"
    "actionInsertLeft\0actionInsertRight\0"
    "actionDelete\0actionMoveTextLabel\0from\0"
    "to\0water_prop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimelineBucket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       1,  114, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    0,   82,    2, 0x06 /* Public */,
       5,    0,   83,    2, 0x06 /* Public */,
       6,    1,   84,    2, 0x06 /* Public */,
       9,    1,   87,    2, 0x06 /* Public */,
      11,    1,   90,    2, 0x06 /* Public */,
      12,    1,   93,    2, 0x06 /* Public */,
      13,    1,   96,    2, 0x06 /* Public */,
      16,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  100,    2, 0x0a /* Public */,
      18,    1,  103,    2, 0x0a /* Public */,
      19,    1,  106,    2, 0x0a /* Public */,
      20,    2,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QSize,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   21,   22,

 // properties: name, type, flags
      23, QMetaType::Int, 0x00095003,

       0        // eod
};

void TimelineBucket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimelineBucket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSizeHintChanged((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 1: _t->signalBucketWidgetPressed(); break;
        case 2: _t->signalBucketWidgetClicked(); break;
        case 3: _t->signalTimeWidgetClicked((*reinterpret_cast< TimelineTimeLabel*(*)>(_a[1]))); break;
        case 4: _t->signalTextWidgetClicked((*reinterpret_cast< TimelineTextLabel*(*)>(_a[1]))); break;
        case 5: _t->signalTimeWidgetDoubleClicked((*reinterpret_cast< TimelineTimeLabel*(*)>(_a[1]))); break;
        case 6: _t->signalTextWidgetDoubleClicked((*reinterpret_cast< TimelineTextLabel*(*)>(_a[1]))); break;
        case 7: _t->signalDroppedAndMoved((*reinterpret_cast< TimelineBucket*(*)>(_a[1]))); break;
        case 8: _t->signalBucketContentsChanged(); break;
        case 9: _t->actionInsertLeft((*reinterpret_cast< TimelineTextLabel*(*)>(_a[1]))); break;
        case 10: _t->actionInsertRight((*reinterpret_cast< TimelineTextLabel*(*)>(_a[1]))); break;
        case 11: _t->actionDelete((*reinterpret_cast< TimelineTextLabel*(*)>(_a[1]))); break;
        case 12: _t->actionMoveTextLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTimeLabel* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTextLabel* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTimeLabel* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTextLabel* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineBucket* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTextLabel* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTextLabel* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TimelineTextLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimelineBucket::*)(QSize );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalSizeHintChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalBucketWidgetPressed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalBucketWidgetClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)(TimelineTimeLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalTimeWidgetClicked)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)(TimelineTextLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalTextWidgetClicked)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)(TimelineTimeLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalTimeWidgetDoubleClicked)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)(TimelineTextLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalTextWidgetDoubleClicked)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)(TimelineBucket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalDroppedAndMoved)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TimelineBucket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineBucket::signalBucketContentsChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TimelineBucket *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getWaterProp(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TimelineBucket *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWaterProp(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TimelineBucket::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TimelineBucket.data,
    qt_meta_data_TimelineBucket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimelineBucket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimelineBucket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimelineBucket.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TimelineBucket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TimelineBucket::signalSizeHintChanged(QSize _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TimelineBucket::signalBucketWidgetPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TimelineBucket::signalBucketWidgetClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TimelineBucket::signalTimeWidgetClicked(TimelineTimeLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TimelineBucket::signalTextWidgetClicked(TimelineTextLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TimelineBucket::signalTimeWidgetDoubleClicked(TimelineTimeLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TimelineBucket::signalTextWidgetDoubleClicked(TimelineTextLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TimelineBucket::signalDroppedAndMoved(TimelineBucket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TimelineBucket::signalBucketContentsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
