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
#include <qdatetime.h>
#include <qtimer.h>
#include <qthread.h>
#include <QUuid>

#ifndef WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif //


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmSession.h"
#include "CdmSettings.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLocatedElement.h"

QAtomicInt CdmLocatedElement::ms_iInstantCount = 0;

/** +-=---------------------------------------------------------Sa 20. Aug 12:46:17 2005----------*
 * @method  CdmLocatedElement::CdmLocatedElement                           // public                            *
 * @return  void                                             //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:46:17 2005----------*/
CdmLocatedElement::CdmLocatedElement(  )
{
   ++ms_iInstantCount;
}

/** +-=---------------------------------------------------------Di 20. Nov 14:28:39 2012----------*
 * @method  CdmLocatedElement::CdmLocatedElement                           // protected                           *
 * @return                                                   //                                   *
 * @param   const CdmLocatedElement&                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 14:28:39 2012----------*/
CdmLocatedElement::CdmLocatedElement(const CdmLocatedElement&)
    : QObject(nullptr),
      QScriptable()
{
    ++ms_iInstantCount;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:46:22 2005----------*
 * @method  CdmLocatedElement::~CdmLocatedElement                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmLocatedElement                                                    *
 *----------------last changed: --------------------------------Sa 20. Aug 12:46:22 2005----------*/
CdmLocatedElement::~CdmLocatedElement(  )
{
   --ms_iInstantCount;
}

/*
QString CdmLocatedElement::GetUuid() const
{
    SYNCHRONIZED_WRITE;
    if (m_qstrUUid.isEmpty())
    {
        const_cast<CdmLocatedElement*> (this)->m_qstrUUid = QUuid::createUuid().toString();
    }

    return m_qstrUUid;
}
*/

/** +-=---------------------------------------------------------Fr 25. Mai 15:17:16 2012----------*
 * @method  CdmLocatedElement::GetInstanceCount                     // public, static                    *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 25. Mai 15:17:16 2012----------*/
int CdmLocatedElement::GetInstanceCount()
{

   return ms_iInstantCount.load();
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:43:47 2013-----------*
 * @method  CdmLocatedElement::IsObject                      // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:43:47 2013-----------*/
bool CdmLocatedElement::IsObject() const
{
   return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:43:52 2013-----------*
 * @method  CdmLocatedElement::IsContainer                  // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:43:52 2013-----------*/
bool CdmLocatedElement::IsContainer() const
{
   return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:43:58 2013-----------*
 * @method  CdmLocatedElement::IsClass                       // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:43:58 2013-----------*/
bool CdmLocatedElement::IsClass() const
{
   return false;
}

bool CdmLocatedElement::IsPackage() const
{
   return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:44:03 2013-----------*
 * @method  CdmLocatedElement::IsValue                       // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:44:03 2013-----------*/
bool CdmLocatedElement::IsValue() const
{
   return false;
}

bool CdmLocatedElement::IsModelElement() const
{
   return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:44:07 2013-----------*
 * @method  CdmLocatedElement::IsMember                      // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:44:07 2013-----------*/
bool CdmLocatedElement::IsMember() const
{
   return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:44:13 2013-----------*
 * @method  CdmLocatedElement::IsUser                        // public, const, virtual            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:44:13 2013-----------*/
bool CdmLocatedElement::IsUser() const
{
   return false;
}

bool CdmLocatedElement::IsMethod() const
{
	return false;
}

bool CdmLocatedElement::IsScheme() const
{
    return false;
}

bool CdmLocatedElement::IsClassManager() const
{
    return false;
}

bool CdmLocatedElement::IsContainerManager() const
{
    return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:44:18 2013-----------*
 * @method  CdmLocatedElement::IsUserGroup                   // public, const, virtual            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:44:18 2013-----------*/
bool CdmLocatedElement::IsUserGroup() const
{
   return false;
}

bool CdmLocatedElement::IsDataProvider() const
{
   return false;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:44:24 2013-----------*
 * @method  CdmLocatedElement::GetUri                        // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:44:24 2013-----------*/
QString CdmLocatedElement::GetUri() const
{
   ERR("Must be implemented in derived class")
   return QString();
}

QString CdmLocatedElement::GetUriInternal() const
{
   ERR("Must be implemented in derived class")
   return QString();
}



/** +-=---------------------------------------------------------Fr 7. Dez 15:14:00 2012-----------*
 * @method  CdmLocatedElement::CreateUri                     // public, static                    *
 * @return  QString                                          //                                   *
 * @param   long p_lDbId                                     //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrValueKeyname = ""                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Dez 15:14:00 2012-----------*/
QString CdmLocatedElement::CreateUri(QString p_qstrType,
                                     QString p_qstrKeyname1,
                                     QString p_qstrKeyname2,
                                     QString p_qstrKeyname3)
{
    QString qstrUri;
    QString qstrScheme;
    qstrUri = CreateUriHost();
    QString qstrPath = "/" + CreateUriPath(p_qstrType, p_qstrKeyname1, p_qstrKeyname2,p_qstrKeyname3);
    qstrUri += qstrPath;
    return qstrUri;
}

QString CdmLocatedElement::CreateUriPath(QString p_qstrType,
                                         QString p_qstrKeyname1,
                                         QString p_qstrKeyname2,
                                         QString p_qstrKeyname3)
{
   QString qstrUri;
   QString qstrScheme;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
       CdmScheme* pScheme = pManager->GetCurrentScheme();

       if (pScheme)
       {
           qstrScheme = pScheme->GetSchemeName();
       }
       else
       {
           qstrScheme = WMS_CURRENT_SCHEME;
       }
   }

   qstrUri += p_qstrType + "/";
   qstrUri += qstrScheme + "/";

   if (!p_qstrKeyname1.isEmpty())
   {
       qstrUri += p_qstrKeyname1 + "/";

       if (!p_qstrKeyname2.isEmpty())
       {
           qstrUri += p_qstrKeyname2 + "/";

           if (!p_qstrKeyname3.isEmpty())
           {
               qstrUri += p_qstrKeyname3 + "/";
           }
       }
    }

   return qstrUri.replace("//", "/");
}

QString CdmLocatedElement::CreateUriHost()
{
    QString qstrUri;
    QString qstrHost;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    CdmSession* pSession = CdmSessionManager::GetSessionManager()->FindSession();

    if (CHKPTR(pManager) && CHKPTR(pSession))
    {
        CdmSettings* pSettings = pManager->GetSettings();

        if (CHKPTR(pSettings))
        {
            if (!pSettings->GetHost().isEmpty())
            {
                qstrHost = pSettings->GetHost();

                if (qstrHost.isEmpty())
                {
                    qstrHost = "localhost";
                }

                int iPort = pSettings->GetPort();

                if (iPort == 0)
                {
                    iPort = pSettings->getDaemonServerPort();

                    if (iPort == 0)
                    {
                        iPort = 8383;
                    }
                }

                if (iPort > 0)
                {
                    qstrHost += ":" + QString::number(pSettings->GetPort());
                }

                qstrHost += ExtendUriPath(pSettings->GetPath());
                qstrHost += ExtendUriPath(pSession->GetServerRequestPath());
            }
            else
            {
                qstrHost = WMS_URI_START_WITHOUT_HTPP;
            }
        }
    }

    return WMS_HTTP + qstrHost;
}


QString CdmLocatedElement::ExtendUriPath(QString p_qstrExtension)
{
   QString qstrHost;

   if (!p_qstrExtension.isEmpty() && p_qstrExtension != "/")
   {
      if (!p_qstrExtension.startsWith("/"))
      {
          qstrHost +=  "/";
      }

      qstrHost += p_qstrExtension;

      if (!p_qstrExtension.endsWith("/"))
      {
          qstrHost +=  "/";
      }
   }

   return qstrHost;
}




