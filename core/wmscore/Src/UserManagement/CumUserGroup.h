/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CUMUSERGROUP_H
#define CUMUSERGROUP_H

// System and QT Includes
#include <QList>
#include <QVariant>

// own Includes
#include "datamanager.h"
#include "CumAccessor.h"


// forwards
class CumUser;
class WMSMANAGER_API CumUserGroup;
/* 
 * This class implements a usergroup.
 */
class CumUserGroup : public CumAccessor 
{
    Q_OBJECT

private:
    QString m_qstrGroupName;

public:
    CumUserGroup(qint64 p_lId, CumUserManager* p_pUserManager);
    CumUserGroup(qint64 p_lId, QString p_qstrGroupName, CumUserManager* p_pUserManager);
    CumUserGroup(QVariantMap& p_qValues, CumUserManager* p_pUserManager);
    virtual ~CumUserGroup();
    void SetGroupName(QString p_qstrGroupName);
    QVariant GetVariant() const;
    void SetVariant(QVariantMap& p_rqvHash);
    bool HasUser(qint64 p_lUserId) const;
    QString GetUriInternal() const;
    QVariant GetVariantForDeplyoment() const;
    void Update();

    virtual bool IsUserGroup() const;

public slots:
    QString GetGroupName() const;
    void GetUserListNewPointers(QList<CumUser*>& p_qvlUsers) const;
    virtual bool IsGroup() const;
    virtual QString GetUri() const;
};
#endif // //CUMUSERGROUP_H
