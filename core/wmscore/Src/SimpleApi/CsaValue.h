/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSCRIPTVALUE
#define CSCRIPTVALUE

// System and QT Includes

// own Includes
#include "CdmValue.h"
#include "datamanager.h"
#include "CsaModelElement.h"
#include "IsaValue.h"

// Forwards
class CsaObject;
class CsaFactory;

class WMSMANAGER_API CsaValue : public CsaModelElement, public IsaValue
{
    Q_OBJECT
    friend class CsaFactory;
    friend class CsaObject;

private:
    QString getUserList();
    QString getUserGroupList();
    QString getEnumList();
    QString getListElementTemplate();
    QString getListStringsQml();
    QString getListIntsQml();
    QString getListDoublesQml();
    int getUserListIndex(int p_iId);
    int getUserGroupListIndex(int p_iId);
    int getEnumListIndex(int p_iId);
public:
    CsaValue(QObject* parent = NULL): CsaModelElement(NULL, parent){}
    CsaValue(CdmValue* p_pValue, QObject* parent = NULL);
    ~CsaValue();
    CdmValue* getInternals();
    QVariant getDetailedVariant();
    QVariant getRoughVariant();

public slots:
    virtual QObject* getMember();
    virtual QVariant getValue();
    virtual EdmValueType getType();
    virtual bool getValueAsBool();
    virtual QString toString();
    virtual bool isDate();
    virtual bool isTime();
    virtual bool isDateTime();
    virtual QDateTime getValueDateTime();
    virtual QDate getValueDate();
    virtual QTime getValueTime();
    virtual QString getBinDocFileName();
    virtual void openBinDoc();
    virtual bool isReadOnly();
    virtual QString getSelectionModel();
    virtual int getSelectionValueIndex();
    virtual QString getJson();
    virtual QVariant getListObjectsEntriesVariant();
    virtual QString getListObjectsEntries();
    virtual bool isListOfObjects();
    virtual QVariantList getListObjects();
    virtual QVariantList getListInts();
    virtual QVariantList getListDoubles();
    virtual QVariantList getListStrings();
    virtual QVariant getValueReference();

    bool removeListValue(QString p_qstrValue);
    bool addListValue(QString p_qstrValue);
    void setValueBool(bool p_bValue);
    void setValueObject(CsaValue* p_pValue);
    void setValue(QVariant p_qvValue);
    void setValueDate(QDate p_qdDate);
    void setValueDateTime(QDateTime p_qdtDateTime);
    void setValueTime(QTime p_qtTime);
    void setSelectionValue(int p_iId);
    void setValueReference(QObject *p_pObject);

    bool removeDictValue(QString p_qstrKey);
    bool InsertDictValue(QString p_qstrKey, QString p_qstrValue);
    bool hasCurrentUserReadAccess();
    bool hasCurrentUserWriteAccess();
};

#endif //
