/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
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
#include "CdmValueTime.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:03:44 2005----------*
 * @method  CdmValueTime::CdmValueTime                                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:03:44 2005----------*/
CdmValueTime::CdmValueTime(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueTime, p_pCdmObject)
{
    m_qtValue = QTime::currentTime();
}


/** +-=---------------------------------------------------------Sa 20. Aug 11:03:52 2005----------*
 * @method  CdmValueTime::CdmValueTime                                 // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:03:52 2005----------*/
CdmValueTime::CdmValueTime(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElement, p_pCdmObject)
{
   XmlImportTime(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 14:10:20 2012----------*
 * @method  CdmValueTime::CdmValueTime                       // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 14:10:20 2012----------*/
CdmValueTime::CdmValueTime(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_qtValue = p_rqvHash[WMS_VALUE].toTime();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:49:06 2005----------*
 * @method  CdmValueTime::~CdmValueTime                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueTime                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:49:06 2005----------*/
CdmValueTime::~CdmValueTime(  )
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:43:05 2012-----------*
 * @method  CdmValueTime::Deploy                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:43:05 2012-----------*/
void CdmValueTime::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qtValue = p_rqvHash[WMS_VALUE].toTime();
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:03:59 2005----------*
 * @method  CdmValueTime::SetDefaultValue                         // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 11:03:59 2005----------*/
void CdmValueTime::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_qtValue);
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 11:50:00 2012----------*
 * @method  CdmValueTime::SetValue                           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const QTime& p_rqtTime                           //                                   *
 * @comment sets the value of this Value.                                                         *
 *----------------last changed: --------------------------------Di 20. Nov 11:50:00 2012----------*/
void CdmValueTime::SetValue(const QTime& p_rqtTime)
{
   if(p_rqtTime != m_qtValue)
   {
      m_qtValue = p_rqtTime;
      ValueChanged();
   }
   else
   {
      INFO("Old and New Value are equal no changes will be done.");
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 11:50:12 2012----------*
 * @method  CdmValueTime::SetValue                           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   double p_dTime                                   //                                   *
 * @comment This method sets the time value as double.                                            *
 *----------------last changed: --------------------------------Di 20. Nov 11:50:12 2012----------*/
void CdmValueTime::SetValue(double p_dTime)
{

   m_qtValue = ChangeDoubleToTime(p_dTime);
}

/** +-=---------------------------------------------------------So 18. Jun 18:50:45 2006----------*
 * @method  CdmValueTime::SetValue                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:50:45 2006----------*/
void CdmValueTime::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(QTime::fromString(p_qstrValue));
}

/** +-=---------------------------------------------------------Di 20. Nov 11:50:20 2012----------*
 * @method  CdmValueTime::GetValue                           // public, const, slots              *
 * @return  QTime                                            //                                   *
 * @comment returns the value of this Value.                                                      *
 *----------------last changed: --------------------------------Di 20. Nov 11:50:20 2012----------*/
QTime CdmValueTime::GetValue() const
{
   return m_qtValue;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:11 2005----------*
 * @method  CdmValueTime::GetValue                                // public, const                     *
 * @return  void                                             //                                   *
 * @param   double& p_dTime                                  //                                   *
 * @comment This method sets the time value as double.                                            *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:11 2005----------*/
void CdmValueTime::GetValue(  double& p_dTime ) const
{
   p_dTime = ChangeTimeToDouble(m_qtValue);
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:14 2005----------*
 * @method  CdmValueTime::IsEqual                                 // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:14 2005----------*/
int CdmValueTime::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toTime() == m_qtValue)
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

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:17 2005----------*
 * @method  CdmValueTime::IsSmaller                               // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:17 2005----------*/
int CdmValueTime::IsSmaller(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toTime() > m_qtValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:20 2005----------*
 * @method  CdmValueTime::IsSmallerEqual                          // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:20 2005----------*/
int CdmValueTime::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toTime() >= m_qtValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:24 2005----------*
 * @method  CdmValueTime::IsLarger                                // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:24 2005----------*/
int CdmValueTime::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toTime() < m_qtValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:28 2005----------*
 * @method  CdmValueTime::IsLargerEqual                           // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:28 2005----------*/
int CdmValueTime::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toTime() <= m_qtValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:31 2005----------*
 * @method  CdmValueTime::IsNotEqual                              // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:31 2005----------*/
int CdmValueTime::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   
   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toTime() != m_qtValue )
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

/** +-=---------------------------------------------------------Sa 7. Jan 14:29:55 2006-----------*
 * @method  CdmValueTime::CheckUnique                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:29:55 2006-----------*/
void CdmValueTime::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 11:32:52 2013----------*
 * @method  CdmValueTime::GetValueAsString                   // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:32:52 2013----------*/
QString CdmValueTime::GetValueAsString() const
{

   return m_qtValue.toString(Qt::ISODate);
}

/** +-=---------------------------------------------------------So 10. Feb 11:32:58 2013----------*
 * @method  CdmValueTime::XmlExport                          // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:32:58 2013----------*/
void CdmValueTime::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, m_qtValue.toString());
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:37 2005----------*
 * @method  CdmValueTime::XmlImportTime                           // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:37 2005----------*/
void CdmValueTime::XmlImportTime(  QDomElement& p_rqDomElement )
{
   m_qtValue = QTime::fromString(p_rqDomElement.attribute(WMS_VALUE, ""));
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:04:39 2005----------*
 * @method  CdmValueTime::XmlImport                               // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Sa 20. Aug 11:04:39 2005----------*/
void CdmValueTime::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportTime(p_rqDomElement);
}

/** +-=---------------------------------------------------------So 10. Feb 11:33:08 2013----------*
 * @method  CdmValueTime::GetDisplayString                   // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 11:33:08 2013----------*/
QString CdmValueTime::GetDisplayString() const
{
   QString qstrRet;

   if (m_qtValue.isValid())
   {
      qstrRet = m_qtValue.toString(Qt::SystemLocaleShortDate);
   }
   else
   {
      qstrRet = "-";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------So 10. Feb 11:33:15 2013----------*
 * @method  CdmValueTime::GetVariant                         // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 11:33:15 2013----------*/
QVariant CdmValueTime::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_qtValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:16:13 2013----------*
 * @method  CdmValueTime::SetVariant                         // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:16:13 2013----------*/
void CdmValueTime::SetVariant(QVariantMap& p_rqvHash)
{
   QString qstrTime = p_rqvHash[WMS_VALUE].toString();
   QTime qtTime = p_rqvHash[WMS_VALUE].toTime();

   if (!qtTime.isValid())
   {
      QDateTime qdtDateTime = p_rqvHash[WMS_VALUE].toDateTime();

      if (qdtDateTime.isValid())
      {
         qtTime = qdtDateTime.time();
      }
      else
      {
         qtTime = QTime(0,0,0,0);
      }
      
   }

   SetValue(qtTime);
}

/** +-=---------------------------------------------------------So 10. Feb 11:33:24 2013----------*
 * @method  CdmValueTime::GetValueVariant                    // public, const, virtual, slots     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:33:24 2013----------*/
QVariant CdmValueTime::GetValueVariant() const
{
   return QVariant(m_qtValue);
}

/** +-=---------------------------------------------------------Di 5. Jun 08:41:26 2012-----------*
 * @method  CdmValueTime::SetValueVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 08:41:26 2012-----------*/
void CdmValueTime::SetValueVariant(QVariant& p_rqVariant)
{
   SetValue(p_rqVariant.toTime());
}
