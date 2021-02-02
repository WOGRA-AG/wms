/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportParserText.h
 ** Started Implementation: 2008/10/14
 ** Description:
 ** 
 ** This class implements the text parser
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORTPARSERTEXT_H
#define CWMSIMPORTPARSERTEXT_H

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
 * This class implements the text parser
 */
class CwmsImportParserText : public CwmsImportParser
{


   public:
   /** +-=---------------------------------------------------------Di 21. Okt 20:06:41 2008-------*
    * @method  CwmsImportParserText::CwmsImportParserText    // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 20:06:41 2008----------*/
    CwmsImportParserText( );

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 20:06:56 2008-------*
    * @method  CwmsImportParserText::~CwmsImportParserText   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImportParserCsv                                        *
    *----------------last changed: -----------------------------Di 21. Okt 20:06:56 2008----------*/
    virtual ~CwmsImportParserText( );

   protected:
   /** +-=---------------------------------------------------------Di 21. Okt 20:07:04 2008-------*
    * @method  CwmsImportParserText::ParseLine               // protected, virtual                *
    * @return  QStringList                                   //                                   *
    * @param   QString p_qstrLine                            //                                   *
    * @comment This method parses one line.                                                       *
    *----------------last changed: -----------------------------Di 21. Okt 20:07:04 2008----------*/
    virtual QStringList ParseLine(QString p_qstrLine);
};

#endif //
