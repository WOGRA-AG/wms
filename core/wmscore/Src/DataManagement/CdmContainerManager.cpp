/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdom.h>
#include <QFile>
#include <QTextStream>
#include <qdatetime.h>
#include <QLinkedList>


// own Includes
#include "wmsdefines.h"
#include "CdmMessageManager.h"
#include "CdmScheme.h"
#include "CdmValue.h"
#include "CwmsJson.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmLogging.h"
#include "IdmDataAccess.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"


/** +-=---------------------------------------------------------Sa 20. Aug 10:33:20 2005----------*
 * @method  CdmContainerManager::CdmContainerManager       // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @comment The Constructor of the ObjectListManager                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 10:33:20 2005----------*/
CdmContainerManager::CdmContainerManager(long p_lDatabaseId)
    : CdmModelElementBase(p_lDatabaseId)
{
    // nothing to do :-)
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:47:55 2005----------*
 * @method  CdmContainerManager::~CdmContainerManager      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmContainerManager                                          *
 *----------------last changed: --------------------------------Sa 20. Aug 12:47:55 2005----------*/
CdmContainerManager::~CdmContainerManager(  )
{
    QMap<long,CdmObjectContainer*>::iterator qmIt    = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::iterator qmItEnd = m_qmContainer.end();

    for ( ; qmIt != qmItEnd; ++qmIt )
    {
        CdmObjectContainer* pContainer = qmIt.value();
        DELPTR(pContainer);
    }

    m_qmContainer.clear();
}

/** +-=---------------------------------------------------------Di 20. Nov 10:36:53 2012----------*
 * @method  CdmContainerManager::RemoveContainerLocally   // public, slots                     *
 * @return  void                                             //                                   *
 * @comment This method removes all objectlists locally. the cahnges on them won't be saved.      *
 *----------------last changed: --------------------------------Di 20. Nov 10:36:53 2012----------*/
void CdmContainerManager::RemoveContainerLocally()
{
    SYNCHRONIZED;
    QMap<long,CdmObjectContainer*>::iterator qmIt    = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::iterator qmItEnd = m_qmContainer.end();

    for ( ; qmIt != qmItEnd; ++qmIt )
    {
        CdmObjectContainer* pContainer = qmIt.value();
        DELPTR(pContainer);
    }

    m_qmContainer.clear();
}

/** +-=---------------------------------------------------------Di 20. Nov 10:36:59 2012----------*
 * @method  CdmContainerManager::RemoveContainerLocally    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment This method removes a objectlists locally no changes will be saved!!!                 *
 *----------------last changed: --------------------------------Di 20. Nov 10:36:59 2012----------*/
void CdmContainerManager::RemoveContainerLocally(CdmObjectContainer* p_pContainer)
{
    SYNCHRONIZED;
    m_qmContainer.remove(p_pContainer->GetId());
    DELPTR(p_pContainer);
}

/** +-=---------------------------------------------------------Di 20. Nov 10:37:06 2012----------*
 * @method  CdmContainerManager::RemoveContainerLocally    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment This method removes a objectlists locally no changes will be saved!!!                 *
 *----------------last changed: --------------------------------Di 20. Nov 10:37:06 2012----------*/
void CdmContainerManager::RemoveContainerLocally(long p_lObjectListId)
{
    CdmObjectContainer* pContainer = FindContainerById(p_lObjectListId);

    if(CHKPTR(pContainer))
    {
        RemoveContainerLocally(pContainer);
    }
}

/** +-=---------------------------------------------------------Di 20. Nov 10:37:16 2012----------*
 * @method  CdmContainerManager::RemoveContainerLocally    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment This method removes a objectlists locally no changes will be saved!!!                 *
 *----------------last changed: --------------------------------Di 20. Nov 10:37:16 2012----------*/
void CdmContainerManager::RemoveContainerLocally(QString p_qstrName)
{
    CdmObjectContainer* pContainer = FindContainerByKeyname(p_qstrName);

    if(CHKPTR(pContainer))
    {
        RemoveContainerLocally(pContainer);
    }
}


/** +-=---------------------------------------------------------Di 20. Nov 10:37:26 2012----------*
 * @method  CdmContainerManager::CreateContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QString& p_qstrKeyname                           //                                   *
 * @comment This emthod creates a new object list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 10:37:26 2012----------*/
int CdmContainerManager::CreateContainer(CdmClass* p_pCdmClass, QString& p_qstrKeyname)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;

    if(CHKPTR(p_pCdmClass))
    {
        int iCounter = 0;
        while(FindEmptyContainerByKeyname(p_qstrKeyname))
        {
            WARNING("Container with Keyname \"" + p_qstrKeyname + "\" already exists creating with other keyname.");
            p_qstrKeyname += QString::number(iCounter);

            if (iCounter >= 1000)
            {
                FATAL("Container cannot be created because there are two many other objectlists which makes namingproblems");
            }

            ++iCounter;

        }

        long lId = GetNewContainerId(p_pCdmClass->GetId());

        if(lId > 0)
        {
            CdmObjectContainer* pContainer = new CdmObjectContainer(GetSchemeId(),
                                                                    lId,
                                                                    p_qstrKeyname,
                                                                    p_pCdmClass);

            pContainer->SetCreatorId(GetUserId());
            pContainer->SetModifierId(GetUserId());
            pContainer->SetNew();


            {
                m_qmContainer.insert(lId, pContainer);
            }

            iRet = pContainer->Commit();
        }
        else
        {
            ERR("Invalid Container Id!!!");
            iRet = lId;
        }

    }

    return iRet;
}



