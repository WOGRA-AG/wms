/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSCRIPTOBJECT
#define CSCRIPTOBJECT

// System and QT Includes
#include <QVariant>
#include <QScriptValue>
#include <QJSValue>

// own Includes
#include "datamanager.h"
#include "IsaObject.h"
#include "CsaModelElement.h"

// Forwards
class CsaFactory;
class CsaValue;
class CsaFunction;
class CsaValueReference;
class CdmObject;
class CdmValue;

class WMSMANAGER_API CsaObject : public CsaModelElement, public IsaObject
{
	Q_OBJECT
    friend class CsaFactory;

    private:
        bool m_bThis;
        QMap<QString, CsaValue*> m_qmValues;
        QList<CsaValueReference*> m_qlReferences;
        QList<CsaFunction*> m_qlFunctions;

        void addValuesAsProperties();
        bool updateValue(QString p_qstrKeyname);

        void addFunctionsToObject();
public:
        CdmObject* getInternals();
        CsaObject(CdmObject* p_pObject, CsaFactory* p_pFactory, bool p_bThis = false);
        ~CsaObject();
        CsaObject():CsaModelElement(NULL), m_bThis(false){}    
        virtual QVariant getDetailedVariant();        
        void updateValues(QVariantMap &p_qvm);
        QList<CsaFunction *> &getFunctions();
        CsaFunction* getFunction(QString qstrName);
public slots:
        virtual QObject *findValue(QString p_qstrKeyname);
        virtual QObject* getClass();
        virtual QVariant getValuePrimitive(QString p_qstrKeyname);
        virtual QObject* getValueReference(QString p_qstrKeyname);
        virtual QDateTime getValueDateTime(QString p_qstrKeyname) const;
        virtual QDate getValueDate(QString p_qstrKeyname) const;
        virtual QTime getValueTime(QString p_qstrKeyname) const;
        virtual QString getValueString(QString p_qstrKeyname) const;
        virtual QObject* getContainer();
        virtual QObject *getValueUser(QString p_qstrKeyname);
        virtual double getValueDouble(QString p_qstrKeyname) const;
        virtual long getValueLong(QString p_qstrKeyname) const;
        virtual int getValueInt(QString p_qstrKeyname) const;
        virtual bool getValueBool(QString p_qstrKeyname) const;
        virtual float getValueFloat(QString p_qstrKeyname) const;
        virtual QString getJson();
        virtual QVariant execute(QString p_qstrMethod, QScriptValue p_qArg1 = QScriptValue(), QScriptValue p_qArg2 = QScriptValue(), QScriptValue p_qArg3 = QScriptValue(), QScriptValue p_qArg4 = QScriptValue(), QScriptValue p_qArg5 = QScriptValue(), QScriptValue p_qArg6 = QScriptValue(), QScriptValue p_qArg7 = QScriptValue(), QScriptValue p_qArg8 = QScriptValue(), QScriptValue p_qArg9 = QScriptValue(), QScriptValue p_qArg10 = QScriptValue(), QScriptValue p_qArg11 = QScriptValue(), QScriptValue p_qArg12 = QScriptValue(), QScriptValue p_qArg13 = QScriptValue(), QScriptValue p_qArg14 = QScriptValue(), QScriptValue p_qArg15 = QScriptValue());
        virtual QString getValueDisplayString(QString p_qstrKeyname);
        virtual QVariant execute(QString p_qstrFunctionName, QJSValue p_qlArguments);
        virtual bool hasOwner();
        virtual bool hasOwner(QString qstrObjectKeyname);
        virtual QObject *getOwner();
        virtual QObject *getOwner(QString qstrObjectKeyname);
        virtual bool isImmutable();
        virtual QVariantMap getObjectGraphVariant(bool p_bFollowNonOwnerObjectlist, bool p_bFollowNonOwnerObject, QStringList p_qstrExcludedKeynames, int p_iMaxDepth, int p_iMaxObjects);
        bool hasCurrentUserWriteAccess();
        bool hasCurrentUserReadAccess();

        void setValuePrimitive(QString p_qstrKeyname, QVariant p_Value);
        void setValueReference(QString p_qstrKeyname, QObject* p_pRef);
        int commit();
        void refreshObject();
        void setValueUser(QString p_qstrKeyname, QObject *p_pRef);
        void setValueString(QString p_qstrKeyname, QString p_qstrValue);
        void setValueDate(QString p_qstrKeyname, QDate p_qdDate);
        void setValueDateTime(QString p_qstrKeyname, QDateTime p_qdtDateTime);
        void setValueTime(QString p_qqstrkeyname, QTime p_qtTime);
        void setValueFloat(QString p_qstrKeyname, float p_fValue);
        void setValueDouble(QString p_qstrKeyname, double p_dValue);
        void setValueInt(QString p_qstrKeyname, int p_iValue);
        void setValueLong(QString p_qstrKeyname, long p_lValue);
        void setValueBool(QString p_qstrKeyname, bool p_bValue);
        void addValueListObjectItem(QString p_qstrKeyname, QObject* p_qObject);
        void removeValueListObjectItem(QString p_qstrKeyname, QObject* p_qObject);
        void setValueBinaryDocument(QString p_qstrKeyname, QString p_qstrFilename, QString p_qstrFiletype, QString p_qstrBase64);
        void setDeleted();
        bool isDeleted();
        bool isModified();
        void setImmutable(bool p_bImmutable);
protected:
        virtual bool eventFilter(QObject *obj, QEvent *event);
        virtual void setFactory(CsaFactory *p_pFactory);
private slots:
        void ValueChangedSlot(CdmValue *p_pCdmValue);
};

#endif //
