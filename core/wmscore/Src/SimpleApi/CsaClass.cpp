// System and QT Includes

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsTimeMeassurement.h"
// own Includes
#include "CdmObject.h"
#include "CdmClassMethod.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CsaFunction.h"
#include "CsaMember.h"
#include "CsaFactory.h"
#include "CsaClass.h"

CsaClass::CsaClass(CdmClass* p_pClass)
   : CsaModelElement(p_pClass)
{
   addStaticFunctionsToClass();
}

CsaClass::~CsaClass()
{
    QMapIterator<QString, CsaFunction*> qmIt(m_qmFunctions);

    while(qmIt.hasNext())
    {
        qmIt.next();
        CsaFunction* pValue = qmIt.value();
        DELPTR(pValue);
    }

   m_qmFunctions.clear();
}

QObject* CsaClass::findMember(QString p_qstrKeyname)
{
   return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(const_cast<CdmMember*>(getInternals()->FindMember(p_qstrKeyname)));
}

QVariantList CsaClass::getMembers()
{
   QVariantList qlMembers;
   QMap<qint64, CdmMember*> qmMembers;
   getInternals()->GetMemberMap(qmMembers);

   QMap<qint64, CdmMember*>::iterator qIt = qmMembers.begin();
   QMap<qint64, CdmMember*>::iterator qItEnd = qmMembers.end();

   for (; qIt != qItEnd; ++qIt)
   {
      CsaLocatedElement* pElement = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(const_cast<CdmMember*>(qIt.value()));
      if (pElement)
      {
         qlMembers.append(QVariant::fromValue(pElement));
      }
   }

   return qlMembers;
}

QVariantList CsaClass::getBaseClasses()
{
   QVariantList qlBaseClasses;
   QMap<qint64,qint64> qmBaseClasses = getInternals()->GetBaseClasses();

   QMap<qint64,qint64>::iterator qIt = qmBaseClasses.begin();
   QMap<qint64,qint64>::iterator qItEnd = qmBaseClasses.end();

   for (; qIt != qItEnd; ++qIt)
   {
      CdmClassManager* pClassManager = getInternals()->GetClassManager();
      CdmClass* pClass = pClassManager->FindClassById(qIt.key());
      CsaLocatedElement* pElement = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pClass);

      if (pElement)
      {
         qlBaseClasses.append(QVariant::fromValue(pElement));
      }

   }

   return qlBaseClasses;
}

bool CsaClass::isTypeOf(QObject *p_pClass)
{
    CsaClass* pClass = dynamic_cast<CsaClass*>(p_pClass);

    if (CHKPTR(pClass))
    {
       return getInternals()->IsInherited(dynamic_cast<CsaClass*>(p_pClass)->getInternals());
    }

    return false;
}

bool CsaClass::isImmutable()
{
   return getInternals()->IsImmutable();
}

bool CsaClass::isSingleton()
{
   return getInternals()->IsImmutable();
}

QString CsaClass::getComment()
{
   return getInternals()->GetComment();
}

QString CsaClass::getCaptionMember()
{
   const CdmMember* pMember = getInternals()->GetCaptionMember();

   if (pMember)
   {
      return pMember->GetKeyname();
   }

   return "";
}

QObject* CsaClass::getSingletonObject()
{
   CdmObject* pObject = getInternals()->GetSingletonObject();

   if (pObject)
   {
      return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pObject);
   }

   return nullptr;
}


CdmClass* CsaClass::getInternals()
{
   return static_cast<CdmClass*>(getElement());
}

void CsaClass::addStaticFunctionsToClass()
{
   CdmClass* pClass = getInternals();
   QMap<QString, CdmClassMethod*> qmMethods = pClass->GetAllMethods();
   QMapIterator<QString, CdmClassMethod*> qmIt(qmMethods);

   while (qmIt.hasNext())
   {
      qmIt.next();
      CdmClassMethod* pMethod = qmIt.value();

      if (CHKPTR(pMethod) && pMethod->IsStatic() && pMethod->GetAccess() == eDmMemberAccessPublic)
      {
         QVariant qvMethod;
         CsaFunction* pFunction = new CsaFunction(this, qmIt.key());
         qvMethod.setValue(pFunction);
         m_qmFunctions.insert(pMethod->GetMethodName(), pFunction);
         setProperty(qmIt.key().toUtf8(), qvMethod);
      }
   }
}


