#ifndef CDBCOMMANDEXISTCLASS_H
#define CDBCOMMANDEXISTCLASS_H

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandExistClass : public CdbAbstractCommand
{
private:
    long m_lSchemeId;
    QString m_qstrKeyname;
    bool m_bResult;

public:
    CdbCommandExistClass(long p_lSchemeId, QString p_qstrKeyname, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandExistClass();
    bool GetResult();


protected:
    bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDEXISTCLASS_H
