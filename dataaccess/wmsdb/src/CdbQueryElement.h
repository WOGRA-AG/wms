#ifndef CODBCQUERYELEMENT_H
#define CODBCQUERYELEMENT_H

// System and QT Inlcudes
#include <QLinkedList>


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
    QLinkedList<CdbQueryElement*> m_qvlChilds;
    QString m_qstrQuery;

public:
    CdbQueryElement(CdbDataAccess* p_pCdbDataAccess, CdmQueryElement* p_pCdmQueryElement );
    ~CdbQueryElement();
    QString GenerateQuery();
    long Execute(QMap<long, long>& p_rqvlResultList);
    QString GetCompareSign();
    QString GetTableName();
    QString GetTableIdName();
    QString GetCompareValueAsString();
    QString GetListCompareValueAsString();
    QString GetDataFieldName();

private:
    void CreateChilds(QLinkedList<CdmQueryElement*> &p_qvlChilds);
    long ExecuteValue(QMap<long,long> &p_rqvlResults);
    QString GenerateValueQuery();
    QString GenerateOrQuery();
    QString GenerateAndQuery();
    QString ExtractCompareEntriesFromList();
};

#endif //
