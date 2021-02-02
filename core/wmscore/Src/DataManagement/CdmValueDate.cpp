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
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueDate.h"


/** +-=---------------------------------------------------------Sa 13. Aug 21:48:13 2005----------*
 * @method  CdmValueDate::CdmValueDate                                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value Keyname                     *
 * @param   CdmObject* p_pCdmObject                          // parent object                     *
 * @comment The cosntructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:48:13 2005----------*/
CdmValueDate::CdmValueDate(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueDate, p_pCdmObject)
{
//   m_qdValue = QDate::currentDate();
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:48:54 2005----------*
 * @method  CdmValueDate::CdmValueDate                                 // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElment                       // XML Element                       *
 * @param   CdmObject* p_pCdmObject                          // parent object                     *
 * @comment the cosntructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:48:54 2005----------*/
CdmValueDate::CdmValueDate(  QDomElement& p_rqDomElment, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElment, p_pCdmObject)
{
   XmlImportDate(p_rqDomElment);
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:18:04 2012----------*
 * @method  CdmValueDate::CdmValueDate                       // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:18:04 2012----------*/
CdmValueDate::CdmValueDate(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_qdValue = p_rqvHash[WMS_VALUE].toDate();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:43:54 2005----------*
 * @method  CdmValueDate::~CdmValueDate                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueDate                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:43:54 2005----------*/
CdmValueDate::~CdmValueDate(  )
{
   // nothing todo
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:32:01 2012-----------*
 * @method  CdmValueDate::Deploy                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:32:01 2012-----------*/
void CdmValueDate::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qdValue = p_rqvHash[WMS_VALUE].toDate();
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:49:02 2005----------*
 * @method  CdmValueDate::SetDefaultValue                         // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Sa 13. Aug 21:49:02 2005----------*/
void CdmValueDate::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_qdValue);
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:25:37 2012----------*
 * @method  CdmValueDate::SetValue                           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const long p_lDate                               //                                   *
 * @comment Sets the date value.                                                                  *
 *----------------last changed: --------------------------------Di 20. Nov 09:25:37 2012----------*/
void CdmValueDate::SetValue(const long p_lDate)
{

   if(m_qdValue != ChangeLongToDate(p_lDate))
   {
      m_qdValue = ChangeLongToDate(p_lDate);
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:25:43 2012----------*
 * @method  CdmValueDate::SetValue                           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const QDate& p_rqdDate                           //                                   *
 * @comment Sets the date value.                                                                  *
 *----------------last changed: --------------------------------Di 20. Nov 09:25:43 2012----------*/
void CdmValueDate::SetValue(const QDate& p_rqdDate)
{
   if(m_qdValue != p_rqdDate)
   {
      m_qdValue = p_rqdDate;
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------So 18. Jun 18:44:50 2006----------*
 * @method  CdmValueDate::SetValue                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:44:50 2006----------*/
void CdmValueDate::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
   Q_UNUSED(p_qstrValue2);
   p_qstrValue = p_qstrValue.simplified();
   QDate qDate = QDate::fromString(p_qstrValue, "yyyy-MM-dd");
   if (qDate.isValid())
   {
       SetValue(qDate);
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:25:53 2012----------*
 * @method  CdmValueDate::GetValue                           // public, const, slots              *
 * @return  QDate                                            //                                   *
 * @comment returns the value date                                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:25:53 2012----------*/
QDate CdmValueDate::GetValue() const
{
   return m_qdValue;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:34:46 2013-----------*
 * @method  CdmValueDate::GetValue                           // public, const, slots              *
 * @return  void                                             //                                   *
 * @param   long& p_dValue                                   //                                   *
 * @comment This emthod returns the date value in the overgiven double reference as time_t        *
 *----------------last changed: --------------------------------Sa 9. Feb 12:34:46 2013-----------*/
void CdmValueDate::GetValue(long& p_dValue) const
{
   p_dValue = ChangeDateToLong(m_qdValue);
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:49:43 2005----------*
 * @method  CdmValueDate::IsEqual                                 // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Sa 13. Aug 21:49:43 2005----------*/
int CdmValueDate::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if ( p_pqVariant->toDate() == m_qdValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:49:46 2005----------*
 * @method  CdmValueDate::IsSmaller                               // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Sa 13. Aug 21:49:46 2005----------*/
int CdmValueDate::IsSmaller(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDate() > m_qdValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:49:49 2005----------*
 * @method  CdmValueDate::IsSmallerEqual                          // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Sa 13. Aug 21:49:49 2005----------*/
int CdmValueDate::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDate() >= m_qdValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:49:53 2005----------*
 * @method  CdmValueDate::IsLarger                                // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Sa 13. Aug 21:49:53 2005----------*/
int CdmValueDate::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDate() < m_qdValue )
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:49:57 2005----------*
 * @method  CdmValueDate::IsLargerEqual                           // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Sa 13. Aug 21:49:57 2005----------*/
int CdmValueDate::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDate() <= m_qdValue )
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:50:00 2005----------*
 * @method  CdmValueDate::IsNotEqual                              // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Sa 13. Aug 21:50:00 2005----------*/
int CdmValueDate::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDate() != m_qdValue )
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 7. Jan 14:27:20 2006-----------*
 * @method  CdmValueDate::CheckUnique                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:27:20 2006-----------*/
void CdmValueDate::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:35:09 2013-----------*
 * @method  CdmValueDate::XmlExport                          // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:35:09 2013-----------*/
void CdmValueDate::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, m_qdValue.toString());
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:50:08 2005----------*
 * @method  CdmValueDate::XmlImportDate                           // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:50:08 2005----------*/
void CdmValueDate::XmlImportDate(  QDomElement& p_rqDomElement )
{
   m_qdValue = QDate::fromString(p_rqDomElement.attribute("Value", ""));
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:50:11 2005----------*
 * @method  CdmValueDate::XmlImport                               // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Sa 13. Aug 21:50:11 2005----------*/
void CdmValueDate::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportDate(p_rqDomElement);
}


/** +-=---------------------------------------------------------Sa 9. Feb 12:35:21 2013-----------*
 * @method  CdmValueDate::GetDisplayString                   // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:35:21 2013-----------*/
QString CdmValueDate::GetDisplayString() const
{
   QString qstrRet;

   if (m_qdValue.isValid() && m_qdValue < QDate(5000,12,31))
   {
      qstrRet = m_qdValue.toString(Qt::SystemLocaleShortDate);
   }
   else
   {
      qstrRet = "-";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:35:41 2013-----------*
 * @method  CdmValueDate::GetValueAsString                   // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:35:41 2013-----------*/
QString CdmValueDate::GetValueAsString() const
{
   return m_qdValue.toString(Qt::ISODate);
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:35:48 2013-----------*
 * @method  CdmValueDate::GetVariant                         // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 12:35:48 2013-----------*/
QVariant CdmValueDate::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_qdValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:07:30 2013----------*
 * @method  CdmValueDate::SetVariant                         // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:07:30 2013----------*/
void CdmValueDate::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toDate());
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:35:56 2013-----------*
 * @method  CdmValueDate::GetValueVariant                    // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:35:56 2013-----------*/
QVariant CdmValueDate::GetValueVariant() const
{

   return QVariant(m_qdValue);
}

/** +-=---------------------------------------------------------Mo 4. Jun 16:44:54 2012-----------*
 * @method  CdmValueDate::SetValueVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 16:44:54 2012-----------*/
void CdmValueDate::SetValueVariant(QVariant& p_rqVariant)
{
   SetValue(p_rqVariant.toDate());
}
