/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: IbmscomService.h
 ** Started Implementation: 2013/10/10
 ** Description:
 ** 
 ** This interface describes a com service 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IWMSCOMSERVICE_H
#define IWMSCOMSERVICE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>

// Own Includes


// Forwards
class CwmscomData;

// TypeDefs


/* 
 * This interface describes a com service 
 */

class IwmsWebService
{

public:
    virtual ~IwmsWebService(){}
   virtual void execute(CwmscomData* p_pData) = 0;
    virtual void executeDescription(CwmscomData* p_pData) = 0;
   virtual QString getVersion() = 0;
   virtual QString getName() = 0;
   virtual QVariantMap getConfiguration() = 0;

};

Q_DECLARE_INTERFACE(IwmsWebService, "com.wogra.service_interface/1.0")

#endif //
