/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CftlDataStructureHelper.h
 ** Started Implementation: 2010/11/12
 ** Description:
 ** 
 ** This class contains helper functions for working with the wms db structure.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CODBCDATASTRUCTUREHELPER_H
#define CODBCDATASTRUCTUREHELPER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// Own Includes

// WMS Manager Incldues
#include "CdmMember.h"

// Forwards


// Enumerations

/* 
 * This class contains helper functions for working with the wms db structure.
 */
class CftlDataStructureHelper
{


   public:
   /** +-=---------------------------------------------------------Mo 25. Mrz 15:33:21 2013-------*
    * @method  CftlDataStructureHelper::GetDataFieldName    // public, static                    *
    * @return  QString                                       //                                   *
    * @comment This method returns the name of the data field.                                    *
    *----------------last changed: -----------------------------Mo 25. Mrz 15:33:21 2013----------*/
    static QString GetDataFieldName();

   public:
   /** +-=---------------------------------------------------------Fr 12. Nov 10:29:39 2010-------*
    * @method  CftlDataStructureHelper::GetTableName        // public, static                    *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValueType                       //                                   *
    * @comment This method returns the table name dependent to the query element.                 *
    *----------------last changed: -----------------------------Fr 12. Nov 10:29:39 2010----------*/
    static QString GetTableName(EdmValueType p_eDmValueType);

   public:
   /** +-=---------------------------------------------------------Mo 25. Mrz 15:34:31 2013-------*
    * @method  CftlDataStructureHelper::GetTableIdName      // public, static                    *
    * @return  QString                                       //                                   *
    * @comment This method returns the name of the id field in the table.                         *
    *----------------last changed: -----------------------------Mo 25. Mrz 15:34:31 2013----------*/
    static QString GetTableIdName();


   public:
   /** +-=---------------------------------------------------------Sa 7. Mai 11:22:07 2011--------*
    * @method  CftlDataStructureHelper::GetFirstMember      // public, static                    *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrMemberChain                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 7. Mai 11:22:07 2011-----------*/
    static QString GetFirstMember(QString p_qstrMemberChain);

   public:
   /** +-=---------------------------------------------------------Sa 7. Mai 11:48:45 2011--------*
    * @method  CftlDataStructureHelper::GetLastMember       // public, static                    *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrMemberChain                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 7. Mai 11:48:45 2011-----------*/
    static QString GetLastMember(QString p_qstrMemberChain);
};

#endif //
