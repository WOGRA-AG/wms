#ifndef ISAVALUE_H
#define ISAVALUE_H

//Qt includes
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QDate>
#include <QDateTime>
#include <QTime>

//wms includes
#include "CdmValue.h"

//forwards
class CsaValue;

class IsaValue
{
public slots:
    virtual QObject* getMember() = 0;
    virtual QVariant getValue() = 0;
    virtual EdmValueType getType() = 0;
    virtual bool getValueAsBool() = 0;
    virtual QString toString() = 0;
    virtual bool isDate() = 0;
    virtual bool isTime() = 0;
    virtual bool isDateTime() = 0;
    virtual QDateTime getValueDateTime() = 0;
    virtual QDate getValueDate() = 0;
    virtual QTime getValueTime() = 0;
    virtual QString getBinDocFileName() = 0;
    virtual void openBinDoc() = 0;
    virtual bool isReadOnly() = 0;
    virtual QString getSelectionModel() = 0;
    virtual int getSelectionValueIndex() = 0;
    virtual QString getJson() = 0;
    virtual QString getListObjectsEntries() = 0;
    virtual QVariant getListObjectsEntriesVariant() = 0;
    virtual bool isListOfObjects() = 0;
    virtual QVariant getValueReference() = 0;
    virtual QVariantList getListObjects() = 0;
    virtual QVariantList getListInts() = 0;
    virtual QVariantList getListDoubles() = 0;
    virtual QVariantList getListStrings() = 0;

//    virtual CdmValue* getInternals();
//    virtual void setSelectionValue(int p_iId);
//    virtual void setValueBool(bool p_bValue);
//    virtual void setValueObject(CsaValue* p_pValue);
//    virtual void setValue(QVariant p_qvValue);
//    virtual void setValueDate(QDate p_qdDate);
//    virtual void setValueDateTime(QDateTime p_qdtDateTime);
//    virtual void setValueTime(QTime p_qtTime);
//    virtual bool removeListValue(QString p_qstrValue);
//    virtual bool addListValue(QString p_qstrValue);
//    virtual void setValueReference(QObject *p_pObject);
};

#endif // ISAVALUE_H
