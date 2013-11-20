/****************************************************************************
** Meta object code from reading C++ file 'qcolorrampeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QmlOgre-master/example/library/QColorRampEditor/qcolorrampeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcolorrampeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QColorRampEditor_t {
    QByteArrayData data[12];
    char stringdata[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QColorRampEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QColorRampEditor_t qt_meta_stringdata_QColorRampEditor = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 11),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 14),
QT_MOC_LITERAL(4, 45, 5),
QT_MOC_LITERAL(5, 51, 3),
QT_MOC_LITERAL(6, 55, 11),
QT_MOC_LITERAL(7, 67, 13),
QT_MOC_LITERAL(8, 81, 1),
QT_MOC_LITERAL(9, 83, 15),
QT_MOC_LITERAL(10, 99, 12),
QT_MOC_LITERAL(11, 112, 10)
    },
    "QColorRampEditor\0rampChanged\0\0"
    "setSliderColor\0index\0col\0resizeEvent\0"
    "QResizeEvent*\0e\0mousePressEvent\0"
    "QMouseEvent*\0updateRamp\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QColorRampEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    2,   40,    2, 0x0a,
       6,    1,   45,    2, 0x09,
       9,    1,   48,    2, 0x09,
      11,    0,   51,    2, 0x09,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QColor,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void,

       0        // eod
};

void QColorRampEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QColorRampEditor *_t = static_cast<QColorRampEditor *>(_o);
        switch (_id) {
        case 0: _t->rampChanged(); break;
        case 1: _t->setSliderColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 2: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->updateRamp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QColorRampEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QColorRampEditor::rampChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QColorRampEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QColorRampEditor.data,
      qt_meta_data_QColorRampEditor,  qt_static_metacall, 0, 0}
};


const QMetaObject *QColorRampEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QColorRampEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QColorRampEditor.stringdata))
        return static_cast<void*>(const_cast< QColorRampEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int QColorRampEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QColorRampEditor::rampChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
struct qt_meta_stringdata_QColorRampEditorSlider_t {
    QByteArrayData data[5];
    char stringdata[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QColorRampEditorSlider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QColorRampEditorSlider_t qt_meta_stringdata_QColorRampEditorSlider = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 10),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 12),
QT_MOC_LITERAL(4, 48, 5)
    },
    "QColorRampEditorSlider\0paintEvent\0\0"
    "QPaintEvent*\0event\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QColorRampEditorSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x09,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QColorRampEditorSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QColorRampEditorSlider *_t = static_cast<QColorRampEditorSlider *>(_o);
        switch (_id) {
        case 0: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QColorRampEditorSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QColorRampEditorSlider.data,
      qt_meta_data_QColorRampEditorSlider,  qt_static_metacall, 0, 0}
};


const QMetaObject *QColorRampEditorSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QColorRampEditorSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QColorRampEditorSlider.stringdata))
        return static_cast<void*>(const_cast< QColorRampEditorSlider*>(this));
    return QWidget::qt_metacast(_clname);
}

int QColorRampEditorSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_QSlidersWidget_t {
    QByteArrayData data[8];
    char stringdata[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QSlidersWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QSlidersWidget_t qt_meta_stringdata_QSlidersWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 15),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 12),
QT_MOC_LITERAL(4, 45, 1),
QT_MOC_LITERAL(5, 47, 14),
QT_MOC_LITERAL(6, 62, 17),
QT_MOC_LITERAL(7, 80, 21)
    },
    "QSlidersWidget\0mousePressEvent\0\0"
    "QMouseEvent*\0e\0mouseMoveEvent\0"
    "mouseReleaseEvent\0mouseDoubleClickEvent\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSlidersWidget[] = {

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
       1,    1,   34,    2, 0x09,
       5,    1,   37,    2, 0x09,
       6,    1,   40,    2, 0x09,
       7,    1,   43,    2, 0x09,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QSlidersWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSlidersWidget *_t = static_cast<QSlidersWidget *>(_o);
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->mouseDoubleClickEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QSlidersWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSlidersWidget.data,
      qt_meta_data_QSlidersWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *QSlidersWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSlidersWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSlidersWidget.stringdata))
        return static_cast<void*>(const_cast< QSlidersWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSlidersWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
