

/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMERROR_H
#define CDMERROR_H

// Sytsem and QT Includes
#include <QString>
#include <QLinkedList>
#include <QTextStream>
#include <QFile>
#include <QMutex>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// own Includes
#include "datamanager.h"


// forwards
class QString;
class QTextStream;



enum EdmErrorSeverity
{
    eDmInfo     = 1,
    eDmWarning  = 2,
    eDmError    = 4,
    eDmFatal    = 8
};

// forwards
class CdmLoggingAdaptor;


// MACROS
#ifdef DISABLE_LOGGING
#define INITERRORMANAGER()
#define ERR(a)
#define FATAL(a)
#define WARNING(a)
#define INFO(a)
#define CHKPTR(a) (a != nullptr)
#define EC(a) CdmLogging::a
#define SUCCESSFULL(a)            CdmLogging::WasSuccessFull(a)
#define NOTIMPLEMENTED
#define SETSEVERITY(a)
#define DEPRECATED
#define BODY_TRY
#define BODY_CATCH
#else
#define INITERRORMANAGER()        CdmLogging::CreateLoggingManager();
#define SETSEVERITY(a)            CdmLogging::SetLoggingMode(a);
#define CHKPTR(a)                 CdmLogging::CheckPtr(a,__FILE__, __LINE__)
#define ERR(a)                    CdmLogging::AddErrorLog(__FILE__, a , __LINE__);
#define FATAL(a)                  CdmLogging::AddFatalLog(__FILE__, a , __LINE__);
#define WARNING(a)                CdmLogging::AddWarningLog(__FILE__, a , __LINE__);
#define INFO(a)                   CdmLogging::AddInfoLog(__FILE__, a, __LINE__);
#define SHUTDOWNERRORMANAGER()    CdmLogging::DestroyLoggingManager();
#define EC(a)                     CdmLogging::AddErrorCode(CdmLogging::a)
#define NOTIMPLEMENTED            CdmLogging::AddFatalLog(__FILE__, "Not Implemented" , __LINE__);
#define SUCCESSFULL(a)            CdmLogging::WasSuccessFull(a)
#define DEPRECATED                CdmLogging::Deprecated(__FILE__, __LINE__);
#define BODY_TRY                  try{
#define BODY_CATCH                }catch(...){FATAL("Unhandled exception")}
#endif

#define DELPTR(a)                 if(a){delete a; a = nullptr;}

void WMSMANAGER_API wmsQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

/**
 * This class is for error handling and locking of wms
 * all received events will be stored there and written to file.
 */
class WMSMANAGER_API CdmLogging : public CwmsSynchronizable
{
private:
    /*
       * The singleton pointer
       */
    static CdmLogging* ms_pCdmLogger;

    /*
       * The counter
       */
    int m_iCounter;

    /*
       * The Error Mode
       */
    int m_iLoggingMode;

    /*
       * List of ErrorAdaptors which wants to be notified
       * if a message occurs
       */
    QLinkedList<CdmLoggingAdaptor*> m_qvlAdaptors;

public:

    /*
       * The possible error codes
       */
    enum EdmErrorCode
    {
        eDmOk                =  2,
        eDmTrue              =  1,
        eDmFalse             =  0,

