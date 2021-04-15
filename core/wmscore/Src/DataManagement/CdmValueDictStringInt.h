#ifndef CDMDICTSTRINGINT_H
#define CDMDICTSTRINGINT_H

// Sytsem and QT Includes
#include <QMap>

// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueDictStringInt : public CdmValueCharacterDocument
{
    Q_OBJECT
private:
    /*
       * The list of strings
       */
    QMap<QString,int> m_qmMap;

public:
    CdmValueDictStringInt( long p_lDatabaseId,
                           long p_lId,
                           QString p_qstrKeyname,
                           CdmObject* p_pCdmObject);

    virtual void SetValue(QString p_qstrValue);
    virtual QString GetValue() const;
    virtual ~CdmValueDictStringInt( );
    CdmValueDictStringInt( QVariantMap& p_rqvHash, CdmObject* p_pCdmObejct);
    QVariant GetValueVariant() const;
    static void DeserializeXmlToMap(QString &p_qstrXml, QMap<QString, int> &p_qmMap);

public slots:
    virtual void SetValueVariant(QVariant& p_rVariant);
    void SetValue( QMap<QString, int> p_qmValue);
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual QString GetValueAsString( ) const;
    bool ExistValue( QString p_qstrKey) const;
    int GetValue( QString p_qstrKey) const;
    void ClearDict( );
    void SetValue( QString p_qstrKey, int p_iData);
    void RemoveValue( QString p_qstrKey);
    QMap<QString, int> GetDict( ) const;

private:
    void Serialize() const;
    void Deserialize();

};

#endif //
