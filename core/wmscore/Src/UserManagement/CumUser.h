/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CUMUSER_H
#define CUMUSER_H


// System and QT Includes
#include <qstring.h>
#include <QList>
#include <QVariant>

// own Includes
#include "CumAccessor.h"


// forwards
class CumUserGroup;
class WMSMANAGER_API CumUser;

/*
 * This class implements an user which can
 * access data over this framework
 */
class CumUser : public CumAccessor 
{
    Q_OBJECT

private:

    /*
       * The list of group in which this user is
       * a member.
       */
    QList<CumUserGroup*> m_qvlUserGroups;

    /*
       * The password of the user
       */
    QString                   m_qstrPassword;

    /*
       * The name of the user
       */
    QString                   m_qstrLastName;

    /*
       * The login of the user
       */
    QString                   m_qstrLogin;

    /*
       * The surname of the user
       */
    QString                   m_qstrFirstName;

    /*
       * Administrator flag
       */
    bool                      m_bAdministrator;

    /*
       * Active flag
       */
    bool                      m_bActive;

    /*
       * The E-mail address of the user
       */
    QString                   m_qstrEmail;

    /*
       * Flag if password is encrypted
       */
    bool                      m_bEncrypted;
    /*
       *  IdentityKey for a User
       */
    QString                   m_qstrIdentityKey;

    /*
       *    Flag if the user can log in to every scheme
       */
    bool                      m_bSchemeIndependent;



public:
    CumUser(long p_lId, CumUserManager* p_pUserManager);
    CumUser(CumUserManager* p_pUserManager);
    virtual ~CumUser(  );
    QString GetPassword() const;
    void SetLogin(  QString p_qstrLogin );
    void SetPassword(  QString p_qstrPassword );
    void SetFirstName(  QString p_qstrSurName );
    void SetLastName(  QString p_qstrName );
    void SetAdministrator(  bool p_bAdministrator );
    void SetIdentityKey( QString p_qstrIdentityKey );
    void SetActive(  bool p_bActive );
    void SetEmail(QString p_qstrEmail);
    QVariant GetVariant() const;
    CumUser(QVariantMap p_qValues, CumUserManager* p_pUserManager);
    void SetEncrypted(bool p_bEncrypted);
    bool IsEncrypted() const;
    QString GetBaseAuth() const;
    QString GetUriInternal() const;
    void SetSchemeIndependent(bool p_bSchemeIndependent);
    bool IsSchemeIndependent() const;
    bool Update(  );

    QString GetCompleteName();
public slots:
    QString GetLogin( ) const;
    QString GetFirstName( ) const;
    QString GetLastName( ) const;
    QString GetIdentitiyKey( ) const;
    bool IsAdministrator( ) const;
    void GetUserGroups( QList<CumUserGroup*>& p_qvlUserGroups);
    QString GetEmail( ) const;
    QString GetDisplayString( ) const;
    virtual bool IsUser( ) const;
    virtual QString GetUri( ) const;
    bool IsActive( ) const;

private:
    void LoadUserGroups(  );
    void DeleteLocalGroups();
};
#endif // //CUMUSER_H
