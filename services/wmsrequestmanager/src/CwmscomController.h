/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomController.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the base controller for all controller impls
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CwmscomController_H
#define CwmscomController_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QMap>

// Own Includes
#include "IwmsWebService.h"
#include "wmscom.h"

// Forwards
class CwmscomResourceBase;
class CwmscomHandler;
class CwmscomData;
class IwmsSerializer;
class IwmsParser;


// TypeDefs


/* 
 * This class implements the base controller for all controller impls
 */
class WMSCOM_API CwmscomController
{
   private:
      QString m_qstrControllerName;
      QMap<QString, IwmsWebService*> m_qmResources;
      CwmscomHandler* m_rpCbmsHandler;


   public:

    CwmscomController( QString p_qstrName, CwmscomHandler* p_pCbmsHandler);
    virtual ~CwmscomController( );
    QString GetName();
    void AddResource(QString p_qstrResource, IwmsWebService* p_pResource);
    QList<QString> GetResources();
    void Execute(CwmscomData* p_pCwmscomData);
    IwmsWebService* GetResource(QString p_qstrName);
    IwmsSerializer* GetSerializer();
    IwmsParser* GetParser();
    QString GetDescription(QString p_qstrResource);
};

#endif // CwmscomController_H
