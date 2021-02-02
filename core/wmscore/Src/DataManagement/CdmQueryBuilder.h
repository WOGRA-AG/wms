/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmQueryBuilder.h
 ** Started Implementation: 2012/07/10
 ** Description:
 **
 ** Implements the Query builder. It creates a CdmQuery Object by parsing a string
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

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
    /** +-=---------------------------------------------------------Di 10. Jul 14:31:50 2012-------*
     * @method  CdmQueryBuilder::CdmQueryBuilder              // public                            *
     * @return                                                //                                   *
     * @param   QString p_qstrQuery                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 10. Jul 14:31:50 2012----------*/
    CdmQueryBuilder(QString p_qstrQuery);

    /** +-=---------------------------------------------------------Di 10. Jul 14:31:50 2012-------*
     * @method  CdmQueryBuilder::CdmQueryBuilder              // public                            *
     * @return                                                //                                   *
     * @param   QString p_qstrQuery                           //                                   *
     * @param   CdmObjectContainer* p_pContainer              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 10. Jul 14:31:50 2012----------*/
    CdmQueryBuilder(QString p_qstrQuery, CdmObjectContainer* p_pContainer);

    /** +-=---------------------------------------------------------Di 10. Jul 14:23:33 2012-------*
     * @method  CdmQueryBuilder::~CdmQueryBuilder             // public, virtual                   *
     * @return  void                                          //                                   *
     * @comment The Destructor of Class CdmQueryBuilder                                            *
     *----------------last changed: -----------------------------Di 10. Jul 14:23:33 2012----------*/
    virtual ~CdmQueryBuilder();

    /** +-=---------------------------------------------------------Di 10. Jul 15:25:31 2012-------*
     * @method  CdmQueryBuilder::BuildQuery                   // public, static                    *
     * @return  CdmQuery*                                     //                                   *
     * @param   QString p_qstrQuery                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 10. Jul 15:25:31 2012----------*/
    static CdmQuery* BuildQuery(QString p_qstrQuery);
    static CdmQuery* BuildQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer);

    /** +-=---------------------------------------------------------Do 26. Jul 16:04:58 2012-------*
     * @method  CdmQueryBuilder::ExecuteQuery                 // public, static                    *
     * @return  CdmQuery*                                     //                                   *
     * @param   QString p_qstrQuery                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Do 26. Jul 16:04:58 2012----------*/
    static CdmQuery* ExecuteQuery(QString p_qstrQuery);
    static CdmQuery* ExecuteQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer);

    /** +-=---------------------------------------------------------Mi 11. Jul 11:31:45 2012-------*
     * @method  CdmQueryBuilder::BuildString                  // public, static                    *
     * @return  QString                                       //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 11:31:45 2012----------*/
    static QString BuildString(CdmQuery* p_pCdmQuery);

    /** +-=---------------------------------------------------------Mo 17. Sep 11:24:03 2012-------*
     * @method  CdmQueryBuilder::GetFinalWql                  // public                            *
     * @return  QString                                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 17. Sep 11:24:03 2012----------*/
    QString GetFinalWql();

    /** +-=---------------------------------------------------------Do 26. Jul 18:07:45 2012-------*
     * @method  CdmQueryBuilder::GenerateQuery                // public                            *
     * @return  CdmQuery*                                     //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Do 26. Jul 18:07:45 2012----------*/
    CdmQuery* GenerateQuery();

    /** +-=---------------------------------------------------------Mo 18. Feb 11:08:02 2013-------*
     * @method  CdmQueryBuilder::AddValueEntry                // public                            *
     * @return  void                                          //                                   *
     * @param   QString p_qstrKey                             //                                   *
     * @param   QString p_qstrValue                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 18. Feb 11:08:02 2013----------*/
    void AddValueEntry(QString p_qstrKey, QString p_qstrValue);

private:
    /** +-=---------------------------------------------------------Do 13. Sep 15:35:26 2012-------*
     * @method  CdmQueryBuilder::ExecutePreProcessor          // private                           *
     * @return  void                                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Do 13. Sep 15:35:26 2012----------*/
    void ExecutePreProcessor();

    void SetContainer(CdmObjectContainer* p_pContainer);

    /** +-=---------------------------------------------------------Mo 18. Feb 10:58:55 2013-------*
     * @method  CdmQueryBuilder::ReadRequestMembersFromQuery  // private, static                   *
     * @return  QString                                       //                                   *
     * @param   CdmQueryEnhanced* p_pCdmQuery                 //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 18. Feb 10:58:55 2013----------*/
    static QString ReadRequestMembersFromQuery(CdmQuery* p_pCdmQuery);

    /** +-=---------------------------------------------------------Mo 18. Feb 10:59:03 2013-------*
     * @method  CdmQueryBuilder::ReadObjectListKeyname        // private, static                   *
     * @return  QString                                       //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 18. Feb 10:59:03 2013----------*/
    static QString ReadObjectListKeyname(CdmQuery* p_pCdmQuery);
};

#endif // CDMQUERYBUILDER_H
