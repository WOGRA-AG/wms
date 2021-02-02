#ifndef CWNCOMMANDUPDATEOBJECT_H
#define CWNCOMMANDUPDATEOBJECT_H

#include "CwnCommandBase.h"
#include "CdmModelElement.h"

#include <QQueue>
#include <QVector>

// forwards
class CwnDataAccess;
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
class CdmValueCounter;

class CwnCommandUpdateObject : public CwnCommandBase
{
    private:
        QString createQueryForUpdateObjects();
        QString getLabel(EdmValueType p_eBaseType);

        QString payload;
        long m_lSessionId;
        CdmObject* m_rpObject;

        QQueue<CdmValue*> editValues;

        bool counterAdded=false;
        QVector<CdmValueCounter*> counterValueList;

        //long UpdateNewOrModifiedObject();
        void InsertOrUpdateValue(CdmValue *p_pValue);
        void InsertValue(CdmValue *p_pValue);
        void UpdateValue(CdmValue *p_pValue);
        void UpdateValueTable(CdmValue *p_pValue, QString &qstrQuery);
        void InsertValue(CdmValue *p_pValue, EdmValueType p_eType, QString &qstrQuery);
        void InsertBool(CdmValueBool *p_pCdmBool);
        void UpdateBool(CdmValueBool *p_pCdmBool, QString &qstrQuery, bool insert);
        void InsertInt(CdmValueInt *p_pCdmInt, EdmValueType p_eType);
        void UpdateInt(CdmValueInt *p_pCdmInt, EdmValueType p_eType, QString &qstrQuery, bool insert);
        void InsertLong(CdmValueLong *p_pCdmLong);
        void UpdateLong(CdmValueLong *p_pCdmLong, QString &qstrQuery, bool insert);
        void InsertFloat(CdmValueFloat *p_pCdmFloat);
        void UpdateFloat(CdmValueFloat *p_pCdmFloat, QString &qstrQuery, bool insert);
        void InsertDouble(CdmValueDouble *p_pCdmDouble);
        void UpdateDouble(CdmValueDouble *p_pCdmDouble, QString &qstrQuery, bool insert);
        void InsertString(CdmValueString *p_pCdmString);
        void UpdateString(CdmValueString *p_pCdmString, QString &qstrQuery, bool insert);
        void InsertDate(CdmValueDate *p_pCdmDate);
        void UpdateDate(CdmValueDate *p_pCdmDate, QString &qstrQuery, bool insert);
        void InsertTime(CdmValueTime *p_pCdmTime);
        void UpdateTime(CdmValueTime *p_pCdmTime, QString &qstrQuery, bool insert);
        void InsertDateTime(CdmValueDateTime *p_pCdmDateTime);
        void UpdateDateTime(CdmValueDateTime *p_pCdmDateTime, QString &qstrQuery, bool insert);
        void InsertObjectRef(CdmValueObjectRef *p_pCdmObjectRef);
        void UpdateObjectRef(CdmValueObjectRef *p_pCdmObjectRef, QString &qstrQuery, bool insert);
        void InsertContainerRef(CdmValueContainerRef *p_pContainerRef);
        void UpdateContainerRef(CdmValueContainerRef *p_pContainerRef, QString &qstrQuery, bool insert);
        void createValueJournal(CdmValue *p_pValue);
        void InsertCounter(CdmValueCounter *p_pCdmCounter);
        void UpdateCounter(CdmValueCounter *p_pCdmCounter, QString &qstrQuery, bool insert);
        void GetCounterValue();
        long GetCounterValue(long p_lObjectListId, long p_lValueId, QString p_qstrKeyname);
        int MakeCounterValueUnique(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int p_iValueId);
        bool CheckIncreaseCounterNeeded(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int);
        int IncreaseCounterValue(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int p_iValueId);
        void InsertBinaryDocument(CdmValueBinaryDocument *p_pCdmBinaryDocument);
        void UpdateBinaryDocument(CdmValueBinaryDocument *p_pCdmBinaryDocument, QString &qstrQuery, bool insert);
        QString ShortFilename(QString p_qstrFilename);
        void InsertCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, EdmValueType p_eType);
        void UpdateCharacterDocument(CdmValueCharacterDocument *p_pCdmCharacterDocument, QString &qstrQuery, bool insert);

        void interpretAnswerForCounter(QVariant& Ret);



    public:
        CwnCommandUpdateObject(long p_lSessionId, CdmObject* p_pObject, CwnDataAccess* p_pDataAccess);
        ~CwnCommandUpdateObject();
        QString queryCausedError;

    protected:
        void interpretAnswer(QVariant& Ret);
        virtual int Execute();
        virtual bool CheckValid();

};

#endif // CWNCOMMANDUPDATEOBJECT_H
