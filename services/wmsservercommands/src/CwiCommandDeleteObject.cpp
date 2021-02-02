#include "CwiCommandDeleteObject.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"


CwiCommandDeleteObject::CwiCommandDeleteObject(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandDeleteObject::~CwiCommandDeleteObject()
{

}

void CwiCommandDeleteObject::Execute()
{
    INFO("Delete Object called");
    CdmObject* pObject = nullptr;
    QString qstrOLKeyname = m_rpData->GetValue("Keyname").toString();
    QList<QVariant> qlObjectsToDelete = m_rpData->GetValue("ObjectIds").toList();
    INFO("Obejcts to delete: " + QString::number(qlObjectsToDelete.count()));

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
       bool bEveryObjectFound = true;
       CdmObjectContainer* pObjectList = pManager->GetObjectContainerEmpty(qstrOLKeyname);
       QString qstrMissingIds;

       if (CHKPTR(pObjectList))
       {
          for (int iCounter = 0; iCounter < qlObjectsToDelete.count(); ++iCounter)
          {
             pObject = pObjectList->FindObjectById(qlObjectsToDelete[iCounter].toInt());

             if (pObject)
             {
                 INFO("Object found counter: " + QString::number(iCounter));
                pObject->SetDeleted();
                pObjectList->ObjectDeletedSlot(pObject); // A HACK because signals and slots does not call this method automatically
             }
             else
             {
                bEveryObjectFound = false;
                qstrMissingIds += qlObjectsToDelete[iCounter].toString() + " ";
             }
          }

          if (pObjectList->Commit() > 0)
          {
              INFO("Commit successfull called");
             if (bEveryObjectFound)
             {
                 INFO("All objects deleted");
                GetResultContainer(m_rpData,
                                 1,
                                 "Object(s) deleted!",
                                 eWmscomMessageServerityInfo);
             }
             else
             {
                 WARNING("Objects to delte are missing. Perhaps they were deleted from other processes.");
                GetResultContainer(m_rpData,
                                 1,
                                 "found Object(s) deleted! but not every object was found. Missing Object Ids: " + qstrMissingIds,
                                 eWmscomMessageServerityWarning);
             }
          }
          else
          {
              ERR("Commit on Obejctcontainer failed.");
             GetResultContainer(m_rpData,
                -5000,
                "Object deletion failed! (DB Error)",
                eWmscomMessageServerityError);
          }
       }
       else
       {
           ERR("Objectcontainer was not found!");
          GetResultContainer(m_rpData,
                            -5000,
                            "objectlist for Object deletion not found!",
                            eWmscomMessageServerityFatal);
       }
    }
    else
    {
        ERR("Invalid Session!");
       GetResultContainer(m_rpData,
                         -5000,
                         "Invalid session object creation not possible!",
                         eWmscomMessageServerityFatal);
    }
}

