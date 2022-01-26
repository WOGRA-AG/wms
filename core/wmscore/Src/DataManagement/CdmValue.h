/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMValue_H
#define CDMValue_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>


// own Includes
#include "CdmModelElement.h"

#define isnan(x) (!(x == x))

// forwards
class CdmMember;
class CdmObject;

/*
 * This class implements the value baseclass.
 */
class WMSMANAGER_API CdmValue : public CdmModelElement
{
    Q_OBJECT

    friend class IdmDataAccess;
    friend class CdmObject;
    friend class CdmDataAccessHelper;

private:
   qint64 m_lMemberId;
    CdmObject* m_rpCdmObject;

public:
    EdmValueType GetValueType() const;
    EdmValueType GetEvenValueType(const CdmObject *pEventObject) const;
    bool IsMustValue() const;
   qint64 GetSize() const;
   qint64 GetMemberId() const;
    const CdmMember* GetMember() const;
    const CdmMember* GetEventMember(const CdmObject *pEventObject) const;
    bool IsUnique() const;
    bool IsOwner() const;
    bool IsClassDisplayString();
    int DeleteValue();
    void SetMemberId(qint64 p_lId);
    int FromStringToValue(QString p_qstrValue);
    const CdmObject* GetObject() const;
    const CdmObject* GetDataObject() const;
    QString GetUriInternal() const;
    virtual void Restore(QString p_qstrValue);
    virtual bool IsValue() const;
    virtual QString GetUri() const;
    virtual QString GetKeyname() const;
    virtual QString GetEventValueKeyname(CdmValue *pCdmEventValue) const;
    virtual QString GetInfo() const;
    virtual QVariant GetValueVariant() const= 0;
    virtual QVariant GetVariant() const;
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetModified();
    virtual bool ResolveValue();
    virtual bool HasValue() const;
    virtual void SetValueVariant(QVariant& p_rqVariant) = 0;
    virtual void SetDefaultValue(const CdmMember* p_pCdmMember) = 0;
    virtual QString GetDisplayString() const = 0;
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2) = 0;
    virtual void XmlExport(QDomElement& p_rqdeValue) const { Q_UNUSED(p_rqdeValue)};
    virtual void XmlImport(QDomElement& p_rqDomElement) {Q_UNUSED(p_rqDomElement)};
    virtual QString GetValueAsString() const= 0;


    static CdmValue* CreateValue(CdmMember* p_pCdmMember, CdmObject* p_pCdmObject);
    static CdmValue* CreateValue(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    static CdmValue* CopyValue(const CdmValue* p_pCdmValue, CdmObject* p_pCdmObject);
    static CdmValue *CopyEventValue(const CdmValue *p_pCdmEventValue, CdmObject *pEventObject, CdmObject* p_pCdmObject, CdmValue *p_pCdmObjectValue);
    static CdmValue *CopyObjectValueToEventValue(const CdmValue *p_pCdmEventValue, const CdmObject *pEventObject, CdmObject *p_pCdmObject, CdmValue *p_pCdmObjectValue);
    static CdmValue* CreateDeployValue(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);


protected:
    CdmValue(qint64 p_lDatabaseId,
            qint64 p_lId,
             QString p_qstrKeyname,
             EdmValueType p_eDmValue,
             CdmObject* p_pCdmObject);
    CdmValue(QVariantMap& p_rqvVaraint, CdmObject* p_pCdmObject);
    CdmValue(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);
    virtual ~CdmValue();
    void ValueChanged();
    void XmlExportValue(QDomElement& p_rqdeValue) const;
    void XmlImportValue(QDomElement& p_rqDomElement);
    virtual void SetNew();
    virtual void SetEventValueNew(const CdmObject *pEventObject);
    virtual void SetKeyname(QString p_qstrKeyname);


signals:
    void ValueChanged(CdmValue*);

};

#endif
