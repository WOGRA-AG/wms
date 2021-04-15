#ifndef CDMINTLIST_H
#define CDMINTLIST_H

// Sytsem and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"
#include <QLinkedList>

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueListInt : public CdmValueCharacterDocument
{
    Q_OBJECT

private:
    /*
       * The list of ints
       */
    QLinkedList<int> m_qvlInts;

public:
    CdmValueListInt( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);
    virtual ~CdmValueListInt( );
    virtual void SetValue(QString p_qstrValue);
    virtual QString GetValue() const;
    QVariant GetValueVariant() const;
    static void DeserializeXmlToIntList(QString &p_qstrXml, QLinkedList<int> &p_qllList);
    CdmValueListInt( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual void Deploy(QVariantMap& p_rqvHash);

private:
    void Serialize() const;
    void Deserialize();

public slots:
    void AddValue( int p_iValue);
    void RemoveValue( int p_iValue);
    QLinkedList<int> GetList( ) const;
    virtual void SetValueVariant(QVariant& p_rVariant);
    void SetList( QLinkedList<int> p_qllInts);
    virtual QString GetValueAsString( ) const;
};

#endif //
