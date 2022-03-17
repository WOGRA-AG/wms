// System and QT Includes

// WMS Commons Inlcudes
#include "wmsdefines.h"

// own Includes
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmModelElement.h"
#include "CumUser.h"
#include "CsaModelElement.h"

CsaModelElement::CsaModelElement(CdmModelElement* p_pElement, QObject* parent)
  : CsaLocatedElement(parent)
{
   if (CHKPTR(p_pElement))
   {
      setElement(p_pElement);
      setObjectName(p_pElement->GetKeyname());
   }
}

CsaModelElement::~CsaModelElement()
{
}


		 	
QString CsaModelElement::getKeyname()
{
    return dynamic_cast<CdmModelElement*>(getElement())->GetKeyname();
}

QString CsaModelElement::getCaption()
{
    return dynamic_cast<CdmModelElement*>(getElement())->GetCaption();
}

void CsaModelElement::setCaption(QString p_qstrCaption)
{
    dynamic_cast<CdmModelElement*>(getElement())->SetCaption(p_qstrCaption);
}

bool CsaModelElement::isDeleted()
{
    return dynamic_cast<CdmModelElement*>(getElement())->IsDeleted();
}

bool CsaModelElement::isModified()
{
    return dynamic_cast<CdmModelElement*>(getElement())->IsModified();
}

QDateTime CsaModelElement::getLastChanged()
{
    return dynamic_cast<CdmModelElement*>(getElement())->GetLastChange();
}

int CsaModelElement::getCreatorId()
{
    return dynamic_cast<CdmModelElement*>(getElement())->GetCreatorId();
}

int CsaModelElement::getModifierId()
{
    return dynamic_cast<CdmModelElement*>(getElement())->GetModifierId();
}

qint64 CsaModelElement::getId()
{
    return dynamic_cast<CdmModelElement*>(getElement())->GetId();
}

void CsaModelElement::addVariantData(QVariantMap& p_qvm)
{
   p_qvm.insert(WMS_ID, static_cast<int>(getId()));
   p_qvm.insert(WMS_KEYNAME, getKeyname());
   p_qvm.insert(WMS_CAPTION, getCaption());
}

void CsaModelElement::addMainRestLinks(QVariantList& p_rqVariantList)
{
    CdmModelElement* pElement = dynamic_cast<CdmModelElement*>(getElement());

    if (CHKPTR(pElement))
    {
        p_rqVariantList.append(generateLinkMap(WMS_CLASSMANAGER, pElement->GetClassManager()));
        p_rqVariantList.append(generateLinkMap(WMS_SCHEME, pElement->GetScheme()));
        p_rqVariantList.append(generateLinkMap(WMS_CONTAINERMANAGER, pElement->GetContainerManager()));
        p_rqVariantList.append(generateLinkMap(WMS_CONTAINERMANAGER, pElement, WMS_URI_WQL "/{?wql}"));
    }
}

QVariant CsaModelElement::generateLinkRestSection()
{
    QVariantList qvList = CsaLocatedElement::generateLinkRestSection().toList();
    addMainRestLinks(qvList);

    return qvList;
}

bool CsaModelElement::isSessionUserAdmin()
{
   bool bRet = false;
   CdmModelElement* pElement = dynamic_cast<CdmModelElement*>(getElement());

   if (CHKPTR(pElement))
   {
      CdmDataProvider* pDataprovider = pElement->GetDataProvider();

      if (CHKPTR(pDataprovider))
      {
         const CumUser* pUser = pDataprovider->GetUser();

         if (CHKPTR(pUser) && pUser->IsAdministrator())
         {
            bRet = true;
         }
      }
   }

   return bRet;
}
