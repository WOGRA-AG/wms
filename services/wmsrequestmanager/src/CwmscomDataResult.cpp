/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomDataResult.cpp
 ** Started Implementation: 2012/04/01
 ** Description:
 **
 ** Implements the result container
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// own Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

/** +-=---------------------------------------------------------So 1. Apr 10:44:30 2012-----------*
 * @method  CwmscomDataResult::CwmscomDataResult             // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomData* p_pRequestObject                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:44:30 2012-----------*/
CwmscomDataResult::CwmscomDataResult(CwmscomData* p_pRequestObject)
: m_rpRequestObject(p_pRequestObject),
  m_eReturnCode(eWmsHttpStatusCodeOk) // Optmistic Default
{
   if (p_pRequestObject)
   {
      p_pRequestObject->SetResult(this);
   }
}

/** +-=---------------------------------------------------------Di 29. Mai 10:47:46 2012----------*
 * @method  CwmscomDataResult::~CwmscomDataResult            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmscomDataResult                                             *
 *----------------last changed: --------------------------------Di 29. Mai 10:47:46 2012----------*/
CwmscomDataResult::~CwmscomDataResult()
{

}

/** +-=---------------------------------------------------------Mo 9. Apr 11:42:53 2012-----------*
 * @method  CwmscomDataResult::AddValue                      // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   QVariant p_qvValue                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:42:53 2012-----------*/
void CwmscomDataResult::AddValue(QString p_qstrKey, QVariant p_qvValue)
{
   m_qmResult.insert(p_qstrKey, p_qvValue);
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:27:48 2012-----------*
 * @method  CwmscomDataResult::SetResultMap                  // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap p_qMap                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:27:48 2012-----------*/
void CwmscomDataResult::SetResultMap(QVariantMap p_qMap)
{
   m_qmResult = p_qMap;
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:27:06 2012-----------*
 * @method  CwmscomDataResult::GetResultMap                  // public                            *
 * @return  QVariantMap&                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:27:06 2012-----------*/
QVariantMap& CwmscomDataResult::GetResultMap()
{
   return m_qmResult;
}

/** +-=---------------------------------------------------------So 1. Apr 10:45:42 2012-----------*
 * @method  CwmscomDataResult::SetMessageCode                // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iCode                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:45:42 2012-----------*/
void CwmscomDataResult::SetMessageCode(int p_iCode)
{
   m_qmResult.insert("MessageCode", p_iCode);
}

/** +-=---------------------------------------------------------So 1. Apr 10:46:04 2012-----------*
 * @method  CwmscomDataResult::GetMessageCode                // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:46:04 2012-----------*/
int CwmscomDataResult::GetMessageCode()
{
   return m_qmResult["MessageCode"].toInt();
}

/** +-=---------------------------------------------------------So 1. Apr 10:46:33 2012-----------*
 * @method  CwmscomDataResult::SetMessage                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:46:33 2012-----------*/
void CwmscomDataResult::SetMessage(QString p_qstrMessage)
{
   m_qmResult.insert("Message", p_qstrMessage);
}

/** +-=---------------------------------------------------------So 1. Apr 10:46:52 2012-----------*
 * @method  CwmscomDataResult::GetMessage                    // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:46:52 2012-----------*/
QString CwmscomDataResult::GetMessage()
{
   return m_qmResult["Message"].toString();
}

/** +-=---------------------------------------------------------So 1. Apr 10:47:20 2012-----------*
 * @method  CwmscomDataResult::SetSeverity                   // public                            *
 * @return  void                                             //                                   *
 * @param   EbmscomMessageServerity p_eSeverity              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:47:20 2012-----------*/
void CwmscomDataResult::SetSeverity(EwmscomMessageServerity p_eSeverity)
{
   m_qmResult.insert("MessageSeverity", p_eSeverity);
}

/** +-=---------------------------------------------------------So 1. Apr 10:47:45 2012-----------*
 * @method  CwmscomDataResult::GetSeverity                   // public                            *
 * @return  EbmscomMessageServerity                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:47:45 2012-----------*/
EwmscomMessageServerity CwmscomDataResult::GetSeverity()
{
   return (EwmscomMessageServerity)m_qmResult["MessageSeverity"].toInt();
}

/** +-=---------------------------------------------------------So 1. Apr 10:48:51 2012-----------*
 * @method  CwmscomDataResult::GetRequestObject              // public                            *
 * @return  CwmscomData*                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:48:51 2012-----------*/
CwmscomData* CwmscomDataResult::GetRequestObject()
{
   return m_rpRequestObject;
}

/** +-=---------------------------------------------------------Mo 9. Jul 11:45:55 2012-----------*
 * @method  CwmscomDataResult::SetReturnCode                 // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iCode                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Jul 11:45:55 2012-----------*/
void CwmscomDataResult::SetReturnCode(int p_iCode)
{
   m_eReturnCode = (EwmsHttpStatusCode)p_iCode;
}

EwmsHttpStatusCode CwmscomDataResult::GetReturnCode()
{
    return m_eReturnCode;
}
