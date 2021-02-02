/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: IwmsViewProxy.h
 ** Started Implementation: 2013/06/25
 ** Description:
 ** 
 ** interface for view proxies
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IWMSVIEWPROXY_H
#define IWMSVIEWPROXY_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>

// Own Includes


// Forwards


// TypeDefs


/* 
 * This interface defines the view proxy
 */
class IwmsViewProxy
{
   public:
      virtual ~IwmsViewProxy(){}
      virtual QVariant data(int p_iRole, QVariant p_qvValue) = 0;

};

#endif // IWMSVIEWPROXY_H
