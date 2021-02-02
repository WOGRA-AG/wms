#ifndef CDMPACKAGE_H
#define CDMPACKAGE_H

// System and Qt Includes
#include <QVariant>

// own Includes
#include "CdmModelElement.h"

// Forwards
class CdmClass;

class WMSMANAGER_API CdmPackage : public CdmModelElement
{
    Q_OBJECT

    friend class CdmClassManager;
    friend class CdmClass;
    friend class CdmDataAccessHelper;

private:
    QList<CdmPackage*> m_qlChildren;
    QList<CdmClass*> m_qlClasses;
    bool m_bSystemPackage;
    CdmPackage* m_rParent;
    QString m_qstrOriginalPackageString;

    CdmPackage(long p_lSchemeId, QString p_qstrKeyname);

public:
    CdmPackage( QVariant p_qvVariant);

    virtual ~CdmPackage();
    virtual bool IsPackage() const;

    void RemoveClass(QString p_qstrKeyname);
    void RemoveClass(CdmClass *p_pClass);
    void DeleteChild(QString p_qstrName);
    void DeleteChild(CdmPackage *p_pPackage);
    void AddChild(CdmPackage *p_pPackage);
    void SetParent(CdmPackage *p_pPackage);
    const CdmPackage *GetParent() const;
    QString GetPackageString() const;
    CdmPackage *FindChild(QString p_qstrName);
    CdmPackage *FindChildByUri(QString p_qstrName);
    CdmPackage *FindChildById(long p_lId);
    int Commit();
    bool IsSystemPackage();
    void SetSystemPackage(bool p_bSystemFlag);
    void Rename(QString p_qstrKeyname);
    virtual QString GetKeyname() const;
    QString GetOriginalPackgeString() const;
    virtual QVariant GetVariant();
    void GetChildren(QList<CdmPackage *> &p_rqlChildren);
    QList<CdmClass *> GetClassList();
    static void RemovePackageFromClasses(CdmPackage *p_pPackage);
    virtual QString GetUri() const;
    virtual void ResetNewModified();
    void AddClass(CdmClass *p_pClass);
    void AddClass(QString p_qstrKeyname);

    QString GetUriInternal() const;
protected:
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetKeyname(QString p_qstrKeyname);
};

#endif // CDMPACKAGE_H
