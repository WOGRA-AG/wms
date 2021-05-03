// WMS includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmDataAccessHelper.h"

// Own Includes
#include "CwmsUtilities.h"
#include "CftlCommandLoadObjects.h"
#include "CftlCommandLoadSingleObject.h"

CftlCommandLoadSingleObject::CftlCommandLoadSingleObject(CdmObjectContainer* p_pContainer, long p_lObjectId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer),
      m_lObjectId(p_lObjectId),
      m_rpObject(nullptr)
{
}

CftlCommandLoadSingleObject::CftlCommandLoadSingleObject(CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer),
      m_qstrKeyname(p_qstrKeyname),
      m_lObjectId(-1),
      m_rpObject(nullptr)
{
}

CftlCommandLoadSingleObject::~CftlCommandLoadSingleObject()
{

}

CdmObject *CftlCommandLoadSingleObject::GetResult()
{
    return m_rpObject;
}

bool CftlCommandLoadSingleObject::CheckValid()
{
    return (m_rpContainer != nullptr && (m_lObjectId > 0 || !m_qstrKeyname.isEmpty()));
}


int CftlCommandLoadSingleObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    QScopedPointer<CftlCommandLoadObjects> pCommand;

    if (m_lObjectId > 0)
    {
        QList<long> qllObjects;
        qllObjects.append(m_lObjectId);
        pCommand.reset(new CftlCommandLoadObjects(m_rpContainer, qllObjects, GetDataAccess()));
    }
    else if (!m_qstrKeyname.isEmpty())
    {
        QList<QString> qllObjects;
        qllObjects.append(m_qstrKeyname);
        pCommand.reset(new CftlCommandLoadObjects(m_rpContainer, qllObjects, GetDataAccess()));
    }
    else
    {
        return lRet;
    }

    lRet = pCommand->Run();

    if (SUCCESSFULL(lRet))
    {
        if (m_lObjectId > 0)
        {
            m_rpObject = m_rpContainer->FindObjectByIdLocal(m_lObjectId);
        }
        else
        {
            m_rpObject = m_rpContainer->FindObjectByKeyname(m_qstrKeyname);
        }
    }

    return lRet;
}

