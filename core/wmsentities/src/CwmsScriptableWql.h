/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptableWql.h
 ** Started Implementation: 2012/11/09
 ** Description:
 ** 
 ** implements the script interface for js methods using wql
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSCRIPTABLEWQL_H
#define CWMSSCRIPTABLEWQL_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>
#include <QVariant>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CdmQuery;
class CdmQueryEnhanced;


// TypeDefs


/* 
 * This class implements the script interface for js methods using wql
 */
class BASETOOLS_API CwmsScriptableWql : public CwmsScriptableBase
{
   Q_OBJECT

   public:
    CwmsScriptableWql();
    virtual ~CwmsScriptableWql();

    public slots:
    QObject* execute(QString p_qstrWql);

};

#endif // CWMSSCRIPTABLEWQL_H
