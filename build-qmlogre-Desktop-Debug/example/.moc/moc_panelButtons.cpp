/****************************************************************************
** Meta object code from reading C++ file 'panelButtons.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QmlOgre-master/example/modules/histogram/panelButtons.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panelButtons.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PanelButtons_t {
    QByteArrayData data[7];
    char stringdata[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PanelButtons_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PanelButtons_t qt_meta_stringdata_PanelButtons = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 15),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 5),
QT_MOC_LITERAL(4, 36, 16),
QT_MOC_LITERAL(5, 53, 15),
QT_MOC_LITERAL(6, 69, 17)
    },
    "PanelButtons\0qBoxNDG_toggled\0\0state\0"
    "qBoxBlue_toggled\0qBoxRed_toggled\0"
    "qBoxGreen_toggled\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelButtons[] = {

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
       6,    1,   43,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void PanelButtons::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelButtons *_t = static_cast<PanelButtons *>(_o);
        switch (_id) {
        case 0: _t->qBoxNDG_toggled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->qBoxBlue_toggled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->qBoxRed_toggled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->qBoxGreen_toggled((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PanelButtons::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PanelButtons.data,
      qt_meta_data_PanelButtons,  qt_static_metacall, 0, 0}
};


const QMetaObject *PanelButtons::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelButtons::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PanelButtons.stringdata))
        return static_cast<void*>(const_cast< PanelButtons*>(this));
    return QWidget::qt_metacast(_clname);
}

int PanelButtons::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
