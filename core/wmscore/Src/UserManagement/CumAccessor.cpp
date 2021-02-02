/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>


// own Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CumUserManager.h"
#include "CumAccessor.h"

CumAccessor::CumAccessor(long p_lId, CumUserManager* p_pUserManager)
   : m_lId(p_lId),
     m_rpUserManager(p_pUserManager)
{
}

CumAccessor::~CumAccessor(  )
{
}

void CumAccessor::SetId(int p_iId)
{
   m_lId = p_iId;
}

void CumAccessor::SetUserManager(CumUserManager *p_pUserManager)
{
    m_rpUserManager = p_pUserManager;
}

/** +-=---------------------------------------------------------So 10. Feb 11:43:23 2013----------*
 * @method  CumAccessor::GetId                               // public, const, slots              *
 * @return  long                                             //                                   *
 * @comment returns the AccessorId                                                                *
 *----------------last changed: --------------------------------So 10. Feb 11:43:23 2013----------*/
long CumAccessor::GetId() const
{
   return m_lId;
}

/** +-=---------------------------------------------------------Di 20. Nov 14:00:07 2012----------*
 * @method  CumAccessor::GetUserManager                      // public, slots                     *
 * @return  CumUserManager*                                  //                                   *
 * @comment This method returns the pointer to the user manager.                                  *
 *----------------last changed: --------------------------------Di 20. Nov 14:00:07 2012----------*/
CumUserManager* CumAccessor::GetUserManager() const
{
    if (!m_rpUserManager)
    {
        CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pProvider))
        {
            return pProvider->GetUserManager();
        }
    }

   return m_rpUserManager;
}

/** +-=---------------------------------------------------------Di 16. Jul 16:51:53 2013----------*
 * @method  CumAccessor::IsUser                              // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment returns if this accessor is a user or not                                             *
 *----------------last changed: --------------------------------Di 16. Jul 16:51:53 2013----------*/
bool CumAccessor::IsUser() const
{
   return false;
}

/** +-=---------------------------------------------------------Di 16. Jul 16:52:01 2013----------*
 * @method  CumAccessor::IsGroup                             // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment returns if this accessor is a usergroup or not.                                       *
 *----------------last changed: --------------------------------Di 16. Jul 16:52:01 2013----------*/
bool CumAccessor::IsGroup() const
{
   return false;
}

void CumAccessor::AddSchemeUri(QString p_qstrUri)
{
    if (!p_qstrUri.isEmpty() && !m_qstrlSchemes.contains(p_qstrUri))
    {
        m_qstrlSchemes.append(p_qstrUri);
    }
}

void CumAccessor::RemoveSchemeUri(QString p_qstrUri)
{
    m_qstrlSchemes.removeAll(p_qstrUri);
}

QStringList CumAccessor::GetSchemeList()
{
    return m_qstrlSchemes;
}
