﻿/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueUser.h
 ** Started Implementation: 2009/04/07
 ** Description:
 ** 
 ** Implements the user values
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CDMVALUEUSER_H
#define CDMVALUEUSER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CdmValueInt.h"


// Forwards


// Enumerations

/* 
 * This class implements the user value
 */
class WMSMANAGER_API CdmValueUser : public CdmValueInt
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 22:07:25 2009--------*
    * @method  CdmValueUser::CdmValueUser                    // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value keyname                     *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The Userconstructor                                                                *
    *----------------last changed: -----------------------------Di 7. Apr 22:07:25 2009-----------*/
    CdmValueUser( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);


   public:
   /** +-=---------------------------------------------------------Di 7. Apr 22:15:36 2009--------*
    * @method  CdmValueUser::~CdmValueUser                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueUser                                               *
    *----------------last changed: -----------------------------Di 7. Apr 22:15:36 2009-----------*/
    virtual ~CdmValueUser( );

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 12:01:45 2012-------*
    * @method  CdmValueUser::GetUser                         // public, slots                     *
    * @return  CumUser*                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 12:01:45 2012----------*/
CumUser* GetUser( );

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 12:01:52 2012-------*
    * @method  CdmValueUser::SetUser                         // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CumUser* p_pCumUser                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 12:01:52 2012----------*/
void SetUser( CumUser* p_pCumUser);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 11:41:46 2013-------*
    * @method  CdmValueUser::GetDisplayString                // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:41:46 2013----------*/
      virtual QString GetDisplayString( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 11:41:57 2013-------*
    * @method  CdmValueUser::GetLogin                        // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:41:57 2013----------*/
      virtual QString GetLogin( ) const;

   public:
   /** +-=---------------------------------------------------------Fr 10. Apr 19:29:58 2009-------*
    * @method  CdmValueUser::CdmValueUser                    // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Source                        *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The integer constructor.                                                           *
    *----------------last changed: -----------------------------Fr 10. Apr 19:29:58 2009----------*/
    CdmValueUser( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:42:07 2013-------*
    * @method  CdmValueUser::GetVariant                      // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 11:42:07 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 14:13:36 2012-------*
    * @method  CdmValueUser::CdmValueUser                    // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 14:13:36 2012----------*/
    CdmValueUser( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:42:16 2013-------*
    * @method  CdmValueUser::GetValueVariant                 // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:42:16 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 08:45:49 2012--------*
    * @method  CdmValueUser::SetValueVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 08:45:49 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

};

#endif //
