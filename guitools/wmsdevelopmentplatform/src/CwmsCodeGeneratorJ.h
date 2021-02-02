/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsCodeGeneratorJ.h
 ** Started Implementation: 2012/07/12
 ** Description:
 ** 
 ** Implements the generator for java
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCODEGENERATORJ_H
#define CWMSCODEGENERATORJ_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QStringList>

// Own Includes
#include "CwmsCodeGeneratorBase.h"

// Forwards
class CdmClass;
class CdmMember;

// TypeDefs


/* 
 * This class implements the generator for java
 */
class CwmsCodeGeneratorJ : public CwmsCodeGeneratorBase
{
   private:
    CdmClass* m_rpCdmClass;
    QString m_qstrClassName;
    QString m_qstrPackage;
    QString m_qstrObjectListKeyname;
    QString m_qstrFilePath;
    QString m_qstrBaseClassName;
      QString m_qstrSource;
      QStringList m_qstrlStrings;
      QStringList m_qstrlDoubles;
      QStringList m_qstrlInts;
      QStringList m_qstrlBools;
      QStringList m_qstrlFloats;



   public:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:33:52 2012-------*
    * @method  CwmsCodeGeneratorJ::CwmsCodeGeneratorJ        // public                            *
    * @return                                                //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   QString p_qstrPackage                         //                                   *
    * @param   QString p_qstrObjectListName                  //                                   *
    * @param   QString p_qstrStorePath                       //                                   *
    * @param   QString p_qstrBaseClassName                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:33:52 2012----------*/
    CwmsCodeGeneratorJ( CdmClass* p_pCdmClass,
                        QString p_qstrClassName,
                        QString p_qstrPackage,
                        QString p_qstrObjectListName,
                        QString p_qstrStorePath,
                        QString p_qstrBaseClassName);

   public:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:35:16 2012-------*
    * @method  CwmsCodeGeneratorJ::GenerateCode              // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 09:35:16 2012----------*/
    void GenerateCode();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:36:35 2012-------*
    * @method  CwmsCodeGeneratorJ::GenerateCodeP             // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 09:36:35 2012----------*/
    void GenerateCodeP();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:46:13 2012-------*
    * @method  CwmsCodeGeneratorJ::SaveFiles                 // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 09:46:13 2012----------*/
    void SaveFiles();

