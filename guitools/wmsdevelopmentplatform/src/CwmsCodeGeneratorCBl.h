/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsCodeGeneratorCBl.h
 ** Started Implementation: 2012/06/05
 ** Description:
 ** 
 ** Implements the code generator for web interfaces.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCODEGENERATORCBL_H
#define CWMSCODEGENERATORCBL_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "CwmsCodeGeneratorCBase.h"


// Forwards
class CdmClass;

// TypeDefs


/* 
 * This class implements the code generator for web interfaces.
 */
class CwmsCodeGeneratorCBl : public CwmsCodeGeneratorCBase
{
   private:
      CdmClass* m_rpCdmClass;
      QStringList m_qstrlAbstractMethods;


   public:
   /** +-=---------------------------------------------------------Mi 6. Jun 10:53:35 2012--------*
    * @method  CwmsCodeGeneratorCBl::CwmsCodeGeneratorCBl    // public                            *
    * @return                                                //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrClassname                       //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QStringList p_qstrlAbstractMethods            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 10:53:35 2012-----------*/
    CwmsCodeGeneratorCBl( QString p_qstrFilename,
                          QString p_qstrClassname,
                          CdmClass* p_pCdmClass,
                          QStringList p_qstrlAbstractMethods);

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 11:21:14 2012--------*
    * @method  CwmsCodeGeneratorCBl::~CwmsCodeGeneratorCBl   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorCBl                                       *
    *----------------last changed: -----------------------------Di 5. Jun 11:21:14 2012-----------*/
    virtual ~CwmsCodeGeneratorCBl( );

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 11:24:16 2012--------*
    * @method  CwmsCodeGeneratorCBl::GenerateCode            // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:24:16 2012-----------*/
    void GenerateCode();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:24:22 2012--------*
    * @method  CwmsCodeGeneratorCBl::GenerateCodeP           // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:24:22 2012-----------*/
    void GenerateCodeP();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 13:36:19 2012--------*
    * @method  CwmsCodeGeneratorCBl::GenerateDefaultConstructorSource // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 13:36:19 2012-----------*/
    void GenerateDefaultConstructorSource();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 13:37:15 2012--------*
    * @method  CwmsCodeGeneratorCBl::GenerateDefaultConstructorHeader // private                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 13:37:15 2012-----------*/
    void GenerateDefaultConstructorHeader();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 13:54:55 2012--------*
    * @method  CwmsCodeGeneratorCBl::AddAbstractMethods      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 13:54:55 2012-----------*/
    void AddAbstractMethods();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 13:55:09 2012--------*
    * @method  CwmsCodeGeneratorCBl::AddValidateMethod       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 13:55:09 2012-----------*/
    void AddValidateMethod();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:24:41 2012--------*
    * @method  CwmsCodeGeneratorCBl::GenerateValidateHeader  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:24:41 2012-----------*/
    void GenerateValidateHeader();

   private:
   /** +-=---------------------------------------------------------Mi 6. Jun 15:29:05 2012--------*
    * @method  CwmsCodeGeneratorCBl::GenerateValidateSource  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 15:29:05 2012-----------*/
    void GenerateValidateSource();
};

#endif // CWMSCODEGENERATORCBL_H
