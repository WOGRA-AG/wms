#ifndef CODBCQUERYELEMENT_H
#define CODBCQUERYELEMENT_H

// System and QT Inlcudes
#include <QList>


// own Includes
#include "CdmQueryElement.h"


// forwards
class CdbDataAccess;

/*
 * This class executes the queryelement query
 */
class CdbQueryElement
{
private:
    CdbDataAccess* m_rpCdbDataAccess;
    CdmQueryElement* m_rpCdmQueryElement;
    QList<CdbQueryElement*> m_qvlChilds;
    QString m_qstrQuery;

public:
    CdbQueryElement(CdbDataAccess* p_pCdbDataAccess, CdmQueryElement* p_pCdmQueryElement );
    ~CdbQueryElement();
    QString GenerateQuery();
   qint64 Execute(QMap<qint64,qint64>& p_rqvlResultList);
    QString GetCompareSign();
    QString GetTableName();
    QString GetTableIdName();
    QString GetCompareValueAsString();
    QString GetListCompareValueAsString();
    QString GetDataFieldName();

private:
    void CreateChilds(QList<CdmQueryElement*> &p_qvlChilds);
   qint64 ExecuteValue(QMap<qint64,qint64> &p_rqvlResults);
    QString GenerateValueQuery();
    QString GenerateOrQuery();
    QString GenerateAndQuery();
    QString ExtractCompareEntriesFromList();
};

#endif //
