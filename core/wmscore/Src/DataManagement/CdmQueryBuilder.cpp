/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmQueryBuilder.cpp
 ** Started Implementation: 2012/07/10
 ** Description:
 **
 ** Implements the Query builder. It creates a CdmQuery Object by parsing a string
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/
#ifndef NOMINMAX
#define NOMINMAX
#endif

// System and QT Includes

// WMS Commons Includes
#include "CwmsTimeMeassurement.h"
#include "CwmsUtilities.h"

// own Includes
#include "CdmMessageManager.h"
#include "CdmSystemVariables.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmQueryFactory.h"
#include "CdmQueryBuilder.h"



/** +-=---------------------------------------------------------Di 10. Jul 14:31:50 2012----------*
 * @method  CdmQueryBuilder::CdmQueryBuilder                 // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrQuery                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 10. Jul 14:31:50 2012----------*/
CdmQueryBuilder::CdmQueryBuilder(QString p_qstrQuery)
    : m_qstrQuery(p_qstrQuery),
      m_qmValueMap(),
      m_rpContainer(nullptr),
      bProcessed(false)
{
}

CdmQueryBuilder::CdmQueryBuilder(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
    : m_qstrQuery(p_qstrQuery),
      m_qmValueMap(),
      m_rpContainer(p_pContainer),
      bProcessed(false)
{
}

/** +-=---------------------------------------------------------Di 10. Jul 14:23:33 2012----------*
 * @method  CdmQueryBuilder::~CdmQueryBuilder                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmQueryBuilder                                               *
 *----------------last changed: --------------------------------Di 10. Jul 14:23:33 2012----------*/
CdmQueryBuilder::~CdmQueryBuilder()
{
}

CdmQuery* CdmQueryBuilder::GenerateQuery()
{
    QString qstrQuery = GetFinalWql();
    return CdmQueryFactory::ParseString(qstrQuery, m_rpContainer);
}

QString CdmQueryBuilder::GetFinalWql()
{
    if (!bProcessed)
    {
        ExecutePreProcessor();
    }
    return m_qstrQuery;
}

void CdmQueryBuilder::ExecutePreProcessor()
{
    int iPosEnd = 0;
    int iPosStart = m_qstrQuery.indexOf("${", 0);

    while (iPosStart > 0)
    {
        iPosEnd = m_qstrQuery.indexOf("}", iPosStart);

        if (iPosEnd > 0)
        {
            QString qstrKey = m_qstrQuery.mid(iPosStart, iPosEnd - iPosStart + 1);
            QString qstrValue;

            if (m_qmValueMap.contains(qstrKey))
            {
                qstrValue = m_qmValueMap[qstrKey];
            }
            else if (CdmSystemVariables::IsSystemValue(qstrKey))
            {
                qstrValue = CdmSystemVariables::GetValueAsString(qstrKey);
            }
            else
            {
                qstrValue = CdmMessageManager::GetMessenger()->AskForInputText("Bitte geben Sie den Wert für \"" + qstrKey + "\" ein.");
            }

            m_qstrQuery.replace(qstrKey, qstrValue);
        }
        else
        {
            ERR(tr("Präprozessor Fehler Variable kann nicht gesetzt werden\nEin Variablenbeginn (\"${\") wurde definiert aber nicht abgeschlossen."));
            break;
        }

        iPosStart = m_qstrQuery.indexOf("${", iPosStart);
    }
}

void CdmQueryBuilder::AddValueEntry(QString p_qstrKey, QString p_qstrValue)
{
    if (!p_qstrKey.startsWith("${"))
    {
        p_qstrKey = "${" + p_qstrKey + "}";
    }

    m_qmValueMap.insert(p_qstrKey, p_qstrValue);
}

void CdmQueryBuilder::SetContainer(CdmObjectContainer* p_pContainer)
{
    m_rpContainer = p_pContainer;
}

QString CdmQueryBuilder::ReadRequestMembersFromQuery(CdmQuery* p_pCdmQuery)
{
    QString qstrRet;

    if (CHKPTR(p_pCdmQuery))
    {
        QVector<QString> qvElements = p_pCdmQuery->GetResultElements();

        if (qvElements.count() > 0)
        {
            for (int iCounter = 0; iCounter < qvElements.count(); iCounter++)
            {
                qstrRet += qvElements[iCounter];

                if (iCounter < qvElements.count() - 1)
                {
                    qstrRet += ", ";
                }
            }
        }
    }

    return qstrRet;
}

/** +-=---------------------------------------------------------Mo 18. Feb 10:59:03 2013----------*
 * @method  CdmQueryBuilder::ReadObjectListKeyname           // private, static                   *
 * @return  QString                                          //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Feb 10:59:03 2013----------*/
QString CdmQueryBuilder::ReadObjectListKeyname(CdmQuery* p_pCdmQuery)
{
    QString qstrRet;

    if (p_pCdmQuery)
    {
        CdmObjectContainer* pContainer = p_pCdmQuery->GetContainer();

        if (pContainer)
        {
            qstrRet = pContainer->GetKeyname();
        }
        else
        {
            const CdmClass* pClass = p_pCdmQuery->GetClass();

            if (pClass)
            {
                qstrRet = pClass->GetFullQualifiedName() + ".class";
            }
        }
    }

    return qstrRet;
}

CdmQuery* CdmQueryBuilder::BuildQuery(QString p_qstrQuery)
{
    CdmQueryBuilder cCdmBuilder(p_qstrQuery);
    CdmQuery* pCdmQuery = cCdmBuilder.GenerateQuery();
    return pCdmQuery;
}

CdmQuery* CdmQueryBuilder::BuildQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
{
    CdmQueryBuilder cCdmBuilder(p_qstrQuery, p_pContainer);
    CdmQuery* pCdmQuery = cCdmBuilder.GenerateQuery();
    return pCdmQuery;
}

CdmQuery* CdmQueryBuilder::ExecuteQuery(QString p_qstrQuery)
{
    CdmQuery* pCdmQuery = BuildQuery(p_qstrQuery);

    if (pCdmQuery)
    {
        if (pCdmQuery->Execute() < 0)
        {
            ERR("Query not successfull executed")
            DELPTR(pCdmQuery)
        }
    }
    else
    {
        ERR("Could not parse query.\n" + p_qstrQuery)
    }

    return pCdmQuery;
}

CdmQuery* CdmQueryBuilder::ExecuteQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
{
    CdmQuery* pCdmQuery = BuildQuery(p_qstrQuery, p_pContainer);

    if (pCdmQuery)
    {
        if (pCdmQuery->Execute() < 0)
        {
            ERR("Query not successfull executed");
            DELPTR(pCdmQuery);
        }
    }
    else
    {
        ERR("Could not parse query.\n" + p_qstrQuery);
    }

    return pCdmQuery;
}


/** +-=---------------------------------------------------------Mi 11. Jul 11:31:45 2012----------*
 * @method  CdmQueryBuilder::BuildString                     // public, static                    *
 * @return  QString                                          //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 11. Jul 11:31:45 2012----------*/
QString CdmQueryBuilder::BuildString(CdmQuery* p_pCdmQuery)
{
    QString qstrRet;

    if (CHKPTR(p_pCdmQuery))
    {
        qstrRet += "select ";

        if (p_pCdmQuery->IsEnhancedQuery())
        {
            qstrRet += ReadRequestMembersFromQuery(p_pCdmQuery);
        }

        qstrRet += " from " + ReadObjectListKeyname(p_pCdmQuery) + " ";

        CdmQueryElement* pCdmElement = p_pCdmQuery->GetQueryElement();

        if (pCdmElement)
        {
            QString qstrCond(pCdmElement->GetConditionAsString());

            if (false == qstrCond.contains(QStringLiteral("where")))
            {
                qstrRet += "where ";
            }

            qstrRet += pCdmElement->GetConditionAsString() + " ";
        }

        if (!p_pCdmQuery->GetOrderBy().isEmpty())
        {
            qstrRet += " order by " + p_pCdmQuery->GetOrderBy().join(", ");

            if (p_pCdmQuery->GetOrderMode())
            {
                qstrRet += " ASC";
            }
            else
            {
                qstrRet += " DESC";
            }
        }
    }

    qstrRet = qstrRet.trimmed();
    return qstrRet;
}




/*void CdmQueryBuilder::displayRceognitionError(antlr4::tree::ParseTree* recognizer,
                                              unsigned char**  tokenNames)
{
    // pANTLR3_PARSER			parser;
    // pANTLR3_TREE_PARSER	    tparser;
    //pANTLR3_INT_STREAM	    is;
    pANTLR3_STRING			ttext;
    pANTLR3_STRING			ftext;
    pANTLR3_EXCEPTION	    ex;
    pANTLR3_COMMON_TOKEN    theToken;
    pANTLR3_BASE_TREE	    theBaseTree;
    pANTLR3_COMMON_TREE	    theCommonTree;
    QString qstrError;
    QString qstrTemp;

    // Retrieve some info for easy reading.
    //
    ex	    =		recognizer->state->exception;
    ttext   =		nullptr;

    // See if there is a 'filename' we can use
    //
    if	(ex->streamName == nullptr)
    {
        if	(((pANTLR3_COMMON_TOKEN)(ex->token))->type == ANTLR3_TOKEN_EOF)
        {
            qstrError += QString("-end of input-(");
        }
        else
        {
            qstrError += QString("-unknown source-(");
        }
    }
    else
    {
        ftext = ex->streamName->to8(ex->streamName);
        qstrError += qstrTemp.sprintf("%s(", ftext->chars);
    }

    // Next comes the line number
    //

    qstrError += QString("%1) ").arg(recognizer->state->exception->line);
    qstrError += qstrTemp.sprintf(" : error %d : %s",
                                  recognizer->state->exception->type,
                                  (pANTLR3_UINT8)	   (recognizer->state->exception->message));


    // How we determine the next piece is dependent on which thing raised the
    // error.
    //
    switch	(recognizer->type)
    {
    case	ANTLR3_TYPE_PARSER:

        // Prepare the knowledge we know we have
        //
        // parser	    = (pANTLR3_PARSER) (recognizer->super);
        //tparser	    = nullptr;
        //is			= parser->tstream->istream;
        theToken    = (pANTLR3_COMMON_TOKEN)(recognizer->state->exception->token);
        ttext	    = theToken->toString(theToken);

        qstrError += qstrTemp.sprintf(", at offset %d", recognizer->state->exception->charPositionInLine);
        if  (theToken != nullptr)
        {
            if (theToken->type == ANTLR3_TOKEN_EOF)
            {
                qstrError += qstrTemp.sprintf(", at <EOF>");
            }
            else
            {
                // Guard against nullptr text in a token
                //
                qstrError += qstrTemp.sprintf("\n    near %s\n    ", ttext == nullptr ? (pANTLR3_UINT8)"<no text for the token>" : ttext->chars);
            }
        }
        break;

    case	ANTLR3_TYPE_TREE_PARSER:

        // tparser		= (pANTLR3_TREE_PARSER) (recognizer->super);
        // parser		= nullptr;
        //is			= tparser->ctnstream->tnstream->istream;
        theBaseTree	= (pANTLR3_BASE_TREE)(recognizer->state->exception->token);
        ttext		= theBaseTree->toStringTree(theBaseTree);

        if  (theBaseTree != nullptr)
        {
            theCommonTree	= (pANTLR3_COMMON_TREE)	    theBaseTree->super;

            if	(theCommonTree != nullptr)
            {
                theToken	= (pANTLR3_COMMON_TOKEN)    theBaseTree->getToken(theBaseTree);
            }
            qstrError += qstrTemp.sprintf(", at offset %d", theBaseTree->getCharPositionInLine(theBaseTree));
            qstrError += qstrTemp.sprintf(", near %s", ttext->chars);
        }
        break;

    default:

        qstrError += "Base recognizer function displayRecognitionError called by unknown parser type - provide override for this function\n";
        return;
        break;
    }

    // Although this function should generally be provided by the implementation, this one
    // should be as helpful as possible for grammar developers and serve as an example
    // of what you can do with each exception type. In general, when you make up your
    // 'real' handler, you should debug the routine with all possible errors you expect
    // which will then let you be as specific as possible about all circumstances.
    //
    // Note that in the general case, errors thrown by tree parsers indicate a problem
    // with the output of the parser or with the tree grammar itself. The job of the parser
    // is to produce a perfect (in traversal terms) syntactically correct tree, so errors
    // at that stage should really be semantic errors that your own code determines and handles
    // in whatever way is appropriate.
    //
    switch  (ex->type)
    {
    case	ANTLR3_UNWANTED_TOKEN_EXCEPTION:

        // Indicates that the recognizer was fed a token which seesm to be
        // spurious input. We can detect this when the token that follows
        // this unwanted token would normally be part of the syntactically
        // correct stream. Then we can see that the token we are looking at
        // is just something that should not be there and throw this exception.
        //
        if	(tokenNames == nullptr)
        {
            qstrError += " : Extraneous input...";
        }
        else
        {
            if	(ex->expecting == ANTLR3_TOKEN_EOF)
            {
                qstrError += " : Extraneous input - expected <EOF>\n";
            }
            else
            {
                qstrError += qstrTemp.sprintf(" : Extraneous input - expected %s ...\n", tokenNames[ex->expecting]);
            }
        }
        break;

    case	ANTLR3_MISSING_TOKEN_EXCEPTION:

        // Indicates that the recognizer detected that the token we just
        // hit would be valid syntactically if preceeded by a particular
        // token. Perhaps a missing ';' at line end or a missing ',' in an
        // expression list, and such like.
        //
        if	(tokenNames == nullptr)
        {
            qstrError += qstrTemp.sprintf(" : Missing token (%d)...\n", ex->expecting);
        }
        else
        {
            if	(ex->expecting == ANTLR3_TOKEN_EOF)
            {
                qstrError += qstrTemp.sprintf(" : Missing <EOF>\n");
            }
            else
            {
                qstrError += qstrTemp.sprintf(" : Missing %s \n", tokenNames[ex->expecting]);
            }
        }
        break;

    case	ANTLR3_RECOGNITION_EXCEPTION:

        // Indicates that the recognizer received a token
        // in the input that was not predicted. This is the basic exception type
        // from which all others are derived. So we assume it was a syntax error.
        // You may get this if there are not more tokens and more are needed
        // to complete a parse for instance.
        //
        qstrError += qstrTemp.sprintf(" : syntax error...\n");
        break;

    case    ANTLR3_MISMATCHED_TOKEN_EXCEPTION:

        // We were expecting to see one thing and got another. This is the
        // most common error if we coudl not detect a missing or unwanted token.
        // Here you can spend your efforts to
        // derive more useful error messages based on the expected
        // token set and the last token and so on. The error following
        // bitmaps do a good job of reducing the set that we were looking
        // for down to something small. Knowing what you are parsing may be
        // able to allow you to be even more specific about an error.
        //
        if	(tokenNames == nullptr)
        {
            qstrError += qstrTemp.sprintf(" : syntax error...\n");
        }
        else
        {
            if	(ex->expecting == ANTLR3_TOKEN_EOF)
            {
                qstrError += qstrTemp.sprintf(" : expected <EOF>\n");
            }
            else
            {
                qstrError += qstrTemp.sprintf(" : expected %s ...\n", tokenNames[ex->expecting]);
            }
        }
        break;

    case	ANTLR3_NO_VIABLE_ALT_EXCEPTION:

        // We could not pick any alt decision from the input given
        // so god knows what happened - however when you examine your grammar,
        // you should. It means that at the point where the current token occurred
        // that the DFA indicates nowhere to go from here.
        //
        qstrError += qstrTemp.sprintf(" : cannot match to any predicted input...\n");

        break;

    case	ANTLR3_MISMATCHED_SET_EXCEPTION:

    {
        ANTLR3_UINT32	  count;
        ANTLR3_UINT32	  bit;
        ANTLR3_UINT32	  size;
        ANTLR3_UINT32	  numbits;
        pANTLR3_BITSET	  errBits;

        // This means we were able to deal with one of a set of
        // possible tokens at this point, but we did not see any
        // member of that set.
        //
        qstrError += qstrTemp.sprintf(" : unexpected input...\n  expected one of : ");

        // What tokens could we have accepted at this point in the
        // parse?
        //
        count   = 0;
        errBits = antlr3BitsetLoad		(ex->expectingSet);
        numbits = errBits->numBits		(errBits);
        size    = errBits->size			(errBits);

        if  (size > 0)
        {
            // However many tokens we could have dealt with here, it is usually
            // not useful to print ALL of the set here. I arbitrarily chose 8
            // here, but you should do whatever makes sense for you of course.
            // No token number 0, so look for bit 1 and on.
            //
            for	(bit = 1; bit < numbits && count < 8 && count < size; bit++)
            {
                if  (tokenNames[bit])
                {
                    qstrError += qstrTemp.sprintf("%s%s", count > 0 ? ", " : "", tokenNames[bit]);
                    count++;
                }
            }
            qstrError += "\n";
        }
        else
        {
            qstrError += "Actually dude, we didn't seem to be expecting anything here, or at least\n";
            qstrError += "I could not work out what I was expecting, like so many of us these days!\n";
        }
    }
        break;

    case	ANTLR3_EARLY_EXIT_EXCEPTION:

        // We entered a loop requiring a number of token sequences
        // but found a token that ended that sequence earlier than
        // we should have done.
        //
        qstrError += " : missing elements...\n";
        break;

    default:

        // We don't handle any other exceptions here, but you can
        // if you wish. If we get an exception that hits this point
        // then we are just going to report what we know about the
        // token.
        //
        qstrError += " : syntax not recognized...\n";
        break;
    }

    // Here you have the token that was in error which if this is
    // the standard implementation will tell you the line and offset
    // and also record the address of the start of the line in the
    // input stream. You could therefore print the source line and so on.
    // Generally though, I would expect that your lexer/parser will keep
    // its own map of lines and source pointers or whatever as there
    // are a lot of specific things you need to know about the input
    // to do something like that.
    // Here is where you do it though :-).
    //

    ERR(tr("WQL Error") + qstrError);
}*/
