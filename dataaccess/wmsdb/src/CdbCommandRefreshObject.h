#ifndef CDBCOMMANDREFRESHOBJECT_H
#define CDBCOMMANDREFRESHOBJECT_H

#include "CdbAbstractCommand.h"

class CdmObject;

class CdbCommandRefreshObject : public CdbAbstractCommand
{
private:
    CdmObject* m_rpObject;


    bool CheckType(QString p_qstrKeyname, EdmValueType p_eNeeded);
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
public:
    CdbCommandRefreshObject(CdmObject* m_rpCdmObject, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandRefreshObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDREFRESHOBJECT_H
