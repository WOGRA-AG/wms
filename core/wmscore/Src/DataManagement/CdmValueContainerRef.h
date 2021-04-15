/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMOBJECTLISTREF_H
#define CDMOBJECTLISTREF_H

// System and QT Includes

// own Includes
#include "CdmMember.h"
#include "CdmValueLong.h"

// forwards

/*
 * This class implements the value reference to an objectlist.
 * The base class contains in value the objectlist id!!!!
 */
class WMSMANAGER_API CdmValueContainerRef : public CdmValueLong 
{
    Q_OBJECT

private:
    QString m_qstrReferenceUri;
    QString m_qstrContainerKeyname;

public:
    CdmValueContainerRef(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueContainerRef(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueContainerRef();
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Deploy(QVariantMap& p_rqvHash);
    CdmClass* GetClass();
    virtual bool ResolveValue();
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual void Restore(QString p_qstrValue);
    CdmObjectContainer* GetContainer();
    long GetClassId() const;
    CdmObjectContainer* GetEmptyContainer();

public slots:
    QString GetDisplayString() const;
    bool IsTypeOf(QString p_qstrClassName) const;
    void SetValue(CdmObjectContainer* p_pContainer);
    void SetValue(long p_lObjectListId, QString p_qstrContainerKeyname);
    void SetValue(long p_lObjectListId);
    virtual bool HasValue( ) const;

};
#endif // //CDMOBJECTLISTREF_H
