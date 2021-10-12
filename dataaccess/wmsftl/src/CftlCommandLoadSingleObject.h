#ifndef CDBCOMMANDLOADSINGLEOBJECT_H
#define CDBCOMMANDLOADSINGLEOBJECT_H

#include "CftlAbstractCommand.h"

class CftlCommandLoadSingleObject : public CftlAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
    QString m_qstrKeyname;
   qint64 m_lObjectId;
    CdmObject* m_rpObject;


    bool CheckType(QString p_qstrKeyname, EdmValueType p_eNeeded);
   qint64 ReadBinaryDocuments();
   qint64 ReadValues();
   qint64 ReadBools();
    CdmValueCharacterDocument *CreateCharDocValue(CftlDataAccess::EodbcBaseType p_eType,qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname);
   qint64 ReadCharacterDocuments(CftlDataAccess::EodbcBaseType p_eType);
   qint64 ReadCounters();
   qint64 ReadDates();
   qint64 ReadDateTimes();
   qint64 ReadDoubles();
   qint64 ReadInts(CftlDataAccess::EodbcBaseType p_eOdbcType);
   qint64 ReadLongs();
   qint64 ReadObjectRefs();
   qint64 ReadObjectListRefs();
   qint64 ReadStrings();
   qint64 ReadFloats();
   qint64 ReadTimes();
    QString GenerateDbQuery();
public:
    CftlCommandLoadSingleObject(CdmObjectContainer* p_pContainer,qint64 p_lObjectId, CftlDataAccess* p_pDataAccess);
    CftlCommandLoadSingleObject(CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadSingleObject();
    CdmObject* GetResult();

protected:
    bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDLOADSINGLEOBJECT_H
