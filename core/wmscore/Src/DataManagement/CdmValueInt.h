/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMINT_H
#define CDMINT_H


// System and QT Includes



// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements an integer value
 */
class WMSMANAGER_API CdmValueInt : public CdmValue 
{
    Q_OBJECT

private:
    int m_iValue;

public:
    CdmValueInt(qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueInt( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    CdmValueInt( EdmValueType p_eDmValue,
                qint64 p_lDatabaseId,
                qint64 p_lId,
                 QString p_qstrKeyname,
                 CdmObject* p_pCdmObject);
    virtual ~CdmValueInt();
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    virtual QString GetDisplayString() const;
    int FromStringToValue(QString p_qstrValue);
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QVariant GetValueVariant() const;
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    void SetValue(int p_iValue);
    int GetValue() const;

};
#endif // //CDMINT_H
