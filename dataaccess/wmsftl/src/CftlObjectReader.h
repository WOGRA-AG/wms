#ifndef CFTLOBJECTREADER_H
#define CFTLOBJECTREADER_H

// System and Qt Includes
#include <QSqlQuery>

// WMS CORE Includes
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmValueCharacterDocument.h"
#include "CdmLogging.h"

// Own Includes
#include "CftlContainerTableSelect.h"

class CftlObjectReader
{
public:
    static qint64 ReadValues(CftlContainerTableSelect& selector, QSqlQuery& cQSqlQuery, CdmObject* p_pObject);
private:
    static int ReadBinaryDocument(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadBool(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadCharacterDocument(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static CdmValueCharacterDocument *CreateCharDocValue(EdmValueType p_eType,qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject *p_pCdmObjectOwner);
    static int ReadCounter(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadDate(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadDateTime(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadDouble(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadFloat(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadInt(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadLong(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadObjectRef(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadContainerRef(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadString(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static int ReadTime(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject);
    static void SetMemberDataToValue(CdmValue *p_pValue, const CdmMember *p_pMember);
    static void SetObjectDataToValue(CdmValue *p_pValue, CdmObject *p_pObject);
};

#endif // CFTLOBJECTREADER_H
