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
#include <qdom.h>


// own Includes
#include "CumAccessorRight.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:21:11 2005----------*
 * @method  CumAccessorRight::CumAccessorRight               // public                            *
 * @return                                                   //                                   *
 * @comment The cosntructor of accessor rights.                                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 11:21:11 2005----------*/
CumAccessorRight::CumAccessorRight(  )
   : m_lAccessorId(0),
  m_eUmAccessRight(eUmAccessRightNone)
{
   // nothing todo
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:21:22 2005----------*
 * @method  CumAccessorRight::CumAccessorRight               // public                            *
 * @return                                                   //                                   *
 * @param   long p_lAccessorId                               //                                   *
 * @param   EumAccessRight p_eUmAccessRight                  //                                   *
 * @comment The cosntructor of accessor rights.                                                   *
 *----------------last changed: --------------------------------Sa 20. Aug 11:21:22 2005----------*/
CumAccessorRight::CumAccessorRight(  long p_lAccessorId, EumAccessRight p_eUmAccessRight )
   : m_lAccessorId(p_lAccessorId),
  m_eUmAccessRight(p_eUmAccessRight)
{
   // nothing todo
}

/** +-=---------------------------------------------------------Mo 16. Apr 15:09:16 2012----------*
 * @method  CumAccessorRight::CumAccessorRight               // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 15:09:16 2012----------*/
CumAccessorRight::CumAccessorRight(QVariantMap& p_rqvHash)
{
   m_lAccessorId = p_rqvHash["AccessorId"].toInt();
   m_eUmAccessRight = (EumAccessRight)p_rqvHash["RightId"].toInt();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:49:32 2005----------*
 * @method  CumAccessorRight::~CumAccessorRight              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CumAccessorRight                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 12:49:32 2005----------*/
CumAccessorRight::~CumAccessorRight(  )
{
   // nothing todo :-)
}

/** +-=---------------------------------------------------------So 10. Feb 11:44:00 2013----------*
 * @method  CumAccessorRight::GetVariant                     // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:44:00 2013----------*/
QVariant CumAccessorRight::GetVariant() const
{
   QVariantMap qvHash;
   qvHash["AccessorId"] = (int)m_lAccessorId;
   qvHash["RightId"] = m_eUmAccessRight;

   return qvHash;
}

/** +-=---------------------------------------------------------So 10. Feb 11:44:08 2013----------*
 * @method  CumAccessorRight::HasReadAccess                  // public, const                     *
 * @return  bool                                             //                                   *
 * @comment This method checks if the user has the right to access this objectlist.               *
 *----------------last changed: --------------------------------So 10. Feb 11:44:08 2013----------*/
bool CumAccessorRight::HasReadAccess() const
{
   bool bRet = false;

   if(m_eUmAccessRight != eUmAccessRightNone)
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 10. Feb 11:44:16 2013----------*
 * @method  CumAccessorRight::HasWriteAccess                 // public, const                     *
 * @return  bool                                             //                                   *
 * @comment This method checks if this user has write access to the objectlist.                   *
 *----------------last changed: --------------------------------So 10. Feb 11:44:16 2013----------*/
bool CumAccessorRight::HasWriteAccess() const
{
   bool bRet = false;

   if(m_eUmAccessRight == eUmAccessRightWrite)
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:21:40 2005----------*
 * @method  CumAccessorRight::SetAccessorId                  // public                            *
 * @return  void                                             //                                   *
 * @param   long p_lAccessorId                               //                                   *
 * @comment This method sets the accessorid of this accessorright.                                *
 *----------------last changed: --------------------------------Sa 20. Aug 11:21:40 2005----------*/
void CumAccessorRight::SetAccessorId(  long p_lAccessorId )
{
   m_lAccessorId = p_lAccessorId;
}

/** +-=---------------------------------------------------------So 10. Feb 11:44:25 2013----------*
 * @method  CumAccessorRight::GetAccessorId                  // public, const                     *
 * @return  long                                             //                                   *
 * @comment This method returns the accessorid of this right.                                     *
 *----------------last changed: --------------------------------So 10. Feb 11:44:25 2013----------*/
long CumAccessorRight::GetAccessorId() const
{
   return m_lAccessorId;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:21:45 2005----------*
 * @method  CumAccessorRight::SetAccessRight                 // public                            *
 * @return  void                                             //                                   *
 * @param   EumAccessRight p_eUmAccessRight                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 11:21:45 2005----------*/
void CumAccessorRight::SetAccessRight(  EumAccessRight p_eUmAccessRight )
{
   m_eUmAccessRight = p_eUmAccessRight;
}

/** +-=---------------------------------------------------------So 10. Feb 11:44:33 2013----------*
 * @method  CumAccessorRight::GetAccessRight                 // public, const                     *
 * @return  EumAccessRight                                   //                                   *
 * @comment returns the Access Right of this accessor.                                            *
 *----------------last changed: --------------------------------So 10. Feb 11:44:33 2013----------*/
EumAccessRight CumAccessorRight::GetAccessRight() const
{
   return m_eUmAccessRight;
}

/** +-=---------------------------------------------------------So 10. Feb 11:44:41 2013----------*
 * @method  CumAccessorRight::XmlExport                      // public, const                     *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeAccessRights                  //                                   *
 * @comment exports the database to a xml file.                                                   *
 *----------------last changed: --------------------------------So 10. Feb 11:44:41 2013----------*/
void CumAccessorRight::XmlExport(QDomElement& p_rqdeAccessRights) const
{
   QDomDocument qddDocument = p_rqdeAccessRights.ownerDocument();

   QDomElement qdeRoot = qddDocument.createElement("AccessorRight");
   p_rqdeAccessRights.appendChild(qdeRoot);

   qdeRoot.setAttribute("Accessor Id", QString::number(m_lAccessorId));
   qdeRoot.setAttribute("Right",       QString::number(m_eUmAccessRight));
}
