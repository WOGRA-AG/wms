/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsDataExchange.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the Data Object which contains the request data and finally the result.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSDATAEXCHANGE_H
#define CWMSDATAEXCHANGE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QList>
#include <QString>
#include <QVariant>

// Own Includes
#include "basetools.h"

// Forwards
class CwmsErrorCollectorSession;
class CwmsDataExchangeConfigurator;
class CwsHttpRequest;
class CwsHttpResponse;

// TypeDefs


/* 
 * This class implements the Data Object which contains the request data and finally the result.
 */
class BASETOOLS_API CwmsDataExchange
{
   protected:
      QVariantMap m_qmMembers;
      bool m_bValid;
      CwmsDataExchangeConfigurator* m_rpHandler;
      CwmsErrorCollectorSession* m_pErrorCollector;
      CwsHttpRequest* m_rpRequest;
      CwsHttpResponse* m_rpResponse;


   public:
    CwmsDataExchange(CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse, CwmsDataExchangeConfigurator* p_pHandler);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 12:16:10 2012--------*
    * @method  CwmsDataExchange::~CwmsDataExchange                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsDataExchange                                                *
    *----------------last changed: -----------------------------So 1. Apr 12:16:10 2012-----------*/
    virtual ~CwmsDataExchange( );

   protected:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:10:24 2012--------*
    * @method  CwmsDataExchange::Parse                            // protected, virtual                *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrSource                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:10:24 2012-----------*/
    virtual bool ParseBody(QString p_qstrSource);
public:
    QString Serialize();
public:
   /** +-=---------------------------------------------------------So 1. Apr 12:15:22 2012--------*
    * @method  CwmsDataExchange::IsValid                          // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 12:15:22 2012-----------*/
    bool IsValid();

   public:
   /** +-=---------------------------------------------------------Di 3. Apr 13:55:33 2012--------*
    * @method  CwmsDataExchange::GetValue                         // public                            *
    * @return  QVariant                                      //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 3. Apr 13:55:33 2012-----------*/
    QVariant GetValue(QString p_qstrKey);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:43:33 2012--------*
    * @method  CwmsDataExchange::HasValue                         // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:43:33 2012-----------*/
    bool HasValue(QString p_qstrValue);

    CwmsDataExchange(CwmsDataExchangeConfigurator *p_pHandler);

    void SetValue(QString p_qstrKey, QVariant p_rValue);
    QVariantMap GetMembers();
    CwmsDataExchange(QString p_qstrSource, CwmsDataExchangeConfigurator *p_pHandler);
    CwsHttpRequest *GetRequest() const;
    CwsHttpResponse *GetResponse() const;
private:
   /** +-=---------------------------------------------------------Fr 13. Apr 13:27:00 2012-------*
    * @method  CwmsDataExchange::ParseHeader                      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrHeader                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 13:27:00 2012----------*/
    void ParseHeader();
    int GetLogSeverity();
};

#endif // CBMSCOMDATA_H
