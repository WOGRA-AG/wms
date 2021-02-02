#ifndef CWMSSYNCHRONIZABLE_H
#define CWMSSYNCHRONIZABLE_H

// System and Qt Includes
#include <QMutex>
#include <QMutexLocker>
#include <QWriteLocker>
#include <QReadLocker>

// own Includes
#include "wmscommons.h"

// MACROS

#define SYNCHRONIZED QMutexLocker lock(const_cast<QMutex*> (&m_qmSychnronizableMutex));
#define SYNCHRONIZED_WRITE QMutexLocker lock(const_cast<QMutex*> (&m_qmSychnronizableMutex));
#define SYNCHRONIZED_READ QMutexLocker lock(const_cast<QMutex*> (&m_qmSychnronizableMutex));

class WMSCOMMONS_API CwmsSynchronizable
{
protected:
    const QMutex m_qmSychnronizableMutex;

public:
    CwmsSynchronizable();
    virtual ~CwmsSynchronizable();
    const QMutex& GetMutex();
};

#endif // CWMSSYNCHRONIZABLE_H
