/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomData.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the Data Object which contains the request data and finally the result.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMDATA_H
#define CBMSCOMDATA_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QList>
#include <QString>
#include <QVariant>

// BASETOOLS Includes
#include "CwmsHttpService.h"

// Own Includes
#include "CwmsDataExchange.h"
#include "wmscom.h"

// Forwards
class CwmsErrorCollectorSession;
class CwmscomDataResult;
class CwmscomHandler;


// TypeDefs


/* 
 * This class implements the Data Object which contains the request data and finally the result.
 */
class WMSCOM_API CwmscomData : public CwmsDataExchange
{
   protected:
      QMap<QString, QList<CwmscomData*> > m_qmChilds;
      CwmscomDataResult* m_pResult;
      bool m_bLoggingActive;


   public:
    CwmscomData(CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse, CwmscomHandler* p_pHandler);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 12:16:10 2012--------*
    * @method  CwmscomData::~CwmscomData                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmscomData                                                *
    *----------------last changed: -----------------------------So 1. Apr 12:16:10 2012-----------*/
    virtual ~CwmscomData( );

    public:
   /** +-=---------------------------------------------------------So 1. Apr 10:32:10 2012--------*
    * @method  CwmscomData::SetResult                        // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomDataResult* p_pResult                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:32:10 2012-----------*/
    void SetResult(CwmscomDataResult* p_pResult);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:33:11 2012--------*
    * @method  CwmscomData::GetResult                        // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:33:11 2012-----------*/
    QString GetResult();

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:23:31 2012--------*
    * @method  CwmscomData::GetControllerName                // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:23:31 2012-----------*/
    QString GetControllerName();

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:23:45 2012--------*
    * @method  CwmscomData::GetResource                      // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:23:45 2012-----------*/
    QString GetResource();

   public:
   /** +-=---------------------------------------------------------Di 3. Apr 13:57:43 2012--------*
    * @method  CwmscomData::GetSession                       // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 3. Apr 13:57:43 2012-----------*/
    int GetSession();
    int GetLogSeverity();

   public:
   /** +-=---------------------------------------------------------Mo 9. Jul 12:12:05 2012--------*
    * @method  CwmscomData::GetStatusCode                    // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Jul 12:12:05 2012-----------*/
    EwmsHttpStatusCode GetStatusCode();
    bool IsLoggingActive();
    void DeactivateLogging();
};

#endif // CBMSCOMDATA_H
