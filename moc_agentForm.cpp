/****************************************************************************
** Meta object code from reading C++ file 'agentForm.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "agentForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agentForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_agentForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      34,   10,   10,   10, 0x0a,
      56,   10,   10,   10, 0x0a,
      78,   10,   10,   10, 0x0a,
      99,   10,   10,   10, 0x0a,
     124,   10,   10,   10, 0x0a,
     141,   10,   10,   10, 0x0a,
     157,   10,   10,   10, 0x0a,
     173,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_agentForm[] = {
    "agentForm\0\0pripojComportClicked()\0"
    "odpojComportClicked()\0pripojServerClicked()\0"
    "odpojServerClicked()\0nastavAktPolohuClicked()\0"
    "dopreduClicked()\0zastavClicked()\0"
    "dolavaClicked()\0dopravaClicked()\0"
};

void agentForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        agentForm *_t = static_cast<agentForm *>(_o);
        switch (_id) {
        case 0: _t->pripojComportClicked(); break;
        case 1: _t->odpojComportClicked(); break;
        case 2: _t->pripojServerClicked(); break;
        case 3: _t->odpojServerClicked(); break;
        case 4: _t->nastavAktPolohuClicked(); break;
        case 5: _t->dopreduClicked(); break;
        case 6: _t->zastavClicked(); break;
        case 7: _t->dolavaClicked(); break;
        case 8: _t->dopravaClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData agentForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject agentForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_agentForm,
      qt_meta_data_agentForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &agentForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *agentForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *agentForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_agentForm))
        return static_cast<void*>(const_cast< agentForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int agentForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
