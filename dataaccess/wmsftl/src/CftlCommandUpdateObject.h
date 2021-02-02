#ifndef CDBCOMMANDUPDATEOBJECT_H
#define CDBCOMMANDUPDATEOBJECT_H

#include "CftlAbstractTransactionalCommand.h"

// forwards
class CftlDataAccess;
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

class CftlCommandUpdateObject : public CftlAbstractTransactionalCommand
{
    private:
        CdmObject* m_rpObject;
        long UpdateNewOrModifiedObject();
        long InsertOrUpdateValue(CdmValue *p_pValue);
        long InsertValue(CdmValue *p_pValue);
        long UpdateValue(CdmValue *p_pValue);
        long UpdateValueTable(CdmValue *p_pValue);
        long InsertValue(CdmValue *p_pValue, CftlDataAccess::EodbcBaseType p_eOdbcBaseType);
        long InsertBool(CdmValueBool *p_pCdmBool);
        long UpdateBool(CdmValueBool *p_pCdmBool);
        long InsertInt(CdmValueInt *p_pCdmInt, CftlDataAccess::EodbcBaseType p_eOdbcType);
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
        long InsertCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CftlDataAccess::EodbcBaseType p_eType);
        long UpdateCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CftlDataAccess::EodbcBaseType p_eType);
        long UpdateString(CdmValueString *p_pCdmString);
        long UpdateContainerRef(CdmValueContainerRef *p_pContainerRef);
        void GetCounterValue(CdmValueCounter *p_pCdmCounter);
        long GetCounterValue(long p_lObjectListId, long p_lValueId, QString p_qstrKeyname);
        int MakeCounterValueUnique(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int p_iValueId);
        bool CheckIncreaseCounterNeeded(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int);
        int IncreaseCounterValue(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int p_iValueId);
public:
        CftlCommandUpdateObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
        ~CftlCommandUpdateObject();

    protected:
        bool CheckValid();
        int Execute();

};

#endif // CDBCOMMANDUPDATEOBJECT_H
