#ifndef CWMSSCRIPTABLEWORKFLOW_H
#define CWMSSCRIPTABLEWORKFLOW_H

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
class CdmObject;

// TypeDefs


/* 
 * This class implements the scriptinterface for workflows
 */
class BASETOOLS_API CwmsScriptableWorkflow : public CwmsScriptableBase
{
    Q_OBJECT

public:
    CwmsScriptableWorkflow( );
    virtual ~CwmsScriptableWorkflow( );

public slots:
    void StartWorkflow( CdmObject* p_pCdmObject);
    void UpdateWorkflow( CdmObject* p_pCdmObject);
};

#endif // CWMSSCRIPTABLEWORKFLOW_H
