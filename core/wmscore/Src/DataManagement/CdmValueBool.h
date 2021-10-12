/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMBOOL_H
#define CDMBOOL_H

// System and QT Includes


// own Incldues
#include "CdmMember.h"
#include "CdmValue.h"

// forwards
class QString;

/**
 * This class implements the Bool value
 */
class WMSMANAGER_API CdmValueBool : public CdmValue 
{
    Q_OBJECT

private:
    /*
       * The Value
       */
    bool m_bValue;

public:
    virtual ~CdmValueBool();
    CdmValueBool(qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueBool(QVariantMap& p_qVariant, CdmObject* p_pCdmObject);
    void SetDefaultValue(const CdmMember* p_pCdmMember);
    void FromStringToValue(QString p_qstrValue);
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);

public slots:
    void SetValue(bool p_bValue);
    bool GetValue() const;
    QString GetDisplayString() const;
    virtual QString GetValueAsString() const;

private:
    void XmlImportBool(QDomElement& p_rqDomElement);

};
#endif // //CDMBOOL_H
