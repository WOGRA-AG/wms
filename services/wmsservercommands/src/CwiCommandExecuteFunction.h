#ifndef CWICOMMANDEXECUTEFUNCTION_H
#define CWICOMMANDEXECUTEFUNCTION_H

// System and Qt Includes
#include <QVariant>



// own Includes
#include "CwiAbstractCommand.h"

class CdmClassManager;
class CdmClassMethod;
class CdmContainerManager;
class CdmObject;
class CsaResultObject;

class CwiCommandExecuteFunction : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;
    QVariant ExecuteFunction(CdmContainerManager* pContainerManager);
    QVariant ExecuteStaticFunction(CdmClassManager* pCdmClassManager);
    QVariant Execute(CdmClassMethod *p_pMethod, CdmObject *p_pObject, QVariantList &p_rqvParameters);

public:
    CwiCommandExecuteFunction(CwmscomData* p_pData);
    virtual ~CwiCommandExecuteFunction();
    virtual void Execute();

};

#endif // CWICOMMANDEXECUTEFUNCTION_H
