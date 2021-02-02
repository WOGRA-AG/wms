/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsCodeGeneratorC.h
 ** Started Implementation: 2011/11/09
 ** Description:
 ** 
 ** This class generates c++ interface code for classes.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCODEGENERATORC_H
#define CWMSCODEGENERATORC_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QMap>

// Own Includes
#include "CwmsCodeGeneratorCBase.h"
#include "CdmMember.h"

// Forwards
class CdmClass;
class CwmsCodeGeneratorTestC;

// TypeDefs

// enumerations
enum EwmsCodeGenerationMethodType
{
   eWmsCodeGenerationMethodTypeSetter,
   eWmsCodeGenerationMethodTypeGetter
};


/* 
 * This This class generates c++ interface code for classes.
 */
class CwmsCodeGeneratorC : public CwmsCodeGeneratorCBase
{
   private:
      CdmClass* m_rpCdmClass;
      bool m_bCreateBaseClassMemberFunctions;
      bool m_bGenerateStandardObjectList;
      bool m_bGenerateTestCode;
      bool m_bGenerateBusinessLogicClass;
      bool m_bGenerateTempClass;
      bool m_bGenerateWebInterface;
      QString m_qstrWebInterfaceClassName;
      QString m_qstrWebInterfaceOLKeyname;
      QStringList m_qstrListAbstractFunctionsForBaseClass;

   public:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:14:00 2011-------*
    * @method  CwmsCodeGeneratorC::CwmsCodeGeneratorC        // public                            *
    * @return                                                //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:14:00 2011----------*/
    CwmsCodeGeneratorC( CdmClass* p_pCdmClass, QString p_qstrClassName, QString p_qstrFilename);

   public:
   /** +-=---------------------------------------------------------Mi 9. Nov 14:35:38 2011--------*
    * @method  CwmsCodeGeneratorC::~CwmsCodeGeneratorC       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorC                                         *
    *----------------last changed: -----------------------------Mi 9. Nov 14:35:38 2011-----------*/
    virtual ~CwmsCodeGeneratorC( );

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:15:45 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateCodeP             // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:15:45 2011----------*/
    void GenerateCodeP();

   public:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:15:07 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateCode              // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:15:07 2011----------*/
    void GenerateCode();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:16:19 2011-------*
    * @method  CwmsCodeGeneratorC::GeneratesConstructors     // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:16:19 2011----------*/
    void GeneratesConstructors();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:20:10 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDestructors       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:20:10 2011----------*/
    void GenerateDestructors();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:20:24 2011-------*
    * @method  CwmsCodeGeneratorC::GeneratesMemberAccess     // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:20:24 2011----------*/
    void GeneratesMemberAccess();

   private:
   /** +-=---------------------------------------------------------Mi 9. Nov 15:16:17 2011--------*
    * @method  CwmsCodeGeneratorC::GenerateMethodInHeader    // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmMemberAccess p_eAccessType                 //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @param   EwmsCodeGenerationMethodType p_eType          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 15:16:17 2011-----------*/
    void GenerateMethodInHeader(QString p_qstrMethodName,
                                EdmMemberAccess p_eAccessType,
                                EdmValueType p_eReturnValue,
                                EwmsCodeGenerationMethodType p_eType);

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:16:46 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateMethodInSource    // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @param   EwmsCodeGenerationMethodType p_eType          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:16:46 2011----------*/
    void GenerateMethodInSource(QString p_qstrMethodName,
                                EdmValueType p_eReturnValue,
                                EwmsCodeGenerationMethodType p_eType);

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:19:01 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDefaultConstructorSource // private                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:19:01 2011----------*/
    void GenerateDefaultConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:19:37 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateParameterConstructorSource // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:19:37 2011----------*/
    void GenerateParameterConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:19:24 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDefaultConstructorHeader // private                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:19:24 2011----------*/
    void GenerateDefaultConstructorHeader();

