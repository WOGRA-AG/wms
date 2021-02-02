/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <QScriptEngine>
#include <QRegularExpression>
#include <QVariantMap>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"

// own Includes
#include "CsaManager.h"
#include "CsaContainerManager.h"
#include "CsaScheme.h"
#include "CsaClassManager.h"
#include "CsaFactory.h"
#include "CsaLocatedElement.h"
#include "CdmLocatedElement.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"

CsaLocatedElement::CsaLocatedElement(QObject* parent)
    : QObject(parent),
      IsaLocatedElement(),
      m_rpFactory(nullptr)
{
}

CsaLocatedElement::~CsaLocatedElement()
{

}

QObject* CsaLocatedElement::getManager()
{
   if (CHKPTR(m_rpFactory))
   {
      return m_rpFactory->getManager();
   }

   return nullptr;
}

QObject* CsaLocatedElement::getContainerManager()
{
   if (CHKPTR(m_rpFactory))
   {
      return m_rpFactory->getContainerManager();
   }

   return nullptr;
}

QObject* CsaLocatedElement::getClassManager()
{
   if (CHKPTR(m_rpFactory))
   {
      return m_rpFactory->getClassManager();
   }

   return nullptr;
}

QObject* CsaLocatedElement::getScheme()
{
   if (CHKPTR(m_rpFactory))
   {
      return m_rpFactory->getScheme();
   }

   return nullptr;
}

CsaFactory* CsaLocatedElement::getFactory()
{
   return m_rpFactory;
}
		
IdmExecutorEngine* CsaLocatedElement::getEngine()
{
   IdmExecutorEngine* pEngine = nullptr;

   if (CHKPTR(m_rpFactory))
   {
      pEngine = m_rpFactory->getEngine();
   }

   return pEngine;
}

void CsaLocatedElement::setFactory(CsaFactory* p_pFactory)
{
   m_rpFactory = p_pFactory;
   setParent(p_pFactory);
}

QString CsaLocatedElement::getUri() const
{
    QString qstrUri;

    CdmLocatedElement* pElement = const_cast<CsaLocatedElement*> (this)->getElement();

    if (CHKPTR(pElement))
    {
        qstrUri = pElement->GetUri();
    }

    return qstrUri;
}

QString CsaLocatedElement::getUriInternal() const
{
//   QString qstrUri;

//   CdmLocatedElement* pElement = const_cast<CsaLocatedElement*> (this)->getElement();

//   if (CHKPTR(pElement))
//   {
//       qstrUri = pElement->GetUriInternal();
//   }

//   return qstrUri;
    return m_qstrUriInternal;
}

bool CsaLocatedElement::isObject()
{
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      return pElement->IsObject();
   }

   return false;
}

bool CsaLocatedElement::isContainer()
{
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      return pElement->IsContainer();
   }

   return false;
}

bool CsaLocatedElement::isClass()
{
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      return pElement->IsClass();
   }

   return false;
}

bool CsaLocatedElement::isMember()
{
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      return pElement->IsMember();
   }

   return false;
}

bool CsaLocatedElement::isValue()
{
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      return pElement->IsValue();
   }

   return false;
}

bool CsaLocatedElement::isModelElement()
{
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      return pElement->IsModelElement();
   }

   return false;
}

bool CsaLocatedElement::isReference()
{
   return false;
}

CdmLocatedElement* CsaLocatedElement::getElement()
{
   CdmLocatedElement* pElement = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      if (!getUriInternal().isEmpty())
      {
          QString qstrUri = getUriInternal();
         pElement = dynamic_cast<CdmLocatedElement*>(pManager->GetUriObject(qstrUri));
      }
      else
      {
         ERR("URI String for this simple api located element is empty.")
      }
   }

   return pElement;
}

void CsaLocatedElement::setElement(CdmLocatedElement* p_pElement)
{
   if (p_pElement)
   {
      m_qstrUriInternal = p_pElement->GetUriInternal();
   }
}

void CsaLocatedElement::setElement(QString p_qstrUri)
{
   m_qstrUriInternal = p_qstrUri;
}

QVariant CsaLocatedElement::generateLinkRestSection()
{
   QVariantList qvList;
   CdmLocatedElement* pElement = getElement();

   if (CHKPTR(pElement))
   {
      qvList.append(generateLinkMap(WMS_SELF, pElement));
      qvList.append(generateLinkMap(WMS_DETAIL, pElement));
   }

   return qvList;
}

QVariant CsaLocatedElement::generateLinkMap(QString qstrLinkName, const CdmLocatedElement* p_pElement)
{
   return generateLinkMap(qstrLinkName, p_pElement->GetUri());
}

QVariant CsaLocatedElement::generateLinkMap(QString qstrLinkName, const CdmLocatedElement* p_pElement, QString p_qstrLink)
{
   return generateLinkMap(qstrLinkName, p_pElement->GetUri() + p_qstrLink);
}

QVariant CsaLocatedElement::generateLinkMap(QString qstrLinkName, QString qstrLink)
{
   QVariantMap qvm;
   qvm.insert(WMS_REL, qstrLinkName);
   CwmsUtilities::OptimizeUrl(qstrLink);
   qvm.insert(WMS_HREF, qstrLink);
   return qvm;
}


