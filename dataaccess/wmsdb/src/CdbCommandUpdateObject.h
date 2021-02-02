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
        long m_lSessionId;
        CdmObject* m_rpObject;
        long UpdateNewOrModifiedObject();
        long InsertOrUpdateValue(CdmValue *p_pValue);
        long InsertValue(CdmValue *p_pValue);
        long UpdateValue(CdmValue *p_pValue);
        long UpdateValueTable(CdmValue *p_pValue);
        long InsertValue(CdmValue *p_pValue, CdbDataAccess::EodbcBaseType p_eOdbcBaseType);
        long InsertBool(CdmValueBool *p_pCdmBool);
        long UpdateBool(CdmValueBool *p_pCdmBool);
        long InsertInt(CdmValueInt *p_pCdmInt, CdbDataAccess::EodbcBaseType p_eOdbcType);
        long UpdateInt(CdmValueInt *p_pCdmInt);
        long InsertLong(CdmValueLong *p_pCdmLong);
        long UpdateLong(CdmValueLong *p_pCdmLong);
        long InsertFloat(CdmValueFloat *p_pCdmFloat);
        long UpdateFloat(CdmValueFloat *p_pCdmFloat);
        long InsertDouble(CdmValueDouble *p_pCdmDouble);
        long UpdateDouble(CdmValueDouble *p_pCdmDouble);
        long InsertString(CdmValueString *p_pCdmString);
        long InsertDate(CdmValueDate *p_pCdmDate);
        long UpdateDate(CdmValueDate *p_pCdmDate);
        long InsertTime(CdmValueTime *p_pCdmTime);
        long UpdateTime(CdmValueTime *p_pCdmTime);
        long InsertDateTime(CdmValueDateTime *p_pCdmDateTime);
        long UpdateDateTime(CdmValueDateTime *p_pCdmDateTime);
        long InsertObjectRef(CdmValueObjectRef *p_pCdmObjectRef);
        long UpdateObjectRef(CdmValueObjectRef *p_pCdmObjectRef);
        long InsertContainerRef(CdmValueContainerRef *p_pContainerRef);
        long InsertCounter(CdmValueCounter *p_pCdmCounter);
        long UpdateCounter(CdmValueCounter *p_pCdmCounter);
        long InsertBinaryDocument(CdmValueBinaryDocument *p_pCdmBinaryDocument);
        QString ShortFilename(QString p_qstrFilename);
        long UpdateBinaryDocument(CdmValueBinaryDocument *p_pCdmBinaryDocument);
        long InsertCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CdbDataAccess::EodbcBaseType p_eType);
        long UpdateCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CdbDataAccess::EodbcBaseType p_eType);
        long UpdateString(CdmValueString *p_pCdmString);
        long UpdateContainerRef(CdmValueContainerRef *p_pContainerRef);
        void GetCounterValue(CdmValueCounter *p_pCdmCounter);
public:
        CdbCommandUpdateObject(long p_lSessionId, CdmObject* p_pObject, CdbDataAccess* p_pDataAccess);
        ~CdbCommandUpdateObject();

    protected:
        bool CheckValid();
        int Execute();

};

#endif // CDBCOMMANDUPDATEOBJECT_H
