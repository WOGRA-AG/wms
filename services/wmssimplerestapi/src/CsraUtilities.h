#ifndef CSRAUTILITIES_H
#define CSRAUTILITIES_H

// System and Qt Includes
#include <QStringList>
#include "QVariantList"

// Forwards
class CdmQueryEnhanced;
class CdmObjectContainer;
class CsaObjectContainer;
class CdmClass;
class CwsHttpResponse;
class CsaFactory;


class CsraUtilities
{
public:

    static QStringList getDisplayMembers(const CdmClass *p_pClass);
    static QString generateSelectPartOrQuery(const CdmClass *p_pClass);
    static QString generateWql(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer, QString qstrCondition);
    static QString generateWql(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer);
    static QString generateWql(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer, QString &qstrCondition, int p_iFrom, int p_iTo);
    static QString generateWql(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer, int p_iFrom, int p_iTo);
    static CdmQueryEnhanced *buildAndExecuteQuery(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer, QString &qstrCondition, int p_iFrom, int p_iTo);
    static CdmQueryEnhanced *buildAndExecuteQuery(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer, int p_iFrom, int p_iTo);
    static CdmQueryEnhanced *buildAndExecuteQuery(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer);
    static CdmQueryEnhanced *buildAndExecuteQuery(const CdmClass *p_pClass, CdmObjectContainer *p_pContainer, QString& qstrCondition);
    static void executeQuery(CsaFactory* p_pFactory, QString p_qstrQuery, CwsHttpResponse* p_pResponse, QVariantMap& qvm);
    static QString generateWql(CdmObjectContainer *p_pContainer);
    static QString generateWql(CdmObjectContainer *p_pContainer, int p_iFrom, int p_iTo);
    static void createAndExecuteQuery(CsaObjectContainer *p_pContainer, CwsHttpResponse* p_pResponse, QVariantMap &qvm);
    static void createAndExecuteQuery(CsaObjectContainer *p_pContainer, CwsHttpResponse* p_pResponse, QVariantMap &qvm, int p_iFrom, int p_iTo);
};

#endif // CSRAUTILITIES_H
