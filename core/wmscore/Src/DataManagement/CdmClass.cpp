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
#include <QString>
#include <QDateTime>
#include <qdom.h>
#include <QVariant>

// WMS Commons Includes
#include "CwmsJson.h"

// own Includes
#include "CdmScheme.h"
#include "wmsdefines.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmPackage.h"
#include "CdmClassMethod.h"
#include "CdmClassValidator.h"
#include "CdmClass.h"

// const int iMaxMembers = 1024;


/** +-=---------------------------------------------------------Sa 13. Aug 21:07:15 2005----------*
 * @method  CdmClass::CdmClass                               // protected                         *
 * @return                                                   //                                   *
 * @param  qint64 p_lDatabaseId                               // Database Id                       *
 * @param  qint64 p_lId                                       // Class Id                          *
 * @param   QString p_qstrKeyname                            // Class keyname                     *
 * @comment The cosntructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:07:15 2005----------*/
CdmClass::CdmClass( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname )
    : CdmModelElement(p_lDatabaseId, p_lId, p_qstrKeyname),
      m_bIsInUse(false),
      m_lBaseClassCounter(0),
      m_bAbstract(false),
      m_lCaptionMember(0),
      m_iVersion(0),
      m_rPackage(nullptr),
      m_pEventClass(nullptr)
{
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:07:52 2005----------*
 * @method  CdmClass::CdmClass                               // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Eelement                      *
 * @comment The cosntructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:07:52 2005----------*/
CdmClass::CdmClass(  QDomElement& p_rqDomElement )
    : CdmModelElement(p_rqDomElement),
      m_bIsInUse(false),
      m_lBaseClassCounter(0),
      m_bAbstract(false),
      m_lCaptionMember(0),
      m_iVersion(0),
      m_rPackage(nullptr),
      m_pEventClass(nullptr)
{
    if(!p_rqDomElement.isNull())
    {
        XmlImportClass(p_rqDomElement);
    }
}

/** +-=---------------------------------------------------------Mo 30. Apr 13:09:34 2012----------*
 * @method  CdmClass::CdmClass                               // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_qvClass                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 30. Apr 13:09:34 2012----------*/
CdmClass::CdmClass(QVariantMap& p_qvClass)
    : CdmModelElement(p_qvClass),
      m_bIsInUse(false),
      m_lBaseClassCounter(0),
      m_bAbstract(false),
      m_lCaptionMember(0),
      m_iVersion(0),
      m_rPackage(nullptr),
      m_pEventClass(nullptr)
{
    SetVariant(p_qvClass);
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:43:10 2005----------*
 * @method  CdmClass::~CdmClass                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmClass                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:43:10 2005----------*/
CdmClass::~CdmClass(  )
{
    ClearMembers();
    ClearGroups();
    ClearMethods();
    ClearValidators();
}


void CdmClass::SetPackage(CdmPackage* p_pPackage)
{
    SYNCHRONIZED_WRITE;
    if (m_rPackage != p_pPackage)
    {
        m_rPackage = p_pPackage;
        if (p_pPackage)
        {
            p_pPackage->AddClass(this);
        }

        SetModified();
    }
}

void CdmClass::SetPackage(QString p_qstrUri)
{

    if (!p_qstrUri.isEmpty())
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            CdmLocatedElement* pElement = pManager->GetUriObject(p_qstrUri);

            if (CHKPTR(pElement) && pElement->IsPackage())
            {
                SYNCHRONIZED_WRITE;
                SetPackage(static_cast<CdmPackage*>(pElement));
                SetModified();
            }
        }
    }
}

CdmPackage* CdmClass::GetPackage()
{
    SYNCHRONIZED_READ;
    return m_rPackage;
}

QString CdmClass::GetFullQualifiedName() const
{
    SYNCHRONIZED_READ;
    QString qstrFullQualifiedName;

    if (m_rPackage)
    {
        qstrFullQualifiedName = m_rPackage->GetPackageString() + "." + GetKeyname();
    }
    else
    {
        qstrFullQualifiedName = GetKeyname();
    }

    return qstrFullQualifiedName;
}

/** +-=---------------------------------------------------------Mi 9. Mai 09:44:58 2012-----------*
 * @method  CdmClass::ClearMembers                           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Mai 09:44:58 2012-----------*/
void CdmClass::ClearMembers()
{
    SYNCHRONIZED_WRITE;
    QMap<qint64, CdmMember*>::iterator iIt = m_qmMembers.begin();
    QMap<qint64, CdmMember*>::iterator iItEnd = m_qmMembers.end();

    for (; iIt != iItEnd; ++iIt)
    {
        CdmMember* pCdmMember = iIt.value();
        DELPTR(pCdmMember)
    }

    m_qmMembers.clear();
}


void CdmClass::ClearGroups()
{
    SYNCHRONIZED_WRITE;
    QMap<int, CdmClassGroup*>::iterator iIt = m_qmGroups.begin();
    QMap<int, CdmClassGroup*>::iterator iItEnd = m_qmGroups.end();

    for (; iIt != iItEnd; ++iIt)
    {
        CdmClassGroup* pGroup = iIt.value();
        DELPTR(pGroup)
    }

    m_qmGroups.clear();
}

void CdmClass::ClearMethods()
{
    SYNCHRONIZED_WRITE;
    QMap<QString, CdmClassMethod*>::iterator iIt = m_qmMethods.begin();
    QMap<QString, CdmClassMethod*>::iterator iItEnd = m_qmMethods.end();

    for (; iIt != iItEnd; ++iIt)
    {
        CdmClassMethod* pMethod = iIt.value();
        DELPTR(pMethod)
    }

    m_qmMethods.clear();
}

void CdmClass::ClearValidators()
{
    SYNCHRONIZED_WRITE;
    QMap<QString, CdmClassValidator*>::iterator iIt = m_qmValidators.begin();
    QMap<QString, CdmClassValidator*>::iterator iItEnd = m_qmValidators.end();

    for (; iIt != iItEnd; ++iIt)
    {
        CdmClassValidator* pValidator = iIt.value();
        DELPTR(pValidator)
    }

    m_qmValidators.clear();
}

/** +-=---------------------------------------------------------Mo 30. Apr 13:09:01 2012----------*
 * @method  CdmClass::SetVariant                             // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvVariant                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 30. Apr 13:09:01 2012----------*/
void CdmClass::SetVariant(QVariantMap& p_rqvVariant)
{
    SYNCHRONIZED_WRITE;
    CdmModelElement::SetVariant(p_rqvVariant);

    m_bAbstract  = p_rqvVariant[WMS_ABSTRACT].toBool();
    m_bIsInUse  = p_rqvVariant[WMS_INUSE].toBool();
    SetImmutable(p_rqvVariant[WMS_IMMUTABLE].toBool());
    SetSingleton(p_rqvVariant[WMS_SINGLETON].toBool());
    m_lBaseClassCounter  = p_rqvVariant[WMS_BASECLASSCOUNTER].toInt();
    m_iVersion = p_rqvVariant[WMS_VERSION].toInt();
    QString qstrPackage = p_rqvVariant[WMS_PACKAGE].toString();
    m_rPackage = dynamic_cast<CdmPackage*>(GetDataProvider()->GetUriObject(qstrPackage));

    QVariantList qvMembers = p_rqvVariant[WMS_STRUCTURALFEATURE].toList();
    QVariantMap qvBaseClasses = p_rqvVariant[WMS_BASECLASSES].toMap();
    QVariantList qvMemberSequences = p_rqvVariant[WMS_MEMBERSEQUENCE].toList();
    QVariantMap qvGroups = p_rqvVariant[WMS_GROUPS].toMap();
    QVariantMap qvMethods = p_rqvVariant[WMS_METHODS].toMap();
    QVariantMap qvValidations = p_rqvVariant[WMS_VALIDATIONS].toMap();
    QVariantMap qvAnnotation = p_rqvVariant[WMS_ANNOTATION].toMap();

    m_qstrComment = qvAnnotation[WMS_COMMENT].toString();
    ParseGroups(qvGroups); // Groups before members!!!
    ParseMembers(qvMembers);
    ParseBaseClasses(qvBaseClasses);
    ParseMemberSequences(qvMemberSequences);
    ParseMethods(qvMethods);
    ParseValidations(qvValidations);

    CdmMember* pMember = const_cast<CdmMember*>(FindMember(p_rqvVariant[WMS_CAPTIONMEMBER].toString()));

    if (pMember)
    {
        m_lCaptionMember = pMember->GetId();
    }
}

void CdmClass::AddBaseClassData(CdmClass* p_pCdmClass)
{
    QVector<QString> qvSequence = p_pCdmClass->GetMemberSequence();

    for (int pos = 0; pos < qvSequence.count(); ++pos)
    {
        if (!m_qlMemberSequence.contains(qvSequence[pos]))
        {
            m_qlMemberSequence.append(qvSequence[pos]);
        }
    }

    SetModified();
    m_qlModifedBaseClasses.append(p_pCdmClass->GetId());
}

int CdmClass::AddBaseClass(CdmClass* p_pCdmClass)
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmBaseClassAdditionError;

    if (p_pCdmClass)
    {
        if (m_bIsInUse && p_pCdmClass->HasMustMembers())
        {
            ERR("Could not add new base class with must Values,\n"
                "if there already exists objects of this class")
            iRet = EC(eDmClassUsageError);
        }
        else
        {
            if (!p_pCdmClass->IsTypeOf(GetId())) // check for circle dependency
            {
                m_lBaseClassCounter++;
                m_qmBaseClasses.insert(m_lBaseClassCounter, p_pCdmClass->GetId());

                AddBaseClassData(p_pCdmClass);
                iRet = EC(eDmTrue);
            }
            else
            {
                iRet = CdmLogging::eDmCircelDependencyInInhertiance;
                ERR("Circle dependecy check failed. Baseclass not added.")
            }
        }
    }

    return iRet;
}

bool CdmClass::HasBaseClassChanges()
{
    return (m_qlModifedBaseClasses.count() > 0);
}

QList<qint64> CdmClass::GetBaseClassChanges()
{
    return m_qlModifedBaseClasses;
}

/** +-=---------------------------------------------------------Mi 11. Jun 16:42:43 2008----------*
 * @method  CdmClass::AddBaseClass                           // public                            *
 * @return  int                                              //                                   *
 * @param   QString p_qstrBaseClass                          //                                   *
 * @comment This method adds a base class to this class.                                          *
 *----------------last changed: --------------------------------Mi 11. Jun 16:42:43 2008----------*/
int CdmClass::AddBaseClass(QString p_qstrBaseClass)
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmBaseClassAdditionError;

    CdmClassManager* pCdmClassManager = GetClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(p_qstrBaseClass);

        if (CHKPTR(pCdmClass))
        {
            iRet = AddBaseClass(pCdmClass);
        }
        else
        {
            ERR("Baseclass with name " + p_qstrBaseClass + " not found!")
        }

    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:08:09 2005----------*
 * @method  CdmClass::CreateMember                           // public                            *
 * @return  CdmMember*                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @param   bool p_bMust                                     //                                   *
 * @param  qint64 p_lSize                                     //                                   *
 * @comment This method is the only way to generates objects of type Valuedescritpion. this is a monopol of CdmClass.*
 *----------------last changed: --------------------------------Sa 13. Aug 21:08:09 2005----------*/
