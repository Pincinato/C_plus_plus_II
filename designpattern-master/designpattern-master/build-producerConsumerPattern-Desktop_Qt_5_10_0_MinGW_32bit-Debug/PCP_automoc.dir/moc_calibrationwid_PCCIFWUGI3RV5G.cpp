/****************************************************************************
** Meta object code from reading C++ file 'calibrationwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../producerConsumerPattern/src/ui/calibrationwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibrationwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalibrationWidget_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalibrationWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalibrationWidget_t qt_meta_stringdata_CalibrationWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CalibrationWidget"
QT_MOC_LITERAL(1, 18, 4), // "back"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "keyPressEvent"
QT_MOC_LITERAL(4, 38, 10), // "QKeyEvent*"
QT_MOC_LITERAL(5, 49, 2), // "ev"
QT_MOC_LITERAL(6, 52, 6), // "Accept"
QT_MOC_LITERAL(7, 59, 6) // "Refuse"

    },
    "CalibrationWidget\0back\0\0keyPressEvent\0"
    "QKeyEvent*\0ev\0Accept\0Refuse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalibrationWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x08 /* Private */,
       6,    0,   38,    2, 0x08 /* Private */,
       7,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CalibrationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalibrationWidget *_t = static_cast<CalibrationWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->back(); break;
        case 1: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->Accept(); break;
        case 3: _t->Refuse(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CalibrationWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationWidget::back)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CalibrationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CalibrationWidget.data,
      qt_meta_data_CalibrationWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CalibrationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalibrationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CalibrationWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IControl"))
        return static_cast< IControl*>(this);
    return QWidget::qt_metacast(_clname);
}

int CalibrationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void CalibrationWidget::back()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
