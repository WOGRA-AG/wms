#ifndef CDMVALUELISTOBJECTS_H
#define CDMVALUELISTOBJECTS_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QLinkedList>

// Own Includes
#include "CdmValueCharacterDocument.h"


// Forwards
class CdmObject;



// Enumerations

/* 
 * This class implements the list of objects value
 */
class WMSMANAGER_API CdmValueListObjects : public CdmValueCharacterDocument
{
    Q_OBJECT

private:
    QLinkedList<QPair<long, long> > m_qllObjects;

public:
    CdmValueListObjects( long p_lDatabaseId,
                         long p_lId,
                         QString p_qstrKeyname,
                         CdmObject* p_pCdmObject);
    CdmValueListObjects( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);
    virtual ~CdmValueListObjects( );
    void GetList(QLinkedList<CdmObject*>& p_rqvlObjects) const;
    void AddValue(CdmObject* p_pCmObject);
    void AddEventValue(CdmObject *pCdmObject, CdmClass *pObjectClass);
    void RemoveValue(CdmObject* p_pCdmObject);
    void SetList(QLinkedList<CdmObject*>& p_rqvlObjects);
    void Deserialize();
    void Serialize() const;
    void RemoveValue(long p_iKey);
    void SetValue(int p_iKey, int p_iData);
    void ClearList();
    void SetValueVariant(QVariant &p_rVariant);
    QVariant GetValueVariant() const;
    QString GetValueAsString() const;
    void Deploy(QVariantMap &p_rqvHash);
    void SetValue(QString p_qstrValue);
    QString GetValue() const;

public slots:
    CdmObject* FindObjectById( int p_iId);
};

#endif //
