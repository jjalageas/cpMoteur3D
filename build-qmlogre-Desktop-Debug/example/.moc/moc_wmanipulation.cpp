/****************************************************************************
** Meta object code from reading C++ file 'wmanipulation.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QmlOgre-master/example/modules/manipulation/wmanipulation.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wmanipulation.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WManipulation_t {
    QByteArrayData data[8];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_WManipulation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_WManipulation_t qt_meta_stringdata_WManipulation = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 15),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 5),
QT_MOC_LITERAL(4, 37, 25),
QT_MOC_LITERAL(5, 63, 19),
QT_MOC_LITERAL(6, 83, 6),
QT_MOC_LITERAL(7, 90, 16)
    },
    "WManipulation\0displayViewType\0\0index\0"
    "displayTransformationType\0displayPictureOrNot\0"
    "active\0displayMaskOrNot\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WManipulation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a,
       4,    1,   37,    2, 0x0a,
       5,    1,   40,    2, 0x0a,
       7,    1,   43,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,

       0        // eod
};

void WManipulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WManipulation *_t = static_cast<WManipulation *>(_o);
        switch (_id) {
        case 0: _t->displayViewType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->displayTransformationType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->displayPictureOrNot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->displayMaskOrNot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject WManipulation::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_WManipulation.data,
      qt_meta_data_WManipulation,  qt_static_metacall, 0, 0}
};


const QMetaObject *WManipulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WManipulation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WManipulation.stringdata))
        return static_cast<void*>(const_cast< WManipulation*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int WManipulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
