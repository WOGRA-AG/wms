#ifndef CDMDICTSTRINGDOUBLE_H
#define CDMDICTSTRINGDOUBLE_H

// Sytsem and QT Includes
#include <qmap.h>

// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueDictStringDouble : public CdmValueCharacterDocument
{
    Q_OBJECT

private:
    QMap<QString,double> m_qmMap;

public:
    CdmValueDictStringDouble( long p_lDatabaseId,
                              long p_lId,
                              QString p_qstrKeyname,
                              CdmObject* p_pCdmObject);
    CdmValueDictStringDouble( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

    virtual ~CdmValueDictStringDouble( );
    virtual void SetValue(QString p_qstrValue);
    virtual QString GetValue() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    QVariant GetValueVariant() const;
    static void DeserializeXmlToMap(QString &p_qstrDocument, QMap<QString, double> &p_qmMap);

public slots:
    void ClearDict();
    virtual QString GetValueAsString( ) const;
    void SetValue(QMap<QString, double> p_qmValue);
    virtual void SetValueVariant(QVariant& p_rVariant);
    void SetValue(QString p_qstrKey, double p_dData);
    void RemoveValue( QString p_qstrKey);
    QMap<QString, double> GetDict( ) const;

private:
    void Serialize() const;
    void Deserialize();


};

#endif //
