#ifndef CDBCOMMANDEXISTCLASS_H
#define CDBCOMMANDEXISTCLASS_H

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandExistClass : public CftlAbstractCommand
{
private:
   qint64 m_lSchemeId;
    QString m_qstrKeyname;
    bool m_bResult;

public:
    CftlCommandExistClass(qint64 p_lSchemeId, QString p_qstrKeyname, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandExistClass();
    bool GetResult();


protected:
    bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDEXISTCLASS_H
