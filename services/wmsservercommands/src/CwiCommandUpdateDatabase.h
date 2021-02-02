#ifndef CWICOMMANDUPDATEDATABASE_H
#define CWICOMMANDUPDATEDATABASE_H

#include "CwiAbstractCommand.h"

class CdmScheme;


class CwiCommandUpdateDatabase : public CwiAbstractCommand
{
private:
    CwmscomData* m_rpData;
    CdmScheme* m_rpDatabase;

public:
    CwiCommandUpdateDatabase(CwmscomData* p_pData, CdmScheme* p_pDatabase);
    virtual ~CwiCommandUpdateDatabase();
    virtual void Execute();
};

#endif // CWICOMMANDUPDATEDATABASE_H
