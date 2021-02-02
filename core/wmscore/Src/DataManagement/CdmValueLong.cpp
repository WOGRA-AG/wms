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
#include "CdmObject.h"
#include "CdmLogging.h"
#include "CdmValueLong.h"


/** +-=---------------------------------------------------------Fr 19. Aug 23:52:07 2005----------*
 * @method  CdmValueLong::CdmValueLong                                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // Value Keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Obejct                     *
 * @comment The constructor of long value.                                                        *
 *----------------last changed: --------------------------------Fr 19. Aug 23:52:07 2005----------*/
CdmValueLong::CdmValueLong(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueLong, p_pCdmObject),
  m_lValue(0)
{
   // nothing to do
}



/** +-=---------------------------------------------------------Fr 19. Aug 23:53:33 2005----------*
 * @method  CdmValueLong::CdmValueLong                                 // protected                         *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value Keyname                     *
 * @param   EdmValue p_eDmValue                              // Value Type                        *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The constructor of value long for derrived classes like counter                       *
 *----------------last changed: --------------------------------Fr 19. Aug 23:53:33 2005----------*/
CdmValueLong::CdmValueLong(  long p_lDatabaseId,
                  long p_lId,
                  QString p_qstrKeyname,
                  EdmValueType p_eDmValue,
                  CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, p_eDmValue, p_pCdmObject),
  m_lValue(0)
{
   // nothing to do
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:53:55 2005----------*
 * @method  CdmValueLong::CdmValueLong                                 // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Source                        *
 * @param   CdmObject* p_pCdmObject                          // parent Obejct.                    *
 * @comment The XML Constructor for value long                                                    *
 *----------------last changed: --------------------------------Fr 19. Aug 23:53:55 2005----------*/
CdmValueLong::CdmValueLong(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElement, p_pCdmObject),
  m_lValue(0)
{
   XmlImportLong(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 13:36:22 2012----------*
 * @method  CdmValueLong::CdmValueLong                       // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 13:36:22 2012----------*/
CdmValueLong::CdmValueLong(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_lValue = p_rqvHash[WMS_VALUE].toInt();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:46:47 2005----------*
 * @method  CdmValueLong::~CdmValueLong                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueLong                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:46:47 2005----------*/
CdmValueLong::~CdmValueLong(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:39:51 2012-----------*
 * @method  CdmValueLong::Deploy                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:39:51 2012-----------*/
void CdmValueLong::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_lValue = p_rqvHash[WMS_VALUE].toInt();
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:54:03 2005----------*
 * @method  CdmValueLong::SetDefaultValue                         // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Fr 19. Aug 23:54:03 2005----------*/
void CdmValueLong::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_lValue);
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:54:03 2012----------*
 * @method  CdmValueLong::SetValue                           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   long p_lValue                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:54:03 2012----------*/
void CdmValueLong::SetValue(long p_lValue)
{
   if(p_lValue != m_lValue)
   {
      m_lValue = p_lValue;
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------So 18. Jun 18:47:05 2006----------*
 * @method  CdmValueLong::SetValue                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:47:05 2006----------*/
void CdmValueLong::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toInt());
}


/** +-=---------------------------------------------------------Di 20. Nov 09:54:30 2012----------*
 * @method  CdmValueLong::GetValue                           // public, const, slots              *
 * @return  long                                             //                                   *
 * @comment returns the long value.                                                               *
 *----------------last changed: --------------------------------Di 20. Nov 09:54:30 2012----------*/
long CdmValueLong::GetValue() const
{
   return m_lValue;
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:45:46 2005----------*
 * @method  CdmValueLong::IsEqual                                 // public, const, virtual            *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Sa 20. Aug 10:45:46 2005----------*/
int CdmValueLong::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() == m_lValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:45:41 2005----------*
 * @method  CdmValueLong::IsSmaller                               // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 10:45:41 2005----------*/
int CdmValueLong::IsSmaller(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() > m_lValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:45:37 2005----------*
 * @method  CdmValueLong::IsSmallerEqual                          // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Sa 20. Aug 10:45:37 2005----------*/
int CdmValueLong::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() >= m_lValue)
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:45:32 2005----------*
 * @method  CdmValueLong::IsLarger                                // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 10:45:32 2005----------*/
int CdmValueLong::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() < m_lValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:45:29 2005----------*
 * @method  CdmValueLong::IsLargerEqual                           // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Sa 20. Aug 10:45:29 2005----------*/
int CdmValueLong::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() <= m_lValue )
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:45:25 2005----------*
 * @method  CdmValueLong::IsNotEqual                              // public, const, virtual            *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Sa 20. Aug 10:45:25 2005----------*/
int CdmValueLong::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toInt() != m_lValue)
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

/** +-=---------------------------------------------------------Sa 7. Jan 14:28:31 2006-----------*
 * @method  CdmValueLong::CheckUnique                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:28:31 2006-----------*/
void CdmValueLong::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 09:18:48 2013----------*
 * @method  CdmValueLong::XmlExport                          // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:18:48 2013----------*/
void CdmValueLong::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, QString::number(m_lValue));
}


/** +-=---------------------------------------------------------Mi 15. Sep 14:06:13 2010----------*
 * @method  CdmValueLong::XmlImportLong                      // protected                         *
 * @return  void                                             //                                   *
 * @param   QDomElement&# p_rqDomElement                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 15. Sep 14:06:13 2010----------*/
void CdmValueLong::XmlImportLong(QDomElement&)
{

}

/** +-=---------------------------------------------------------Fr 19. Aug 23:54:47 2005----------*
 * @method  CdmValueLong::XmlImport                               // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Fr 19. Aug 23:54:47 2005----------*/
void CdmValueLong::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportLong(p_rqDomElement);
}

