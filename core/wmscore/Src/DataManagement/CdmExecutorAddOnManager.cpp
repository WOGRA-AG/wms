/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmExecutorAddOnManager.cpp
 ** Started Implementation: 2012/09/19
 ** Description:
 **
 ** Implements the executor for functions and validations in Objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QJSValue>

// own Includes
#include "CsaFactory.h"
#include "IwmsPrintingPlugin.h"
#include "IwmsPluginInterface.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"

/** +-=---------------------------------------------------------Mi 19. Sep 14:17:10 2012----------*
 * @method  CdmExecutorAddOnManager::CdmExecutorAddOnManager                         // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 14:17:10 2012----------*/
CdmExecutorAddOnManager::CdmExecutorAddOnManager()
    : m_pPrintingPlugin(nullptr)
{
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012----------*
 * @method  CdmExecutorAddOnManager::~CdmExecutorAddOnManager                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmExecutorAddOnManager                                                   *
 *----------------last changed: --------------------------------Mi 19. Sep 14:18:59 2012----------*/
CdmExecutorAddOnManager::~CdmExecutorAddOnManager()
{
    SYNCHRONIZED;
    QMap<QString, QObject*>::iterator qmIt = m_qmAdditionalFunctions.begin();
    QMap<QString, QObject*>::iterator qmItEnd = m_qmAdditionalFunctions.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        QObject* pObject = qmIt.value();
        DELPTR(pObject)
    }

    DELPTR(m_pPrintingPlugin)
    m_qmAdditionalFunctions.clear();
    ClearPlugins();
}

void CdmExecutorAddOnManager::SetPrintingPlugin(IwmsPrintingPlugin* p_pPlugin)
{
    SYNCHRONIZED;
    m_pPrintingPlugin = p_pPlugin;
}

IwmsPrintingPlugin* CdmExecutorAddOnManager::GetPrintingPlugin()
{
    return m_pPrintingPlugin;
}

void CdmExecutorAddOnManager::ResetPrintingPlugin()
{
    SYNCHRONIZED;
    DELPTR(m_pPrintingPlugin)
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:34:02 2012----------*
* @method  CdmExecutorAddOnManager::AddFunctionality                    // private                           *
* @return  void                                             //                                   *
* @param   QString p_qstrName                               //                                   *
* @param   QObject* p_pqFunctionality                       //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Mi 19. Sep 14:34:02 2012----------*/
void CdmExecutorAddOnManager::AddFunctionality(QString p_qstrName, QObject* p_pqFunctionality)
{
   SYNCHRONIZED;
   if (!m_qmAdditionalFunctions.contains(p_qstrName))
   {
      m_qmAdditionalFunctions.insert(p_qstrName, p_pqFunctionality);
   }
}

bool CdmExecutorAddOnManager::ContainsFunctionality(QString p_qstrName)
{
    return m_qmAdditionalFunctions.contains(p_qstrName);
}

/** +-=---------------------------------------------------------Mo 7. Jan 14:30:19 2013-----------*
 * @method  CdmExecutorAddOnManager::AddPlugin                           // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   IwmsPluginInterface* p_pPlugin                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 7. Jan 14:30:19 2013-----------*/
void CdmExecutorAddOnManager::AddPlugin(QString p_qstrName, IwmsPluginInterface* p_pPlugin)
{
    SYNCHRONIZED;
   if (!m_qmPlugins.contains(p_qstrName) && CHKPTR(p_pPlugin))
   {
      m_qmPlugins.insert(p_qstrName, p_pPlugin);
   }
}

void CdmExecutorAddOnManager::RemovePlugin(QString p_qstrName)
{
    SYNCHRONIZED;
   QMap<QString, IwmsPluginInterface*>::iterator qmIt = m_qmPlugins.begin();
   QMap<QString, IwmsPluginInterface*>::iterator qmItEnd = m_qmPlugins.end();
   QStringList qstrlKeysToRemove;
   QList<IwmsPluginInterface*> qlPointers;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrName = qmIt.key();

      if (qstrName.startsWith(p_qstrName))
      {
         IwmsPluginInterface* pPlugin = qmIt.value();

         if (CHKPTR(pPlugin) && !qlPointers.contains(pPlugin))
         {
            qlPointers.append(pPlugin);
            DELPTR(pPlugin)
            qstrlKeysToRemove.append(qstrName);
         }
      }
   }

   for (int iPos = 0; iPos < qstrlKeysToRemove.count(); ++iPos)
   {
      m_qmPlugins.remove(qstrlKeysToRemove[iPos]);
   }
}

