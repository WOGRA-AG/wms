/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmJournalItem.h
 ** Started Implementation: 2012/08/29
 ** Description:
 ** 
 ** implements the item of a change on a dataobject
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMJOURNALITEM_H
#define CDMJOURNALITEM_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QDateTime>
#include <QObject>
#include <QVariant>

// Own Includes
#include "datamanager.h"

// Forwards
class CdmObject;

// TypeDefs

// enums
enum EdmChangeMode
{
   eDmChangeModeNew,
   eDmChangeModeModified,
   eDmChangeModeDeleted
};


/* 
 * This class implements the item of a change on a dataobject
 */
class WMSMANAGER_API CdmJournalItem : public QObject
{
   Q_OBJECT

   private:
      int       m_iUserId;
      int       m_iSessionId;
      QDateTime m_qdtModified;
      EdmChangeMode m_eChangeMode;
      int       m_iObjectId;
      int       m_iObjectListId;
      int       m_iMemberId;
      QString   m_qstrChanges;
      QString   m_qstrDisplayString;


   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:03:28 2012-------*
    * @method  CdmJournalItem::CdmJournalItem                // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:03:28 2012----------*/
    CdmJournalItem( );

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:03:44 2012-------*
    * @method  CdmJournalItem::CdmJournalItem                // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:03:44 2012----------*/
    CdmJournalItem( QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:14:29 2013-------*
    * @method  CdmJournalItem::GetVariant                    // public, const                     *
    * @return  QVariantMap                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:14:29 2013----------*/
    QVariantMap GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:05:31 2012-------*
    * @method  CdmJournalItem::SetUserId                     // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iUserId                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:05:31 2012----------*/
    void SetUserId(int p_iUserId);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:14:39 2013-------*
    * @method  CdmJournalItem::GetUserId                     // public, const, slots              *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:14:39 2013----------*/
int GetUserId( ) const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:06:36 2012-------*
    * @method  CdmJournalItem::SetSessionId                  // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iSessionId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:06:36 2012----------*/
    void SetSessionId(int p_iSessionId);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:14:48 2013-------*
    * @method  CdmJournalItem::GetSessionId                  // public, const, slots              *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:14:48 2013----------*/
int GetSessionId( ) const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:07:45 2012-------*
    * @method  CdmJournalItem::SetModified                   // public                            *
    * @return  void                                          //                                   *
    * @param   QDateTime p_qdModified                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:07:45 2012----------*/
    void SetModified(QDateTime p_qdModified);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:15:07 2013-------*
    * @method  CdmJournalItem::GetModified                   // public, const, slots              *
    * @return  QDateTime                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:15:07 2013----------*/
QDateTime GetModified( ) const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:09:38 2012-------*
    * @method  CdmJournalItem::SetChangeMode                 // public                            *
    * @return  void                                          //                                   *
    * @param   EdmChangeMode p_eMode                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:09:38 2012----------*/
    void SetChangeMode(EdmChangeMode p_eMode);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:15:17 2013-------*
    * @method  CdmJournalItem::GetChangeMode                 // public, const, slots              *
    * @return  EdmChangeMode                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:15:17 2013----------*/
EdmChangeMode GetChangeMode( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:15:38 2013-------*
    * @method  CdmJournalItem::GetObjectId                   // public, const, slots              *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:15:38 2013----------*/
int GetObjectId( ) const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:11:52 2012-------*
    * @method  CdmJournalItem::SetObjectId                   // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iId                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:11:52 2012----------*/
    void SetObjectId(int p_iId);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:12:37 2012-------*
    * @method  CdmJournalItem::SetObjectListId               // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iId                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:12:37 2012----------*/
    void SetObjectListId(int p_iId);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:15:48 2013-------*
    * @method  CdmJournalItem::GetObjectListId               // public, const, slots              *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:15:48 2013----------*/
int GetObjectListId( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:16:10 2013-------*
    * @method  CdmJournalItem::GetMemberId                   // public, const, slots              *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:16:10 2013----------*/
int GetMemberId( ) const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:13:58 2012-------*
    * @method  CdmJournalItem::SetMemberId                   // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iId                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:13:58 2012----------*/
    void SetMemberId(int p_iId);

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 11:14:36 2012-------*
    * @method  CdmJournalItem::SetChanges                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrChanges                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 11:14:36 2012----------*/
    void SetChanges(QString p_qstrChanges);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:16:20 2013-------*
    * @method  CdmJournalItem::GetChanges                    // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:16:20 2013----------*/
QString GetChanges( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:16:28 2013-------*
    * @method  CdmJournalItem::GetDisplayString              // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:16:28 2013----------*/
QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------Mi 29. Aug 13:33:11 2012-------*
    * @method  CdmJournalItem::SetDisplayString              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 13:33:11 2012----------*/
    void SetDisplayString(QString p_qstrValue);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:16:37 2013-------*
    * @method  CdmJournalItem::GetUserString                 // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:16:37 2013----------*/
QString GetUserString( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:15:28 2013-------*
    * @method  CdmJournalItem::GetChangeModeAsString         // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:15:28 2013----------*/
QString GetChangeModeAsString( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:17:28 2013-------*
    * @method  CdmJournalItem::GetMemberAsString             // public, const, slots              *
    * @return  QString                                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:17:28 2013----------*/
QString GetMemberAsString( CdmObject* p_pCdmObject) const;
};

#endif // CDMJOURNALITEM_H
