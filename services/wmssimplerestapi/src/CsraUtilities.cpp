// System and Qt Includes



// WMS Commons Includes
#include "wmsdefines.h"
#include "CwsHttpResponse.h"

// WMS COnre Includes
#include "CsaQuery.h"
#include "CsaFactory.h"
#include "CsaObjectContainer.h"
#include "CdmQueryElement.h"
#include "CdmClass.h"
#include "CdmQueryBuilder.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"

// Own Includes
#include "CsraUtilities.h"

CdmQuery* CsraUtilities::buildAndExecuteQuery(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer, QString& qstrCondition)
{
    QString qstrQuery = generateWql(p_pClass, p_pContainer, qstrCondition);
    return dynamic_cast<CdmQuery*> (CdmQueryBuilder::ExecuteQuery(qstrQuery));
}

CdmQuery* CsraUtilities::buildAndExecuteQuery(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer)
{
    QString qstrQuery = generateWql(p_pClass, p_pContainer, "");
    return dynamic_cast<CdmQuery*> (CdmQueryBuilder::ExecuteQuery(qstrQuery));
}

CdmQuery* CsraUtilities::buildAndExecuteQuery(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer, int p_iFrom, int p_iTo)
{
    QString qstrCondition;
    QString qstrQuery = generateWql(p_pClass, p_pContainer, qstrCondition, p_iFrom, p_iTo);
    return dynamic_cast<CdmQuery*> (CdmQueryBuilder::ExecuteQuery(qstrQuery));
}

CdmQuery* CsraUtilities::buildAndExecuteQuery(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer, QString& qstrCondition, int p_iFrom, int p_iTo)
{
    QString qstrQuery = generateWql(p_pClass, p_pContainer, qstrCondition, p_iFrom, p_iTo);
    return dynamic_cast<CdmQuery*> (CdmQueryBuilder::ExecuteQuery(qstrQuery));
}

QString CsraUtilities::generateWql(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer, int p_iFrom, int p_iTo)
{
    QString qstrCondition;
    return generateWql(p_pClass, p_pContainer, qstrCondition, p_iFrom, p_iTo);
}

QString CsraUtilities::generateWql(CdmObjectContainer* p_pContainer, int p_iFrom, int p_iTo)
{
    QString qstrResult;

    if (CHKPTR(p_pContainer))
    {
        const CdmClass* pClass = p_pContainer->GetClass();
        QString qstrCondition;
        qstrResult = generateWql(pClass, p_pContainer, qstrCondition, p_iFrom, p_iTo);
    }

    return qstrResult;
}

QString CsraUtilities::generateWql(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer, QString& qstrCondition, int p_iFrom, int p_iTo)
{
    QString qstrQuery = generateWql(p_pClass, p_pContainer, qstrCondition);
    p_iTo = p_iTo - p_iFrom + 1;

    qstrQuery += " limit " + QString::number(p_iFrom) + ", " + QString::number(p_iTo);
    return qstrQuery;
}

QString CsraUtilities::generateWql(CdmObjectContainer* p_pContainer)
{
    QString qstrRet;
    const CdmClass* pClass = nullptr;

    if (CHKPTR(p_pContainer))
    {   pClass = p_pContainer->GetClass();

        if (CHKPTR(pClass))
        {
            qstrRet = generateWql(pClass, p_pContainer, "");
        }
    }

    return qstrRet;
}

QString CsraUtilities::generateWql(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer)
{
    return generateWql(p_pClass, p_pContainer, "");
}

QString CsraUtilities::generateWql(const CdmClass* p_pClass, CdmObjectContainer* p_pContainer, QString qstrCondition)
{
    QString qstrQuery = generateSelectPartOrQuery(p_pClass) + "from " + p_pContainer->GetKeyname();

    if (!qstrCondition.isEmpty())
    {
        qstrQuery += " where " + qstrCondition;
    }

    return qstrQuery;
}


QString CsraUtilities::generateSelectPartOrQuery(const CdmClass* p_pClass)
{
    QString qstrSelect = "select ";
    QStringList qstrlDisplayMembers = getDisplayMembers(p_pClass);


    for (int iPos = 0; iPos < qstrlDisplayMembers.count(); ++iPos)
    {
        if (iPos > 0)
        {
            qstrSelect += ", ";
        }

        qstrSelect += qstrlDisplayMembers[iPos];
    }

    qstrSelect += " ";
    return qstrSelect;
}

QStringList CsraUtilities::getDisplayMembers(const CdmClass* p_pClass)
{
    QStringList qstrlMembers;
    if (CHKPTR(p_pClass))
    {
        QMap<qint64, CdmMember*> qmMembers;
        p_pClass->GetMemberMap(qmMembers);
        QList<CdmMember*> qlMembers = qmMembers.values();

        for (int iPos = 0; iPos < qlMembers.count(); ++iPos)
        {
            CdmMember* pMember = qlMembers[iPos];

            if (CHKPTR(pMember) && pMember->IsDisplayMember())
            {
                qstrlMembers.append(pMember->GetKeyname());
            }
        }
    }

    return qstrlMembers;
}

void CsraUtilities::executeQuery(CsaFactory* p_pFactory, QString p_qstrQuery, CwsHttpResponse* p_pResponse, QVariantMap& qvm)
{
    if (CHKPTR(p_pFactory))
    {
        CsaQuery* pQuery =  dynamic_cast<CsaQuery*> (p_pFactory->createQuery(p_qstrQuery));

        if (CHKPTR(pQuery))
        {
            pQuery->execute();
            QVariant qvResult = pQuery->getDetailedVariant();
            qvm.insert(WMS_RESULT, qvResult);
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeOk);
        }
        else
        {
            ERR("Invalid Query");
            p_pResponse->SetStatusCode(eWmsHttpStatusCodeInternalServerError);
        }
    }
}

void CsraUtilities::createAndExecuteQuery(CsaObjectContainer* p_pContainer, CwsHttpResponse* p_pResponse, QVariantMap& qvm)
{
    if (CHKPTR(p_pContainer))
    {
        QString qstrQuery = generateWql(p_pContainer->getInternals());
        executeQuery(dynamic_cast<CsaFactory*> (p_pContainer->getFactory()), qstrQuery, p_pResponse, qvm);
    }
}

void CsraUtilities::createAndExecuteQuery(CsaObjectContainer* p_pContainer, CwsHttpResponse* p_pResponse, QVariantMap& qvm, int p_iFrom, int p_iTo)
{
    if (CHKPTR(p_pContainer))
    {
        QString qstrQuery = generateWql(p_pContainer->getInternals(), p_iFrom, p_iTo);
        executeQuery(dynamic_cast<CsaFactory*> (p_pContainer->getFactory()), qstrQuery, p_pResponse, qvm);
    }
}
