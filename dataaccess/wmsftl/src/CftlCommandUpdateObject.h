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
       qint64 UpdateNewOrModifiedObject();
       qint64 InsertOrUpdateValue(CdmValue *p_pValue);
       qint64 InsertValue(CdmValue *p_pValue);
       qint64 UpdateValue(CdmValue *p_pValue);
       qint64 UpdateValueTable(CdmValue *p_pValue);
       qint64 InsertValue(CdmValue *p_pValue, CftlDataAccess::EodbcBaseType p_eOdbcBaseType);
       qint64 InsertBool(CdmValueBool *p_pCdmBool);
       qint64 UpdateBool(CdmValueBool *p_pCdmBool);
       qint64 InsertInt(CdmValueInt *p_pCdmInt, CftlDataAccess::EodbcBaseType p_eOdbcType);
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
       qint64 InsertCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CftlDataAccess::EodbcBaseType p_eType);
       qint64 UpdateCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, CftlDataAccess::EodbcBaseType p_eType);
       qint64 UpdateString(CdmValueString *p_pCdmString);
       qint64 UpdateContainerRef(CdmValueContainerRef *p_pContainerRef);
        void GetCounterValue(CdmValueCounter *p_pCdmCounter);
       qint64 GetCounterValue(qint64 p_lObjectListId,qint64 p_lValueId, QString p_qstrKeyname);
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
