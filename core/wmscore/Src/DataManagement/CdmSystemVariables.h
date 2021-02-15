/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmSystemVariables.h
 ** Started Implementation: 2012/09/13
 ** Description:
 ** 
 ** implements functions for returning system values
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMSYSTEMVARIABLES_H
#define CDMSYSTEMVARIABLES_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QStringList>

// Own Includes
#include "datamanager.h"

// Forwards


// TypeDefs


/* 
 * This class implements functions for returning system values
 */
class WMSMANAGER_API CdmSystemVariables
{
   private:
      static QStringList m_sqstrlVariables;
      static QString m_sqstrOpen;
      static QString m_sqstrClose;

   public:
    static QString GetValueAsString(QString p_qstrVariable);
    static bool IsSystemValue(QString p_qstrValue);
    static QStringList GetSystemVariables();

private:
    static void FillVariablesInList();
    static bool RemoveBraces(QString& p_qstrValue);
};

#endif //
