#ifndef CWMSCODEGENERATORBASE_H
#define CWMSCODEGENERATORBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// WMS Includes
#include "CdmModelElement.h"

// Own Includes
#include "IwmsCodeGenerator.h"

// Forwards
class CdmMember;
class CdmClass;

// TypeDefs


/* 
 * This class implements the language independent base class for code generation
 */
class CwmsCodeGeneratorBase : public IwmsCodeGenerator
{


   public:
    CwmsCodeGeneratorBase();
    virtual ~CwmsCodeGeneratorBase();

   protected:
    void SaveFile(QString p_qstrFilename, QString p_qstrContent);
    QString GenerateCodeMemberName(QString p_qstrMember);
    QString AddIndent(int p_iIndentStage);
    bool CheckSetterMethod(EdmValueType p_eDmValue);
    bool CheckGetterMethod(EdmValueType p_eDmValue);
    void GetClassMembers(CdmClass* p_pCdmClass,
                         bool p_bIncludeBaseClassMembers,
                         QMap<qint64,
                         CdmMember*>& p_rqmMembers);
};

#endif // CWMSCODEGENERATORBASE_H
