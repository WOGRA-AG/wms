// antlr4::Lexer::emit() : Avoid conflict with emit keyword
#ifndef ANTLR_EMIT_WORKAROUND_WMS
#define ANTLR_EMIT_WORKAROUND_WMS
#undef emit
#endif

// System and QT Includes

// WMS Commons Includes
#include "antlr4-runtime.h"

// own Includes
#include "CdmLogging.h"
#include "CdmAntlrErrorListener.h"


using namespace antlr4;

CdmAntlrErrorListener::CdmAntlrErrorListener()
{
}

CdmAntlrErrorListener::~CdmAntlrErrorListener()
{
}

void CdmAntlrErrorListener::syntaxError(Recognizer *recognizer, Token *offendingSymbol,
                                        size_t line, size_t charPositionInLine,
                                        const std::string &msg, std::exception_ptr e)
{
    QString qstrMsg = "line " + QString::number(line) + ":" + QString::number(charPositionInLine)
            + "\n" + QString::fromStdString(msg);
    if (antlrcpp::is<Lexer*>(recognizer))
    {
        qstrMsg = "Couldn't parse lexer tokens in " + qstrMsg;
    }
    else if (antlrcpp::is<Parser*>(recognizer))
    {
        qstrMsg = "Couldn't parse " + qstrMsg;
    }
    if (offendingSymbol)
    {
        qstrMsg += "\nOffending Symbol: " + QString::fromStdString(offendingSymbol->toString());
    }
    if (e)
    {
        ERR(qstrMsg);
    }
    else
    {
        INFO(qstrMsg);
    }
}
