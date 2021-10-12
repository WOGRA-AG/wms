#ifndef CDBCOMMANDLOADOBJECTS_H
#define CDBCOMMANDLOADOBJECTS_H

#include <QList>

#include "CdbAbstractCommand.h"

// Forwards
class CdmValueCharacterDocument;
class CdmObjectContainer;

class CdbCommandLoadObjects : public CdbAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
    QList<qint64> m_qvlObjectIds;


   qint64 ReadValues(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadBinaryDocuments(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    bool CheckType(CdmObject *p_pObject, QString p_qstrKeyname, EdmValueType p_eNeeded);
    int ReadBools(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadCharacterDocuments(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects, CdbDataAccess::EodbcBaseType p_eType);
    CdmValueCharacterDocument *CreateCharDocValue(CdbDataAccess::EodbcBaseType p_eType,qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject *p_pCdmObjectOwner);
    int ReadCounters(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadDates(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadDateTimes(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadDoubles(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadFloats(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadInts(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects, CdbDataAccess::EodbcBaseType p_eOdbcType);
    int ReadLongs(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadObjectRefs(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadObjectListRefs(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadStrings(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    int ReadTimes(QString p_qstrInString, QMap<qint64, CdmObject *> &p_rqmObjects);
    QString GenerateInString(QList<qint64> &p_rqvlIds);
public:
    CdbCommandLoadObjects(CdmObjectContainer* p_pContainer, QList<qint64>& p_qlObjectIds, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadObjects();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDLOADOBJECTS_H
