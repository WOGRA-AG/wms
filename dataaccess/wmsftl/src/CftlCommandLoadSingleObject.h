#ifndef CDBCOMMANDLOADSINGLEOBJECT_H
#define CDBCOMMANDLOADSINGLEOBJECT_H

#include "CftlAbstractCommand.h"

class CftlCommandLoadSingleObject : public CftlAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
    QString m_qstrKeyname;
    long m_lObjectId;
    CdmObject* m_rpObject;


    bool CheckType(QString p_qstrKeyname, EdmValueType p_eNeeded);
    long ReadBinaryDocuments();
    long ReadValues();
    long ReadBools();
    CdmValueCharacterDocument *CreateCharDocValue(CftlDataAccess::EodbcBaseType p_eType, long p_lDatabaseId, long p_lId, QString p_qstrKeyname);
    long ReadCharacterDocuments(CftlDataAccess::EodbcBaseType p_eType);
    long ReadCounters();
    long ReadDates();
    long ReadDateTimes();
    long ReadDoubles();
    long ReadInts(CftlDataAccess::EodbcBaseType p_eOdbcType);
    long ReadLongs();
    long ReadObjectRefs();
    long ReadObjectListRefs();
    long ReadStrings();
    long ReadFloats();
    long ReadTimes();
    QString GenerateDbQuery();
public:
    CftlCommandLoadSingleObject(CdmObjectContainer* p_pContainer, long p_lObjectId, CftlDataAccess* p_pDataAccess);
    CftlCommandLoadSingleObject(CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadSingleObject();
    CdmObject* GetResult();

protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADSINGLEOBJECT_H
