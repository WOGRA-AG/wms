#ifndef CWMSSCRIPTABLELOGGER_H
#define CWMSSCRIPTABLELOGGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CwmsbtMailMessage;

// TypeDefs


/* 
 * This class implements the the script interface for js methods
 */
class BASETOOLS_API CwmsScriptableLogger: public CwmsScriptableBase
{
    Q_OBJECT

public:
    CwmsScriptableLogger( );
    virtual ~CwmsScriptableLogger( );

public slots:
    void info( QString p_qstrMessage);
    void warning( QString p_qstrMessage);
    void error( QString p_qstrMessage);
    void fatal( QString p_qstrMessage);
};

#endif //
