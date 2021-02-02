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
#include "CdmValueFloat.h"


/** +-=---------------------------------------------------------Fr 19. Aug 23:31:21 2005----------*
 * @method  CdmValueFloat::CdmValueFloat                               // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // Value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The constructor of Cdmfloat                                                           *
 *----------------last changed: --------------------------------Fr 19. Aug 23:31:21 2005----------*/
CdmValueFloat::CdmValueFloat(  long p_lDatabaseId,
                    long p_lId,
                    QString p_qstrKeyname,
                    CdmObject* p_pCdmObject )
   : CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueFloat, p_pCdmObject),
  m_fValue(0.0f)
{
   // nothing to do
}


/** +-=---------------------------------------------------------Fr 19. Aug 23:32:25 2005----------*
 * @method  CdmValueFloat::CdmValueFloat                               // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // xml source                        *
 * @param   CdmObject* p_pCdmObject                          // the parent Obejct                 *
 * @comment he xml import constructor.                                                            *
 *----------------last changed: --------------------------------Fr 19. Aug 23:32:25 2005----------*/
CdmValueFloat::CdmValueFloat(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElement, p_pCdmObject),
  m_fValue(0.0f)
{
   XmlImportFloat(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:49:28 2012----------*
 * @method  CdmValueFloat::CdmValueFloat                     // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqHash                           //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:49:28 2012----------*/
CdmValueFloat::CdmValueFloat(QVariantMap& p_rqHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqHash, p_pCdmObject)
{
   m_fValue = p_rqHash[WMS_VALUE].toFloat();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:51 2005----------*
 * @method  CdmValueFloat::~CdmValueFloat                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueFloat                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:51 2005----------*/
CdmValueFloat::~CdmValueFloat(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:37:46 2012-----------*
 * @method  CdmValueFloat::Deploy                            // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:37:46 2012-----------*/
void CdmValueFloat::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_fValue = p_rqvHash[WMS_VALUE].toFloat();
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:32:34 2005----------*
 * @method  CdmValueFloat::SetDefaultValue                        // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Fr 19. Aug 23:32:34 2005----------*/
void CdmValueFloat::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if ( CHKPTR( p_pCdmMember ) )
   {
      p_pCdmMember->GetDefaultValue(m_fValue);
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 09:47:57 2012----------*
 * @method  CdmValueFloat::SetValue                          // public, slots                     *
 * @return  void                                             //                                   *
 * @param   float p_fValue                                   //                                   *
 * @comment this method sets the value.                                                           *
 *----------------last changed: --------------------------------Di 20. Nov 09:47:57 2012----------*/
void CdmValueFloat::SetValue(float p_fValue)
{
   if (m_fValue != p_fValue)
   {
      m_fValue = p_fValue;
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------So 18. Jun 18:46:22 2006----------*
 * @method  CdmValueFloat::SetValue                               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:46:22 2006----------*/
void CdmValueFloat::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toDouble());
}



/** +-=---------------------------------------------------------Di 20. Nov 09:48:12 2012----------*
 * @method  CdmValueFloat::GetValue                          // public, const, slots              *
 * @return  float                                            //                                   *
 * @comment This method returns the value.                                                        *
 *----------------last changed: --------------------------------Di 20. Nov 09:48:12 2012----------*/
float CdmValueFloat::GetValue() const
{
   return m_fValue;
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:32:54 2005----------*
 * @method  CdmValueFloat::IsEqual                                // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Fr 19. Aug 23:32:54 2005----------*/
int CdmValueFloat::IsEqual(QVariant* p_pqVariant) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDouble() == m_fValue )
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:32:57 2005----------*
 * @method  CdmValueFloat::IsSmaller                              // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Fr 19. Aug 23:32:57 2005----------*/
int CdmValueFloat::IsSmaller(QVariant* p_pqVariant) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDouble() > m_fValue)
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:33:00 2005----------*
 * @method  CdmValueFloat::IsSmallerEqual                         // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:00 2005----------*/
int CdmValueFloat::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDouble() >= m_fValue)
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:33:04 2005----------*
 * @method  CdmValueFloat::IsLarger                               // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:04 2005----------*/
int CdmValueFloat::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDouble() < m_fValue)
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:33:08 2005----------*
 * @method  CdmValueFloat::IsLargerEqual                          // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:08 2005----------*/
int CdmValueFloat::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDouble() <= m_fValue)
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:33:11 2005----------*
 * @method  CdmValueFloat::IsNotEqual                             // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:11 2005----------*/
int CdmValueFloat::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toDouble() != m_fValue)
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

