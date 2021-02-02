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

#ifndef CWMSCODEGENERATORCWEBIF_H
#define CWMSCODEGENERATORCWEBIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// Own Includes
#include "CwmsCodeGeneratorCBase.h"


// Forwards
class CdmClass;

// TypeDefs


/* 
* This class implements the code generator for web interfaces.
*/
class CwmsCodeGeneratorCWebIf : public CwmsCodeGeneratorCBase
{
private:
   CdmClass* m_rpCdmClass;
   QString m_qstrObjectListKeyname;
   QString m_qstrAdaptorClassname;


   public:
   /** +-=---------------------------------------------------------Fr 8. Jun 16:12:20 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::CwmsCodeGeneratorCWebIf // public                         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QString p_qstrObjectListKeyname               //                                   *
    * @param   QString p_qstrAdaptorClassname                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Jun 16:12:20 2012-----------*/
    CwmsCodeGeneratorCWebIf( QString p_qstrFilename,
                             QString p_qstrClassName,
                             CdmClass* p_pCdmClass,
                             QString p_qstrObjectListKeyname,
                             QString p_qstrAdaptorClassname);

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 16:26:40 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::~CwmsCodeGeneratorCWebIf // public, virtual               *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorCBl                                       *
    *----------------last changed: -----------------------------Di 5. Jun 16:26:40 2012-----------*/
    virtual ~CwmsCodeGeneratorCWebIf( );

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 11:39:39 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateCode         // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:39:39 2012-----------*/
    void GenerateCode();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:39:45 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateCodeP        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:39:45 2012-----------*/
    void GenerateCodeP();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:44:52 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateConstructor  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:44:52 2012-----------*/
    void GenerateConstructor();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:44:06 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateParameterConstructorHeader // private             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:44:06 2012-----------*/
    void GenerateParameterConstructorHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:44:21 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateParameterConstructorSource // private             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:44:21 2012-----------*/
    void GenerateParameterConstructorSource();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:50:15 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDestructor   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:50:15 2012-----------*/
    void GenerateDestructor();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:58:40 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateGet          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:58:40 2012-----------*/
    void GenerateGet();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:58:51 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GeneratePut          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:58:51 2012-----------*/
    void GeneratePut();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:59:01 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDelete       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:59:01 2012-----------*/
    void GenerateDelete();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:59:13 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDescription  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:59:13 2012-----------*/
    void GenerateDescription();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 11:59:34 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDetails      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:59:34 2012-----------*/
    void GenerateDetails();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:09:30 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateGetHeader    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:09:30 2012-----------*/
    void GenerateGetHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:09:40 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateGetSource    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:09:40 2012-----------*/
    void GenerateGetSource();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:11:04 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GeneratePutHeader    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:11:04 2012-----------*/
    void GeneratePutHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:11:28 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDeleteHeader // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:11:28 2012-----------*/
    void GenerateDeleteHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:12:00 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDescriptionHeader // private                      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:12:00 2012-----------*/
    void GenerateDescriptionHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:12:36 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDetailsHeader // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:12:36 2012-----------*/
    void GenerateDetailsHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:20:46 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateListHeader   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:20:46 2012-----------*/
    void GenerateListHeader();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:20:55 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateList         // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:20:55 2012-----------*/
    void GenerateList();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:22:02 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateListSource   // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:22:02 2012-----------*/
    void GenerateListSource();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 13:49:48 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GeneratePutSource    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 13:49:48 2012-----------*/
    void GeneratePutSource();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 14:11:35 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDeleteSource // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 14:11:35 2012-----------*/
    void GenerateDeleteSource();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 14:23:58 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDescriptionSource // private                      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 14:23:58 2012-----------*/
    void GenerateDescriptionSource();

   private:
   /** +-=---------------------------------------------------------Di 5. Jun 14:31:13 2012--------*
    * @method  CwmsCodeGeneratorCWebIf::GenerateDetailsSource // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 14:31:13 2012-----------*/
    void GenerateDetailsSource();
};

#endif // CWMSCODEGENERATORCWEBIF_H
