#ifndef CDMQUERYBUILDER_H
#define CDMQUERYBUILDER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QString>

// Own Includes
#include "datamanager.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryElement.h"


// Forwards
class CdmQuery;
class CdmObjectContainer;

// TypeDefs

// defines
#define EXECUTE_QUERY(q) QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(q));

/* 
 * This class implements the Query builder. It creates a CdmQuery Object by parsing a string
 */
class WMSMANAGER_API CdmQueryBuilder : public QObject
{
    Q_OBJECT

private:
    QString m_qstrQuery;
    QMap<QString, QString> m_qmValueMap; // <Key, Value>
    CdmObjectContainer* m_rpContainer;
    bool bProcessed;

public:
    CdmQueryBuilder(QString p_qstrQuery);
    CdmQueryBuilder(QString p_qstrQuery, CdmObjectContainer* p_pContainer);
    virtual ~CdmQueryBuilder();
    static CdmQuery* BuildQuery(QString p_qstrQuery);
    static CdmQuery* BuildQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer);
    static CdmQuery* ExecuteQuery(QString p_qstrQuery);
    static CdmQuery* ExecuteQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer);
    static QString BuildString(CdmQuery* p_pCdmQuery);
    QString GetFinalWql();
    CdmQuery* GenerateQuery();
    void AddValueEntry(QString p_qstrKey, QString p_qstrValue);

private:
    void ExecutePreProcessor();
    void SetContainer(CdmObjectContainer* p_pContainer);
    static QString ReadRequestMembersFromQuery(CdmQuery* p_pCdmQuery);
    static QString ReadObjectListKeyname(CdmQuery* p_pCdmQuery);
};

#endif // CDMQUERYBUILDER_H
