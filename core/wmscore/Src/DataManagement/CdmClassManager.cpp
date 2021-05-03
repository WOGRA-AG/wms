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
#include <qfile.h>
#include <qtextstream.h>
#include <qstring.h>
#include <qdom.h>
#include <qdatetime.h>
#include <QList>
#include <QVariant>
#include <QDebug>


// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CdmMessageManager.h"
#include "CdmModelElement.h"
#include "CdmPackage.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "IdmDataAccess.h"
#include "CdmClass.h"
#include "CdmClassManager.h"


CdmClassManager::CdmClassManager(long p_lDbId)
    : CdmModelElementBase(p_lDbId)
{
}


CdmClassManager::~CdmClassManager(  )
{
    CdmClass* pCdmClass = nullptr;
    QMap<long,CdmClass*>::iterator qmiItClass = m_qmClasses.begin();
    QMap<long,CdmClass*>::iterator qmiItClassEnd = m_qmClasses.end();

    for (; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        pCdmClass = qmiItClass.value();

        if ( pCdmClass )
        {
            delete pCdmClass;
            pCdmClass = nullptr;
        }
    }

    m_qmClasses.clear();
}

/** +-=---------------------------------------------------------Mo 19. Nov 18:34:57 2012----------*
 * @method  CdmClassManager::FindClassById                   // public, slots                     *
 * @return  CdmClass*                                        // if not found nullptr will be returned*
 * @param   long p_lId                                       //                                   *
 * @comment This method searches for the class in the map and if found it will be returned.       *
 *----------------last changed: --------------------------------Mo 19. Nov 18:34:57 2012----------*/
CdmClass* CdmClassManager::FindClassById(long p_lId)
{
    CdmClass* pCdmClass = nullptr;
    SYNCHRONIZED_READ;
    if (m_qmClasses.contains(p_lId))
    {
        pCdmClass = m_qmClasses[p_lId];
    }

    return pCdmClass;
}

CdmClass* CdmClassManager::FindClassByKeyname(CdmPackage* p_pPackage, QString p_qstrKeyname)
{
    SYNCHRONIZED_READ;
    CdmClass* pClass = nullptr;

    if (p_pPackage)
    {
        pClass = FindClassByKeyname(p_pPackage->GetPackageString() + QStringLiteral(".") + p_qstrKeyname);
    }
    else
    {
        pClass = FindClassByKeyname(p_qstrKeyname);
    }

    return pClass;
}

/** +-=---------------------------------------------------------Mo 19. Nov 18:35:08 2012----------*
 * @method  CdmClassManager::FindClassByKeyname              // public, slots                     *
 * @return  CdmClass*                                        // if not found nullptr will returned   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment returns the class with the keyname p_qstrKeyname. If there is no class with this      *
 *----------------last changed: --------------------------------Mo 19. Nov 18:35:08 2012----------*/
CdmClass* CdmClassManager::FindClassByKeyname(QString p_qstrKeyname)
{
    SYNCHRONIZED_READ;
    CdmClass* pCdmClass = nullptr;
    QMap<long,CdmClass*>::iterator qmiItClass = m_qmClasses.begin();
    QMap<long,CdmClass*>::iterator qmiItClassEnd = m_qmClasses.end();

    for(; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        pCdmClass = qmiItClass.value();

        if(CHKPTR(pCdmClass))
        {
            if(pCdmClass->GetFullQualifiedName() == p_qstrKeyname)
            {
                break;
            }
            else
            {
                pCdmClass = nullptr;
            }
        }
    }

    return pCdmClass;
}

QList<CdmClass*> CdmClassManager::getEventClassList()
{
    SYNCHRONIZED_READ;
    CdmClass *pClass = nullptr;
    QList<CdmClass*> qlClasses;
    QMap<long,CdmClass*>::iterator qmiItClass = m_qmClasses.begin();
    QMap<long,CdmClass*>::iterator qmiItClassEnd = m_qmClasses.end();

    for(; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        pClass = qmiItClass.value();

        if(CHKPTR(pClass))
        {
            if(pClass->IsEventClass())
            {
                qlClasses.append(pClass);
            }
        }
    }
    return qlClasses;
}

