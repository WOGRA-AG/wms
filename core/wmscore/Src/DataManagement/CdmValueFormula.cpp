/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueFormula.cpp
 ** Started Implementation: 2009/04/03
 ** Description:
 ** 
 ** implements the formular value member
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QString>
#include <QDateTime>
#include <QScriptEngine>


// Own Includes
#include "wmsdefines.h"
#include "CdmExecutor.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueFormula.h"
#include "CdmValueContainerRef.h"

/** +-=---------------------------------------------------------Fr 3. Apr 17:07:02 2009-----------*
 * @method  CdmValueFormula::CdmValueFormula                 // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 3. Apr 17:07:02 2009-----------*/
CdmValueFormula::CdmValueFormula(long p_lDatabaseId,
                                 long p_lId,
                                 QString p_qstrKeyname,
                                 CdmObject* p_pCdmObject)
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueFormula, p_pCdmObject)
{
}


/** +-=---------------------------------------------------------Fr 3. Apr 17:08:15 2009-----------*
 * @method  CdmValueFormula::~CdmValueFormula                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueFormula                                               *
 *----------------last changed: --------------------------------Fr 3. Apr 17:08:15 2009-----------*/
CdmValueFormula::~CdmValueFormula()
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mi 15. Sep 13:58:45 2010----------*
 * @method  CdmValueFormula::SetDefaultValue                 // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember*#p_pCdmMember                    //                                   *
 * @comment This method sets the default value. Does nothing for the formular vlaue. this         *
 *          method is just for keeping the interface alive.                                       *
 *----------------last changed: --------------------------------Mi 15. Sep 13:58:45 2010----------*/
void CdmValueFormula::SetDefaultValue(const CdmMember*)
{
   // does nothing
}

/** +-=---------------------------------------------------------So 10. Feb 18:01:49 2013----------*
 * @method  CdmValueFormula::GetValueAsString                // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment returns the value of the formula as string.                                           *
 *----------------last changed: --------------------------------So 10. Feb 18:01:49 2013----------*/
QString CdmValueFormula::GetValueAsString() const
{
   QString qstrResult;
   QVariant qScriptValue = Evaluate();

   if (qScriptValue.canConvert(QMetaType::Double))
   {
      QLocale qLocale;
      bool bOk = false;
      qstrResult = qLocale.toString(qScriptValue.toDouble(&bOk));

      if (!bOk)
      {
        qstrResult = qScriptValue.toString();
      }
   }
   else
   {
      qstrResult = qScriptValue.toString();         
   }
   
   return qstrResult;
}


/** +-=---------------------------------------------------------Di 20. Nov 11:58:01 2012----------*
 * @method  CdmValueFormula::GetValueAsInt                   // public, slots                     *
 * @return  int                                              //                                   *
 * @comment returns the value as int.                                                             *
 *----------------last changed: --------------------------------Di 20. Nov 11:58:01 2012----------*/