/** +-=---------------------------------------------------------Di 20. Nov 10:37:50 2012----------*
 * @method  CdmContainerManager::CreateContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @param   QString& p_qstrKeyname                           //                                   *
 * @comment This method creates a new object list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 10:37:50 2012----------*/
int CdmContainerManager::CreateContainer(long p_lClassId, QString& p_qstrKeyname)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;

    CdmClassManager* pCdmClassManager = GetClassManager();

    if(CHKPTR(pCdmClassManager))
    {
        CdmClass* pCdmClass = pCdmClassManager->FindClassById(p_lClassId);

        if(CHKPTR(pCdmClass))
        {
            iRet = CreateContainer(pCdmClass, p_qstrKeyname);
        }
        else
        {
            iRet = EC(eDmInvalidClassPtr);
            ERR( "Class for this new Container not found!!!. ClassId: " + QString::number(p_lClassId) );
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
        FATAL( "There is no Classmanager for creating Container." );
    }

    return iRet;
}


/** +-=---------------------------------------------------------Di 20. Nov 10:38:02 2012----------*
 * @method  CdmContainerManager::CreateContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   QString p_qstrClassKeyname                       //                                   *
 * @param   QString& p_qstrObjectListKeyname                 //                                   *
 * @param   QString p_qstrObjectListCaption                  //                                   *
 * @param   QString p_qstrObjectListComment                  //                                   *
 * @comment This method creates a new objectlist.                                                 *
 *----------------last changed: --------------------------------Di 20. Nov 10:38:02 2012----------*/
