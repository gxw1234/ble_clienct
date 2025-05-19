/****************************************************************************
** Meta object code from reading C++ file 'caselinetextlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ble_time_line/caselinetextlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'caselinetextlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TimelineTextLabel_t {
    QByteArrayData data[15];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimelineTextLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimelineTextLabel_t qt_meta_stringdata_TimelineTextLabel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TimelineTextLabel"
QT_MOC_LITERAL(1, 18, 13), // "signalClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "signalDoubleClicked"
QT_MOC_LITERAL(4, 53, 16), // "signalInsertLeft"
QT_MOC_LITERAL(5, 70, 17), // "signalInsertRight"
QT_MOC_LITERAL(6, 88, 12), // "signalDelete"
QT_MOC_LITERAL(7, 101, 14), // "signalCopyText"
QT_MOC_LITERAL(8, 116, 18), // "signalDraggedToOut"
QT_MOC_LITERAL(9, 135, 17), // "signalSizeChanged"
QT_MOC_LITERAL(10, 153, 4), // "size"
QT_MOC_LITERAL(11, 158, 12), // "mouseEntered"
QT_MOC_LITERAL(12, 171, 4), // "text"
QT_MOC_LITERAL(13, 176, 9), // "mouseLeft"
QT_MOC_LITERAL(14, 186, 14) // "slotMenuShowed"

    },
    "TimelineTextLabel\0signalClicked\0\0"
    "signalDoubleClicked\0signalInsertLeft\0"
    "signalInsertRight\0signalDelete\0"
    "signalCopyText\0signalDraggedToOut\0"
    "signalSizeChanged\0size\0mouseEntered\0"
    "text\0mouseLeft\0slotMenuShowed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimelineTextLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,
       8,    0,   75,    2, 0x06 /* Public */,
       9,    1,   76,    2, 0x06 /* Public */,
      11,    1,   79,    2, 0x06 /* Public */,
      13,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    2,

       0        // eod
};

void TimelineTextLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimelineTextLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalClicked(); break;
        case 1: _t->signalDoubleClicked(); break;
        case 2: _t->signalInsertLeft(); break;
        case 3: _t->signalInsertRight(); break;
        case 4: _t->signalDelete(); break;
        case 5: _t->signalCopyText(); break;
        case 6: _t->signalDraggedToOut(); break;
        case 7: _t->signalSizeChanged((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 8: _t->mouseEntered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->mouseLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->slotMenuShowed((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalDoubleClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalInsertLeft)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalInsertRight)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalDelete)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalCopyText)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalDraggedToOut)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)(QSize );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::signalSizeChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::mouseEntered)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (TimelineTextLabel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimelineTextLabel::mouseLeft)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TimelineTextLabel::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_TimelineTextLabel.data,
    qt_meta_data_TimelineTextLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimelineTextLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimelineTextLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimelineTextLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int TimelineTextLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TimelineTextLabel::signalClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TimelineTextLabel::signalDoubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TimelineTextLabel::signalInsertLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TimelineTextLabel::signalInsertRight()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TimelineTextLabel::signalDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void TimelineTextLabel::signalCopyText()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TimelineTextLabel::signalDraggedToOut()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void TimelineTextLabel::signalSizeChanged(QSize _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TimelineTextLabel::mouseEntered(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void TimelineTextLabel::mouseLeft(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
