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
#include <qvariant.h>
#include <qdom.h>

// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueBool.h"


/** +-=---------------------------------------------------------Sa 13. Aug 20:59:24 2005----------*
 * @method  CdmValueBool::CdmValueBool                                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // Value Keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The Constructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 20:59:24 2005----------*/
CdmValueBool::CdmValueBool(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueBool, p_pCdmObject),
  m_bValue(false)
{
   // nothing todo here :-)
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:00:13 2005----------*
 * @method  CdmValueBool::CdmValueBool                                 // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Element                       *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The constructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:00:13 2005----------*/
CdmValueBool::CdmValueBool(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValue(p_rqDomElement, p_pCdmObject),
  m_bValue(false)
{
   XmlImportBool(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:10:49 2012----------*
 * @method  CdmValueBool::CdmValueBool                       // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_qVariant                         //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:10:49 2012----------*/
CdmValueBool::CdmValueBool(QVariantMap& p_qVariant, CdmObject* p_pCdmObject)
   : CdmValue(p_qVariant, p_pCdmObject)
{
   m_bValue = p_qVariant[WMS_VALUE].toBool();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:39:58 2005----------*
 * @method  CdmValueBool::~CdmValueBool                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueBool                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:39:58 2005----------*/
CdmValueBool::~CdmValueBool(  )
{
   // nothing to do here :-)
}

/** +-=---------------------------------------------------------Mo 13. Mai 13:59:45 2013----------*
 * @method  CdmValueBool::SetVariant                         // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 13:59:45 2013----------*/
void CdmValueBool::SetVariant(QVariantMap& p_rqvHash)
{
   QVariant qValue = p_rqvHash["Value"];
   SetValue(qValue.toBool());
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:29:42 2012-----------*
 * @method  CdmValueBool::Deploy                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:29:42 2012-----------*/
void CdmValueBool::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_bValue = p_rqvHash["Value"].toBool();
}

/** +-=---------------------------------------------------------Mo 19. Nov 15:58:02 2012----------*
 * @method  CdmValueBool::SetValue                           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   bool p_bValue                                    //                                   *
 * @comment This method sets the bool value.                                                      *
 *----------------last changed: --------------------------------Mo 19. Nov 15:58:02 2012----------*/
void CdmValueBool::SetValue(bool p_bValue)
{
   if (p_bValue != m_bValue)
   {
      m_bValue = p_bValue;
      ValueChanged();
   }
}

/** +-=---------------------------------------------------------So 18. Jun 18:42:23 2006----------*
 * @method  CdmValueBool::SetValue                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:42:23 2006----------*/
void CdmValueBool::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
    p_qstrValue = p_qstrValue.simplified();
   if (p_qstrValue == "true" || 
       p_qstrValue == "1" || 
       p_qstrValue == tr("Ja"))
   {
      SetValue(true);
   }
   else
   {
      SetValue(false);
   }
}

/** +-=---------------------------------------------------------Mo 19. Nov 15:58:11 2012----------*
 * @method  CdmValueBool::GetValue                           // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment returns the bool value.                                                               *
 *----------------last changed: --------------------------------Mo 19. Nov 15:58:11 2012----------*/
bool CdmValueBool::GetValue() const
{
   return m_bValue;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:00:53 2005----------*
 * @method  CdmValueBool::SetDefaultValue                         // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Sa 13. Aug 21:00:53 2005----------*/
void CdmValueBool::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   QVariant qvVariant = p_pCdmMember->GetDefaultValue();
   m_bValue = qvVariant.toBool();
   ValueChanged();
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:01:00 2005----------*
 * @method  CdmValueBool::IsEqual                                 // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Sa 13. Aug 21:01:00 2005----------*/
int CdmValueBool::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if (p_pqVariant->toBool() == m_bValue)
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

/** +-=---------------------------------------------------------Mi 15. Sep 14:21:00 2010----------*
 * @method  CdmValueBool::IsSmaller                          // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*#p_pqVariant                            //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Mi 15. Sep 14:21:00 2010----------*/
int CdmValueBool::IsSmaller(QVariant*) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:21:10 2010----------*
 * @method  CdmValueBool::IsSmallerEqual                     // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Mi 15. Sep 14:21:10 2010----------*/
int CdmValueBool::IsSmallerEqual(QVariant* ) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:21:22 2010----------*
 * @method  CdmValueBool::IsLarger                           // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 14:21:22 2010----------*/
int CdmValueBool::IsLarger(QVariant*) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:21:33 2010----------*
 * @method  CdmValueBool::IsLargerEqual                      // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Mi 15. Sep 14:21:33 2010----------*/
int CdmValueBool::IsLargerEqual(QVariant*) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:01:15 2005----------*
 * @method  CdmValueBool::IsNotEqual                              // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant* p_pqVariant                            //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Sa 13. Aug 21:01:15 2005----------*/
int CdmValueBool::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(p_pqVariant)
   {
      if (p_pqVariant->toBool() != m_bValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 7. Jan 14:26:09 2006-----------*
 * @method  CdmValueBool::CheckUnique                             // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:26:09 2006-----------*/
void CdmValueBool::CheckUnique(  )
{
   // todo
}


/** +-=---------------------------------------------------------Sa 9. Feb 11:57:10 2013-----------*
 * @method  CdmValueBool::XmlExport                          // public, const                     *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:57:10 2013-----------*/
void CdmValueBool::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);
   p_rqdeValue.setAttribute(WMS_VALUE, ChangeBoolToString(m_bValue));
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:01:22 2005----------*
 * @method  CdmValueBool::XmlImportBool                           // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:01:22 2005----------*/
void CdmValueBool::XmlImportBool(  QDomElement& p_rqDomElement )
{
   m_bValue = ChangeStringToBool(p_rqDomElement.attribute(WMS_VALUE, ""));
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:01:25 2005----------*
 * @method  CdmValueBool::XmlImport                               // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Sa 13. Aug 21:01:25 2005----------*/
void CdmValueBool::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportBool(p_rqDomElement);
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:57:20 2013-----------*
 * @method  CdmValueBool::GetDisplayString                   // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 11:57:20 2013-----------*/
QString CdmValueBool::GetDisplayString() const
{
   QString qstrRet = tr("Nein");

   if (m_bValue)
   {
      qstrRet = tr("Ja");
   }
   
   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:01:30 2005----------*
 * @method  CdmValueBool::FromStringToValue                       // public                            *
 * @return  int                                              // Succcessflag                      *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method tries to convert a string to a Value.                                     *
 *----------------last changed: --------------------------------Sa 13. Aug 21:01:30 2005----------*/
void CdmValueBool::FromStringToValue(QString p_qstrValue)
{
   SetValue(ChangeStringToBool(p_qstrValue));
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:57:34 2013-----------*
 * @method  CdmValueBool::GetVariant                         // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------Sa 9. Feb 11:57:34 2013-----------*/
QVariant CdmValueBool::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_bValue);
   return qmVariant;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:57:43 2013-----------*
 * @method  CdmValueBool::GetValueVariant                    // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:57:43 2013-----------*/
QVariant CdmValueBool::GetValueVariant() const
{
   return QVariant(m_bValue);
}

/** +-=---------------------------------------------------------Mo 4. Jun 16:42:52 2012-----------*
 * @method  CdmValueBool::SetValueVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 16:42:52 2012-----------*/
void CdmValueBool::SetValueVariant(QVariant& p_rqVariant)
{
    if (p_rqVariant.canConvert<bool>())
    {
        SetValue(p_rqVariant.toBool());
    }
    else
    {
        FromStringToValue(p_rqVariant.toString());
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:57:52 2013-----------*
 * @method  CdmValueBool::GetValueAsString                   // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:57:52 2013-----------*/
QString CdmValueBool::GetValueAsString() const
{
   QString qstrRet = "true";
   
   if (!m_bValue)
   {
      qstrRet = "false";
   }

   return qstrRet;
}
