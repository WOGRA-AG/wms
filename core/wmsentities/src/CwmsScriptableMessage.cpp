// System and QT Includes


// own Includes
#include "CdmMessageManager.h"
#include "CwmsScriptableMessage.h"


/** +-=---------------------------------------------------------Di 13. Nov 11:22:15 2012----------*
 * @method  CwmsScriptableMessage::CwmsScriptableMessage     // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 11:22:15 2012----------*/
CwmsScriptableMessage::CwmsScriptableMessage()
{
}

/** +-=---------------------------------------------------------Di 13. Nov 11:22:23 2012----------*
 * @method  CwmsScriptableMessage::~CwmsScriptableMessage    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsScriptableMessage                                         *
 *----------------last changed: --------------------------------Di 13. Nov 11:22:23 2012----------*/
CwmsScriptableMessage::~CwmsScriptableMessage()
{
}

/** +-=---------------------------------------------------------Di 13. Nov 11:24:15 2012----------*
 * @method  CwmsScriptableMessage::Information               // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 11:24:15 2012----------*/
void CwmsScriptableMessage::information(QString p_qstrTitle, QString p_qstrMessage)
{
   MSG_INFO(p_qstrTitle.toUtf8(), p_qstrMessage.toUtf8());
}

/** +-=---------------------------------------------------------Di 13. Nov 11:24:33 2012----------*
 * @method  CwmsScriptableMessage::Warning                   // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 11:24:33 2012----------*/
void CwmsScriptableMessage::warning(QString p_qstrTitle, QString p_qstrMessage)
{
   MSG_WARN(p_qstrTitle.toUtf8(), p_qstrMessage.toUtf8());
}

/** +-=---------------------------------------------------------Di 13. Nov 11:24:51 2012----------*
 * @method  CwmsScriptableMessage::Critical                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 11:24:51 2012----------*/
void CwmsScriptableMessage::critical(QString p_qstrTitle, QString p_qstrMessage)
{
   MSG_CRIT(p_qstrTitle.toUtf8(), p_qstrMessage.toUtf8());
}

/** +-=---------------------------------------------------------Fr 8. Feb 15:07:32 2013-----------*
 * @method  CwmsScriptableMessage::Ask                       // public, slots                     *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrTitle                              //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 15:07:32 2013-----------*/
bool CwmsScriptableMessage::ask(QString p_qstrTitle, QString p_qstrMessage)
{

   return CdmMessageManager::Ask(p_qstrTitle, p_qstrMessage);
}

/** +-=---------------------------------------------------------Fr 8. Feb 15:07:41 2013-----------*
 * @method  CwmsScriptableMessage::ShowResult                // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @param   QString p_qstrResultText                         //                                   *
 * @param   QString p_qstrResult                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 15:07:41 2013-----------*/
void CwmsScriptableMessage::showResult(QString p_qstrCaption,
                                       QString p_qstrResultText,
                                       QString p_qstrResult)
{
    CdmMessageManager::ShowResult(p_qstrCaption, p_qstrResultText, p_qstrResult);
}

bool CwmsScriptableMessage::startProgressBar(QString p_qstrProgessBarName, QString p_qstrTitle, QString p_qstrDisplayText, int p_iSteps)
{
    return CdmMessageManager::StartProgressBar(p_qstrProgessBarName, p_qstrTitle, p_qstrDisplayText, p_iSteps);
}

bool CwmsScriptableMessage::setProgress(QString p_qstrProgessBarName, QString p_qstrDisplayText, int p_iProgressSteps)
{
    return CdmMessageManager::SetProgress(p_qstrProgessBarName, p_qstrDisplayText, p_iProgressSteps);
}

bool CwmsScriptableMessage::closeProgressBar(QString p_qstrProgessBarName)
{
    return CdmMessageManager::CloseProgressBar(p_qstrProgessBarName);
}

bool CwmsScriptableMessage::startAsyncMessageCollection()
{
    return CdmMessageManager::StartAsyncMessageCollection();
}

bool CwmsScriptableMessage::endAndShowAsyncMessageCollection()
{
    return CdmMessageManager::EndAndShowAsyncMessageCollection();
}

bool CwmsScriptableMessage::isAsyncMessageCollectionRunning()
{
    return CdmMessageManager::IsAsyncMessageCollectionRunning();
}
