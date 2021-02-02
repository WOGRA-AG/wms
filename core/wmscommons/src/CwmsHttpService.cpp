
// System and QT Includes
#include <QDateTime>

// Own Includes
#include "CwmsHttpService.h"



QString CwmsHttpService::GenerateHttpResponse(QString& p_qstrContent, EwmsHttpStatusCode p_eStatusCode)
{
    QString qstrResult;

    if (p_qstrContent.isEmpty())
    {
       p_qstrContent = "WOGRA Application Server V 0.1.0\n\n";
       p_qstrContent += "copyright by WOGRA Consulting GmbH\n\n";
       p_qstrContent += "Invalid request.\n";
       p_qstrContent += "No response from Server.\n";
    }

    qstrResult += GenerateHeader(p_qstrContent, p_eStatusCode);
    qstrResult += p_qstrContent;
    return qstrResult;
}


QString CwmsHttpService::GenerateHeader(QString& p_qstrContent, EwmsHttpStatusCode p_eStatusCode)
{
    // send answer
    QByteArray qbResult = p_qstrContent.toUtf8();
    int iContentLength = qbResult.size();

    QString qstrHeader = "HTTP/1.1 " + QString::number(p_eStatusCode) + "\r\n";
    qstrHeader += "Date: " + QDateTime::currentDateTime().toString() + "\r\n";
    qstrHeader += "Server: WOGRA Application Server\r\n";
    qstrHeader += "Content-Length: " + QString::number(iContentLength) +"\r\n";
    qstrHeader += "Connection: close\r\n";
    qstrHeader += "Access-Control-Allow-Origin: *\r\n";
    qstrHeader += "Content-Type: application/json; charset=utf-8\r\n";
    qstrHeader += "\r\n";

    return qstrHeader;
}

QString CwmsHttpService::GetReturnCodeAsString(EwmsHttpStatusCode p_eStatusCode)
{
   return QString::number(p_eStatusCode) + " " + CwmsHttpService::TranslateStatusCodeToString(p_eStatusCode);
}


