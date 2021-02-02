/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#ifdef WIN32
#ifdef WMSMANAGER_EXPORTS
#define WMSMANAGER_API __declspec(dllexport)
#else
#define WMSMANAGER_API __declspec(dllimport)
#endif //
#else
#define WMSMANAGER_API
#include <wchar.h>
#endif //


#endif //
