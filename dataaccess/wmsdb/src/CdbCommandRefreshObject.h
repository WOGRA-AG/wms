#ifndef CDBCOMMANDREFRESHOBJECT_H
#define CDBCOMMANDREFRESHOBJECT_H

#include "CdbAbstractCommand.h"

class CdmObject;

class CdbCommandRefreshObject : public CdbAbstractCommand
{
private:
    CdmObject* m_rpObject;


    bool CheckType(QString p_qstrKeyname, EdmValueType p_eNeeded);
    long ReadBinaryDocuments();
    long ReadValues();
    long ReadBools();
    CdmValueCharacterDocument *CreateCharDocValue(CdbDataAccess::EodbcBaseType p_eType, long p_lDatabaseId, long p_lId, QString p_qstrKeyname);
    long ReadCharacterDocuments(CdbDataAccess::EodbcBaseType p_eType);
    long ReadCounters();
    long ReadDates();
    long ReadDateTimes();
    long ReadDoubles();
    long ReadInts(CdbDataAccess::EodbcBaseType p_eOdbcType);
    long ReadLongs();
    long ReadObjectRefs();
    long ReadObjectListRefs();
    long ReadStrings();
    long ReadFloats();
    long ReadTimes();
public:
    CdbCommandRefreshObject(CdmObject* m_rpCdmObject, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandRefreshObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDREFRESHOBJECT_H
