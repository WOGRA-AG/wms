#ifndef WMSMACROS_H
#define WMSMACROS_H

// helper macros for C++ -> QML data transfer
#define QT_GENARG(x)Q_ARG(QVariant,x)

#define QT_GENARC_LIST1(p1)          QT_GENARG(p1)
#define QT_GENARC_LIST2(p1,p2)       QT_GENARG(p1),QT_GENARG(p2)
#define QT_GENARC_LIST3(p1,p2,p3)    QT_GENARG(p1),QT_GENARG(p2),QT_GENARG(p3)
#define QT_GENARC_LIST4(p1,p2,p3,p4) QT_GENARG(p1),QT_GENARG(p2),QT_GENARG(p3),QT_GENARG(p4)

#define QTQUICK_SETDATA1(o,p1)          QMetaObject::invokeMethod(o,"setData",QT_GENARC_LIST1(p1))
#define QTQUICK_SETDATA2(o,p1,p2)       QMetaObject::invokeMethod(o,"setData",QT_GENARC_LIST2(p1,p2))
#define QTQUICK_SETDATA3(o,p1,p2,p3)    QMetaObject::invokeMethod(o,"setData",QT_GENARC_LIST3(p1,p2,p3))
#define QTQUICK_SETDATA4(o,p1,p2,p3,p4) QMetaObject::invokeMethod(o,"setData",QT_GENARC_LIST4(p1,p2,p3,p4))

// User has to be very patient now
#define QT_WAIT_BEGIN QApplication::setOverrideCursor(QCursor(Qt::WaitCursor)); {

// User may continue working
#define QT_WAIT_END } QApplication::restoreOverrideCursor();

#endif // WMSMACROS_H
