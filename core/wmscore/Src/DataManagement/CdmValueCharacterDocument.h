/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMCHARACTERDOCUMENT_H
#define CDMCHARACTERDOCUMENT_H


// System and QT Includes
#include <qstring.h>

// own Includes
#include "CdmValue.h"

// forwards


/*
 * This class implements the character document value
 * this is a document which consists of characters like
 * xml documents
 */
class WMSMANAGER_API CdmValueCharacterDocument : public CdmValue
{
    Q_OBJECT

protected:
    /*
    * The Document Value
    */
    mutable QString m_qstrDocument;

public:
    CdmValueCharacterDocument(QVariantMap& p_rqHash, CdmObject* p_pCdmObject);
    CdmValueCharacterDocument(long p_lDatabaseId,
                              long p_lId,
                              QString p_qstrKeyname,
                              CdmObject* p_pCdmObject);
    virtual ~CdmValueCharacterDocument();
    virtual void SetValue(QString p_qstrDocument);
    virtual QString GetValue() const;
    virtual void SetDefaultValue(const CdmMember* p_pCdmMember);
    QString GetDisplayString() const;
    int FromStringToValue(QString p_qstrValue);

public:
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
    CdmValueCharacterDocument( long p_lDatabaseId,
                               long p_lId,
                               QString p_qstrKeyname,
                               EdmValueType p_edmValue,
                               CdmObject* p_pCdmObject);
    virtual QVariant GetVariant() const;
    virtual void SetValueVariant(QVariant& p_rqVariant);
    virtual QVariant GetValueVariant() const;
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);

    virtual void SetVariant(QVariantMap& p_rqvHash);
    virtual void Restore(QString p_qstrValue);
};

#endif //
