#include <QFileInfo>

// WMS includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmValue.h"
#include "CdmLogging.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListString.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueListObjects.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"
#include "CdmValueEnum.h"
#include "CdmDataAccessHelper.h"

// Own Includes
#include "CwmsUtilities.h"
#include "CftlObjectReader.h"
#include "CftlContainerTableSelect.h"
#include "CftlCommandLoadObjects.h"

CftlCommandLoadObjects::CftlCommandLoadObjects(CdmObjectContainer* p_pContainer, QList<long>& p_qlObjectIds, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer),
      m_qvlObjectIds(p_qlObjectIds)
{
}

CftlCommandLoadObjects::CftlCommandLoadObjects(CdmObjectContainer *p_pContainer, QList<QString> &p_qlObjectKeynames, CftlDataAccess *p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer),
      m_qvlObjectKeynames(p_qlObjectKeynames)
{

}

CftlCommandLoadObjects::CftlCommandLoadObjects(CdmObjectContainer *p_pContainer, CftlDataAccess *p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer)
{

}

CftlCommandLoadObjects::~CftlCommandLoadObjects()
{

}

bool CftlCommandLoadObjects::CheckValid()
{
    return (CHKPTR(m_rpContainer));
}


int CftlCommandLoadObjects::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    CdmObject* pObject = nullptr;
    CftlContainerTableSelect selector(m_rpContainer, GetDialect());
    selector.SetObjectList(m_qvlObjectIds);
    selector.SetObjectList(m_qvlObjectKeynames);
    selector.Execute(GetInterface());
    QSqlQuery& cQSqlQuery = selector.GetQuery();
    cQSqlQuery.first();

    while (cQSqlQuery.isValid())
    {
        long lObjectId       = cQSqlQuery.value(0).toInt();
        QString qstrKeyname  = cQSqlQuery.value(1).toString();
        QString qstrCaption  = cQSqlQuery.value(2).toString();
        QDateTime qdLastChange = cQSqlQuery.value(3).toDateTime();
        long lCreatorId      = cQSqlQuery.value(4).toInt();
        long lLastModifierId = cQSqlQuery.value(5).toInt();
        long lParent         = cQSqlQuery.value(6).toInt();
        QString qstrConfig   = cQSqlQuery.value(7).toString(); // TODO derive object from config class!!!
        long lClassId        = m_rpContainer->GetClassId();
        long lDataBaseId     = m_rpContainer->GetSchemeId();

        pObject = CdmDataAccessHelper::CreateObject(lDataBaseId,
                                                   lObjectId,
                                                   lClassId,
                                                   m_rpContainer->GetId());

        INFO("Object with Id " + QString::number(pObject->GetId()) + " created");

        pObject->SetCaption(qstrCaption);
        pObject->SetParent(lParent);
        CdmDataAccessHelper::SetKeyname(pObject, qstrKeyname);
        CdmDataAccessHelper::SetCreatorId(pObject, lCreatorId);
        CdmDataAccessHelper::SetModifierId(pObject, lLastModifierId);
        CdmDataAccessHelper::SetValid(pObject);
        INFO("Object still has Id " + QString::number(pObject->GetId()));
        CdmDataAccessHelper::AddObjectToObjectList(pObject, m_rpContainer);
        INFO("Object still has Id " + QString::number(pObject->GetId()));
        CftlObjectReader::ReadValues(selector, cQSqlQuery, pObject);
        pObject->SetLastChange(qdLastChange);
        pObject->ResetNewModified();
        INFO("Object with Id " + QString::number(pObject->GetId()) + " creation finished");
        lRet = EC(eDmTrue);
        cQSqlQuery.next();
    }

    return lRet;
}


