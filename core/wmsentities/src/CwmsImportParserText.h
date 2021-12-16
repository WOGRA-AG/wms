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
    CwmsImportParserText( );
    virtual ~CwmsImportParserText( );

   protected:
    virtual QStringList ParseLine(QString p_qstrLine);
};

#endif //
