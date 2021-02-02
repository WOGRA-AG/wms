#ifndef CDMCLASSVALIDATOR_H
#define CDMCLASSVALIDATOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>
#include <QString>

// Own Includes
#include "datamanager.h"

// Forwards
class CdmObject;
class CdmObjectContainer;

// TypeDefs

enum EdmValidationType
{
    eDmValidationTypeObject,
    eDmValidationTypeObjectList
};

/* 
 * This class implements the the class validator. a validator is able to validate
 * objects or objectlist that it fits the user demands. if it does not fit
 * it returns an error message.
 */
class WMSMANAGER_API CdmClassValidator
{
    friend class CdmClass;

private:
    int m_iId;
    QString m_qstrName;
    QString m_qstrCode;
    QString m_qstrErrorMessage;
    EdmValidationType m_eValType;
    int m_iVersion;

private:
    CdmClassValidator();
    CdmClassValidator(QVariantMap& p_rqvHash);
    virtual ~CdmClassValidator();

public:
    void SetVariant(QVariantMap& p_rqvHash);
    QVariant GetVariant() const;
    void SetId(int p_iId);
    int GetId() const;
    void SetVersion(int p_iVersion);
    int GetVersion() const;
    void SetName(QString p_qstrName);
    QString GetName() const;
    void SetCode(QString p_qstrCode);
    QString GetCode() const;
    QString GetCodeBase64() const;
    void SetMessage(QString p_qstrMesage);
    QString GetErrorMessage() const;
    void SetValidationType(EdmValidationType p_eType);
    EdmValidationType GetValidationType() const;
    QString GenerateScriptCode();
};

#endif

