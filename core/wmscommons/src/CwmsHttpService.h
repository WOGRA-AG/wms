#ifndef CWMSHTTPSERVICE_H
#define CWMSHTTPSERVICE_H

// System and Qt Includes

// own Includes
#include "wmscommons.h"

enum EwmsHttpStatusCode
{
    eWmsHttpStatusCodeOk = 200,
    eWmsHttpStatusCodeCreated = 201,
    eWmsHttpStatusCodeAccepted = 202,
    eWmsHttpStatusCodeNoneAuthitiveInfo = 203,
    eWmsHttpStatusCodeNoContent = 204,
    eWmsHttpStatusCodeReset = 205,
    eWmsHttpStatusCodePartialContent = 206,
    eWmsHttpStatusCodeMultiStatus = 207,
    eWmsHttpStatusCodeAlreadyReported = 208,
    eWmsHttpStatusCodeIMUsed = 226,

    eWmsHttpStatusCodeMultipleChoices = 300,
    eWmsHttpStatusCodeMultipleMovePermanently = 301,
    eWmsHttpStatusCodeMultipleFound = 302,
    eWmsHttpStatusCodeMultipleSeeOther = 303,
    eWmsHttpStatusCodeMultipleNotModified = 304,
    eWmsHttpStatusCodeMultipleUseProxy = 305,
    eWmsHttpStatusCodeMultipleTemporaryRedirect = 307,
    eWmsHttpStatusCodeMultiplePermanentRedirect = 308,


    eWmsHttpStatusCodeBadRequest = 400,
    eWmsHttpStatusCodeUnauthorized = 401,
    eWmsHttpStatusCodePaymentRequired = 402,
    eWmsHttpStatusCodeNotFound = 404,
    eWmsHttpStatusCodeMethodNotAllowed = 405,
    eWmsHttpStatusCodeNotAcceptable = 406,
    eWmsHttpStatusCodeProxyAuthenticationRequired = 407,
    eWmsHttpStatusCodeRequestTimeout = 408,
    eWmsHttpStatusCodeConflict = 409,
    eWmsHttpStatusCodeGone = 410,
    eWmsHttpStatusCodeLengthRequired = 411,
    eWmsHttpStatusCodePreconditionFailed = 412,
    eWmsHttpStatusCodeRequestEntityTooLarge = 413,
    eWmsHttpStatusCodeRequestUrlTooLong = 414,
    eWmsHttpStatusCodeUnsupportedMediaType = 415,
    eWmsHttpStatusCodeRequestRangeUnsatifiable = 416,
    eWmsHttpStatusCodeExpectationFailed = 417,
    eWmsHttpStatusCodePolicyNotFulfilled = 420,
    eWmsHttpStatusCodeTooManyConnectionFromYourIP = 421,
    eWmsHttpStatusCodeUnprocessableEntity = 422,
    eWmsHttpStatusCodeLocked = 423,
    eWmsHttpStatusCodeFailedDependency = 424,
    eWmsHttpStatusCodeUnorderedCollection = 425,
    eWmsHttpStatusCodeUpgradeRequired = 426,
    eWmsHttpStatusCodePreconditionRequired = 428,
    eWmsHttpStatusCodeTooManyRequests = 429,
    eWmsHttpStatusCodeRequestHeadersTooLarge = 431,
    eWmsHttpStatusCodeNoResponse = 444,
    eWmsHttpStatusCodeUnavailableForLegalReasons = 451,

    eWmsHttpStatusCodeInternalServerError = 500,
    eWmsHttpStatusCodeNotImplemented = 501,
    eWmsHttpStatusCodeBadGateway = 502,
    eWmsHttpStatusCodeServiceUnavailable = 503,
    eWmsHttpStatusCodeGatewayTimeout = 504,
    eWmsHttpStatusCodeHttpVersionNotSupported = 505,
    eWmsHttpStatusCodeVariantAlsoNegotiates = 506,
    eWmsHttpStatusCodeInsufficientStorage = 507,
    eWmsHttpStatusCodeLoopDetected = 508,
    eWmsHttpStatusCodeBandwithLimitExceeded = 509,
    eWmsHttpStatusCodeNotExtended = 510,

};


class WMSCOMMONS_API CwmsHttpService
{
public:
    static QString GenerateHttpResponse(QString& p_qstrContent, EwmsHttpStatusCode p_eStatusCode);
    static QString TranslateStatusCodeToString(EwmsHttpStatusCode p_eStatusCode);
    static QString GetReturnCodeAsString(EwmsHttpStatusCode p_eStatusCode);
    static QString GenerateHeader(QString &p_qstrContent, EwmsHttpStatusCode p_eStatusCode);
};

#endif // CWMSHTTPSERVICE_H
