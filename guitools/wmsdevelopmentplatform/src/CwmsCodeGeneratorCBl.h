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
    CwmsCodeGeneratorCBl(QString p_qstrFilename,
                         QString p_qstrClassname,
                         CdmClass* p_pCdmClass,
                         QStringList p_qstrlAbstractMethods);
    virtual ~CwmsCodeGeneratorCBl();
    void GenerateCode();

   private:
    void GenerateCodeP();
    void GenerateDefaultConstructorSource();
    void GenerateDefaultConstructorHeader();
    void AddAbstractMethods();
    void AddValidateMethod();
    void GenerateValidateHeader();
    void GenerateValidateSource();
};

#endif // CWMSCODEGENERATORCBL_H
