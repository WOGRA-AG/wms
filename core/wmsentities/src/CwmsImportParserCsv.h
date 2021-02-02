/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportParserCsv.h
 ** Started Implementation: 2008/10/14
 ** Description:
 ** 
 ** implements the csv parser
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORTPARSERCSV_H
#define CWMSIMPORTPARSERCSV_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// Own Includes
#include "CwmsImportParser.h"


// Forwards


// Enumerations

/* 
 * This class implements the csv parser
 */
class CwmsImportParserCsv : public CwmsImportParser
{


   public:
   /** +-=---------------------------------------------------------Di 21. Okt 20:04:47 2008-------*
    * @method  CwmsImportParserCsv::CwmsImportParserCsv      // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 20:04:47 2008----------*/
    CwmsImportParserCsv( );

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 20:04:55 2008-------*
    * @method  CwmsImportParserCsv::~CwmsImportParserCsv     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImportParserCsv                                        *
    *----------------last changed: -----------------------------Di 21. Okt 20:04:55 2008----------*/
    virtual ~CwmsImportParserCsv( );

   protected:
   /** +-=---------------------------------------------------------Di 21. Okt 20:05:27 2008-------*
    * @method  CwmsImportParserCsv::ParseLine                // protected, virtual                *
    * @return  QStringList                                   //                                   *
    * @param   QString p_qstrLine                            //                                   *
    * @comment This method parses one line.                                                       *
    *----------------last changed: -----------------------------Di 21. Okt 20:05:27 2008----------*/
    virtual QStringList ParseLine(QString p_qstrLine);
};

#endif //
