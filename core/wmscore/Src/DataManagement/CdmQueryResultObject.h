/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmQueryResultObject.h
 ** Started Implementation: 2012/10/14
 ** Description:
 ** 
 ** implements the result object of an query
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMQUERYRESULTOBJECT_H
#define CDMQUERYRESULTOBJECT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QList>
#include <QObject>
#include <QVariant>

// Own Includes
#include "datamanager.h"

// Forwards
class CdmQuery;
class CdmObject;

// TypeDefs


/* 
 * This class implements the result object of an query
 */
class WMSMANAGER_API CdmQueryResultObject : public QObject
{
    Q_OBJECT

private:
    CdmQuery* m_rpCdmQuery;
    QMap<int, QVariant> m_qmResultValues;
    QMap<qint64, CdmQueryResultObject*> m_qmChildrenByObject;
    QMap<int, CdmQueryResultObject*> m_qmChildrenByRow;
   qint64 m_lObjectId;
   qint64 m_lContainerId;
    CdmQueryResultObject* m_pParent;
    int m_iRow;

public:
    /** +-=---------------------------------------------------------Mo 15. Okt 08:44:50 2012-------*
     * @method  CdmQueryResultObject::CdmQueryResultObject    // public                            *
     * @return                                                //                                   *
     * @param  qint64 p_lObjectId                              //                                   *
     * @param   CdmQueryResultObject* p_pParent               //                                   *
     * @param   CdmQueryEnhanced* p_pQuery                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 15. Okt 08:44:50 2012----------*/
    CdmQueryResultObject(qint64 p_lObjectId,
                         qint64 p_lContainerId,
                          CdmQueryResultObject* p_pParent,
                          CdmQuery* p_pQuery);

    /** +-=---------------------------------------------------------So 14. Okt 14:38:50 2012-------*
     * @method  CdmQueryResultObject::~CdmQueryResultObject   // public, virtual                   *
     * @return  void                                          //                                   *
     * @comment The Destructor of Class CdmQueryResultObject                                       *
     *----------------last changed: -----------------------------So 14. Okt 14:38:50 2012----------*/
    virtual ~CdmQueryResultObject( );

    /** +-=---------------------------------------------------------Mo 15. Okt 08:47:25 2012-------*
     * @method  CdmQueryResultObject::CreateResultObject      // public, static                    *
     * @return  CdmQueryResultObject*                         //                                   *
     * @param   CdmQueryEnhanced* p_pQuery                    //                                   *
     * @param   CdmQueryResultObject* p_pRoot                 //                                   *
     * @param  qint64 p_lObjectId                              //                                   *
     * @param  qint64 p_lParentId                              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 15. Okt 08:47:25 2012----------*/
    static CdmQueryResultObject* CreateResultObject(CdmQuery* p_pQuery,
                                                    CdmQueryResultObject* p_pRoot,
                                                   qint64 p_lObjectId,
                                                   qint64 p_lContainerId,
                                                   qint64 p_lParentId);

    /** +-=---------------------------------------------------------Mo 15. Okt 10:17:00 2012-------*
     * @method  CdmQueryResultObject::FindOrCreateResultObject // public, static                   *
     * @return  CdmQueryResultObject*                         //                                   *
     * @param  qint64 p_lObjectId                              //                                   *
     * @param   CdmQueryResultObject* p_pRoot                 //                                   *
     * @param   CdmQueryEnhanced* p_pQuery                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 15. Okt 10:17:00 2012----------*/
    static CdmQueryResultObject* FindOrCreateResultObject(qint64 p_lObjectId,
                                                         qint64 p_lContainerId,
                                                          CdmQueryResultObject* p_pRoot,
                                                          CdmQuery* p_pQuery);

    /** +-=---------------------------------------------------------Di 12. Feb 11:02:03 2013-------*
     * @method  CdmQueryResultObject::GetVariant              // public                            *
     * @return  QVariant                                      //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 12. Feb 11:02:03 2013----------*/
    QVariant GetVariant();

    /** +-=---------------------------------------------------------Di 12. Feb 11:06:32 2013-------*
     * @method  CdmQueryResultObject::SetVariant              // public                            *
     * @return  void                                          //                                   *
     * @param   QVariantMap& p_rqvHash                       //                                    *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 12. Feb 11:06:32 2013----------*/
    void SetVariant(QVariantMap& p_rqvHash);

    QString GetResultAsString();
   qint64 GetContainerId() const;
   qint64 SetContainerId(qint64 p_lContainerId);
    QVariant GetResultAsVariant();



public slots:
    /** +-=---------------------------------------------------------Di 20. Nov 11:41:01 2012-------*
     * @method  CdmQueryResultObject::AddChildren             // public, slots                     *
     * @return  void                                          //                                   *
     * @param   CdmQueryResultObject* p_pChild                //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:41:01 2012----------*/
    void AddChildren( CdmQueryResultObject* p_pChild);

    /** +-=---------------------------------------------------------Di 20. Nov 11:41:10 2012-------*
     * @method  CdmQueryResultObject::GetParent               // public, slots                     *
     * @return  CdmQueryResultObject*                         //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:41:10 2012----------*/
    CdmQueryResultObject* GetParent( );