void CdmExecutorAddOnManager::ClearPlugins()
{
    SYNCHRONIZED;
    QMap<QString, IwmsPluginInterface*>::iterator qmIt = m_qmPlugins.begin();
    QMap<QString, IwmsPluginInterface*>::iterator qmItEnd = m_qmPlugins.end();
    QList<IwmsPluginInterface*> qlPointers;

    for (; qmIt != qmItEnd; ++qmIt)
    {
        IwmsPluginInterface* pObject = qmIt.value();

        if (CHKPTR(pObject)  && !qlPointers.contains(pObject))
        {
            qlPointers.append(pObject);
            DELPTR(pObject)
        }
    }

    ResetPrintingPlugin();
    m_qmPlugins.clear();
}

/** +-=---------------------------------------------------------Do 20. Sep 10:22:29 2012----------*
 * @method  CdmExecutorAddOnManager::AddAditionalFunctionalityToEngine   // public                *
 * @return  void                                             //                                   *
 * @param   QScriptEngine& p_rqEngine                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 10:22:29 2012----------*/
void CdmExecutorAddOnManager::AddAditionalFunctionalityToEngine(QScriptEngine& p_rqEngine)
{
    SYNCHRONIZED;
   QMap<QString, QObject*>::iterator qmIt = m_qmAdditionalFunctions.begin();
   QMap<QString, QObject*>::iterator qmItEnd = m_qmAdditionalFunctions.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QScriptValue qsvObject = p_rqEngine.newQObject(qmIt.value());
      QString qstrKey = qmIt.key();
      p_rqEngine.globalObject().setProperty(qstrKey, qsvObject);
   }
}

void CdmExecutorAddOnManager::AddAditionalFunctionalityToEngine(QJSEngine& p_rqEngine)
{
    SYNCHRONIZED;
    QMap<QString, QObject*>::iterator qmIt = m_qmAdditionalFunctions.begin();
    QMap<QString, QObject*>::iterator qmItEnd = m_qmAdditionalFunctions.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
       QJSValue qjsObject = p_rqEngine.newQObject(qmIt.value());
       QString qstrKey = qmIt.key();
       p_rqEngine.globalObject().setProperty(qstrKey, qjsObject);
    }
}

/** +-=---------------------------------------------------------Mo 7. Jan 14:36:06 2013-----------*
 * @method  CdmExecutorAddOnManager::GetFunctionObject                   // public                            *
 * @return  QObject*                                         //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 7. Jan 14:36:06 2013-----------*/
QObject* CdmExecutorAddOnManager::GetFunctionObject(QString p_qstrName)
{
    SYNCHRONIZED;
   QObject* pObject = nullptr;
   
   if (m_qmPlugins.contains(p_qstrName))
   {
      IwmsPluginInterface* pInterface = m_qmPlugins[p_qstrName];

      if (CHKPTR(pInterface))
      {
          int iPos = p_qstrName.indexOf(".");

          if (iPos >= 0)
          {
              p_qstrName = p_qstrName.mid(iPos + 1);
          }

          pObject = pInterface->getFunctionClass(p_qstrName);
      }
   }

   return pObject;
}

/** +-=---------------------------------------------------------Mo 7. Jan 14:22:01 2013-----------*
 * @method  CdmExecutorAddOnManager::InstallPlugin                       // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   IwmsPluginInterface* p_pPlugin                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 7. Jan 14:22:01 2013-----------*/
void CdmExecutorAddOnManager::InstallPlugin(QString p_qstrName, IwmsPluginInterface* p_pPlugin)
{
   if (CHKPTR(p_pPlugin))
   {
      AddPlugin(p_qstrName, p_pPlugin);
   }
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:35:28 2012----------*
 * @method  CdmExecutorAddOnManager::InstallAdditionalFunctionality      // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   QObject* p_pqObject                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 14:35:28 2012----------*/
void CdmExecutorAddOnManager::InstallAdditionalFunctionality(QString p_qstrName, QObject* p_pqObject)
{
   AddFunctionality(p_qstrName, p_pqObject);
}
