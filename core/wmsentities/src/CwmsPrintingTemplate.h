/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CbmsPrintingTemplate.h
 ** Started Implementation: 2010/11/03
 ** Description:
 ** 
 ** This class implements the printing template for one document
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSPRINTINGTEMPLATE_H
#define CWMSPRINTINGTEMPLATE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"


// Own Includes
#include "basetools.h"


// Forwards
class CdmClass;

// Enumerations
enum EwmsTemplateType
{
   eWmsTemplateTypeObject,
   eWmsTemplateTypeList
};

/* 
 * This class implements  the printing template for one document
 */
class BASETOOLS_API CwmsPrintingTemplate : public CdmObjectAdaptor
{

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:27:45 2012-------*
    * @method  CwmsPrintingTemplate::CwmsPrintingTemplate    // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:27:45 2012----------*/
    CwmsPrintingTemplate( CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:27:25 2012-------*
    * @method  CwmsPrintingTemplate::CwmsPrintingTemplate    // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:27:25 2012----------*/
    CwmsPrintingTemplate( );

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:28:14 2012-------*
    * @method  CwmsPrintingTemplate::~CwmsPrintingTemplate   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbmsPrintingTemplate                                       *
    *----------------last changed: -----------------------------Mo 27. Aug 10:28:14 2012----------*/
    virtual ~CwmsPrintingTemplate( );

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:28:20 2012-------*
    * @method  CwmsPrintingTemplate::GetName                 // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:28:20 2012----------*/
    QString GetName();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:28:25 2012-------*
    * @method  CwmsPrintingTemplate::SetName                 // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:28:25 2012----------*/
    void SetName(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 16:30:25 2012-------*
    * @method  CwmsPrintingTemplate::SetLanguage             // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_iId                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 16:30:25 2012----------*/
    virtual void SetLanguage(QString p_iId);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 16:30:36 2012-------*
    * @method  CwmsPrintingTemplate::GetLanguage             // public                            *
    * @return  QString                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 16:30:36 2012----------*/
    QString GetLanguage();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:28:44 2012-------*
    * @method  CwmsPrintingTemplate::GetLanguageId           // public                            *
    * @return  long                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:28:44 2012----------*/
    long GetLanguageId();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:28:49 2012-------*
    * @method  CwmsPrintingTemplate::SetTemplate             // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrContent                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:28:49 2012----------*/
    void SetTemplate(QString p_qstrContent);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:28:54 2012-------*
    * @method  CwmsPrintingTemplate::GetTemplate             // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:28:54 2012----------*/
    QString GetTemplate();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:29:07 2012-------*
    * @method  CwmsPrintingTemplate::ReadTemplateFromFile    // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:29:07 2012----------*/
    bool ReadTemplateFromFile(QString p_qstrFilename);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:29:13 2012-------*
    * @method  CwmsPrintingTemplate::SaveTemplateToFile      // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:29:13 2012----------*/
    bool SaveTemplateToFile(QString p_qstrFilename);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 11:24:35 2012-------*
    * @method  CwmsPrintingTemplate::SetClass                // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_rpCdmClass                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 11:24:35 2012----------*/
    void SetClass(CdmClass* p_rpCdmClass);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 16:32:28 2012-------*
    * @method  CwmsPrintingTemplate::GetClass                // public                            *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 16:32:28 2012----------*/
    CdmClass* GetClass();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 11:30:48 2012-------*
    * @method  CwmsPrintingTemplate::SetType                 // public                            *
    * @return  void                                          //                                   *
    * @param   EwmsTemplateType p_eWmsType                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 11:30:48 2012----------*/
    void SetType(EwmsTemplateType p_eWmsType);
    void SetType(int p_eWmsType);

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 11:32:01 2012-------*
    * @method  CwmsPrintingTemplate::GetType                 // public                            *
    * @return  EwmsTemplateType                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 11:32:01 2012----------*/
    EwmsTemplateType GetType();
    int GetTypeAsInt();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:29:40 2012-------*
    * @method  CwmsPrintingTemplate::IsDefault               // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:29:40 2012----------*/
    bool IsDefault();

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 10:29:46 2012-------*
    * @method  CwmsPrintingTemplate::SetDefault              // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bDefault                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 10:29:46 2012----------*/
    void SetDefault(bool p_bDefault);
};

#endif //
