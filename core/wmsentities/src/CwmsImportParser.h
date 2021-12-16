#ifndef CWMSIMPORTPARSER_H
#define CWMSIMPORTPARSER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QFile>

// Own Includes
#include "basetools.h"


// Forwards
class CwmsImport;
class CwmsImportSettings;
// Enumerations

/* 
 * This class implements the parserbaseclass
 */
class BASETOOLS_API CwmsImportParser
{
protected:
    CwmsImportSettings* m_pCwmsImportSettings;
    QIODevice* m_pqDevice;

public:
    CwmsImportParser();
    virtual ~CwmsImportParser();
    void SetImportSettings(CwmsImportSettings* p_pImportSettings);
    static CwmsImportParser* ParserFactory(CwmsImportSettings* p_pImportSettings);
    bool OpenDevice();
    void ParseFile(CwmsImport* p_pCwmsImport);
    void SetDevice(QIODevice* p_pDevice);

protected:
    virtual QStringList ParseLine(QString p_qstrLine)= 0;


private:
    void CloseDevice();
};

#endif //
