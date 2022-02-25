#ifndef CDMCLASSMETHOD_H
#define CDMCLASSMETHOD_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QList>
#include <QPair>

// Own Includes
#include "datamanager.h"
#include "CdmLocatedElement.h"
#include "CdmMember.h"
#include "CdmRights.h"

// Forwards


// TypeDefs

// Enumerations

class WMSMANAGER_API CdmClassMethodParameter
{
public:
    int m_iPos;
    EdmValueType m_eType;
   qint64 m_lReference;

private:
    QString m_qstrName;
    
public:
    CdmClassMethodParameter();
    void SetName(QString p_qstrName);
    QString GetName() const;
};

/* 
 * This class implements the class methods
 */
class WMSMANAGER_API CdmClassMethod : public CdmLocatedElement
{
    Q_OBJECT

    friend class CdmClass;

private:
    QString m_qstrMethodName;
    QString m_qstrCaption;
    QByteArray m_qbaIcon;
    QString m_qstrSourceCode;
    QString m_qstrComment;
    QList<CdmClassMethodParameter> m_qlParameters;
    CdmRights m_cCdmRights;
    EdmMemberAccess m_eAccess;
    QAtomicInt m_iVersion;
    EdmValueType m_eReturnType;
    QAtomicInt m_iId;
    QAtomicInteger<bool> m_bStatic;
    CdmClass* m_rpCdmClass;

private:
    CdmClassMethod(int p_iId,
                   QString p_qstrMethodName,
                   EdmValueType p_eReturnType,
                   EdmMemberAccess p_eAccessMode,
                   QString p_qstrCode,
                   int p_iVersion);
    CdmClassMethod();
    virtual ~CdmClassMethod();

public:
    void SetVersion(int p_iVersion);
    void SetMethodName(QString p_qstrName);
    void SetAccess(EdmMemberAccess p_eType);
    void SetReturnType(EdmValueType p_eType);
    void SetParameters(QList<CdmClassMethodParameter> p_qmParameters);
    void AddParameter(QString p_qstrName, EdmValueType p_eValueType,qint64 p_lClassId = 0);
    QString GetParametersAsString() const;
    CdmClassMethod( QVariantMap& p_rvHash);
    void SetVariant(QVariantMap& p_rqvHash);
    virtual QVariant GetVariant() const;
    void SetParameters(QString p_qqstrParameters);
    void SetSourceCode(QString p_qstrCode);
    void SetId(int p_iId);
    void SetComment(QString p_qstrComment);
    void SetStatic(bool p_bStatic);
    void SetClass(CdmClass* p_pCdmClass);
    void DeleteParameter(QString p_qstrName);
    void MoveParameterUp(QString p_qstrParam);
    void MoveParameterDown(QString p_qstrParam);
    CdmClassMethodParameter GetParameterByPos(int p_iPos) const;
    void SetCaption(QString p_qstrCaption);
    QString GetCaption() const;
    void SetIcon(QString p_qstrFilename);
    QPixmap GetIcon() const;
    void SetIcon(QByteArray p_qbArray);
    QByteArray GetIconAsByteArray() const;
    QString GenerateScriptCode();
    QString GetParametersAsStringForFunction() const;
    bool LockClassMethod();
    bool UnlockClassMethod();
    virtual QString GetUri() const;
    virtual bool IsMethod() const;
    QString GetAccessModeAsString() const;
    QString GetUriInternal() const;
    bool IsStatic() const;
    CdmClass* GetClass() const;
    bool HasParameters() const;
    int GetVersion() const;
    QString GetMethodName() const;
    EdmMemberAccess GetAccess() const;
    EdmValueType GetReturnType() const;
    bool CheckExecuteAccess() const;
    CdmRights& GetRights();
    QString GetSourceCode() const;
    QString GetSourceCodeBase64() const;
    int GetId() const;
    int GetParameterCount() const;
    QList<CdmClassMethodParameter> GetParameters() const;
    QString GetCallInterface() const;
    QString GetComment() const;

    QVariant ExecuteFunction(bool p_bDebugger, CdmObject *pObject);
    QVariant ExecuteStaticFunction(bool p_bDebugger);
};

#endif //
