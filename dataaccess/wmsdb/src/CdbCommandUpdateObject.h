#ifndef CDBCOMMANDUPDATEOBJECT_H
#define CDBCOMMANDUPDATEOBJECT_H

#include "CdbAbstractCommandTransactional.h"

// forwards
class CdbDataAccess;
class CdmQuery;
class CdmObject;
class CdmObjectContainer;
class CdmValueBool;
class CdmValueInt;
class CdmValueFloat;
class CdmValueLong;
class CdmValueDouble;
class CdmValueString;
class CdmValueObjectRef;
class CdmValueContainerRef;
class CdmValueCharacterDocument;
class CdmValueBinaryDocument;
class CdmValueCounter;
class CdmValueDate;
class CdmValueTime;
class CdmValueDateTime;
class CdmValue;

class CdbCommandUpdateObject : public CdbAbstractCommandTransactional
{
    private:
       qint64 m_lSessionId;
        CdmObject* m_rpObject;
       qint64 UpdateNewOrModifiedObject();
       qint64 InsertOrUpdateValue(CdmValue *p_pValue);
       qint64 InsertValue(CdmValue *p_pValue);
       qint64 UpdateValue(CdmValue *p_pValue);
       qint64 UpdateValueTable(CdmValue *p_pValue);
       qint64 InsertValue(CdmValue *p_pValue, CdbDataAccess::EodbcBaseType p_eOdbcBaseType);
       qint64 InsertBool(CdmValueBool *p_pCdmBool);
       qint64 UpdateBool(CdmValueBool *p_pCdmBool);
       qint64 InsertInt(CdmValueInt *p_pCdmInt, CdbDataAccess::EodbcBaseType p_eOdbcType);
       qint64 UpdateInt(CdmValueInt *p_pCdmInt);
       qint64 InsertLong(CdmValueLong *p_pCdmLong);
       qint64 UpdateLong(CdmValueLong *p_pCdmLong);
       qint64 InsertFloat(CdmValueFloat *p_pCdmFloat);
       qint64 UpdateFloat(CdmValueFloat *p_pCdmFloat);
       qint64 InsertDouble(CdmValueDouble *p_pCdmDouble);
       qint64 UpdateDouble(CdmValueDouble *p_pCdmDouble);
       qint64 InsertString(CdmValueString *p_pCdmString);
       qint64 InsertDate(CdmValueDate *p_pCdmDate);
       qint64 UpdateDate(CdmValueDate *p_pCdmDate);
       qint64 InsertTime(CdmValueTime *p_pCdmTime);
       qint64 UpdateTime(CdmValueTime *p_pCdmTime);
       qint64 InsertDateTime(CdmValueDateTime *p_pCdmDateTime);
       qint64 UpdateDateTime(CdmValueDateTime *p_pCdmDateTime);
       qint64 InsertObjectRef(CdmValueObjectRef *p_pCdmObjectRef);
       qint64 UpdateObjectRef(CdmValueObjectRef *p_pCdmObjectRef);
       qint64 InsertContainerRef(CdmValueContainerRef *p_pContainerRef);
       qint64 InsertCounter(CdmValueCounter *p_pCdmCounter);
       qint64 UpdateCounter(CdmValueCounter *p_pCdmCounter);
       qint64 InsertBinaryDocument(CdmValueBinaryDocument *p_pCdmBinaryDocument);
        QString ShortFilename(QString p_qstrFilename);
       qint64 UpdateBinaryDocument(CdmValueBinaryDocument *p_pCdmBinaryDocument);
       qint64 InsertCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CdbDataAccess::EodbcBaseType p_eType);
       qint64 UpdateCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CdbDataAccess::EodbcBaseType p_eType);
       qint64 UpdateString(CdmValueString *p_pCdmString);
       qint64 UpdateContainerRef(CdmValueContainerRef *p_pContainerRef);
        void GetCounterValue(CdmValueCounter *p_pCdmCounter);
public:
        CdbCommandUpdateObject(qint64 p_lSessionId, CdmObject* p_pObject, CdbDataAccess* p_pDataAccess);
        ~CdbCommandUpdateObject();

    protected:
        bool CheckValid();
        int Execute();

};

#endif // CDBCOMMANDUPDATEOBJECT_H
