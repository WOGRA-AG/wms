/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsGenerateWmsDefinitionCode.h
 ** Started Implementation: 2011/11/20
 ** Description:
 ** 
 ** This class implements the generator for wms definition code
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSGENERATEWMSDEFINITIONCODE_H
#define CWMSGENERATEWMSDEFINITIONCODE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QStringList>

// Own Includes
#include "CwmsCodeGeneratorCBase.h"

// Forwards
class CdmScheme;

// TypeDefs


/* 
 * This class implements  the generator for wms definition code
 */
class CwmsGenerateWmsDefinitionCode : public CwmsCodeGeneratorCBase
{
   private:
      CdmScheme* m_rpCdmDatabase;
      QStringList m_qstrlMethodsToCall;

   public:
   /** +-=---------------------------------------------------------Mo 21. Nov 14:54:27 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::CwmsGenerateWmsDefinitionCode // public             *
    * @return                                                //                                   *
    * @param   CdmDatabase* p_pCdmDatabase                   //                                   *
    * @param   QString p_qstrPath                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 14:54:27 2011----------*/
    CwmsGenerateWmsDefinitionCode( CdmScheme* p_pCdmDatabase, QString p_qstrPath);

   public:
   /** +-=---------------------------------------------------------Mo 21. Nov 14:45:36 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::~CwmsGenerateWmsDefinitionCode // public, virtual   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsGenerateWmsDefinitionCode                              *
    *----------------last changed: -----------------------------Mo 21. Nov 14:45:36 2011----------*/
    virtual ~CwmsGenerateWmsDefinitionCode( );

   public:
   /** +-=---------------------------------------------------------Mo 21. Nov 14:54:48 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateCode   // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 14:54:48 2011----------*/
    void GenerateCode();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:11:46 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateClassesCode // private                      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:11:46 2011----------*/
    void GenerateClassesCode();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:11:35 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateDatabaseCode // private                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:11:35 2011----------*/
    void GenerateDatabaseCode();

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 15:12:36 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateObjectListsCode // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 15:12:36 2011----------*/
    void GenerateObjectListsCode();

   private:
   /** +-=---------------------------------------------------------Di 22. Nov 18:58:26 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateConstructor // private                      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:58:26 2011----------*/
    void GenerateConstructor();

   private:
   /** +-=---------------------------------------------------------Di 22. Nov 18:58:41 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateDestructor // private                       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:58:41 2011----------*/
    void GenerateDestructor();

   private:
   /** +-=---------------------------------------------------------Di 22. Nov 19:18:39 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateConstructorSource // private                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:18:39 2011----------*/
    void GenerateConstructorSource();


   private:
   /** +-=---------------------------------------------------------Di 22. Nov 19:36:54 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::AddIncludesAndForwards // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:36:54 2011----------*/
    void AddIncludesAndForwards();

   private:
   /** +-=---------------------------------------------------------Mi 23. Nov 10:47:35 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateCreateClassesByNameCode // private          *
    * @return  void                                          //                                   *
    * @param   QList<CdmClass*>& p_rqllClasses         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 10:47:35 2011----------*/
    void GenerateCreateClassesByNameCode(QList<CdmClass*>& p_rqllClasses);

   private:
   /** +-=---------------------------------------------------------Mi 23. Nov 10:59:32 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateClassDetailsMethod // private               *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 10:59:32 2011----------*/
    void GenerateClassDetailsMethod(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:18:18 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::AddBaseClassCode // private                         *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:18:18 2011----------*/
    void AddBaseClassCode(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:31:49 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::AddMembers     // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:31:49 2011----------*/
    void AddMembers(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:32:27 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::AddMember      // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:32:27 2011----------*/
    void AddMember(CdmMember* p_pCdmMember);

   public:
   /** +-=---------------------------------------------------------Mi 23. Nov 12:24:36 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GetValueTypeAsString // public                      *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment This method generates from the Value a string translation.                         *
    *----------------last changed: -----------------------------Mi 23. Nov 12:24:36 2011----------*/
    QString GetValueTypeAsString(EdmValueType p_eDmValue);

   private:
   /** +-=---------------------------------------------------------Mi 23. Nov 12:38:07 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::AddDefaultValue // private                          *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 12:38:07 2011----------*/
    void AddDefaultValue(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Fr 25. Nov 15:36:47 2011-------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateDataStructureMethod // private              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 25. Nov 15:36:47 2011----------*/
    void GenerateDataStructureMethod();

   private:
   /** +-=---------------------------------------------------------Fr 2. Dez 12:49:27 2011--------*
    * @method  CwmsGenerateWmsDefinitionCode::GenerateObjectListMethod // private                 *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 2. Dez 12:49:27 2011-----------*/
    void GenerateObjectListMethod(CdmClass* p_pCdmClass);
};

#endif // CWMSGENERATEWMSDEFINITIONCODE_H
