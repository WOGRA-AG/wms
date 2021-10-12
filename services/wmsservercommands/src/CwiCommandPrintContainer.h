#ifndef CWICOMMANDPRINTCONTAINER_H
#define CWICOMMANDPRINTCONTAINER_H

#include "CwiAbstractCommand.h"

class CdmObjectContainer;

class CwiCommandPrintContainer : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

    CdmObjectContainer *GetObjectList(qint64 p_lObjectList);
public:
    CwiCommandPrintContainer(CwmscomData* p_pData);
    virtual ~CwiCommandPrintContainer();
    virtual void Execute();
};

#endif // CWICOMMANDPRINTCONTAINER_H
