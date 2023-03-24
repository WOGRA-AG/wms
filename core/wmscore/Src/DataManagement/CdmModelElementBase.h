#ifndef CDMBASEMANAGER_H
#define CDMBASEMANAGER_H

// System and QT Includes


// own Includes
#include "CdmLocatedElement.h"
#include "datamanager.h"
#include "IdmDataAccess.h"

// forwards
class QString;
class CdmDataProvider;
class CdmSettings;
class CdmLogging;
class CdmClassManager;
class CdmContainerManager;
class IdmDataAccess;


/*
 * This class is the base class for all manager classes
 */
class WMSMANAGER_API CdmModelElementBase : public CdmLocatedElement
{
    Q_OBJECT

protected:
    /*
       * The db id of this manager
       */
    QAtomicInteger<qint64> m_lSchemeId;

public:
    CdmModelElementBase(qint64 p_lDbId);
    virtual ~CdmModelElementBase();
    CdmDataProvider* GetDataProvider() const;
    CdmSettings* GetSettings() const;
    CdmClassManager* GetClassManager() const;
    CdmContainerManager* GetContainerManager() const;
    IdmDataAccess* GetDataAccess() const;
    qint64 GetSessionId() const;
    qint64 GetUserId() const;
    void SetSchemeId(qint64 p_lDbId);
    QString CreateUri(QString p_qstrKey,
                      QString p_qstrKeyname,
                      QString p_qstrKeyname2 = "",
                      QString p_qstrKeyname3 = "") const;

public slots:
    QString GetSchemeName() const;
    CdmScheme* GetScheme() const;
    qint64 GetSchemeId() const;

protected:
    bool IsInDeploymentMode() const;
};
#endif // //CDMBASEMANAGER_H
