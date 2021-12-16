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
    CwmsImportParserCsv( );
    virtual ~CwmsImportParserCsv( );

   protected:
    virtual QStringList ParseLine(QString p_qstrLine);
};

#endif //
