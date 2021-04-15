#ifndef CDMDICTSTRINGSTRING_H
#define CDMDICTSTRINGSTRING_H

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
class WMSMANAGER_API CdmValueDictStringString : public CdmValueCharacterDocument
{
    Q_OBJECT
private:
    /*
       * The list of strings
       */
    QMap<QString,QString> m_qmMap;

public:
    CdmValueDictStringString( long p_lDatabaseId,
                              long p_lId,
                              QString p_qstrKeyname,
                              CdmObject* p_pCdmObject);
    virtual ~CdmValueDictStringString( );
    virtual void SetValue(QString p_qstrValue);
    virtual QString GetValue() const;
    CdmValueDictStringString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual void Deploy(QVariantMap& p_rqvHash);
    QVariant GetValueVariant() const;
    static void DeserializeXmlToMap(QString &p_qstrXml, QMap<QString, QString> &p_qmMap);

public slots:
    virtual void SetValueVariant(QVariant& p_rVariant);
    virtual QString GetValueAsString( ) const;
    void SetValue( QMap<QString, QString> p_qmValue);
    bool ExistValue( QString p_qstrKey);
    QString GetValue( QString p_qstrKey);
    void ClearDict( );
    void SetValue( QString p_qstrKey, QString p_qstrData);
    void RemoveValue( QString p_qstrKey);
    QMap<QString, QString> GetDict( ) const;

private:
    void Serialize() const;
    void Deserialize();

};

#endif //
