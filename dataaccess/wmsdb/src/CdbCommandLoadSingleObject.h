#ifndef CDBCOMMANDLOADSINGLEOBJECT_H
#define CDBCOMMANDLOADSINGLEOBJECT_H

#include "CdbAbstractCommand.h"

class CdbCommandLoadSingleObject : public CdbAbstractCommand
{
private:
    long m_lContainerId;
    long m_lObjectId;
    QString m_qstrKeyname;
    CdmObject* m_rpObject;


    bool CheckType(long p_lId, EdmValueType p_eNeeded);
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
    QString GenerateDbQuery();
    const CdmMember *FindMember(long p_lId);
public:
    CdbCommandLoadSingleObject(long p_lContainerId, long p_lObjectId, CdbDataAccess* p_pDataAccess);
    CdbCommandLoadSingleObject(long p_lContainerId, QString p_qstrKeyname, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadSingleObject();
    CdmObject* GetResult();

protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADSINGLEOBJECT_H