   private:
   /** +-=---------------------------------------------------------Di 22. Nov 18:53:46 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateParameterConstructorHeader // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:53:46 2011----------*/
    void GenerateParameterConstructorHeader();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:18:34 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDestructorHeader  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:18:34 2011----------*/
    void GenerateDestructorHeader();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:18:47 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDestructorSource  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:18:47 2011----------*/
    void GenerateDestructorSource();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:17:04 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateSetterSource      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:17:04 2011----------*/
    void GenerateSetterSource(QString p_qstrMember, EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:17:44 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateGetterSource      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:17:44 2011----------*/
    void GenerateGetterSource(QString p_qstrMember, EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------Mi 9. Nov 16:33:12 2011--------*
    * @method  CwmsCodeGeneratorC::GenerateSetterHeader      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmMemberAccess p_eAccessType                 //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 16:33:12 2011-----------*/
    void GenerateSetterHeader(QString p_qstrMethodName,
                              EdmMemberAccess p_eAccessType,
                              EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------Mi 9. Nov 16:33:17 2011--------*
    * @method  CwmsCodeGeneratorC::GenerateGetterHeader      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmMemberAccess p_eAccessType                 //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 16:33:17 2011-----------*/
    void GenerateGetterHeader(QString p_qstrMethodName,
                              EdmMemberAccess p_eAccessType,
                              EdmValueType p_eReturnValue);



   private:
   /** +-=---------------------------------------------------------Mi 9. Nov 16:56:21 2011--------*
    * @method  CwmsCodeGeneratorC::GenerateGetterCode        // private                           *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 16:56:21 2011-----------*/
    QString GenerateGetterCode(EdmValueType p_eDmValue, QString p_qstrMember);


   private:
   /** +-=---------------------------------------------------------Mi 9. Nov 17:43:54 2011--------*
    * @method  CwmsCodeGeneratorC::GenerateSetterCode        // private                           *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 17:43:54 2011-----------*/
    QString GenerateSetterCode(EdmValueType p_eReturnValue, QString p_qstrMember);




   public:
   /** +-=---------------------------------------------------------Mi 9. Nov 19:17:25 2011--------*
    * @method  CwmsCodeGeneratorC::SetCreateBaseClassMemberFunctions // public                    *
    * @return  void                                          //                                   *
    * @param   bool p_bCreate                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Nov 19:17:25 2011-----------*/
    void SetCreateBaseClassMemberFunctions(bool p_bCreate);


   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:21:23 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateMemberAccess      // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:21:23 2011----------*/
    void GenerateMemberAccess(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:21:06 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateAllMembersAccess  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:21:06 2011----------*/
    void GenerateAllMembersAccess();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:20:41 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateClassMembersAccess // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:20:41 2011----------*/
    void GenerateClassMembersAccess();



   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:22:38 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateCreateMethod      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:22:38 2011----------*/
    void GenerateCreateMethod();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:24:03 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateCreateMethodSource // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:24:03 2011----------*/
    void GenerateCreateMethodSource();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:24:33 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateCreateMethodHeader // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:24:33 2011----------*/
    void GenerateCreateMethodHeader();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:22:50 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDeleteMethod      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:22:50 2011----------*/
    void GenerateDeleteMethod();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:23:44 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDeleteMethodHeader // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:23:44 2011----------*/
    void GenerateDeleteMethodHeader();

   public:
   /** +-=---------------------------------------------------------Fr 18. Nov 15:30:30 2011-------*
    * @method  CwmsCodeGeneratorC::SetGenerateStandardObjectList // public                        *
    * @return  void                                          //                                   *
    * @param   bool p_bStandard                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 18. Nov 15:30:30 2011----------*/
    void SetGenerateStandardObjectList(bool p_bStandard);

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:24:55 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateStandardObjectList // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:24:55 2011----------*/
    void GenerateStandardObjectList();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:23:16 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateDeleteMethodSource // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:23:16 2011----------*/
    void GenerateDeleteMethodSource();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:25:24 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateStandardObjectListSource // private                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrObjListName                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:25:24 2011----------*/
    void GenerateStandardObjectListSource(QString p_qstrObjListName);

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:25:52 2011-------*
    * @method  CwmsCodeGeneratorC::GenerateStandardObjectListHeader // private                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:25:52 2011----------*/
    void GenerateStandardObjectListHeader();

   public:
   /** +-=---------------------------------------------------------Fr 2. Dez 15:47:35 2011--------*
    * @method  CwmsCodeGeneratorC::SetGenerateTestCode       // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bGenerate                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 2. Dez 15:47:35 2011-----------*/
    void SetGenerateTestCode(bool p_bGenerate);

   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 10:40:21 2012--------*
    * @method  CwmsCodeGeneratorC::SetGenerateBusinessLogicCode // public                         *
    * @return  void                                          //                                   *
    * @param   bool p_bGenerate                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 10:40:21 2012-----------*/
    void SetGenerateBusinessLogicCode(bool p_bGenerate);

   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 10:42:40 2012--------*
    * @method  CwmsCodeGeneratorC::SetGenerateTempClassCode  // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bGenerate                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 10:42:40 2012-----------*/
    void SetGenerateTempClassCode(bool p_bGenerate);

   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 10:43:12 2012--------*
    * @method  CwmsCodeGeneratorC::SetGenerateWebInterfaceCode // public                          *
    * @return  void                                          //                                   *
    * @param   bool p_bGenerate                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 10:43:12 2012-----------*/
    void SetGenerateWebInterfaceCode(bool p_bGenerate);


   private:
   /** +-=---------------------------------------------------------Fr 8. Jun 10:18:09 2012--------*
    * @method  CwmsCodeGeneratorC::GenerateStandardObjectListKeyname // private                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 10:18:09 2012-----------*/
    QString GenerateStandardObjectListKeyname();

   public:
   /** +-=---------------------------------------------------------Fr 8. Jun 10:20:24 2012--------*
    * @method  CwmsCodeGeneratorC::SetWebInterfaceClassName  // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 10:20:24 2012-----------*/
    void SetWebInterfaceClassName(QString p_qstrClassName);

   public:
   /** +-=---------------------------------------------------------Fr 8. Jun 10:20:47 2012--------*
    * @method  CwmsCodeGeneratorC::SetWebInterfaceObjectListName // public                        *
    * @return  void                                          //                                   *
    * @param   QString p_qstrOLName                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 10:20:47 2012-----------*/
    void SetWebInterfaceObjectListName(QString p_qstrOLName);

   private:
   /** +-=---------------------------------------------------------Fr 8. Jun 16:51:54 2012--------*
    * @method  CwmsCodeGeneratorC::GenerateCreateMethodSourceWithoutParameter // private          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 16:51:54 2012-----------*/
    void GenerateCreateMethodSourceWithoutParameter();

   private:
   /** +-=---------------------------------------------------------Fr 8. Jun 16:52:11 2012--------*
    * @method  CwmsCodeGeneratorC::GenerateCreateMethodHeaderWithoutParameter // private          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 16:52:11 2012-----------*/
    void GenerateCreateMethodHeaderWithoutParameter();
};

#endif // CWMSCODEGENERATORC_H