    /** +-=---------------------------------------------------------Di 20. Nov 11:41:42 2012-------*
     * @method  CdmQueryResultObject::GetResultAt             // public, slots                     *
     * @return  QVariant                                      //                                   *
     * @param   int p_iPos                                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:41:42 2012----------*/
    QVariant GetResultAt( int p_iPos);

    /** +-=---------------------------------------------------------Di 20. Nov 11:42:02 2012-------*
     * @method  CdmQueryResultObject::GetChild                // public, slots                     *
     * @return  CdmQueryResultObject*                         //                                   *
     * @param  qint64 p_lObjectId                              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:42:02 2012----------*/
    CdmQueryResultObject* GetChild(qint64 p_lObjectId);

    /** +-=---------------------------------------------------------So 10. Feb 10:17:36 2013-------*
     * @method  CdmQueryResultObject::GetObjectId             // public, const, slots              *
     * @return qint64                                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:17:36 2013----------*/
   qint64 GetObjectId( ) const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:42:13 2012-------*
     * @method  CdmQueryResultObject::GetChildAtRow           // public, slots                     *
     * @return  CdmQueryResultObject*                         //                                   *
     * @param   int p_iRow                                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:42:13 2012----------*/
    CdmQueryResultObject* GetChildAtRow( int p_iRow);

    /** +-=---------------------------------------------------------So 10. Feb 10:17:07 2013-------*
     * @method  CdmQueryResultObject::GetRowCount             // public, const, slots              *
     * @return  int                                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:17:07 2013----------*/
    int GetRowCount( ) const;

    /** +-=---------------------------------------------------------So 10. Feb 10:17:28 2013-------*
     * @method  CdmQueryResultObject::GetColumnCount          // public, const, slots              *
     * @return  int                                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:17:28 2013----------*/
    int GetColumnCount( ) const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:41:52 2012-------*
     * @method  CdmQueryResultObject::AddResult               // public, slots                     *
     * @return  void                                          //                                   *
     * @param   int p_iColumn                                 //                                   *
     * @param   QVariant qvResult                             //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:41:52 2012----------*/
    void AddResult( int p_iColumn, QVariant qvResult);

    /** +-=---------------------------------------------------------Di 20. Nov 11:40:53 2012-------*
     * @method  CdmQueryResultObject::ClearResults            // public, slots                     *
     * @return  void                                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:40:53 2012----------*/
    void ClearResults( );

    /** +-=---------------------------------------------------------Di 20. Nov 11:42:51 2012-------*
     * @method  CdmQueryResultObject::GetResult               // public, slots                     *
     * @return  QVariant                                      //                                   *
     * @param   int p_iRow                                    //                                   *
     * @param   int p_iColumn                                 //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:42:51 2012----------*/
    QVariant GetResult( int p_iRow, int p_iColumn);

    /** +-=---------------------------------------------------------Di 20. Nov 11:43:01 2012-------*
     * @method  CdmQueryResultObject::GetResult               // public, slots                     *
     * @return  QVariant                                      //                                   *
     * @param   int p_iRow                                    //                                   *
     * @param   int p_iColumn                                 //                                   *
     * @param  qint64 p_lParentId                              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:43:01 2012----------*/
    QVariant GetResult( int p_iRow, int p_iColumn,qint64 p_lParentId);

    /** +-=---------------------------------------------------------So 10. Feb 10:16:30 2013-------*
     * @method  CdmQueryResultObject::GetRow                  // public, const, slots              *
     * @return  int                                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:16:30 2013----------*/
    int GetRow( ) const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:44:24 2012-------*
     * @method  CdmQueryResultObject::GetChildList            // public, slots                     *
     * @return  QList<CdmObject*>                             //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:44:24 2012----------*/
    QList<CdmObject*> GetChildList( );

    /** +-=---------------------------------------------------------Di 20. Nov 11:42:40 2012-------*
     * @method  CdmQueryResultObject::GetChildAtRow           // public, slots                     *
     * @return  CdmQueryResultObject*                         //                                   *
     * @param   int p_iRow                                    //                                   *
     * @param   int p_lParentId                               //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:42:40 2012----------*/
    CdmQueryResultObject* GetChildAtRow( int p_iRow, int p_lParentId);

    /** +-=---------------------------------------------------------Di 20. Nov 11:44:43 2012-------*
     * @method  CdmQueryResultObject::GetObject               // public, slots                     *
     * @return  CdmObject*                                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:44:43 2012----------*/
    CdmObject* GetObject( );

    /** +-=---------------------------------------------------------Di 20. Nov 11:41:17 2012-------*
     * @method  CdmQueryResultObject::GetObjectParentId       // public, slots                     *
     * @return qint64                                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:41:17 2012----------*/
   qint64 GetObjectParentId( );



private:
    /** +-=---------------------------------------------------------Mo 15. Okt 10:17:38 2012-------*
     * @method  CdmQueryResultObject::GetObjectParentId       // private, static                   *
     * @return qint64                                          //                                   *
     * @param  qint64 p_lObjectId                              //                                   *
     * @param   CdmQueryEnhanced* p_pQuery                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 15. Okt 10:17:38 2012----------*/
    static qint64 GetObjectParentId(qint64 p_lObjectId,qint64 p_lContainerId, CdmQuery* p_pQuery);

    void ClearChildData();
};

#endif // CDMQUERYRESULTOBJECT_H
