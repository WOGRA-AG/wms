// System and QT Includes

// WMS Includes
#include "CdmLogging.h"

// BAsetools includes
#include "CwmsbtMailMessage.h"

// own Includes
#include "CwmsSmtpManager.h"
#include "CwmsSmtpConfiguration.h"
#include "CwmsScriptableMailer.h"


/** +-=---------------------------------------------------------Fr 9. Nov 10:59:32 2012-----------*
 * @method  CwmsScriptableMailer::CwmsScriptableMailer       // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 9. Nov 10:59:32 2012-----------*/
CwmsScriptableMailer::CwmsScriptableMailer()
{
}

/** +-=---------------------------------------------------------Fr 9. Nov 10:59:40 2012-----------*
 * @method  CwmsScriptableMailer::~CwmsScriptableMailer      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsScriptableMailer                                          *
 *----------------last changed: --------------------------------Fr 9. Nov 10:59:40 2012-----------*/
CwmsScriptableMailer::~CwmsScriptableMailer()
{
}

/** +-=---------------------------------------------------------Di 27. Nov 16:28:49 2012----------*
 * @method  CwmsScriptableMailer::CreateMailObject           // public                            *
 * @return  QObject*                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:28:49 2012----------*/
QObject* CwmsScriptableMailer::createMailObject()
{
   CwmsbtMailMessage* pMail = nullptr;
   CwmsSmtpManager cManager;
   CwmsSmtpConfiguration* pConfig = cManager.GetSmtpConfiguration();

   if (CHKPTR(pConfig) && pConfig->IsValid())
   {
      // pConfig will be destroyed bei MailMessage
      pMail = new CwmsbtMailMessage(pConfig);
      addObjectForGarbageCollection(pMail);
   }

   return pMail;
}
