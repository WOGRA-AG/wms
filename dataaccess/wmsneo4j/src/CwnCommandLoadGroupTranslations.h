#ifndef CWNCOMMANDLOADGROUPTRANSLATIONS_H
#define CWNCOMMANDLOADGROUPTRANSLATIONS_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>
#include <QList>

class CwnDataAccess;
class CdmClassGroup;

class CwnCommandLoadGroupTranslations : public CwnCommandBase
{

public:
    CwnCommandLoadGroupTranslations(CwnDataAccess* m_rpDataAccess, CdmClassGroup *group);
    virtual ~CwnCommandLoadGroupTranslations();

    QString createQuery();
    QString queryCausedError;
private:
    CdmClassGroup* g;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOADGROUPTRANSLATIONS_H
