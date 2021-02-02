/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsExportSettingsHandler.cpp
 ** Started Implementation: 2008/10/20
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CwmsJson.h"

// Own Includes
#include "CwmsImExportConfiguration.h"
#include "CwmsImExportManager.h"
#include "CwmsImExportSettingsHandler.h"

const float  PRECISION_FLOAT  = 1000.0;
const double PRECISION_DOUBLE = 1000000.0;

/** +-=---------------------------------------------------------Mon Aug 26 21:33:56 2002----------*
 * @method  CwmsImExportSettingsHandler::CwmsImExportSettingsHandler             // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:33:56 2002---------*/
CwmsImExportSettingsHandler::CwmsImExportSettingsHandler(  )
{
}


/** +-=---------------------------------------------------------Mon Aug 26 21:34:09 2002----------*
 * @method  CwmsImExportSettingsHandler::~CwmsImExportSettingsHandler            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImExportSettingsHandler                                             *
 *                                                                                                *
 *---------------------------------------------------------------Mon Aug 26 21:34:09 2002---------*/
CwmsImExportSettingsHandler::~CwmsImExportSettingsHandler(  )
{
}

/** +-=---------------------------------------------------------Mi 6. Feb 12:05:30 2013-----------*
 * @method  CwmsImExportSettingsHandler::Load                // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   QString p_qstrContent                            //                                   *
 * @comment Loads the Sessionfile.                                                                *
 *----------------last changed: --------------------------------Mi 6. Feb 12:05:30 2013-----------*/
bool CwmsImExportSettingsHandler::Load(QString p_qstrName, QString p_qstrContent)
{
   bool bRet = false;

   if (!p_qstrName.isEmpty() && ! p_qstrContent.isEmpty())
   {
	   m_qstrName = p_qstrName;
      CwmsJson cJson;
	   m_qvData = cJson.parse(p_qstrContent, bRet).toMap();
   }

	return bRet;
}

/** +-=---------------------------------------------------------Mi 6. Feb 11:44:17 2013-----------*
 * @method  CwmsImExportSettingsHandler::Save                // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   long p_lCassId                                   //                                   *
 * @param   EwmsImExportMode p_eMode                         //                                   *
 * @comment Save the Sessionfile under an other filename.                                         *
 *----------------last changed: --------------------------------Mi 6. Feb 11:44:17 2013-----------*/
bool CwmsImExportSettingsHandler::Save(QString p_qstrName, CdmClass* p_pClass, EwmsImExportMode p_eMode)
{
   bool bRet = false;
   CwmsImExportManager cManager;
   CwmsImExportConfiguration cConfig;

   if (CHKPTR(p_pClass))
   {
       if (p_eMode == eWmsImExportModeImport)
       {
          cConfig = cManager.CreateOrGetImportConfiguration(p_qstrName, p_pClass->GetId());
       }
       else
       {
          cConfig = cManager.CreateOrGetExportConfiguration(p_qstrName, p_pClass->GetId());
       }

       if (cConfig.IsValid())
       {
          cConfig.SetName(p_qstrName);
          cConfig.SetClass(p_pClass);
          CwmsJson cJson;
          QByteArray qArray = cJson.serialize(m_qvData, bRet);
          cConfig.SetConfiguration(QString(qArray));

          if (cConfig.CommitObject() > 0)
          {
             bRet = true;
          }
       }
   }

	return bRet;
}

/** +-=---------------------------------------------------------Fri Nov 1 09:43:06 2002-----------*
 * @method  CwmsImExportSettingsHandler::AddKey                        // public                            *
 * @return  void                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @comment Adds a Key to the the session.                                                        *
 *---------------------------------------------------------------Fri Nov 1 09:43:06 2002----------*/
void CwmsImExportSettingsHandler::AddKey(  QString sKey )
{
   if (!m_qvData.contains(sKey))
   {
      QVariantMap qvChild;
      m_qvData.insert(sKey, qvChild);
   }
}

/** +-=---------------------------------------------------------Mon Aug 26 21:38:15 2002----------*
 * @method  CwmsImExportSettingsHandler::IsKey                         // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @comment returns if this is a key or not.                                                      *
 *---------------------------------------------------------------Mon Aug 26 21:38:15 2002---------*/
bool CwmsImExportSettingsHandler::IsKey(  QString sKey )
{
	return static_cast<bool>(m_qvData.contains(sKey));
}

