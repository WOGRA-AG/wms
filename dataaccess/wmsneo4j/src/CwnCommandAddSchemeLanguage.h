#ifndef CWNCOMMANDADDSCHEMELANGUAGE_H
#define CWNCOMMANDADDSCHEMELANGUAGE_H

#include "CwnCommandBase.h"

class CwnCommandAddSchemeLanguage : public CwnCommandBase
{

private:
   qint64 m_lSchemeId;
    QString m_qstrLanguage;

public:
    CwnCommandAddSchemeLanguage(qint64 p_lSchemeId, QString p_qstrLanguage, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandAddSchemeLanguage();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDADDSCHEMELANGUAGE_H
