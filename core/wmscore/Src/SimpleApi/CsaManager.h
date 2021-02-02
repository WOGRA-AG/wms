/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CSCRIPTMANAGER
#define CSCRIPTMANAGER

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CdmDataProvider;
class CsaFactory;

class WMSMANAGER_API CsaManager : public CsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;

public:
    CdmDataProvider* getInternals();

public slots:
    QString getWmsVersion();
    QString getWmsBuild();
    QString getApplicationVersion();
    QObject* getCurrentUser();
    int getSessionId();
    QObject *getUserByLogin(QString pLoginName);
    QObject *getUsergroupByName(QString pGroupName);
private:
    CdmDataProvider* m_rpManager;
    CsaManager(CdmDataProvider* p_pManager);
    virtual ~CsaManager();

    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();
    virtual QString getUri() const;
};

#endif //