int CdmContainerManager::CreateContainer(QString p_qstrClassKeyname,
                                         QString& p_qstrObjectListKeyname,
                                         QString p_qstrObjectListCaption,
                                         QString p_qstrObjectListComment)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;

    iRet = CreateContainer(p_qstrClassKeyname, p_qstrObjectListKeyname);

    if (iRet > 0)
    {
        CdmObjectContainer* pContainer = FindContainerByKeyname(p_qstrObjectListKeyname);

        if (CHKPTR(pContainer))
        {
            pContainer->SetCaption(p_qstrObjectListCaption);
            pContainer->SetComment(p_qstrObjectListComment);
            pContainer->Commit();
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:38:12 2012----------*
 * @method  CdmContainerManager::CreateContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   QString p_qstrClassKeyname                       //                                   *
 * @param   QString& p_qstrObjectListKeyname                 //                                   *
 * @param   QString p_qstrObjectListCaption                  //                                   *
 * @param   QString p_qstrObjectListComment                  //                                   *
 * @param   bool p_bTree                                     //                                   *
 * @comment This method creates a new objectlist.                                                 *
 *----------------last changed: --------------------------------Di 20. Nov 10:38:12 2012----------*/
int CdmContainerManager::CreateContainer(QString p_qstrClassKeyname,
                                         QString& p_qstrObjectListKeyname,
                                         QString p_qstrObjectListCaption,
                                         QString p_qstrObjectListComment,
                                         bool p_bTree)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;

    iRet = CreateContainer(p_qstrClassKeyname, p_qstrObjectListKeyname);

    if (iRet > 0)
    {
        CdmObjectContainer* pContainer = FindContainerByKeyname(p_qstrObjectListKeyname);

        if (CHKPTR(pContainer))
        {
            pContainer->SetCaption(p_qstrObjectListCaption);
            pContainer->SetComment(p_qstrObjectListComment);
            pContainer->SetTree(p_bTree);
            pContainer->Commit();
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:38:49 2012----------*
 * @method  CdmContainerManager::CreateContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   QString p_qstrClassKeyname                       //                                   *
 * @param   QString& p_qstrObjectListKeyname                 //                                   *
 * @comment This method creates a new objectlist.                                                 *
 *----------------last changed: --------------------------------Di 20. Nov 10:38:49 2012----------*/
int CdmContainerManager::CreateContainer(QString p_qstrClassKeyname,
                                         QString& p_qstrObjectListKeyname)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;
    CdmClassManager* pCdmClassManager = GetClassManager();

    if(CHKPTR(pCdmClassManager))
    {
        CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(p_qstrClassKeyname);

        if(CHKPTR(pCdmClass))
        {
            iRet = CreateContainer(pCdmClass, p_qstrObjectListKeyname);
        }
        else
        {
            iRet = EC(eDmInvalidClassPtr);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:39:01 2012----------*
 * @method  CdmContainerManager::FindContainerByIdLocal         // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment This method finds a objectlist or returns nullptr. The objectlist will be completly      *
 *----------------last changed: --------------------------------Di 20. Nov 10:39:01 2012----------*/
CdmObjectContainer* CdmContainerManager::FindContainerByIdLocal(long p_lObjectListId)
{
    CdmObjectContainer* pContainer = nullptr;

    if (p_lObjectListId > 0)
    {
        SYNCHRONIZED;
        // first step looking for objetclist in RAM
        pContainer = m_qmContainer[p_lObjectListId];

        if(pContainer)
        {
            if(pContainer->IsDeleted())
            {
                INFO("ObjectList was found but it has an deleted flag.");
                pContainer = nullptr;
            }
            else
            {
                INFO("ObjectList found.");
            }
        }


    }

    return pContainer;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:39:01 2012----------*
 * @method  CdmContainerManager::FindContainerById         // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment This method finds a objectlist or returns nullptr. The objectlist will be completly      *
 *----------------last changed: --------------------------------Di 20. Nov 10:39:01 2012----------*/
CdmObjectContainer* CdmContainerManager::FindContainerById(long p_lObjectListId)
{
    SYNCHRONIZED;
    CdmObjectContainer* pContainer = FindContainerByIdLocal(p_lObjectListId);

    // if not found in RAM it will be searched on the server
    if(!pContainer)
    {
        INFO("Object list locally not found, now it will be searched on the server!!!");
        IdmDataAccess* pIdmDataAccess = GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
            pIdmDataAccess->LoadObjectContainer(p_lObjectListId, pContainer);
            if(pContainer)
            {
                m_qmContainer.insert(pContainer->GetId(), pContainer);
            }
        }
    }

    return pContainer;
}


/** +-=---------------------------------------------------------Di 20. Nov 10:39:12 2012----------*
 * @method  CdmContainerManager::FindContainerByKeyname    // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method finds a objectlist by keyname or if not found nullptr will returned. It      *
 *----------------last changed: --------------------------------Di 20. Nov 10:39:12 2012----------*/
CdmObjectContainer* CdmContainerManager::FindContainerByKeyname(QString p_qstrKeyname)
{
    SYNCHRONIZED;
    CdmObjectContainer* pContainer = nullptr;
    QMap<long,CdmObjectContainer*>::iterator qmIt    = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::iterator qmItEnd = m_qmContainer.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmObjectContainer* pContainerTemp = qmIt.value();

        if (pContainerTemp && pContainerTemp->GetKeyname() == p_qstrKeyname)
        {
            if (!pContainerTemp->IsDeleted())
            {
                pContainer = pContainerTemp;
            }
            
            break;
        }
    }

    if(!pContainer)
    {
        IdmDataAccess* pIdmDataAccess = GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
            pIdmDataAccess->LoadObjectContainer(GetSchemeId(), p_qstrKeyname, pContainer);
            if(pContainer)
            {
                m_qmContainer.insert(pContainer->GetId(), pContainer);
            }
        }
    }

    return pContainer;
}


/** +-=---------------------------------------------------------Di 20. Nov 10:39:23 2012----------*
 * @method  CdmContainerManager::FindEmptyContainerByKeyname // public, slots                   *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method finds the objectlist by keyname. If not found nullptr will returned. It      *
 *----------------last changed: --------------------------------Di 20. Nov 10:39:23 2012----------*/
CdmObjectContainer* CdmContainerManager::FindEmptyContainerByKeyname(QString p_qstrKeyname)
{
    CdmObjectContainer* pContainer = nullptr;

    SYNCHRONIZED;
    QMap<long,CdmObjectContainer*>::iterator qmIt    = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::iterator qmItEnd = m_qmContainer.end();

    for(; qmIt != qmItEnd; ++qmIt)
    {
        CdmObjectContainer* pContainerTemp = qmIt.value();

        if (pContainerTemp && pContainerTemp->GetKeyname() == p_qstrKeyname)
        {
            if ( !pContainerTemp->IsDeleted() )
            {
                INFO("ObjectContainer found locally");
                pContainer = pContainerTemp;
            }
            
            break;
        }
    }

    if(!pContainer)
    {
        INFO("ObjectContainer locally not found, now it will be searched on the db!!!");
        IdmDataAccess* pIdmDataAccess = GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
            pIdmDataAccess->LoadEmptyObjectContainer(GetSchemeId(), p_qstrKeyname, pContainer);

            if(pContainer)
            {
                INFO("ObjectContainer found!!!");
                m_qmContainer.insert(pContainer->GetId(), pContainer);
            }
            else
            {
                INFO("ObjectContainer not found on the db!!!");
            }
        }
    }

    return pContainer;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:39:34 2012----------*
 * @method  CdmContainerManager::FindEmptyObjectListById    // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   long p_lId                                       //                                   *
 * @comment This method finds the objectlist by keyname. If not found nullptr will returned. It      *
 *----------------last changed: --------------------------------Di 20. Nov 10:39:34 2012----------*/
CdmObjectContainer* CdmContainerManager::FindEmptyContainerById(long p_lId)
{
    CdmObjectContainer* pContainer = FindContainerByIdLocal(p_lId);
    bool bContinueSearch = true;

    if(!pContainer && bContinueSearch)
    {
        INFO("Objectlist locally not found, now it will be searched on the db!!!");
        IdmDataAccess* pIdmDataAccess = GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
            pIdmDataAccess->LoadEmptyObjectContainer(GetSchemeId(), p_lId, pContainer);

            if(pContainer)
            {
                INFO("Objectlist found!!!");
                SYNCHRONIZED;
                m_qmContainer.insert(pContainer->GetId(), pContainer);
            }
            else
            {
                INFO("Objectlist not found on the db!!!");
            }
        }
    }

    return pContainer;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:39:55 2012----------*
 * @method  CdmContainerManager::DeleteContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment This method deletes an objectlist                                                     *
 *----------------last changed: --------------------------------Di 20. Nov 10:39:55 2012----------*/
int CdmContainerManager::DeleteContainer(CdmObjectContainer* p_pContainer)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;
    SYNCHRONIZED;
    if(p_pContainer)
    {
        long lId = p_pContainer->GetId();
        m_qmContainer.remove(lId);
        p_pContainer->SetDeleted();
        p_pContainer->Commit();
        iRet = EC(eDmOk);
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
        ERR("There is no valid ObjectList for deleting.");
    }



    return iRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:40:05 2012----------*
 * @method  CdmContainerManager::DeleteContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment This method deletes an objectlsit.                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 10:40:05 2012----------*/
int CdmContainerManager::DeleteContainer(long p_lObjectListId)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;
    CdmObjectContainer* pContainer = FindContainerById(p_lObjectListId);

    if(CHKPTR(pContainer))
    {
        iRet = DeleteContainer(pContainer);
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
        ERR("There is no valid ObjectList for deleting.");
    }

    return iRet;
}


/** +-=---------------------------------------------------------Di 20. Nov 10:40:17 2012----------*
 * @method  CdmContainerManager::DeleteContainer           // public, slots                     *
 * @return  int                                              //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method deltes an objectlist.                                                     *
 *----------------last changed: --------------------------------Di 20. Nov 10:40:17 2012----------*/
int CdmContainerManager::DeleteContainer(QString p_qstrKeyname)
{
    int iRet = CdmLogging::eDmUnknownObjectListError;
    CdmObjectContainer* pContainer = FindContainerByKeyname(p_qstrKeyname);

    if(CHKPTR(pContainer))
    {
        iRet = DeleteContainer(pContainer);
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
        ERR("There is no valid ObjectList for deleting.");
    }

    return iRet;
}

long CdmContainerManager::GetNewContainerId(long p_lClassId)
{
    long lId = CdmLogging::eDmUnknownObjectListError;

    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        lId = pIdmDataAccess->GetNewContainerId(p_lClassId);
    }
    else
    {
        lId = EC(eDmInvalidPtr);
        FATAL("There is no valid DataAccess for taking a new objectlist number.");
    }

    return lId;
}


/** +-=---------------------------------------------------------Di 20. Nov 10:40:35 2012----------*
 * @method  CdmContainerManager::CopyContainer             // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   CdmObjectContainer* p_pCdmObjetList                   //                                   *
 * @param   bool p_bComplete                                 // the complete list or the local copy*
 * @comment This method makes a copy from a objectlist. the copy will be isnerted in the          *
 *          objectlistmanager.                                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 10:40:35 2012----------*/
CdmObjectContainer* CdmContainerManager::CopyContainer(CdmObjectContainer* p_pCdmObjetList,
                                                       bool p_bComplete)
{
    CdmObjectContainer* pContainerNew = nullptr;

    if(p_bComplete)
    {
        if(CHKPTR(p_pCdmObjetList))
        {
            if (p_pCdmObjetList->IsModified() ||p_pCdmObjetList->IsNew())
            {
                p_pCdmObjetList->Commit();
            }

            ReloadContainerComplete(p_pCdmObjetList);
        }
    }

    if(CHKPTR(p_pCdmObjetList))
    {
        long lId = GetNewContainerId(p_pCdmObjetList->GetClassId());
        pContainerNew = new CdmObjectContainer(lId, p_pCdmObjetList);
        pContainerNew->SetNew();

        if(pContainerNew->Commit() >= 0)
        {
            {
                SYNCHRONIZED;
                m_qmContainer.insert(lId, pContainerNew);
            }
        }
        else
        {
            DELPTR(pContainerNew);
        }
    }

    return pContainerNew;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:40:57 2012----------*
 * @method  CdmContainerManager::CopyContainer             // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   long p_lObjetListId                              //                                   *
 * @param   bool p_bComplete                                 // the complete objectlist or the local*
 *                                                           //  part.                            *
 * @comment This method makes a copy from a objectlist. the copy will be isnerted in the          *
 *          objectlistmanager.                                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 10:40:57 2012----------*/
CdmObjectContainer* CdmContainerManager::CopyContainer(long p_lObjetListId, bool p_bComplete)
{
    CdmObjectContainer* pContainer = FindContainerById(p_lObjetListId);

    if(CHKPTR(pContainer))
    {
        pContainer = CopyContainer(pContainer, p_bComplete);
    }

    return pContainer;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:41:07 2012----------*
 * @method  CdmContainerManager::CopyContainer             // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool p_bComplete                                 // the complete objectlist or the local*
 *                                                           //  part                             *
 * @comment This method makes a copy from a objectlist. the copy will be isnerted in the          *
 *          objectlistmanager.                                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 10:41:07 2012----------*/
CdmObjectContainer* CdmContainerManager::CopyContainer(QString p_qstrKeyname, bool p_bComplete)
{
    CdmObjectContainer* pContainer = FindContainerByKeyname(p_qstrKeyname);

    if(CHKPTR(pContainer))
    {
        pContainer = CopyContainer(pContainer, p_bComplete);
    }

    return pContainer;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:41:21 2012----------*
 * @method  CdmContainerManager::GetContainerList          // public, slots                     *
 * @return  QLinkedList<QString>                             //                                   *
 * @param   QString p_qstrClassKeyName                       //                                   *
 * @comment Returns the list of objectlists of the current database.                              *
 *----------------last changed: --------------------------------Di 20. Nov 10:41:21 2012----------*/
QLinkedList<QString> CdmContainerManager::GetContainerList(QString p_qstrClassKeyName)
{
    QLinkedList<QString> qvlRet;
    CdmClassManager* pCdmClassManager = GetClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(p_qstrClassKeyName);

        if (CHKPTR(pCdmClass))
        {
            qvlRet = GetContainerList(pCdmClass->GetId());
        }
    }

    return qvlRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:41:32 2012----------*
 * @method  CdmContainerManager::GetContainerList          // public, slots                     *
 * @return  QLinkedList<QString>                             //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @comment Returns the list of objectlists of the current database.                              *
 *----------------last changed: --------------------------------Di 20. Nov 10:41:32 2012----------*/
QLinkedList<QString> CdmContainerManager::GetContainerList(long p_lClassId)
{
    SYNCHRONIZED;
    QLinkedList<QString> qvlRet;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if (CHKPTR(pIdmDataAccess))
    {
        QMap<long, QString> qmObjectLists;

        pIdmDataAccess->GetContainerList(GetSchemeId(),
                                         p_lClassId,
                                         qmObjectLists);

        QMap<long, QString>::iterator qmIt = qmObjectLists.begin();
        QMap<long, QString>::iterator qmItEnd = qmObjectLists.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            qvlRet.append(qmIt.value());
        }
    }

    return qvlRet;
}


/** +-=---------------------------------------------------------So 10. Feb 09:55:01 2013----------*
 * @method  CdmContainerManager::XmlExport                  // public, const, virtual            *
 * @return  int                                              //                                   *
 * @param   QDomElement& p_rqdeObjectListManager             //                                   *
 * @comment exports the database to a xml file.                                                   *
 *----------------last changed: --------------------------------So 10. Feb 09:55:01 2013----------*/
int CdmContainerManager::XmlExport(QDomElement& p_rqdeObjectListManager) const
{
    int iRet = CdmLogging::eDmUnknownObjectListError;

    QMap<long,CdmObjectContainer*>::const_iterator qmIt    = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::const_iterator qmItEnd = m_qmContainer.end();

    for(; qmIt != qmItEnd; ++qmIt)
    {
        CdmObjectContainer* pContainerTemp = qmIt.value();

        if(CHKPTR(pContainerTemp))
        {
            iRet = pContainerTemp->XmlExport(p_rqdeObjectListManager);
        }
    }

    return iRet;
}


/** +-=---------------------------------------------------------Sa 20. Aug 10:40:09 2005----------*
 * @method  CdmContainerManager::XmlImport                  // public                            *
 * @return  int                                              //                                   *
 * @param   QDomElement& p_rqdeObjectListManager             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 10:40:09 2005----------*/
int CdmContainerManager::XmlImport(  QDomElement& p_rqdeObjectListManager )
{
    int iRet = CdmLogging::eDmUnknownObjectListError;

    QDomNode qDomNode = p_rqdeObjectListManager.firstChild();
    while(!qDomNode.isNull())
    {
        QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.

        if(!qDomElement.isNull() && qDomElement.tagName() == WMS_CONTAINER)
        {
            QString qstrKeyname = qDomElement.attribute(WMS_KEYNAME);

            if(!qstrKeyname.isEmpty())
            {
                CdmObjectContainer* pContainer = FindContainerByKeyname(qstrKeyname);

                if(!pContainer)
                {
                    pContainer = new CdmObjectContainer(qDomElement);
                    //               pContainer->setParent(this);

                    if(pContainer->IsValid())
                    {
                        SYNCHRONIZED;
                        m_qmContainer.insert(pContainer->GetId(), pContainer);
                    }
                    else
                    {
                        DELPTR(pContainer);
                        ERR("Invalid Class created with XML Import");
                    }
                }
                else
                {
                    pContainer->XmlImport(qDomElement);
                }
            }
            else
            {
                ERR("Keyname not found in XML Attribute");
            }
        }
        else
        {
            ERR("Wrong XML Child on this position.");
        }

        qDomNode = qDomNode.nextSibling();
    }


    return iRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:42:00 2012----------*
 * @method  CdmContainerManager::ReloadContainerComplete   // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer*& p_rpContainer                //                                   *
 * @comment reloads the complete objectlist. it loads all objects.                                *
 *----------------last changed: --------------------------------Di 20. Nov 10:42:00 2012----------*/
void CdmContainerManager::ReloadContainerComplete(CdmObjectContainer*& p_rpContainer)
{
    if (CHKPTR(p_rpContainer))
    {
        p_rpContainer = ReloadContainerComplete(p_rpContainer->GetId());
    }
}

/** +-=---------------------------------------------------------Di 20. Nov 10:42:15 2012----------*
 * @method  CdmContainerManager::ReloadContainerComplete   // public, slots                     *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @comment reloads the complete objectlist. it loads all objects.                                *
 *----------------last changed: --------------------------------Di 20. Nov 10:42:15 2012----------*/
CdmObjectContainer* CdmContainerManager::ReloadContainerComplete(long p_lObjectListId)
{
    CdmObjectContainer* pContainer = nullptr;

    // ToDo the implementation is high risky because already existing pointer references
    // looses their validity
    RemoveContainerLocally(p_lObjectListId);
    pContainer = FindContainerById(p_lObjectListId);

    return pContainer;
}


CdmObject* CdmContainerManager::FindObject(long p_lContainerId, long p_lObjectId)
{
    CdmObject* pObject = nullptr;
    CdmObjectContainer* pContainer = FindEmptyContainerById(p_lContainerId);

    if (CHKPTR(pContainer))
    {
        pObject = pContainer->FindObjectById(p_lObjectId);
    }
    else
    {
        ERR("Container with Id " + QString::number(p_lContainerId) + " not found");
    }

    return pObject;
}

/** +-=---------------------------------------------------------So 10. Feb 09:55:17 2013----------*
 * @method  CdmContainerManager::GetVariant                 // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:55:17 2013----------*/
QVariant CdmContainerManager::GetVariant() const
{
    QVariantMap qvHash;
    QMap<long,CdmObjectContainer*>::const_iterator qmIt    = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::const_iterator qmItEnd = m_qmContainer.end();

    QVariantList qvObjectLists;
    for(; qmIt != qmItEnd; ++qmIt)
    {
        CdmObjectContainer* pContainerTemp = qmIt.value();

        if(CHKPTR(pContainerTemp))
        {
            qvObjectLists.append(pContainerTemp->GetVariant());
        }
    }

    qvHash.insert(WMS_CONTAINERS, qvObjectLists);
    return qvHash;
}

/** +-=---------------------------------------------------------So 10. Feb 09:55:27 2013----------*
 * @method  CdmContainerManager::GetDeploymentVariant       // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:55:27 2013----------*/
void CdmContainerManager::GetDeploymentVariant(CdmClass* p_pClass, QVariantList& p_rqvObjectContainers) const
{
    SYNCHRONIZED;
    if (CHKPTR(p_pClass))
    {
        QString qstrKeyname = p_pClass->GetKeyname();
        QLinkedList<QString> qllObjectLists;
        qllObjectLists = const_cast<CdmContainerManager*>(this)->GetContainerList(p_pClass->GetId());

        QLinkedList<QString>::iterator qllItOL = qllObjectLists.begin();
        QLinkedList<QString>::iterator qllItOLEnd = qllObjectLists.end();

        for (; qllItOL != qllItOLEnd; ++qllItOL)
        {
            CdmObjectContainer* pContainer = const_cast<CdmContainerManager*>(this)->FindEmptyContainerByKeyname(*qllItOL);

            if (CHKPTR(pContainer) &&
                    !GetScheme()->IsDeployedContainerId(pContainer->GetId()))
            {
                if (pContainer->IsDeploymentRelevant())
                {
                     if (pContainer->IsTechnicalDeploymentRelevant())
                     {
                        const_cast<CdmContainerManager*>(this)->ReloadContainerComplete(pContainer);
                     }

                     p_rqvObjectContainers.append(pContainer->GetVariant());
                }
                else
                {
                    p_rqvObjectContainers.append(pContainer->GetContainerDataVariant());
                }
            }
        }
    }
}


void CdmContainerManager::DeployNewContainer(QString qstrClassUri, QString qstrKeyname, QVariantMap qvObjectList)
{
    CdmClass* pClass = (CdmClass*)CdmSessionManager::GetDataProvider()->GetUriObject(qstrClassUri);

    if (CHKPTR(pClass))
    {
        qstrKeyname = qstrKeyname.simplified();
        qstrKeyname = qstrKeyname.replace(QRegExp("[^A-Za-z0-9_]"), "_");
        qstrKeyname = qstrKeyname.replace(":", "_");
        qstrKeyname = qstrKeyname.replace(".", "_");

        if (CreateContainer(pClass, qstrKeyname) > 0)
        {
            CdmObjectContainer* pContainer = FindEmptyContainerByKeyname(qstrKeyname);

            if (CHKPTR(pContainer))
            {
                pContainer->Deploy(qvObjectList);
            }
        }
    }
}

void CdmContainerManager::Deploy(QVariantList& p_rqvList)
{
    CdmMessageManager::StartProgressBar("DeployContainer", "Importiere Datencontainer", "Starte Import", p_rqvList.count());

    for (int iCounter = 0; iCounter < p_rqvList.count(); ++iCounter)
    {
        QVariantMap qvObjectList = p_rqvList[iCounter].toMap();
        QString qstrKeyname = qvObjectList[WMS_KEYNAME].toString();
        QString qstrClassUri = qvObjectList[WMS_CLASSURI].toString();

        if (!qstrKeyname.isEmpty())
        {
            CdmObjectContainer* pList = FindEmptyContainerByKeyname(qstrKeyname);

            if (pList)
            {
                const CdmClass* pClass = pList->GetClass();

                if (CHKPTR(pClass))
                {
                    QString qstrListUri = pClass->GetUriInternal();
                    CdmDataProvider::ReplaceUnnecessaryUriPartsAndScheme(qstrListUri);
                    CdmDataProvider::ReplaceUnnecessaryUriPartsAndScheme(qstrClassUri);
                    if (qstrListUri == qstrClassUri)
                    {
                        ReloadContainerComplete(pList); // must be loaded complete to find all object by keyname

                        if (pList)
                        {
                            pList->Deploy(qvObjectList);
                        }
                    }
                    else
                    {
                        DeployNewContainer(pClass->GetUriInternal(), qstrKeyname, qvObjectList);
                    }
                }
            }
            else
            {
                DeployNewContainer(qstrClassUri, qstrKeyname, qvObjectList);
            }
        }
        else
        {
            ERR("Empty Keyname found in list of object containers.")
        }

        CdmMessageManager::SetProgress("DeployContainer", tr("Importiere Datencontainer ") + QString::number(iCounter) + tr(" von ") + QString::number(p_rqvList.count()), iCounter);
    }

    CdmMessageManager::CloseProgressBar("DeployContainer");

    DeploymentResolveValue();
    Commit();
}

/** +-=---------------------------------------------------------So 18. Aug 10:14:41 2013----------*
 * @method  CdmContainerManager::Commit                      // public                            *
 * @return  void                                             //                                   *
 * @comment Commits all modified objectcontainers.                                                *
 *----------------last changed: --------------------------------So 18. Aug 10:14:41 2013----------*/
void CdmContainerManager::Commit()
{
    SYNCHRONIZED;
    QMap<long,CdmObjectContainer*>::iterator qmIt = m_qmContainer.begin();
    QMap<long,CdmObjectContainer*>::iterator qmItEnd = m_qmContainer.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmObjectContainer* pContainer = qmIt.value();

        if (CHKPTR(pContainer) && pContainer->IsModified())
        {
            pContainer->Commit();
        }
    }
}

/** +-=---------------------------------------------------------Do 13. Dez 08:25:08 2012----------*
 * @method  CdmContainerManager::DeploymentResolveValue     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 08:25:08 2012----------*/
void CdmContainerManager::DeploymentResolveValue()
{
    CdmMessageManager::StartProgressBar("ResolveValues", "Löse Werte auf", "Löse Werte auf", m_qlToResolve.count());

    for (int iCounter = 0; iCounter < m_qlToResolve.count(); ++iCounter)
    {
        QString qstrUri =  m_qlToResolve[iCounter];
        CdmValue* pValue = dynamic_cast<CdmValue*>(GetDataProvider()->GetUriObject(qstrUri));

        if (CHKPTR(pValue))
        {
            if (!pValue->ResolveValue())
            {
                ERR(tr("Wert konnte nicht aufgelöst werden.\nWert konnte nicht aufgelöst werden! URI: ") + pValue->GetUri());
            }
        }

        CdmMessageManager::SetProgress("ResolveValues", tr("Löse Werte ") + QString::number(iCounter) + tr(" von ") + QString::number(m_qlToResolve.count()) + " auf.", iCounter);
    }

    CdmMessageManager::CloseProgressBar("ResolveValues");
}

/** +-=---------------------------------------------------------Do 13. Dez 08:24:37 2012----------*
 * @method  CdmContainerManager::AddDeploymentResolveValue  // public                            *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 08:24:37 2012----------*/
void CdmContainerManager::AddDeploymentResolveValue(CdmValue* p_pCdmValue)
{
    m_qlToResolve.append(p_pCdmValue->GetUriInternal());
}

QString  CdmContainerManager::GetUri() const
{
    return CreateUri(WMS_URI_CONTAINER_MANAGER, "");
}

QString CdmContainerManager::GetUriInternal() const
{
    return CreateUriPath(WMS_URI_CONTAINER_MANAGER, "", "", "");
}

bool CdmContainerManager::IsContainerManager() const
{
    return true;
}
