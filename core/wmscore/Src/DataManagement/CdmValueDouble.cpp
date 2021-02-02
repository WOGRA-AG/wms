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
#include <qlocale.h>
#include <qdom.h>


// own Includes
#include "CwmsUtilities.h"
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueDouble.h"



/** +-=---------------------------------------------------------Sa 20. Aug 12:44:20 2005----------*
 * @method  CdmValueDouble::CdmValueDouble                             // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:44:20 2005----------*/
CdmValueDouble::CdmValueDouble(  long p_lDatabaseId,
                      long p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject )
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDouble, p_pCdmObject),
  m_dValue(0.0)
{
   // nothing to do
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:44:37 2005----------*
 * @method  CdmValueDouble::CdmValueDouble                             // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:44:37 2005----------*/
CdmValueDouble::CdmValueDouble(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElement, p_pCdmObject),
  m_dValue(0.0)
{
   XmlImportDouble(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:42:13 2012----------*
 * @method  CdmValueDouble::CdmValueDouble                   // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:42:13 2012----------*/
CdmValueDouble::CdmValueDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_dValue = p_rqvHash[WMS_VALUE].toDouble();
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:44:42 2005----------*
 * @method  CdmValueDouble::~CdmValueDouble                            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueDouble                                                     *
 *----------------last changed: --------------------------------Sa 20. Aug 12:44:42 2005----------*/
CdmValueDouble::~CdmValueDouble(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:36:11 2012-----------*
 * @method  CdmValueDouble::Deploy                           // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:36:11 2012-----------*/
void CdmValueDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_dValue = p_rqvHash[WMS_VALUE].toDouble();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:44:46 2005----------*
 * @method  CdmValueDouble::SetDefaultValue                       // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:44:46 2005----------*/
void CdmValueDouble::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_dValue);
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:39:36 2012----------*
 * @method  CdmValueDouble::SetValue                         // public, slots                     *
 * @return  void                                             //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment sets tghe value.                                                                      *
 *----------------last changed: --------------------------------Di 20. Nov 09:39:36 2012----------*/
void CdmValueDouble::SetValue(double p_dValue)
{
   if(m_dValue != p_dValue)
   {
      m_dValue = p_dValue;
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------So 18. Jun 18:46:06 2006----------*
 * @method  CdmValueDouble::SetValue                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:46:06 2006----------*/
void CdmValueDouble::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toDouble());
}


/** +-=---------------------------------------------------------Di 20. Nov 09:40:03 2012----------*
 * @method  CdmValueDouble::GetValue                         // public, const, slots              *
 * @return  double                                           //                                   *
 * @comment returns its value.                                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 09:40:03 2012----------*/
double CdmValueDouble::GetValue() const
{
   return m_dValue;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:01 2005----------*
 * @method  CdmValueDouble::IsEqual                               // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:01 2005----------*/
int CdmValueDouble::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() == m_dValue)
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

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:04 2005----------*
 * @method  CdmValueDouble::IsSmaller                             // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:04 2005----------*/
int CdmValueDouble::IsSmaller(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() > m_dValue)
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

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:07 2005----------*
 * @method  CdmValueDouble::IsSmallerEqual                        // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:07 2005----------*/
int CdmValueDouble::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() >= m_dValue)
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

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:10 2005----------*
 * @method  CdmValueDouble::IsLarger                              // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:10 2005----------*/
int CdmValueDouble::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() < m_dValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:13 2005----------*
 * @method  CdmValueDouble::IsLargerEqual                         // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:13 2005----------*/
int CdmValueDouble::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() <= m_dValue)
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

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:16 2005----------*
 * @method  CdmValueDouble::IsNotEqual                            // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:16 2005----------*/
int CdmValueDouble::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() != m_dValue)
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

/** +-=---------------------------------------------------------Sa 7. Jan 14:27:46 2006-----------*
 * @method  CdmValueDouble::CheckUnique                           // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:27:46 2006-----------*/
void CdmValueDouble::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 09:05:47 2013----------*
 * @method  CdmValueDouble::XmlExport                        // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:05:47 2013----------*/
void CdmValueDouble::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, QString::number(m_dValue));
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:23 2005----------*
 * @method  CdmValueDouble::XmlImportDouble                       // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:23 2005----------*/
void CdmValueDouble::XmlImportDouble(  QDomElement& p_rqDomElement )
{
   m_dValue = p_rqDomElement.attribute(WMS_VALUE, "").toDouble();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:26 2005----------*
 * @method  CdmValueDouble::XmlImport                             // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:26 2005----------*/
void CdmValueDouble::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportDouble(p_rqDomElement);
}


/** +-=---------------------------------------------------------So 10. Feb 09:06:01 2013----------*
 * @method  CdmValueDouble::GetDisplayString                 // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:06:01 2013----------*/
QString CdmValueDouble::GetDisplayString() const
{
   QString qstrRet;
   QLocale qlDefault;

   const CdmMember* pMember = GetMember();

   qstrRet = pMember->GetPrefix();

   if (pMember->GetDecimalCountOutput() > 0)
   {
       qstrRet += qlDefault.toString(m_dValue, 'f', pMember->GetDecimalCountOutput());
   }
   else
   {
       qstrRet += qlDefault.toString(m_dValue, 'f', 2);
   }

   qstrRet += pMember->GetSuffix();

   return qstrRet;
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:45:31 2005----------*
 * @method  CdmValueDouble::FromStringToValue                     // public                            *
 * @return  int                                              // Succcessflag                      *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method tries to convert a string to a Value.                                     *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:31 2005----------*/
int CdmValueDouble::FromStringToValue(  QString p_qstrValue )
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   m_dValue = qlDefault.toDouble(p_qstrValue, &bSuccess);

   // this is allways successfull
   if(bSuccess)
   {
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmValueConversionError);
   }

   return iRet;
}

/** +-=---------------------------------------------------------So 10. Feb 09:06:28 2013----------*
 * @method  CdmValueDouble::GetVariant                       // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:06:28 2013----------*/
QVariant CdmValueDouble::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert("Value", m_dValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:08:58 2013----------*
 * @method  CdmValueDouble::SetVariant                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:08:58 2013----------*/
void CdmValueDouble::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash["Value"].toDouble());
}

/** +-=---------------------------------------------------------So 10. Feb 09:06:36 2013----------*
 * @method  CdmValueDouble::GetValueVariant                  // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:06:36 2013----------*/
QVariant CdmValueDouble::GetValueVariant() const
{
   return QVariant(m_dValue);
}

/** +-=---------------------------------------------------------So 10. Feb 09:06:44 2013----------*
 * @method  CdmValueDouble::GetValueAsString                 // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:06:44 2013----------*/
QString CdmValueDouble::GetValueAsString() const
{
    QLocale loc;
   return loc.toString(m_dValue);
}

/** +-=---------------------------------------------------------Mo 4. Jun 17:17:17 2012-----------*
 * @method  CdmValueDouble::SetValueVariant                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 17:17:17 2012-----------*/
void CdmValueDouble::SetValueVariant(QVariant& p_rqVariant)
{
    if (CwmsUtilities::isNumberValid(p_rqVariant.toDouble()))
    {
        SetValue(p_rqVariant.toDouble());
    }
}
