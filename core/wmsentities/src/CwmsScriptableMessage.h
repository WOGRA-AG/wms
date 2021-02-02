/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptablePrinter.h
 ** Started Implementation: 2012/11/09
 ** Description:
 ** 
 ** implements the script interface for js methods using messages
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSCRIPTABLEMESSAGE_H
#define CWMSSCRIPTABLEMESSAGE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards


// TypeDefs


/* 
 * This class implements the script interface for js methods using print
 */
class BASETOOLS_API CwmsScriptableMessage: public CwmsScriptableBase
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 11:22:15 2012-------*
    * @method  CwmsScriptableMessage::CwmsScriptableMessage  // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:22:15 2012----------*/
    CwmsScriptableMessage( );

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 11:22:23 2012-------*
    * @method  CwmsScriptableMessage::~CwmsScriptableMessage // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsScriptableMessage                                      *
    *----------------last changed: -----------------------------Di 13. Nov 11:22:23 2012----------*/
    virtual ~CwmsScriptableMessage( );

    public slots:
         /** +-=---------------------------------------------------------Di 13. Nov 11:24:15 2012-------*
    * @method  CwmsScriptableMessage::Information            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:24:15 2012----------*/
void information( QString p_qstrTitle, QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Di 13. Nov 11:24:33 2012-------*
    * @method  CwmsScriptableMessage::Warning                // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:24:33 2012----------*/
void warning( QString p_qstrTitle, QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Di 13. Nov 11:24:51 2012-------*
    * @method  CwmsScriptableMessage::Critical               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:24:51 2012----------*/
void critical( QString p_qstrTitle, QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Fr 8. Feb 15:07:32 2013--------*
    * @method  CwmsScriptableMessage::Ask                    // public, slots                     *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrTitle                           //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 15:07:32 2013-----------*/
bool ask( QString p_qstrTitle, QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Fr 8. Feb 15:07:41 2013--------*
    * @method  CwmsScriptableMessage::ShowResult             // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @param   QString p_qstrResultText                      //                                   *
    * @param   QString p_qstrResult                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 15:07:41 2013-----------*/
void showResult( QString p_qstrCaption, QString p_qstrResultText, QString p_qstrResult);
bool startProgressBar(QString p_qstrProgessBarName, QString p_qstrTitle, QString p_qstrDisplayText, int p_iSteps);
bool setProgress(QString p_qstrProgessBarName, QString p_qstrDisplayText, int p_iProgressSteps);
bool closeProgressBar(QString p_qstrProgessBarName);
bool startAsyncMessageCollection();
bool endAndShowAsyncMessageCollection();
bool isAsyncMessageCollectionRunning();
};

#endif // CWMSSCRIPTABLEPRINTER_H
