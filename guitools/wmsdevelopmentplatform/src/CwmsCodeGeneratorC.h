#ifndef CWMSCODEGENERATORC_H
#define CWMSCODEGENERATORC_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QMap>

// Own Includes
#include "CwmsCodeGeneratorCBase.h"
#include "CdmMember.h"

// Forwards
class CdmClass;
class CwmsCodeGeneratorTestC;

// TypeDefs

// enumerations
enum EwmsCodeGenerationMethodType
{
    eWmsCodeGenerationMethodTypeSetter,
    eWmsCodeGenerationMethodTypeGetter
};


/* 
 * This This class generates c++ interface code for classes.
 */
class CwmsCodeGeneratorC : public CwmsCodeGeneratorCBase
{
private:
    CdmClass* m_rpCdmClass;
    bool m_bCreateBaseClassMemberFunctions;
    bool m_bGenerateStandardObjectList;
    bool m_bGenerateTestCode;
    bool m_bGenerateBusinessLogicClass;
    bool m_bGenerateTempClass;
    bool m_bGenerateWebInterface;
    QString m_qstrWebInterfaceClassName;
    QString m_qstrWebInterfaceOLKeyname;
    QStringList m_qstrListAbstractFunctionsForBaseClass;

public:
    CwmsCodeGeneratorC(CdmClass* p_pCdmClass, QString p_qstrClassName, QString p_qstrFilename);
    virtual ~CwmsCodeGeneratorC();
    void GenerateCode();
    void SetCreateBaseClassMemberFunctions(bool p_bCreate);
    void SetGenerateStandardObjectList(bool p_bStandard);
    void SetGenerateTestCode(bool p_bGenerate);
    void SetGenerateBusinessLogicCode(bool p_bGenerate);
    void SetGenerateTempClassCode(bool p_bGenerate);
    void SetGenerateWebInterfaceCode(bool p_bGenerate);
    void SetWebInterfaceClassName(QString p_qstrClassName);
    void SetWebInterfaceObjectListName(QString p_qstrOLName);

private:
    void GenerateCodeP();
    void GeneratesConstructors();
    void GenerateDestructors();
    void GeneratesMemberAccess();
    void GenerateMethodInHeader(QString p_qstrMethodName,
                                EdmMemberAccess p_eAccessType,
                                EdmValueType p_eReturnValue,
                                EwmsCodeGenerationMethodType p_eType);
    void GenerateMethodInSource(QString p_qstrMethodName,
                                EdmValueType p_eReturnValue,
                                EwmsCodeGenerationMethodType p_eType);
    void GenerateDefaultConstructorSource();
    void GenerateParameterConstructorSource();
    void GenerateDefaultConstructorHeader();
    void GenerateParameterConstructorHeader();
    void GenerateDestructorHeader();
    void GenerateDestructorSource();
    void GenerateSetterSource(QString p_qstrMember, EdmValueType p_eReturnValue);
    void GenerateGetterSource(QString p_qstrMember, EdmValueType p_eReturnValue);
    void GenerateSetterHeader(QString p_qstrMethodName,
                              EdmMemberAccess p_eAccessType,
                              EdmValueType p_eReturnValue);
    void GenerateGetterHeader(QString p_qstrMethodName,
                              EdmMemberAccess p_eAccessType,
                              EdmValueType p_eReturnValue);
    QString GenerateGetterCode(EdmValueType p_eDmValue, QString p_qstrMember);
    QString GenerateSetterCode(EdmValueType p_eReturnValue, QString p_qstrMember);
    void GenerateMemberAccess(CdmMember* p_pCdmMember);
    void GenerateAllMembersAccess();
    void GenerateClassMembersAccess();
    void GenerateCreateMethod();
    void GenerateCreateMethodSource();
    void GenerateCreateMethodHeader();
    void GenerateDeleteMethod();
    void GenerateDeleteMethodHeader();
    void GenerateStandardObjectList();
    void GenerateDeleteMethodSource();
    void GenerateStandardObjectListSource(QString p_qstrObjListName);
    void GenerateStandardObjectListHeader();
    QString GenerateStandardObjectListKeyname();
    void GenerateCreateMethodSourceWithoutParameter();
    void GenerateCreateMethodHeaderWithoutParameter();
};

#endif // CWMSCODEGENERATORC_H
