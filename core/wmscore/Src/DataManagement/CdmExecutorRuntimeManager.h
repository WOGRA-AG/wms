#ifndef CDMEXECUTORRUNTIMEMANAGER_H
#define CDMEXECUTORRUNTIMEMANAGER_H

// System and QT Includes
#include <QMap>
#include <QMutex>

// WMS Commons Includes
#include "CwmsSynchronizable.h"
// own Includes
#include "datamanager.h"

// Forwards
class QScriptEngine;
class IdmExecutorEngine;
class CdmExecutorRuntime;

class WMSMANAGER_API CdmExecutorRuntimeManager : CwmsSynchronizable
{
private:
    QMap<IdmExecutorEngine*,CdmExecutorRuntime*> m_qmRuntimes;

public:
    CdmExecutorRuntimeManager();
    ~CdmExecutorRuntimeManager();
    int GetActiveRuntimesCount();
    void EndRuntime(IdmExecutorEngine *p_pEngine);
    CdmExecutorRuntime *CreateOrGetRuntime(IdmExecutorEngine *p_pEngine);
    bool IsScriptRunning();
    bool NeedsCurrentThisObjectUpdate(CdmObject *p_pObject);
    CdmExecutorRuntime *GetRuntime(IdmExecutorEngine *p_pEngine);
};

#endif // CDMEXECUTORRUNTIMEMANAGER_H
