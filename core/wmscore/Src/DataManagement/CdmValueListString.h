#ifndef CDMSTRINGLIST_H
#define CDMSTRINGLIST_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"
#include <QLinkedList>

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueListString : public CdmValueCharacterDocument
{
    Q_OBJECT

private:
    /*
       * The list of strings
       */
    QLinkedList<QString> m_qvlStrings;

public:
    CdmValueListString(long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    CdmValueListString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueListString();
    virtual void SetValue(QString p_qstrValue);
    virtual QString GetValue() const;
    void SetList(QLinkedList<QString> p_qllStrings);
    virtual void Deploy(QVariantMap& p_rqvHash);
    QVariant GetValueVariant() const;
    static void DeserializeXmlToStringList(QString &p_qstrXml, QLinkedList<QString> &p_qllResultList);
    QStringList GetStringList() const;
    int GetListSize() const;

public slots:
    void AddValue( QString p_qstrValue);
    void RemoveValue( QString p_qstrValue);
    QLinkedList<QString> GetList( ) const;
    void ClearList( );
    virtual QString GetValueAsString( ) const;
    virtual void SetValueVariant(QVariant& p_rVariant);

private:
    void Serialize() const;
    void Deserialize();
};

#endif //
