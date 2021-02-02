#ifndef CDBCOMMANDLOADOBJECTS_H
#define CDBCOMMANDLOADOBJECTS_H

#include <QLinkedList>

#include "CdbAbstractCommand.h"

// Forwards
class CdmValueCharacterDocument;
class CdmObjectContainer;

class CdbCommandLoadObjects : public CdbAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
    QLinkedList<long> m_qvlObjectIds;


    long ReadValues(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadBinaryDocuments(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    bool CheckType(CdmObject *p_pObject, QString p_qstrKeyname, EdmValueType p_eNeeded);
    int ReadBools(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadCharacterDocuments(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects, CdbDataAccess::EodbcBaseType p_eType);
    CdmValueCharacterDocument *CreateCharDocValue(CdbDataAccess::EodbcBaseType p_eType, long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject *p_pCdmObjectOwner);
    int ReadCounters(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadDates(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadDateTimes(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadDoubles(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadFloats(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadInts(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects, CdbDataAccess::EodbcBaseType p_eOdbcType);
    int ReadLongs(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadObjectRefs(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadObjectListRefs(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadStrings(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    int ReadTimes(QString p_qstrInString, QMap<long, CdmObject *> &p_rqmObjects);
    QString GenerateInString(QLinkedList<long> &p_rqvlIds);
public:
    CdbCommandLoadObjects(CdmObjectContainer* p_pContainer, QLinkedList<long>& p_qlObjectIds, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadObjects();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDLOADOBJECTS_H