int CdmValueFormula::GetValueAsInt()
{
   int iValue = 0;
   QVariant qScriptValue = Evaluate();
   iValue = qScriptValue.toInt();
   return iValue;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:58:11 2012----------*
 * @method  CdmValueFormula::GetValueAsDouble                // public, slots                     *
 * @return  double                                           //                                   *
 * @comment returns the value as double.                                                          *
 *----------------last changed: --------------------------------Di 20. Nov 11:58:11 2012----------*/
double CdmValueFormula::GetValueAsDouble()
{
   double dValue = 0.0;
   QVariant qScriptValue = Evaluate();
   dValue = qScriptValue.toDouble();
   return dValue;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:58:21 2012----------*
 * @method  CdmValueFormula::GetValueAsTimestamp             // public, slots                     *
 * @return  QDateTime                                        //                                   *
 * @comment returns the formula value as timestamp.                                               *
 *----------------last changed: --------------------------------Di 20. Nov 11:58:21 2012----------*/
QDateTime CdmValueFormula::GetValueAsTimestamp()
{
   QDateTime qdtDateTime;
   QVariant qScriptValue = Evaluate();
   qdtDateTime = qScriptValue.toDateTime();
   return qdtDateTime;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:58:29 2012----------*
 * @method  CdmValueFormula::GetValueAsDate                  // public, slots                     *
 * @return  QDate                                            //                                   *
 * @comment returns the formulavalue as date.                                                     *
 *----------------last changed: --------------------------------Di 20. Nov 11:58:29 2012----------*/
QDate CdmValueFormula::GetValueAsDate()
{
   QDate qdDate;
   QVariant qScriptValue = Evaluate();
   qdDate = qScriptValue.toDateTime().date();
   return qdDate;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:58:39 2012----------*
 * @method  CdmValueFormula::GetValueAsTime                  // public, slots                     *
 * @return  QTime                                            //                                   *
 * @comment returns the formula value as time.                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 11:58:39 2012----------*/
QTime CdmValueFormula::GetValueAsTime()
{
   QTime qtTime;
   QVariant qScriptValue = Evaluate();
   qtTime = qScriptValue.toDateTime().time();
   return qtTime;
}

/** +-=---------------------------------------------------------So 10. Feb 18:39:14 2013----------*
 * @method  CdmValueFormula::Evaluate                        // private, const                    *
 * @return  QVariant                                         //                                   *
 * @comment evaluates the formula and returns the variant.                                        *
 *----------------last changed: --------------------------------So 10. Feb 18:39:14 2013----------*/
QVariant CdmValueFormula::Evaluate() const
{
   QVariant qResult;
   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      QString qstrFormula = pCdmMember->GetValidationCode();
      qResult = CdmExecutor::GetExecutor()->EvaluateFormula(GetObject(), qstrFormula);
   }

   return qResult;
}

/** +-=---------------------------------------------------------Mi 15. Sep 13:59:09 2010----------*
 * @method  CdmValueFormula::IsEqual                         // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment This emthod returns if the overgiven Value has the same value as this parameter.      *
 *----------------last changed: --------------------------------Mi 15. Sep 13:59:09 2010----------*/
int CdmValueFormula::IsEqual(QVariant*) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   return iRet;
}

/** +-=---------------------------------------------------------Mi 15. Sep 13:59:23 2010----------*
 * @method  CdmValueFormula::IsSmaller                       // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Mi 15. Sep 13:59:23 2010----------*/
int CdmValueFormula::IsSmaller(QVariant* ) const
{
   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 13:59:33 2010----------*
 * @method  CdmValueFormula::IsSmallerEqual                  // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Mi 15. Sep 13:59:33 2010----------*/
int CdmValueFormula::IsSmallerEqual(QVariant*) const
{
   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 13:59:42 2010----------*
 * @method  CdmValueFormula::IsLarger                        // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 13:59:42 2010----------*/
int CdmValueFormula::IsLarger(QVariant* ) const
{
   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 13:59:52 2010----------*
 * @method  CdmValueFormula::IsLargerEqual                   // public, const                     *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Mi 15. Sep 13:59:53 2010----------*/
int CdmValueFormula::IsLargerEqual(QVariant*) const
{
   ERR("Not Comparable");
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:00:02 2010----------*
 * @method  CdmValueFormula::IsNotEqual                      // public, const                     *
 * @return  int                                              // -1 = invalid 0 = false 1 = true   *
 * @param   QVariant*# p_pqVariant                           //                                   *
 * @comment This emthod returns if the overgiven Value has not the same value as this             *
 *          parameter.                                                                            *
 *----------------last changed: --------------------------------Mi 15. Sep 14:00:02 2010----------*/
int CdmValueFormula::IsNotEqual(QVariant*) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;
   ERR("Not Comparable");
   return iRet;
}

/** +-=---------------------------------------------------------Fr 3. Apr 17:17:54 2009-----------*
 * @method  CdmValueFormula::CheckUnique                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: --------------------------------Fr 3. Apr 17:17:54 2009-----------*/
void CdmValueFormula::CheckUnique()
{
   // DOES NOTHING
}

/** +-=---------------------------------------------------------So 10. Feb 18:00:07 2013----------*
 * @method  CdmValueFormula::XmlExport                       // public, const                     *
 * @return  void                                             //                                   *
 * @param   QDomElement&# p_rqdeValue                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 18:00:07 2013----------*/
void CdmValueFormula::XmlExport(QDomElement&) const
{
 // DOES NOTHING
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:00:24 2010----------*
 * @method  CdmValueFormula::XmlImportString                 // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& #p_rqDomElement                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 15. Sep 14:00:24 2010----------*/
void CdmValueFormula::XmlImportString(QDomElement& )
{
    // DOES NOTHING
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:00:34 2010----------*
 * @method  CdmValueFormula::XmlImport                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QDomElement& #p_rqDomElement                     //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived       *
 *          class.                                                                                *
 *----------------last changed: --------------------------------Mi 15. Sep 14:00:34 2010----------*/
void CdmValueFormula::XmlImport(QDomElement& )
{
   // DOES NOTHING
}

/** +-=---------------------------------------------------------So 10. Feb 18:00:21 2013----------*
 * @method  CdmValueFormula::GetDisplayString                // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 18:00:21 2013----------*/
QString CdmValueFormula::GetDisplayString() const
{
   return GetValueAsString();
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:00:51 2010----------*
 * @method  CdmValueFormula::FromStringToValue               // public                            *
 * @return  int                                              // Succcessflag                      *
 * @param   QString# p_qstrValue                             //                                   *
 * @comment This method tries to convert a string to a Value.                                     *
 *----------------last changed: --------------------------------Mi 15. Sep 14:00:51 2010----------*/
int CdmValueFormula::FromStringToValue(QString)
{
   // DOES NOTHING Keeping baseclass work
   int iRet = EC(eDmOk);
   return iRet;
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:01:01 2010----------*
 * @method  CdmValueFormula::SetValue                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString #p_qstrValue                             //                                   *
 * @param   QString #p_qstrValue2                            // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: --------------------------------Mi 15. Sep 14:01:01 2010----------*/
void CdmValueFormula::SetValue(QString , QString )
{
   // Does nothing
}

/** +-=---------------------------------------------------------So 10. Feb 18:00:41 2013----------*
 * @method  CdmValueFormula::GetVariant                      // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 18:00:41 2013----------*/
QVariant CdmValueFormula::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValueAsString());
   return qmVariant;
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:17:20 2013----------*
 * @method  CdmValueFormula::SetVariant                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:17:20 2013----------*/
void CdmValueFormula::SetVariant(QVariantMap& p_rqvHash)
{
   Q_UNUSED(p_rqvHash);
   // Does nothing
}

/** +-=---------------------------------------------------------So 10. Feb 18:00:49 2013----------*
 * @method  CdmValueFormula::GetValueVariant                 // public, const, virtual, slots     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 18:00:49 2013----------*/
QVariant CdmValueFormula::GetValueVariant() const
{
   return QVariant(GetValueAsString());
}

/** +-=---------------------------------------------------------Di 5. Jun 08:58:39 2012-----------*
 * @method  CdmValueFormula::SetValueVariant                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant&# p_rqVariant                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 08:58:39 2012-----------*/
void CdmValueFormula::SetValueVariant(QVariant&)
{
    // Does nothing
}
