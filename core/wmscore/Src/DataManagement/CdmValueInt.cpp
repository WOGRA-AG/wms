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
#include <qlocale.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueInt.h"


/** +-=---------------------------------------------------------Fr 19. Aug 23:35:07 2005----------*
 * @method  CdmValueInt::CdmValueInt                                   // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The Integer constructor                                                               *
 *----------------last changed: --------------------------------Fr 19. Aug 23:35:07 2005----------*/
CdmValueInt::CdmValueInt(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueInt, p_pCdmObject),
  m_iValue(0)
{
   // nothing to do
}

/** +-=---------------------------------------------------------Di 7. Apr 22:06:00 2009-----------*
 * @method  CdmValueInt::CdmValueInt                         // public                            *
 * @return                                                   //                                   *
 * @param   EdmValue p_eDmValue                              // Valuetype.                        *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The Integer constructor                                                               *
 *----------------last changed: --------------------------------Di 7. Apr 22:06:00 2009-----------*/
CdmValueInt::CdmValueInt(EdmValueType p_eDmValue,
                         long p_lDatabaseId,
                         long p_lId,
                         QString p_qstrKeyname,
                         CdmObject* p_pCdmObject)
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, p_eDmValue, p_pCdmObject),
  m_iValue(0)
{

   // nothing to do
}


/** +-=---------------------------------------------------------Fr 19. Aug 23:35:54 2005----------*
 * @method  CdmValueInt::CdmValueInt                                   // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Source                        *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The integer constructor.                                                              *
 *----------------last changed: --------------------------------Fr 19. Aug 23:35:54 2005----------*/
CdmValueInt::CdmValueInt(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElement, p_pCdmObject),
  m_iValue(0)
{
   XmlImportInt(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 13:32:11 2012----------*
 * @method  CdmValueInt::CdmValueInt                         // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 13:32:11 2012----------*/
CdmValueInt::CdmValueInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_iValue = p_rqvHash[WMS_VALUE].toInt();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:45:59 2005----------*
 * @method  CdmValueInt::~CdmValueInt                                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueInt                                                        *
 *----------------last changed: --------------------------------Sa 20. Aug 12:45:59 2005----------*/
CdmValueInt::~CdmValueInt(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:38:18 2012-----------*
 * @method  CdmValueInt::Deploy                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:38:18 2012-----------*/
void CdmValueInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_iValue = p_rqvHash[WMS_VALUE].toInt();
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:02 2005----------*
 * @method  CdmValueInt::SetDefaultValue                          // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:02 2005----------*/
void CdmValueInt::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if ( CHKPTR( p_pCdmMember ) )
   {
      p_pCdmMember->GetDefaultValue(m_iValue);
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 09:48:36 2012----------*
 * @method  CdmValueInt::SetValue                            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iValue                                     //                                   *
 * @comment stes the value of this Value.                                                         *
 *----------------last changed: --------------------------------Di 20. Nov 09:48:36 2012----------*/
void CdmValueInt::SetValue(int p_iValue)
{
   if (m_iValue != p_iValue && !isnan(p_iValue))
   {
      m_iValue = p_iValue;
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------So 18. Jun 18:46:46 2006----------*
 * @method  CdmValueInt::SetValue                                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:46:46 2006----------*/
void CdmValueInt::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toInt());
}

/** +-=---------------------------------------------------------Di 20. Nov 09:49:01 2012----------*
 * @method  CdmValueInt::GetValue                            // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment returns the value of this Value.                                                      *
 *----------------last changed: --------------------------------Di 20. Nov 09:49:01 2012----------*/
int CdmValueInt::GetValue() const
{
   return m_iValue;
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:18 2005----------*
 * @method  CdmValueInt::IsEqual                                  // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:18 2005----------*/
int CdmValueInt::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() == m_iValue)
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:22 2005----------*
 * @method  CdmValueInt::IsSmaller                                // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:22 2005----------*/
int CdmValueInt::IsSmaller(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() > m_iValue )
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:29 2005----------*
 * @method  CdmValueInt::IsSmallerEqual                           // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:29 2005----------*/
int CdmValueInt::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() >= m_iValue )
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:33 2005----------*
 * @method  CdmValueInt::IsLarger                                 // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:33 2005----------*/
int CdmValueInt::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() < m_iValue)
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:36 2005----------*
 * @method  CdmValueInt::IsLargerEqual                            // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:36 2005----------*/
int CdmValueInt::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() <= m_iValue )
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

/** +-=---------------------------------------------------------Fr 19. Aug 23:36:40 2005----------*
 * @method  CdmValueInt::IsNotEqual                               // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Fr 19. Aug 23:36:40 2005----------*/
int CdmValueInt::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() != m_iValue )
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

