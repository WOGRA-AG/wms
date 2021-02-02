/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CFTLQUERYELEMENT_H
#define CFTLQUERYELEMENT_H

// System and QT Inlcudes
#include <QLinkedList>
#include <QStringList>


// own Includes
#include "CdmQueryElement.h"

// Defines
#define SQL_AND "and"
#define SQL_OR "or"

// forwards
class CftlDataAccess;
class CftlCommandQuery;

/*
 * This class executes the queryelement query
 */
class CftlCommandQueryElement
{
private:
    CftlDataAccess* m_rpCftlDataAccess;
    CdmQueryElement* m_rpCdmQueryElement;
    CftlCommandQuery* m_rpCtflQuery;
    QLinkedList<CftlCommandQueryElement*> m_qvlChilds;
    QString m_qstrQuery;

public:
    CftlCommandQueryElement(CftlDataAccess* p_pCftlDataAccess,
                            CdmQueryElement* p_pCdmQueryElement,
                            CftlCommandQuery* p_rpQuery);
    ~CftlCommandQueryElement();
    QString GetCompareSign();
    QString GetCompareKeyname();
    QString GenerateQuery();
    QString GetCompareValueAsString();
    QString GenerateValueQuery();
    QString GetListCompareValueAsString();
    QString GetListCompareValueAsStringFromDecimals();

private:
    void CreateChilds(QLinkedList<CdmQueryElement*>& p_qvlChilds);
    QString GenerateOrQuery();
    QString GenerateAndQuery();
    QString ExtractCompareEntriesFromList();
    QString GenerateAndOrQuery(QString p_qstrAndOr);
    QString GenerateSelectPartOfQuery();
    void CollectChildConditions(QStringList& qstrlConditions);
    void BuildWhereClauseQuery(QStringList& qstrlConditions, QString& qstrQuery, QString& p_qstrAndOr);
    QString GenerateValueConditionObjectId();
    bool IsCompareValueValid(QString &p_qstrCompareValue);
    QString getComparisionValueFromQueryElement(EdmValueType p_eType);
};

#endif //
