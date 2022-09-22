#ifndef CWMSCODEGENERATORCBASE_H
#define CWMSCODEGENERATORCBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QStringList>
#include <QMap>

// Own Includes
#include "CwmsCodeGeneratorBase.h"
// Forwards


// TypeDefs


/* 
 * This class implements the base class for c++ code generation
 */
class CwmsCodeGeneratorCBase : public CwmsCodeGeneratorBase
{
protected:
    QString m_qstrSource;
    QString m_qstrHeader;
    QString m_qstrFilename;
    QString m_qstrClassName;
    QString m_qstrDllExportDeclaration;
    QStringList m_qstrlSourceIncludes;
    QStringList m_qstrlHeaderIncludes;
    QStringList m_qstrlForwards;
    QMap<QString, QString> m_qmBaseClasses; // <ClassName, Filename>

public:
    CwmsCodeGeneratorCBase( QString p_qstrFilename, QString p_qstrClassName);
    virtual ~CwmsCodeGeneratorCBase( );
    void AddBaseClassData(QString p_qstrBaseClassName, QString p_qstrBaseClassFilename);
    QString GetClassName();
    void SetDllExportDeclaration(QString p_qstrDeclaration);


protected:
    void SaveHeaderFile();
    void SaveFiles();
    QString GenerateMethodHeadSource(QString p_qstrReturnType,
                                     QString p_qstrClassName,
                                     QString p_qstrMethodName,
                                     QString p_qstrParameters);
    QString GenerateMethodHeadHeader(QString p_qstrAccessType,
                                     QString p_qstrReturnType,
                                     QString p_qstrMethodName,
                                     QString p_qstrParameters);
    QString GenerateConstructorSourceHead(QString p_qstrClassName, QString p_qstrParameter);
    QString GenerateConstructorHeader(QString p_qstrClassName, QString p_qstrParameter);
    QString GenerateDestructorHeader(QString p_qstrClassName);
    QString GenerateDestructorSource(QString p_qstrClassName);
    void CloseClass();
    void OpenClass();
    void GenerateSourceHeader();
    void AddMemberVariable(QString p_qstrType, QString p_qstrName);
    void AddSourceInclude(QString p_qstrInclude);
    void AddForward(QString p_qstrForward);
    void AddHeaderInclude(QString p_qstrInclude);
    QString GenerateSlotHeadHeader(QString p_qstrAccessType,
                                   QString p_qstrReturnType,
                                   QString p_qstrMethodName,
                                   QString p_qstrParameters);
    void GenerateDefaultConstructorHeader(QString p_qstrClassName);
    void GenerateDefaultConstructorSourceWithoutBaseClasses(QString p_qstrClassName);
    QString GetParameter(EdmValueType p_eDmValue);
    QString GetReturnType(EdmValueType p_eDmValue);

private:
    void SaveSourceFile();

};

#endif // CWMSCODEGENERATORCBASE_H
