#ifndef CWNQUERY_H
#define CWNQUERY_H

// System and QT Includes
#include <QLinkedList>
#include <QMap>

#include "CwnHelper.h"
#include "CwnQueryVariables.h"

#include "CwnCommandStdHeader.h"
#include "CwnCommandBase.h"

#include "wmsneo4j.h"

// forwards
class CwnDataAccess;
class CdmQuery;
class CwnQueryElement;

/*
 * This class implements the queries on db side
 */
class WMSNEO4J_API CwnQuery : public CwnCommandBase
{
private:
   CwnDataAccess* m_rpCwnDataAccess;
   CdmQuery*        m_rpCdmQuery;

   QString GenerateReturnStatement();
   QString MakeKeynameSave(QString p_qstrKeyname);

public:
    CwnQuery(CwnDataAccess* p_pCwnDataAccess, CdmQuery* p_pCdmQuery);
    virtual ~CwnQuery();
    QString GenerateQueryCypher();
    QString queryCausedError;

    int m_iKeynameCount;
    QMap<QString, int> m_qmKeynames;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNQUERY_H
