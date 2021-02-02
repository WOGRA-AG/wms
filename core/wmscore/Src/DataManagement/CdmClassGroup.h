#ifndef CDMCLASSGROUP_H
#define CDMCLASSGROUP_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QString>
#include <QVariant>
#include <QAtomicInt>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// Own Includes
// #include "datamanager.h"
#include "CdmRights.h"

// Forwards
class CdmClass;
class CdmMember;

// TypeDefs

class WMSMANAGER_API CdmClassGroup : public CwmsSynchronizable
{
    friend class CdmClass;

private:
    QAtomicInt m_iId;
    CdmClass* m_rpCdmClass;
    CdmRights m_cCdmRights;
    QString m_qstrName;
    QAtomicInt m_iVersion;
    QAtomicInt m_iParentId;
    QAtomicInt m_iPosition;
    QMap<int, CdmClassGroup*> m_qmChilds; //<Position, Object>
    QMap<QString, QString> m_qmTranslations;

private:
    CdmClassGroup(CdmClass* p_pCdmClass,
                  QString p_qstrName,
                  int p_iPosition,
                  int p_iVersion,
                  int p_iParentId = 0);
    CdmClassGroup(QVariantMap& p_rqvHash, CdmClass* p_pCdmClass, CdmClassGroup* p_pCdmClassGroup);
    virtual ~CdmClassGroup();


public:
    void SetParentId(int p_iParentId);
    void SetName(QString p_qstrName);
    void SetPosition(int p_iPos);
    void SetVersion(int p_iVersion);
    void DeleteTranslation(QString p_iId);
    void SetVariant(QVariantMap& p_rqvHash);
    virtual QVariant GetVariant() const;
    int GetChildPosition(CdmClassGroup* p_pCdmGroup);
    void SetId(int p_iId);
    QMap<QString, QString>& GetTranslations();
    QString GetTranslation(QString p_iLanguageId) const;
    void SetTranslation(QString p_qstrLanguage, QString p_qstrTranslation);
    virtual QString GetCaption() const;
    CdmClassGroup* GetParent() const;
    QString GetName() const;
    int GetPosition() const;
    int GetVersion() const;
    void GetMembers(QList<CdmMember*>& p_rqlMembers) const;
    CdmRights& GetRights();
    bool CheckWriteAccess() const;
    bool CheckReadAccess() const;
    int GetId() const;

private:
    void AppendChild(CdmClassGroup* p_pCdmChild);
    void ClearChildren();
    void MoveChildUp(CdmClassGroup* p_pCdmGroup);
    void MoveChildDown(CdmClassGroup* p_pCdmGroup);
};

#endif
