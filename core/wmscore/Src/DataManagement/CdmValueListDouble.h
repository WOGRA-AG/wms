#ifndef CDMDOUBLELIST_H
#define CDMDOUBLELIST_H

// Sytsem and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"
#include <QList>

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueListDouble : public CdmValueCharacterDocument 
{
    Q_OBJECT

private:
    QList<double> m_qvlDoubles;

public:
    CdmValueListDouble(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    virtual ~CdmValueListDouble();
    virtual void SetValue(QString p_qstrValue);
    virtual QString GetValue() const;
    CdmValueListDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual QVariant GetValueVariant() const;
    static void DeserializeXmlToDoubleList(QString &p_qstrXml, QList<double> &p_qllList);

public slots:
    void AddValue(double p_dValue);
    void RemoveValue(double p_dValue);
    QList<double> GetList() const;
    void SetList( QList<double> p_qllDoubles);
    virtual QString GetValueAsString() const;
    virtual void SetValueVariant(QVariant& p_rVariant);

private:
    void Serialize() const;
    void Deserialize();
};

#endif //