/** +-=---------------------------------------------------------So 10. Feb 09:19:00 2013----------*
 * @method  CdmValueLong::GetDisplayString                   // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:19:00 2013----------*/
QString CdmValueLong::GetDisplayString() const
{
    const CdmMember* pMember = GetMember();

    if (CHKPTR(pMember))
    {
        QString qstrDisplayConfig = pMember->GetDisplayConfig();

        if (!qstrDisplayConfig.isEmpty())
        {
            return QString::asprintf(qstrDisplayConfig.toLatin1(), m_lValue);
        }

        return QString::number(m_lValue);
    }

    // should never happen
    return QString::number(m_lValue);
}

/** +-=---------------------------------------------------------Fr 19. Aug 23:54:54 2005----------*
 * @method  CdmValueLong::FromStringToValue                       // public                            *
 * @return  int                                              // Succcessflag                      *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method tries to convert a string to a Value.                                     *
 *----------------last changed: --------------------------------Fr 19. Aug 23:54:54 2005----------*/
int CdmValueLong::FromStringToValue(QString p_qstrValue)
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   m_lValue = p_qstrValue.toLong();

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

/** +-=---------------------------------------------------------So 10. Feb 09:19:09 2013----------*
 * @method  CdmValueLong::GetVariant                         // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 09:19:09 2013----------*/
QVariant CdmValueLong::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, (int)m_lValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:10:28 2013----------*
 * @method  CdmValueLong::SetVariant                         // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:10:28 2013----------*/
void CdmValueLong::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toInt());
}

/** +-=---------------------------------------------------------So 10. Feb 09:19:18 2013----------*
 * @method  CdmValueLong::GetValueAsString                   // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:19:18 2013----------*/
QString CdmValueLong::GetValueAsString() const
{
   return QString::number(m_lValue);
}

/** +-=---------------------------------------------------------So 10. Feb 09:19:27 2013----------*
 * @method  CdmValueLong::GetValueVariant                    // public, const, virtual, slots     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:19:27 2013----------*/
QVariant CdmValueLong::GetValueVariant() const
{
   return QVariant((int) m_lValue);
}

/** +-=---------------------------------------------------------Di 5. Jun 08:35:02 2012-----------*
 * @method  CdmValueLong::SetValueVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 08:35:02 2012-----------*/
void CdmValueLong::SetValueVariant(QVariant& p_rqVariant)
{
    QString qstrValue = p_rqVariant.toString();
    QLocale qLocale;
    SetValue(qLocale.toInt(qstrValue));
}
