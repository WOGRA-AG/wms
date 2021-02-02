#ifndef CDMGLOBALCONTEXT_H
#define CDMGLOBALCONTEXT_H

// System and Qt Includes
#include <QMap>
#include <QMutex>

#include "CwmsSynchronizable.h"

// own Includes
#include "datamanager.h"
#include "CdmSettings.h"

// Forwards
class CdmClassManager;
class QThread;


/**
 * @brief The CdmGlobalContext stores data in global not in session context to save memory.
 */
class WMSMANAGER_API CdmGlobalContext : public CwmsSynchronizable
{
private:
    /**
     * @brief the classmanagers of diefferent schemes.
     */
    QMap<long, CdmClassManager*> m_qmClassManagers;
    EdmSettingsMode m_eDmSettingsMode;
    QList<long> m_qlLoadingClassManagers;
    CdmSettings* m_pCdmSettings;

    CdmClassManager *LoadClassManager(long p_lSchemeId);
public:
    CdmGlobalContext(EdmSettingsMode p_eMode);
    virtual ~CdmGlobalContext();
    CdmClassManager* GetClassManager(long p_lSchemeId);
    void DeleteClassManager(long p_lSchemeId);
    void UpdateClassManager(long p_lSchemeId);
    void DeleteAllClassManagers();
    EdmSettingsMode GetMode();
    CdmSettings *GetSettings();
};

#endif // CDMGLOBALCONTEXT_H
