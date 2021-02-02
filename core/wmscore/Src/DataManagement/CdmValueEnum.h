/******************************************************************************
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

#ifndef CDMVALUEENUM_H
#define CDMVALUEENUM_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QStringList>

// Own Includes
#include "CdmValueInt.h"


// Forwards


// Enumerations

/* 
 * This class implements the user value
 */
class WMSMANAGER_API CdmValueEnum : public CdmValueInt
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 09:58:48 2012-------*
    * @method  CdmValueEnum::CdmValueEnum                    // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value keyname                     *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The Userconstructor                                                                *
    *----------------last changed: -----------------------------Di 28. Aug 09:58:48 2012----------*/
    CdmValueEnum( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);


   public:
   /** +-=---------------------------------------------------------Di 28. Aug 09:58:58 2012-------*
    * @method  CdmValueEnum::CdmValueEnum                    // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Source                        *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The integer constructor.                                                           *
    *----------------last changed: -----------------------------Di 28. Aug 09:58:58 2012----------*/
    CdmValueEnum( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 09:59:03 2012-------*
    * @method  CdmValueEnum::CdmValueEnum                    // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 09:59:03 2012----------*/
    CdmValueEnum( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 09:59:08 2012-------*
    * @method  CdmValueEnum::~CdmValueEnum                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueEnum                                               *
    *----------------last changed: -----------------------------Di 28. Aug 09:59:08 2012----------*/
    virtual ~CdmValueEnum( );

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 11:39:04 2013-------*
    * @method  CdmValueEnum::GetDisplayString                // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:39:04 2013----------*/
      virtual QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:39:38 2013-------*
    * @method  CdmValueEnum::GetVariant                      // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 11:39:38 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:39:48 2013-------*
    * @method  CdmValueEnum::GetValueVariant                 // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:39:48 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 10:00:09 2012-------*
    * @method  CdmValueEnum::SetValueVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 10:00:09 2012----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 11:39:17 2013-------*
    * @method  CdmValueEnum::GetSelectionList                // public, const, slots              *
    * @return  QStringList                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:39:17 2013----------*/
QStringList GetSelectionList( ) const;
};

#endif //
