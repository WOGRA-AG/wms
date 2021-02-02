#ifndef CdmAntlrErrorListener_H
#define CdmAntlrErrorListener_H


// System and QT Includes
#include <QObject>

// Own Includes
#include "datamanager.h"
#include "antlr4-common.h"
#include "BaseErrorListener.h"

// Forwards

// TypeDefs


/* 
 * This class implements the Query builder. It creates a CdmQuery Object by parsing a string
 */
class WMSMANAGER_API CdmAntlrErrorListener : public QObject, public antlr4::BaseErrorListener
{
    Q_OBJECT

public:
    CdmAntlrErrorListener();
    virtual ~CdmAntlrErrorListener();

    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                             size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e);
};

#endif // CdmAntlrErrorListener_H
