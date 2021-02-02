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

#ifndef CDMVALUEUSERGROUP_H
#define CDMVALUEUSERGROUP_H

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
class WMSMANAGER_API CdmValueUserGroup : public CdmValueInt
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 10:29:08 2012-------*
    * @method  CdmValueUserGroup::CdmValueUserGroup          // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value keyname                     *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The Userconstructor                                                                *
    *----------------last changed: -----------------------------Di 28. Aug 10:29:08 2012----------*/
    CdmValueUserGroup( long p_lDatabaseId,
                       long p_lId,
                       QString p_qstrKeyname,
                       CdmObject* p_pCdmObject);


   public:
   /** +-=---------------------------------------------------------Di 28. Aug 10:30:02 2012-------*
    * @method  CdmValueUserGroup::CdmValueUserGroup          // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Source                        *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The integer constructor.                                                           *
    *----------------last changed: -----------------------------Di 28. Aug 10:30:02 2012----------*/
    CdmValueUserGroup( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 10:30:07 2012-------*
    * @method  CdmValueUserGroup::CdmValueUserGroup          // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 10:30:07 2012----------*/
    CdmValueUserGroup( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 10:30:13 2012-------*
    * @method  CdmValueUserGroup::~CdmValueUserGroup         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueUserGroup                                          *
    *----------------last changed: -----------------------------Di 28. Aug 10:30:13 2012----------*/
    virtual ~CdmValueUserGroup( );

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 12:02:41 2012-------*
    * @method  CdmValueUserGroup::GetUserGroup               // public, slots                     *
    * @return  CumUserGroup*                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 12:02:41 2012----------*/
CumUserGroup* GetUserGroup( );

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 12:02:50 2012-------*
    * @method  CdmValueUserGroup::SetUserGroup               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CumUserGroup* p_pCumUserGroup                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 12:02:50 2012----------*/
void SetUserGroup( CumUserGroup* p_pCumUserGroup);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 11:42:50 2013-------*
    * @method  CdmValueUserGroup::GetDisplayString           // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:42:50 2013----------*/
      virtual QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:42:58 2013-------*
    * @method  CdmValueUserGroup::GetVariant                 // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 11:42:58 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:43:06 2013-------*
    * @method  CdmValueUserGroup::GetValueVariant            // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:43:06 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Di 28. Aug 10:33:21 2012-------*
    * @method  CdmValueUserGroup::SetValueVariant            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Aug 10:33:21 2012----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);
};

#endif //
