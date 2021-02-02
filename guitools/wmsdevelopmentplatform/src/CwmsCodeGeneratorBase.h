/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsCodeGeneratorBase.h
 ** Started Implementation: 2012/07/13
 ** Description:
 ** 
 ** Implements the language independent base class for code generation
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCODEGENERATORBASE_H
#define CWMSCODEGENERATORBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// WMS Includes
#include "CdmModelElement.h"

// Own Includes
#include "IwmsCodeGenerator.h"

// Forwards
class CdmMember;
class CdmClass;

// TypeDefs


/* 
 * This class implements the language independent base class for code generation
 */
class CwmsCodeGeneratorBase : public IwmsCodeGenerator
{


   public:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:44:00 2012-------*
    * @method  CwmsCodeGeneratorBase::CwmsCodeGeneratorBase  // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 09:44:00 2012----------*/
    CwmsCodeGeneratorBase( );

   public:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:44:09 2012-------*
    * @method  CwmsCodeGeneratorBase::~CwmsCodeGeneratorBase // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorBase                                      *
    *----------------last changed: -----------------------------Fr 13. Jul 09:44:09 2012----------*/
    virtual ~CwmsCodeGeneratorBase( );

   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:44:35 2012-------*
    * @method  CwmsCodeGeneratorBase::SaveFile               // protected                         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrContent                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 09:44:35 2012----------*/
    void SaveFile(QString p_qstrFilename, QString p_qstrContent);

   protected:
   /** +-=---------------------------------------------------------Mo 23. Jul 10:24:05 2012-------*
    * @method  CwmsCodeGeneratorBase::GenerateCodeMemberName // protected                         *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jul 10:24:05 2012----------*/
    QString GenerateCodeMemberName(QString p_qstrMember);


   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:50:11 2012-------*
    * @method  CwmsCodeGeneratorBase::AddIndent              // protected                         *
    * @return  QString                                       //                                   *
    * @param   int p_iIndentStage                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 09:50:11 2012----------*/
    QString AddIndent(int p_iIndentStage);

   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 13:23:20 2012-------*
    * @method  CwmsCodeGeneratorBase::CheckSetterMethod      // protected                         *
    * @return  bool                                          //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 13:23:20 2012----------*/
    bool CheckSetterMethod(EdmValueType p_eDmValue);

   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 13:36:21 2012-------*
    * @method  CwmsCodeGeneratorBase::CheckGetterMethod      // protected                         *
    * @return  bool                                          //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 13:36:21 2012----------*/
    bool CheckGetterMethod(EdmValueType p_eDmValue);

   protected:
   /** +-=---------------------------------------------------------Mi 18. Jul 08:42:40 2012-------*
    * @method  CwmsCodeGeneratorBase::GetClassMembers        // protected                         *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   bool p_bIncludeBaseClassMembers               //                                   *
    * @param   QMap<long, CdmMember*>& p_rqmMembers          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Jul 08:42:40 2012----------*/
    void GetClassMembers(CdmClass* p_pCdmClass,
                         bool p_bIncludeBaseClassMembers,
                         QMap<long,
                         CdmMember*>& p_rqmMembers);
};

#endif // CWMSCODEGENERATORBASE_H
