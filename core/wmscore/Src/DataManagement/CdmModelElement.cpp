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
#include <QUuid>
#include <QString>
#include <QDateTime>
#include <qdom.h>
#include <QVariant>

// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmModelElement.h"

#include "CumUser.h"

/** +-=---------------------------------------------------------Fr 12. Aug 00:30:46 2005----------*
 * @method  CdmModelElement::CdmModelElement                                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrCaption = ""                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 12. Aug 00:30:46 2005----------*/
CdmModelElement::CdmModelElement(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, QString p_qstrCaption )
: CdmModelElementBase(p_lDatabaseId),
   m_lId(p_lId),
   m_lModifierId(0),
   m_lCreatorId(0),
   m_qstrKeyname(p_qstrKeyname),
   m_qstrCaption(p_qstrCaption),
   m_bModified(false),
   m_bValid(true),
   m_bDeleted(false),
   m_bNew(false)

{
   if(m_lId < 0 || m_qstrKeyname.isEmpty())
   {
      INFO("ID or Keyname are missing, this object is not valid" );
      m_bValid = false;
   }

   if(m_lSchemeId < 0)
   {
      FATAL("DatabaseId is missing, this object is not valid" );
      m_bValid = false;
   }

   if (m_bValid)
   {
       SetKeyname(p_qstrKeyname);
   }
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:30:51 2005----------*
 * @method  CdmModelElement::CdmModelElement                                 // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method creates a base object with xml information                                *
 *----------------last changed: --------------------------------Fr 12. Aug 00:30:51 2005----------*/
CdmModelElement::CdmModelElement(  QDomElement& p_rqDomElement )
: CdmModelElementBase(-1),
   m_lId(-1),
   m_lModifierId(0),
   m_lCreatorId(0),
   m_bModified(false),
   m_bValid(true),
   m_bDeleted(false),
   m_bNew(false)

{
   XmlImportBase(p_rqDomElement);

   if(m_lId < 0 || m_qstrKeyname.isEmpty())
   {
      FATAL("ID or Keyname are missing, this object is not valid" );
      m_bValid = false;
   }

   if(m_lSchemeId < 0)
   {
      FATAL("DatabaseId is missing, this object is not valid" );
      m_bValid = false;
   }

   m_bNew = true;
}

/** +-=---------------------------------------------------------So 15. Apr 13:08:14 2012----------*
 * @method  CdmModelElement::CdmModelElement                                 // public                            *
 * @return                                                   //                                   *
 * @param   QVariant p_qvVariant                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 13:08:14 2012----------*/
CdmModelElement::CdmModelElement(QVariant p_qvVariant)
: CdmModelElementBase(-1),
  m_lId(-1),
  m_lModifierId(0),
  m_lCreatorId(0),
  m_bModified(false),
  m_bValid(true),
  m_bDeleted(false),
  m_bNew(true)
{
   QVariantMap qvHash = p_qvVariant.toMap();
   SetVariant(qvHash);

   if (m_bValid)
   {
       SetKeyname(m_qstrKeyname);
   }
}

CdmModelElement::CdmModelElement()
: CdmModelElementBase(-1),
  m_lId(-1),
  m_lModifierId(0),
  m_lCreatorId(0),
  m_bModified(false),
  m_bValid(true),
  m_bDeleted(false),
  m_bNew(false)
{
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:35:45 2005----------*
 * @method  CdmModelElement::~CdmModelElement                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmModelElement                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:35:45 2005----------*/
CdmModelElement::~CdmModelElement(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 14:56:50 2012-----------*
 * @method  CdmModelElement::SetVariant                      // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 14:56:50 2012-----------*/
void CdmModelElement::SetVariant(QVariantMap& p_rqvHash)
{
   SYNCHRONIZED_WRITE;

   if (p_rqvHash[WMS_ID].toInt() > 0)
   {
        m_lId = p_rqvHash[WMS_ID].toInt();
        SetModified();
   }

   if (m_qstrKeyname != p_rqvHash[WMS_KEYNAME].toString())
   {
        m_qstrKeyname = p_rqvHash[WMS_KEYNAME].toString();
        SetModified();
   }

   if (m_qstrCaption  != p_rqvHash[WMS_CAPTION].toString())
   {
        m_qstrCaption  = p_rqvHash[WMS_CAPTION].toString();
        SetModified();
   }

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
       CdmScheme* pScheme = pManager->GetCurrentScheme();

       if (CHKPTR(pScheme))
       {
        SetSchemeId(pScheme->GetId());
       }
   }
}

/** +-=---------------------------------------------------------Mo 3. Dez 14:56:57 2012-----------*
 * @method  CdmModelElement::Deploy                          // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 14:56:57 2012-----------*/
void CdmModelElement::Deploy(QVariantMap& p_rqvHash)
{
   SYNCHRONIZED_WRITE;
   if (m_qstrKeyname.isEmpty())
   {
        m_qstrKeyname = p_rqvHash[WMS_KEYNAME].toString();
   }

   m_qstrCaption  = p_rqvHash[WMS_CAPTION].toString();
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      m_lSchemeId = GetSchemeId();
   }


//   QVariantMap qvChangeInfo = p_rqvHash[WMS_CHANGEINFO].toMap();

//   m_bModified = true;
//   //m_bNew = true;
//   m_bDeleted = false;
//   m_lModifierId = GetUserId();
//   m_lCreatorId = GetUserId();
//   m_qdtLastChange = QDateTime::currentDateTime();
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:31:19 2005----------*
 * @method  CdmModelElement::SetId                           // private                           *
 * @return  void                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @comment sets the Id of this base object.                                                      *
 *----------------last changed: --------------------------------Fr 12. Aug 00:31:19 2005----------*/
void CdmModelElement::SetId(long p_lId)
{
   m_lId = p_lId;
}


/** +-=---------------------------------------------------------Mo 19. Nov 15:45:35 2012----------*
 * @method  CdmModelElement::GetId                           // public, const, slots              *
 * @return  long                                             //                                   *
 * @comment returns the Id of this base object.                                                   *
 *----------------last changed: --------------------------------Mo 19. Nov 15:45:35 2012----------*/
long CdmModelElement::GetId() const
{
   return m_lId.load();
}

/** +-=---------------------------------------------------------Fr 13. Sep 13:12:51 2013----------*
 * @method  CdmModelElement::GetKeyname                      // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment returns the Keyname of this base object.                                              *
 *----------------last changed: --------------------------------Fr 13. Sep 13:12:51 2013----------*/
QString CdmModelElement::GetKeyname() const
{
    SYNCHRONIZED_READ;
   return m_qstrKeyname;
}

QString CdmModelElement::GetOriginalKeyname() const
{
    SYNCHRONIZED_READ;
   return m_qstrOriginalKeyname;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:31:35 2005----------*
 * @method  CdmModelElement::GetLastChange                           // public, const                     *
 * @return  QDateTime                                        //                                   *
 * @comment returns the DateTime of the last change in this object.                               *
 *----------------last changed: --------------------------------Fr 12. Aug 00:31:35 2005----------*/
QDateTime CdmModelElement::GetLastChange(  ) const
{
    SYNCHRONIZED_READ;
   return m_qdtLastChange;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:45:45 2013-----------*
 * @method  CdmModelElement::GetLastChange                   // public, const                     *
 * @return  void                                             //                                   *
 * @param   double& p_dLastChange                            //                                   *
 * @comment This method returns the last change date time in a double                             *
 *----------------last changed: --------------------------------Sa 9. Feb 11:45:45 2013-----------*/
void CdmModelElement::GetLastChange(double& p_dLastChange) const
{
    SYNCHRONIZED_READ;
   p_dLastChange = ChangeDateTimeToDouble(m_qdtLastChange);
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:31:41 2005----------*
 * @method  CdmModelElement::SetLastChange                           // public                            *
 * @return  void                                             //                                   *
 * @param   QDateTime& p_qdDateTime                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 12. Aug 00:31:41 2005----------*/
void CdmModelElement::SetLastChange(  QDateTime& p_qdDateTime )
{
    SYNCHRONIZED_WRITE;
   m_qdtLastChange = p_qdDateTime;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:31:45 2005----------*
 * @method  CdmModelElement::SetLastChange                           // public                            *
 * @return  void                                             //                                   *
 * @param   double p_dLastChanged                            //                                   *
 * @comment This method sets the lastchanged date time with a double                              *
 *----------------last changed: --------------------------------Fr 12. Aug 00:31:45 2005----------*/
void CdmModelElement::SetLastChange(  double p_dLastChanged )
{
    SYNCHRONIZED_WRITE;
   m_qdtLastChange = ChangeDoubleToDateTime(p_dLastChanged);
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:09:01 2012----------*
 * @method  CdmModelElement::SetModified                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method will be called if the object has been modified.                           *
 *----------------last changed: --------------------------------Fr 17. Aug 15:09:01 2012----------*/
void CdmModelElement::SetModified()
{
   SYNCHRONIZED_WRITE;
   m_bModified = true;
   m_qdtLastChange = QDateTime::currentDateTime();
   m_lModifierId = GetUserId();
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:45:59 2013-----------*
 * @method  CdmModelElement::IsValid                         // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment This method returns if this object is a valid object or not.                          *
 *----------------last changed: --------------------------------Sa 9. Feb 11:45:59 2013-----------*/
bool CdmModelElement::IsValid() const
{
   return m_bValid.load();
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:32:23 2005----------*
 * @method  CdmModelElement::SetInvalid                              // protected                         *
 * @return  void                                             //                                   *
 * @comment This method sets this object as invalid object. This is only possibled to set from    *
 *          derived classes.                                                                      *
 *----------------last changed: --------------------------------Fr 12. Aug 00:32:23 2005----------*/
void CdmModelElement::SetInvalid(  )
{
   m_bValid = false;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:32:26 2005----------*
 * @method  CdmModelElement::SetValid                                // protected                         *
 * @return  void                                             //                                   *
 * @comment This method sets the Base Object valid.                                               *
 *----------------last changed: --------------------------------Fr 12. Aug 00:32:26 2005----------*/
void CdmModelElement::SetValid(  )
{
   m_bValid = true;
}

/** +-=---------------------------------------------------------Do 9. Mai 18:30:18 2013-----------*
 * @method  CdmModelElement::SetDeleted                      // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment This method sets this base object deleted.                                            *
 *----------------last changed: --------------------------------Do 9. Mai 18:30:18 2013-----------*/
void CdmModelElement::SetDeleted()
{
   m_bDeleted = true;
}

/** +-=---------------------------------------------------------Do 9. Mai 18:29:46 2013-----------*
 * @method  CdmModelElement::IsDeleted                       // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment This emthod returns if this base object is deleted.                                   *
 *----------------last changed: --------------------------------Do 9. Mai 18:29:46 2013-----------*/
bool CdmModelElement::IsDeleted() const
{
   return m_bDeleted;
}

/** +-=---------------------------------------------------------Do 9. Mai 18:30:03 2013-----------*
 * @method  CdmModelElement::IsModified                      // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment returns if an object is modified or not.                                              *
 *----------------last changed: --------------------------------Do 9. Mai 18:30:03 2013-----------*/
bool CdmModelElement::IsModified() const
{

   return m_bModified;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:33:00 2005----------*
 * @method  CdmModelElement::SetCreatorId                            // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment This method sets the creator of this object.                                          *
 *----------------last changed: --------------------------------Fr 12. Aug 00:33:00 2005----------*/
void CdmModelElement::SetCreatorId(  long p_lUserId )
{
   m_lCreatorId = p_lUserId;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:33:03 2005----------*
 * @method  CdmModelElement::GetCreatorId                            // public, const                     *
 * @return  long                                             //                                   *
 * @comment returns the Id of the creator or nullptr if the system has created this object.          *
 *----------------last changed: --------------------------------Fr 12. Aug 00:33:03 2005----------*/
long CdmModelElement::GetCreatorId(  ) const
{
   return m_lCreatorId.load();
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:33:06 2005----------*
 * @method  CdmModelElement::SetModifierId                           // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment Sets the Modifier Id.                                                                 *
 *----------------last changed: --------------------------------Fr 12. Aug 00:33:06 2005----------*/
void CdmModelElement::SetModifierId(  long p_lUserId )
{
   m_lModifierId = p_lUserId;
}

/** +-=---------------------------------------------------------Mo 19. Nov 15:49:09 2012----------*
 * @method  CdmModelElement::GetModifierId                           // public, const, slots              *
 * @return  long                                             //                                   *
 * @comment returns the id of the modifier or 0 for system modifier.                              *
 *----------------last changed: --------------------------------Mo 19. Nov 15:49:09 2012----------*/
long CdmModelElement::GetModifierId() const
{
   return m_lModifierId.load();
}

/** +-=---------------------------------------------------------Fr 13. Sep 13:13:07 2013----------*
 * @method  CdmModelElement::SetKeyname                      // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment sets the keyname of this baseobject.                                                  *
 *----------------last changed: --------------------------------Fr 13. Sep 13:13:07 2013----------*/
void CdmModelElement::SetKeyname(QString p_qstrKeyname)
{
    SYNCHRONIZED_WRITE;
   m_qstrOriginalKeyname = m_qstrKeyname;
   m_qstrKeyname =  p_qstrKeyname.simplified();

   m_qstrKeyname = m_qstrKeyname.replace(QRegExp("[^A-Za-z0-9_]"), "_");
   m_qstrKeyname = m_qstrKeyname.replace(":", "_");
   m_qstrKeyname = m_qstrKeyname.replace(".", "_");
   m_qstrKeyname = m_qstrKeyname.replace(" ", "_");

   if (m_qstrKeyname.length() > 100)
   {
       m_qstrKeyname = m_qstrKeyname.right(100);
   }


   if (!CheckKeyname(m_qstrKeyname))
   {
       WARNING("Keyname does not match rules RegEx: [A-Za-z][A-Za-z0-9_]*");
   }
}

/** +-=---------------------------------------------------------Mo 20. Jul 21:03:11 2009----------*
 * @method  CdmModelElement::SetNew                                  // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment This method sets the new flag on this base object.                                    *
 *----------------last changed: --------------------------------Mo 20. Jul 21:03:11 2009----------*/
void CdmModelElement::SetNew()
{
   m_bNew = true;
   m_lCreatorId = GetUserId();
}

/** +-=---------------------------------------------------------Mo 19. Nov 15:49:20 2012----------*
 * @method  CdmModelElement::IsNew                                   // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment returns if this base object is new.                                                   *
 *----------------last changed: --------------------------------Mo 19. Nov 15:49:20 2012----------*/
bool CdmModelElement::IsNew() const
{
   return m_bNew;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:33:36 2005----------*
 * @method  CdmModelElement::ResetNewModified                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method resets the new and modified value at this base object. This is needed     *
 *          for after updating this object.                                                       *
 *----------------last changed: --------------------------------Fr 12. Aug 00:33:36 2005----------*/
void CdmModelElement::ResetNewModified(  )
{
   m_bNew      = false;
   m_bModified = false;
}

/** +-=---------------------------------------------------------Mo 19. Nov 15:49:33 2012----------*
 * @method  CdmModelElement::SetCaption                              // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment This method sets the caption of this baseobject.                                      *
 *----------------last changed: --------------------------------Mo 19. Nov 15:49:33 2012----------*/
void CdmModelElement::SetCaption(QString p_qstrCaption)
{
    SYNCHRONIZED_WRITE;
   m_qstrCaption = p_qstrCaption;
   SetModified();
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:46:45 2013-----------*
 * @method  CdmModelElement::GetCaption                      // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment This method returns the caption of this object.                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:46:45 2013-----------*/
QString CdmModelElement::GetCaption() const
{
    SYNCHRONIZED_READ;
   QString qstrRet = m_qstrCaption;

   if(qstrRet.isEmpty())
   {
      qstrRet = GetKeyname();
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:47:12 2013-----------*
 * @method  CdmModelElement::ChangeDateToLong                // public, static                    *
 * @return  long                                             //                                   *
 * @param   const QDate p_qdDate                             //                                   *
 * @comment This method changes a date to a long value. This long value means the number of       *
 *          days since 1.1.1900.                                                                  *
 *----------------last changed: --------------------------------Sa 9. Feb 11:47:12 2013-----------*/
long CdmModelElement::ChangeDateToLong(const QDate p_qdDate)
{
   long lRet = 0;

   lRet = QDate(1900,1,1).daysTo(p_qdDate);

   return lRet;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:21 2005----------*
 * @method  CdmModelElement::ChangeLongToDate                        // public, static                    *
 * @return  QDate                                            //                                   *
 * @param   long p_lDate                                     //                                   *
 * @comment This method converts a long value whixh contains the number of days sind 1.1.1970 to a valid qdate.*
 *----------------last changed: --------------------------------Fr 12. Aug 00:34:21 2005----------*/
QDate CdmModelElement::ChangeLongToDate(  long p_lDate )
{
   QDate qdDate(1900,1,1);

   qdDate = qdDate.addDays(p_lDate);

   return qdDate;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:23 2005----------*
 * @method  CdmModelElement::ChangeTimeToDouble                      // public, static                    *
 * @return  double                                           //                                   *
 * @param   QTime p_qtTime                                   //                                   *
 * @comment This method changes a qtime to a double. The double is a percentage value of the complete day.*
 *----------------last changed: --------------------------------Fr 12. Aug 00:34:23 2005----------*/
double CdmModelElement::ChangeTimeToDouble(  QTime p_qtTime )
{
   double dRet =0.0;

   // it starts on msec on and adds a msec afterwards to prevent negative values.
   dRet = (QTime(0,0,0, 1).msecsTo(p_qtTime) + 1) / 8640000;

   return dRet;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:26 2005----------*
 * @method  CdmModelElement::ChangeDoubleToTime                      // public, static                    *
 * @return  QTime                                            //                                   *
 * @param   double p_dTime                                   //                                   *
 * @comment This method changes a percentage double value to a time value.                        *
 *----------------last changed: --------------------------------Fr 12. Aug 00:34:26 2005----------*/
QTime CdmModelElement::ChangeDoubleToTime(  double p_dTime )
{
   QTime qtTime(0,0,0,0);

   double dMsecs = p_dTime * 8640000;
   qtTime = qtTime.addMSecs(dMsecs);

   return qtTime;
}

/** +-=---------------------------------------------------------So 10. Feb 18:25:16 2013----------*
 * @method  CdmModelElement::ChangeDateTimeToDouble          // public, const                     *
 * @return  double                                           //                                   *
 * @param   QDateTime p_qdtDateTime                          //                                   *
 * @comment This method changes a qdatetime value to a double. It uses the definition of the      *
 *          ChangeDateToLong and ChangeTimeToDouble methods.                                      *
 *----------------last changed: --------------------------------So 10. Feb 18:25:16 2013----------*/
double CdmModelElement::ChangeDateTimeToDouble(QDateTime p_qdtDateTime) const
{
   long lDate = ChangeDateToLong(p_qdtDateTime.date());
   double dTime = ChangeTimeToDouble(p_qdtDateTime.time());

   return dTime + lDate;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:32 2005----------*
 * @method  CdmModelElement::ChangeDoubleToDateTime                  // public, static                    *
 * @return  QDateTime                                        //                                   *
 * @param   double p_dDateTime                               //                                   *
 * @comment This method changes a double value to a qdatetime value.                              *
 *----------------last changed: --------------------------------Fr 12. Aug 00:34:32 2005----------*/
QDateTime CdmModelElement::ChangeDoubleToDateTime(  double p_dDateTime )
{
   QDateTime qdtDateTime;

   long lDate = (long)p_dDateTime;
   double dTime = lDate - p_dDateTime;
   QDate qdDate = ChangeLongToDate(lDate);
   QTime qtTime = ChangeDoubleToTime(dTime);

   qdtDateTime.setDate(qdDate);
   qdtDateTime.setTime(qtTime);

   return qdtDateTime;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:42 2005----------*
* @method  CdmModelElement::ChangeBoolToString                      // public, static                    *
* @return  QString                                          //                                   *
* @param   bool p_bValue                                    //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Fr 12. Aug 00:34:42 2005----------*/
QString CdmModelElement::ChangeBoolToString(bool p_bValue)
{
   QString qstrRet = "Unknown";
   if(p_bValue)
   {
      qstrRet = "true";
   }
   else
   {
      qstrRet = "false";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:45 2005----------*
* @method  CdmModelElement::ChangeStringToBool                      // public, static                    *
* @return  bool                                             //                                   *
* @param   QString p_qstrBool                               //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Fr 12. Aug 00:34:45 2005----------*/
bool CdmModelElement::ChangeStringToBool(QString p_qstrBool)
{
   bool bRet = false;

   if(p_qstrBool == "true")
   {
      bRet =  true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:47:50 2013-----------*
 * @method  CdmModelElement::XmlExportBase                   // protected, const                  *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeBase                          //                                   *
 * @comment exports the database to a xml file.                                                   *
 *----------------last changed: --------------------------------Sa 9. Feb 11:47:50 2013-----------*/
void CdmModelElement::XmlExportBase(QDomElement& p_rqdeBase) const
{
   SYNCHRONIZED_READ;
   p_rqdeBase.setAttribute(WMS_ID, QString::number(m_lId));
   p_rqdeBase.setAttribute(WMS_KEYNAME,    m_qstrKeyname);
   p_rqdeBase.setAttribute(WMS_CAPTION,    m_qstrCaption);
   p_rqdeBase.setAttribute(WMS_LASTCHANGE, m_qdtLastChange.toString());
   p_rqdeBase.setAttribute(WMS_DELETED,    ChangeBoolToString(m_bDeleted));
   p_rqdeBase.setAttribute(WMS_MODIFIED,   ChangeBoolToString(m_bModified));
   p_rqdeBase.setAttribute(WMS_NEW,        ChangeBoolToString(m_bNew));
   p_rqdeBase.setAttribute(WMS_VALID,      ChangeBoolToString(m_bValid));
   p_rqdeBase.setAttribute(WMS_CREATORID,    QString::number(m_lCreatorId));
   p_rqdeBase.setAttribute(WMS_MODIFIERID,   QString::number(m_lModifierId));
   p_rqdeBase.setAttribute(WMS_SCHEME,       QString::number(m_lSchemeId));
   p_rqdeBase.setAttribute(WMS_URI,       GetUriInternal());
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:34:39 2005----------*
 * @method  CdmModelElement::XmlImportBase                           // protected                         *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method imports the basedata of this base object from xml to object.              *
 *----------------last changed: --------------------------------Fr 12. Aug 00:34:39 2005----------*/
void CdmModelElement::XmlImportBase(  QDomElement& p_rqDomElement )
{
    SYNCHRONIZED_WRITE;
   m_lId           = p_rqDomElement.attribute(WMS_ID, "-1").toInt();
   m_qstrKeyname   = p_rqDomElement.attribute(WMS_KEYNAME, "");
   m_qstrCaption   = p_rqDomElement.attribute(WMS_CAPTION, "");
   m_qdtLastChange = QDateTime::fromString(p_rqDomElement.attribute(WMS_LASTCHANGE, ""));
   m_bDeleted      = ChangeStringToBool(p_rqDomElement.attribute(WMS_DELETED, ""));
   m_bModified     = ChangeStringToBool(p_rqDomElement.attribute(WMS_MODIFIED, ""));
   m_bNew          = ChangeStringToBool(p_rqDomElement.attribute(WMS_NEW, ""));
   m_bValid        = ChangeStringToBool(p_rqDomElement.attribute(WMS_VALID, ""));
   m_lCreatorId    = p_rqDomElement.attribute(WMS_CREATORID, "-1").toInt();
   m_lModifierId   = p_rqDomElement.attribute(WMS_MODIFIERID, "-1").toInt();
   m_lSchemeId   = p_rqDomElement.attribute(WMS_SCHEME, "").toInt();

   m_bModified = true;
}



/** +-=---------------------------------------------------------Sa 9. Feb 11:48:08 2013-----------*
 * @method  CdmModelElement::GetInfo                         // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment returns the info to the current object.                                               *
 *----------------last changed: --------------------------------Sa 9. Feb 11:48:08 2013-----------*/
QString CdmModelElement::GetInfo() const
{
    SYNCHRONIZED_READ;
   QString qstrRet;

   qstrRet = "Base Informations:\n";
   qstrRet += "ID:           " + QString::number(GetId()) + "\n";
   qstrRet += "Uri:          " + GetUriInternal() + "\n";
   qstrRet += "Keyname:      " + m_qstrKeyname + "\n";
   qstrRet += "Caption:      " + m_qstrCaption + "\n";
   qstrRet += "Scheme:       " + QString::number(GetSchemeId()) + "\n";
   qstrRet += "CreatorId:    " + QString::number(m_lCreatorId) + "\n";
   qstrRet += "Last Changed: " + m_qdtLastChange.toString() + "\n";
   qstrRet += "Valid:        ";

   if (m_bValid.load())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }

   qstrRet += "New:          ";

   if (m_bNew.load())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }


   qstrRet += "Modified:     ";

   if (m_bModified.load())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }
   
   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:48:21 2013-----------*
 * @method  CdmModelElement::GetVariant                      // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:48:21 2013-----------*/
QVariant CdmModelElement::GetVariant() const
{
   SYNCHRONIZED_READ;
   QVariantMap qmVariant;
   QVariantMap qvChangeInfo;

   qmVariant.insert(WMS_ID,(int) m_lId);
   qmVariant.insert(WMS_KEYNAME, m_qstrKeyname);
   qmVariant.insert(WMS_DATABASEID, (int)GetSchemeId());
   qmVariant.insert(WMS_CAPTION, m_qstrCaption);
   qmVariant.insert(WMS_URI, GetUriInternal());
   return qmVariant;
}


/** +-=---------------------------------------------------------Mi 12. Sep 15:22:13 2012----------*
 * @method  CdmModelElement::GetDisplayTypeAsString                  // public, static                    *
 * @return  QString                                          //                                   *
 * @param   EdmStringDisplayType p_eType                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 15:22:13 2012----------*/
QString CdmModelElement::GetDisplayTypeAsString(EdmStringDisplayType p_eType)
{
   QString qstrRet;

   switch (p_eType)
   {
      case edmStringDisplayTypeFormatted:   
         qstrRet = tr("Formatiert");
         break;
      case edmStringDisplayTypeUnFormatted:   
         qstrRet = tr("Unformatiert");
         break;
      case edmStringDisplayTypeDirectory:
         qstrRet = tr("Verzeichnis");
         break;
      case edmStringDisplayTypeFile:
         qstrRet = tr("Datei");
         break;
      case edmStringDisplayTypeEncrypted:
         qstrRet = tr("Verschlüsselt");
         break;
      case edmStringDisplayTypeLink:
         qstrRet = tr("Link");
         break;
      case edmStringDisplayTypeJson:   
         qstrRet = tr("Json");
         break;
      case edmStringDisplayTypeXml:   
         qstrRet = tr("XML");
         break;
   }

   return qstrRet;
}

QString CdmModelElement::GetUriType() const
{
    QString qstrType;

    if (IsClass())
    {
       qstrType = WMS_URI_CLASS;
    }
    else if (IsObject())
    {
       qstrType = WMS_URI_OBJECT;
    }
    else if (IsContainer())
    {
       qstrType = WMS_URI_CONTAINER;
    }
    else if (IsValue())
    {
       qstrType = WMS_URI_VALUE;
    }
    else if (IsMember())
    {
       qstrType = WMS_URI_MEMBER;
    }
	else if (IsPackage())
	{
		qstrType = WMS_URI_PACKAGE;
	}
    else
    {
       qstrType = WMS_URI_UNKNOWN;
    }

    return qstrType;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:48:48 2013-----------*
 * @method  CdmModelElement::GetUri                          // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:48:48 2013-----------*/
QString CdmModelElement::GetUri() const
{
   QString qstrType = GetUriType();
   return CreateUri(qstrType, GetKeyname());
}


QString CdmModelElement::GetUriInternal() const
{
    QString qstrType = GetUriType();
    return CreateUriPath(qstrType, GetKeyname(), "", "");
}


QString CdmModelElement::GenerateKeyname() const
{
    SYNCHRONIZED_READ;
    return  m_qstrKeyname + QUuid::createUuid().toString()
            .remove("-")
            .remove("{")
            .remove("}");
}

bool CdmModelElement::CheckKeyname(QString p_qstrKeyname)
{
    bool bSuccess = false;
    QRegExp regex("[A-Za-z][A-Za-z0-9_]*");
    bSuccess = regex.exactMatch(p_qstrKeyname);

    if (!bSuccess)
    {
        WARNING("Keyname check failed. Keyname:  \"" + p_qstrKeyname +"\"");
    }

    return bSuccess;
}

bool CdmModelElement::IsModelElement() const
{
   return true;
}

bool CdmModelElement::HasUserDeleteAccess()
{
    bool bRet = false;

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    CumUser *pCurrentUser = const_cast<CumUser*>(pManager->GetUser());

    if(CHKPTR(pCurrentUser))
    {
        if(pCurrentUser->IsAdministrator())
        {
            bRet = true;
        }
    }

    return bRet;
}