CdmClass *CdmClassManager::findEventClassByKeyname(QString qstrKeyname)
{
    SYNCHRONIZED_READ;
    CdmClass* pCdmClass = nullptr;
    QList<CdmClass*> qlEventClasses = getEventClassList();

    for(int i = 0; i < qlEventClasses.count(); ++i)
    {
        pCdmClass = qlEventClasses.at(i);

        if(CHKPTR(pCdmClass))
        {
            if(pCdmClass->GetKeyname() == qstrKeyname)
            {
                break;
            }
            else
            {
                pCdmClass = nullptr;
            }
        }
    }
    return pCdmClass;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:16:47 2005----------*
 * @method  CdmClassManager::GetInheritedClasses             // public                            *
 * @return  int                                              //                                   *
 * @param   CdmClass* p_pCdmBaseClass                        //                                   *
 * @param   QList<CdmClass*>& p_rqvlClassList           //                                   *
 * @comment This method returns all classes which are inherited from this class.                  *
 *----------------last changed: --------------------------------Sa 13. Aug 21:16:47 2005----------*/
int CdmClassManager::GetInheritedClasses(  CdmClass* p_pCdmBaseClass,
                                           QList<CdmClass*>& p_rqvlClassList )
{
    int iRet = CdmLogging::eDmUnknownClassError;
    SYNCHRONIZED_READ;
    QMap<long,CdmClass*>::iterator qmiItClass = m_qmClasses.begin();
    QMap<long,CdmClass*>::iterator qmiItClassEnd = m_qmClasses.end();

    CdmClass* pCdmClass = nullptr;

    for(; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        pCdmClass = qmiItClass.value();

        if(CHKPTR(pCdmClass))
        {
            if(pCdmClass->IsInherited(p_pCdmBaseClass))
            {
                p_rqvlClassList.append(pCdmClass);
            }
        }
        else
        {
            iRet = EC(eDmInvalidPtr);
        }
    }

    if(CdmLogging::eDmUnknownClassError == iRet)
    {
        iRet = EC(eDmOk);
    }

    return iRet;
}

CdmClass* CdmClassManager::CreateClass(QString p_qstrKeyname, CdmPackage* p_pPackage)
{
    SYNCHRONIZED_WRITE;
    CdmClass* pClass = nullptr;

    if (!p_pPackage)
    {
        int pos = p_qstrKeyname.lastIndexOf(".");

        if (pos > 0)
        {
            p_qstrKeyname = p_qstrKeyname.mid(pos + 1, p_qstrKeyname.length() - pos - 1);
        }
        pClass = CreateClass(p_qstrKeyname);
    }
    else
    {
        pClass = FindClassByKeyname(p_qstrKeyname);

        if (!pClass)
        {
            int pos = p_qstrKeyname.lastIndexOf(".");

            if (pos > 0)
            {
                p_qstrKeyname = p_qstrKeyname.mid(pos + 1, p_qstrKeyname.length() - pos - 1);
            }

            pClass = CreateClassWithoutCheck(p_qstrKeyname);
            pClass->SetPackage(p_pPackage);
            //p_pPackage->AddClass(pClass);
        }
    }

    return pClass;
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:16:51 2005----------*
 * @method  CdmClassManager::CreateClass                     // public                            *
 * @return  CdmClass*                                        //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method creates a class and returns the pointer. This is the onliiest             *
 *          possibility to create a class.                                                        *
 *----------------last changed: --------------------------------Sa 13. Aug 21:16:51 2005----------*/
CdmClass* CdmClassManager::CreateClass(QString p_qstrKeyname)
{
    SYNCHRONIZED_WRITE;
    CdmClass* pCdmClass = nullptr;

    // check if keyname is already there
    pCdmClass = FindClassByKeyname(p_qstrKeyname);

    if (!pCdmClass)
    {
        pCdmClass = CreateClassWithoutCheck(p_qstrKeyname);
    }
    else
    {
        ERR("Could not create class with Keyname:\"" + p_qstrKeyname +
            "\". A class with this Keyname already exists." )
        EC(eDmKeynameAlreadyExists);
        pCdmClass = nullptr;
    }

    return pCdmClass;
}

CdmClass* CdmClassManager::CreateClassWithoutCheck(QString p_qstrKeyname)
{
    SYNCHRONIZED_WRITE;
    CdmClass* pCdmClass = nullptr;
    long lClassId = GetNewClassId();

    if(lClassId > 0)
    {
        pCdmClass = new CdmClass(GetSchemeId(), lClassId, p_qstrKeyname);
        pCdmClass->SetCreatorId(GetUserId());
        pCdmClass->SetModifierId(GetUserId());

        if (SUCCESSFULL(pCdmClass->Commit()))
        {
            SYNCHRONIZED;
            m_qmClasses.insert(lClassId, pCdmClass);
        }
        else
        {
            ERR("Commit failed")
            delete pCdmClass;
            pCdmClass = nullptr;
        }
    }
    else
    {
        ERR("Invalid classid from dataaccess returned. No creation posssible!!")
        EC(eDmInvalidId);
    }


    return pCdmClass;
}


/** +-=---------------------------------------------------------Mi 15. Sep 14:09:58 2010----------*
 * @method  CdmClassManager::CreateClass                     // private                           *
 * @return  CdmClass*                                        //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method creates a class and wit an Id and Keyname. This method is private,        *
 *          because it should only be used by itselves or by friend classes.                      *
 *----------------last changed: --------------------------------Mi 15. Sep 14:09:58 2010----------*/
CdmClass* CdmClassManager::CreateClass(long p_lId, QString p_qstrKeyname)
{
    SYNCHRONIZED_WRITE;
    CdmClass* pCdmClass = nullptr;

    // check if keyname is already there
    if(!FindClassByKeyname(p_qstrKeyname) && !FindClassById(p_lId))
    {
        if(p_lId > 0)
        {
            pCdmClass = new CdmClass(GetSchemeId(), p_lId, p_qstrKeyname);
            pCdmClass->SetCreatorId(GetUserId());
            pCdmClass->SetModifierId(GetUserId());
            SYNCHRONIZED;
            m_qmClasses.insert(p_lId, pCdmClass);
        }
        else
        {
            ERR("Invalid ClassId the Id must be larger then 0. No creation possible!!");
            EC(eDmInvalidId);
        }
    }
    else
    {
        ERR("Could not create class with Keyname:\"" + p_qstrKeyname +
            "\" and ID \"" + QString::number( p_lId ) + ". A class with this Keyname or ID already exists." );

        EC(eDmKeynameAlreadyExists);
    }

    return pCdmClass;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:17:04 2005----------*
 * @method  CdmClassManager::DeleteClass                     // public                            *
 * @return  int                                              //                                   *
 * @param   long p_lId                                       //                                   *
 * @comment removes a class from classmanager.                                                    *
 *----------------last changed: --------------------------------Sa 13. Aug 21:17:04 2005----------*/
int CdmClassManager::DeleteClass(long p_lId)
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmUnknownClassError;
    CdmClass* pCdmClass = nullptr;
    QMap<long,CdmClass*>::iterator qmiClass = m_qmClasses.find(p_lId);

    if(qmiClass != m_qmClasses.end())
    {
        pCdmClass = qmiClass.value();

        if(CHKPTR(pCdmClass))
        {
            if(!pCdmClass->IsInUse())
            {
                IdmDataAccess* pIdmDataAccess = GetDataAccess();

                if (CHKPTR(pIdmDataAccess))
                {
                    iRet = pIdmDataAccess->DeleteClass(pCdmClass->GetId());

                    if (SUCCESSFULL(iRet))
                    {
                        CdmPackage* pPackage = pCdmClass->GetPackage();

                        if (pPackage)
                        {
                            pPackage->RemoveClass(pCdmClass);
                        }

                        m_qmClasses.remove(qmiClass.key());
                        DELPTR(pCdmClass);
                    }
                    else
                    {
                        ERR("Could not delete class in DB");
                    }
                }
            }
            else
            {
                ERR("Class with Id \"" + QString::number( p_lId ) +
                    "\" is in use.\n Can not remove class." );
                iRet = EC(eDmClassUsageError);
            }
        }
        else
        {
            ERR("Class with Id \"" + QString::number( p_lId ) +
                "\" not found.\n Can not remove class." );
            iRet = EC(eDmInvalidClassPtr);
        }
    }
    else
    {
        ERR("Class with Id \"" + QString::number( p_lId ) +
            "\" not found.\n Can not remove class." );
        iRet = EC(eDmInvalidId);
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:17:10 2005----------*
 * @method  CdmClassManager::AddClass                        // private                           *
 * @return  int                                              //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment This methods adds a class.                                                            *
 *----------------last changed: --------------------------------Sa 13. Aug 21:17:10 2005----------*/
int CdmClassManager::AddClass(  CdmClass* p_pCdmClass )
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmUnknownClassError;

    if(CHKPTR(p_pCdmClass))
    {
        if (!FindClassById(p_pCdmClass->GetId()))
        {
            m_qmClasses.insert(p_pCdmClass->GetId(), p_pCdmClass);
            iRet = EC(eDmTrue);
        }
        else
        {
            iRet = EC(eDmClassAlreadyExist);
        }
    }
    else
    {
        iRet = EC(eDmInvalidClassPtr);
    }

    return iRet;
}

int CdmClassManager::DeleteClass(QString p_qstrClassName)
{
    int iRet = CdmLogging::eDmUnknownClassError;

    CdmClass* pClass = FindClassByKeyname(p_qstrClassName);

    if (CHKPTR(pClass))
    {
        iRet = DeleteClass(pClass);
    }
    else
    {
        ERR("Class not found for deletion");
        iRet = EC(eDmInvalidId);
    }


    return iRet;
}


int CdmClassManager::DeleteClass(CdmClass* p_pCdmClass)
{
    int iRet = CdmLogging::eDmUnknownClassError;

    if (CHKPTR(p_pCdmClass))
    {
        iRet = DeleteClass(p_pCdmClass->GetId());
    }
    else
    {
        iRet = CdmLogging::eDmInvalidClassPtr;
    }

    return iRet;
}

long CdmClassManager::GetNewClassId()
{
    long lId = CdmLogging::eDmUnknownClassError;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        lId = pIdmDataAccess->GetNewClassId(GetSchemeId());
    }
    else
    {
        lId = EC(eDmInvalidPtr);
    }

    return lId;
}

/** +-=---------------------------------------------------------Mo 19. Nov 18:35:47 2012----------*
 * @method  CdmClassManager::GetClassList                    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QList<CdmClass*>& p_pqlClasses             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Nov 18:35:47 2012----------*/
void CdmClassManager::GetClassList(QList<CdmClass*>& p_pqlClasses)
{
    SYNCHRONIZED_READ;
    CdmClass* pCdmClass = nullptr;

    QMap<long,CdmClass*>::iterator qmiItClass = m_qmClasses.begin();
    QMap<long,CdmClass*>::iterator qmiItClassEnd = m_qmClasses.end();

    for(; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        pCdmClass = qmiItClass.value();

        if(CHKPTR(pCdmClass))
        {
            p_pqlClasses.append(pCdmClass);
        }
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:18:33 2013-----------*
 * @method  CdmClassManager::ExistClass                      // public, const, slots              *
 * @return  int                                              //                                   *
 * @param   QString p_qstrClassKeyname                       //                                   *
 * @comment This method checks if a class exists or not.                                          *
 *----------------last changed: --------------------------------Sa 9. Feb 12:18:33 2013-----------*/
int CdmClassManager::ExistClass(QString p_qstrClassKeyname) const
{
    int iRet = CdmLogging::eDmUnknownClassError;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        bool bRet = false;
        iRet = pIdmDataAccess->ExistClass(GetSchemeId(),
                                          p_qstrClassKeyname,
                                          bRet);

        if(iRet < 0)
        {
            ERR("Error occured while checking if class exist. Errorcode: " + QString::number(iRet));
        }
        else
        {
            if(bRet)
            {
                iRet = EC(eDmTrue);
            }
            else
            {
                iRet = EC(eDmFalse);
            }
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}


/** +-=---------------------------------------------------------Sa 9. Feb 12:18:56 2013-----------*
 * @method  CdmClassManager::GenerateClassDocumentation      // public, const, slots              *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDatabase                           //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment This method generates the class documentation of the overgiven Database.              *
 *----------------last changed: --------------------------------Sa 9. Feb 12:18:56 2013-----------*/
void CdmClassManager::GenerateClassDocumentation(QString p_qstrDatabase, QString p_qstrFilename) const
{
    SYNCHRONIZED_READ;
    QString qstrDocument;
    qstrDocument = "<html>";
    qstrDocument += "<h1>WMS Class Documentation for Database " +  p_qstrDatabase + "</h1>";

    QMap<long, CdmClass*>::const_iterator qmiItClass = m_qmClasses.begin();
    QMap<long, CdmClass*>::const_iterator qmiItClassEnd = m_qmClasses.end();

    for(; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        CdmClass* pCdmClass = qmiItClass.value();

        if (CHKPTR(pCdmClass))
        {
            qstrDocument += pCdmClass->GenerateDocumentation();
        }
    }

    qstrDocument += "</html>";

    QFile qfFile(p_qstrFilename);

    if (qfFile.open(QIODevice::WriteOnly))
    {
        QTextStream qtsStream(&qfFile);
        qtsStream << qstrDocument;
        qfFile.close();
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:19:06 2013-----------*
 * @method  CdmClassManager::XmlExport                       // public, const                     *
 * @return  int                                              //                                   *
 * @param   QDomElement& p_rqdeClassManager                  //                                   *
 * @comment exports the database to a xml file.                                                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:19:06 2013-----------*/
int CdmClassManager::XmlExport(QDomElement& p_rqdeClassManager) const
{
    SYNCHRONIZED_READ;
    int iRet = CdmLogging::eDmUnknownClassError;
    QMap<long, CdmClass*>::const_iterator qmiItClass = m_qmClasses.begin();
    QMap<long, CdmClass*>::const_iterator qmiItClassEnd = m_qmClasses.end();

    for (; qmiItClass != qmiItClassEnd; ++qmiItClass)
    {
        CdmClass* pCdmClass = qmiItClass.value();

        if (CHKPTR(pCdmClass))
        {
            iRet = pCdmClass->XmlExport(p_rqdeClassManager);
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:17:38 2005----------*
 * @method  CdmClassManager::XmlImport                       // public                            *
 * @return  int                                              //                                   *
 * @param   QDomElement& p_rqdeClassManager                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:17:38 2005----------*/
int CdmClassManager::XmlImport(  QDomElement& p_rqdeClassManager )
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmUnknownClassError;

    QDomNode qDomNode = p_rqdeClassManager.firstChild();
    while(!qDomNode.isNull())
    {
        QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.
        iRet = XmlImportClass(qDomElement);
        qDomNode = qDomNode.nextSibling();
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:17:41 2005----------*
 * @method  CdmClassManager::XmlImportClass                  // private                           *
 * @return  int                                              //                                   *
 * @param   QDomElement& p_rqdeElement                       //                                   *
 * @comment This method imports or merges a single class.                                         *
 *----------------last changed: --------------------------------Sa 13. Aug 21:17:41 2005----------*/
int CdmClassManager::XmlImportClass(  QDomElement& p_rqdeElement )
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmUnknownClassError;

    if(!p_rqdeElement.isNull())
    {
        QString qstrKeyname = p_rqdeElement.attribute(WMS_KEYNAME, "");

        if(!qstrKeyname.isEmpty())
        {
            CdmClass* pCdmClass = FindClassByKeyname(qstrKeyname);

            if(!pCdmClass)
            {
                INFO("Class not found must be created");
                pCdmClass = new CdmClass(p_rqdeElement);

                if(pCdmClass->IsValid())
                {
                    SYNCHRONIZED;
                    m_qmClasses.insert(pCdmClass->GetId(), pCdmClass);
                }
                else
                {
                    DELPTR(pCdmClass);
                    ERR("Invalid Class read!!!");
                    iRet = EC(eDmXmlImportError);
                }
            }
            else
            {
                pCdmClass->XmlImport(p_rqdeElement);
            }
        }
        else
        {
            ERR("Keyname is missing at this class element!!!");
            iRet = EC(eDmXmlImportError);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}


/** +-=---------------------------------------------------------Sa 9. Feb 12:19:31 2013-----------*
 * @method  CdmClassManager::GetVariant                      // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:19:31 2013-----------*/
QVariant CdmClassManager::GetVariant() const
{
    QVariantMap qvClasses;
    SYNCHRONIZED_READ;
    QMap<long,CdmClass*>::const_iterator qmIt =  m_qmClasses.begin();
    QMap<long,CdmClass*>::const_iterator qmItEnd =  m_qmClasses.end();
    QVariantList qlClasses;
    QStringList qstrlClasses;

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClass* pCdmClass = qmIt.value();

        if (CHKPTR(pCdmClass))
        {
           CreateClassVariant(pCdmClass, qstrlClasses, qlClasses);
        }
    }

    qvClasses.insert(WMS_ECLASS, qlClasses);
    QVariantList qlPackages;

    for (int iPos = 0; iPos < m_qlPackages.count(); ++iPos)
    {
        CdmPackage* pPackage = m_qlPackages[iPos];

        if (CHKPTR(pPackage))
        {
            QVariant qvPackage = pPackage->GetVariant();
            qlPackages.append(qvPackage);
        }
    }

    qvClasses.insert(WMS_PACKAGE, qlPackages);
    return qvClasses;
}

void CdmClassManager::CreateClassVariant(CdmClass* pCdmClass, QStringList& qstrlClasses, QVariantList& p_rqlMap) const
{
   if (CHKPTR(pCdmClass))
   {
      if (!qstrlClasses.contains(pCdmClass->GetFullQualifiedName()))
      {
         const QMap<long,long> qmBaseClasses = pCdmClass->GetBaseClasses();

         QMap<long,long>::const_iterator iItClasses = qmBaseClasses.begin();
         QMap<long,long>::const_iterator iItClassesEnd = qmBaseClasses.end();

         for(; iItClasses != iItClassesEnd; ++iItClasses)
         {
            CdmClass* pBaseClass = const_cast<CdmClassManager*> (this)->FindClassById(iItClasses.value());

            if (CHKPTR(pBaseClass))
            {
               CreateClassVariant(pBaseClass, qstrlClasses, p_rqlMap);
            }
         }

         p_rqlMap.append(pCdmClass->GetVariant());
         qstrlClasses.append(pCdmClass->GetFullQualifiedName());
      }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 12:59:03 2012----------*
 * @method  CdmClassManager::SetVariant                      // public                            *
 * @return  void                                             //                                   *
 * @param   QVariant p_qvClasses                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 12:59:03 2012----------*/
void CdmClassManager::SetVariant(QVariant p_qvClasses)
{
    SYNCHRONIZED_WRITE;
    QVariantMap qvClasses = p_qvClasses.toMap();
    QVariantList qlPackages = qvClasses[WMS_PACKAGE].toList();

    for (int iPos = 0; iPos < qlPackages.count(); ++iPos)
    {
        QVariantMap qvHash = qlPackages[iPos].toMap();
        CdmPackage* pPackage = new CdmPackage(qvHash);
        m_qlPackages.append(pPackage);
    }

    QVariantList qlClasses = qvClasses[WMS_ECLASS].toList();

    for (int iPos = 0; iPos < qlClasses.count(); ++iPos)
    {
        QVariantMap qvHash = qlClasses[iPos].toMap();
        CdmClass* pCdmClass = new CdmClass(qvHash);
        m_qmClasses.insert(pCdmClass->GetId(), pCdmClass);
    }
}

/** +-=---------------------------------------------------------Fr 30. Nov 10:17:21 2012----------*
 * @method  CdmClassManager::Deploy                          // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 10:17:21 2012----------*/
void CdmClassManager::DeployPackages(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantList qlPackages = p_rqvHash[WMS_PACKAGE].toList();
    CdmMessageManager::StartProgressBar("DeployPackages", tr("Importiere Packages"), tr("Beginne Packages-Import"), p_rqvHash.count());
    int iSteps = 0;

    for (int iPos = 0; iPos < qlPackages.count(); ++iPos)
    {
        QVariantMap qvHash = qlPackages[iPos].toMap();
        CdmPackage* pPackage = FindPackageByName(qvHash[WMS_KEYNAME].toString());

        if (pPackage)
        {
            pPackage->Deploy(qvHash);
        }
        else
        {
            pPackage = new CdmPackage(qvHash);
            pPackage->SetNew();
            SYNCHRONIZED;
            m_qlPackages.append(pPackage);
        }

        pPackage->Commit();
        ++iSteps;
        CdmMessageManager::SetProgress("DeployPackages", tr("Importiere Package ") + QString::number(iSteps) + tr(" von ") + QString::number(p_rqvHash.count()), iSteps);
    }

    CdmMessageManager::CloseProgressBar("DeployPackages");
}

void CdmClassManager::DeployClasses(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QList<QVariant> qlClasses = p_rqvHash[WMS_ECLASS].toList();
    CdmDataProvider* pManager = GetDataProvider();

    CdmMessageManager::StartProgressBar("DeployClasses", tr("Importiere Klassen"), tr("Beginne Klassenimport"), qlClasses.count());
    int iSteps = 0;

    for (int iPos = 0; iPos < qlClasses.count(); ++iPos)
    {
        QVariantMap qvClassHash = qlClasses[iPos].toMap();
        QString qstrUri = qvClassHash[WMS_URI].toString();
        QString qstrKeyname = qvClassHash[WMS_KEYNAME].toString();
        QString qstrPackageUri = qvClassHash[WMS_PACKAGE].toString();
        CdmClass* pClass = static_cast<CdmClass*>(GetDataProvider()->GetUriObject(qstrUri));
        CdmPackage* pPackage = nullptr;

        if (CHKPTR(pManager) && !qstrPackageUri.isEmpty())
        {
            CdmLocatedElement* pElement = pManager->GetUriObject(qstrPackageUri);

            if (CHKPTR(pElement) && pElement->IsPackage())
            {
                pPackage = dynamic_cast<CdmPackage*>(pElement);
            }
        }


        if (pClass)
        {
            pClass->Deploy(qvClassHash);
        }
        else if (!qstrKeyname.isEmpty())
        {
            pClass = CreateClass(qstrKeyname, pPackage);

            if (CHKPTR(pClass))
            {
                pClass->Deploy(qvClassHash);
            }
        }

        if (pClass)
        {
            pClass->Commit();
        }
        else
        {
            ERR("Class with Uri " + qstrUri + " not found and not created!");
        }

        ++iSteps;
        CdmMessageManager::SetProgress("DeployClasses", tr("Importiere Klasse ") + QString::number(iSteps) + tr(" von ") + QString::number(qlClasses.count()), iSteps);
    }

    CdmMessageManager::CloseProgressBar("DeployClasses");
}

void CdmClassManager::Deploy(QVariantMap& p_rqvHash)
{
    DeployPackages(p_rqvHash);
    DeployClasses(p_rqvHash);
}

CdmPackage *CdmClassManager::CreatePackage(QString p_qstrName)
{
    return CreatePackage(p_qstrName, nullptr);
}

CdmPackage *CdmClassManager::CreatePackage(QString p_qstrName, CdmPackage *p_pParent)
{
    QString qstrFullQualifiedName;
    SYNCHRONIZED_WRITE;

    if (p_pParent)
    {
        qstrFullQualifiedName = p_pParent->GetPackageString() + "." + p_qstrName;
    }
    else
    {
        qstrFullQualifiedName = p_qstrName;
    }

    CdmPackage* pPackage = FindPackageByName(qstrFullQualifiedName);

    if (pPackage == nullptr || (pPackage->GetParent() == p_pParent && p_pParent != nullptr))
    {
        pPackage = new CdmPackage(GetSchemeId(), p_qstrName);

        if (pPackage)
        {
            pPackage->SetNew();
            pPackage->SetModified();

            if (p_pParent)
            {
                p_pParent->AddChild(pPackage);
                pPackage->SetParent(p_pParent);
            }
            else
            {
                m_qlPackages.append(pPackage);
            }

            if (!SUCCESSFULL(pPackage->Commit()))
            {
                if (p_pParent)
                {
                    p_pParent->DeleteChild(pPackage);
                }
                else
                {
                    m_qlPackages.removeAll(pPackage);
                }

                DELPTR(pPackage);
            }
        }
    }
    else
    {
        pPackage = nullptr;
        ERR(tr("Package with this name already exists"));
    }

    return pPackage;
}

void CdmClassManager::AddPackage(CdmPackage *p_pPackage)
{
    SYNCHRONIZED_WRITE;
    m_qlPackages.append(p_pPackage);
}

CdmPackage *CdmClassManager::FindPackageByName(QString p_qstrPackage)
{
    SYNCHRONIZED_READ;
    CdmPackage* pPackage = nullptr;

    QString qstrPackageKeynameFirstArea;
    int iIndex = p_qstrPackage.indexOf(".");

    if (iIndex > 0)
    {
        qstrPackageKeynameFirstArea = p_qstrPackage.left(iIndex);
    }
    else
    {
        qstrPackageKeynameFirstArea = p_qstrPackage;
    }

    for (int iPos = 0; iPos < m_qlPackages.count(); ++iPos)
    {
        CdmPackage* pPackageTemp = m_qlPackages[iPos];

        if (CHKPTR(pPackageTemp))
        {
            if (pPackageTemp->GetKeyname() == qstrPackageKeynameFirstArea)
            {
                if (iIndex > 0)
                {
                    pPackage = pPackageTemp->FindChild(p_qstrPackage.mid(iIndex + 1));
                }
                else
                {
                    pPackage = pPackageTemp;
                }
                break;
            }

        }
    }

    return pPackage;
}

CdmPackage *CdmClassManager::FindPackageByUri(QString p_qstrPackage)
{
    CdmPackage* pPackage = nullptr;
    SYNCHRONIZED_READ;

    for (int iPos = 0; iPos < m_qlPackages.count(); ++iPos)
    {
        CdmPackage* pPackageTemp = m_qlPackages[iPos];

        if (CHKPTR(pPackageTemp))
        {
            if (pPackageTemp->GetUriInternal() == p_qstrPackage)
            {
                pPackage = pPackageTemp;
                break;
            }
            else
            {
                pPackage = pPackageTemp->FindChildByUri(p_qstrPackage);
                if (pPackage)
                {
                    break;
                }
            }
        }
    }


    return pPackage;
}

CdmPackage *CdmClassManager::FindPackageByClassUri(QString p_qstrUri)
{
    SYNCHRONIZED_READ;
    CdmPackage* pPackage = nullptr;
    p_qstrUri = p_qstrUri.replace(WMS_URI_CLASS,WMS_URI_PACKAGE);
    int iPos = p_qstrUri.lastIndexOf(".");

    if (iPos >= 0)
    {
        p_qstrUri = p_qstrUri.left(iPos);

        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (!p_qstrUri.isEmpty() && CHKPTR(pManager))
        {
            CdmModelElement* pElement = (CdmModelElement*)pManager->GetUriObject(p_qstrUri);

            if (pElement && pElement->IsPackage())
            {
                pPackage = static_cast<CdmPackage*>(pElement);
            }
        }
    }

    return pPackage;
}


void CdmClassManager::DeletePackage(CdmPackage *p_pPackage)
{
    if (CHKPTR(p_pPackage))
    {
        SYNCHRONIZED_WRITE;
        CdmPackage::RemovePackageFromClasses(p_pPackage);
        CdmPackage* pParent = const_cast<CdmPackage*>(p_pPackage->GetParent());

        if (pParent)
        {
            pParent->DeleteChild(p_pPackage);
            pParent->Commit();
        }
        else
        {
            m_qlPackages.removeAll(p_pPackage);
            p_pPackage->SetDeleted();
        }

        p_pPackage->Commit();
    }
}

void CdmClassManager::MoveClassToPackage(CdmClass *p_pClass, CdmPackage *p_pPackage)
{
    SYNCHRONIZED_WRITE;

    if (CHKPTR(p_pClass))
    {
        // Remove it from Original Package
        CdmPackage* pOriginal = p_pClass->GetPackage();

        if (pOriginal)
        {
            pOriginal->RemoveClass(p_pClass);
        }

        if (p_pPackage)
        {
            p_pPackage->AddClass(p_pClass);
        }
        else
        {
            p_pClass->SetPackage(nullptr);
        }
    }
}

void CdmClassManager::UpdateModifiedClasses()
{
    SYNCHRONIZED_WRITE;
    QMap<long,CdmClass*>::const_iterator qmIt =  m_qmClasses.begin();
    QMap<long,CdmClass*>::const_iterator qmItEnd =  m_qmClasses.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClass* pCdmClass = qmIt.value();

        if (CHKPTR(pCdmClass))
        {
            if (pCdmClass->IsModified() || pCdmClass->IsDeleted())
            {
                pCdmClass->Commit();
            }
        }
    }
}

QList<CdmPackage*> CdmClassManager::GetPackageList()
{
    SYNCHRONIZED_READ;
    return m_qlPackages;
}

bool CdmClassManager::ExistPackage(QString p_qstrPackage)
{
    SYNCHRONIZED_READ;
    bool bRet = false;
    CdmPackage* pPackage = nullptr;
    QString qstrPackageKeynameFirstArea;
    int iIndex = p_qstrPackage.indexOf(".");

    if (iIndex > 0)
    {
        qstrPackageKeynameFirstArea = p_qstrPackage.left(iIndex);
    }
    else
    {
        qstrPackageKeynameFirstArea = p_qstrPackage;
    }

    for (int iPos = 0; iPos < m_qlPackages.count(); ++iPos)
    {
        CdmPackage* pPackageTemp = m_qlPackages[iPos];

        if (CHKPTR(pPackageTemp))
        {
            if (pPackageTemp->GetKeyname() == qstrPackageKeynameFirstArea)
            {
                if (iIndex > 0)
                {
                    pPackage = pPackageTemp->FindChild(p_qstrPackage.mid(iIndex + 1));
                }
                else
                {
                    pPackage = pPackageTemp;
                }
                break;
            }

        }
    }

    if (pPackage)
    {
        bRet = true;
    }

    return bRet;
}

QString CdmClassManager::GetUri() const
{
    return CreateUri(WMS_URI_CLASS_MANAGER, "");
}

QString CdmClassManager::GetUriInternal() const
{
    return CreateUriPath(WMS_URI_CLASS_MANAGER, "", "", "");
}

bool CdmClassManager::IsClassManager() const
{
    return true;
}