   public:
   /** +-=---------------------------------------------------------Fr 13. Jul 09:40:35 2012-------*
    * @method  CwmsCodeGeneratorJ::~CwmsCodeGeneratorJ       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorJ                                         *
    *----------------last changed: -----------------------------Fr 13. Jul 09:40:35 2012----------*/
    virtual ~CwmsCodeGeneratorJ( );

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:05:31 2012-------*
    * @method  CwmsCodeGeneratorJ::AddImportPackage          // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrPackage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:05:31 2012----------*/
    void AddImportPackage(QString p_qstrPackage);

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:06:41 2012-------*
    * @method  CwmsCodeGeneratorJ::SetPackage                // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:06:41 2012----------*/
    void SetPackage();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:08:07 2012-------*
    * @method  CwmsCodeGeneratorJ::OpenClass                 // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:08:07 2012----------*/
    void OpenClass();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:08:57 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateConstructors        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:08:57 2012----------*/
    void CreateConstructors();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:09:28 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateDefaultConstructor  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:09:28 2012----------*/
    void CreateDefaultConstructor();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:09:36 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateJSonConstructor     // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:09:36 2012----------*/
    void CreateJSonConstructor();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:10:37 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateMemberMethods       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:10:37 2012----------*/
    void CreateMemberMethods();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:11:04 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateClassMembers        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:11:04 2012----------*/
    void CreateClassMembers();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:12:07 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetter              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:12:07 2012----------*/
    void CreateSetter(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:12:30 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetter              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:12:30 2012----------*/
    void CreateGetter(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:13:14 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetJSonMethod       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:13:14 2012----------*/
    void CreateGetJSonMethod();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:15:11 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetMemberMapMethod  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:15:11 2012----------*/
    void CreateGetMemberMapMethod();


   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:15:33 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateCommitMethod        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:15:33 2012----------*/
    void CreateCommitMethod();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:15:43 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateDeleteMethod        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:15:43 2012----------*/
    void CreateDeleteMethod();

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 10:31:08 2012-------*
    * @method  CwmsCodeGeneratorJ::CloseClass                // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 10:31:08 2012----------*/
    void CloseClass();

   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 14:17:54 2012-------*
    * @method  CwmsCodeGeneratorJ::GetReturnType             // protected                         *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 14:17:54 2012----------*/
    QString GetReturnType(EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Fr 13. Jul 14:18:05 2012-------*
    * @method  CwmsCodeGeneratorJ::GetParameter              // private                           *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 14:18:05 2012----------*/
    QString GetParameter(EdmValueType p_eDmValue);

   protected:
   /** +-=---------------------------------------------------------Mo 16. Jul 10:50:07 2012-------*
    * @method  CwmsCodeGeneratorJ::GetJsonType               // protected                         *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Jul 10:50:07 2012----------*/
    QString GetJsonType(EdmValueType p_eDmValue);

   public:
   /** +-=---------------------------------------------------------Mi 18. Jul 08:39:54 2012-------*
    * @method  CwmsCodeGeneratorJ::GetJsonCast               // public                            *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Jul 08:39:54 2012----------*/
    QString GetJsonCast(EdmValueType p_eDmValue);

   public:
   /** +-=---------------------------------------------------------Mi 18. Jul 08:40:02 2012-------*
    * @method  CwmsCodeGeneratorJ::GetJsonFunction           // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrJsonType                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Jul 08:40:02 2012----------*/
    QString GetJsonFunction(QString p_qstrJsonType);

   private:
   /** +-=---------------------------------------------------------Mi 18. Jul 13:36:17 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateConstructorAssignment // private                         *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Jul 13:36:17 2012----------*/
    void CreateConstructorAssignment(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Mo 23. Jul 12:02:13 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateDictionaryConstructorAssignment // private               *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jul 12:02:13 2012----------*/
    void CreateDictionaryConstructorAssignment(QString p_qstrKeyname, EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mo 23. Jul 16:43:34 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateListConstructorAssignment // private                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jul 16:43:34 2012----------*/
    void CreateListConstructorAssignment(QString p_qstrKeyname, EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mo 23. Jul 17:43:32 2012-------*
    * @method  CwmsCodeGeneratorJ::PutMemberToJsonObject     // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jul 17:43:32 2012----------*/
    void PutMemberToJsonObject(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 11:17:00 2012-------*
    * @method  CwmsCodeGeneratorJ::PutDictonaryMembersToJsonObject // private                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 11:17:00 2012----------*/
    void PutDictonaryMembersToJsonObject(QString p_qstrKeyname, EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 11:17:16 2012-------*
    * @method  CwmsCodeGeneratorJ::PutListMembersToJsonObject // private                          *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 11:17:16 2012----------*/
    void PutListMembersToJsonObject(QString p_qstrKeyname, EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 13:24:45 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetStringValueMethod // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 13:24:45 2012----------*/
    void CreateGetStringValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 13:24:53 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetIntValueMethod   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 13:24:53 2012----------*/
    void CreateGetIntValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 13:25:18 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetDoubleValueMethod // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 13:25:18 2012----------*/
    void CreateGetDoubleValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 13:26:37 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetBoolValueMethod  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 13:26:37 2012----------*/
    void CreateGetBoolValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 13:52:03 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateGetFloatValueMethod // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 13:52:03 2012----------*/
    void CreateGetFloatValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 14:01:27 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetStringValueMethod // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 14:01:27 2012----------*/
    void CreateSetStringValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 14:02:54 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetValueMethod      // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrType                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 14:02:54 2012----------*/
    void CreateSetValueMethod(QString p_qstrType);

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 14:06:29 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetBoolValueMethod  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 14:06:29 2012----------*/
    void CreateSetBoolValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 14:06:47 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetDoubleValueMethod // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 14:06:47 2012----------*/
    void CreateSetDoubleValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 14:07:39 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetFloatValueMethod // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 14:07:39 2012----------*/
    void CreateSetFloatValueMethod();

   private:
   /** +-=---------------------------------------------------------Di 24. Jul 14:07:55 2012-------*
    * @method  CwmsCodeGeneratorJ::CreateSetIntValueMethod   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 14:07:55 2012----------*/
    void CreateSetIntValueMethod();

   protected:
   /** +-=---------------------------------------------------------Di 24. Jul 15:40:10 2012-------*
    * @method  CwmsCodeGeneratorJ::GetDefaultValue           // protected                         *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 24. Jul 15:40:10 2012----------*/
    QString GetDefaultValue(EdmValueType p_eDmValue);
};

#endif // CWMSCODEGENERATORJ_H
