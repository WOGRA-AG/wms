/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsCodeGeneratorCTemp.h
 ** Started Implementation: 2012/06/06
 ** Description:
 ** 
 ** Generates the code for a temporary class for doing validations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCODEGENERATORCTEMP_H
#define CWMSCODEGENERATORCTEMP_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CwmsCodeGeneratorC.h"
#include "CwmsCodeGeneratorCBase.h"

// Forwards
class CdmClass;

// TypeDefs


/* 
 * This class implements the generator for a temporary class for doing validations without saving
 */
class CwmsCodeGeneratorCTemp : public CwmsCodeGeneratorCBase
{
   private:
      CdmClass* m_rpCdmClass;
      bool m_bCreateBaseClassMemberFunctions;
      QString m_qstrClassNameTwin;
      QString m_qstrBaseClassName;
      QStringList m_qstrlMembers;
   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:31:33 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateMemberAccess  // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:31:33 2012-----------*/
    void GenerateMemberAccess(CdmMember* p_pCdmMember);


   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 18:07:01 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateMembersAccess // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<long, CdmMember*>& p_rMap                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 18:07:01 2012-----------*/
    void GenerateMembersAccess(QMap<long, CdmMember*>& p_rMap);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:32:55 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GeneratesMemberAccess // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:32:55 2012-----------*/
    void GeneratesMemberAccess();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:33:05 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateDestructors   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:33:05 2012-----------*/
    void GenerateDestructors();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:33:16 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateParameterConstructorHeader // private              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:33:16 2012-----------*/
    void GenerateParameterConstructorHeader();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:33:39 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateParameterConstructorSource // private              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:33:39 2012-----------*/
    void GenerateParameterConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:33:51 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateDefaultConstructorHeader // private                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:33:51 2012-----------*/
    void GenerateDefaultConstructorHeader();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:34:02 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateDefaultConstructorSource // private                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:34:02 2012-----------*/
    void GenerateDefaultConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:34:12 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateDestructorSource // private                        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:34:12 2012-----------*/
    void GenerateDestructorSource();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:34:21 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateDestructorHeader // private                        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:34:21 2012-----------*/
    void GenerateDestructorHeader();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:34:35 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateGetterHeader  // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmMemberAccess p_eAccessType                 //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:34:35 2012-----------*/
    void GenerateGetterHeader(QString p_qstrMethodName,
                              EdmMemberAccess p_eAccessType,
                              EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:34:45 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateSetterHeader  // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmMemberAccess p_eAccessType                 //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:34:45 2012-----------*/
    void GenerateSetterHeader(QString p_qstrMethodName,
                              EdmMemberAccess p_eAccessType,
                              EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------So 4. Nov 09:17:19 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateGetterCode    // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 09:17:19 2012-----------*/
    QString GenerateGetterCode(QString p_qstrMember);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:35:08 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GetReturnType         // private                           *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:35:08 2012-----------*/
    QString GetReturnType(EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:35:20 2012--------*
    * @method  CwmsCodeGeneratorCTemp::CheckGetterMethod     // private                           *
    * @return  bool                                          //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:35:20 2012-----------*/
    bool CheckGetterMethod(EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:35:32 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateGetterSource  // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:35:32 2012-----------*/
    void GenerateGetterSource(QString p_qstrMember, EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:35:43 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GetParameter          // private                           *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:35:43 2012-----------*/
    QString GetParameter(EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:35:52 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateSetterCode    // private                           *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:35:52 2012-----------*/
    QString GenerateSetterCode(EdmValueType p_eReturnValue, QString p_qstrMember);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:00 2012--------*
    * @method  CwmsCodeGeneratorCTemp::CheckSetterMethod     // private                           *
    * @return  bool                                          //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:00 2012-----------*/
    bool CheckSetterMethod(EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:06 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateSetterSource  // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:06 2012-----------*/
    void GenerateSetterSource(QString p_qstrMember, EdmValueType p_eReturnValue);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:12 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateMethodInSource // private                          *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @param   EwmsCodeGenerationMethodType p_eType          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:12 2012-----------*/
    void GenerateMethodInSource(QString p_qstrMethodName,
                                EdmValueType p_eReturnValue,
                                EwmsCodeGenerationMethodType p_eType);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:25 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateMethodInHeader // private                          *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   EdmMemberAccess p_eAccessType                 //                                   *
    * @param   EdmValue p_eReturnValue                       //                                   *
    * @param   EwmsCodeGenerationMethodType p_eType          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:25 2012-----------*/
    void GenerateMethodInHeader(QString p_qstrMethodName,
                                EdmMemberAccess p_eAccessType,
                                EdmValueType p_eReturnValue,
                                EwmsCodeGenerationMethodType p_eType);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:34 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GeneratesConstructors // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:34 2012-----------*/
    void GeneratesConstructors();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:39 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCodeP         // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:39 2012-----------*/
    void GenerateCodeP();

   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:43 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCode          // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:43 2012-----------*/
    void GenerateCode();


   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:36:53 2012--------*
    * @method  CwmsCodeGeneratorCTemp::SetCreateBaseClassMemberFunctions // public                *
    * @return  void                                          //                                   *
    * @param   bool p_bCreate                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:36:53 2012-----------*/
    void SetCreateBaseClassMemberFunctions(bool p_bCreate);


   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:46:01 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorSource // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:46:01 2012-----------*/
    void GenerateCopyConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:46:17 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorHeader // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:46:17 2012-----------*/
    void GenerateCopyConstructorHeader();

   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 17:37:54 2012--------*
    * @method  CwmsCodeGeneratorCTemp::CwmsCodeGeneratorCTemp // public                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrClassNameTwin                   //                                   *
    * @param   QString p_qstrBaseClassName                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 17:37:54 2012-----------*/
    CwmsCodeGeneratorCTemp( CdmClass* p_pCdmClass,
                            QString p_qstrClassName,
                            QString p_qstrFilename,
                            QString p_qstrClassNameTwin,
                            QString p_qstrBaseClassName);

   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 16:27:37 2012--------*
    * @method  CwmsCodeGeneratorCTemp::~CwmsCodeGeneratorCTemp // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorC                                         *
    *----------------last changed: -----------------------------Mi 6. Jun 16:27:37 2012-----------*/
    virtual ~CwmsCodeGeneratorCTemp( );

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 16:38:49 2012--------*
    * @method  CwmsCodeGeneratorCTemp::AddMemberString       // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 16:38:49 2012-----------*/
    void AddMemberString(QString p_qstrMember);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 17:35:59 2012--------*
    * @method  CwmsCodeGeneratorCTemp::AddMembersToHeader    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 17:35:59 2012-----------*/
    void AddMembersToHeader();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 17:36:33 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructor // private                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 17:36:33 2012-----------*/
    void GenerateCopyConstructor();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 17:47:00 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorMembers // private                  *
    * @return  void                                          //                                   *
    * @param   QMap<long, CdmMember*>& p_rMap                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 17:47:00 2012-----------*/
    void GenerateCopyConstructorMembers(QMap<long, CdmMember*>& p_rMap);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 17:47:18 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorMember // private                   *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 17:47:18 2012-----------*/
    void GenerateCopyConstructorMember(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 17:48:27 2012--------*
    * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorMembers // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 17:48:27 2012-----------*/
    void GenerateCopyConstructorMembers();
};

#endif // CWMSCODEGENERATORCTEMP_H