/** +-=---------------------------------------------------------Sa 7. Jan 14:28:17 2006-----------*
 * @method  CdmValueInt::CheckUnique                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:28:17 2006-----------*/
void CdmValueInt::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 09:12:03 2013----------*
 * @method  CdmValueInt::XmlExport                           // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment The XML Export Method                                                                 *
 *----------------last changed: --------------------------------So 10. Feb 09:12:03 2013----------*/
void CdmValueInt::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, QString::number(m_iValue));
}


/** +-=---------------------------------------------------------Fr 19. Aug 23:37:11 2005----------*
 * @method  CdmValueInt::XmlImportInt                             // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment The import method                                                                     *
 *----------------last changed: --------------------------------Fr 19. Aug 23:37:11 2005----------*/
void CdmValueInt::XmlImportInt(  QDomElement& p_rqDomElement )
{
   m_iValue = p_rqDomElement.attribute(WMS_VALUE, "-1").toInt();
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:37:14 2005----------*
 * @method  CdmValueInt::XmlImport                                // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Fr 19. Aug 23:37:14 2005----------*/
void CdmValueInt::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportInt(p_rqDomElement);
}

/** +-=---------------------------------------------------------So 10. Feb 09:12:15 2013----------*
 * @method  CdmValueInt::GetDisplayString                    // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:12:15 2013----------*/
QString CdmValueInt::GetDisplayString() const
{
    const CdmMember* pMember = GetMember();

    if (CHKPTR(pMember))
    {
        QString qstrDisplayConfig = pMember->GetDisplayConfig();

        if (!qstrDisplayConfig.isEmpty())
        {
            return QString::asprintf(qstrDisplayConfig.toLatin1(), m_iValue);
        }

        return QString::number(m_iValue);
    }

    // should never happen
    return QString::number(m_iValue);
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:37:21 2005----------*
 * @method  CdmValueInt::FromStringToValue                        // public                            *
 * @return  int                                              // Succcessflag                      *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method tries to convert a string to a Value.                                     *
 *----------------last changed: --------------------------------Fr 19. Aug 23:37:21 2005----------*/
int CdmValueInt::FromStringToValue(  QString p_qstrValue )
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   m_iValue = qlDefault.toInt(p_qstrValue, &bSuccess);

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

/** +-=---------------------------------------------------------So 10. Feb 09:12:37 2013----------*
 * @method  CdmValueInt::GetVariant                          // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:12:37 2013----------*/
QVariant CdmValueInt::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_iValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:10:02 2013----------*
 * @method  CdmValueInt::SetVariant                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:10:02 2013----------*/
void CdmValueInt::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toInt());
}

/** +-=---------------------------------------------------------So 10. Feb 09:12:45 2013----------*
 * @method  CdmValueInt::GetValueVariant                     // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:12:45 2013----------*/
QVariant CdmValueInt::GetValueVariant() const
{
   return QVariant(m_iValue);
}

/** +-=---------------------------------------------------------So 10. Feb 09:13:05 2013----------*
 * @method  CdmValueInt::GetValueAsString                    // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:13:05 2013----------*/
QString CdmValueInt::GetValueAsString() const
{
    QLocale loc;
    return loc.toString(m_iValue);
}

/** +-=---------------------------------------------------------Mo 4. Jun 17:18:25 2012-----------*
 * @method  CdmValueInt::SetValueVariant                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 17:18:25 2012-----------*/
void CdmValueInt::SetValueVariant(QVariant& p_rqVariant)
{
    QString qstrValue = p_rqVariant.toString();
    QLocale qLocale;
    SetValue(qLocale.toInt(qstrValue));
}