QString CwmsHttpService::TranslateStatusCodeToString(EwmsHttpStatusCode p_eStatusCode)
{
   QString qstrRet;

   switch(p_eStatusCode)
   {
   case eWmsHttpStatusCodeOk:
       qstrRet = "OK";
       break;
   case eWmsHttpStatusCodeCreated:
       qstrRet = "Created";
       break;
   case eWmsHttpStatusCodeAccepted:
       qstrRet = "Accepted";
       break;
   case eWmsHttpStatusCodeNoneAuthitiveInfo:
       qstrRet = "None Authoritive Info";
       break;
   case eWmsHttpStatusCodeNoContent:
       qstrRet = "No Content";
       break;
   case eWmsHttpStatusCodeReset :
       qstrRet = "Code Reset";
       break;
   case eWmsHttpStatusCodePartialContent:
       qstrRet = "Partial Content";
       break;
   case eWmsHttpStatusCodeMultiStatus:
       qstrRet = "Multi Status";
       break;
   case eWmsHttpStatusCodeAlreadyReported:
       qstrRet = "Already Reported";
       break;
   case eWmsHttpStatusCodeIMUsed:
       qstrRet = "IM Used";
       break;
   case eWmsHttpStatusCodeMultipleChoices:
       qstrRet = "Multiple Choices";
       break;
   case eWmsHttpStatusCodeMultipleMovePermanently:
       qstrRet = "Moved Permanently";
       break;
   case eWmsHttpStatusCodeMultipleFound:
       qstrRet = "Multiple Found";
       break;
   case eWmsHttpStatusCodeMultipleSeeOther:
       qstrRet = "Multiple See Other";
       break;
   case eWmsHttpStatusCodeMultipleNotModified:
       qstrRet = "Multiple Not Modified";
       break;
   case eWmsHttpStatusCodeMultipleUseProxy:
       qstrRet = "Use Proxy";
       break;
   case eWmsHttpStatusCodeMultipleTemporaryRedirect:
       qstrRet = "Temporary Redirect";
       break;
   case eWmsHttpStatusCodeMultiplePermanentRedirect:
       qstrRet = "Permanent Redirect";
       break;
   case eWmsHttpStatusCodeBadRequest:
       qstrRet = "Bad Request";
       break;
   case eWmsHttpStatusCodeUnauthorized:
       qstrRet = "Unauthorized";
       break;
   case eWmsHttpStatusCodePaymentRequired:
       qstrRet = "Payment Required";
       break;
   case eWmsHttpStatusCodeNotFound:
       qstrRet = "Not Found";
       break;
   case eWmsHttpStatusCodeMethodNotAllowed:
       qstrRet = "Method not Allowed";
       break;
   case eWmsHttpStatusCodeNotAcceptable:
       qstrRet = "Not Acceptable";
       break;
   case eWmsHttpStatusCodeProxyAuthenticationRequired:
       qstrRet = "Proxy Authentication Required";
       break;
   case eWmsHttpStatusCodeRequestTimeout:
       qstrRet = "Request Timeout";
       break;
   case eWmsHttpStatusCodeConflict:
       qstrRet = "Conflict";
       break;
   case eWmsHttpStatusCodeGone:
       qstrRet = "Gone";
       break;
   case eWmsHttpStatusCodeLengthRequired:
       qstrRet = "Length Required";
       break;
   case eWmsHttpStatusCodePreconditionFailed:
       qstrRet = "Precondition Failed";
       break;
   case eWmsHttpStatusCodeRequestEntityTooLarge:
       qstrRet = "Request Entity too large";
       break;
   case eWmsHttpStatusCodeRequestUrlTooLong:
       qstrRet = "Request Url too long";
       break;
   case eWmsHttpStatusCodeUnsupportedMediaType:
       qstrRet = "Unsupported Media Type";
       break;
   case eWmsHttpStatusCodeRequestRangeUnsatifiable:
       qstrRet = "Unsatifiable";
       break;
   case eWmsHttpStatusCodeExpectationFailed:
       qstrRet = "Expectation Failed";
       break;
   case eWmsHttpStatusCodePolicyNotFulfilled:
       qstrRet = "Policy Not fulfilled";
       break;
   case eWmsHttpStatusCodeTooManyConnectionFromYourIP:
       qstrRet = "Too many connections from your IP";
       break;
   case eWmsHttpStatusCodeUnprocessableEntity:
       qstrRet = "Unprocessable Entity";
       break;
   case eWmsHttpStatusCodeLocked:
       qstrRet = "Locked";
       break;
   case eWmsHttpStatusCodeFailedDependency:
       qstrRet = "Failed Dependenvcy";
       break;
   case eWmsHttpStatusCodeUnorderedCollection:
       qstrRet = "Unordered Collection";
       break;
   case eWmsHttpStatusCodeUpgradeRequired:
       qstrRet = "Upgrade Required";
       break;
   case eWmsHttpStatusCodePreconditionRequired:
       qstrRet = "Precondition Required";
       break;
   case eWmsHttpStatusCodeTooManyRequests:
       qstrRet = "Too many Requests";
       break;
   case eWmsHttpStatusCodeRequestHeadersTooLarge:
       qstrRet = "Request Headers too large";
       break;
   case eWmsHttpStatusCodeNoResponse:
       qstrRet = "No Response";
       break;
   case eWmsHttpStatusCodeUnavailableForLegalReasons:
       qstrRet = "Unavailable for legal reasons";
       break;
   case eWmsHttpStatusCodeInternalServerError:
       qstrRet = "Internal Server error";
       break;
   case eWmsHttpStatusCodeNotImplemented:
       qstrRet = "Not implemented";
       break;
   case eWmsHttpStatusCodeBadGateway:
       qstrRet = "Bad Gateway";
       break;
   case eWmsHttpStatusCodeServiceUnavailable:
       qstrRet = "Unavailable";
       break;
   case eWmsHttpStatusCodeGatewayTimeout:
       qstrRet = "Timeout";
       break;
   case eWmsHttpStatusCodeHttpVersionNotSupported:
       qstrRet = "Not supported";
       break;
   case eWmsHttpStatusCodeVariantAlsoNegotiates:
       qstrRet = "Variant also negotiates";
       break;
   case eWmsHttpStatusCodeInsufficientStorage:
       qstrRet = "Insufficient storage";
       break;
   case eWmsHttpStatusCodeLoopDetected:
       qstrRet = "Loop detected";
       break;
   case eWmsHttpStatusCodeBandwithLimitExceeded:
       qstrRet = "Bandwidth Limit exceeded";
       break;
   case eWmsHttpStatusCodeNotExtended:
       qstrRet = "Not extended";
       break;
    default:
        qstrRet = "Unknown";
        break;
    }

   return qstrRet;
}

