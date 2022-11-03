/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: wmsusermanagerglobal.h
 ** Started Implementation: 2011/09/06
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef WMSUSERMANAGERGLOBAL_H
#define WMSUSERMANAGERGLOBAL_H

#ifdef WURZELBLA
#define slots
#endif //

#ifdef WIN32
#ifdef WMSUSERMANAGERDLL_LIB
#define WMSUSERMANAGER_API __declspec(dllexport)
#else
#define WMSUSERMANAGER_API __declspec(dllimport)
#endif //
#else
#define WMSUSERMANAGER_API
#endif //

#endif // WMSUSERMANAGERGLOBAL_H
