/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsCodeGeneratorCBl.cpp
 ** Started Implementation: 2012/06/05
 ** Description:
 **
 ** Implements the code generator for web interfaces.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// own Includes
#include "CwmsCodeGeneratorCBl.h"

/** +-=---------------------------------------------------------Mi 6. Jun 10:53:35 2012-----------*
 * @method  CwmsCodeGeneratorCBl::CwmsCodeGeneratorCBl       // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrClassname                          //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QStringList p_qstrlAbstractMethods               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 10:53:35 2012-----------*/
CwmsCodeGeneratorCBl::CwmsCodeGeneratorCBl(QString p_qstrFilename,
                                           QString p_qstrClassname,
                                           CdmClass* p_pCdmClass,
                                           QStringList p_qstrlAbstractMethods)
   : CwmsCodeGeneratorCBase(p_qstrFilename, p_qstrClassname),
  m_rpCdmClass(p_pCdmClass),
  m_qstrlAbstractMethods(p_qstrlAbstractMethods)
{



}

/** +-=---------------------------------------------------------Di 5. Jun 11:21:14 2012-----------*
 * @method  CwmsCodeGeneratorCBl::~CwmsCodeGeneratorCBl      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorCBl                                          *
 *----------------last changed: --------------------------------Di 5. Jun 11:21:14 2012-----------*/
CwmsCodeGeneratorCBl::~CwmsCodeGeneratorCBl()
{
}

/** +-=---------------------------------------------------------Di 5. Jun 11:24:16 2012-----------*
 * @method  CwmsCodeGeneratorCBl::GenerateCode               // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:24:16 2012-----------*/
void CwmsCodeGeneratorCBl::GenerateCode()
{
   if (!m_qstrFilename.isEmpty() && !m_qstrClassName.isEmpty())
   {
      GenerateCodeP();
      SaveFiles();
   }
}


/** +-=---------------------------------------------------------Di 5. Jun 11:24:22 2012-----------*
 * @method  CwmsCodeGeneratorCBl::GenerateCodeP              // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:24:22 2012-----------*/
void CwmsCodeGeneratorCBl::GenerateCodeP()
{
   AddSourceInclude(m_qstrClassName + ".h");
   
   OpenClass();
   GenerateSourceHeader();
   GenerateDefaultConstructorSource();
   GenerateDefaultConstructorHeader();
   AddAbstractMethods();
   AddValidateMethod();
   CloseClass();
}

/** +-=---------------------------------------------------------Mi 6. Jun 13:36:19 2012-----------*
 * @method  CwmsCodeGeneratorCBl::GenerateDefaultConstructorSource // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 13:36:19 2012-----------*/
void CwmsCodeGeneratorCBl::GenerateDefaultConstructorSource()
{
   GenerateDefaultConstructorSourceWithoutBaseClasses(m_qstrClassName);
}

/** +-=---------------------------------------------------------Mi 6. Jun 13:37:15 2012-----------*
 * @method  CwmsCodeGeneratorCBl::GenerateDefaultConstructorHeader // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 13:37:15 2012-----------*/
void CwmsCodeGeneratorCBl::GenerateDefaultConstructorHeader()
{
   GenerateConstructorHeader(m_qstrClassName, "");
}

/** +-=---------------------------------------------------------Mi 6. Jun 13:54:55 2012-----------*
 * @method  CwmsCodeGeneratorCBl::AddAbstractMethods         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 13:54:55 2012-----------*/
void CwmsCodeGeneratorCBl::AddAbstractMethods()
{
   for (int iCounter = 0; iCounter < m_qstrlAbstractMethods.count(); ++iCounter)
   {
      m_qstrHeader += m_qstrlAbstractMethods[iCounter] + "\n";
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 13:55:09 2012-----------*
 * @method  CwmsCodeGeneratorCBl::AddValidateMethod          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 13:55:09 2012-----------*/
void CwmsCodeGeneratorCBl::AddValidateMethod()
{
   GenerateValidateHeader();
   GenerateValidateSource();
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:24:41 2012-----------*
 * @method  CwmsCodeGeneratorCBl::GenerateValidateHeader     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:24:41 2012-----------*/
void CwmsCodeGeneratorCBl::GenerateValidateHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "bool Validate();\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:29:05 2012-----------*
 * @method  CwmsCodeGeneratorCBl::GenerateValidateSource     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:29:05 2012-----------*/
void CwmsCodeGeneratorCBl::GenerateValidateSource()
{
   m_qstrSource += "bool " + m_qstrClassName + "::Validate()\n";
   m_qstrSource += "{\n";
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "//TODO Implement validation logic here\n";
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "return true;\n";
   m_qstrSource += "}\n";
}