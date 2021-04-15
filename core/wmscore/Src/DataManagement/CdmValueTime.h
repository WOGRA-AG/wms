/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMTIME_H
#define CDMTIME_H


// System and QT Includes
#include <qdatetime.h>

// own includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements the value time
 */
class WMSMANAGER_API CdmValueTime : public CdmValue 
{
    Q_OBJECT

private:
    /*
       * The Value Time
       */
    QTime m_qtValue;

public:
    CdmValueTime(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueTime(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueTime();
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    void GetValue(double& p_dTime) const;
    virtual QString GetDisplayString() const;
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    void SetValue(const QTime& p_rqtTime);
    QTime GetValue() const;
    virtual QVariant GetValueVariant() const;
    void SetValue(double p_dTime);

};
#endif // //CDMTIME_H
