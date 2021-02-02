/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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
    /*
     * The dataaccess
     */
    CdbDataAccess* m_rpCdbDataAccess;

    /*
     * The source query element
     */
    CdmQueryElement* m_rpCdmQueryElement;

    /*
     * The childs
     */
    QLinkedList<CdbQueryElement*> m_qvlChilds;

    /*
     * the query as string
     */
    QString m_qstrQuery;



public:
    /** +-=---------------------------------------------------------Sa 20. Aug 12:12:14 2005---*
     * @method  CdbQueryElement::CdbQueryElement          // public                            *
     * @return                                            //                                   *
     * @param   CdbDataAccess* p_pCdbDataAccess           //                                   *
     * @param   CdmQueryElement* p_pCdmQueryElement       //                                   *
     * @comment                                                                                *
     *----------------last changed: -----------------------------Sa 20. Aug 12:12:14 2005------*/
    CdbQueryElement(CdbDataAccess* p_pCdbDataAccess, CdmQueryElement* p_pCdmQueryElement );

    /** +-=---------------------------------------------------------Sa 20. Aug 12:12:17 2005---*
     * @method  CdbQueryElement::~CdbQueryElement         // public                            *
     * @return  void                                      //                                   *
     * @comment The Destructor of Class CdbQueryElement   //                                   *
     *----------------last changed: -----------------------------Sa 20. Aug 12:12:17 2005------*/
    ~CdbQueryElement();

    /** +-=---------------------------------------------------------Fr 8. Aug 22:00:19 2008--------*
     * @method  CdbQueryElement::GenerateQuery              // public                              *
     * @return  QString                                     //                                     *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 8. Aug 22:00:19 2008-----------*/
    QString GenerateQuery();

    /** +-=---------------------------------------------------------Do 1. Jun 17:20:08 2006--------*
     * @method  CdbQueryElement::Execute                      // public                            *
     * @return  long                                          //                                   *
     * @param   QValueList<long>& p_rqvlResultList            //                                   *
     * @comment This method starts the queryexecution for one object and returns if the object     *
     *          has passed the query or it's failed.                                               *
     *----------------last changed: Wolfgang Gra�of-------------Do 1. Jun 17:20:08 2006-----------*/
    long Execute(QMap<long, long>& p_rqvlResultList);

    /** +-=---------------------------------------------------------Sa 20. Aug 12:13:29 2005-------*
     * @method  CdbQueryElement::GetCompareSign             // public                              *
     * @return  QString                                     //                                     *
     * @comment This method generates from the Compare enum of the query a compare sign.           *
     *----------------last changed: -----------------------------Sa 20. Aug 12:13:29 2005----------*/
    QString GetCompareSign();

    /** +-=---------------------------------------------------------Fr 17. Aug 16:28:00 2007-------*
     * @method  CdbQueryElement::GetTableName                 // public                            *
     * @return  QString                                       //                                   *
     * @comment This method returns the tablename dependent to the queryelement.                   *
     *----------------last changed: -----------------------------Fr 17. Aug 16:28:00 2007----------*/
    QString GetTableName();

    /** +-=---------------------------------------------------------Fr 17. Aug 16:31:53 2007-------*
     * @method  CdbQueryElement::GetTableIdName               // public                            *
     * @return  QString                                       //                                   *
     * @comment This method returns the name of the id field in the table.                         *
     *----------------last changed: -----------------------------Fr 17. Aug 16:31:53 2007----------*/
    QString GetTableIdName();

    /** +-=---------------------------------------------------------Mi 22. Aug 10:15:24 2007-------*
     * @method  CdbQueryElement::GetCompareValueAsString      // public                            *
     * @return  QString                                       //                                   *
     * @comment This method returns the comparevalue as string.                                    *
     *----------------last changed: -----------------------------Mi 22. Aug 10:15:24 2007----------*/
    QString GetCompareValueAsString();

    /** +-=---------------------------------------------------------Mi 22. Aug 10:42:05 2007-------*
     * @method  CdbQueryElement::GetListCompareValueAsString  // public                            *
     * @return  QString                                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 22. Aug 10:42:05 2007----------*/
    QString GetListCompareValueAsString();

    /** +-=---------------------------------------------------------Mi 22. Aug 12:49:04 2007-------*
     * @method  CdbQueryElement::GetDataFieldName             // public                            *
     * @return  QString                                       //                                   *
     * @comment This method returns the name of the datafield.                                     *
     *----------------last changed: -----------------------------Mi 22. Aug 12:49:04 2007----------*/
    QString GetDataFieldName();



private:
    /** +-=---------------------------------------------------------Sa 20. Aug 12:12:23 2005*
     * @method  CdbQueryElement::CreateChilds                 // private                           *
     * @return  void                                          //                                   *
     * @param   QValueList<CdmQueryElement*>& p_qvlChilds     //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Sa 20. Aug 12:12:23 2005----------*/
    void CreateChilds(QLinkedList<CdmQueryElement*> &p_qvlChilds);

    /** +-=---------------------------------------------------------Do 1. Jun 17:50:24 2006--------*
     * @method  CdbQueryElement::ExecuteValue                 // private                           *
     * @return  long                                          //                                   *
     * @param   QValueList<long>& p_rqvlResults               //                                   *
     * @comment                                                                                    *
     *----------------last changed: Wolfgang Gra�of-------------Do 1. Jun 17:50:24 2006-----------*/
    long ExecuteValue(QMap<long,long> &p_rqvlResults);

    /** +-=---------------------------------------------------------Mi 22. Aug 15:20:47 2007-------*
     * @method  CdbQueryElement::GenerateValueQuery           // private                           *
     * @return  QString                                       //                                   *
     * @comment This method creates the correct query for the valuecompare.                        *
     *----------------last changed: -----------------------------Mi 22. Aug 15:20:47 2007----------*/
    QString GenerateValueQuery();

    /** +-=---------------------------------------------------------Fr 8. Aug 21:55:01 2008--------*
     * @method  CdbQueryElement::GenerateOrQuery              // private                           *
     * @return  QString                                       //                                   *
     * @comment This method creates the Or Query.                                                  *
     *----------------last changed: -----------------------------Fr 8. Aug 21:55:01 2008-----------*/
    QString GenerateOrQuery();

    /** +-=---------------------------------------------------------Fr 6. Mai 11:46:00 2011--------*
     * @method  CdbQueryElement::GenerateAndQuery             // private                           *
     * @return  QString                                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 6. Mai 11:46:00 2011-----------*/
    QString GenerateAndQuery();

    /** +-=---------------------------------------------------------Di 17. Apr 16:13:09 2012-------*
     * @method  CdbQueryElement::ExtractCompareEntriesFromList // private                          *
     * @return  QString                                        //                                  *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 17. Apr 16:13:09 2012----------*/
    QString ExtractCompareEntriesFromList();
};

#endif //
