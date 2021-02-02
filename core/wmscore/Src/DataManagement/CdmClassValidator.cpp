/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmClassValidator.cpp
 ** Started Implementation: 2012/06/25
 ** Description:
 **
 ** This class implements the class validator. a validator is able to validate
 ** objects or objectlist that it fits the user demands. if it does not fit
 ** it returns an error message.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QByteArray>


// own Includes
#include "wmsdefines.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmClassValidator.h"

/** +-=---------------------------------------------------------Mo 25. Jun 18:23:28 2012----------*
 * @method  CdmClassValidator::CdmClassValidator             // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:23:28 2012----------*/
CdmClassValidator::CdmClassValidator()
: m_iId(0),
  m_eValType(eDmValidationTypeObject),
  m_iVersion(0)
{
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:23:53 2012----------*
 * @method  CdmClassValidator::CdmClassValidator             // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:23:53 2012----------*/
CdmClassValidator::CdmClassValidator(QVariantMap& p_rqvHash)
: m_iId(0),
  m_eValType(eDmValidationTypeObject),
  m_iVersion(0)
{
   SetVariant(p_rqvHash);
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:23:36 2012----------*
 * @method  CdmClassValidator::~CdmClassValidator            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmClassValidator                                             *
 *----------------last changed: --------------------------------Mo 25. Jun 18:23:36 2012----------*/
CdmClassValidator::~CdmClassValidator()
{
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:24:09 2012----------*
 * @method  CdmClassValidator::SetVariant                    // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:24:09 2012----------*/
void CdmClassValidator::SetVariant(QVariantMap& p_rqvHash)
{
   m_iId = p_rqvHash[WMS_ID].toInt();
   m_iVersion = p_rqvHash[WMS_VERSION].toInt();
   m_eValType = (EdmValidationType)p_rqvHash[WMS_VALIDATIONTYPE].toInt();
   m_qstrCode = p_rqvHash[WMS_CODE].toString();
   m_qstrName = p_rqvHash[WMS_NAME].toString();
   m_qstrErrorMessage = p_rqvHash[WMS_ERRORMESSAGE].toString();
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:24:17 2013-----------*
 * @method  CdmClassValidator::GetVariant                    // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:24:17 2013-----------*/
QVariant CdmClassValidator::GetVariant() const
{
   QVariantMap qvHash;

   qvHash.insert(WMS_ID, m_iId);
   qvHash.insert(WMS_VALIDATIONTYPE, m_eValType);
   qvHash.insert(WMS_NAME, m_qstrName);
   qvHash.insert(WMS_VERSION, m_iVersion);
   qvHash.insert(WMS_CODE, m_qstrCode);
   qvHash.insert(WMS_ERRORMESSAGE, m_qstrErrorMessage);

   return qvHash;
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:26:00 2012----------*
 * @method  CdmClassValidator::SetId                         // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:26:00 2012----------*/
void CdmClassValidator::SetId(int p_iId)
{
   m_iId = p_iId;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:24:55 2013-----------*
 * @method  CdmClassValidator::GetId                         // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:24:55 2013-----------*/
int CdmClassValidator::GetId() const
{
   return m_iId;
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:26:39 2012----------*
 * @method  CdmClassValidator::SetVersion                    // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iVersion                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:26:39 2012----------*/
void CdmClassValidator::SetVersion(int p_iVersion)
{
   m_iVersion = p_iVersion;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:25:06 2013-----------*
 * @method  CdmClassValidator::GetVersion                    // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:25:06 2013-----------*/
int CdmClassValidator::GetVersion() const
{
   return m_iVersion;
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:27:23 2012----------*
 * @method  CdmClassValidator::SetName                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:27:23 2012----------*/
void CdmClassValidator::SetName(QString p_qstrName)
{
   m_qstrName = p_qstrName;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:25:17 2013-----------*
 * @method  CdmClassValidator::GetName                       // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:25:17 2013-----------*/
QString CdmClassValidator::GetName() const
{
   return m_qstrName;
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:28:05 2012----------*
 * @method  CdmClassValidator::SetCode                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCode                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:28:05 2012----------*/
void CdmClassValidator::SetCode(QString p_qstrCode)
{
   m_qstrCode = p_qstrCode;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:25:26 2013-----------*
 * @method  CdmClassValidator::GetCode                       // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:25:26 2013-----------*/
QString CdmClassValidator::GetCode() const
{
    return m_qstrCode;
}

QString CdmClassValidator::GetCodeBase64() const
{
    QByteArray ba;
    ba.append(m_qstrCode);
    return ba.toBase64();
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:29:01 2012----------*
 * @method  CdmClassValidator::SetMessage                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMesage                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:29:01 2012----------*/
void CdmClassValidator::SetMessage(QString p_qstrMesage)
{
   m_qstrErrorMessage = p_qstrMesage;
}

QString CdmClassValidator::GetErrorMessage() const
{
   return m_qstrErrorMessage;
}

/** +-=---------------------------------------------------------Mo 25. Jun 18:30:04 2012----------*
 * @method  CdmClassValidator::SetValidationType             // public                            *
 * @return  void                                             //                                   *
 * @param   EdmValidationType p_eType                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 18:30:04 2012----------*/
void CdmClassValidator::SetValidationType(EdmValidationType p_eType)
{
   m_eValType = p_eType;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:25:55 2013-----------*
 * @method  CdmClassValidator::GetValidationType             // public, const, slots              *
 * @return  EdmValidationType                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:25:55 2013-----------*/
EdmValidationType CdmClassValidator::GetValidationType() const
{
   return m_eValType;
}

QString CdmClassValidator::GenerateScriptCode()
{
   QString qstrCode = "function " + GetName() + "()\n";
   qstrCode += "{\n";
   qstrCode += GetCode() + "\n";
   qstrCode += "}\n";


   return qstrCode;

}
