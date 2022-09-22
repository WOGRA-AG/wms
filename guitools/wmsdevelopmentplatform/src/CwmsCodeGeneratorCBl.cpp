// System and QT Includes


// own Includes
#include "CwmsCodeGeneratorCBl.h"

CwmsCodeGeneratorCBl::CwmsCodeGeneratorCBl(QString p_qstrFilename,
                                           QString p_qstrClassname,
                                           CdmClass* p_pCdmClass,
                                           QStringList p_qstrlAbstractMethods)
   : CwmsCodeGeneratorCBase(p_qstrFilename, p_qstrClassname),
  m_rpCdmClass(p_pCdmClass),
  m_qstrlAbstractMethods(p_qstrlAbstractMethods)
{



}

CwmsCodeGeneratorCBl::~CwmsCodeGeneratorCBl()
{
}

void CwmsCodeGeneratorCBl::GenerateCode()
{
   if (!m_qstrFilename.isEmpty() && !m_qstrClassName.isEmpty())
   {
      GenerateCodeP();
      SaveFiles();
   }
}

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

void CwmsCodeGeneratorCBl::GenerateDefaultConstructorSource()
{
   GenerateDefaultConstructorSourceWithoutBaseClasses(m_qstrClassName);
}

void CwmsCodeGeneratorCBl::GenerateDefaultConstructorHeader()
{
   GenerateConstructorHeader(m_qstrClassName, "");
}

void CwmsCodeGeneratorCBl::AddAbstractMethods()
{
   for (int iCounter = 0; iCounter < m_qstrlAbstractMethods.count(); ++iCounter)
   {
      m_qstrHeader += m_qstrlAbstractMethods[iCounter] + "\n";
   }
}

void CwmsCodeGeneratorCBl::AddValidateMethod()
{
   GenerateValidateHeader();
   GenerateValidateSource();
}

void CwmsCodeGeneratorCBl::GenerateValidateHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "bool Validate();\n";
}

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
