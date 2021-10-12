#ifndef CDBCOMMANDLOADSINGLEOBJECT_H
#define CDBCOMMANDLOADSINGLEOBJECT_H

#include "CdbAbstractCommand.h"

class CdbCommandLoadSingleObject : public CdbAbstractCommand
{
private:
   qint64 m_lContainerId;
   qint64 m_lObjectId;
    QString m_qstrKeyname;
    CdmObject* m_rpObject;


    bool CheckType(qint64 p_lId, EdmValueType p_eNeeded);
   qint64 ReadBinaryDocuments();
   qint64 ReadValues();
   qint64 ReadBools();
    CdmValueCharacterDocument *CreateCharDocValue(CdbDataAccess::EodbcBaseType p_eType,qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname);
   qint64 ReadCharacterDocuments(CdbDataAccess::EodbcBaseType p_eType);
   qint64 ReadCounters();
   qint64 ReadDates();
   qint64 ReadDateTimes();
   qint64 ReadDoubles();
   qint64 ReadInts(CdbDataAccess::EodbcBaseType p_eOdbcType);
   qint64 ReadLongs();
   qint64 ReadObjectRefs();
   qint64 ReadObjectListRefs();
   qint64 ReadStrings();
   qint64 ReadFloats();
   qint64 ReadTimes();
    QString GenerateDbQuery();
    const CdmMember *FindMember(qint64 p_lId);
public:
    CdbCommandLoadSingleObject(qint64 p_lContainerId,qint64 p_lObjectId, CdbDataAccess* p_pDataAccess);
    CdbCommandLoadSingleObject(qint64 p_lContainerId, QString p_qstrKeyname, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadSingleObject();
    CdmObject* GetResult();

protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADSINGLEOBJECT_H
