/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CUMACCESSOR_H
#define CUMACCESSOR_H

// System and QT Includes


// own Includes
#include "CdmLocatedElement.h"
#include "datamanager.h"

// forwards
class CumUserManager;

enum EumUserGroupType
{
   eUmUserGroupTypeNone,
   eUmUserGroupTypeUser,
   eUmUserGroupTypeGroup
};

/*
 * This class is the base class for user
 * and user groups. It implements base functionality
 */
class WMSMANAGER_API CumAccessor : public CdmLocatedElement
{
    Q_OBJECT

    friend class CumUserManager;

private:
    long m_lId;
    CumUserManager* m_rpUserManager;
    QStringList m_qstrlSchemes;
    void SetUserManager(CumUserManager* p_pUserManager);

public:
    CumAccessor(long p_lId, CumUserManager* p_pUserManager);
    virtual ~CumAccessor();

    void AddSchemeUri(QString p_qstrUri);
    QStringList GetSchemeList();
    void RemoveSchemeUri(QString p_qstrUri);

public slots:
    long GetId( ) const;
    CumUserManager* GetUserManager( ) const;
    virtual bool IsUser( ) const;
    virtual bool IsGroup( ) const;

protected:
    void SetId(int p_iId);
};
#endif // //CUMACCESSOR_H
