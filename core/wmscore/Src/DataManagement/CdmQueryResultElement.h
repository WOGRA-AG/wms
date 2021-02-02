/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmQueryResultElement.h
 ** Started Implementation: 2010/11/10
 ** Description:
 ** 
 ** This class implements the result elements of queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMQUERYRESULTELEMENT_H
#define CDMQUERYRESULTELEMENT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVector>
#include <QVariant>
#include <QObject>

// WMS Manager Includes
#include "datamanager.h"
#include "CdmMember.h"

// Own Includes


// Forwards
class CdmQuery;

// Enumerations
enum EdmQueryResultElementMode
{
   eDmQueryResultElementModeNone,
   eDmQueryResultElementModeSum,
   eDmQueryResultElementModeAvg,
   eDmQueryResultElementModeMin,
   eDmQueryResultElementModeMax,
   eDmQueryResultElementModeCount
};

/* 
 * This class implements the result elements of queries
 */
class WMSMANAGER_API CdmQueryResultElement : public QObject
{

   Q_OBJECT
   friend class CdmQuery;

   private:
      QString m_qstrKeyname;
      EdmQueryResultElementMode m_eDmMode;
      QVector<QVariant> m_qvResults;
      CdmQuery* m_rpCdmQuery;

   public:
   /** +-=---------------------------------------------------------Do 11. Nov 10:12:43 2010-------*
    * @method  CdmQueryResultElement::CdmQueryResultElement  // public                            *
    * @return                                                //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EdmQueryResultElementMode p_eDmMode           //                                   *
    * @param   CdmQuery* p_pCdmQuery         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 10:12:43 2010----------*/
    CdmQueryResultElement( QString p_qstrKeyname,
                           EdmQueryResultElementMode p_eDmMode,
                           CdmQuery* p_pCdmQuery);

   public:
   /** +-=---------------------------------------------------------Mi 10. Nov 17:00:06 2010-------*
    * @method  CdmQueryResultElement::~CdmQueryResultElement // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmQueryResultElement                                      *
    *----------------last changed: -----------------------------Mi 10. Nov 17:00:06 2010----------*/
    virtual ~CdmQueryResultElement( );

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:15:30 2013-------*
    * @method  CdmQueryResultElement::GetKeyname             // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:15:30 2013----------*/
QString GetKeyname( ) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:15:39 2013-------*
    * @method  CdmQueryResultElement::GetMode                // public, const, slots              *
    * @return  EdmQueryResultElementMode                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:15:39 2013----------*/
EdmQueryResultElementMode GetMode( ) const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:38:37 2012-------*
    * @method  CdmQueryResultElement::GetResults             // public, slots                     *
    * @return  QVector<QVariant>&                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 11:38:37 2012----------*/
QVector<QVariant>& GetResults( );

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:39:20 2012-------*
    * @method  CdmQueryResultElement::GetResultCount         // public, const, slots              *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 11:39:20 2012----------*/
int GetResultCount( ) const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:39:28 2012-------*
    * @method  CdmQueryResultElement::GetResultAt            // public, const, slots              *
    * @return  QVariant                                      //                                   *
    * @param   int p_iPos                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 11:39:28 2012----------*/
QVariant GetResultAt(int p_iPos) const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:39:38 2012-------*
    * @method  CdmQueryResultElement::GetValueType           // public, slots                     *
    * @return  EdmValue                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 11:39:38 2012----------*/
EdmValueType GetValueType( );

   private:
   /** +-=---------------------------------------------------------Fr 12. Nov 08:49:17 2010-------*
    * @method  CdmQueryResultElement::AddResult              // private                           *
    * @return  void                                          //                                   *
    * @param   QVariant p_qvValue                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 12. Nov 08:49:17 2010----------*/
    void AddResult(QVariant p_qvValue);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:39:57 2012-------*
    * @method  CdmQueryResultElement::ClearResults           // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 11:39:57 2012----------*/
void ClearResults( );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:15:22 2013-------*
    * @method  CdmQueryResultElement::GetVariant             // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:15:22 2013----------*/
    QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Di 17. Apr 13:15:28 2012-------*
    * @method  CdmQueryResultElement::CdmQueryResultElement  // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmQuery* p_pQuery                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 17. Apr 13:15:28 2012----------*/
    CdmQueryResultElement( QVariantMap& p_rqvHash, CdmQuery* p_pQuery);

public:
    static QStringList GetResultAsStringList(CdmQuery* p_pQuery, int p_iCol, bool p_bTrimmed);
};

#endif //
