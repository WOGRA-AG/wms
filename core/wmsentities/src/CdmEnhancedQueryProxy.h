﻿#ifndef CDMENHANCEDQUERYPROXY_H
#define CDMENHANCEDQUERYPROXY_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
//#include <QAbstractItemView>
#include <QAbstractTableModel>
#include <QTimer>

// WMS Manager Includes
#include "CdmContainerAdaptor.h"

// Own Includes
#include "CdmQueryModel.h"
#include "basetools.h"


// Forwards
class CdmObjectContainer;
class CdmQueryEnhanced;

// Enumerations

/* 
 * This class implements the proxy for table/tree views of queries
 */
class BASETOOLS_API CdmEnhancedQueryProxy : public CdmQueryModel
{
    Q_OBJECT

protected:
    bool m_bOrderbyModeAsc;
    QStringList m_qstrOrderBy;
public:
    CdmEnhancedQueryProxy();
    virtual ~CdmEnhancedQueryProxy();
    virtual void GetDisplayListV(CdmObjectContainer* p_pContainer, QList<qint64>& p_rqvlResults);
    virtual CdmQuery* GetQuery();
    virtual void CreateQuery(CdmObjectContainer* p_pContainer);

protected:
    virtual void ValueChanged();
    virtual void sort(int p_iColumn, Qt::SortOrder p_eSortOrder);
    virtual void ObjectCommitedEvent(qint64);
    void ClearOrderBy();
public:
    QStringList GetOrderBy();
    void SetOrderByMode(bool p_bAsc);
    bool GetOrderByMode();
    void AddOrderBy(QString p_qstrOrderBy);


public slots:
    virtual void Execute();
    bool IsInResult(CdmObject* p_pCdmObject);
    bool IsInResult(qint64 p_lObjectId, CdmObjectContainer* p_pContainer);
    void GetDisplayList(CdmObjectContainer* p_pContainer, QList<qint64>& p_rqvlResults);
    int GetFirstResult(CdmObjectContainer* p_pContainer);
    void GetDisplaySet(CdmObjectContainer* p_pContainer, QSet<qint64>& p_rqsResult);
    virtual void GetDisplaySetV(CdmObjectContainer* p_pContainer, QSet<qint64>& p_rqsResult);
};

#endif //
