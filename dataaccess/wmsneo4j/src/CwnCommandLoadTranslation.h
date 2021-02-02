#ifndef CWNCOMMANDLOADTRANSLATION_H
#define CWNCOMMANDLOADTRANSLATION_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>
#include <QLinkedList>

class CwnDataAccess;
class CdmMember;

class CwnCommandLoadTranslation : public CwnCommandBase
{

public:
    CwnCommandLoadTranslation(CwnDataAccess* m_rpDataAccess, CdmMember *member);
    virtual ~CwnCommandLoadTranslation();

    QString createQuery();
    QString queryCausedError;
private:
    CdmMember* m;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOADTRANSLATION_H