        // Database Errors from -1000 till -1999
        eDmSqlError                                    = -1000,
        eDmUnknownSqlError                             = -1001,
        eDmUnknownClassAccessError                     = -1002,
        eDmInvalidInsertStatement                      = -1003,
        eDmInvalidSelectStatement                      = -1004,
        eDmInvalidSqlResult                            = -1005,
        eDmInvalidDeleteStatement                      = -1006,
        eDmInvalidUpdateStatement                      = -1007,
        eDmNotUniqueQueryResult                        = -1008,
        eDmQueryResultMismatch                         = -1009,
        eDmNoQueryResult                               = -1010,
        eDmUnknownDbAccessError                        = -1011,
        eDmNoDatabaseExists                            = -1012,
        eDmUnknownLoginManagerError                    = -1013,
        eDmUserNotFound                                = -1014,
        eDmSessionNotFound                             = -1015,
        eDmSessionCreationError                        = -1016,
        eDmObjectAccessError                           = -1017,
        eDmObjectDeathLock                             = -1018,
        eDmNoUniqueId                                  = -1019,
        eDmNoNewIdCreated                              = -1020,
        eDmObjectListNotFound                          = -1021,
        eDmObjectNotFound                              = -1022,
        eDmInvalidLockingState                         = -1023,
        eDmInsertvalueBaseDataFailed                   = -1024,
        eDmNoBoolValuesFoundForThisObjectInDb          = -1025,
        eDmNoIntValuesFoundForThisObjectInDb           = -1026,
        eDmNoLongValuesFoundForThisObjectInDb          = -1027,
        eDmNoFloatValuesFoundForThisObjectInDb         = -1028,
        eDmNoDoubleValuesFoundForThisObjectInDb        = -1029,
        eDmNoStringValuesFoundForThisObjectInDb        = -1030,
        eDmNoDateValuesFoundForThisObjectInDb          = -1031,
        eDmNoTimeValuesFoundForThisObjectInDb          = -1032,
        eDmNoDateTimeValuesFoundForThisObjectInDb      = -1033,
        eDmNoObjectRefValuesFoundForThisObjectInDb     = -1034,
        eDmNoObjectListRefValuesFoundForThisObjectInDb = -1035,
        eDmNoCounterValuesFoundForThisObjectInDb       = -1036,
        eDmNoBinaryDocValuesFoundForThisObjectInDb     = -1037,
        eDmNoCharacterDocValuesFoundForThisObjectInDb  = -1038,
        eDmUnknownDBQueryError                         = -1039,
        eDmNoObjectsForQueryFound                      = -1040,
        eDmNoQueryElements                             = -1041,
        eDmNoObjectForQueryInDb                        = -1042,
        eDmNoQueryForBinaryDocumentsPossible           = -1043,
        eDmUnknownQueryValueType                       = -1044,
        eDmUnknownUserQueryError                       = -1045,
        eDmAccessorIdNotFoundInDb                      = -1046,
        eDmUserNotFoundInDb                            = -1047,
        eDmNoUserFoundInDb                             = -1048,
        eDmInternalDbError                             = -1049,
        eDmUserNotUniqueInDb                           = -1050,
        eDmUserGroupNotUniqueInDb                      = -1051,
        eDmNoUserGroupFoundInDb                        = -1052,
        eDmNotSupportedFeatureForThisDb                = -1053,
        eDmNoValueFound                                = -1054,
        eDmInvalidValueType                            = -1055,
        eDmNoDbLoginPossible                           = -1056,
        eDmNoLicenceLeft                               = -1057,
        eDmValidationFailed                            = -1058,
        eDmInsertPackageFailed                         = -1056,
        eDmPreconditionCheckFailed                     = -1057,
        eDmNoUsersInGroup                              = -1058,
        eDmUserIsNotInAGroup                           = -1059,
        eDmEmailAlreadyExist                           = -1060,


        // Internal WMS Data Manager Errors from -2000 till -2999
        eDmNotFound                           = -2000,
        eDmInvalidPtr                         = -2001,
        eDmLockingErr                         = -2002,
        eDmNoFileAccess                       = -2003,
        eDmClassUpdateFailed                  = -2004,
        eDmInvalidSession                     = -2005,
        eDmInvalidCompareType                 = -2006,
        eDmUnknownCompareError                = -2007,
        eDmDefaultValueForbidden              = -2008,
        eDmClassUsageError                    = -2009,
        eDmBaseClassAdditionError             = -2010,
        eDmInvalidId                          = -2011,
        eDmUnknownMemberError                 = -2012,
        eDmNoNewMustValuePossible             = -2013,
        eDmKeynameAlreadyExists               = -2014,
        eDmInvalidClassPtr                    = -2015,
        eDmInvalidMemberPtr                   = -2016,
        eDmBaseClassRemovalError              = -2017,
        eDmBaseClassNotFoundError             = -2018,
        eDmMemberRemovalError                 = -2019,
        eDmUnknownClassError                  = -2020,
        eDmInvalidObjectPtr                   = -2021,
        eDmObjectClassIsDifferent             = -2022,
        eDmUnknownDbError                     = -2023,
        eDmClassAlreadyExist                  = -2024,
        eDmUnallowedValueOperation            = -2025,
        eDmUnknownDataAccessError             = -2026,
        eDmUnknownObjectError                 = -2027,
        eDmInitObjectWithoutMembers           = -2028,
        eDmObjectValueCreationFailed          = -2029,
        eDmObjectValueNotFound                = -2030,
        eDmWrongValueType                     = -2031,
        eDmLockingError                       = -2032,
        eDmInvalidObject                      = -2033,
        eDmWrongObjectClass                   = -2034,
        eDmUnknownObjectListError             = -2035,
        eDmUnknownQueryError                  = -2036,
        eDmUnknownQueryElementType            = -2037,
        eDmUnknownValueError                  = -2038,
        eDmMustValueDeletion                  = -2039,
        eDmMemoryAllocationError              = -2041,
        eDmInvalidBaseState                   = -2042,
        eDmXmlImportError                     = -2043,
        eDmXmlExportError                     = -2044,
        eDmValueConversionError               = -2045,
        eDmWqlError                           = -2046,
        eDmInsufficentPrivileges              = -2047,
        eDmRequiredValueIsMissing             = -2048,
        eDmCircelDependencyInInhertiance      = -2050,



