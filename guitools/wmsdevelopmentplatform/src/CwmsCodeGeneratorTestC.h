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

#ifndef CWMSCODEGENERATORTESTC_H
#define CWMSCODEGENERATORTESTC_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QStringList>
#include <QMap>

// Own Includes
#include "CwmsCodeGeneratorC.h"
#include "CwmsCodeGeneratorCBase.h"
#include "CdmMember.h"

// Forwards
class CwmsCodeGeneratorC;


// TypeDefs



/* 
 * This This class generates c++ interface code for classes.
 */
class CwmsCodeGeneratorTestC : public CwmsCodeGeneratorCBase
{
   private:
      CwmsCodeGeneratorC* m_pCodeGenerator;
      CdmClass* m_rpCdmClass;
      QStringList m_qstrlTestMethods;


   public:
   /** +-=---------------------------------------------------------Fr 8. Jun 13:47:39 2012--------*
    * @method  CwmsCodeGeneratorTestC::CwmsCodeGeneratorTestC // public                           *
    * @return                                                //                                   *
    * @param   CwmsCodeGeneratorC* p_pCodeGenerator          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 13:47:39 2012-----------*/
    CwmsCodeGeneratorTestC( CwmsCodeGeneratorC* p_pCodeGenerator,
                            QString p_qstrFilename,
                            QString p_qstrClassName,
                            CdmClass* p_pCdmClass);

   public:
   /** +-=---------------------------------------------------------Fr 2. Dez 16:01:52 2011--------*
    * @method  CwmsCodeGeneratorTestC::~CwmsCodeGeneratorTestC // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorC                                         *
    *----------------last changed: -----------------------------Fr 2. Dez 16:01:52 2011-----------*/
    virtual ~CwmsCodeGeneratorTestC( );

   public:
   /** +-=---------------------------------------------------------Fr 2. Dez 16:02:37 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateCode          // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 2. Dez 16:02:37 2011-----------*/
    void GenerateCode();

   private:
   /** +-=---------------------------------------------------------Mo 5. Dez 11:06:48 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateConstructor   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 11:06:48 2011-----------*/
    void GenerateConstructor();

   private:
   /** +-=---------------------------------------------------------Fr 2. Dez 16:06:53 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateDestructor    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 2. Dez 16:06:53 2011-----------*/
    void GenerateDestructor();

   public:
   /** +-=---------------------------------------------------------Sa 3. Dez 09:32:12 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateTestCodeForMembers // public                       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 3. Dez 09:32:12 2011-----------*/
    void GenerateTestCodeForMembers();

   private:
   /** +-=---------------------------------------------------------Sa 3. Dez 09:26:13 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateCreateTestObjectListMethod // private              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 3. Dez 09:26:13 2011-----------*/
    void GenerateCreateTestObjectListMethod();

   private:
   /** +-=---------------------------------------------------------Sa 3. Dez 09:26:42 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateCreateTestObjectClassMethod // private             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 3. Dez 09:26:42 2011-----------*/
    void GenerateCreateTestObjectClassMethod();

   private:
   /** +-=---------------------------------------------------------Sa 3. Dez 09:30:55 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateDeleteTestObjectListMethod // private              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 3. Dez 09:30:55 2011-----------*/
    void GenerateDeleteTestObjectListMethod();

   private:
   /** +-=---------------------------------------------------------Sa 3. Dez 09:31:00 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateDeleteTestObjectClassMethod // private             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 3. Dez 09:31:00 2011-----------*/
    void GenerateDeleteTestObjectClassMethod();

   private:
   /** +-=---------------------------------------------------------Mo 5. Dez 11:04:28 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateConstructorSource // private                       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 11:04:28 2011-----------*/
    void GenerateConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mo 5. Dez 11:08:33 2011--------*
    * @method  CwmsCodeGeneratorTestC::AddIncludesAndForwards // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 11:08:33 2011-----------*/
    void AddIncludesAndForwards();

    private slots:
   /** +-=---------------------------------------------------------Mo 5. Dez 12:56:44 2011--------*
    * @method  CwmsCodeGeneratorTestC::GenerateTestSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 12:56:44 2011-----------*/
void GenerateTestSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 5. Dez 14:52:38 2011--------*
    * @method  CwmsCodeGeneratorTestC::CreateMemberTestMethod // private                          *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 14:52:38 2011-----------*/
    void CreateMemberTestMethod(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Mo 5. Dez 15:14:20 2011--------*
    * @method  CwmsCodeGeneratorTestC::ReadTestData          // private                           *
    * @return  void                                          //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @param   QStringList& p_rqstrlTestData                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 15:14:20 2011-----------*/
    void ReadTestData(EdmValueType p_eDmValue, QStringList& p_rqstrlTestData);
};

#endif // CWMSCODEGENERATORC_H
