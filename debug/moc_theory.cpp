/****************************************************************************
** Meta object code from reading C++ file 'theory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../theory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'theory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Theory_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Theory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Theory_t qt_meta_stringdata_Theory = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Theory"
QT_MOC_LITERAL(1, 7, 17), // "onListItemClicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 43, 19), // "anchorClickedAction"
QT_MOC_LITERAL(5, 63, 17) // "actionRefreshList"

    },
    "Theory\0onListItemClicked\0\0QListWidgetItem*\0"
    "anchorClickedAction\0actionRefreshList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Theory[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    1,   32,    2, 0x08 /* Private */,
       5,    0,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QUrl,    2,
    QMetaType::Void,

       0        // eod
};

void Theory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Theory *_t = static_cast<Theory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onListItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->anchorClickedAction((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: _t->actionRefreshList(); break;
        default: ;
        }
    }
}

const QMetaObject Theory::staticMetaObject = {
    { &BaseWindow::staticMetaObject, qt_meta_stringdata_Theory.data,
      qt_meta_data_Theory,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Theory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Theory::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Theory.stringdata0))
        return static_cast<void*>(const_cast< Theory*>(this));
    return BaseWindow::qt_metacast(_clname);
}

int Theory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