        // Internal WMS User Manager Errors from -3000 till -39999
        eDmUnknownUserManagerError            = -3000,
        eDmInvalidUserId                      = -3001,
        eDmInvalidUserManager                 = -3002,

        // Communication Errors from -4000 till -4999
        eDmUnknownComError                    = -4000,
        eDmServerError                        = -4001,
        eDmCommunicationError                 = -4002,



        eDmLastvalue                          = -9999
    };



private:

    CdmLogging();
    ~CdmLogging(  );

    void AddAdaptorP(CdmLoggingAdaptor* p_pCdmErrorAdaptor);
    void RemoveAdaptorP(CdmLoggingAdaptor* p_pCdmErrorAdaptor);

public:

    static void CreateLoggingManager();
    static void DestroyLoggingManager(  );

    void AddLog(EdmErrorSeverity p_eDmErrorSeverity,
                QString p_qstrErrorModule,
                QString p_qstrEventText,
                int p_iLine);
    static void AddInfoLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine);
    static void AddWarningLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine);
    static void AddErrorLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine);
    static void AddFatalLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine);
    static void SetLoggingMode(int p_iMode);
    static bool CheckPtr(const void* p_pPtr, QString p_qstrFile, int p_iLine);

    template <typename T> static bool CheckPtr(const QScopedPointer<T>& p_pPtr, QString p_qstrFile, int p_iLine)
    {
        bool bRet = false;

        if(!p_pPtr.isNull())
        {
           bRet = true;
        }
        else
        {
           CdmLogging::AddErrorLog(p_qstrFile, "nullptr found\n", p_iLine);
        }

        return bRet;
    }

    static int AddErrorCode(EdmErrorCode p_eDmErrorCode);
    static void AddAdaptor(CdmLoggingAdaptor* p_pCdmErrorAdaptor);
    static void RemoveAdaptor(CdmLoggingAdaptor* p_pCdmErrorAdaptor);
    static bool WasSuccessFull(long p_lReturnCode);
    static bool Deprecated(QString p_qstrFile, int p_iLine);

};

/**
 * This method tries to cast two pointers from source to target.
 * If the cast does not succeeded a info message will be set to error manager.
 */
template<class C, class D> void iCast(C* p_pC, D*& p_rpD)
{
    if(CHKPTR(p_pC))
    {
        try
        {
            p_rpD = dynamic_cast<D*>(p_pC);

            if (!p_rpD)
            {
                INFO("Cast was not successfull WRONG TYPE!!!");
            }
        }
        catch(...)
        {
            INFO("Cast was not successfull WRONG TYPE!!!");
            p_rpD = nullptr;
        }
    }
    else
    {
        p_rpD = nullptr;
    }
};

/**
 * This method tries to cast two pointers from source to target.
 * If the cast does not succeeded a error message will be set to error manager.
 */
template<class C, class D> void eCast(C* p_pC, D*& p_rpD)
{
    if(CHKPTR(p_pC))
    {
        try
        {
            p_rpD = dynamic_cast<D*>(p_pC);

            if (!p_rpD)
            {
                ERR("Cast was not successfull WRONG TYPE!!!");
            }
        }
        catch(...)
        {
            ERR("Cast was not successfull WRONG TYPE!!!");
            p_rpD = nullptr;
        }
    }
    else
    {
        p_rpD = nullptr;
    }
};

/**
 * This method tries to cast two pointers from source to target.
 * If the cast does not succeeded a fatal message will be set to error manager.
 */
template<class C, class D> void fCast(C* p_pC, D*& p_rpD)
{
    if(CHKPTR(p_pC))
    {
        try
        {
            p_rpD = dynamic_cast<D*>(p_pC);

            if (!p_rpD)
            {
                FATAL("Cast was not successfull WRONG TYPE!!!");
            }
        }
        catch(...)
        {
            FATAL("Cast was not successfull WRONG TYPE!!!");
            p_rpD = nullptr;
        }
    }
    else
    {
        p_rpD = nullptr;
    }
};

#endif

