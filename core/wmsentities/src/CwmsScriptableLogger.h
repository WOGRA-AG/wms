/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptableLogger.h
 ** Started Implementation: 2012/11/09
 ** Description:
 ** 
 ** implements the script interface for js methods using logging
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSCRIPTABLELOGGER_H
#define CWMSSCRIPTABLELOGGER_H

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
class CwmsbtMailMessage;

// TypeDefs


/* 
 * This class implements the the script interface for js methods
 */
class BASETOOLS_API CwmsScriptableLogger: public CwmsScriptableBase
{
    Q_OBJECT


   public:
   /** +-=---------------------------------------------------------Mi 9. Okt 14:39:10 2013--------*
    * @method  CwmsScriptableLogger::CwmsScriptableLogger    // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Okt 14:39:10 2013-----------*/
    CwmsScriptableLogger( );

   public:
   /** +-=---------------------------------------------------------Mi 9. Okt 14:40:18 2013--------*
    * @method  CwmsScriptableLogger::~CwmsScriptableLogger   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsScriptableLogger                                       *
    *----------------last changed: -----------------------------Mi 9. Okt 14:40:18 2013-----------*/
    virtual ~CwmsScriptableLogger( );

    public slots:
         /** +-=---------------------------------------------------------Mi 9. Okt 14:44:45 2013--------*
    * @method  CwmsScriptableLogger::Info                    // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Okt 14:44:45 2013-----------*/
void info( QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Mi 9. Okt 14:44:31 2013--------*
    * @method  CwmsScriptableLogger::Warning                 // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Okt 14:44:31 2013-----------*/
void warning( QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Mi 9. Okt 14:44:22 2013--------*
    * @method  CwmsScriptableLogger::Error                   // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Okt 14:44:22 2013-----------*/
void error( QString p_qstrMessage);

    public slots:
         /** +-=---------------------------------------------------------Mi 9. Okt 14:45:28 2013--------*
    * @method  CwmsScriptableLogger::Fatal                   // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Okt 14:45:28 2013-----------*/
void fatal( QString p_qstrMessage);
};

#endif //
