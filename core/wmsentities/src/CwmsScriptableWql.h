#ifndef CWMSSCRIPTABLEWQL_H
#define CWMSSCRIPTABLEWQL_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>
#include <QVariant>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CdmQuery;
class CdmQueryEnhanced;


// TypeDefs


/* 
 * This class implements the script interface for js methods using wql
 */
class BASETOOLS_API CwmsScriptableWql : public CwmsScriptableBase
{
   Q_OBJECT

   public:
    CwmsScriptableWql();
    virtual ~CwmsScriptableWql();

    public slots:
    QObject* execute(QString p_qstrWql);

};

#endif // CWMSSCRIPTABLEWQL_H
