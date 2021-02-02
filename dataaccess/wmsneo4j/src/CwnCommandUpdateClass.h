#ifndef CWNCOMMANDUPDATECLASS_H
#define CWNCOMMANDUPDATECLASS_H

#include <QMap>
#include <QList>
#include <QLinkedList>
#include <QVariant>
#include <QQueue>
#include <QPair>
#include <QVector>

#include "CwnCommandBase.h"

class CwnDataAccess;
class CdmClass;
class CdmClassGroup;
class CdmMember;
class CdmGroup;
class CdmScheme;
class CdmClassMethod;

class CwnCommandUpdateClass : public CwnCommandBase
{

private:
    QString payload;
    CdmClass* m_rpClass;
    QList<QString> insertedClasses;

    QQueue< QPair<CdmMember*,CdmClass*> > forInsertMember;

    void SaveGroupTranslations(CdmClassGroup *p_pCdmGroup);
    void SaveTranslations(QString &qstrQuery, CdmMember *p_pCdmMember);

    void InsertOrUpdateBaseClasses(CdmClass *p_pCdmClass);

    void DeleteMember(CdmMember *p_lMember);
    void UpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
    void InsertMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
    void InsertOrUpdateMember(CdmMember *p_pCdmMember, CdmClass *p_pCdmClass);
    void CaptionMemberid();

    void SaveValidators(CdmClass *&p_rCdmClass);
    void SaveMethods(CdmClass *&p_rCdmClass);
    void SaveGroups(CdmClass *&p_rCdmClass);

    void addRights(QVariantMap qvHash, int &i, QString &qstrQuery, QString NodeName, QString NodeVar);

    void createQueryForUpdateAttributesOfClass();

public:
    CwnCommandUpdateClass(CdmClass* p_pClass, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdateClass();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDUPDATECLASS_H


