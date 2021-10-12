/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CftlJournal.h
 ** Started Implementation: 2012/08/29
 ** Description:
 ** 
 ** implements the journal for wms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CODBCJOURNAL_H
#define CODBCJOURNAL_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes


// Forwards
class CdmValue;
class CftlDataAccess;
class CdmJournalItem;

// TypeDefs


/* 
 * This class implements the journal for wms
 */
class CftlJournal
{
protected:
   /*
   * The dataaccess
   */
   CftlDataAccess* m_rpCftlDataAccess;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 10:20:51 2012-------*
    * @method  CftlJournal::CftlJournal                    // public                            *
    * @return                                                //                                   *
    * @param   CftlDataAccess* p_pCftlDataAccess           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 10:20:51 2012----------*/
    CftlJournal( CftlDataAccess* p_pCftlDataAccess);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 10:21:10 2012-------*
    * @method  CftlJournal::~CftlJournal                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CftlJournal                                               *
    *----------------last changed: -----------------------------Mi 29. Aug 10:21:10 2012----------*/
    virtual ~CftlJournal( );

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:39:55 2012-------*
    * @method  CftlJournal::ValueModified                   // public                            *
    * @return qint64                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:39:55 2012----------*/
   qint64 ValueModified(CdmValue* p_pCdmValue);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:40:06 2012-------*
    * @method  CftlJournal::ObjectModified                  // public                            *
    * @return qint64                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:40:06 2012----------*/
   qint64 ObjectModified(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:39:46 2012-------*
    * @method  CftlJournal::ObjectListModified              // public                            *
    * @return qint64                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:39:46 2012----------*/
   qint64 ObjectListModified(CdmObjectContainer* p_pContainer);




   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 13:54:17 2012-------*
    * @method  CftlJournal::GetDatabaseModifications        // public                            *
    * @return qint64                                          //                                   *
    * @param   int p_iDatabaseId                             //                                   *
    * @param   QDate p_qdFrom                                //                                   *
    * @param   QDate p_qdTo                                  //                                   *
    * @param   QList<CdmJournalItem*>& p_rqlItems            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 13:54:17 2012----------*/
   qint64 GetDatabaseModifications(int p_iDatabaseId,
                                  QDate p_qdFrom,
                                  QDate p_qdTo,
                                  QList<CdmJournalItem*>& p_rqlItems);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 13:55:15 2012-------*
    * @method  CftlJournal::GetObjectListModifications      // public                            *
    * @return qint64                                          //                                   *
    * @param   int p_iObjectListId                           //                                   *
    * @param   QDate p_qdFrom                                //                                   *
    * @param   QDate p_qdTo                                  //                                   *
    * @param   QList<CdmJournalItem*>& p_rqlItems            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 13:55:15 2012----------*/
   qint64 GetObjectListModifications(int p_iObjectListId,
                                    QDate p_qdFrom,
                                    QDate p_qdTo,
                                    QList<CdmJournalItem*>& p_rqlItems);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 13:57:31 2012-------*
    * @method  CftlJournal::GetObjectModifications          // public                            *
    * @return qint64                                          //                                   *
    * @param   int p_iObjectId                               //                                   *
    * @param   QDate p_qdFrom                                //                                   *
    * @param   QDate p_qdTo                                  //                                   *
    * @param   QList<CdmJournalItem*>& p_rqlItems            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 13:57:31 2012----------*/
   qint64 GetObjectModifications(const CdmObject *p_pObject,
                                QDate p_qdFrom,
                                QDate p_qdTo,
                                QList<CdmJournalItem*>& p_rqlItems);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 14:22:55 2012-------*
    * @method  CftlJournal::ObjectListDeleted               // public                            *
    * @return qint64                                          //                                   *
    * @param   int p_iObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 14:22:55 2012----------*/
   qint64 ObjectListDeleted(int p_iObjectListId);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 14:26:05 2012-------*
    * @method  CftlJournal::ObjectDeleted                   // public                            *
    * @return qint64                                          //                                   *
    * @param   int p_iObjectId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 14:26:05 2012----------*/
   qint64 ObjectDeleted(int p_iObjectId);
};

#endif // CODBCJOURNAL_H