/** +-=---------------------------------------------------------Sa 7. Jan 14:28:02 2006-----------*
 * @method  CdmValueFloat::CheckUnique                            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:28:02 2006-----------*/
void CdmValueFloat::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 09:10:37 2013----------*
 * @method  CdmValueFloat::XmlExport                         // public, const                     *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:10:37 2013----------*/
void CdmValueFloat::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, QString::number(m_fValue));
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:33:18 2005----------*
 * @method  CdmValueFloat::XmlImportFloat                         // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:18 2005----------*/
void CdmValueFloat::XmlImportFloat(  QDomElement& p_rqDomElement )
{
   m_fValue = p_rqDomElement.attribute(WMS_VALUE, "").toFloat();
}


/** +-=---------------------------------------------------------Fr 19. Aug 23:33:21 2005----------*
 * @method  CdmValueFloat::XmlImport                              // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:21 2005----------*/
void CdmValueFloat::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportFloat(p_rqDomElement);
}

/** +-=---------------------------------------------------------So 10. Feb 09:10:47 2013----------*
 * @method  CdmValueFloat::GetDisplayString                  // public, const                     *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:10:47 2013----------*/
QString CdmValueFloat::GetDisplayString() const
{
   QLocale qlDefault;
   return qlDefault.toString(m_fValue, 'f', 2);
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:33:34 2005----------*
 * @method  CdmValueFloat::FromStringToValue                      // public                            *
 * @return  int                                              // Succcessflag                      *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method tries to convert a string to a Value.                                     *
 *----------------last changed: --------------------------------Fr 19. Aug 23:33:34 2005----------*/
int CdmValueFloat::FromStringToValue(QString p_qstrValue)
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   float fValue = qlDefault.toFloat(p_qstrValue, &bSuccess);

   // this is allways successfull
   if(bSuccess)
   {
       SetValue(fValue);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmValueConversionError);
   }

   return iRet;
}

/** +-=---------------------------------------------------------So 10. Feb 09:11:03 2013----------*
 * @method  CdmValueFloat::GetVariant                        // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:11:03 2013----------*/
QVariant CdmValueFloat::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   double dValue = m_fValue;
   qmVariant.insert(WMS_VALUE, dValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:09:34 2013----------*
 * @method  CdmValueFloat::SetVariant                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:09:34 2013----------*/
void CdmValueFloat::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toFloat());
}

/** +-=---------------------------------------------------------So 10. Feb 09:11:11 2013----------*
 * @method  CdmValueFloat::GetValueAsString                  // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:11:11 2013----------*/
QString CdmValueFloat::GetValueAsString() const
{
   QLocale loc;
   return loc.toString(m_fValue);
}


/** +-=---------------------------------------------------------So 10. Feb 09:11:18 2013----------*
 * @method  CdmValueFloat::GetValueVariant                   // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:11:18 2013----------*/
QVariant CdmValueFloat::GetValueVariant() const
{
   return QVariant(m_fValue);
}

/** +-=---------------------------------------------------------Mo 4. Jun 17:17:49 2012-----------*
 * @method  CdmValueFloat::SetValueVariant                   // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 17:17:49 2012-----------*/
void CdmValueFloat::SetValueVariant(QVariant& p_rqVariant)
{
    bool bSuccess = false;
    float fValue = p_rqVariant.toFloat(&bSuccess);

    if (bSuccess && CwmsUtilities::isNumberValid(fValue))
    {
        SetValue(fValue);
    }
    else if (CwmsUtilities::isNumberValid(fValue))
    {
        FromStringToValue(p_rqVariant.toString());
    }
}