CdmMember* CdmClass::CreateMember(QString p_qstrKeyname,
                                  EdmValueType p_eDmValue,
                                  bool p_bMust,
                                 qint64 p_lSize)
{
    SYNCHRONIZED_WRITE;
    CdmMember* pCdmMember = nullptr;

    if (CheckMemberKeyname(p_qstrKeyname))
    {
       qint64 lId = GetNewMemberId();

        if (lId > 0)
        {
            pCdmMember = new CdmMember(GetSchemeId(),
                                       lId,
                                       p_qstrKeyname,
                                       p_eDmValue,
                                       p_bMust,
                                       p_lSize);

            pCdmMember->SetClassId(GetId());

            if (AddMember(pCdmMember) > 0) // no Error found!!!
            {
                pCdmMember->SetNew();
                pCdmMember->SetModified();
            }
            else
            {
                DELPTR(pCdmMember)
                ERR("Member could not be added and was deleted now!!!")
            }
        }
        else
        {
            ERR("Invalid Member Id")
            EC(eDmInvalidId);
        }
    }
    else
    {
        // Errorhandling Value with the same keyname is already there
        ERR("Could not add new Value, because there is already a memebr with the same name.\n")
        EC(eDmKeynameAlreadyExists);
    }

    return pCdmMember;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:08:19 2005----------*
 * @method  CdmClass::GetNewMemberId                         // public                            *
 * @return qint64                                             //                                   *
 * @comment This method returns a new Value Description Id or -1 if not possible.                 *
 *----------------last changed: --------------------------------Sa 13. Aug 21:08:19 2005----------*/
qint64 CdmClass::GetNewMemberId(  )
{
    SYNCHRONIZED_READ;
   qint64 lRet = 0;

    while (true)
    {
        lRet++;

        if (!m_qmMembers.contains(lRet))
        {
            break;
        }
    }

    return lRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:08:23 2005----------*
 * @method  CdmClass::AddMember                              // private                           *
 * @return  int                                              //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment Adds a Value Description to this class.                                               *
 *----------------last changed: --------------------------------Sa 13. Aug 21:08:23 2005----------*/
int CdmClass::AddMember(CdmMember* p_pCdmMember)
{
    int iRet = CdmLogging::eDmUnknownMemberError;

    if (CHKPTR(p_pCdmMember))
    {
        if (p_pCdmMember->IsMust() && m_bIsInUse)
        {
            // not possible to add a must field if there are Values
            // which are using this class
            ERR("Could not add new Value with must value, if there\n"
                "exist objects of this class." )
            iRet = EC(eDmNoNewMustValuePossible);
        }
        else
        {
            if (!FindMember(p_pCdmMember->GetKeyname()))
            {
                SYNCHRONIZED_WRITE;
                INFO ("Member not found will be added!")
                        m_qmMembers.insert(p_pCdmMember->GetId(), p_pCdmMember);
                UpdateSequenceOfDerivedClasses(p_pCdmMember->GetKeyname());

                SetModified();
                iRet = EC(eDmTrue);

            }
            else
            {
                INFO("Member with this name already exists!!! Keyname: " + p_pCdmMember->GetKeyname() + " Class: " + GetKeyname())
                iRet = EC(eDmKeynameAlreadyExists);
            }
        }
    }

    return iRet;
}

void CdmClass::UpdateSequenceOfDerivedClasses(QString p_qstrKeyname)
{
    SYNCHRONIZED_WRITE;
    QList<CdmClass*> qlClasses;

    CdmClassManager* pManager = GetClassManager();

    if (CHKPTR(pManager))
    {
        pManager->GetInheritedClasses(this, qlClasses);
        QList<CdmClass*>::iterator qllIt = qlClasses.begin();
        QList<CdmClass*>::iterator qllItEnd = qlClasses.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            CdmClass* pClass = *qllIt;

            if (CHKPTR(pClass))
            {
                if (!pClass->m_qlMemberSequence.contains(p_qstrKeyname))
                {
                    pClass->m_qlMemberSequence.append(p_qstrKeyname);
                }
            }
        }
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:01:40 2013-----------*
 * @method  CdmClass::CheckMemberKeyname                     // private, const                    *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method checks if this Value description is already in this class. if not         *
 *          true will returned else false.                                                        *
 *----------------last changed: --------------------------------Sa 9. Feb 12:01:40 2013-----------*/
bool CdmClass::CheckMemberKeyname(QString p_qstrKeyname) const
{
    SYNCHRONIZED_READ;
    bool bRet = true;

    if (!p_qstrKeyname.isEmpty())
    {
        QMap<qint64, CdmMember*>::const_iterator iIt = m_qmMembers.begin();
        QMap<qint64, CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

        for (; iIt != iItEnd; ++iIt)
        {
            CdmMember* pCdmMember = iIt.value();

            if (CHKPTR(pCdmMember))
            {
                if (p_qstrKeyname == pCdmMember->GetKeyname())
                {
                    bRet = false;
                    ERR("Member with this keyname already exists!")
                    break;
                }
            }
        }
    }
    else
    {
        ERR("Member Keyname is Empty!")
        bRet = false;
    }

    return bRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:02:09 2013-----------*
 * @method  CdmClass::HasMustMembers                         // private, const                    *
 * @return  bool                                             //                                   *
 * @comment This method checks if this class has must Values. If yes true will be returned        *
 *          else False.                                                                           *
 *----------------last changed: --------------------------------Sa 9. Feb 12:02:09 2013-----------*/
bool CdmClass::HasMustMembers() const
{
    SYNCHRONIZED_READ;
    bool bRet = false;

    QMap<qint64, CdmMember*>::const_iterator iIt = m_qmMembers.begin();
    QMap<qint64, CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

    for (; iIt != iItEnd; ++iIt)
    {
        CdmMember* pCdmMember = iIt.value();

        if (CHKPTR(pCdmMember))
        {
            if (pCdmMember->IsMust())
            {
                bRet = true;
                break;
            }
        }
    }

    return bRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:02:39 2013-----------*
 * @method  CdmClass::HasNonSystemMembers                    // public, const                     *
 * @return  bool                                             //                                   *
 * @comment This method checks if this class contains member whcih were added by the suer.        *
 *----------------last changed: --------------------------------Sa 9. Feb 12:02:39 2013-----------*/
bool CdmClass::HasNonSystemMembers() const
{
    SYNCHRONIZED_READ;
    bool bRet = false;

    QMap<qint64,CdmMember*> qmMap;
    GetMemberMap(qmMap);

    QMap<qint64,CdmMember*>::iterator iIt = qmMap.begin();
    QMap<qint64,CdmMember*>::iterator iItEnd = qmMap.end();

    for(; iIt != iItEnd; ++iIt)
    {
        CdmMember* pCdmMember = iIt.value();
        if(CHKPTR(pCdmMember))
        {
            if(!pCdmMember->IsSystemMember())
            {
                bRet = true;
                break;
            }
        }
    }

    return bRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:08:34 2005----------*
 * @method  CdmClass::SetClassInUse                          // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bInUse                                    //                                   *
 * @comment This method will be called if the class is in use. This means there are objects in    *
 *          object lists which will refer to thiis class.                                         *
 *----------------last changed: --------------------------------Sa 13. Aug 21:08:34 2005----------*/
void CdmClass::SetClassInUse(  bool p_bInUse )
{
    SYNCHRONIZED_WRITE;
    m_bIsInUse = p_bInUse;

    if(m_bIsInUse)
    {
        CdmDataProvider* pCdmManager = GetDataProvider();

        if(CHKPTR(pCdmManager))
        {
            CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

            if(CHKPTR(pCdmClassManager))
            {
                CdmClass* pCdmClass = nullptr;

                QMap<qint64,qint64>::iterator iItClasses = m_qmBaseClasses.begin();
                QMap<qint64,qint64>::iterator iItClassesEnd = m_qmBaseClasses.end();

                for(; iItClasses != iItClassesEnd; ++iItClasses)
                {
                    pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                    if(pCdmClass)
                    {
                        pCdmClass->SetClassInUse(true);
                    }
                }
            }
            else
            {
                EC(eDmInvalidClassPtr);
            }
        }
        else
        {
            EC(eDmInvalidPtr);
        }
    }
}

/** +-=---------------------------------------------------------So 10. Feb 18:06:35 2013----------*
 * @method  CdmClass::FindMember                             // public, const, slots              *
 * @return  const CdmMember*                                 // if not found nullptr will be returned*
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method searches this and all baseclasses for this Value and returns it. If       *
 *          this Member was not found nullptr will returned.                                         *
 *----------------last changed: --------------------------------So 10. Feb 18:06:35 2013----------*/
const CdmMember* CdmClass::FindMember(QString p_qstrKeyname) const
{
    SYNCHRONIZED_READ;
    const CdmMember* pCdmMember = nullptr;
    pCdmMember = FindMember(p_qstrKeyname, 0);
    return pCdmMember;
}

/** +-=---------------------------------------------------------So 10. Feb 18:06:20 2013----------*
 * @method  CdmClass::FindMember                             // public, const, slots              *
 * @return  const CdmMember*                                 // if not found nullptr will be returned*
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   int p_iRecursionLevel                            //                                   *
 * @comment This method searches this and all baseclasses for this Value and returns it. If       *
 *          this Member was not found nullptr will returned.                                         *
 *----------------last changed: --------------------------------So 10. Feb 18:06:20 2013----------*/
const CdmMember* CdmClass::FindMember(QString p_qstrKeyname, int p_iRecursionLevel) const
{
    const CdmMember* pCdmMember = nullptr;

    if (!p_qstrKeyname.contains("."))
    {
        pCdmMember = (const_cast<CdmClass*>(this))->FindClassMember(p_qstrKeyname);
    }
    else
    {
        pCdmMember = (const_cast<CdmClass*>(this))->FindReferencedMember(p_qstrKeyname, p_iRecursionLevel);
    }


    if (!pCdmMember)
    {
        INFO("Value " + p_qstrKeyname + " in this class and all base classes not found.")
    }

    return pCdmMember;
}

CdmMember* CdmClass::FindEventClassMember(QString p_qstrKeyname)
{
    CdmMember* pCdmMember = nullptr;

    if (!p_qstrKeyname.contains("."))
    {
        pCdmMember = FindClassMember(p_qstrKeyname);
    }
    else
    {
        pCdmMember = FindReferencedMember(p_qstrKeyname, 0);
    }

    if (!pCdmMember)
    {
        INFO("Value" + p_qstrKeyname + " in this class and all base classes not found.")
    }

    return pCdmMember;
}

/** +-=---------------------------------------------------------Sa 25. Jul 14:19:38 2009----------*
 * @method  CdmClass::FindClassMember                        // private                           *
 * @return  CdmMember*                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment Finds the searched  direct in this class. The search member has no references in      *
 *----------------last changed: --------------------------------Sa 25. Jul 14:19:38 2009----------*/
CdmMember* CdmClass::FindClassMember(QString p_qstrKeyname)
{
    SYNCHRONIZED_READ;
    CdmMember* pCdmMember = nullptr;
    QMap<qint64,CdmMember*>::iterator iIt = m_qmMembers.begin();
    QMap<qint64,CdmMember*>::iterator iItEnd = m_qmMembers.end();

    for(; iIt != iItEnd; ++iIt)
    {
        CdmMember* pCdmMemberTemp = iIt.value();

        if(CHKPTR(pCdmMemberTemp) &&
                pCdmMemberTemp->GetKeyname() == p_qstrKeyname)
        {
            pCdmMember = pCdmMemberTemp;
            break;
        }
    }

    if(!pCdmMember)
    {
        CdmDataProvider* pCdmManager = GetDataProvider();
        if(CHKPTR(pCdmManager))
        {
            CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

            if(pCdmClassManager)
            {
                CdmClass* pCdmClass = nullptr;

                QMap<qint64,qint64>::iterator iItClasses = m_qmBaseClasses.begin();
                QMap<qint64,qint64>::iterator iItClassesEnd = m_qmBaseClasses.end();

                for (; iItClasses != iItClassesEnd; ++iItClasses)
                {
                    pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                    if(pCdmClass && pCdmClass != this)
                    {
                        pCdmMember = const_cast<CdmMember*>(pCdmClass->FindMember(p_qstrKeyname));

                        if(pCdmMember)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                EC(eDmInvalidClassPtr);
            }
        }
        else
        {
            EC(eDmInvalidPtr);
        }
    }

    return pCdmMember;
}

/** +-=---------------------------------------------------------Sa 25. Jul 14:23:10 2009----------*
 * @method  CdmClass::FindReferencedMember                   // private                           *
 * @return  CdmMember*                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   int p_iRecusrionLevel = 0                        //                                   *
 * @comment Finds the searched  direct in this class. The search member has no references in      *
 *----------------last changed: --------------------------------Sa 25. Jul 14:23:10 2009----------*/
CdmMember* CdmClass::FindReferencedMember(QString p_qstrKeyname, int p_iRecusrionLevel)
{
    CdmMember* pCdmMember = nullptr;
    int iPointPos = p_qstrKeyname.indexOf('.');

    if (iPointPos > 0)
    {
        QString qstrKeyname = p_qstrKeyname.mid(0, iPointPos);
        pCdmMember = const_cast<CdmMember*>(FindMember(qstrKeyname));

        if(pCdmMember && pCdmMember->GetValueType() == eDmValueObjectRef)
        {
           qint64 lClassId = pCdmMember->GetClassReference();

            if (lClassId > 0)
            {
                CdmDataProvider* pCdmManager = GetDataProvider();
                if(CHKPTR(pCdmManager))
                {
                    CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

                    if(CHKPTR(pCdmClassManager))
                    {
                        CdmClass* pCdmClass = nullptr;
                        pCdmClass = pCdmClassManager->FindClassById(lClassId);

                        if (pCdmClass)
                        {
                            qstrKeyname = p_qstrKeyname.mid(iPointPos + 1, p_qstrKeyname.length() - iPointPos -1);
                            pCdmMember = const_cast<CdmMember*>(pCdmClass->FindMember(qstrKeyname, ++p_iRecusrionLevel));
                        }
                        else
                        {
                            pCdmMember = nullptr;
                        }

                    }
                    else
                    {
                        pCdmMember = nullptr;
                    }
                }
                else
                {
                    pCdmMember = nullptr;
                }
            }
            else
            {
                pCdmMember = nullptr;
            }
        }
        else
        {
            pCdmMember = nullptr;
        }
    }

    return pCdmMember;
}



/** +-=---------------------------------------------------------Mo 11. Feb 11:05:37 2013----------*
 * @method  CdmClass::GetVisibleUserDefinedMembers           // public, const                     *
 * @return  QList<QString>                             // the list of keynames.             *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:05:37 2013----------*/
QList<QString> CdmClass::GetVisibleUserDefinedMembers() const
{
    SYNCHRONIZED_READ;
    QList<QString> qllUserDefinedMembers;
    QMap<qint64,CdmMember*> qmMembers;
    GetMemberMap(qmMembers);

    QMap<qint64,CdmMember*>::iterator qmIt = qmMembers.begin();
    QMap<qint64,CdmMember*>::iterator qmItEnd = qmMembers.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmMember* pCdmMember = qmIt.value();

        if (CHKPTR(pCdmMember) &&
                !pCdmMember->IsSystemMember() &&
                (pCdmMember->GetAccessMode() == eDmMemberAccessPublic ||
                 pCdmMember->GetAccessMode() == eDmMemberAccessProtected))
        {
            qllUserDefinedMembers.append(pCdmMember->GetKeyname());
        }
    }

    return qllUserDefinedMembers;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:04:01 2013-----------*
 * @method  CdmClass::GetMemberMap                           // public, const                     *
 * @return  int                                              // quantity of Values.               *
 * @param   QMap<qint64,CdmMember*>& p_rqlMembers              //                                   *
 * @comment This method returns all Values of this and all base classes.                          *
 *----------------last changed: --------------------------------Sa 9. Feb 12:04:01 2013-----------*/
int CdmClass::GetMemberMap(QMap<qint64, CdmMember*>& p_rqlMembers) const
{
    SYNCHRONIZED_READ;
    int iRet = CdmLogging::eDmUnknownMemberError;
    QMap<qint64,CdmMember*>::const_iterator iIt    = m_qmMembers.begin();
    QMap<qint64,CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

    for ( ; iIt != iItEnd; ++iIt)
    {
        CdmMember* pCdmMember = iIt.value();

        if (CHKPTR(pCdmMember))
        {
            p_rqlMembers.insert(pCdmMember->GetId(), pCdmMember);
        }
    }

    CdmDataProvider* pCdmManager = GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

        if (pCdmClassManager)
        {
            QMap<qint64,qint64>::const_iterator iItClasses    = m_qmBaseClasses.begin();
            QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

            for ( ; iItClasses != iItClassesEnd; ++iItClasses)
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                if (CHKPTR(pCdmClass))
                {
                    pCdmClass->GetMemberMap(p_rqlMembers);
                }
                else
                {
                    ERR("Baseclass not found!!!")
                    iRet = EC(eDmInvalidClassPtr);
                }
            }

            if (CdmLogging::eDmUnknownMemberError == iRet)
            {
                iRet = p_rqlMembers.count();
            }
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:04:46 2013-----------*
 * @method  CdmClass::GetClassMemberMap                      // public, const                     *
 * @return  const QMap<qint64, CdmMember*>&                    //                                   *
 * @comment This method returns the membermap of this class.                                      *
 *----------------last changed: --------------------------------Sa 9. Feb 12:04:46 2013-----------*/
const QMap<qint64, CdmMember*> CdmClass::GetClassMemberMap() const
{
    return m_qmMembers;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:05:05 2013-----------*
 * @method  CdmClass::GetClassMemberMap                      // public, const                     *
 * @return  int                                              // quantity of Values.               *
 * @param   QMap<qint64,CdmMember*>& p_rqlValues               //                                   *
 * @comment This method returns only the members of this class. Base classes will be              *
 *          ignored.                                                                              *
 *----------------last changed: --------------------------------Sa 9. Feb 12:05:05 2013-----------*/
int CdmClass::GetClassMemberMap(QMap<qint64,CdmMember*>& p_rqlValues) const
{
    SYNCHRONIZED_READ;
    int iRet = CdmLogging::eDmUnknownMemberError;

    QMap<qint64,CdmMember*>::const_iterator iIt    = m_qmMembers.begin();
    QMap<qint64,CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

    for ( ; iIt != iItEnd; ++iIt )
    {
        CdmMember* pCdmMember = iIt.value();

        if(CHKPTR(pCdmMember))
        {
            p_rqlValues.insert(pCdmMember->GetId(), pCdmMember);
        }
        else
        {
            EC(eDmInvalidMemberPtr);
        }
    }

    iRet = p_rqlValues.count();
    return iRet;
}

/** +-=---------------------------------------------------------Mo 19. Mai 20:11:30 2008----------*
 * @method  CdmClass::RemoveBaseClass                        // public                            *
 * @return  int                                              //                                   *
 * @param   QString p_qstrBaseClass                          //                                   *
 * @comment Removes the overgivven baseclass from this class.                                     *
 *----------------last changed: --------------------------------Mo 19. Mai 20:11:30 2008----------*/
int CdmClass::RemoveBaseClass(QString p_qstrBaseClass)
{
    int iRet = CdmLogging::eDmBaseClassRemovalError;

    CdmClassManager* pCdmClassManager = GetClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(p_qstrBaseClass);

        if (pCdmClass)
        {
            iRet = RemoveBaseClass(pCdmClass->GetId());
        }
    }


    return iRet;
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:09:01 2005----------*
 * @method  CdmClass::RemoveBaseClass                        // public                            *
 * @return  int                                              //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @comment Removes a baseclass from this class. This is only possible, if this class is not      *
 *          in use.                                                                               *
 *----------------last changed: --------------------------------Sa 13. Aug 21:09:01 2005----------*/
int CdmClass::RemoveBaseClass(qint64 p_lClassId)
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmBaseClassRemovalError;

    if (!m_bIsInUse)
    {
        QMap<qint64,qint64>::iterator iItClasses = m_qmBaseClasses.begin();
        QMap<qint64,qint64>::iterator iItClassesEnd = m_qmBaseClasses.end();

        for ( ; iItClasses != iItClassesEnd; ++iItClasses )
        {
            if (*iItClasses == p_lClassId)
            {
                m_qmBaseClasses.erase(iItClasses);
                m_qlModifedBaseClasses.append(p_lClassId);
                iRet = EC(eDmTrue);
                SetModified();
                break;
            }
        }

        if (iRet != EC(eDmTrue))
        {
            ERR("Base Class not found could not remove it.")
            iRet = EC(eDmBaseClassNotFoundError);
        }
    }
    else
    {
        ERR("Could not remove base class, because class is in use." )
        iRet = EC(eDmClassUsageError);
    }

    return iRet;
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:09:05 2005----------*
 * @method  CdmClass::DeleteMember                           // public                            *
 * @return  int                                              //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method removes a DatatType description from class. This is only possible, if     *
 *          this class is not in use.                                                             *
 *----------------last changed: --------------------------------Sa 13. Aug 21:09:05 2005----------*/
int CdmClass::DeleteMember(  QString p_qstrKeyname )
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmUnknownMemberError;
    bool bRemoved = false;

    if (!m_bIsInUse)
    {
        QMap<qint64, CdmMember*>::iterator iIt    = m_qmMembers.begin();
        QMap<qint64, CdmMember*>::iterator iItEnd = m_qmMembers.end();

        for(; iIt != iItEnd; ++iIt)
        {
            CdmMember* pCdmMember = iIt.value();

            if (CHKPTR(pCdmMember))
            {
                QString qstrKeyname = pCdmMember->GetKeyname();

                if (qstrKeyname == p_qstrKeyname)
                {
                    pCdmMember->SetDeleted();
                    int pos = m_qlMemberSequence.indexOf(pCdmMember->GetKeyname());

                    if (pos >= 0)
                    {
                        m_qlMemberSequence.remove(pos);
                    }

                    SetModified();
                    bRemoved = true;
                    iRet = EC(eDmOk);
                    break;
                }
            }
        }

        if (!bRemoved)
        {
            ERR("Member not found no removal possible!!")
            iRet = EC(eDmMemberRemovalError);
        }
    }
    else
    {
        ERR("Could not remove Member, because class is in use.")
        iRet = EC(eDmClassUsageError);
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:05:29 2013-----------*
 * @method  CdmClass::IsInherited                            // public, const, slots              *
 * @return  int                                              //                                   *
 * @param   int p_iClassId                                   //                                   *
 * @comment This method checks if thep_pCdmClass is a base class of this class.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:05:29 2013-----------*/
int CdmClass::IsInherited(int p_iClassId) const
{
    int iRet = CdmLogging::eDmUnknownClassError;

    if (p_iClassId == GetId())
    {
        iRet = EC(eDmTrue);
    }
    else
    {
        CdmDataProvider* pCdmManager = GetDataProvider();

        if(CHKPTR(pCdmManager))
        {
            CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

            if(pCdmClassManager)
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassById(p_iClassId);

                if (CHKPTR(pCdmClass))
                {
                    iRet = IsInherited(pCdmClass);
                }
            }
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:06:00 2013-----------*
 * @method  CdmClass::IsInherited                            // public, const, slots              *
 * @return  int                                              //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment This method checks if thep_pCdmClass is a base class of this class.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:06:00 2013-----------*/
int CdmClass::IsInherited(QString p_qstrClassName) const
{
    int iRet = CdmLogging::eDmUnknownClassError;

    if (p_qstrClassName == GetKeyname())
    {
        iRet = EC(eDmTrue);
    }
    else
    {
        CdmDataProvider* pCdmManager = GetDataProvider();

        if(CHKPTR(pCdmManager))
        {
            CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

            if(pCdmClassManager)
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(p_qstrClassName);

                if (CHKPTR(pCdmClass))
                {
                    iRet = IsInherited(pCdmClass);
                }
            }
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Mo 11. Feb 09:27:59 2013----------*
 * @method  CdmClass::IsInherited                            // public, const, slots              *
 * @return  int                                              //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @comment This method checks if thep_pCdmClass is a base class of this class.                   *
 *----------------last changed: --------------------------------Mo 11. Feb 09:27:59 2013----------*/
int CdmClass::IsInherited(const CdmClass* p_pCdmClass) const
{
    SYNCHRONIZED_READ;
    int iRet = CdmLogging::eDmUnknownClassError;

    if(CHKPTR(p_pCdmClass))
    {
        if (p_pCdmClass == this)
        {
            iRet = EC(eDmTrue);
        }
        else
        {
            CdmDataProvider* pCdmManager = GetDataProvider();
            if(CHKPTR(pCdmManager))
            {
                CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

                if(pCdmClassManager)
                {
                    CdmClass* pCdmClass = nullptr;

                    QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
                    QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

                    for(; iItClasses != iItClassesEnd; ++iItClasses)
                    {

                        pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                        if(CHKPTR(pCdmClass))
                        {
                            if(pCdmClass == p_pCdmClass)
                            {
                                iRet = EC(eDmTrue);
                                break;
                            }
                            else
                            {
                                iRet = pCdmClass->IsInherited(p_pCdmClass);
                            }
                        }
                        else
                        {
                            ERR("Base class not found!!")
                            iRet = EC(eDmInvalidClassPtr);
                        }
                    }
                }
                else
                {
                    iRet = EC(eDmInvalidPtr);
                }
            }
            else
            {
                iRet = EC(eDmInvalidPtr);
            }
        }
    }
    else
    {
        EC(eDmInvalidClassPtr);
    }

    if (CdmLogging::eDmUnknownClassError == iRet)
    {
        iRet = EC(eDmFalse);
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:07:10 2013-----------*
 * @method  CdmClass::GetBaseClasses                         // public, const                     *
 * @return  const QMap<qint64,qint64>&                           //                                   *
 * @comment returns a list of base classes.                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:07:10 2013-----------*/
const QMap<qint64,qint64>& CdmClass::GetBaseClasses() const
{
    SYNCHRONIZED_READ;
    return m_qmBaseClasses;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:07:18 2013-----------*
 * @method  CdmClass::IsInUse                                // public, const                     *
 * @return  bool                                             //                                   *
 * @comment This method returns if this class is in use.                                          *
 *----------------last changed: --------------------------------Sa 9. Feb 12:07:18 2013-----------*/
bool CdmClass::IsInUse() const
{
    SYNCHRONIZED_READ;
    return m_bIsInUse;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:07:38 2013-----------*
 * @method  CdmClass::CheckObject                            // public, const                     *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment This method checks if this object is correct initialised with this class.             *
 *----------------last changed: --------------------------------Sa 9. Feb 12:07:38 2013-----------*/
int CdmClass::CheckObject(CdmObject* p_pCdmObject) const
{
    SYNCHRONIZED_READ;
    int iRet = CdmLogging::eDmUnknownClassError;

    if(CHKPTR(p_pCdmObject))
    {
        if(p_pCdmObject->GetClass() == this)
        {
            QMap<qint64,CdmMember*>::const_iterator iIt    = m_qmMembers.begin();
            QMap<qint64,CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

            for(; iIt != iItEnd; ++iIt) // Check the member of this class
            {
                CdmMember* pCdmMember = iIt.value();

                if (CHKPTR(pCdmMember))
                {
                    CdmValue* pCdmValue = nullptr;
                    pCdmValue = p_pCdmObject->GetValue(pCdmMember->GetKeyname());

                    if(!pCdmValue)
                    {
                        INFO("Value not found in Object with keyname: " + pCdmMember->GetKeyname() + ".")
                        iRet = EC(eDmFalse);
                        break;
                    }
                }
            }

            // now it is time to check the members of the baseclass
            if(CdmLogging::eDmUnknownClassError == iRet)
            {
                CdmDataProvider* pCdmManager = GetDataProvider();

                if(CHKPTR(pCdmManager))
                {
                    CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

                    if(CHKPTR(pCdmClassManager))
                    {
                        CdmClass* pCdmClass = nullptr;

                        QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
                        QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

                        for(; iItClasses != iItClassesEnd; ++iItClasses)
                        {

                            pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                            if(CHKPTR(pCdmClass))
                            {
                                iRet = pCdmClass->CheckObject(p_pCdmObject);

                                if(iRet <= 0) // Error occurred or False returned
                                {
                                    break;
                                }
                            }
                            else
                            {
                                ERR("Base class not found!!")
                                iRet = EC(eDmInvalidClassPtr);
                            }
                        }
                    }
                    else
                    {
                        iRet = EC(eDmInvalidPtr);
                    }
                }
                else
                {
                    iRet = EC(eDmInvalidPtr);
                }

                // for the case there are no baseclasses the return value
                // must be set to true
                if(CdmLogging::eDmUnknownClassError == iRet)
                {
                    iRet = EC(eDmTrue);
                }
            }
        }
        else
        {
            INFO("The class of the object is not the same as this class")
            iRet = EC(eDmObjectClassIsDifferent);
        }
    }
    else
    {
        iRet = EC(eDmInvalidObjectPtr);
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:10:54 2005----------*
 * @method  CdmClass::Commit                                 // public                            *
 * @return  int                                              //                                   *
 * @comment This method commits data for direct writing to db.                                    *
 *----------------last changed: --------------------------------Sa 13. Aug 21:10:54 2005----------*/
int CdmClass::Commit(  )
{
    SYNCHRONIZED_WRITE;
    SetModifierId(GetUserId());
    int iRet = CdmLogging::eDmUnknownClassError;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        IncreaseVersion();
        CdmClass* pCdmClass = this;

        iRet = pIdmDataAccess->UpdateClass(pCdmClass);

        if(iRet > 0)
        {
            ResetNewModified();
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:08:23 2013-----------*
 * @method  CdmClass::ResetNewModified                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method resets the new and modified value at this base object. This is            *
 *          needed                                                                                *
 *          for after updating this object.                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:08:23 2013-----------*/
void CdmClass::ResetNewModified()
{
    SYNCHRONIZED_WRITE;
    CdmModelElement::ResetNewModified();

    QMap<qint64,CdmMember*>::iterator qmIt    = m_qmMembers.begin();
    QMap<qint64,CdmMember*>::iterator qmItEnd = m_qmMembers.end();

    for ( ; qmIt != qmItEnd; ++qmIt )
    {
        CdmMember* pCdmMember = qmIt.value();

        if(CHKPTR(pCdmMember))
        {
            pCdmMember->ResetNewModified();
        }
    }

    m_qlModifedBaseClasses.clear();
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:11:07 2005----------*
 * @method  CdmClass::SetComment                             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrComment                            //                                   *
 * @comment This method sets the comment for this class.                                          *
 *----------------last changed: --------------------------------Sa 13. Aug 21:11:07 2005----------*/
void CdmClass::SetComment(  QString p_qstrComment )
{
    m_qstrComment = p_qstrComment;
}


/** +-=---------------------------------------------------------Sa 9. Feb 12:08:48 2013-----------*
 * @method  CdmClass::GetComment                             // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method returns the comment for this class.                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:08:48 2013-----------*/
QString CdmClass::GetComment() const
{
    SYNCHRONIZED_READ;
    return m_qstrComment;
}


/** +-=---------------------------------------------------------Sa 9. Feb 12:08:59 2013-----------*
 * @method  CdmClass::GenerateDocumentation                  // private, const, slots             *
 * @return  QString                                          //                                   *
 * @comment This method generates html documentation for this class.                              *
 *----------------last changed: --------------------------------Sa 9. Feb 12:08:59 2013-----------*/
QString CdmClass::GenerateDocumentation() const
{
    SYNCHRONIZED_READ;
    QString qstrDocument;

    qstrDocument = "<h2>Class " + GetKeyname() + "</h2>\n";
    qstrDocument += "<p><b>" + GetComment() + "</b></p>\n";

    CdmClassManager* pCdmClassManager = GetClassManager();

    if(m_qmBaseClasses.count() > 0)
    {
        qstrDocument += "<h3>Baseclasses:</h3>\n";
        qstrDocument += "<p>";

        QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
        QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

        if(pCdmClassManager)
        {
            for(; iItClasses != iItClassesEnd; ++iItClasses)
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassById( iItClasses.value() );
                if(CHKPTR(pCdmClass))
                {
                    qstrDocument += pCdmClass->GetKeyname() + "<br>\n";
                }
            }
        }

        qstrDocument += "</p>\n";

    }


    qstrDocument += "<h3>Members:</h3>\n";
    qstrDocument += "<p>";


    if(CHKPTR(pCdmClassManager))
    {
        qstrDocument += "<table>\n";
        qstrDocument += "<tr>";
        qstrDocument += "<td><b>Name</b></td>";
        qstrDocument += "<td><b>Type</b></td>";
        qstrDocument += "<td><b>Comment</b></td>";
        qstrDocument += "<td><b>Default</b></td>";
        qstrDocument += "<td><b>References</b></td>";
        qstrDocument += "</tr>";

        QMap<qint64,CdmMember*>::const_iterator iIt = m_qmMembers.begin();
        QMap<qint64,CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

        for ( ; iIt != iItEnd; ++iIt )
        {
            CdmMember* pCdmMember = iIt.value();
            if (pCdmMember)
            {
                qstrDocument += pCdmMember->GenerateDocument();
            }
        }
    }

    qstrDocument += "</table>\n";
    qstrDocument += "</p>\n";

    return qstrDocument;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:09:19 2013-----------*
 * @method  CdmClass::XmlExport                              // public, const                     *
 * @return  int                                              //                                   *
 * @param   QDomElement& p_rqdeClassManager                  //                                   *
 * @comment exports the database to a xml file.                                                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:09:19 2013-----------*/
int CdmClass::XmlExport(QDomElement& p_rqdeClassManager) const
{
    SYNCHRONIZED_WRITE;
    int iRet = CdmLogging::eDmUnknownClassError;

    QDomDocument qddDocument = p_rqdeClassManager.ownerDocument();

    QDomElement qdeRoot = qddDocument.createElement("Class");
    p_rqdeClassManager.appendChild(qdeRoot);

    XmlExportBase(qdeRoot);
    qdeRoot.setAttribute("InUse",   ChangeBoolToString(m_bIsInUse));
    qdeRoot.setAttribute("Comment", m_qstrComment);


    QDomElement qdeTag = qddDocument.createElement("Base Classes");
    qdeRoot.appendChild(qdeTag);

    QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
    QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

    CdmClassManager* pCdmClassManager = GetClassManager();

    if(pCdmClassManager)
    {
        for(; iItClasses != iItClassesEnd; ++iItClasses)
        {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById( iItClasses.value() );
            if(CHKPTR(pCdmClass))
            {
                qdeTag.setAttribute("BaseClass", pCdmClass->GetKeyname());
            }
        }
    }

    qdeTag = qddDocument.createElement("Class Members");
    qdeRoot.appendChild(qdeTag);

    QMap<qint64,CdmMember*>::const_iterator iIt = m_qmMembers.begin();
    QMap<qint64,CdmMember*>::const_iterator iItEnd = m_qmMembers.end();

    for ( ; iIt != iItEnd; ++iIt )
    {
        CdmMember* pCdmMember = iIt.value();
        if (pCdmMember)
        {
            pCdmMember->XmlExport(qdeTag);
        }
    }

    return iRet;
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:12:45 2005----------*
 * @method  CdmClass::XmlImportClass                         // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeElement                       //                                   *
 * @comment This method imports a dom document. This method imports no base data and should be called by the constructor or by XmlImport.*
 *----------------last changed: --------------------------------Sa 13. Aug 21:12:45 2005----------*/
void CdmClass::XmlImportClass(  QDomElement& p_rqdeElement )
{
    SYNCHRONIZED_READ;
    m_bIsInUse    = ChangeStringToBool(p_rqdeElement.attribute("InUse", ""));
    m_qstrComment = p_rqdeElement.attribute("Comment", "");
    QDomNode qDomNode = p_rqdeElement.firstChild();

    while (!qDomNode.isNull())
    {
        QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.

        if (!qDomElement.isNull())
        {
            if(qDomElement.tagName() == "Base Classes")
            {
                XmlImportBaseClasses(qDomElement);
            }
            else if(qDomElement.tagName() == "Class Members")
            {
                XmlImportMembers(qDomElement);
            }
            else
            {
                ERR("Invalid Tagin XML Document!!!!")
            }
        }
        else
        {
            ERR("Invalid DomElement in Class!!!")
        }

        qDomNode = qDomNode.nextSibling();
    }
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:12:49 2005----------*
 * @method  CdmClass::XmlImportBaseClasses                   // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:12:49 2005----------*/
void CdmClass::XmlImportBaseClasses(  QDomElement& p_rqDomElement )
{
    SYNCHRONIZED_WRITE;
    QDomNode qDomNode = p_rqDomElement.firstChild();
    while(!qDomNode.isNull())
    {
        QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.

        if(!qDomElement.isNull())
        {
            QString qstrKeyname = qDomElement.attribute("BaseClass", "");

            CdmClassManager* pCdmClassManager = GetClassManager();

            if(CHKPTR(pCdmClassManager))
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(qstrKeyname);

                if(CHKPTR(pCdmClass))
                {
                    if(!IsInherited(pCdmClass))
                    {
                        AddBaseClass(pCdmClass);
                    }
                    else
                    {
                        INFO("Class is already in baseclass list.")
                    }
                }
                else
                {
                    ERR("Base Class not found!!!")
                }
            }
        }
        else
        {
            ERR("Invalid DomElement in Class!!!")
        }

        qDomNode = qDomNode.nextSibling();
    }
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:12:53 2005----------*
 * @method  CdmClass::XmlImportMembers                       // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:12:53 2005----------*/
void CdmClass::XmlImportMembers(  QDomElement& p_rqDomElement )
{
    SYNCHRONIZED_WRITE;
    QDomNode qDomNode = p_rqDomElement.firstChild();

    while (!qDomNode.isNull())
    {
        QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.

        if (!qDomElement.isNull())
        {
            // TODO SB ???
        }
        else
        {
            ERR("Invalid DomElement in Class!!!")
        }

        qDomNode = qDomNode.nextSibling();
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:09:35 2013-----------*
 * @method  CdmClass::IsAbstract                             // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment returns if this class is an abstract base class.                                      *
 *----------------last changed: --------------------------------Sa 9. Feb 12:09:35 2013-----------*/
bool CdmClass::IsAbstract() const
{
    SYNCHRONIZED_READ;
    return m_bAbstract;
}

/** +-=---------------------------------------------------------Fr 8. Aug 19:20:09 2008-----------*
 * @method  CdmClass::SetAbstract                            // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bAbstract                                 //                                   *
 * @comment This method sets this class to an abstract class.                                     *
 *----------------last changed: --------------------------------Fr 8. Aug 19:20:09 2008-----------*/
void CdmClass::SetAbstract(bool p_bAbstract)
{
    m_bAbstract = p_bAbstract;
}

/** +-=---------------------------------------------------------Mi 7. Aug 20:04:39 2013-----------*
 * @method  CdmClass::GetCaptionMemberId                     // public, const                     *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 7. Aug 20:04:39 2013-----------*/
qint64 CdmClass::GetCaptionMemberId() const
{
    return m_lCaptionMember.load();
}

/** +-=---------------------------------------------------------Mi 7. Aug 20:04:14 2013-----------*
 * @method  CdmClass::GetCaptionMember                       // public, const                     *
 * @return  const CdmMember*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 7. Aug 20:04:14 2013-----------*/
const CdmMember* CdmClass::GetCaptionMember() const
{
    int iMember = m_lCaptionMember.load();

    if (iMember > 0)
    {
        return FindMember(m_lCaptionMember.load());
    }
    else
    {
        QString qstrCaptionMemberKeyname = GetCaptionMemberKeyname();

        if (!qstrCaptionMemberKeyname.isEmpty())
        {
            return FindMember(qstrCaptionMemberKeyname);
        }
    }

    return nullptr;
}

/** +-=---------------------------------------------------------Mi 7. Aug 19:52:41 2013-----------*
 * @method  CdmClass::GetCaptionMemberKeyname                // public, const                     *
 * @return  QString                                          //                                   *
 * @comment This method returns the caption member if exists. Otherwise an empty string will      *
 *----------------last changed: --------------------------------Mi 7. Aug 19:52:41 2013-----------*/
QString CdmClass::GetCaptionMemberKeyname() const
{
    SYNCHRONIZED_READ;
    QString qstrRet;

    const CdmMember* pMember = FindMember(m_lCaptionMember.load());

    if (pMember)
    {
        qstrRet = pMember->GetKeyname();
    }
    else // if no Captionmember exists
    {
        const CdmMember* pMember = FindMember("Name");
        INFO("No CaptionMember set")

        if (pMember && pMember->GetAccessMode() != eDmMemberAccessPrivate) // find out if a member "Name" exists
        {
            qstrRet = "Name";
            INFO("Not private Name member found using this as caption Member")
        }
        else // if not take the first member in class
        {
            QMap<qint64, CdmMember*>::const_iterator qmIt = m_qmMembers.begin();
            QMap<qint64, CdmMember*>::const_iterator qmItEnd = m_qmMembers.end();
            WARNING("No Caption Member and no non private Name member found. Looking for the first non private Member for displaying")

            for (; qmIt != qmItEnd; ++qmIt)
            {
                CdmMember* pCdmMember = qmIt.value();

                if (CHKPTR(pCdmMember) && (pCdmMember->GetAccessMode() != eDmMemberAccessPrivate))
                {
                    INFO("Member " + pCdmMember->GetKeyname() + " used as Caption Member.")
                    qstrRet = pCdmMember->GetKeyname();
                    break;
                }
            }
        }
    }

    return qstrRet;
}

/** +-=---------------------------------------------------------Fr 8. Aug 19:21:57 2008-----------*
 * @method  CdmClass::SetCaptionMember                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaptionMember                      //                                   *
 * @comment This method sets the caption member.                                                  *
 *----------------last changed: --------------------------------Fr 8. Aug 19:21:57 2008-----------*/
void CdmClass::SetCaptionMember(QString p_qstrCaptionMember)
{
    SYNCHRONIZED_WRITE;
    const CdmMember* pMember = FindMember(p_qstrCaptionMember);

    if (pMember)
    {
        if (pMember->GetId() != m_lCaptionMember.load())
        {
            m_lCaptionMember = pMember->GetId();
            SetModified();
        }
    }
}

/** +-=---------------------------------------------------------Mi 7. Aug 19:49:00 2013-----------*
 * @method  CdmClass::SetCaptionMember                       // public                            *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 7. Aug 19:49:00 2013-----------*/
void CdmClass::SetCaptionMember(CdmMember* p_pMember)
{
    if (p_pMember)
    {
        if (p_pMember->GetId() != m_lCaptionMember.load())
        {
            m_lCaptionMember = p_pMember->GetId();
            SetModified();
        }
    }
}

/** +-=---------------------------------------------------------Mi 7. Aug 19:50:11 2013-----------*
 * @method  CdmClass::SetCaptionMember                       // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lMemberId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 7. Aug 19:50:11 2013-----------*/
void CdmClass::SetCaptionMember(qint64 p_lMemberId)
{
    if (p_lMemberId != m_lCaptionMember.load())
    {
        m_lCaptionMember = p_lMemberId;
        SetModified();
    }
}

void CdmClass::SetMemberSequenceString(QMap<qint64,QString>& p_Sequence)
{
    SYNCHRONIZED_WRITE;
    if (!p_Sequence.isEmpty())
    {
        QMapIterator<qint64,QString> i(p_Sequence);
        while (i.hasNext()) {
            i.next();

            if (!m_qlMemberSequence.contains(i.value()))
            {
                m_qlMemberSequence.append(i.value());
            }
        }
    }
    else
    {
        QMap<qint64, CdmMember*> qmMembers;
        GetMemberMap(qmMembers);

        QMapIterator<qint64, CdmMember*> qmIt(qmMembers);
        while (qmIt.hasNext())
        {
            qmIt.next();
            m_qlMemberSequence.append(qmIt.value()->GetKeyname());
        }
    }
}


/** +-=---------------------------------------------------------Fr 8. Aug 19:25:53 2008-----------*
 * @method  CdmClass::SetMemberSequenceString                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrSequence                           //                                   *
 * @comment This method sets the position sequence string.                                        *
 *----------------last changed: --------------------------------Fr 8. Aug 19:25:53 2008-----------*/
void CdmClass::SetMemberSequenceString(QString p_qstrSequence)
{
    SYNCHRONIZED_WRITE;
    if (!p_qstrSequence.isEmpty())
    {
        QDomDocument qddDocument;
        QString qstrKey;
        QString qstrData;
        qddDocument.setContent(p_qstrSequence);
        QDomElement qdeElement = qddDocument.documentElement();
        QDomNode qdnNode = qdeElement.firstChild();

        while(!qdnNode.isNull())
        {
            qstrData = "";
            qstrKey = "";
            QDomElement qdeElement = qdnNode.toElement(); // try to convert the node to an element.
            qstrData = qdeElement.attribute("Data");

            if (!m_qlMemberSequence.contains(qstrData))
            {
                m_qlMemberSequence.append(qstrData);
            }

            qdnNode = qdnNode.nextSibling();
        }
    }
    else
    {
        QMap<qint64, CdmMember*> qmMembers;
        GetMemberMap(qmMembers);

        QMapIterator<qint64, CdmMember*> qmIt(qmMembers);
        while (qmIt.hasNext())
        {
            qmIt.next();
            if (!m_qlMemberSequence.contains(qmIt.value()->GetKeyname()))
            {
                m_qlMemberSequence.append(qmIt.value()->GetKeyname());
            }
        }
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:10:14 2013-----------*
 * @method  CdmClass::GetMemberSequenceString                // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method serializes the position sequence and returns it.                          *
 *----------------last changed: --------------------------------Sa 9. Feb 12:10:14 2013-----------*/
QString CdmClass::GetMemberSequenceString() const
{
    SYNCHRONIZED_READ;
    QDomDocument qddDocument("StringList");

    QDomElement qdeElement = qddDocument.createElement("ListEntries");
    qddDocument.appendChild(qdeElement);

    for (int iCounter = 0; iCounter < m_qlMemberSequence.size(); ++iCounter)
    {
        QString qstrMember = m_qlMemberSequence.at(iCounter);
        QDomElement qdeMapEntry = qddDocument.createElement("Entry");
        qdeMapEntry.setAttribute("Count", iCounter);
        qdeMapEntry.setAttribute("Data", qstrMember);
        qdeElement.appendChild(qdeMapEntry);
    }

    return qddDocument.toString();
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:00:31 2013----------*
 * @method  CdmClass::GetMemberSequence                      // public, const, slots              *
 * @return  QVector<QString>                                 //                                   *
 * @comment This method returns the membersequence.                                               *
 *----------------last changed: --------------------------------Mo 11. Feb 11:00:31 2013----------*/
QVector<QString> CdmClass::GetMemberSequence() const
{
    SYNCHRONIZED_READ;
    if (m_qlMemberSequence.isEmpty() || m_qlMemberSequence.count() < m_qmMembers.count())
    {
        QMap<qint64, CdmMember*> qmMembers;
        GetMemberMap(qmMembers);
        bool bModified = false;
        QMap<qint64, CdmMember*>::const_iterator qmIt = qmMembers.begin();
        QMap<qint64, CdmMember*>::const_iterator qmItEnd = qmMembers.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmMember* pCdmMember = qmIt.value();

            if (CHKPTR(pCdmMember))
            {
                if (!m_qlMemberSequence.contains(pCdmMember->GetKeyname()))
                {
                    m_qlMemberSequence.append(pCdmMember->GetKeyname());
                    bModified = true;
                }
            }
        }

        if (bModified)
        {
            (const_cast<CdmClass*>(this))->SetModified();
        }
    }

    return m_qlMemberSequence;
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:58:05 2012----------*
 * @method  CdmClass::SetMemberSequence                      // public                            *
 * @return  void                                             //                                   *
 * @param   QVector<QString>& p_qvlSequence                  //                                   *
 * @comment This method sets the membersequence.                                                  *
 *----------------last changed: --------------------------------Mi 22. Aug 17:58:05 2012----------*/
void CdmClass::SetMemberSequence(QVector<QString>& p_qvlSequence)
{
    SYNCHRONIZED_WRITE;
    m_qlMemberSequence.clear();

    for (int iPos = 0; iPos < p_qvlSequence.count(); ++iPos)
    {
        if (!m_qlMemberSequence.contains(p_qvlSequence[iPos]))
        {
            m_qlMemberSequence.append(p_qvlSequence[iPos]);
        }
    }

    SetModified();
}

/** +-=---------------------------------------------------------Do 28. Jun 15:29:18 2012----------*
 * @method  CdmClass::CreateGroup                            // public                            *
 * @return  CdmClassGroup*                                   //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   int p_iVersion                                   //                                   *
 * @param   CdmClassGroup* p_pCdmParent = nullptr               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Jun 15:29:18 2012----------*/
CdmClassGroup* CdmClass::CreateGroup(QString p_qstrName,
                                     int p_iVersion,
                                     int p_iPosition,
                                     CdmClassGroup* p_pCdmParent)
{
    SYNCHRONIZED_WRITE;
    CdmClassGroup* pCdmGroup = nullptr;

    if (!ExistClassGroup(p_qstrName))
    {
        if (p_pCdmParent)
        {
            pCdmGroup = new CdmClassGroup(this, p_qstrName, p_iPosition, p_iVersion, p_pCdmParent->GetId());
        }
        else
        {
            pCdmGroup = new CdmClassGroup(this, p_qstrName, p_iPosition, p_iVersion, 0);
        }

        m_qmGroups.insert(p_iPosition, pCdmGroup);
    }

    return pCdmGroup;
}

CdmClassGroup* CdmClass::CreateGroup(QString p_qstrName,
                                     int p_iVersion,
                                     CdmClassGroup* p_pCdmParent)
{
    SYNCHRONIZED_WRITE;
    CdmClassGroup* pCdmGroup = nullptr;

    if (!ExistClassGroup(p_qstrName))
    {
        if (p_pCdmParent)
        {
            pCdmGroup = new CdmClassGroup(this, p_qstrName, m_qmGroups.count(), p_iVersion, p_pCdmParent->GetId());
        }
        else
        {
            pCdmGroup = new CdmClassGroup(this, p_qstrName, m_qmGroups.count(), p_iVersion, 0);
        }

        m_qmGroups.insert(m_qmGroups.count(), pCdmGroup);
    }

    return pCdmGroup;
}


/** +-=---------------------------------------------------------Mo 20. Aug 16:58:08 2012----------*
 * @method  CdmClass::DeleteGroup                            // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 16:58:08 2012----------*/
void CdmClass::DeleteGroup(int p_iId)
{
    SYNCHRONIZED_WRITE;
    if (m_qmGroups.contains(p_iId))
    {
        CdmClassGroup* pCdmGroup = m_qmGroups[p_iId];

        if (pCdmGroup)
        {
            // now move up
            QMap<int, CdmClassGroup*>::const_iterator qmIt = m_qmGroups.begin();
            QMap<int, CdmClassGroup*>::const_iterator qmItEnd = m_qmGroups.end();
            QMap<int, CdmClassGroup*> qmGroupMap;

            for (; qmIt != qmItEnd; ++qmIt)
            {
                if (qmIt.key() < p_iId)
                {
                    qmGroupMap.insert(qmIt.key(), qmIt.value());
                }
                else if (qmIt.key() > p_iId)
                {
                    qmGroupMap[qmIt.key() - 1] = qmIt.value();
                }
                else
                {
                    // don't add the group which must be deleted
                }
            }

            m_qmGroups = qmGroupMap;
            QMap<qint64,CdmMember*> qmMap;
            GetMemberMap(qmMap);

            QMap<qint64,CdmMember*>::iterator iIt = qmMap.begin();
            QMap<qint64,CdmMember*>::iterator iItEnd = qmMap.end();

            for(; iIt != iItEnd; ++iIt)
            {
                CdmMember* pCdmMember = iIt.value();
                if(CHKPTR(pCdmMember) && pCdmMember->GetGroup() == pCdmGroup)
                {
                    pCdmMember->SetGroup(nullptr);
                }
            }

            DELPTR(pCdmGroup)
            SetModified();
        }


    }
}


/** +-=---------------------------------------------------------Sa 9. Feb 12:10:46 2013-----------*
 * @method  CdmClass::ExistClassGroup                        // private, const                    *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:10:46 2013-----------*/
bool CdmClass::ExistClassGroup(QString p_qstrName) const
{
    SYNCHRONIZED_READ;
    bool bRet = false;
    QMap<int, CdmClassGroup*>::const_iterator qmIt = m_qmGroups.begin();
    QMap<int, CdmClassGroup*>::const_iterator qmItEnd = m_qmGroups.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pCdmGroup = qmIt.value();

        if (CHKPTR(pCdmGroup) && pCdmGroup->GetName() == p_qstrName)
        {
            bRet = true;
        }
    }

    return bRet;
}

/** +-=---------------------------------------------------------Di 21. Aug 12:02:01 2012----------*
 * @method  CdmClass::MoveGroupUp                            // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iGroupId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Aug 12:02:01 2012----------*/
void CdmClass::MoveGroupUp(int p_iGroupId)
{
    SYNCHRONIZED_WRITE;
    int iPos = FindGroupPosById(p_iGroupId);

    if (m_qmGroups.contains(iPos) && m_qmGroups.contains(iPos - 1))
    {
        CdmClassGroup* pCdmGroupOldPos = m_qmGroups[iPos];
        CdmClassGroup* pCdmGroupNewPos = m_qmGroups[iPos - 1];

        if (CHKPTR(pCdmGroupOldPos) && CHKPTR(pCdmGroupOldPos))
        {
            m_qmGroups.insert(iPos - 1, pCdmGroupOldPos);
            pCdmGroupOldPos->SetPosition(iPos - 1);
            m_qmGroups.insert(iPos, pCdmGroupNewPos);
            pCdmGroupNewPos->SetPosition(iPos);
            SetModified();
        }
    }
}

/** +-=---------------------------------------------------------Di 21. Aug 12:01:54 2012----------*
 * @method  CdmClass::MoveGroupDown                          // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iGroupId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Aug 12:01:54 2012----------*/
void CdmClass::MoveGroupDown(int p_iGroupId)
{
    SYNCHRONIZED_WRITE;
    int iPos = FindGroupPosById(p_iGroupId);

    if (m_qmGroups.contains(iPos) && m_qmGroups.contains(iPos + 1))
    {
        CdmClassGroup* pCdmGroupOldPos = m_qmGroups[iPos];
        CdmClassGroup* pCdmGroupNewPos = m_qmGroups[iPos + 1];

        if (CHKPTR(pCdmGroupOldPos) && CHKPTR(pCdmGroupNewPos))
        {
            m_qmGroups.insert(iPos + 1, pCdmGroupOldPos);
            pCdmGroupOldPos->SetPosition(iPos + 1);
            m_qmGroups.insert(iPos, pCdmGroupNewPos);
            pCdmGroupNewPos->SetPosition(iPos);
            SetModified();
        }
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:11:19 2013-----------*
 * @method  CdmClass::GetClassGroups                         // public, const                     *
 * @return  const QMap<int, CdmClassGroup*>&                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:11:19 2013-----------*/
const QMap<int, CdmClassGroup*>& CdmClass::GetClassGroups() const
{
    return m_qmGroups;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:11:30 2013-----------*
 * @method  CdmClass::HasGroups                              // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:11:30 2013-----------*/
bool CdmClass::HasGroups() const
{
    SYNCHRONIZED_READ;
    bool bRet = false;

    QMap<int, CdmClassGroup*> qmGroups;
    GetGroups(qmGroups);

    if (qmGroups.count() > 0)
    {
        bRet = true;
    }

    return bRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:11:44 2013-----------*
 * @method  CdmClass::GetGroups                              // public, const, slots              *
 * @return  void                                             //                                   *
 * @param   QMap<int, CdmClassGroup*>& p_qmGroups            //                                   *
 * @param   int iIteration = 1                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:11:44 2013-----------*/
void CdmClass::GetGroups(QMap<int, CdmClassGroup*>& p_qmGroups, int iIteration) const
{
    SYNCHRONIZED_READ;
    QMap<int, CdmClassGroup*> qmGroups = GetClassGroups();

    QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
    QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pCdmGroup = qmIt.value();
        int iPos = qmIt.key();

        if (iIteration > 1)
        {
            iPos += ((iIteration - 1) * 100);
        }

        p_qmGroups.insert(iPos, pCdmGroup);
    }

    CdmDataProvider* pCdmManager = GetDataProvider();
    if(CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = GetDataProvider()->GetClassManager(GetSchemeId());

        if(pCdmClassManager)
        {
            CdmClass* pCdmClass = nullptr;

            QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
            QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

            for (int iCounter = 1; iItClasses != iItClassesEnd; ++iItClasses, ++iCounter)
            {
                pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                if(CHKPTR(pCdmClass))
                {
                    pCdmClass->GetGroups(p_qmGroups, ++iIteration);
                }
            }
        }
    }
}

CdmClassMethod* CdmClass::CreateMethod(QString p_qstrMethodName)
{
    CdmClassMethod* pMethod = nullptr;

    if (!HasMethod(p_qstrMethodName))
    {
        pMethod = new CdmClassMethod();
        pMethod->SetMethodName(p_qstrMethodName);
        AddMethod(pMethod);
    }

    return pMethod;

}

CdmClassMethod* CdmClass::CreateMethod(int p_iId,
                                       QString p_qstrMethodName,
                                       EdmValueType p_eReturnType,
                                       EdmMemberAccess p_eAccessMode,
                                       QString p_qstrCode,
                                       int p_iVersion)
{
    CdmClassMethod* pMethod = nullptr;

    if (!HasMethod(p_qstrMethodName))
    {
        pMethod = new CdmClassMethod(p_iId, p_qstrMethodName, p_eReturnType, p_eAccessMode, p_qstrCode, p_iVersion);
        AddMethod(pMethod);
    }

    return pMethod;
}


/** +-=---------------------------------------------------------Do 28. Jun 15:31:33 2012----------*
 * @method  CdmClass::AddMethod                              // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClassMethod* p_pCdmMethod                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Jun 15:31:33 2012----------*/
bool CdmClass::AddMethod(CdmClassMethod* p_pCdmMethod)
{
    bool bRet = false;
    SYNCHRONIZED_WRITE;
    if (CHKPTR(p_pCdmMethod))
    {
        if (!HasMethod(p_pCdmMethod->GetMethodName()))
        {
            p_pCdmMethod->SetClass(this);
            m_qmMethods.insert(p_pCdmMethod->GetMethodName(), p_pCdmMethod);
            SetModified();
            bRet = true;
        }
        else
        {
            ERR("Method already exists!")
        }
    }

    return bRet;
}

bool CdmClass::HasDirectClassImplementation(QString p_qstrName) const
{
    SYNCHRONIZED_READ;
    return m_qmMethods.contains(p_qstrName);
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:11:57 2013-----------*
 * @method  CdmClass::HasMethod                              // public, const, slots              *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:11:57 2013-----------*/
bool CdmClass::HasMethod(QString p_qstrName) const
{
    SYNCHRONIZED_READ;
    bool bRet = false;
    bRet = m_qmMethods.contains(p_qstrName);

    if (!bRet)
    {
        CdmClassManager* pCdmClassManager = GetDataProvider()->GetClassManager(GetSchemeId());

        if(pCdmClassManager)
        {
            QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
            QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

            for (; iItClasses != iItClassesEnd; ++iItClasses)
            {
               qint64 lId = iItClasses.value();
                CdmClass* pCdmClass = pCdmClassManager->FindClassById(lId);

                if(pCdmClass)
                {
                    bRet = pCdmClass->HasMethod(p_qstrName);
                    if (bRet)
                    {
                        break;
                    }
                }
            }
        }
    }

    return bRet;
}

/** +-=---------------------------------------------------------Mo 19. Nov 16:57:44 2012----------*
 * @method  CdmClass::FindMethod                             // public, slots                     *
 * @return  CdmClassMethod*                                  //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Nov 16:57:44 2012----------*/
CdmClassMethod* CdmClass::FindMethod(QString p_qstrName)
{
    SYNCHRONIZED_READ;
    CdmClassMethod* pRet = nullptr;

    if (m_qmMethods.contains(p_qstrName))
    {
        pRet = m_qmMethods[p_qstrName];
    }

    if (!pRet) // Ask baseclasses
    {
        CdmDataProvider* pCdmManager = GetDataProvider();
        if(CHKPTR(pCdmManager))
        {
            CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

            if(CHKPTR(pCdmClassManager))
            {
                CdmClass* pCdmClass = nullptr;

                QMap<qint64,qint64>::iterator iItClasses = m_qmBaseClasses.begin();
                QMap<qint64,qint64>::iterator iItClassesEnd = m_qmBaseClasses.end();

                for (; iItClasses != iItClassesEnd; ++iItClasses)
                {
                    pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                    if(pCdmClass && pCdmClass != this)
                    {
                        pRet = pCdmClass->FindMethod(p_qstrName);

                        if(pRet)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                EC(eDmInvalidClassPtr);
            }
        }
        else
        {
            EC(eDmInvalidPtr);
        }
    }

    return pRet;
}

/** +-=---------------------------------------------------------Fr 21. Sep 16:11:48 2012----------*
 * @method  CdmClass::DeleteMethod                           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Sep 16:11:48 2012----------*/
void CdmClass::DeleteMethod(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
    if (HasMethod(p_qstrName))
    {
        CdmClassMethod* pCdmMethod = m_qmMethods[p_qstrName];
        DELPTR(pCdmMethod)
        m_qmMethods.remove(p_qstrName);
        SetModified();
    }
}

void CdmClass::RemoveMethod(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
    if (HasMethod(p_qstrName))
    {
        m_qmMethods.remove(p_qstrName);
        SetModified();
    }
}

/** +-=---------------------------------------------------------Do 28. Jun 15:29:33 2012----------*
 * @method  CdmClass::AddValidation                          // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClassValidator* p_pValidator                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Jun 15:29:33 2012----------*/
void CdmClass::AddValidator(CdmClassValidator* p_pValidator)
{
    SYNCHRONIZED_WRITE;
    if (CHKPTR(p_pValidator))
    {
        if (!HasValidator(p_pValidator->GetName()))
        {
            m_qmValidators.insert(p_pValidator->GetName(), p_pValidator);
            SetModified();
        }
        else
        {
            ERR("Method already exists!")
        }
    }
}

/** +-=---------------------------------------------------------Fr 21. Sep 16:27:23 2012----------*
 * @method  CdmClass::FindValidation                         // public                            *
 * @return  CdmClassValidator*                               //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Sep 16:27:23 2012----------*/
CdmClassValidator* CdmClass::FindValidation(QString p_qstrName)
{
    SYNCHRONIZED_READ;
    CdmClassValidator* pRet = nullptr;

    if (HasValidator(p_qstrName))
    {
        pRet = m_qmValidators[p_qstrName];
    }

    if (!pRet) // Ask baseclasses
    {
        CdmDataProvider* pCdmManager = GetDataProvider();

        if (CHKPTR(pCdmManager))
        {
            CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

            if (CHKPTR(pCdmClassManager))
            {
                CdmClass* pCdmClass = nullptr;

                QMap<qint64,qint64>::iterator iItClasses = m_qmBaseClasses.begin();
                QMap<qint64,qint64>::iterator iItClassesEnd = m_qmBaseClasses.end();

                for (; iItClasses != iItClassesEnd; ++iItClasses)
                {
                    pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                    if (pCdmClass && (pCdmClass != this))
                    {
                        pRet = pCdmClass->FindValidation(p_qstrName);

                        if (pRet)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                EC(eDmInvalidClassPtr);
            }
        }
        else
        {
            EC(eDmInvalidPtr);
        }
    }

    return pRet;
}

bool CdmClass::HasValidator(QString p_qstrName) const
{
    SYNCHRONIZED_WRITE;
    return m_qmValidators.contains(p_qstrName);
}

void CdmClass::DeleteValidator(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
    if (HasValidator(p_qstrName))
    {
        CdmClassValidator* pValidation = m_qmValidators[p_qstrName];
        DELPTR(pValidation)
        m_qmValidators.remove(p_qstrName);
        SetModified();
    }
}

void CdmClass::UpdateVersion()
{
    ++m_iVersion;
    SetModified();
}

void CdmClass::SetVersion(int p_iVersion)
{
    m_iVersion = p_iVersion;
}

void CdmClass::IncreaseVersion()
{
    m_iVersion++;
}

int CdmClass::GetVersion() const
{
    return m_iVersion.load();
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:12:56 2005----------*
 * @method  CdmClass::XmlImport                              // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This is the public interface to import a xml class document.                          *
 *----------------last changed: --------------------------------Sa 13. Aug 21:12:56 2005----------*/
void CdmClass::XmlImport(QDomElement& p_rqDomElement)
{
    if(!p_rqDomElement.isNull())
    {
        XmlImportBase(p_rqDomElement);
        XmlImportClass(p_rqDomElement);
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:13:01 2013-----------*
 * @method  CdmClass::GetVariant                             // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:13:01 2013-----------*/
QVariant CdmClass::GetVariant() const
{
    SYNCHRONIZED_READ;
    QVariantMap qmVariant = CdmModelElement::GetVariant().toMap();
    QVariantMap qvAnnotation;
    QVariantList qlMembers;
    qmVariant.insert(WMS_CAPTIONMEMBER, GetCaptionMemberKeyname());
    qmVariant.insert(WMS_ABSTRACT, m_bAbstract);
    qmVariant.insert(WMS_INUSE, m_bIsInUse);
    qmVariant.insert(WMS_IMMUTABLE, IsImmutable());
    qmVariant.insert(WMS_SINGLETON, IsSingleton());
    qmVariant.insert(WMS_KEYNAME, GetFullQualifiedName());

    if (m_rPackage)
    {
        qmVariant.insert(WMS_PACKAGE, m_rPackage->GetUriInternal());
    }
    else
    {
        qmVariant.insert(WMS_PACKAGE, "");
    }

    qmVariant.insert(WMS_BASECLASSCOUNTER, m_lBaseClassCounter.load());
    qvAnnotation.insert(WMS_COMMENT, m_qstrComment);

    QMap<qint64,CdmMember*>::const_iterator qmIt = m_qmMembers.begin();
    QMap<qint64,CdmMember*>::const_iterator qmItEnd = m_qmMembers.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmMember* pCdmMember = qmIt.value();

        if (pCdmMember)
        {
            QVariant qvMember = pCdmMember->GetVariant();
            qlMembers.append(qvMember.toMap());
        }
    }

    qmVariant.insert(WMS_STRUCTURALFEATURE, qlMembers);


    QList<QVariant> qlMemberSequence;
    QVector<QString>::const_iterator qllIt = m_qlMemberSequence.begin();
    QVector<QString>::const_iterator qllItEnd = m_qlMemberSequence.end();


    for (; qllIt != qllItEnd; ++qllIt)
    {
        qlMemberSequence.append(*qllIt);
    }

    qmVariant.insert(WMS_MEMBERSEQUENCE, qlMemberSequence);

    QMap<qint64,qint64>::const_iterator qmItBC = m_qmBaseClasses.begin();
    QMap<qint64,qint64>::const_iterator qmItEndBC = m_qmBaseClasses.end();
    QVariantMap qmBaseclasses;

    for (; qmItBC != qmItEndBC; ++qmItBC)
    {
        CdmClassManager* pClassManager = GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassById(qmItBC.value());

            if (CHKPTR(pClass))
            {
                QVariantMap qvHash;
                qvHash.insert(WMS_CLASSID, pClass->GetId());
                qvHash.insert(WMS_POS, qmItBC.key());
                qvHash.insert(WMS_KEYNAME, pClass->GetFullQualifiedName());
                qvHash.insert(WMS_URI, pClass->GetUriInternal());

                qmBaseclasses.insert(pClass->GetKeyname(), qvHash);
            }
        }
    }

    qmVariant.insert(WMS_BASECLASSES, qmBaseclasses);

    QVariantMap qvGroups;
    QMap<int, CdmClassGroup*>::const_iterator qmItGroups = m_qmGroups.begin();
    QMap<int, CdmClassGroup*>::const_iterator qmItGroupsEnd = m_qmGroups.end();

    for (; qmItGroups != qmItGroupsEnd; ++qmItGroups)
    {
        CdmClassGroup* pCdmGroup = qmItGroups.value();

        if (CHKPTR(pCdmGroup))
        {
            qvGroups.insert(QString::number(qmItGroups.key()), pCdmGroup->GetVariant());
        }
    }

    qmVariant.insert(WMS_GROUPS, qvGroups);

    QVariantMap qvMethods;
    QMap<QString, CdmClassMethod*>::const_iterator qmItMethod = m_qmMethods.begin();
    QMap<QString, CdmClassMethod*>::const_iterator qmItMethodEnd = m_qmMethods.end();

    for (; qmItMethod != qmItMethodEnd; ++qmItMethod)
    {
        CdmClassMethod* pCdmMethod = qmItMethod.value();

        if (CHKPTR(pCdmMethod))
        {
            qvMethods.insert(qmItMethod.key(), pCdmMethod->GetVariant());
        }
    }

    qmVariant.insert(WMS_METHODS, qvMethods);


    QVariantMap qvValidations;
    QMap<QString, CdmClassValidator*>::const_iterator qmItValidators = m_qmValidators.begin();
    QMap<QString, CdmClassValidator*>::const_iterator qmItValidatorsEnd = m_qmValidators.end();

    for (; qmItValidators != qmItValidatorsEnd; ++qmItValidators)
    {
        CdmClassValidator* pCdmValidator = qmItValidators.value();

        if (CHKPTR(pCdmValidator))
        {
            qvValidations.insert(qmItValidators.key(), pCdmValidator->GetVariant());
        }
    }

    qmVariant.insert(WMS_VALIDATIONS, qvValidations);
    qmVariant.insert(WMS_ANNOTATION, qvAnnotation);


    return qmVariant;
}

/** +-=---------------------------------------------------------Mo 19. Nov 16:58:40 2012----------*
 * @method  CdmClass::FindGroupById                          // public, slots                     *
 * @return  CdmClassGroup*                                   //                                   *
 * @param  qint64 p_lGroupId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Nov 16:58:40 2012----------*/
CdmClassGroup* CdmClass::FindGroupById(qint64 p_lGroupId)
{
    SYNCHRONIZED_READ;
    CdmClassGroup* pCdmGroup = nullptr;

    if (p_lGroupId > 0)
    {
        QMap<int, CdmClassGroup*>::iterator qmItGroups = m_qmGroups.begin();
        QMap<int, CdmClassGroup*>::iterator qmItGroupsEnd = m_qmGroups.end();

        for (; qmItGroups != qmItGroupsEnd; ++qmItGroups)
        {
            CdmClassGroup* pCdmGroupTemp = qmItGroups.value();

            if (CHKPTR(pCdmGroupTemp))
            {
                if (pCdmGroupTemp->GetId() == p_lGroupId)
                {
                    pCdmGroup = pCdmGroupTemp;
                    break;
                }
            }
        }
    }

    if (!pCdmGroup)
    {
        CdmClassManager* pCdmClassManager = GetClassManager();
        if (pCdmClassManager)
        {
            QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
            QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

            for (int iCounter = 1; iItClasses != iItClassesEnd; ++iItClasses, ++iCounter)
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                if(CHKPTR(pCdmClass))
                {
                    pCdmGroup = pCdmClass->FindGroupById(p_lGroupId);

                    if (pCdmGroup)
                    {
                        break;
                    }
                }
            }
        }
    }

    return pCdmGroup;
}

/** +-=---------------------------------------------------------Mo 19. Nov 16:58:49 2012----------*
 * @method  CdmClass::FindGroupPosById                       // public, slots                     *
 * @return  int                                              //                                   *
 * @param  qint64 p_lGroupId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Nov 16:58:49 2012----------*/
int CdmClass::FindGroupPosById(qint64 p_lGroupId)
{
    SYNCHRONIZED_READ;
    int iRet = 0;
    QMap<int, CdmClassGroup*>::iterator qmItGroups = m_qmGroups.begin();
    QMap<int, CdmClassGroup*>::iterator qmItGroupsEnd = m_qmGroups.end();

    for (; qmItGroups != qmItGroupsEnd; ++qmItGroups)
    {
        CdmClassGroup* pCdmGroupTemp = qmItGroups.value();

        if (CHKPTR(pCdmGroupTemp))
        {
            if (pCdmGroupTemp->GetId() == p_lGroupId)
            {
                iRet = qmItGroups.key();
                break;
            }
        }
    }

    return iRet;
}

/** +-=---------------------------------------------------------Fr 7. Dez 11:15:17 2012-----------*
 * @method  CdmClass::FindGroupByName                        // public, slots                     *
 * @return  CdmClassGroup*                                   //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Dez 11:15:17 2012-----------*/
CdmClassGroup* CdmClass::FindGroupByName(QString p_qstrName)
{
    SYNCHRONIZED_READ;
    CdmClassGroup* pCdmGroup = nullptr;
    QMap<int, CdmClassGroup*>::iterator qmItGroups = m_qmGroups.begin();
    QMap<int, CdmClassGroup*>::iterator qmItGroupsEnd = m_qmGroups.end();

    for (; qmItGroups != qmItGroupsEnd; ++qmItGroups)
    {
        CdmClassGroup* pCdmGroupTemp = qmItGroups.value();

        if (CHKPTR(pCdmGroupTemp))
        {
            if (pCdmGroupTemp->GetName() == p_qstrName)
            {
                pCdmGroup = pCdmGroupTemp;
                break;
            }
        }
    }

    if (!pCdmGroup)
    {
        CdmClassManager* pCdmClassManager = GetClassManager();
        if (pCdmClassManager)
        {
            QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
            QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

            for (int iCounter = 1; iItClasses != iItClassesEnd; ++iItClasses, ++iCounter)
            {
                CdmClass* pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

                if(CHKPTR(pCdmClass))
                {
                    pCdmGroup = pCdmClass->FindGroupByName(p_qstrName);

                    if (pCdmGroup)
                    {
                        break;
                    }
                }
            }
        }
    }

    return pCdmGroup;
}

/** +-=---------------------------------------------------------So 15. Apr 13:32:49 2012----------*
 * @method  CdmClass::ParseBaseClasses                       // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 13:32:49 2012----------*/
void CdmClass::ParseBaseClasses(QVariantMap& p_rqHash)
{
    SYNCHRONIZED_WRITE;
    m_qmBaseClasses.clear();
    QVariantMap::iterator qIt = p_rqHash.begin();
    QVariantMap::iterator qItEnd = p_rqHash.end();

    for (; qIt != qItEnd; ++qIt)
    {
        QString qstrKeyname = qIt.key();
        QVariantMap qvHash = qIt.value().toMap();
       qint64 lPos = qvHash["Pos"].toInt();
       qint64 lClassId = qvHash["ClassId"].toInt();
        m_qmBaseClasses.insert(lPos, lClassId);
    }
}

/** +-=---------------------------------------------------------Mo 12. Nov 17:38:36 2012----------*
 * @method  CdmClass::ParseMembers                           // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantList& p_rqHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 12. Nov 17:38:36 2012----------*/
void CdmClass::ParseMembers(QVariantList& p_rqHash)
{
    SYNCHRONIZED_WRITE;
    QVariantList::iterator qIt = p_rqHash.begin();
    QVariantList::iterator qItEnd = p_rqHash.end();

    for (; qIt != qItEnd; ++qIt)
    {
        QVariantMap qMember = (*qIt).toMap();
        CdmMember* pCdmMember = FindClassMember(qMember[WMS_KEYNAME].toString());

        if (pCdmMember == nullptr)
        {
            pCdmMember = new CdmMember(qMember, GetId());
           qint64 lId = pCdmMember->GetId();
            m_qmMembers.insert(lId, pCdmMember);
        }
        else
        {
            pCdmMember->SetVariant(qMember);
        }
    }
}

/** +-=---------------------------------------------------------So 15. Apr 13:35:36 2012----------*
 * @method  CdmClass::ParseMemberSequences                   // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantList& p_rqHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 13:35:36 2012----------*/
void CdmClass::ParseMemberSequences(QVariantList& p_rqHash)
{
    SYNCHRONIZED_WRITE;
    m_qlMemberSequence.clear();
    for (int iPos = 0; iPos < p_rqHash.size(); ++iPos)
    {
        if (!m_qlMemberSequence.contains(p_rqHash[iPos].toString()))
        {
            m_qlMemberSequence.append(p_rqHash[iPos].toString());
        }
    }
}

/** +-=---------------------------------------------------------Mo 25. Jun 19:04:03 2012----------*
 * @method  CdmClass::ParseMethods                           // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 19:04:03 2012----------*/
void CdmClass::ParseMethods(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qvIt = p_rqvHash.begin();
    QVariantMap::iterator qvItEnd = p_rqvHash.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        QVariantMap qvHash = qvIt.value().toMap();
        CdmClassMethod* pCdmMethod = new CdmClassMethod(qvHash);
        AddMethod(pCdmMethod);
    }
}

/** +-=---------------------------------------------------------Mo 25. Jun 19:04:26 2012----------*
 * @method  CdmClass::ParseGroups                            // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 19:04:26 2012----------*/
void CdmClass::ParseGroups(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qvIt = p_rqvHash.begin();
    QVariantMap::iterator qvItEnd = p_rqvHash.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        int iKey = qvIt.key().toInt();
        QVariantMap qvHash = qvIt.value().toMap();
        CdmClassGroup* pCdmGroup = new CdmClassGroup(qvHash, this, nullptr);
        m_qmGroups.insert(iKey, pCdmGroup);
    }
}

/** +-=---------------------------------------------------------Mo 25. Jun 19:04:39 2012----------*
 * @method  CdmClass::ParseValidations                       // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 19:04:39 2012----------*/
void CdmClass::ParseValidations(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qvIt = p_rqvHash.begin();
    QVariantMap::iterator qvItEnd = p_rqvHash.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        QVariantMap qvHash = qvIt.value().toMap();
        CdmClassValidator* pCdmValidator = new CdmClassValidator(qvHash);
        AddValidator(pCdmValidator);
    }
}

/** +-=---------------------------------------------------------Mi 27. Jun 15:49:19 2012----------*
 * @method  CdmClass::GetMethods                             // public                            *
 * @return  QMap<QString, CdmClassMethod*>&                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 15:49:19 2012----------*/
QMap<QString, CdmClassMethod*>& CdmClass::GetMethods()
{
    SYNCHRONIZED_READ;
    return m_qmMethods;
}

QMap<QString, CdmClassMethod*> CdmClass::GetAllMethods()
{
    SYNCHRONIZED_READ;
    QMap<QString, CdmClassMethod*> qmMethods;
    CdmClassManager* pCdmClassManager = GetClassManager();

    if(CHKPTR(pCdmClassManager))
    {
        CdmClass* pCdmClass = nullptr;
        QMap<qint64,qint64>::iterator iItClasses = m_qmBaseClasses.begin();
        QMap<qint64,qint64>::iterator iItClassesEnd = m_qmBaseClasses.end();

        for (; iItClasses != iItClassesEnd; ++iItClasses)
        {
            pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

            if(pCdmClass && pCdmClass != this)
            {
                QMap<QString, CdmClassMethod*> qmTemp = pCdmClass->GetAllMethods();
                QMap<QString, CdmClassMethod*>::iterator qmIt = qmTemp.begin();
                QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmTemp.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    CdmClassMethod* pMethod = qmIt.value();
                    qmMethods.insert(qmIt.key(), pMethod);
                }
            }
        }
    }

    QMap<QString, CdmClassMethod*>::iterator qmIt = m_qmMethods.begin();
    QMap<QString, CdmClassMethod*>::iterator qmItEnd = m_qmMethods.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassMethod* pMethod = qmIt.value();

        if (CHKPTR(pMethod))
        {
            qmMethods.insert(qmIt.key(), qmIt.value());
        }
    }

    return qmMethods;
}

/** +-=---------------------------------------------------------Mo 19. Nov 16:59:21 2012----------*
 * @method  CdmClass::GetMethod                              // public, slots                     *
 * @return  CdmClassMethod*                                  //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Nov 16:59:21 2012----------*/
CdmClassMethod* CdmClass::GetMethod(QString p_qstrName)
{
    SYNCHRONIZED_READ;
    return FindMethod(p_qstrName);
}

/** +-=---------------------------------------------------------Mi 27. Jun 16:25:26 2012----------*
 * @method  CdmClass::GetValidators                          // public                            *
 * @return  QMap<QString, CdmClassValidator*>&               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 16:25:26 2012----------*/
QMap<QString, CdmClassValidator*>& CdmClass::GetValidators()
{
    return m_qmValidators;
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:52:17 2012----------*
 * @method  CdmClass::HasValidators                          // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 14:52:17 2012----------*/
bool CdmClass::HasValidators()
{
    bool bRet = false;

    if (m_qmValidators.count() > 0)
    {
        bRet = true;
    }

    return bRet;
}

/** +-=---------------------------------------------------------So 10. Feb 18:07:15 2013----------*
 * @method  CdmClass::FindMember                             // public, const, slots              *
 * @return  const CdmMember*                                 //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 18:07:15 2013----------*/
const CdmMember* CdmClass::FindMember(int p_iId) const
{
    SYNCHRONIZED_READ;
    CdmMember* pCdmMember = nullptr;

    if (m_qmMembers.contains(p_iId))
    {
        pCdmMember = m_qmMembers[p_iId];
    }
    else
    {
        CdmClassManager* pCdmClassManager = GetClassManager();
        QMap<qint64,qint64>::const_iterator iItClasses = m_qmBaseClasses.begin();
        QMap<qint64,qint64>::const_iterator iItClassesEnd = m_qmBaseClasses.end();

        for (int iCounter = 1; iItClasses != iItClassesEnd; ++iItClasses, ++iCounter)
        {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(iItClasses.value());

            if(CHKPTR(pCdmClass))
            {
                pCdmMember = const_cast<CdmMember*>(pCdmClass->FindMember(p_iId));

                if (pCdmMember)
                {
                    break;
                }
            }
        }
    }

    return pCdmMember;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:14:09 2013-----------*
 * @method  CdmClass::IsClass                                // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:14:09 2013-----------*/
bool CdmClass::IsClass() const
{
    return true;
}

/** +-=---------------------------------------------------------Fr 30. Nov 10:17:43 2012----------*
 * @method  CdmClass::Deploy                                 // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 10:17:43 2012----------*/
void CdmClass::Deploy(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    CdmModelElement::Deploy(p_rqvHash);
    m_bAbstract  = p_rqvHash[WMS_ABSTRACT].toBool();
    m_bIsInUse  = p_rqvHash[WMS_INUSE].toBool();
    m_lBaseClassCounter  = p_rqvHash[WMS_BASECLASSCOUNTER].toInt();
    m_iVersion = p_rqvHash[WMS_VERSION].toInt();
    QVariantMap qvAnnotation = p_rqvHash[WMS_ANNOTATION].toMap();
    m_qstrComment = qvAnnotation[WMS_COMMENT].toString();
    SetImmutable(qvAnnotation[WMS_IMMUTABLE].toBool());
    SetSingleton(qvAnnotation[WMS_SINGLETON].toBool());

    QVariantList qvMembers = p_rqvHash[WMS_STRUCTURALFEATURE].toList();
    QVariantMap qvBaseClasses = p_rqvHash[WMS_BASECLASSES].toMap();
    QVariantList qvMemberSequences = p_rqvHash[WMS_MEMBERSEQUENCE].toList();
    QVariantMap qvMethods = p_rqvHash[WMS_METHODS].toMap();
    QVariantMap qvGroups = p_rqvHash[WMS_GROUPS].toMap();
    QVariantMap qvValidations = p_rqvHash[WMS_VALIDATIONS].toMap();
    QString qstrPackage = p_rqvHash[WMS_PACKAGE].toString();

    CdmDataProvider* pManager = GetDataProvider();

    if (CHKPTR(pManager) && !qstrPackage.isEmpty())
    {
        CdmLocatedElement* pElement = pManager->GetUriObject(qstrPackage);

        if (CHKPTR(pElement) && pElement->IsPackage())
        {
            m_rPackage = static_cast<CdmPackage*>(pElement);
            m_rPackage->AddClass(this);
        }
    }

    DeployGroups(qvGroups);
    DeployMembers(qvMembers);
    DeployBaseClasses(qvBaseClasses);
    ParseMemberSequences(qvMemberSequences);
    DeployMethods(qvMethods);
    DeployValidations(qvValidations);

    ResetGroupIds();


    SetCaptionMember(p_rqvHash[WMS_CAPTIONMEMBER].toString());
}

/** +-=---------------------------------------------------------Fr 30. Nov 10:21:54 2012----------*
 * @method  CdmClass::DeployMembers                          // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantList& p_rqHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 10:21:54 2012----------*/
void CdmClass::DeployMembers(QVariantList& p_rqHash)
{
    SYNCHRONIZED_WRITE;
    QVariantList::iterator qIt = p_rqHash.begin();
    QVariantList::iterator qItEnd = p_rqHash.end();

    for (; qIt != qItEnd; ++qIt)
    {
        QVariantMap qMember = (*qIt).toMap();
        QString qstrKeyname = qMember[WMS_KEYNAME].toString();
        CdmMember* pCdmMember = const_cast<CdmMember*>(FindMember(qstrKeyname));

        if (pCdmMember)
        {
            pCdmMember->Deploy(qMember);
        }
        else
        {
            CdmMember* pCdmMember = new CdmMember(GetSchemeId(),
                                                  GetNewMemberId(),
                                                  qMember[WMS_KEYNAME].toString(),
                                                  (EdmValueType)qMember[WMS_VALUETYPE].toInt(),
                                                  false,
                                                  0);
            pCdmMember->SetClassId(GetId());
            pCdmMember->Deploy(qMember);
            AddMember(pCdmMember);
            pCdmMember->SetNew();
        }
    }
}

/** +-=---------------------------------------------------------Fr 30. Nov 10:21:43 2012----------*
 * @method  CdmClass::DeployMethods                          // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 10:21:43 2012----------*/
void CdmClass::DeployMethods(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qvIt = p_rqvHash.begin();
    QVariantMap::iterator qvItEnd = p_rqvHash.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        QVariantMap qvHash = qvIt.value().toMap();
        QString qstrName = qvHash[WMS_NAME].toString();
        CdmClassMethod* pCdmMethod = FindMethod(qstrName);

        if (pCdmMethod)
        {
            pCdmMethod->SetVariant(qvHash);
        }
        else
        {
            pCdmMethod = new CdmClassMethod(qvHash);
            pCdmMethod->SetId(-1);
            AddMethod(pCdmMethod);
        }
    }
}

/** +-=---------------------------------------------------------Fr 30. Nov 10:21:35 2012----------*
 * @method  CdmClass::DeployGroups                           // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 10:21:35 2012----------*/
void CdmClass::DeployGroups(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qvIt = p_rqvHash.begin();
    QVariantMap::iterator qvItEnd = p_rqvHash.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        int iKey = qvIt.key().toInt();
        QVariantMap qvHash = qvIt.value().toMap();
        QString qstrName = qvHash[WMS_NAME].toString();

        if (!FindGroupByName(qstrName))
        {
            CdmClassGroup* pCdmGroup = new CdmClassGroup(qvHash, this, nullptr);

            if (m_qmGroups.contains(iKey))
            {
                WARNING("Group with Key " + QString::number(iKey) + " already exists.")
            }

            m_qmGroups.insert(iKey, pCdmGroup);
        }
    }
}

/** +-=---------------------------------------------------------Fr 30. Nov 10:21:26 2012----------*
 * @method  CdmClass::DeployValidations                      // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 10:21:26 2012----------*/
void CdmClass::DeployValidations(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qvIt = p_rqvHash.begin();
    QVariantMap::iterator qvItEnd = p_rqvHash.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        QVariantMap qvHash = qvIt.value().toMap();

        QString qstrName = qvHash[WMS_NAME].toString();
        CdmClassValidator* pCdmValidator = FindValidation(qstrName);

        if (pCdmValidator)
        {
            pCdmValidator->SetVariant(qvHash);
        }
        else
        {
            CdmClassValidator* pCdmValidator = new CdmClassValidator(qvHash);
            pCdmValidator->SetId(-1);
            AddValidator(pCdmValidator);
        }
    }
}

/** +-=---------------------------------------------------------Fr 30. Nov 11:52:16 2012----------*
 * @method  CdmClass::DeployBaseClasses                      // private                           *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Nov 11:52:16 2012----------*/
void CdmClass::DeployBaseClasses(QVariantMap& p_rqHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap::iterator qIt = p_rqHash.begin();
    QVariantMap::iterator qItEnd = p_rqHash.end();

    for (; qIt != qItEnd; ++qIt)
    {
        QVariantMap qvHash = qIt.value().toMap();
       qint64 lPos = qvHash[WMS_POS].toInt();
        QString qstrKeyname = qvHash[WMS_KEYNAME].toString();

        CdmClassManager* pClassManager = GetClassManager();

        if (pClassManager)
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(qstrKeyname);

            if (CHKPTR(pClass))
            {
               qint64 lId = pClass->GetId();

                if (m_qmBaseClasses.contains(lPos))
                {
                    if (m_qmBaseClasses[lPos] != lId && !IsTypeOf(lId))
                    {
                        AddBaseClass(pClass);
                    }
                }
                else if (!IsTypeOf(lId))
                {
                    m_qmBaseClasses.insert(lPos, lId);
                    AddBaseClassData(pClass);
                }
            }
        }
    }
}

void CdmClass::ResetGroupIds()
{
    SYNCHRONIZED_READ;
    QMap<int, CdmClassGroup*>::iterator qmIt = m_qmGroups.begin();
    QMap<int, CdmClassGroup*>::iterator qmItEnd = m_qmGroups.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmClassGroup* pGroup = qmIt.value();

        if (CHKPTR(pGroup))
        {
            pGroup->SetId(0);
        }
    }
}

void CdmClass::SetKeyname(QString p_qstrKeyname)
{
    CdmModelElement::SetKeyname(p_qstrKeyname);
}

QString CdmClass::GetUri() const
{
    QString qstrType = GetUriType();
    return CreateUri(qstrType, GetFullQualifiedName());
}

QString CdmClass::GetUriInternal() const
{
    QString qstrType = GetUriType();
    return CreateUriPath(qstrType, GetFullQualifiedName(), "", "");
}

bool CdmClass::IsTypeOf(qint64 p_lClassId)
{
    SYNCHRONIZED_READ;
    bool bRet = false;

    CdmClassManager* pClassManager = GetClassManager();

    if (CHKPTR(pClassManager))
    {
        QMap<qint64,qint64>::const_iterator qmIt = m_qmBaseClasses.begin();
        QMap<qint64,qint64>::const_iterator qmItEnd = m_qmBaseClasses.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            if (qmIt.value() == p_lClassId)
            {
                bRet = true;
                break;
            }
            else
            {
                CdmClass* pClass = pClassManager->FindClassById(qmIt.value());

                if (pClass)
                {
                    bRet = pClass->IsTypeOf(p_lClassId);

                    if (bRet)
                    {
                        break;
                    }
                }
            }
        }
    }

    return bRet;
}

QList<qint64> CdmClass::GetDerivedClasses() const
{
    SYNCHRONIZED_READ;
    QList<qint64> qlDerivedClasses;
    CdmClassManager* pClassManager = GetClassManager();

    if (CHKPTR(pClassManager))
    {
        QList<CdmClass*> qlClasses;
        pClassManager->GetClassList(qlClasses);

        QList<CdmClass*>::iterator qIt = qlClasses.begin();
        QList<CdmClass*>::iterator qItEnd = qlClasses.end();

        for (; qIt != qItEnd; ++qIt)
        {
            if ((*qIt)->IsTypeOf(GetId()))
            {
                qlDerivedClasses.append((*qIt)->GetId());
            }
        }
    }

    return qlDerivedClasses;
}

QList<CdmClass*> CdmClass::getDerivedClasses()
{
    SYNCHRONIZED_READ;
    QList<CdmClass*> qlDerivedClasses;
    CdmClassManager *pClassManager = GetClassManager();

    if(CHKPTR(pClassManager))
    {
        QList<CdmClass*> qlClasses;
        pClassManager->GetClassList(qlClasses);

        QList<CdmClass*>::iterator qIt = qlClasses.begin();
        QList<CdmClass*>::iterator qItEnd = qlClasses.end();

        for (; qIt != qItEnd; ++qIt)
        {
            if ((*qIt)->IsTypeOf(GetId()))
            {
                qlDerivedClasses.append((*qIt));
            }
        }
    }
    return qlDerivedClasses;
}

bool CdmClass::IsSingleton() const
{
    return GetConfigItem("Singleton").toBool();
}

bool CdmClass::IsImmutable() const
{
    return GetConfigItem("Immutable").toBool();
}

void CdmClass::SetSingleton(bool p_bSingleton)
{
    SetConfigItem("Singleton", p_bSingleton);
    SetModified();
}

void CdmClass::SetImmutable(bool p_bImmutable)
{
    SetConfigItem("Immutable", p_bImmutable);
    SetModified();
}

CdmObject* CdmClass::GetSingletonObject()
{
    CdmObject* pObject = nullptr;

    if (IsSingleton())
    {
        CdmContainerManager* pContainerManager = GetContainerManager();
        QString qstrKeyname = GetFullQualifiedName().replace(".","_") + "_Singleton";

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindContainerByKeyname(qstrKeyname);

            if (!pContainer)
            {
                if (SUCCESSFULL(pContainerManager->CreateContainer(this, qstrKeyname)))
                {
                    pContainer = pContainerManager->FindContainerByKeyname(qstrKeyname);
                }
            }

            if (CHKPTR(pContainer))
            {
                pObject = pContainer->FindObjectByKeyname(qstrKeyname);

                if (!pObject)
                {
                    pObject = pContainer->CreateNewObject(qstrKeyname);

                    if (!pObject)
                    {
                        ERR("Failed to create singleton object.")
                    }
                    else
                    {
                        pObject->Commit();
                    }
                }
            }
        }
    }

    return pObject;
}

void CdmClass::SetIsEventClass(bool p_bIsEventClass)
{
    SetConfigItem("IsEventClass", p_bIsEventClass);
    SetModified();
}

bool CdmClass::IsEventClass() const
{
    return false;
}

void CdmClass::SetEventSourcingActive(bool p_bEventSourcingActive)
{
    SetConfigItem("IsEventSourcingActive", p_bEventSourcingActive);
    SetModified();
}

bool CdmClass::IsEventSourcingActive() const
{

    return false;
}

void CdmClass::SetCreateEventClass(QString p_qstrCreateEvent)
{
    SetConfigItem("CreateEventClass", p_qstrCreateEvent);
    SetModified();
}

QString CdmClass::getCreateEventClass() const
{
    return GetConfigItem("CreateEventClass").toString();
}

void CdmClass::SetDeleteEventClass(QString p_qstrDeleteEvent)
{
    SetConfigItem("DeleteEventClass", p_qstrDeleteEvent);
    SetModified();
}

QString CdmClass::getDeleteEventClass() const
{
    return GetConfigItem("DeleteEventClass").toString();
}

void CdmClass::SetUpdateEventClass(QString p_qstrUpdateEvent)
{
    SetConfigItem("UpdateEventClass",p_qstrUpdateEvent);
    SetModified();
}

QString CdmClass::getUpdateEventClass() const
{
    return GetConfigItem("UpdateEventClass").toString();
}

QStringList CdmClass::getCreateEventClassStringList() const
{
    return GetConfigItem("CreateEventClassStringList").toStringList();
}

void CdmClass::SetCreateEventClassStringList(QStringList p_qstrlList)
{
    SetConfigItem("CreateEventClassStringList", p_qstrlList);
}

QStringList CdmClass::getDeleteEventClassStringList() const
{
    return GetConfigItem("DeleteEventClassStringList").toStringList();
}

void CdmClass::SetDeleteEventClassStringList(QStringList p_qstrlList)
{
    SetConfigItem("DeleteEventClassStringList", p_qstrlList);
}

QStringList CdmClass::getUpdateEventClassStringList() const
{
    return GetConfigItem("UpdateEventClassStringList").toStringList();
}

void CdmClass::SetUpdateEventClassStringList(QStringList p_qstrlList)
{
    SetConfigItem("UpdateEventClassStringList", p_qstrlList);
}


void CdmClass::SetCreateEventClassList(QList<CdmClass *> qlCreateEventClasses)
{
    QList<CdmClass*>::iterator qlItStart = qlCreateEventClasses.begin();
    QList<CdmClass*>::iterator qlItEnd = qlCreateEventClasses.end();
    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        if(!m_qlCreateEventClasses.contains((*qlItStart)))
        {
            m_qlCreateEventClasses.append((*qlItStart));
        }
    }
    setCreateEventClassListStringList(qlCreateEventClasses);
}

QList<CdmClass *> CdmClass::getCreateEventClassList() const
{
    return m_qlCreateEventClasses;
}

void CdmClass::setCreateEventClassListStringList(QList<CdmClass*> qlCreateEventClassList)
{
    QList<CdmClass*>::iterator qlItStart = qlCreateEventClassList.begin();
    QList<CdmClass*>::iterator qlItEnd = qlCreateEventClassList.end();
    QStringList qstrlEventClasses = getCreateEventClassStringList();
    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        QString qstrEventClass = (*qlItStart)->GetKeyname();

        if(!qstrlEventClasses.contains(qstrEventClass))
        {
            qstrlEventClasses.append(qstrEventClass);
        }
    }

    SetCreateEventClassStringList(qstrlEventClasses);
}

void CdmClass::SetDeleteEventClassList(QList<CdmClass *> qlDeleteEventClasses)
{
    QList<CdmClass*>::iterator qlItStart = qlDeleteEventClasses.begin();
    QList<CdmClass*>::iterator qlItEnd = qlDeleteEventClasses.end();

    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        if(!m_qlDeleteEventClasses.contains((*qlItStart)))
        {
            m_qlDeleteEventClasses.append((*qlItStart));
        }
    }
    setDeleteEventClassListStringList(qlDeleteEventClasses);
}

QList<CdmClass *> CdmClass::getDeleteEventClassList() const
{
    return m_qlDeleteEventClasses;
}

QList<CdmClass *> CdmClass::getUpdateEventClassList() const
{
    return m_qlUpdateEventClasses;
}

void CdmClass::setSelectedEventClass(CdmClass *pEventClass)
{
    m_pEventClass = pEventClass;
}

CdmClass *CdmClass::getSelectedEventClass()
{
    return m_pEventClass;
}

void CdmClass::setDeleteEventClassListStringList(QList<CdmClass *> qlDeleteEventClassList)
{
    QList<CdmClass*>::iterator qlItStart = qlDeleteEventClassList.begin();
    QList<CdmClass*>::iterator qlItEnd = qlDeleteEventClassList.end();
    QStringList qstrlEventClasses = getDeleteEventClassStringList();
    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        QString qstrEventClass = (*qlItStart)->GetKeyname();
        if(!qstrlEventClasses.contains(qstrEventClass))
        {
            qstrlEventClasses.append(qstrEventClass);
        }
    }

    SetDeleteEventClassStringList(qstrlEventClasses);
}

void CdmClass::SetUpdateEventClassList(QList<CdmClass*> qlUpdateEventClasses)
{
    QList<CdmClass*>::iterator qlItStart = qlUpdateEventClasses.begin();
    QList<CdmClass*>::iterator qlItEnd = qlUpdateEventClasses.end();
    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        if(!m_qlUpdateEventClasses.contains((*qlItStart)))
        {
            m_qlUpdateEventClasses.append((*qlItStart));
        }
    }
    setUpdateEventClassListStringList(qlUpdateEventClasses);
}

void CdmClass::setUpdateEventClassListStringList(QList<CdmClass*> qlUpdateEventClassList)
{
    QList<CdmClass*>::iterator qlItStart = qlUpdateEventClassList.begin();
    QList<CdmClass*>::iterator qlItEnd = qlUpdateEventClassList.end();
    QStringList qstrlEventClasses = getUpdateEventClassStringList();

    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        QString qstrEventClass = (*qlItStart)->GetKeyname();
        if(!qstrlEventClasses.contains(qstrEventClass))
        {
            qstrlEventClasses.append(qstrEventClass);
        }
    }

    SetUpdateEventClassStringList(qstrlEventClasses);
}

CdmClassValidator* CdmClass::CreateValidator(QString p_qstrName)
{
    CdmClassValidator* pValidator = nullptr;

    if (!HasValidator(p_qstrName))
    {
        pValidator = new CdmClassValidator();
        pValidator->SetName(p_qstrName);
        AddValidator(pValidator);
    }

    return pValidator;
}

void CdmClass::DeleteValidator(CdmClassValidator* p_pValidator)
{
    if (CHKPTR(p_pValidator) && HasValidator(p_pValidator->GetName()))
    {
        m_qmValidators.remove(p_pValidator->GetName());
        DELPTR(p_pValidator)
        SetModified();
    }
}