/** +-=---------------------------------------------------------Sa 21. Jun 11:58:22 2003----------*
 * @method  CwmsImExportSettingsHandler::SetString                     // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString sContent                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 21. Jun 11:58:22 2003----------*/
bool CwmsImExportSettingsHandler::SetString(  QString sKey, QString sValue, QString sContent )
{
	return SetContent(sKey,sValue,sContent);
}


/** +-=---------------------------------------------------------Mon Aug 26 21:41:19 2002----------*
 * @method  CwmsImExportSettingsHandler::SetInteger                    // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   int nContent                                     //                                   *
 * @comment Sets the Integer value to session.                                                    *
 *---------------------------------------------------------------Mon Aug 26 21:41:19 2002---------*/
bool CwmsImExportSettingsHandler::SetInteger(  QString sKey, QString sValue, int nContent )
{
	return SetContent(sKey,sValue,QString::number(nContent));	
}

/** +-=---------------------------------------------------------Mon Aug 26 21:46:40 2002----------*
 * @method  CwmsImExportSettingsHandler::SetFloat                      // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   float fContent                                   //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:46:40 2002---------*/
bool CwmsImExportSettingsHandler::SetFloat(  QString sKey, QString sValue, float fContent )
{
	int nContent = static_cast<int>(PRECISION_FLOAT * fContent);
	return SetContent(sKey,sValue,QString::number(nContent));
}

/** +-=---------------------------------------------------------Mon Aug 26 21:47:34 2002----------*
 * @method  CwmsImExportSettingsHandler::SetContent                    // private                           *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString sContent                                 //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:47:34 2002---------*/
bool CwmsImExportSettingsHandler::SetContent(  QString sKey, QString sValue, QString sContent )
{
	QVariantMap qvContent;

   if (m_qvData.contains(sKey))
   {
      qvContent = m_qvData[sKey].toMap();
   }
	
   qvContent.insert(sValue, sContent);
   m_qvData[sKey] = qvContent;
	return true;
}
/** +-=---------------------------------------------------------Mon Aug 26 21:52:19 2002----------*
 * @method  CwmsImExportSettingsHandler::GetString                     // public                            *
 * @return  QString                                          //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString sReturn                                  //                                   *
 * @comment returns the String of the Key and Value.                                              *
 *---------------------------------------------------------------Mon Aug 26 21:52:19 2002---------*/
QString CwmsImExportSettingsHandler::GetString(  QString sKey, QString sValue, QString sReturn )
{
	QString sContent;

	if (!GetContent(sKey,sValue,sContent)) 
      return sReturn;
	else 
      return sContent;
}

/** +-=---------------------------------------------------------Mon Aug 26 21:53:08 2002----------*
 * @method  CwmsImExportSettingsHandler::GetInteger                    // public                            *
 * @return  int                                              //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   int nReturn                                      //                                   *
 * @comment returns the Integer at Key and Value.                                                 *
 *---------------------------------------------------------------Mon Aug 26 21:53:08 2002---------*/
int CwmsImExportSettingsHandler::GetInteger(  QString sKey, QString sValue, int nReturn )
{
	QString sContent;

	if (!GetContent(sKey,sValue,sContent)) 
      return nReturn;
   else
	   return sContent.toInt();
}


/** +-=---------------------------------------------------------Mon Aug 26 21:57:54 2002----------*
 * @method  CwmsImExportSettingsHandler::GetFloat                      // public                            *
 * @return  float                                            //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   float fReturn                                    //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:57:54 2002---------*/
float CwmsImExportSettingsHandler::GetFloat(  QString sKey, QString sValue, float fReturn )
{
	QString sContent;

	if (!GetContent(sKey,sValue,sContent)) 
      return fReturn;
   else
	   return static_cast<float>(sContent.toFloat()/PRECISION_FLOAT);
}

/** +-=---------------------------------------------------------Mo 29. Okt 14:04:47 2012----------*
 * @method  CwmsImExportSettingsHandler::GetContent            // private                           *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString& sContent                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 14:04:47 2012----------*/
bool CwmsImExportSettingsHandler::GetContent(QString sKey, QString sValue, QString& sContent)
{

   bool bRet = false;
   QVariantMap qvContent;

   if (m_qvData.contains(sKey))
   {
      qvContent = m_qvData[sKey].toMap();
   }

   if (qvContent.contains(sValue))
   {
      sContent = qvContent[sValue].toString();
      bRet = true;
   }

	return bRet;
}
