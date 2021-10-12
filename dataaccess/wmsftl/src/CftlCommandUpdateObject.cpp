// System and Qt Includes
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

// own Includes
#include "CftlJournal.h"
#include "CftlCommandDeleteObject.h"
#include "CftlCommandCheckObjectLocked.h"
#include "CftlContainerTableUpdate.h"
#include "CftlContainerTableInsert.h"
#include "CftlCommandUpdateObject.h"

CftlCommandUpdateObject::CftlCommandUpdateObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpObject(p_pObject)
{
}

CftlCommandUpdateObject::~CftlCommandUpdateObject()
{

}

bool CftlCommandUpdateObject::CheckValid()
{
    return (CHKPTR(m_rpObject));
}

int CftlCommandUpdateObject::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;


    CftlCommandCheckObjectLocked command(m_rpObject, GetDataAccess());
    if(!SUCCESSFULL(command.Run())) // is not locked
    {
        if((m_rpObject->IsNew() || m_rpObject->IsModified()) && !m_rpObject->IsDeleted() && m_rpObject->IsValid())
        {
            lRet = UpdateNewOrModifiedObject();

            if (lRet < 0)
            {
                ERR("UpdateNewOrModifiedObject failed!");
            }
        }
        else if(m_rpObject->IsDeleted() || !m_rpObject->IsValid())
        {
            CftlCommandDeleteObject command(m_rpObject, GetDataAccess());
            lRet = command.Run();

            if(lRet > 0)
            {
                CdmDataAccessHelper::DeleteObject(m_rpObject);
            }
            else
            {
                ERR("DeleteObject failed!");
            }
        }
        else
        {
            // is not new deleted or modified
            // so nothing is to do
            lRet = EC(eDmOk);
        }
    }
    else
    {
        lRet = EC(eDmObjectDeathLock);
        ERR("Cannot update object because it is locked.");
    }

    return lRet;
}

qint64 CftlCommandUpdateObject::UpdateNewOrModifiedObject()
{
    CftlContainerTableUpdate update(m_rpObject, GetDialect());
    return update.Execute(GetInterface());
}

