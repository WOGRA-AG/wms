/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMERRORADAPTOR_H
#define CDMERRORADAPTOR_H

// System and QT Includes
#include <QMap>
#include <QStringList>

// WMS COmmons Includes
#include "CwmsSynchronizable.h"
// Own Includes
#include "datamanager.h"
#include "CdmLogEntry.h"
#include "CdmLogging.h"



// forwards
class QDateTime;
class QTime;



class WMSMANAGER_API CdmLoggingAdaptor : public CwmsSynchronizable
{
    private:
        QMap<EdmErrorSeverity,QStringList*> m_qmRelevanceClasses;
    public:
    virtual ~CdmLoggingAdaptor();
   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:18:56 2007--------*
    * @method  CdmErrorAdaptor::AddError                     // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:18:56 2007-----------*/
    virtual void AddError(CdmLogEntry& p_Entry)= 0;

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:19:06 2007--------*
    * @method  CdmErrorAdaptor::AddInfo                      // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:19:06 2007-----------*/
    virtual void AddInfo(CdmLogEntry& p_Entry)= 0;

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:19:19 2007--------*
    * @method  CdmErrorAdaptor::AddWarning                   // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:19:19 2007-----------*/
    virtual void AddWarning(CdmLogEntry& p_Entry)= 0;

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 21:19:29 2007--------*
    * @method  CdmErrorAdaptor::AddFatal                     // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   QTime p_qdtTimestamp                          //                                   *
    * @param   QString p_qstrModule                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment Adds an error message to the adaptor must be reimplemented by derived class.       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 21:19:29 2007-----------*/
    virtual void AddFatal(CdmLogEntry& p_Entry)= 0;

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 19:54:08 2007--------*
    * @method  CdmErrorAdaptor::AddEvent                     // public                            *
    * @return  void                                          //                                   *
    * @param   EdmErrorSeverity p_eDmErrorSeverity           //                                   *
    * @param   QString p_qstrErrorModule                     //                                   *
    * @param   QString p_qstrEventText                       //                                   *
    * @param   int p_iLine                                   //                                   *
    * @comment This method adds a error event in the queue.                                       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 19:54:08 2007-----------*/
    void AddEvent(CdmLogEntry& p_Entry);

   public:
   /** +-=---------------------------------------------------------Mo 2. Jul 20:08:50 2007--------*
    * @method  CdmErrorAdaptor::AddErrorCode                 // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   QDateTime p_qdtTimeStamp                      //                                   *
    * @param   int p_iCode                                   //                                   *
    * @comment This method adds an error code to the adaptor.                                     *
    *----------------last changed: Wolfgang Graßhof-------------Mo 2. Jul 20:08:50 2007-----------*/
    virtual void AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode)= 0;

   public:
   /** +-=---------------------------------------------------------Sa 7. Jul 17:44:29 2007--------*
    * @method  CdmErrorAdaptor::GetDataAccessCallCounter     // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jul 17:44:29 2007-----------*/
    int GetDataAccessCallCounter();
    void AddLoggingRelevance(EdmErrorSeverity p_eSeverity, QString p_qstrPattern);
    void RemoveLoggingRelevance(EdmErrorSeverity p_eSeverity, QString p_qstrPattern);
    bool MatchesPatterns(CdmLogEntry& p_Entry);
};

#endif //
