/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NotePad/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "OnFileOpen"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "OnFileSave"
QT_MOC_LITERAL(4, 34, 12), // "OnFileSavaAs"
QT_MOC_LITERAL(5, 47, 9), // "OnFileNew"
QT_MOC_LITERAL(6, 57, 13), // "OnTextChanged"
QT_MOC_LITERAL(7, 71, 13), // "OnFilePrinter"
QT_MOC_LITERAL(8, 85, 22), // "OnCursorPositionChange"
QT_MOC_LITERAL(9, 108, 12), // "OnEditDelete"
QT_MOC_LITERAL(10, 121, 10), // "OnFileExit"
QT_MOC_LITERAL(11, 132, 10), // "OnEditFind"
QT_MOC_LITERAL(12, 143, 13), // "OnEditReplace"
QT_MOC_LITERAL(13, 157, 15), // "OnCopyAvailable"
QT_MOC_LITERAL(14, 173, 10), // "bAvailable"
QT_MOC_LITERAL(15, 184, 15), // "OnUndoAvailable"
QT_MOC_LITERAL(16, 200, 15), // "OnRedoAvailable"
QT_MOC_LITERAL(17, 216, 10), // "OnEditGoto"
QT_MOC_LITERAL(18, 227, 13), // "OnViewToolBar"
QT_MOC_LITERAL(19, 241, 15) // "OnViewStatusBar"

    },
    "MainWindow\0OnFileOpen\0\0OnFileSave\0"
    "OnFileSavaAs\0OnFileNew\0OnTextChanged\0"
    "OnFilePrinter\0OnCursorPositionChange\0"
    "OnEditDelete\0OnFileExit\0OnEditFind\0"
    "OnEditReplace\0OnCopyAvailable\0bAvailable\0"
    "OnUndoAvailable\0OnRedoAvailable\0"
    "OnEditGoto\0OnViewToolBar\0OnViewStatusBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    1,  110,    2, 0x08 /* Private */,
      15,    1,  113,    2, 0x08 /* Private */,
      16,    1,  116,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnFileOpen(); break;
        case 1: _t->OnFileSave(); break;
        case 2: _t->OnFileSavaAs(); break;
        case 3: _t->OnFileNew(); break;
        case 4: _t->OnTextChanged(); break;
        case 5: _t->OnFilePrinter(); break;
        case 6: _t->OnCursorPositionChange(); break;
        case 7: _t->OnEditDelete(); break;
        case 8: _t->OnFileExit(); break;
        case 9: _t->OnEditFind(); break;
        case 10: _t->OnEditReplace(); break;
        case 11: _t->OnCopyAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->OnUndoAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->OnRedoAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->OnEditGoto(); break;
        case 15: _t->OnViewToolBar(); break;
        case 16: _t->OnViewStatusBar(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