void CsaClass::addMembersToVariant(CdmClass* pClass, QVariantMap& qvm)
{
    CwmsTimeMeassurement cTime(true, "addMembersToVariant");
   QMap<qint64, CdmMember*> qmMembers = pClass->GetClassMemberMap();
   QList<CdmMember*> qlMembers =  qmMembers.values();
   QVariantList qvlMembers;
   cTime.finishedTask("Get MemberMap");

   for (int iPos = 0; iPos < qlMembers.count(); ++iPos)
   {
      CdmMember* pMember = qlMembers[iPos];
      if ((pMember->GetAccessMode() == eDmMemberAccessPublic ||
           pMember->GetAccessMode() == eDmMemberAccessProtected) &&
          pMember->GetRights().HasCurrentUserReadAccess())
      {
         CsaMember* pMember = dynamic_cast<CsaMember*> (dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(qlMembers[iPos]));
         cTime.finishedTask("Created Member Script Object " + QString::number(iPos));

         if (pMember)
         {
            qvlMembers.append(pMember->getRoughVariant());
            cTime.finishedTask("Added Memberdata zu Variant " + QString::number(iPos));
         }
      }
   }

   qvm.insert(WMS_MEMBER, qvlMembers);
   cTime.finishedTask("Insert Members to Map");
}

void CsaClass::addBaseClassesToVariant(CdmClass* pClass, CdmClassManager* pClassManager, QVariantMap& qvm)
{
   QMap<qint64,qint64> qmBaseClasses = pClass->GetBaseClasses();
   QVariantList qvlBaseClasses;
   QList<qint64> qlBaseClassIds =  qmBaseClasses.values();

   for (int iPos = 0; iPos < qlBaseClassIds.count(); ++iPos)
   {
      CdmClass* pBaseClass = pClassManager->FindClassById(qlBaseClassIds[iPos])        ;

      if (CHKPTR(pBaseClass))
      {
         CsaClass* pClass = dynamic_cast<CsaClass*> (dynamic_cast<CsaFactory*> (dynamic_cast<CsaFactory*> (getFactory()))->createScriptObject(pBaseClass));
         qvlBaseClasses.append(pClass->getRoughVariant());
      }
   }

   qvm.insert(WMS_BASECLASSES, qvlBaseClasses);
}

CsaFunction* CsaClass::getFunction(QString p_qstrName)
{
    if (m_qmFunctions.contains(p_qstrName))
    {
        return m_qmFunctions[p_qstrName];
    }

    return nullptr;
}

void CsaClass::addFunctionsToVariant(QVariantMap& qvm)
{
    QVariantList qvlMethods;

    QMapIterator<QString, CsaFunction*> qmIt(m_qmFunctions);

    while(qmIt.hasNext())
    {
        qmIt.next();
        CsaFunction* pFunction = qmIt.value();
        if (CHKPTR(pFunction))
        {
            qvlMethods.append(pFunction->getRoughVariant());
        }
    }

    qvm.insert(WMS_METHODS, qvlMethods);
}

QVariant CsaClass::getRoughVariant()
{
   QVariantMap qvm;
   addVariantData(qvm);
   qvm.insert(WMS_KEYNAME, getInternals()->GetFullQualifiedName());
   qvm.insert(WMS_URI, getUri());
   return qvm;
}

QVariant CsaClass::getDetailedVariant()
{
    CwmsTimeMeassurement cTime(true, "getDetailedVariant");
   QVariantMap qvm = getRoughVariant().toMap();
   cTime.finishedTask("Get Rough Data");
   CdmClass* pClass = getInternals();
   cTime.finishedTask("Get Class");

   if (CHKPTR(pClass))
   {
      CdmClassManager* pClassManager = pClass->GetClassManager();

      if (CHKPTR(pClassManager))
      {
          cTime.finishedTask("Get ClassManager");
         getRoughVariant();
         cTime.finishedTask("Get Rough Variants");
         qvm.insert(WMS_CAPTIONMEMBER, getCaptionMember());
         qvm.insert(WMS_COMMENT, getComment());
         qvm.insert(WMS_IMMUTABLE, isImmutable());
         qvm.insert(WMS_SINGLETON, isSingleton());
         cTime.finishedTask("Insert furhter class data");

         addBaseClassesToVariant(pClass, pClassManager, qvm);
         cTime.finishedTask("Added Baseclasses");
         addMembersToVariant(pClass, qvm);
         cTime.finishedTask("Added Members");
         addFunctionsToVariant(qvm);
         cTime.finishedTask("Added Functions");
      }
   }

   return qvm;
}

