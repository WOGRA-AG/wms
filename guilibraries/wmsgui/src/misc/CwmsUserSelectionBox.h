#ifndef CWMSUSERSELECTIONBOX_H
#define CWMSUSERSELECTIONBOX_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QComboBox>
#include <QMap>
#include <QList>

// Own Includes
#include "wmsgui.h"


// Forwards
class CumUser;
class CumUserGroup;

// Enumerations

/* 
 * This class implements the selection box for users
 */
class WMSGUI_API CwmsUserSelectionBox : public QComboBox
{
private:
    bool m_bOnlyActiveUsers;

public:
    CwmsUserSelectionBox( QWidget* p_pqwParent = NULL);
    virtual ~CwmsUserSelectionBox( );
    void SetCurrentUser(int p_iUserId);
    void SetCurrentUser(const CumUser* p_CumUser);
    CumUser* GetSelectedUser();
    int GetSelectedUserId();
    void FillComboBoxWithGivenUserGroup(CumUserGroup *pUserGroup);

    void SetOnlyActiveUser(bool p_bOnlyActive);
    bool GetOnlyActiveUser();
    void Refresh();
private:
    void FillComboBox();
    void GetUserList(QList<CumUser*>& p_rqllUsers);
    QString GetUserAsSelectionString(CumUser *p_pUser);
    void FillUsersToComboBox(QList<CumUser*> qllUsers);
};

#endif //
