/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomHandler.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** IMplements the handler for incoming requests
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMHANDLER_H
#define CBMSCOMHANDLER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QString>

// WMS Commons Includes
#include "IwmsHttpRequestHandler.h"

// BASETOOLS Includes
#include "CwmsDataExchangeConfigurator.h"
#include "CwmsHttpService.h"
// Own Includes
#include "wmscom.h"

// Forwards
class CwmscomData;
class CwmscomController;
class IwmscomParser;
class IwmscomSerializer;

// TypeDefs


/* 
 * This class implements the handler for incoming requests
 */
class WMSCOM_API CwmscomHandler : public CwmsDataExchangeConfigurator, public IwmsHttpRequestHandler
{
   private:
      static CwmscomHandler* ms_pCommandHandler;
      QMap<QString, CwmscomController*> m_qmController;
      QString m_qstrSystemUserLogin;
      QString m_qstrSystemUserPassword;

      void CleanupCachedData();
      
public:
    CwmscomHandler( );
    virtual ~CwmscomHandler( );
    virtual bool HandleRequest(CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse);
    void AddController(QString p_qstrName, CwmscomController* p_pController);
    CwmscomController* GetController(QString m_qstrControllerName);
    QString GetDescription(QString p_qstrController, QString p_qstrResource);
    QString GetSystemUserPassword() const;
    void SetSystemUserPassword(const QString &qstrSystemUserPassword);
    QString GetSystemUserLogin() const;
    void SetSystemUserLogin(const QString &qstrSystemUserLogin);
    static CwmscomHandler *CreateOrGetCommandHandler();
    virtual void Init();
};

#endif // CBMSCOMHANDLER_H
