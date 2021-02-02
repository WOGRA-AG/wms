#ifndef CWICOMMANDCREATEDATABASE_H
#define CWICOMMANDCREATEDATABASE_H

#include "CwiAbstractCommand.h"

class CdmDataProvider;


class CwiCommandCreateDatabase : public CwiAbstractCommand
{
private:
    CwmscomData* m_rpData;

public:
    CwiCommandCreateDatabase(CwmscomData* p_pData);
    virtual ~CwiCommandCreateDatabase();
    virtual void Execute();
};

#endif // CWICOMMANDCREATEDATABASE_H
