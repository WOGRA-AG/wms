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
#include "CftlContainerTableSelect.h"
#include "CftlObjectReader.h"
#include "CftlCommandRefreshObject.h"

CftlCommandRefreshObject::CftlCommandRefreshObject(CdmObject* p_pCdmObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpObject(p_pCdmObject)
{
}

CftlCommandRefreshObject::~CftlCommandRefreshObject()
{

}

bool CftlCommandRefreshObject::CheckValid()
{
    return CHKPTR(m_rpObject);
}

int CftlCommandRefreshObject::Execute()
{
    int lRet = CdmLogging::eDmObjectAccessError;
    CftlContainerTableSelect selector(m_rpObject->GetObjectContainer(), GetDialect());
    QList<long> qllIds;
    qllIds.append(m_rpObject->GetId());
    selector.SetObjectList(qllIds);
    selector.Execute(GetInterface());
    QSqlQuery& cQSqlQuery = selector.GetQuery();
    cQSqlQuery.first();

    if (cQSqlQuery.isValid())
    {
        QString qstrKeyname  = cQSqlQuery.value(1).toString();
        QString qstrCaption  = cQSqlQuery.value(2).toString();
        QDateTime qdLastChange = cQSqlQuery.value(3).toDateTime();
        long lCreatorId      = cQSqlQuery.value(4).toInt();
        long lLastModifierId = cQSqlQuery.value(5).toInt();
        long lParent         = cQSqlQuery.value(6).toInt();
        QString qstrConfig   = cQSqlQuery.value(7).toString(); // TODO derive object from config class!!!

        m_rpObject->SetCaption(qstrCaption);
        m_rpObject->SetParent(lParent);
        CdmDataAccessHelper::SetKeyname(m_rpObject, qstrKeyname);
        CdmDataAccessHelper::SetCreatorId(m_rpObject, lCreatorId);
        CdmDataAccessHelper::SetModifierId(m_rpObject, lLastModifierId);
        CdmDataAccessHelper::SetValid(m_rpObject);
        CftlObjectReader::ReadValues(selector, cQSqlQuery, m_rpObject);
        m_rpObject->SetLastChange(qdLastChange);
        m_rpObject->ResetNewModified();
        INFO("Object with Id " + QString::number(m_rpObject->GetId()) + " creation finished");
        lRet = EC(eDmTrue);
    }

    return lRet;
}

