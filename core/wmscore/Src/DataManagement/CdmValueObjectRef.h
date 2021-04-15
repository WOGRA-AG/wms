/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMOBJECTREF_H
#define CDMOBJECTREF_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueLong.h"

// forwards

/*
 * This class implements the value reference to a single
 * object. The objectid is contained by the baseclass in
 * member value.
 */
class WMSMANAGER_API CdmValueObjectRef : public CdmValueLong 
{
    Q_OBJECT

private:    
    long m_lObjectListId;
    mutable bool m_bObjectConnected;
    QString m_qstrObjectKeyname;
    QString m_qstrContainerKeyname;
    QString m_qstrReferenceUri;

public:
    CdmValueObjectRef(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    CdmValueObjectRef( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueObjectRef(  );
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    virtual void Deploy(QVariantMap& p_rqvHash);
    CdmClass* GetClass() const;
    virtual bool ResolveValue();
    virtual void SetVariant(QVariantMap& p_rqvHash);
    CdmObject *GetEventObject();
    CdmObject *GetReferenceObjectFromEvent(CdmObject *pEventObject);
    virtual void Restore(QString p_qstrValue);
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);

public slots:
    virtual bool HasValue( ) const;
    void SetValue(long p_lObjectListId, long p_lObjectId, QString p_qstrObjectKeyname, QString p_qstrContainerKeyname);
    void SetValue( const CdmObject* p_pCdmObject);
    void SetEventValue(const CdmObject *p_pCdmObject, const CdmObject *pEventObject);
    CdmObject* GetObject( );
    long GetObjectListId( );
    long GetClassId( ) const;
    QString GetDisplayString( ) const;
    bool IsTypeOf( QString p_qstrClassName) const;

signals:
    void ObjectRefModifiedSignal( CdmObject*, CdmValue*);

private:
    CdmObject* TryToCreateOwnerObject();
    CdmObject* TryToGetOwnerObject();
    CdmObject* TryToGetOwnerObjectByEventObject(CdmObject *pEventObject);
    void SetValueVariantMap(QVariant &p_rqVariant);
    void SetValueVariantUri(QVariant& p_rqVariant);

private slots:
    void ObjectRefModifiedSlot( );

};
#endif // //CDMOBJECTREF_H
