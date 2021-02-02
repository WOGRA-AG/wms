/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsLoginEstablishConnection.h
 ** Started Implementation: 2008/03/23
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSLOGINESTABLISHCONNECTION_H
#define CWMSLOGINESTABLISHCONNECTION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// WMS Manager Includes
#include "CdmSettings.h"

// Own Includes
#include "wmsgui.h"

// Forwards


// Enumerations

/* 
 * This class implements the establishing of the connection to server, db or file
 */
class WMSGUI_API CwmsLoginEstablishConnection : public QObject
{
   
private:
      QString m_qstrApplicationName;
      QString m_qstrVersion;


   public:
   /** +-=---------------------------------------------------------Mo 5. Mai 20:24:59 2008--------*
    * @method  CwmsLoginEstablishConnection::CwmsLoginEstablishConnection // public               *
    * @return                                                //                                   *
    * @param   QString p_qstrApplicationName                 //                                   *
    * @param   QString p_qstrVersion                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Mai 20:24:59 2008-----------*/
    CwmsLoginEstablishConnection( QString p_qstrApplicationName, QString p_qstrVersion);

   public:
   /** +-=---------------------------------------------------------So 23. Mrz 21:40:03 2008-------*
    * @method  CwmsLoginEstablishConnection::~CwmsLoginEstablishConnection // public, virtual     *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsLoginEstablishConnection                               *
    *----------------last changed: -----------------------------So 23. Mrz 21:40:03 2008----------*/
    virtual ~CwmsLoginEstablishConnection( );

   public:
   /** +-=---------------------------------------------------------Mo 17. Aug 18:33:27 2009-------*
    * @method  CwmsLoginEstablishConnection::EstablishConnection // public                        *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Aug 18:33:27 2009----------*/
    bool EstablishConnection();

   private: 
   /** +-=---------------------------------------------------------So 23. Mrz 11:58:43 2008-------*
    * @method  CwmsLoginEstablishConnection::CreateManager   // private                           *
    * @return  bool                                          //                                   *
    * @comment this method creates the manager object.                                            *
    *----------------last changed: -----------------------------So 23. Mrz 11:58:43 2008----------*/
    bool CreateManager();

   public:
   /** +-=---------------------------------------------------------So 18. Mai 12:49:43 2008-------*
    * @method  CwmsLoginEstablishConnection::GetApplicationName // public                         *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 12:49:43 2008----------*/
    QString GetApplicationName();
};

#endif //
